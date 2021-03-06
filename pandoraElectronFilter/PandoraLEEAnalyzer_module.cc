////////////////////////////////////////////////////////////////////////
// Class:       PandoraLEEAnalyzer
// Module Type: analyzer
// File:        PandoraLEEAnalyzer_module.cc
//
// Generated at Thu Jun 23 00:24:52 2016 by Lorena Escudero Sanchez using artmod
// from cetpkgsupport v1_10_02.
////////////////////////////////////////////////////////////////////////

#include "PandoraLEEAnalyzer.h"
#include "larevt/SpaceChargeServices/SpaceChargeService.h"

lee::PandoraLEEAnalyzer::PandoraLEEAnalyzer(fhicl::ParameterSet const &pset)
    : EDAnalyzer(pset) // ,
// More initializers here.
{

  // create output tree
  art::ServiceHandle<art::TFileService> tfs;
  // myTFile = new TFile("PandoraLEEAnalyzerOutput.root", "RECREATE");
  myTTree = tfs->make<TTree>("pandoratree", "PandoraAnalysis Tree");

  myPOTTTree = tfs->make<TTree>("pot", "POT Tree");

  myTTree->Branch("category", &_category, "category/i");
  myTTree->Branch("E", &_energy, "E/d");
  myTTree->Branch("n_tracks", &_n_tracks, "n_tracks/i");
  myTTree->Branch("n_showers", &_n_showers, "n_showers/i");
  myTTree->Branch("vx", &_vx, "vx/d");
  myTTree->Branch("vy", &_vy, "vy/d");
  myTTree->Branch("vz", &_vz, "vz/d");

  myTTree->Branch("true_vx", &_true_vx, "true_vx/d");
  myTTree->Branch("true_vy", &_true_vy, "true_vy/d");
  myTTree->Branch("true_vz", &_true_vz, "true_vz/d");

  myTTree->Branch("true_vx_sce", &_true_vx_sce, "true_vx_sce/d");
  myTTree->Branch("true_vy_sce", &_true_vy_sce, "true_vy_sce/d");
  myTTree->Branch("true_vz_sce", &_true_vz_sce, "true_vz_sce/d");

  myTTree->Branch("nu_E", &_nu_energy, "nu_E/d");
  myTTree->Branch("passed", &_event_passed, "passed/I");
  myTTree->Branch("n_candidates", &_n_candidates, "n_candidates/i");
  myTTree->Branch("n_true_nu", &_n_true_nu, "n_true_nu/i");
  myTTree->Branch("distance", &_distance, "distance/d");
  myTTree->Branch("true_nu_is_fiducial", &_true_nu_is_fiducial,
                  "true_nu_is_fiducial/I");

  myTTree->Branch("n_matched", &_n_matched, "n_matched/i");
  myTTree->Branch("nu_matched_tracks", &_nu_matched_tracks,
                  "nu_matched_tracks/i");
  myTTree->Branch("nu_matched_showers", &_nu_matched_showers,
                  "nu_matched_showers/i");
  
  myTTree->Branch("true_shower_E_dep", &_true_shower_E_dep,
		  "true_shower_E_dep/d");
  myTTree->Branch("true_shower_E_dep_fiducial", &_true_shower_E_dep_fiducial,
		  "true_shower_E_dep_fiducial/d");

  myTTree->Branch("nu_daughters_pdg", "std::vector< int >", &_nu_daughters_pdg);
  myTTree->Branch("nu_daughters_E", "std::vector< double >", &_nu_daughters_E);

  myTTree->Branch("nu_daughters_vx", "std::vector< double >",
                  &_nu_daughters_vx);
  myTTree->Branch("nu_daughters_vy", "std::vector< double >",
                  &_nu_daughters_vy);
  myTTree->Branch("nu_daughters_vz", "std::vector< double >",
                  &_nu_daughters_vz);

  myTTree->Branch("nu_daughters_endx", "std::vector< double >",
                  &_nu_daughters_endx);
  myTTree->Branch("nu_daughters_endy", "std::vector< double >",
                  &_nu_daughters_endy);
  myTTree->Branch("nu_daughters_endz", "std::vector< double >",
                  &_nu_daughters_endz);

  myTTree->Branch("nu_daughters_px", "std::vector< double >",
                  &_nu_daughters_px);
  myTTree->Branch("nu_daughters_py", "std::vector< double >",
                  &_nu_daughters_py);
  myTTree->Branch("nu_daughters_pz", "std::vector< double >",
                  &_nu_daughters_pz);

  myTTree->Branch("event", &_event, "event/i");
  myTTree->Branch("run", &_run, "run/i");
  myTTree->Branch("subrun", &_subrun, "subrun/i");

  myTTree->Branch("bnbweight", &_bnbweight, "bnbweight/d");

  myTTree->Branch("chosen_candidate", &_chosen_candidate, "chosen_candidate/i");
  myTTree->Branch("n_primaries", &_n_primaries, "n_primaries/i");

  myTTree->Branch("primary_indexes", "std::vector< int >", &_primary_indexes);


  myTTree->Branch("flash_passed", "std::vector< int >", &_flash_passed);
  myTTree->Branch("track_passed", "std::vector< int >", &_track_passed);
  myTTree->Branch("shower_passed", "std::vector< int >", &_shower_passed);

  myTTree->Branch("shower_dir_x", "std::vector< double >", &_shower_dir_x);
  myTTree->Branch("shower_dir_y", "std::vector< double >", &_shower_dir_y);
  myTTree->Branch("shower_dir_z", "std::vector< double >", &_shower_dir_z);

  myTTree->Branch("shower_start_x", "std::vector< double >", &_shower_start_x);
  myTTree->Branch("shower_start_y", "std::vector< double >", &_shower_start_y);
  myTTree->Branch("shower_start_z", "std::vector< double >", &_shower_start_z);

  myTTree->Branch("shower_theta", "std::vector< double >", &_shower_theta);
  myTTree->Branch("shower_phi", "std::vector< double >", &_shower_phi);

  myTTree->Branch("shower_energy", "std::vector< double >", &_shower_energy);
  myTTree->Branch("track_energy", "std::vector< double >", &_track_energy);

  myTTree->Branch("track_dir_x", "std::vector< double >", &_track_dir_x);
  myTTree->Branch("track_dir_y", "std::vector< double >", &_track_dir_y);
  myTTree->Branch("track_dir_z", "std::vector< double >", &_track_dir_z);

  myTTree->Branch("track_start_x", "std::vector< double >", &_track_start_x);
  myTTree->Branch("track_start_y", "std::vector< double >", &_track_start_y);
  myTTree->Branch("track_start_z", "std::vector< double >", &_track_start_z);

  myTTree->Branch("track_is_fiducial", "std::vector< int >",
                  &_track_is_fiducial);
  myTTree->Branch("shower_is_fiducial", "std::vector< int >",
                  &_shower_is_fiducial);

  myTTree->Branch("track_end_x", "std::vector< double >", &_track_end_x);
  myTTree->Branch("track_end_y", "std::vector< double >", &_track_end_y);
  myTTree->Branch("track_end_z", "std::vector< double >", &_track_end_z);

  myTTree->Branch("track_theta", "std::vector< double >", &_track_theta);
  myTTree->Branch("track_phi", "std::vector< double >", &_track_phi);

  myTTree->Branch("track_len", "std::vector< double >", &_track_length);
  myTTree->Branch("track_id", "std::vector< double >", &_track_id);

  myTTree->Branch("nu_pdg", &_nu_pdg, "nu_pdg/i");

  myPOTTTree->Branch("run", &_run_sr, "run/i");
  myPOTTTree->Branch("subrun", &_subrun_sr, "subrun/i");
  myPOTTTree->Branch("pot", &_pot, "pot/d");

  myTTree->Branch("predict_p", "std::vector< double >", &_predict_p);
  myTTree->Branch("predict_mu", "std::vector< double >", &_predict_mu);
  myTTree->Branch("predict_pi", "std::vector< double >", &_predict_pi);
  myTTree->Branch("predict_em", "std::vector< double >", &_predict_em);
  myTTree->Branch("predict_cos", "std::vector< double >", &_predict_cos);

  myTTree->Branch("interaction_type", &_interaction_type, "interaction_type/i");

  myTTree->Branch("shower_dQdx", "std::vector< std::vector< double > >",
                  &_shower_dQdx);
  myTTree->Branch("shower_dEdx", "std::vector< std::vector< double > >",
                  &_shower_dEdx);

  myTTree->Branch("shower_open_angle", "std::vector< double >",
                  &_shower_open_angle);

  myTTree->Branch("dQdx_hits", "std::vector< std::vector< double > >",
                  &_dQdx_hits);
  myTTree->Branch("dEdx_hits", "std::vector< std::vector< double > >",
                  &_dEdx_hits);

  myTTree->Branch("matched_tracks", "std::vector< int >",
                &_matched_tracks);
  myTTree->Branch("matched_showers", "std::vector< int >",
                &_matched_showers);
  myTTree->Branch("matched_showers_process", "std::vector< std::string >",
                &_matched_showers_process);
  myTTree->Branch("matched_showers_energy", "std::vector< double >",
                &_matched_showers_energy);

  myTTree->Branch("shower_pca", "std::vector< double >",
                  &_shower_pca);

  myTTree->Branch("shower_nhits", "std::vector< std::vector<int> >",
                  &_shower_nhits);

  myTTree->Branch("track_pca", "std::vector< double >",
                  &_track_pca);

  myTTree->Branch("track_nhits", "std::vector< std::vector<int> >",
                  &_track_nhits);

  this->reconfigure(pset);
}

lee::PandoraLEEAnalyzer::~PandoraLEEAnalyzer() {
  std::cout << "[PandoraLEE] "
            << "End!" << std::endl;
}

art::Ptr<recob::Shower> lee::PandoraLEEAnalyzer::get_most_energetic_shower(
    std::vector<art::Ptr<recob::Shower>> &showers) {
  art::Ptr<recob::Shower> most_energetic_shower;

  double max_energy = std::numeric_limits<double>::lowest();
  for (auto const &shower : showers) {
    if (shower->Energy()[shower->best_plane()] > max_energy) {
      most_energetic_shower = shower;
      max_energy = shower->Energy()[shower->best_plane()];
    }
  }
  return most_energetic_shower;
}

art::Ptr<recob::Track> lee::PandoraLEEAnalyzer::get_longest_track(
    std::vector<art::Ptr<recob::Track>> &tracks) {
  art::Ptr<recob::Track> longest_track;

  double max_length = std::numeric_limits<double>::lowest();
  for (auto const &track : tracks) {
    try {
      if (track->Length() > max_length) {
        longest_track = track;
        max_length = track->Length();
      }
    } catch (...) {
      std::cout << "[PandoraLEE] "
                << "Error getting longest track " << track << std::endl;
    }
  }
  return longest_track;
}


void lee::PandoraLEEAnalyzer::get_true_energy_dep_daughters(const simb::MCTruth& gen, const simb::MCParticle& mcparticle, std::vector<double>& energy_dep) {
  double Bounds[] = {0.0, -116.5, 0.0, 256.35, 116.5, 1036.8};
  double ReverseOrder[] = {0.0, 0.0, 0.0};

  std::vector<double> ParticleEndPoints;
  std::vector<double> IntersectParams;
  
  ParticleEndPoints.push_back(mcparticle.Vx());
  ParticleEndPoints.push_back(mcparticle.Vy());
  ParticleEndPoints.push_back(mcparticle.Vz());
  ParticleEndPoints.push_back(mcparticle.EndX());
  ParticleEndPoints.push_back(mcparticle.EndY());
  ParticleEndPoints.push_back(mcparticle.EndZ());

  // Parameterize mcparticle by line and get parameter of entering/exiting fid vol in each dimension
  for (Int_t i=0; i<6; i++)
    IntersectParams.push_back((Bounds[i]-ParticleEndPoints.at(i%3)) / (ParticleEndPoints.at(i%3+3)-ParticleEndPoints.at(i%3)));

  for (Int_t i=0; i<3; i++) {
    if (ParticleEndPoints.at(i) > ParticleEndPoints.at(i+3))
      ReverseOrder[i] = 1.0;
  }

  // Get min/max linear parameter between 0 and 1
  double ParticleParamStart = 0.0;
  double ParticleParamEnd = 1.0;
  for (Int_t i=0; i<3; i++) {
    if (IntersectParams.at(i + ReverseOrder[i]*3) > ParticleParamStart)
      ParticleParamStart = IntersectParams.at(i + ReverseOrder[i]*3);
    if (IntersectParams.at(i + 3 - ReverseOrder[i]*3) < ParticleParamEnd)
      ParticleParamEnd = IntersectParams.at(i + 3 - ReverseOrder[i]*3);
  }

  // If mcparticle is electron
  if (mcparticle.PdgCode() == 11) {
    double EnergyDeposited = mcparticle.E() - mcparticle.EndE();
    for (Int_t i_daughter = 0; i_daughter < mcparticle.NumberDaughters(); i_daughter++)
      EnergyDeposited -= gen.GetParticle(mcparticle.Daughter(i_daughter)).E();

    energy_dep.at(0) += EnergyDeposited;
    if (ParticleParamStart < 1.0 && ParticleParamEnd > 0.0)
      energy_dep.at(1) += EnergyDeposited * (ParticleParamEnd-ParticleParamStart);

    for (Int_t i_daughter = 0; i_daughter < mcparticle.NumberDaughters(); i_daughter++)
      get_true_energy_dep_daughters(gen, gen.GetParticle(mcparticle.Daughter(i_daughter)), energy_dep);
  }

  // If mcparticle is photon
  if (mcparticle.PdgCode() == 22) {
    double EnergyDeposited = mcparticle.E();
    for (Int_t i_daughter = 0; i_daughter < mcparticle.NumberDaughters(); i_daughter++)
      EnergyDeposited -= gen.GetParticle(mcparticle.Daughter(i_daughter)).E();
    
    energy_dep.at(0) += EnergyDeposited;
    if (ParticleParamStart < 1.0 && ParticleParamEnd == 1.0)
      energy_dep.at(1) += EnergyDeposited;

    for (Int_t i_daughter = 0; i_daughter < mcparticle.NumberDaughters(); i_daughter++)
      get_true_energy_dep_daughters(gen, gen.GetParticle(mcparticle.Daughter(i_daughter)), energy_dep);
  }
}


size_t
lee::PandoraLEEAnalyzer::choose_candidate(std::vector<size_t> &candidates,
                                          const art::Event &evt) {

  size_t chosen_candidate = 0;
  double most_z = -1;
  double longest_track_dir;

  for (auto const &ic : candidates) {
    std::vector<art::Ptr<recob::Track>> nu_tracks;
    std::cout << "[PandoraLEE] Candidate " << ic << std::endl;
    std::vector<size_t> pfp_tracks_id =
        fElectronEventSelectionAlg.get_pfp_id_tracks_from_primary().at(ic);
    pandoraHelper.get_daughter_tracks(pfp_tracks_id, evt, nu_tracks);
    longest_track_dir = get_longest_track(nu_tracks)->StartDirection().Z();

    if (longest_track_dir > most_z) {
      chosen_candidate = ic;
      most_z = longest_track_dir;
    }
  }

  return chosen_candidate;
}

void lee::PandoraLEEAnalyzer::endSubRun(const art::SubRun &sr) {

  _run_sr = sr.run();
  _subrun_sr = sr.subRun();

  art::Handle<sumdata::POTSummary> potListHandle;
  if (!m_isData) {
    if (sr.getByLabel("generator", potListHandle))
      _pot = potListHandle->totpot;
    else
      _pot = 0.;
  } else {
    if (sr.getByLabel("beamdata", "bnbETOR860", potListHandle))
      _pot = potListHandle->totpot;
    else
      _pot = 0.;
  }

  myPOTTTree->Fill();
}
void lee::PandoraLEEAnalyzer::clear() {
  _interaction_type = std::numeric_limits<int>::lowest();

  _shower_pca.clear();
  _track_pca.clear();
  _shower_nhits.clear();
  _track_nhits.clear();
  _matched_tracks.clear();
  _matched_showers.clear();
  _matched_showers_process.clear();
  _matched_showers_energy.clear();

  _dQdx_hits.clear();
  _dEdx_hits.clear();

  _shower_open_angle.clear();
  _shower_dir_x.clear();
  _shower_dir_y.clear();
  _shower_dir_z.clear();
  _shower_dQdx.clear();
  _shower_dEdx.clear();


  _shower_start_x.clear();
  _shower_start_y.clear();
  _shower_start_z.clear();

  _track_is_fiducial.clear();
  _shower_is_fiducial.clear();

  _track_start_x.clear();
  _track_start_y.clear();
  _track_start_z.clear();

  _track_end_x.clear();
  _track_end_y.clear();
  _track_end_z.clear();

  _predict_p.clear();
  _predict_mu.clear();
  _predict_em.clear();
  _predict_pi.clear();
  _predict_cos.clear();

  _shower_theta.clear();
  _shower_phi.clear();

  _track_dir_x.clear();
  _track_dir_y.clear();
  _track_dir_z.clear();

  _track_theta.clear();
  _track_phi.clear();

  _shower_energy.clear();
  _track_energy.clear();

  _track_length.clear();
  _track_id.clear();

  _nu_pdg = 0;

  _flash_passed.clear();
  _track_passed.clear();
  _shower_passed.clear();
  _primary_indexes.clear();
  _chosen_candidate = std::numeric_limits<int>::lowest();
  _n_primaries = 0;

  _energy = std::numeric_limits<double>::lowest();

  _true_nu_is_fiducial = std::numeric_limits<int>::lowest();
  _nu_energy = std::numeric_limits<double>::lowest();

  _n_tracks = std::numeric_limits<int>::lowest();
  _n_showers = std::numeric_limits<int>::lowest();

  _vx = std::numeric_limits<double>::lowest();
  _vy = std::numeric_limits<double>::lowest();
  _vz = std::numeric_limits<double>::lowest();

  _true_vx = std::numeric_limits<double>::lowest();
  _true_vy = std::numeric_limits<double>::lowest();
  _true_vz = std::numeric_limits<double>::lowest();

  _true_vx_sce = std::numeric_limits<double>::lowest();
  _true_vy_sce = std::numeric_limits<double>::lowest();
  _true_vz_sce = std::numeric_limits<double>::lowest();

  _true_shower_E_dep = std::numeric_limits<double>::lowest();
  _true_shower_E_dep_fiducial = std::numeric_limits<double>::lowest();

  _nu_matched_tracks = std::numeric_limits<int>::lowest();
  _nu_matched_showers = std::numeric_limits<int>::lowest();

  _category = std::numeric_limits<int>::lowest();
  _run = std::numeric_limits<int>::lowest();
  _subrun = std::numeric_limits<int>::lowest();
  _event = std::numeric_limits<int>::lowest();
  _n_candidates = std::numeric_limits<int>::lowest();
  _n_true_nu = std::numeric_limits<int>::lowest();
  _run_sr = std::numeric_limits<int>::lowest();
  _subrun_sr = std::numeric_limits<int>::lowest();
  _n_matched = std::numeric_limits<int>::lowest();
  _pot = std::numeric_limits<double>::lowest();
  _event_passed = 0;
  _distance = std::numeric_limits<double>::lowest();

  _nu_daughters_E.clear();
  _nu_daughters_pdg.clear();

  _nu_daughters_px.clear();
  _nu_daughters_py.clear();
  _nu_daughters_pz.clear();

  _nu_daughters_vx.clear();
  _nu_daughters_vy.clear();
  _nu_daughters_vz.clear();

  _nu_daughters_endx.clear();
  _nu_daughters_endy.clear();
  _nu_daughters_endz.clear();

  _bnbweight = std::numeric_limits<int>::lowest();
}

void lee::PandoraLEEAnalyzer::categorizePFParticles(
  art::Event const &evt,
  std::vector<int> &neutrino_pdg,
  std::vector<std::string> &neutrino_process,
  std::vector<double> &neutrino_energy,
  std::vector<art::Ptr<recob::PFParticle>> &neutrino_pf,

  std::vector<int> &cosmic_pdg,
  std::vector<std::string> &cosmic_process,
  std::vector<double> &cosmic_energy,
  std::vector<art::Ptr<recob::PFParticle>> &cosmic_pf) {

  lar_pandora::PFParticlesToMCParticles matchedParticles;

  pandoraHelper.Configure(evt, _pfp_producer, _spacepointLabel,
    _hitfinderLabel, _geantModuleLabel);
  pandoraHelper.GetRecoToTrueMatches(matchedParticles);

  art::ServiceHandle<cheat::BackTracker> bt;

  std::cout << "[PandoraLEE] Matched size " << matchedParticles.size () << std::endl;

  for (lar_pandora::PFParticlesToMCParticles::const_iterator
    iter = matchedParticles.begin(),
    iterEnd = matchedParticles.end();
    iter != iterEnd; ++iter) {

    art::Ptr<simb::MCParticle> mc_par = iter->second; // The MCParticle
    art::Ptr<recob::PFParticle> pf_par = iter->first; // The matched PFParticle
    std::cout << "[PandoraLEE] PdgCode " << mc_par->PdgCode() << std::endl;
    const art::Ptr<simb::MCTruth> mc_truth =
    bt->TrackIDToMCTruth(mc_par->TrackId());
    std::cout << "[PandoraLEE] Origin " <<  mc_truth->Origin() << std::endl;
    if (mc_truth->Origin() == simb::kBeamNeutrino) {
      neutrino_pf.push_back(pf_par);
      neutrino_pdg.push_back(mc_par->PdgCode());
      if (mc_par->EndProcess() != NULL) {
        neutrino_process.push_back(mc_par->EndProcess());
      }
      neutrino_energy.push_back(mc_par->E());
    }

    if (mc_truth->Origin() == simb::kCosmicRay) {
      cosmic_pf.push_back(pf_par);
      cosmic_pdg.push_back(mc_par->PdgCode());
      if (mc_par->EndProcess() != NULL) {
        cosmic_process.push_back(mc_par->EndProcess());
      }
      cosmic_energy.push_back(mc_par->E());
    }
  }
}
// }
//
// void lee::PandoraLEEAnalyzer::categorizePFParticles(
//   art::Event const &evt,
//   std::vector<int> &neutrino_pdg,
//   std::vector<std::string> &neutrino_process,
//   std::vector<double> &neutrino_energy,
//   std::vector<art::Ptr<recob::PFParticle>> &neutrino_pf,
//
//   std::vector<int> &cosmic_pdg,
//   std::vector<std::string> &cosmic_process,
//   std::vector<double> &cosmic_energy,
//   std::vector<art::Ptr<recob::PFParticle>> &cosmic_pf) {
//
//     lar_pandora::MCParticlesToPFParticles
//         matchedParticles; // This is a map: MCParticle to matched PFParticle
//     lar_pandora::MCParticlesToHits matchedParticleHits;
//
//     // --- Do the matching
//     pandoraHelper.GetRecoToTrueMatches(evt, _pfp_producer, _spacepointLabel,
//       _geantModuleLabel, _hitfinderLabel,
//       matchedParticles, matchedParticleHits);
//
//     art::ServiceHandle<cheat::BackTracker> bt;
//
//     for (lar_pandora::MCParticlesToPFParticles::const_iterator
//       iter1 = matchedParticles.begin(),
//       iterEnd1 = matchedParticles.end();
//       iter1 != iterEnd1; ++iter1) {
//
//       art::Ptr<simb::MCParticle> mc_par = iter1->first; // The MCParticle
//       art::Ptr<recob::PFParticle> pf_par =
//       iter1->second; // The matched PFParticle
//
//       const art::Ptr<simb::MCTruth> mc_truth =
//       bt->TrackIDToMCTruth(mc_par->TrackId());
//
//       if (mc_truth->Origin() == simb::kBeamNeutrino) {
//         neutrino_pf.push_back(pf_par);
//         neutrino_pdg.push_back(mc_par->PdgCode());
//         if (mc_par->EndProcess() != NULL) {
//           neutrino_process.push_back(mc_par->EndProcess());
//         }
//         neutrino_energy.push_back(mc_par->E());
//       }
//
//       if (mc_truth->Origin() == simb::kCosmicRay) {
//         cosmic_pf.push_back(pf_par);
//         cosmic_pdg.push_back(mc_par->PdgCode());
//         if (mc_par->EndProcess() != NULL) {
//           cosmic_process.push_back(mc_par->EndProcess());
//         }
//         cosmic_energy.push_back(mc_par->E());
//       }
//     }
//
// }

void lee::PandoraLEEAnalyzer::analyze(art::Event const &evt) {
  clear();

  _run = evt.run();
  _subrun = evt.subRun();
  _event = evt.id().event();

  std::cout << "[PandoraLEE] "
            << "RUN " << _run << " SUBRUN " << _subrun << " EVENT " << _event
            << std::endl;

  std::vector<size_t> nu_candidates;

  _event_passed = int(fElectronEventSelectionAlg.eventSelected(evt));

  _category = 0;
  std::vector<double> true_neutrino_vertex(3);

  if (!evt.isRealData()) {
    _gain = 200;

    // nu_e flux must be corrected by event weight

    try {
      art::InputTag eventweight_tag("eventweight");
      auto const &eventweights_handle =
          evt.getValidHandle<std::vector<evwgh::MCEventWeight>>(eventweight_tag);
      auto const &eventweights(*eventweights_handle);

      if (eventweights.size() > 0) {

        for (auto last : eventweights.at(0).fWeight) {
          if (last.first.find("bnbcorrection") != std::string::npos) {

            if (!std::isfinite(last.second.at(0))) {
              _bnbweight = 1;
            } else {
              _bnbweight = last.second.at(0);
            }
          }
        }

      } else {
        _bnbweight = 1;
      }
    } catch (...) {
      std::cout << "[PandoraLEE] No MCEventWeight data product" << std::endl;
      _bnbweight = 1;
    }

    auto const &generator_handle =
        evt.getValidHandle<std::vector<simb::MCTruth>>(_mctruthLabel);
    auto const &generator(*generator_handle);
    _n_true_nu = generator.size();
    _true_nu_is_fiducial = 0;
    std::vector<simb::MCParticle> nu_mcparticles;

    bool there_is_a_neutrino = false;

    if (generator.size() > 0) {
      for (auto &gen: generator) {
        if (gen.Origin() == simb::kBeamNeutrino) {
          there_is_a_neutrino = true;
          _nu_pdg = gen.GetNeutrino().Nu().PdgCode();

          _nu_energy = gen.GetNeutrino().Nu().E();
          int ccnc = gen.GetNeutrino().CCNC();

          if (ccnc == simb::kNC) {
            _category = k_nc;
          }

          true_neutrino_vertex[0] = gen.GetNeutrino().Nu().Vx();
          true_neutrino_vertex[1] = gen.GetNeutrino().Nu().Vy();
          true_neutrino_vertex[2] = gen.GetNeutrino().Nu().Vz();
          _true_vx = true_neutrino_vertex[0];
          _true_vy = true_neutrino_vertex[1];
          _true_vz = true_neutrino_vertex[2];

          _true_nu_is_fiducial = int(geoHelper.isFiducial(true_neutrino_vertex));

          _interaction_type = gen.GetNeutrino().InteractionType();

          try {
            auto const* SCE = lar::providerFrom<spacecharge::SpaceChargeService>();
            if (SCE->GetPosOffsets(_true_vx, _true_vy, _true_vz).size() == 3) {

              _true_vx_sce =
              _true_vx - SCE->GetPosOffsets(_true_vx, _true_vy, _true_vz)[0] + 0.7;
              _true_vy_sce =
              _true_vy + SCE->GetPosOffsets(_true_vx, _true_vy, _true_vz)[1];
              _true_vz_sce =
              _true_vz + SCE->GetPosOffsets(_true_vx, _true_vy, _true_vz)[2];
            } else {
              std::cout << "[PandoraLEE] " <<  "Space Charge service offset size < 3" << std::endl;
            }
          } catch (...) {
            std::cout << "[PandoraLEE] " <<  "Space Charge service error" << std::endl;
          }

          if (!geoHelper.isActive(true_neutrino_vertex)) {
            _category = k_dirt;
          }

          for (int i = 0; i < gen.NParticles(); i++) {
            nu_mcparticles.push_back(gen.GetParticle(i));
          }

     	  for(auto &mcparticle : nu_mcparticles) {
            if (mcparticle.Process() == "primary" and mcparticle.T() != 0 and
                mcparticle.StatusCode() == 1) {
              if (mcparticle.PdgCode() == 11) {
          	std::vector<double> energy_dep = {0.0, 0.0};
          	get_true_energy_dep_daughters(gen, mcparticle, energy_dep);
          	_true_shower_E_dep = energy_dep.at(0);
          	_true_shower_E_dep_fiducial = energy_dep.at(1);
              }
            }
	  }     
        }
      }
    }

    if (!there_is_a_neutrino) _category = k_cosmic;

    for (auto &mcparticle : nu_mcparticles) {
      if (mcparticle.Process() == "primary" and mcparticle.T() != 0 and
          mcparticle.StatusCode() == 1) {

        _nu_daughters_E.push_back(mcparticle.E());
        _nu_daughters_pdg.push_back(mcparticle.PdgCode());

        _nu_daughters_px.push_back(mcparticle.Px());
        _nu_daughters_py.push_back(mcparticle.Py());
        _nu_daughters_pz.push_back(mcparticle.Pz());

        _nu_daughters_vx.push_back(mcparticle.Vx());
        _nu_daughters_vy.push_back(mcparticle.Vy());
        _nu_daughters_vz.push_back(mcparticle.Vz());

        _nu_daughters_endx.push_back(mcparticle.EndX());
        _nu_daughters_endy.push_back(mcparticle.EndY());
        _nu_daughters_endz.push_back(mcparticle.EndZ());
      }
    }

    if (_category != k_cosmic && _category != k_dirt && _category != k_nc) {
      if (abs(_nu_pdg) == 12) {
        _category = k_nu_e;
      }
      if (abs(_nu_pdg) == 14) {
        _category = k_nu_mu;
      }
    }
  } else {
    _gain = 240;
    _category = k_data;
  }

  std::cout << "[PandoraLEE] "
            << "True neutrino PDG " << _nu_pdg << std::endl;
  std::cout << "[PandoraLEE] "
            << "Nu energy " << _nu_energy << std::endl;

  std::vector<art::Ptr<recob::PFParticle>> neutrino_pf;
  std::vector<art::Ptr<recob::PFParticle>> cosmic_pf;

  std::vector<int> neutrino_pdg;
  std::vector<std::string> neutrino_process;
  std::vector<double> neutrino_energy;

  std::vector<int> cosmic_pdg;
  std::vector<std::string> cosmic_process;
  std::vector<double> cosmic_energy;

  if (!evt.isRealData() && !m_isCosmicInTime) {
    categorizePFParticles(evt,
      neutrino_pdg, neutrino_process, neutrino_energy, neutrino_pf,
      cosmic_pdg, cosmic_process, cosmic_energy, cosmic_pf);

    _n_matched = neutrino_pf.size();
  }

  size_t ipf_candidate = std::numeric_limits<size_t>::lowest();
  if (_event_passed) {

    for (auto &inu : fElectronEventSelectionAlg.get_primary_indexes()) {
      if (fElectronEventSelectionAlg.get_neutrino_candidate_passed().at(inu)) {
        nu_candidates.push_back(inu);
      }
    }

    _n_candidates = nu_candidates.size();


    std::cout << "[PandoraLEE] "
              << "EVENT PASSED" << std::endl;
    auto const &pfparticle_handle =
        evt.getValidHandle<std::vector<recob::PFParticle>>(_pfp_producer);

    ipf_candidate = choose_candidate(nu_candidates, evt);
    std::cout << "[PandoraLEE] "
              << "Neutrino candidate " << ipf_candidate << std::endl;
    _chosen_candidate = ipf_candidate;

    _energy = 0;
    energyHelper.measureEnergy(ipf_candidate, evt, _energy);

    art::FindOneP<recob::Vertex> vertex_per_pfpart(pfparticle_handle, evt,
                                                   _pfp_producer);
    auto const &vertex_obj = vertex_per_pfpart.at(ipf_candidate);

    double reco_neutrino_vertex[3];
    vertex_obj->XYZ(reco_neutrino_vertex);
    _vx = reco_neutrino_vertex[0];
    _vy = reco_neutrino_vertex[1];
    _vz = reco_neutrino_vertex[2];

    if (_category != k_data) {
      TVector3 v_reco_vertex(_vx, _vy, _vz);
      TVector3 sce_true_vertex(_true_vx_sce, _true_vy_sce, _true_vz_sce);

      _distance = geoHelper.distance(v_reco_vertex, sce_true_vertex);
    }

    std::vector<size_t> pfp_tracks_id;

    try {
      pfp_tracks_id =
          fElectronEventSelectionAlg.get_pfp_id_tracks_from_primary().at(
              ipf_candidate);
      _n_tracks = fElectronEventSelectionAlg.get_n_tracks().at(ipf_candidate);
    } catch (...) {
      std::cout << "[PandoraLEE] Error getting associated tracks to neutrino "
                   "candidate"
                << std::endl;
    }

    for (auto &pf_id : pfp_tracks_id) {

      art::FindOneP<recob::Track> track_per_pfpart(pfparticle_handle, evt,
                                                   _pfp_producer);
      auto const &track_obj = track_per_pfpart.at(pf_id);

      _matched_tracks.push_back(std::numeric_limits<int>::lowest());

      auto const &trackVecHandle =
          evt.getValidHandle<std::vector<recob::Track>>(_pfp_producer);

      art::FindManyP<anab::CosmicTag> dtAssns(trackVecHandle, evt,
                                              "decisiontreeid");

      std::vector<art::Ptr<anab::CosmicTag>> dtVec =
          dtAssns.at(track_obj.key());

      for (auto const &dttag : dtVec) {
        if (dttag->CosmicType() == TAGID_P)
          _predict_p.push_back(dttag->CosmicScore());
        else if (dttag->CosmicType() == TAGID_MU)
          _predict_mu.push_back(dttag->CosmicScore());
        else if (dttag->CosmicType() == TAGID_PI)
          _predict_pi.push_back(dttag->CosmicScore());
        else if (dttag->CosmicType() == TAGID_EM)
          _predict_em.push_back(dttag->CosmicScore());
        else if (dttag->CosmicType() == TAGID_CS)
          _predict_cos.push_back(dttag->CosmicScore());
      }

      std::vector<double> start_point;
      std::vector<double> end_point;

      start_point.push_back(track_obj->Start().X());
      start_point.push_back(track_obj->Start().Y());
      start_point.push_back(track_obj->Start().Z());

      end_point.push_back(track_obj->End().X());
      end_point.push_back(track_obj->End().Y());
      end_point.push_back(track_obj->End().Z());

      _track_is_fiducial.push_back(int(geoHelper.isFiducial(start_point) &&
                                       geoHelper.isFiducial(end_point)));

      _track_energy.push_back(energyHelper.trackEnergy(track_obj, evt));
      _track_length.push_back(track_obj->Length());
      _track_id.push_back(track_obj->ID());
      _track_dir_x.push_back(track_obj->StartDirection().X());
      _track_dir_y.push_back(track_obj->StartDirection().Y());
      _track_dir_z.push_back(track_obj->StartDirection().Z());

      _track_start_x.push_back(track_obj->Start().X());
      _track_start_y.push_back(track_obj->Start().Y());
      _track_start_z.push_back(track_obj->Start().Z());

      _track_end_x.push_back(track_obj->End().X());
      _track_end_y.push_back(track_obj->End().Y());
      _track_end_z.push_back(track_obj->End().Z());

      _track_theta.push_back(track_obj->Theta());
      _track_phi.push_back(track_obj->Phi());


      std::vector< std::vector<double> > pca;

      pca.resize(3, std::vector< double > (2));
      std::vector<int> nHits;

      energyHelper.nHits(pf_id, evt, nHits);
      energyHelper.PCA(pf_id, evt, pca);

      double weighted_pca = 0;
      int total_hits = 0;
      for (size_t i = 0; i < nHits.size(); i++) {
        weighted_pca += nHits[i]*pca[i][0];
        total_hits += nHits[i];
      }

      weighted_pca /= total_hits;
      _track_pca.push_back(weighted_pca);
      _track_nhits.push_back(nHits);


      std::cout << "[PCA] Track " << pca[2][0] << " " << pca[2][1] << std::endl;
      std::cout << "[nHits] " << nHits[2] << std::endl;
    }

    std::vector<size_t> pfp_showers_id;

    try {
      pfp_showers_id =
          fElectronEventSelectionAlg.get_pfp_id_showers_from_primary().at(
              ipf_candidate);
      _n_showers = fElectronEventSelectionAlg.get_n_showers().at(ipf_candidate);
    } catch (...) {
      std::cout << "[PandoraLEE] Error getting associated showers to neutrino "
                   "candidate"
                << std::endl;
    }

    for (auto &pf_id : pfp_showers_id) {

      std::vector<double> dqdx(3, std::numeric_limits<double>::lowest());
      std::vector<double> dedx(3, std::numeric_limits<double>::lowest());
      std::vector<double> dqdx_hits_shower;
      _matched_showers.push_back(std::numeric_limits<int>::lowest());
      _matched_showers_process.push_back("");

      _matched_showers_energy.push_back(std::numeric_limits<double>::lowest());

      std::vector< std::vector<double> > pca;

      pca.resize(3, std::vector< double > (2));
      std::vector<int> nHits;

      energyHelper.nHits(pf_id, evt, nHits);
      energyHelper.PCA(pf_id, evt, pca);

      double weighted_pca = 0;
      int total_hits = 0;
      for (size_t i = 0; i < nHits.size(); i++) {
        weighted_pca += nHits[i]*pca[i][0];
        total_hits += nHits[i];
      }

      weighted_pca /= total_hits;
      _shower_pca.push_back(weighted_pca);
      _shower_nhits.push_back(nHits);
      std::cout << "[PCA] Shower " << pca[2][0] << " " << pca[2][1] << std::endl;
      std::cout << "[nHits] " << nHits[2] << std::endl;

      energyHelper.dQdx(pf_id, evt, dqdx, dqdx_hits_shower, m_dQdxRectangleLength,
                        m_dQdxRectangleWidth);

      _dQdx_hits.push_back(dqdx_hits_shower);
      std::cout << "[dQdx] nohits " << dqdx_hits_shower.size() << " " << dqdx[0] << " " << dqdx[1] << " " << dqdx[2] << std::endl;

      std::vector<double> dedx_hits_shower(dqdx_hits_shower.size(), std::numeric_limits<double>::lowest());

      energyHelper.dEdxFromdQdx(dedx, dqdx);
      energyHelper.dEdxFromdQdx(dedx_hits_shower, dqdx_hits_shower);
      _dEdx_hits.push_back(dedx_hits_shower);

      _shower_dQdx.push_back(dqdx);
      _shower_dEdx.push_back(dedx);

      int direction = geoHelper.correct_direction(pf_id, evt);
      art::FindOneP<recob::Shower> shower_per_pfpart(pfparticle_handle, evt,
                                                     _pfp_producer);
      auto const &shower_obj = shower_per_pfpart.at(pf_id);

      TVector3 correct_dir(direction * shower_obj->Direction().X(),
                           direction * shower_obj->Direction().Y(),
                           direction * shower_obj->Direction().Z());

      _shower_dir_x.push_back(correct_dir.X());
      _shower_dir_y.push_back(correct_dir.Y());
      _shower_dir_z.push_back(correct_dir.Z());

      _shower_open_angle.push_back(shower_obj->OpenAngle());

      std::vector<double> correct_dir_v;
      correct_dir_v.resize(3);
      correct_dir_v[0] = correct_dir.X();
      correct_dir_v[1] = correct_dir.Y();
      correct_dir_v[2] = correct_dir.Z();
      double shower_length = shower_obj->Length();

      std::vector<double> start_point;
      std::vector<double> end_point;
      start_point.resize(3);
      end_point.resize(3);
      for (int ix = 0; ix < 3; ix++) {
        start_point[ix] = shower_obj->ShowerStart()[ix];
        end_point[ix] =
            shower_obj->ShowerStart()[ix] + shower_length * correct_dir_v[ix];
      }

      _shower_is_fiducial.push_back(int(geoHelper.isFiducial(start_point) &&
                                        geoHelper.isFiducial(end_point)));

      _shower_start_x.push_back(shower_obj->ShowerStart().X());
      _shower_start_y.push_back(shower_obj->ShowerStart().Y());
      _shower_start_z.push_back(shower_obj->ShowerStart().Z());

      _shower_phi.push_back(correct_dir.Phi());
      _shower_theta.push_back(correct_dir.Theta());

      _shower_energy.push_back(energyHelper.showerEnergy(shower_obj, evt));

    }


    /* For each neutrino PFParticle checks how many daughter tracks and showers
    with true neutrino origin we have */
    _nu_matched_showers = 0;
    bool shower_cr_found = false;

    _nu_matched_tracks = 0;
    bool track_cr_found = false;

    for (auto &inu : fElectronEventSelectionAlg.get_primary_indexes()) {
      _primary_indexes.push_back(inu);

      _flash_passed.push_back(fElectronEventSelectionAlg.get_op_flash_indexes().at(inu));

      std::vector<size_t> pfp_tracks_id = fElectronEventSelectionAlg.get_pfp_id_tracks_from_primary().at(inu);
      std::vector<size_t> pfp_showers_id = fElectronEventSelectionAlg.get_pfp_id_showers_from_primary().at(inu);

      int pass_shower = 0;

      for (size_t ish = 0; ish < pfp_showers_id.size(); ish++) {
        for (size_t ipf = 0; ipf < neutrino_pf.size(); ipf++) {
          if (pfp_showers_id[ish] == neutrino_pf[ipf].key()) {
            pass_shower += 1;
            if (inu == ipf_candidate) {
              _nu_matched_showers++;
              _matched_showers[ish] = neutrino_pdg[ipf];
              _matched_showers_process[ish] = neutrino_process[ipf];
              _matched_showers_energy[ish] = neutrino_energy[ipf];
            }
          }
        }

        if (inu == ipf_candidate) {
          for (size_t ipf = 0; ipf < cosmic_pf.size(); ipf++) {
            if (pfp_showers_id[ish] == cosmic_pf[ipf].key()) {
              shower_cr_found = true;
              _matched_showers[ish] = cosmic_pdg[ipf];
              _matched_showers_process[ish] = cosmic_process[ipf];
              _matched_showers_energy[ish] = cosmic_energy[ipf];


            }
          }
        }

      }

      _shower_passed.push_back(pass_shower);

      int pass_track = 0;

      for (size_t itr = 0; itr < pfp_tracks_id.size(); itr++) {

        for (size_t ipf = 0; ipf < neutrino_pf.size(); ipf++) {
          if (pfp_tracks_id[itr] == neutrino_pf[ipf].key()) {
            pass_track += 1;
            if (inu == ipf_candidate) {
              _nu_matched_tracks++;
              _matched_tracks[itr] = neutrino_pdg[ipf];
            }
          }
        }

        if (inu == ipf_candidate) {
          for (size_t ipf = 0; ipf < cosmic_pf.size(); ipf++) {
            if (pfp_tracks_id[itr] == cosmic_pf[ipf].key()) {
              track_cr_found = true;
              _matched_tracks[itr] = cosmic_pdg[ipf];
            }
          }
        }

      }

      _track_passed.push_back(pass_track);

    }

    _n_primaries = _primary_indexes.size();

    if (
      !track_cr_found && _nu_matched_tracks == 0
      && !shower_cr_found && _nu_matched_showers == 0
      && _category != k_dirt && _category != k_data) {
        _category = k_other;
        std::cout << "[PandoraLEE] "
        << "***NOT NEUTRINO NOR COSMIC***" << std::endl;
    }

    if ((track_cr_found && _nu_matched_tracks > 0)
    || (shower_cr_found && _nu_matched_showers > 0)) {
      _category = k_mixed;
      std::cout << "[PandoraLEE] "
                << "***MIXED COSMIC/NEUTRINO***" << std::endl;
    }

    if ((track_cr_found || shower_cr_found) && _category != k_mixed) {
      _category = k_cosmic;
    }

    std::cout << "[PandoraLEE] "
              << "Category " << _category << std::endl;

  } else {
    std::cout << "[PandoraLEE] "
              << "EVENT NOT PASSED" << std::endl;
  }



  myTTree->Fill();
  std::cout << "[PandoraLEE] "
            << "END ANALYZER" << std::endl;

} // end analyze function

//------------------------------------------------------------------------------------------------------------------------------------

void lee::PandoraLEEAnalyzer::reconfigure(fhicl::ParameterSet const &pset) {

  // TODO: add an external fcl file to change configuration
  // add what you want to read, and default values of your labels etc. example:
  //  m_particleLabel = pset.get<std::string>("PFParticleModule","pandoraNu");
  fElectronEventSelectionAlg.reconfigure(
      pset.get<fhicl::ParameterSet>("ElectronSelectionAlg"));

  m_printDebug = pset.get<bool>("PrintDebug", false);

  m_isData = pset.get<bool>("isData", false);
  m_isCosmicInTime = pset.get<bool>("isCosmicInTime", false);

  m_dQdxRectangleWidth = pset.get<double>("dQdxRectangleWidth", 1);
  m_dQdxRectangleLength = pset.get<double>("dQdxRectangleLength", 4);
}

//---------------------------------------------------------------------------------------------------------------------------
// add other functions here

DEFINE_ART_MODULE(lee::PandoraLEEAnalyzer)
