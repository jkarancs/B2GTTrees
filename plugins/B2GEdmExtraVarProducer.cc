#include "Analysis/B2GTTrees/interface/B2GEdmExtraVarProducer.h"
#include "Analysis/B2GTTrees/interface/Razor.h"

void B2GEdmExtraVarProducer::calculate_variables(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Read variables from EdmNtuple
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Pt"),  h_floats_["met_Pt"]);
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Phi"), h_floats_["met_Phi"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt"),         h_floats_["AK8_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta"),        h_floats_["AK8_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi"),        h_floats_["AK8_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E"),          h_floats_["AK8_E"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau2"),       h_floats_["AK8_tau2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau3"),       h_floats_["AK8_tau3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"prunedMass"), h_floats_["AK8_prunedMass"]);
  
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Pt"),  h_floats_["ele_Pt"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Eta"), h_floats_["ele_Eta"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Phi"), h_floats_["ele_Phi"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"E"),   h_floats_["ele_E"]);
  
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Pt"),          h_floats_["mu_Pt"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Eta"),         h_floats_["mu_Eta"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Phi"),         h_floats_["mu_Phi"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"E"),           h_floats_["mu_E"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"IsTightMuon"), h_floats_["mu_IsTightMuon"]);
  
  // ---------------------
  // - Lepton Selection  -
  // ---------------------
  
  // Find good leptons (for letponic tops)
  single_int_["NLep"] = 0;
  single_float_["HtLep"] = 0;
  std::vector<TLorentzVector> goodleps;
  for (size_t i=0; i<h_floats_["ele_Pt"]->size(); ++i) {
    if (h_floats_["ele_Pt"]->at(i) > 35 && 
       fabs(h_floats_["ele_Eta"]->at(i)) < 2.5) {
      ++single_int_["NLep"];                                                        /* NLep */
      TLorentzVector goodele; 
      goodele.SetPtEtaPhiE(h_floats_["ele_Pt"]->at(i), h_floats_["ele_Eta"]->at(i),
                           h_floats_["ele_Phi"]->at(i), h_floats_["ele_E"]->at(i));
      goodleps.push_back(goodele);
      single_float_["HtLep"] += h_floats_["ele_Pt"]->at(i);                         /* HtLep */
    }
  }
  for (size_t i=0; i<h_floats_["mu_Pt"]->size(); ++i) {
    //std::cout<<h_floats_["mu_IsTightMuon"]->at(i)<<" "
    //         <<(h_floats_["mu_IsTightMuon"]->at(i)==1)<<std::endl;
    if (h_floats_["mu_Pt"]->at(i) > 45 && 
        fabs(h_floats_["mu_Eta"]->at(i)) < 2.1 &&
        h_floats_["mu_IsTightMuon"]->at(i) == 1) {
      ++single_int_["NLep"];                                                        /* NLep */
      TLorentzVector goodmu;
      goodmu.SetPtEtaPhiE(h_floats_["mu_Pt"]->at(i), h_floats_["mu_Eta"]->at(i), 
                          h_floats_["mu_Phi"]->at(i), h_floats_["mu_E"]->at(i));
      goodleps.push_back(goodmu);
      single_float_["HtLep"] += h_floats_["mu_Pt"]->at(i);                          /* HtLep */
    }
  }
  
  // ---------------------
  // --- Top Selection ---
  // ---------------------
  
  single_int_["NTopHad"] = 0;
  single_int_["NTopLep"] = 0;
  single_int_["NTop"] = 0;
  single_float_["HtTop"] = 0;
  single_float_["Ht"] = 0;
  TLorentzVector top1_had;
  TLorentzVector top2_had;
  TLorentzVector top1_lep;
  TLorentzVector top2_lep;
  for (size_t i=0; i<h_floats_["AK8_Pt"]->size(); ++i) {
    bool is_top = false;
    // Hadronic tops (Loose selection)
    if (h_floats_["AK8_Pt"]->at(i) > 400 &&
        h_floats_["AK8_prunedMass"]->at(i) > 140 &&
        ( (h_floats_["AK8_tau2"]->at(i)>0 && h_floats_["AK8_tau3"]->at(i)>0) ?  
          (h_floats_["AK8_tau3"]->at(i)/h_floats_["AK8_tau2"]->at(i)) < 0.75 : 0 )) {
      ++single_int_["NTopHad"];                                                     /* NTopHad */
      is_top = true;
      if (single_int_["NTopHad"]==1) 
        top1_had.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                              h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
      if (single_int_["NTopHad"]==2) 
        top2_had.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                              h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
    }
    // Leptonic tops
    TLorentzVector lep;
    TLorentzVector jet;
    jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                     h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
    double DR_lep = 9999;
    for (size_t i=0; i<goodleps.size(); ++i) {
      double DR = goodleps[i].DeltaR(jet);
      if (DR < DR_lep) {
        DR_lep = DR;
        lep = goodleps[i];
      }
    }
    if (DR_lep<1.0) {
      ++single_int_["NTopLep"];                                                     /* NTopLep */
      is_top = true;
      TLorentzVector leptop = lep + jet;
      if (single_int_["NTopLep"]==1) top1_lep = leptop;
      if (single_int_["NTopLep"]==2) top2_lep = leptop;
    }
    // HT
    if (is_top) {
      ++single_int_["NTop"];                                                        /* NTop */
      single_float_["HtTop"] += h_floats_["AK8_Pt"]->at(i);                         /* HtTop */
    }
    single_float_["Ht"] += h_floats_["AK8_Pt"]->at(i);                              /* Ht */
  }
  single_float_["HtAll"] = single_float_["Ht"] +                                    /* HtAll */
    h_floats_["met_Pt"]->at(0) + single_float_["HtLep"];
  single_float_["HtEx"] = single_float_["HtAll"] - single_float_["HtTop"];          /* HtEx */
  single_float_["HtExFr"] = single_float_["HtEx"] / single_float_["HtAll"];         /* HtExFr */
  single_float_["HtTopFr"] = single_float_["HtTop"] / single_float_["HtAll"];       /* HtTopFr */
  
  // ---------------------
  // --- TT Selection ----
  // ---------------------
  
  // Fully hadronic channel
  single_float_["TTHadDR"]   = -9999;
  single_float_["TTHadDPhi"] = -9999;
  single_float_["TTHadDEta"] = -9999;
  single_float_["TTHadMass"] = -9999;
  single_float_["TTHadPz"]   = -9999;
  single_float_["TTHadHz"]   = -9999;
  single_float_["TTHadDPz"]  = -9999;
  if (single_int_["NTopHad"]==2) {
    single_float_["TTHadDR"]   = top1_had.DeltaR(top2_had);                         /* TTHadDR */
    single_float_["TTHadDPhi"] = top1_had.DeltaPhi(top2_had);                       /* TTHadDPhi */
    single_float_["TTHadDEta"] = fabs(top1_had.Eta() - top2_had.Eta());             /* TTHadDEta */
    single_float_["TTHadMass"] = (top1_had + top2_had).M();                         /* TTHadMass */
    single_float_["TTHadPz"]   = (top1_had + top2_had).Pz();                        /* TTHadPz */
    single_float_["TTHadHz"]   = top1_had.Pz() + top2_had.Pz();                     /* TTHadHz */
    single_float_["TTHadDPz"]  = fabs(top1_had.Pz() - top2_had.Pz());               /* TTHadDPz */
  }
  
  // ---------------------
  // -- Razor variables --
  // ---------------------
  
  // Select the best pair of jets (AK8, pt>40, |eta| < 3.0)
  std::vector<TLorentzVector> sjetl;
  for (size_t i=0; i<h_floats_["AK8_Pt"]->size(); ++i) {
    if ((h_floats_["AK8_Pt"]->at(i) > 40) && (h_floats_["AK8_Eta"]->at(i) < 3)) {
      TLorentzVector jl;
      jl.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                      h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
      sjetl.push_back(jl);
    }
  }
  std::vector<TLorentzVector> hemis = Razor::CombineJets_(sjetl);
  
  TVector3 metl;
  metl.SetPtEtaPhi(h_floats_["met_Pt"]->at(0), 0, h_floats_["met_Phi"]->at(0));
  
  // Fully hadronic channel
  single_float_["TTHadMR"]  = -9999;
  single_float_["TTHadMTR"] = -9999;
  single_float_["TTHadR"]   = -9999;
  single_float_["TTHadR2"]  = -9999;
  if (single_int_["NTopHad"]==2) {
    single_float_["TTHadMR"]  = Razor::CalcMR_(top1_had, top2_had);                 /* TTHadMR */
    single_float_["TTHadMTR"] = Razor::CalcMTR_(top1_had, top2_had, metl);          /* TTHadMTR */
    single_float_["TTHadR"]   = single_float_["TTHadMTR"]/single_float_["TTHadMR"]; /* TTHadR */
    single_float_["TTHadR2"]  = pow(single_float_["TTHadR"], 2);                    /* TTHadR2 */
  }
  // Default variables
  single_float_["MR"]  = -9999;
  single_float_["MTR"] = -9999;
  single_float_["R"]   = -9999;
  single_float_["R2"]  = -9999;
  if (hemis.size() == 2) {
    single_float_["MR"]  = Razor::CalcMR_(hemis[0], hemis[1]);                      /* MR */
    single_float_["MTR"] = Razor::CalcMTR_(hemis[0], hemis[1], metl);               /* MTR */
    single_float_["R"]   = single_float_["MTR"] / single_float_["MR"];              /* R */
    single_float_["R2"]  = std::pow(single_float_["R"], 2);                         /* R2 */
  }
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GEdmExtraVarProducer);
