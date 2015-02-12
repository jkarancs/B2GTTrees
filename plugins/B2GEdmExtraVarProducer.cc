#include "Analysis/B2GTTrees/interface/B2GEdmExtraVarProducer.h"
#include "Analysis/B2GTTrees/interface/Razor.h"

void B2GEdmExtraVarProducer::calculate_variables(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Read variables from EdmNtuple
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Pt"),   h_floats_["met_Pt"]);
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Phi"),  h_floats_["met_Phi"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt"),  h_floats_["AK8_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta"), h_floats_["AK8_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi"), h_floats_["AK8_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E"),   h_floats_["AK8_E"]);
  
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
  
  if (hemis.size() == 2) {
    single_float_["MR"] = Razor::CalcMR_(hemis[0], hemis[1]);
    single_float_["MTR"] = Razor::CalcMTR_(hemis[0], hemis[1], metl);
    single_float_["R"] = single_float_["MTR"] / single_float_["MR"];
    single_float_["R2"] = std::pow(single_float_["R"], 2);
  }
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GEdmExtraVarProducer);
