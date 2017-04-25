////////////////////////////////////////////////////////////////////////
// Class:       ElectronSelectionAna
// Plugin Type: analyzer (art v2_06_03)
// File:        ElectronSelectionAna_module.cc
//
// Generated at Mon Apr 24 16:33:33 2017 by Corey Adams using cetskelgen
// from cetlib version v2_03_00.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "ElectronEventSelectionAlg.h"

#include "TTree.h"
#include "TFile.h"

constexpr int kMaxVertices   = 10;                  ///< max number of PandoraNu neutrino candidate vertices
constexpr int kMaxTruth      = 10;                  ///< max number of neutrino Interactions in the spill

namespace lee {
  class ElectronSelectionAna;
}


class lee::ElectronSelectionAna : public art::EDAnalyzer {
public:
  explicit ElectronSelectionAna(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  void reconfigure(fhicl::ParameterSet const & p);

  // Plugins should not be copied or assigned.
  ElectronSelectionAna(ElectronSelectionAna const &) = delete;
  ElectronSelectionAna(ElectronSelectionAna &&) = delete;
  ElectronSelectionAna & operator = (ElectronSelectionAna const &) = delete;
  ElectronSelectionAna & operator = (ElectronSelectionAna &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;


private:
  // functions
  void fillTree(art::Event const & e);

  // variables
  lee::ElectronEventSelectionAlg fElectronEventSelectionAlg;

  TFile*      fTFile;
  TTree*      fTree;

  //Truth information
  Int_t     mcevts_truth;                               ///< number of neutrino Interactions in the spill
  Int_t     nuPDG_truth[kMaxTruth];                     ///< neutrino PDG code
  Int_t     ccnc_truth[kMaxTruth];                      ///< 0=CC 1=NC
  Int_t     mode_truth[kMaxTruth];                      ///< 0=QE/El, 1=RES, 2=DIS, 3=Coherent production
  Float_t   enu_truth[kMaxTruth];                       ///< true neutrino energy
  Float_t   nuvtxx_truth[kMaxTruth];                    ///< neutrino vertex x
  Float_t   nuvtxy_truth[kMaxTruth];                    ///< neutrino vertex y
  Float_t   nuvtxz_truth[kMaxTruth];                    ///< neutrino vertex z

  //PandoraNu information
  Short_t nnuvtx;                                       ///< Number of PandoraNu neutrino candidate vertices
  Float_t nuvtxx[kMaxVertices];                         ///< x coordinate
  Float_t nuvtxy[kMaxVertices];                         ///< y coordinate
  Float_t nuvtxz[kMaxVertices];                         ///< z coordinate
  Short_t nuvtxpdg[kMaxVertices];                       ///< PDG code assigned by PandoraNu
  std::vector<TVector3> center_of_charge[kMaxVertices]  ///< Center of deposited charge 

  //Optical information
  Short_t nfls;                                         ///< Number of reconstructed flashes
  std::vector<Float_t> flsTime;                         ///< Flash time (us)
  std::vector<Float_t> flsPe;                           ///< Flash total PE
  std::vector<Float_t> flsYcenter;                      ///< Flash Y center (cm)
  std::vector<Float_t> flsZcenter;                      ///< Flash Z center (cm)
  std::vector<Float_t> flsYwidth;                       ///< Flash Y width (cm)
  std::vector<Float_t> flsZwidth;                       ///< Flash Z width (cm)
};

void lee::ElectronSelectionAna::reconfigure(fhicl::ParameterSet const & p){
  fElectronEventSelectionAlg.reconfigure(p.get<fhicl::ParameterSet>("ElectronSelectionAlg"));
}


lee::ElectronSelectionAna::ElectronSelectionAna(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p)  // ,
 // More initializers here.
{
  //initialize output tree
  std::cout << "Initializing output tree..." << std::endl;
  art::ServiceHandle<art::TFileService> tfs;
  fTFile = new TFile("FlashOutput.root", "RECREATE");
  fTree  = tfs->make<TTree>("flashtree","FlashAnalysis Tree");

  //Set branches for truth information 
  fTree->Branch("mcevts_truth", &mcevts_truth,  "mcevts_truth/I"               );
  fTree->Branch("nuPDG_truth",  nuPDG_truth,    "nuPDG_truth[mcevts_truth]/I"  );
  fTree->Branch("ccnc_truth",   ccnc_truth,     "ccnc_truth[mcevts_truth]/I"   );
  fTree->Branch("mode_truth",   mode_truth,     "mode_truth[mcevts_truth]/I"   );
  fTree->Branch("enu_truth",    enu_truth,      "enu_truth[mcevts_truth]/F"    );
  fTree->Branch("nuvtxx_truth", nuvtxx_truth,   "nuvtxx_truth[mcevts_truth]/F" );
  fTree->Branch("nuvtxy_truth", nuvtxy_truth,   "nuvtxy_truth[mcevts_truth]/F" );
  fTree->Branch("nuvtxz_truth", nuvtxz_truth,   "nuvtxz_truth[mcevts_truth]/F" );

  //Set branches for PandoraNU information
  fTree->Branch("nnuvtx",     &nnuvtx,    "nnuvtx/S"             );
  fTree->Branch("nuvtxx",     nuvtxx,     "nuvtxx[nnuvtx]/F"     );
  fTree->Branch("nuvtxy",     nuvtxy,     "nuvtxy[nnuvtx]/F"     );
  fTree->Branch("nuvtxz",     nuvtxz,     "nuvtxz[nnuvtx]/F"     ); 
  fTree->Branch("nuvtxpdg",   nuvtxpdg,   "nuvtxpdg[nnuvtx]/S"   );
  fTree->Branch("chrgecenter",chrgecenter,"chrgecenter[nnuvtx]/S");  //????????????????????????????????

  //Set branches for optical information
  fTree->Branch("nfls",       &nfls,       "nfls/S"             );
  fTree->Branch("flsTime",    &flsTime,    "flash_time[nfls]/F" );
  fTree->Branch("flsPe",      &flsPe,      "flsPe[nfls]/F"      );
  fTree->Branch("flsYcenter", &flsYcenter, "flsYcenter[nfls]/F" );
  fTree->Branch("flsZcenter", &flsZcenter, "flsZcenter[nfls]/F" );
  fTree->Branch("flsYwidth",  &flsYwidth,  "flsYwidth[nfls]/F"  );
  fTree->Branch("flsZwidth",  &flsZwidth,  "flsZwidth[nfls]/F"  );

  this->reconfigure(pset);
}

lee::ElectronSelectionAna::~ElectronSelectionAna()
{

  //wrrite output file and tree
  std::cout << "Writing output..." << std::endl;
  fTFile->cd();
  fTree->Write("flashtree");
  fTFile->Close();
  std::cout << "Done!" << std::endl;
}

void lee::ElectronSelectionAna::analyze(art::Event const & e)
{
  // Implementation of required member function here.
  fillTree(art::Event const & e);

  bool event_passed = fElectronEventSelectionAlg.eventSelected(e);

  if (event_passed){
    // Find out how many passing neutrino candidates there are:
    for (size_t i = 0; i < fElectronEventSelectionAlg.get_n_neutrino_candidates(); i ++){
      if (fElectronEventSelectionAlg.get_neutrino_candidate_passed().at(i)){
        std::cout << "Candidate " << i << " passed." << std::endl;
      }
    }
  }

  return;
}

void lee::ElectronSelectionAna::fillTree(art::Event const & e)
{


}


DEFINE_ART_MODULE(lee::ElectronSelectionAna)

