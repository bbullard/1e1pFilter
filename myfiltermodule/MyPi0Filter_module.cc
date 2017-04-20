////////////////////////////////////////////////////////////////////////
// Class:       MyFilter
// Module Type: filter
// File:        MyFilter_module.cc
//
// Generated at Mon Oct  3 13:17:19 2016 by Lorena Escudero Sanchez using artmod
// from cetpkgsupport v1_10_02.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include <memory>

#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "larcore/Geometry/Geometry.h"
#include "lardataobj/RawData/TriggerData.h"

#include "lardataobj/RecoBase/PFParticle.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Shower.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/MCBase/MCShower.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "canvas/Persistency/Common/FindOneP.h"
#include "canvas/Utilities/InputTag.h"

#include "larpandora/LArPandoraInterface/LArPandoraHelper.h"

#include "TTree.h"
#include "TFile.h"
#include "TEfficiency.h"
#include "TH1F.h"

double x_start = 0;
double x_end = 256.35;
double y_start = -116.5;
double y_end = 116.5;
double z_start = 0;
double z_end = 1036.8;
double fidvol = 10;

double distance(double a[3], double b[3]) {
  double d = 0;

  for (int i = 0; i < 3; i++) {
    d += pow((a[i]-b[i]),2);
  }

  return sqrt(d);
}

using namespace lar_pandora;


class MyPi0Filter;

class MyPi0Filter : public art::EDFilter {
public:
  explicit MyPi0Filter(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  MyPi0Filter(MyPi0Filter const &) = delete;
  MyPi0Filter(MyPi0Filter &&) = delete;
  MyPi0Filter & operator = (MyPi0Filter const &) = delete;
  MyPi0Filter & operator = (MyPi0Filter &&) = delete;

  // Required functions.
  bool filter(art::Event & e) override;

  // Selected optional functions.
  void beginJob() override;
  void reconfigure(fhicl::ParameterSet const & p) override;

private:
  TEfficiency * e_energy;
  TH1F * h_track_length;

  int m_nTracks;
  double m_fidvolXstart;
  double m_fidvolXend;

  double m_fidvolYstart;
  double m_fidvolYend;

  double m_fidvolZstart;
  double m_fidvolZend;

  double m_trackLength;

  bool is_fiducial(double x[3]) const;

  // Declare member data here.

};


MyPi0Filter::MyPi0Filter(fhicl::ParameterSet const & p)
// :
// Initialize member data here.
{
  art::ServiceHandle<art::TFileService> tfs;
  e_energy = tfs->make<TEfficiency>("e_energy",";#nu_{e} energy [GeV];",30,0,3);
  h_track_length = tfs->make<TH1F>("h_track_length",";Track length [cm]; N. Entries / 2 cm",150,0,300);

  this->reconfigure(p);

  // Call appropriate produces<>() functions here.
}

bool MyPi0Filter::is_fiducial(double x[3]) const
{
  bool is_x = x[0] > (x_start+m_fidvolXstart) && x[0] < (x_end-m_fidvolXend);
  bool is_y = x[1] > (y_start+m_fidvolYstart) && x[1] < (y_end-m_fidvolYend);
  bool is_z = x[2] > (z_start+m_fidvolZstart) && x[2] < (z_end-m_fidvolZend);
  return is_x && is_y && is_z;
}

bool MyPi0Filter::filter(art::Event & evt)
{
  bool pass = false;

  art::InputTag pandoraNu_tag { "pandoraNu" };

  int nu_candidates = 0;

  try {
    auto const& pfparticle_handle = evt.getValidHandle< std::vector< recob::PFParticle > >( pandoraNu_tag );
    auto const& pfparticles(*pfparticle_handle);

    art::FindOneP< recob::Vertex > vertex_per_pfpart(pfparticle_handle, evt, pandoraNu_tag);

    for (size_t ipf = 0; ipf < pfparticles.size(); ipf++) {

      bool is_neutrino = (abs(pfparticles[ipf].PdgCode()) == 12 || abs(pfparticles[ipf].PdgCode()) == 14) && pfparticles[ipf].IsPrimary();

      // Is a nu_e or nu_mu PFParticle?
      if (!is_neutrino) continue;

      int showers = 0;
      int tracks = 0;

      double neutrino_vertex[3];

      auto const& neutrino_vertex_obj = vertex_per_pfpart.at(ipf);
      neutrino_vertex_obj->XYZ(neutrino_vertex); // PFParticle neutrino vertex coordinates

      // Is the vertex within fiducial volume?
      if (!is_fiducial(neutrino_vertex)) continue;

      // Loop over the neutrino daughters and check if there is a shower and a track
      for (auto const& pfdaughter: pfparticles[ipf].Daughters()) {


        if (pfparticles[pfdaughter].PdgCode() == 11) {
          art::FindOneP< recob::Shower > shower_per_pfpart(pfparticle_handle, evt, pandoraNu_tag);
          auto const& shower_obj = shower_per_pfpart.at(pfdaughter);
          bool contained_shower = false;
          double start_point[3];
          double end_point[3];

          double shower_length = shower_obj->Length();
          for (int ix = 0; ix < 3; ix++) {
            start_point[ix] = shower_obj->ShowerStart()[ix];
            end_point[ix] = shower_obj->ShowerStart()[ix]+shower_length*shower_obj->Direction()[ix];
          }

          contained_shower = is_fiducial(start_point) && is_fiducial(end_point);
          // TODO flash position check
          if (contained_shower) showers++;

        }

        if (pfparticles[pfdaughter].PdgCode() == 13) {
          art::FindOneP< recob::Track > track_per_pfpart(pfparticle_handle, evt, pandoraNu_tag);
          auto const& track_obj = track_per_pfpart.at(pfdaughter);

          if (track_obj->Length() < m_trackLength) tracks++;
          h_track_length->Fill(track_obj->Length());
        }

      } // end for pfparticle daughters

      if (showers >= 1 && tracks >= m_nTracks) {
        //closest_distance = std::min(distance(neutrino_vertex,true_neutrino_vertex),closest_distance);
        nu_candidates++;
      }

    } // end for pfparticles

    //e_energy->Fill(pass, nu_energy);

  } catch (...) {
    std::cout << "NO RECO DATA PRODUCTS" << std::endl;
  }

  if (nu_candidates >= 1) pass = true;
  if (pass) {
    std::cout << "EVENT SELECTED" << std::endl;
  }

  return pass;
}

void MyPi0Filter::beginJob()
{
  // Implementation of optional member function here.
}

void MyPi0Filter::reconfigure(fhicl::ParameterSet const & p)
{
  // Implementation of optional member function here.
  m_nTracks = p.get<int>("nTracks",1);

  m_trackLength = p.get<int>("trackLength",100);

  m_fidvolXstart = p.get<double>("fidvolXstart",10);
  m_fidvolXend = p.get<double>("fidvolXstart",10);

  m_fidvolYstart = p.get<double>("fidvolYstart",20);
  m_fidvolYend = p.get<double>("fidvolYend",20);

  m_fidvolZstart = p.get<double>("fidvolZstart",10);
  m_fidvolZend = p.get<double>("fidvolZend",50);

}

DEFINE_ART_MODULE(MyPi0Filter)
