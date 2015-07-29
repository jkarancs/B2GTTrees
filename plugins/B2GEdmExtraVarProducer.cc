#include "Analysis/B2GTTrees/interface/B2GEdmExtraVarProducer.h"
#include "Analysis/B2GTTrees/interface/Razor.h"

void B2GEdmExtraVarProducer::calculate_variables(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Read variables from EdmNtuple
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Pt"),  h_floats_["met_Pt"]);
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Phi"), h_floats_["met_Phi"]);
  
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Pt"),         h_floats_["AK4_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Eta"),        h_floats_["AK4_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Phi"),        h_floats_["AK4_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"E"),          h_floats_["AK4_E"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt"),              h_floats_["AK8_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta"),             h_floats_["AK8_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi"),             h_floats_["AK8_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E"),               h_floats_["AK8_E"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau2"),            h_floats_["AK8_tau2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau3"),            h_floats_["AK8_tau3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"prunedMass"),      h_floats_["AK8_prunedMass"]);
  /*
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"nSubJets"),        h_floats_["AK8_nSubJets"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex0"), h_floats_["AK8_topSubjetIndex0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex1"), h_floats_["AK8_topSubjetIndex1"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex2"), h_floats_["AK8_topSubjetIndex2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex3"), h_floats_["AK8_topSubjetIndex3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex0"),   h_floats_["AK8_vSubjetIndex0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex1"),   h_floats_["AK8_vSubjetIndex1"]);

  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Pt"),    h_floats_["CmsTTSub_Pt"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Eta"),   h_floats_["CmsTTSub_Eta"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Phi"),   h_floats_["CmsTTSub_Phi"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"E"),     h_floats_["CmsTTSub_E"]);
  
  iEvent.getByLabel(edm::InputTag(AK8JetKeys_label_),      h_keys_["AK8"]);
  iEvent.getByLabel(edm::InputTag(AK8SubjetKeys_label_),   h_keys_["AK8Sub"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjetKeys_label_), h_keys_["CmsTTSub"]);
  */
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Pt"),     h_floats_["ele_Pt"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Eta"),    h_floats_["ele_Eta"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Phi"),    h_floats_["ele_Phi"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"E"),      h_floats_["ele_E"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Charge"), h_floats_["ele_Charge"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Key"),    h_floats_["ele_Key"]);
  
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Pt"),          h_floats_["mu_Pt"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Eta"),         h_floats_["mu_Eta"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Phi"),         h_floats_["mu_Phi"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"E"),           h_floats_["mu_E"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Charge"),      h_floats_["mu_Charge"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"IsTightMuon"), h_floats_["mu_IsTightMuon"]);
  iEvent.getByLabel(edm::InputTag(muons_label_, muons_prefix_+"Key"),         h_floats_["mu_Key"]);
  
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Pt"),     h_floats_["gen_Pt"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Eta"),    h_floats_["gen_Eta"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Phi"),    h_floats_["gen_Phi"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"E"),      h_floats_["gen_E"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Charge"), h_floats_["gen_Charge"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"ID"),     h_floats_["gen_ID"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"MomID"),  h_floats_["gen_MomID"]);
  iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Status"), h_floats_["gen_Status"]);
  
  
  // ---------------------
  // - Gen Particle Info -
  // ---------------------
  
  // Make a list of Generator level objects and save them to vectors
  vector_int_["gen_ID"].clear();
  vector_int_["gen_MomID"].clear();
  vector_int_["gen_Status"].clear();
  vector_float_["gen_Pt"].clear();
  vector_float_["gen_Phi"].clear();
  vector_float_["gen_Eta"].clear();
  vector_float_["gen_E"].clear();
  vector_float_["gen_Charge"].clear();
  
  std::vector<TLorentzVector> gen_top;
  std::vector<size_t > gen_top_index;
  std::vector<TLorentzVector> gen_W_from_top;
  std::vector<TLorentzVector> gen_b_from_top;
  std::vector<TLorentzVector> gen_lep_from_W;
  std::vector<TLorentzVector> gen_neu_from_W;
  std::vector<int> gen_top_ID;
  std::vector<int> gen_W_from_top_ID;
  std::vector<int> gen_lep_from_W_ID;
  std::vector<int> gen_neu_from_W_ID;
  for (size_t i=0, n=h_floats_["gen_Pt"]->size(); i<n; ++i) {
    // Only saving b,t,W,l,nu
    if (abs(h_floats_["gen_ID"]->at(i))==5||abs(h_floats_["gen_ID"]->at(i))==6||
	(abs(h_floats_["gen_ID"]->at(i))>=11&&abs(h_floats_["gen_ID"]->at(i))<=16)
	||abs(h_floats_["gen_ID"]->at(i))==24) {
      vector_int_["gen_ID"].push_back(h_floats_["gen_ID"]->at(i));                                  /* gen_ID  */
      vector_int_["gen_MomID"].push_back(h_floats_["gen_MomID"]->at(i));			    /* gen_MomID */
      vector_int_["gen_Status"].push_back(h_floats_["gen_Status"]->at(i));			    /* gen_Status */
      vector_float_["gen_Pt"].push_back(h_floats_["gen_Pt"]->at(i));				    /* gen_Pt */
      vector_float_["gen_Eta"].push_back(h_floats_["gen_Eta"]->at(i));				    /* gen_Eta */
      vector_float_["gen_Phi"].push_back(h_floats_["gen_Phi"]->at(i));				    /* gen_Phi */
      vector_float_["gen_E"].push_back(h_floats_["gen_E"]->at(i));				    /* gen_E */
      vector_float_["gen_Charge"].push_back(h_floats_["gen_Charge"]->at(i));			    /* gen_Charge */
    }
    if (h_floats_["gen_Pt"]->at(i)>0) {
      TLorentzVector genp; genp.SetPtEtaPhiE(h_floats_["gen_Pt"]->at(i), h_floats_["gen_Eta"]->at(i),
					     h_floats_["gen_Phi"]->at(i), h_floats_["gen_E"]->at(i));
      if (h_floats_["gen_ID"]->at(i)!=h_floats_["gen_MomID"]->at(i)) {
        if (abs(h_floats_["gen_ID"]->at(i))==6) { 
          gen_top.push_back(genp);
	  gen_top_index.push_back(i);
          gen_top_ID.push_back(h_floats_["gen_ID"]->at(i));
        }
        if (abs(h_floats_["gen_ID"]->at(i))==5&&abs(h_floats_["gen_MomID"]->at(i))==6) gen_b_from_top.push_back(genp);
        if (abs(h_floats_["gen_ID"]->at(i))==24&&abs(h_floats_["gen_MomID"]->at(i))==6) {
	  gen_W_from_top.push_back(genp);
	  gen_W_from_top_ID.push_back(h_floats_["gen_ID"]->at(i));
	}
        if ((abs(h_floats_["gen_ID"]->at(i))==11||abs(h_floats_["gen_ID"]->at(i))==13
	     ||abs(h_floats_["gen_ID"]->at(i))==15)&&(abs(h_floats_["gen_MomID"]->at(i))==24)) {
	  gen_lep_from_W.push_back(genp);
	  gen_lep_from_W_ID.push_back(h_floats_["gen_ID"]->at(i));
	}
        if ((abs(h_floats_["gen_ID"]->at(i))==12||abs(h_floats_["gen_ID"]->at(i))==14
	     ||abs(h_floats_["gen_ID"]->at(i))==16)&&(abs(h_floats_["gen_MomID"]->at(i))==24)) {
	  gen_neu_from_W.push_back(genp);
	  gen_neu_from_W_ID.push_back(h_floats_["gen_ID"]->at(i));
	}
      } else if (h_floats_["gen_ID"]->at(i)==h_floats_["gen_MomID"]->at(i)&&abs(h_floats_["gen_ID"]->at(i))==6) {
        // tops emit particles and we have to match consecutive tops to the original one
        size_t t=0, t_m_dR = -1, t_m_dE = -1;
        double min_dE = 9999, min_dR = 9999;
        while(t<gen_top.size()) {
          if (gen_top_ID[t]==h_floats_["gen_MomID"]->at(i)) {
            double dE = gen_top[t].E()-genp.E();
            double dR = gen_top[t].DeltaR(genp);
            if (fabs(dE)<fabs(min_dE)) {
              min_dE = dE;
              t_m_dE = t;
            }
            if (dR<min_dR) {
              min_dR = dR;
              t_m_dR = t;
            }
          }
          ++t;
        }
        size_t imatch = (t_m_dE==t_m_dR) ? t_m_dE : ( (fabs(min_dE)/gen_top[t_m_dE].E()<0.1) ? t_m_dE : t_m_dR );
	gen_top[imatch] = genp;
        gen_top_index[imatch]=i;
      }
    }
  }
  
  std::vector<TLorentzVector> gen_top_matched_b;
  std::vector<TLorentzVector> gen_top_matched_W;
  std::vector<int> gen_top_matched_W_ID;
  // Find bs and Ws
  // Method: bs and Ws with top parent are combined
  // Best pair with lowest combined mass and DR difference is selected
  bool good_W_matches = true;
  for (size_t i=0; i<gen_top.size(); ++i) {
    // Match b and W to t
    size_t j_b = -1, k_W = -1;
    double min_DM = 9999, min_DR = 9999;
    if (gen_b_from_top.size()<gen_top.size()||gen_W_from_top.size()<gen_top.size()) {
      good_W_matches = false;
    } else {
      for (size_t j=0; j<gen_b_from_top.size(); ++j) {
        for (size_t k=0; k<gen_W_from_top.size(); ++k) {
          TLorentzVector bW_comb = gen_b_from_top[j]+gen_W_from_top[k];
          double DR = gen_top[i].DeltaR(bW_comb);
          double DM = fabs(gen_top[i].M()-bW_comb.M());
          if (DR<0.8) {
            if (DM<min_DM) {
              min_DM = DM;
	      min_DR = DR;
              j_b = j;
              k_W = k;
            }
          }
        }
      }
      if (min_DR<0.8&&min_DM<1) {
        gen_top_matched_b.push_back(gen_b_from_top[j_b]);
        gen_top_matched_W.push_back(gen_W_from_top[k_W]);
        gen_top_matched_W_ID.push_back(gen_W_from_top_ID[k_W]);
      } else {
        good_W_matches = false;
      }
    }
  }
  
  // If we have lepton/nu from W, find parent
  // Do as above with tops, but use neutrino and lepton instead to find W parent
  // In the end associate with top already found
  std::vector<int> W_type;
  std::vector<TLorentzVector> gen_top_matched_W_matched_lep;
  std::vector<TLorentzVector> gen_top_matched_W_matched_neu;
  for (size_t i=0; i<gen_top_matched_W.size(); ++i) {
    TLorentzVector lep, neu;
    // Match lep and neutrino to W
    size_t j_l = -1, k_n = -1, type = 0;
    double min_DM = 9999, min_DR = 9999;
    for (size_t j=0; j<gen_lep_from_W.size(); ++j) {
      for (size_t k=0; k<gen_neu_from_W.size(); ++k) {
	if (gen_W_from_top_ID[i]/24==gen_lep_from_W_ID[j]+gen_neu_from_W_ID[k]) {
	  TLorentzVector ln_comb = gen_lep_from_W[j]+gen_neu_from_W[k];
	  double DR = gen_top_matched_W[i].DeltaR(ln_comb);
	  double DM = fabs(gen_top_matched_W[i].M()-ln_comb.M());
	  if (DR<0.8) {
	    if (DM<min_DM) {
	      min_DM = DM;
	      min_DR = DR;
	      j_l = j;
	      k_n = k;
	      type = (abs(gen_lep_from_W_ID[j])-9)/2;
	    }
	  }
	}
      }
    }
    bool lep_found = (min_DR<0.8&&min_DM<1);
    W_type.push_back(lep_found ? type : 0);
    if (lep_found) {
      lep = gen_lep_from_W[j_l];
      neu = gen_neu_from_W[k_n];
    }
    gen_top_matched_W_matched_lep.push_back(lep);
    gen_top_matched_W_matched_neu.push_back(neu);
  }
  
  // Match jets to tops (find the closest jet to top, sort by distance from gen)
  // Could also do genjet matching (but this is done in B2G)
  std::vector<TLorentzVector> temp = gen_top;
  std::map<size_t, size_t > jet_gentop_index;
  size_t njet = h_floats_["AK8_Pt"]->size();
  while (temp.size()) {
    // find gentop  - jet pair with lowest DR (associate them and remove from temp top colelction)
    double min_DR = 9999, matched_DR = 9999;
    size_t top_m_index = -1, top_closest_index = -1, jet_m_index = -1;
    for (size_t i=0; i<temp.size(); ++i) {
      TLorentzVector top = temp[i];
      for (size_t j=0; j<njet; ++j) {
	TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(j), h_floats_["AK8_Eta"]->at(j),
					     h_floats_["AK8_Phi"]->at(j), h_floats_["AK8_E"]->at(j));
        double DR = jet.DeltaR(top);
        if (DR<min_DR) {
          min_DR = DR;
          top_closest_index = i;
          if (!jet_gentop_index.count(j)) {
            matched_DR = DR;
	    for (size_t k=0; k<gen_top.size(); ++k) if (gen_top[k]==top) top_m_index = k;
            jet_m_index = j;
          }
        }
      }
    }
    if (matched_DR<0.8) {
      jet_gentop_index[jet_m_index] = top_m_index;
      temp.erase(temp.begin()+top_m_index);
    } else if (njet) {
      temp.erase(temp.begin()+top_closest_index);
    } else {
      temp.clear();
    }
  }
  
  // Match gen leptons (from decaying W of top), sort by distance
  temp = gen_top_matched_W_matched_lep;
  std::vector<int> temp_type = W_type;
  std::map<size_t, size_t > ele_genlep_index;
  std::map<size_t, size_t > mu_genlep_index;
  size_t nele = h_floats_["ele_Pt"]->size();
  size_t nmu = h_floats_["mu_Pt"]->size();
  // Remove hadronically decaying Ws and tau decays
  for (int i=temp.size()-1; i>=0; --i) if (W_type[i]==0||W_type[i]==3) {
    temp.erase(temp.begin()+i);
    temp_type.erase(temp_type.begin()+i);
  }
  while (temp.size()) {
    // find genlep  - lepton pair with lowest DR (associate them and remove from temp collection)
    double min_DR = 9999; //, matched_DR = 9999;
    size_t genlep_m_index = -1, lep_m_index = -1, type=-1;
    for (size_t i=0; i<temp.size(); ++i) {
      TLorentzVector genlep = temp[i];
      // loop on electrons
      if (temp_type[i]==1) {
	for (size_t j=0; j<nele; ++j) {
	  TLorentzVector ele; ele.SetPtEtaPhiE(h_floats_["ele_Pt"]->at(j), h_floats_["ele_Eta"]->at(j),
					       h_floats_["ele_Phi"]->at(j), h_floats_["ele_E"]->at(j));
	  double DR = ele.DeltaR(genlep);
	  if (DR<min_DR) {
	    min_DR = DR;
	    if (!ele_genlep_index.count(j)) {
	      type = 1;
	      //matched_DR = DR;
	      for (size_t k=0; k<gen_top_matched_W_matched_lep.size(); ++k)
		if (gen_top_matched_W_matched_lep[k]==genlep) genlep_m_index = k;
	      lep_m_index = j;
	    }
	  }
	}
	// loop on muons
      } else if (temp_type[i]==2) {
	for (size_t j=0; j<nmu; ++j) {
	  TLorentzVector mu; mu.SetPtEtaPhiE(h_floats_["mu_Pt"]->at(j), h_floats_["mu_Eta"]->at(j),
					     h_floats_["mu_Phi"]->at(j), h_floats_["mu_E"]->at(j));
	  double DR = mu.DeltaR(genlep);
	  if (DR<min_DR) {
	    min_DR = DR;
	    if (!mu_genlep_index.count(j)) {
	      type = 2;
	      //matched_DR = DR;
	      for (size_t k=0; k<gen_top_matched_W_matched_lep.size(); ++k)
		if (gen_top_matched_W_matched_lep[k]==genlep) genlep_m_index = k;
	      lep_m_index = j;
	    }
	  }
	}
      }
    }
    if (type==1) {
      ele_genlep_index[lep_m_index] = genlep_m_index;
      temp.erase(temp.begin()+genlep_m_index);
    } else if (type==2) {
      mu_genlep_index[lep_m_index] = genlep_m_index;
      temp.erase(temp.begin()+genlep_m_index);
    } else {
      // leptons usually with too low pt, out of acceptance (eg. high eta)
      // or not reconstructed (electrons)
      // or misreconstructed (eg. muon as electron)
      temp.clear();
    }
  }
  
  
  // ---------------------
  // -      Jets         -
  // ---------------------
  
  vector_int_["jetAK8_HasNearGenTop"].assign(njet,0);
  vector_int_["jetAK8_NearGenTopIsHadronic"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWIsHadronic"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToENu"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToMuNu"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToTauNu"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenTop"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenWFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenBFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenLepFromSLTop"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenNuFromSLTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenBFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenWFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenLepFromSLTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenNuFromSLTop"].assign(njet,-9999);
  
  for (size_t i=0; i<njet; ++i) {
    TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
					 h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
    // Unsing Gen Particle Info
    if (jet_gentop_index.count(i)) {
      size_t top_index = jet_gentop_index[i];
      vector_int_["jetAK8_HasNearGenTop"][i]=1;                                                  /* jetAK8_HasNearGenTop */
      vector_float_["jetAK8_PtNearGenTop"][i] = gen_top[top_index].Pt();			 /* jetAK8_PtNearGenTop */
      vector_float_["jetAK8_DRNearGenTop"][i] = gen_top[top_index].DeltaR(jet);			 /* jetAK8_DRNearGenTop */
      // If W matching was successful, more information is available
      if (good_W_matches) {
        vector_float_["jetAK8_DRNearGenWFromTop"][i] = gen_top_matched_W[top_index].DeltaR(jet); /* jetAK8_DRNearGenWFromTop */
        vector_float_["jetAK8_DRNearGenBFromTop"][i] = gen_top_matched_b[top_index].DeltaR(jet); /* jetAK8_DRNearGenBFromTop */
        vector_float_["jetAK8_DRNearGenLepFromSLTop"][i] = 					 /* jetAK8_DRNearGenLepFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_lep[top_index].DeltaR(jet) : -9999;
        vector_float_["jetAK8_DRNearGenNuFromSLTop"][i]  = 					 /* jetAK8_DRNearGenNuFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_neu[top_index].DeltaR(jet) : -9999;
        vector_float_["jetAK8_PtNearGenWFromTop"][i] = gen_top_matched_W[top_index].Pt();	 /* jetAK8_PtNearGenWFromTop */
        vector_float_["jetAK8_PtNearGenBFromTop"][i] = gen_top_matched_b[top_index].Pt();	 /* jetAK8_PtNearGenBFromTop */
        vector_float_["jetAK8_PtNearGenLepFromSLTop"][i] = 					 /* jetAK8_PtNearGenLepFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_lep[top_index].Pt() : -9999;
        vector_float_["jetAK8_PtNearGenNuFromSLTop"][i]  = 					 /* jetAK8_PtNearGenNuFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_neu[top_index].Pt() : -9999;
	vector_int_["jetAK8_NearGenTopIsHadronic"][i] = !W_type[top_index];			 /* jetAK8_NearGenTopIsHadronic */
	vector_int_["jetAK8_NearGenWIsHadronic"][i] = !W_type[top_index];			 /* jetAK8_NearGenWIsHadronic */
	vector_int_["jetAK8_NearGenWToENu"][i] = W_type[top_index]==1;				 /* jetAK8_NearGenWToENu */
	vector_int_["jetAK8_NearGenWToMuNu"][i] = W_type[top_index]==2;				 /* jetAK8_NearGenWToMuNu */
	vector_int_["jetAK8_NearGenWToTauNu"][i] = W_type[top_index]==3;			 /* jetAK8_NearGenWToTauNu */
      }
    }
  }
  
  // ---------------------
  // - Lepton Selection  -
  // ---------------------
  
  vector_float_["el_DRNearGenEleFromSLTop"].assign(nele,-9999);
  vector_float_["el_PtNearGenEleFromSLTop"].assign(nele,-9999);
  vector_float_["el_AK8DeltaR"].assign(nele,-9999);
  vector_float_["el_AK8SubJetFrac"].assign(nele,-9999);
  
  // Find good leptons (for letponic tops)
  single_int_["evt_NLep"] = 0;
  single_float_["evt_HtLep"] = 0;
  std::vector<TLorentzVector> goodleps;
  for (size_t i=0; i<nele; ++i) {
    TLorentzVector ele; ele.SetPtEtaPhiE(h_floats_["ele_Pt"]->at(i), h_floats_["ele_Eta"]->at(i),
					 h_floats_["ele_Phi"]->at(i), h_floats_["ele_E"]->at(i));
    if (ele_genlep_index.count(i)) {
      size_t genlep_index = ele_genlep_index[i];
      vector_float_["el_DRNearGenEleFromSLTop"][i] =                                    /* el_DRNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].DeltaR(ele);
      vector_float_["el_PtNearGenEleFromSLTop"][i] =                                    /* el_PtNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].Pt();
    }
    if (h_floats_["ele_Pt"]->at(i) > 35 && 
       fabs(h_floats_["ele_Eta"]->at(i)) < 2.5) {
      ++single_int_["evt_NLep"];                                                        /* evt_NLep */
      goodleps.push_back(ele);
      single_float_["evt_HtLep"] += h_floats_["ele_Pt"]->at(i);                         /* evt_HtLep */
    }
  }
  
  vector_float_["mu_DRNearGenMuFromSLTop"].assign(nmu,-9999);
  vector_float_["mu_PtNearGenMuFromSLTop"].assign(nmu,-9999);
  
  for (size_t i=0; i<nmu; ++i) {
    TLorentzVector mu; mu.SetPtEtaPhiE(h_floats_["mu_Pt"]->at(i), h_floats_["mu_Eta"]->at(i),
				       h_floats_["mu_Phi"]->at(i), h_floats_["mu_E"]->at(i));
    if (mu_genlep_index.count(i)) {
      size_t genlep_index = mu_genlep_index[i];
      vector_float_["mu_DRNearGenMuFromSLTop"][i] =                                     /* mu_DRNearGenMuFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].DeltaR(mu); 
      vector_float_["mu_PtNearGenMuFromSLTop"][i] =                                     /* mu_PtNearGenMuFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].Pt();
    }
    if (h_floats_["mu_Pt"]->at(i) > 45 && 
        fabs(h_floats_["mu_Eta"]->at(i)) < 2.1 &&
        h_floats_["mu_IsTightMuon"]->at(i) == 1) {
      ++single_int_["evt_NLep"];                                                        /* evt_NLep */
      goodleps.push_back(mu);
      single_float_["evt_HtLep"] += h_floats_["mu_Pt"]->at(i);                          /* evt_HtLep */
    }
    // ------------------ Lepton-Jet Disambiguation ---------------------
    /*
    // Find closest jet
    float min_DR = 9999; size_t imatch_jet = -1;
    for (size_t ij=0; ij<njet; ++ij) {
      TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(ij), h_floats_["AK8_Eta"]->at(ij),
					   h_floats_["AK8_Phi"]->at(ij), h_floats_["AK8_E"]->at(ij));
      float DR = mu.DeltaR(jet);
      if (DR<min_DR) { 
	min_DR = DR; imatch_jet = ij;
      }
    }
    // Find closest subjet
    float min_DR_sj = 9999; size_t imatch_sj = -1;
    for (size_t isj=0, nsj=h_floats_["CmsTTSub_Pt"]->size(); isj<nsj; ++isj) {
      TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["CmsTTSub_Pt"]->at(isj), h_floats_["CmsTTSub_Eta"]->at(isj),
					   h_floats_["CmsTTSub_Phi"]->at(isj), h_floats_["CmsTTSub_E"]->at(isj));
      float DR = mu.DeltaR(jet); if (DR<min_DR) { min_DR_sj = DR; imatch_sj = isj; }
    }
    if (imatch_jet == (size_t)-1 || min_DR>0.8) {
      std::cout<<"No close jet"<<std::endl;
    } else {
      // Frist Make list of jet/subjets keys (only fill subjet is match is found)
      bool SoftDrop = 0;
      std::vector<int> AK8Keys;
      // Add removed objects (cleaned by the SoftDrop algorithm)
      if (SoftDrop) {
        AK8Keys = h_keys_["AK8"]->at(imatch_jet);
        AK8Keys.erase(AK8Keys.begin(), AK8Keys.begin()+2);
      }
      // Loop on subjets and check if a match found
      // Also collect all subjet constituents
      size_t imatch_sj_const = -1;
      for (size_t iSub=0, nSub = SoftDrop? 2 : h_floats_["AK8_nSubJets"]->at(imatch_jet); iSub<nSub; ++iSub){
	size_t subjet_index = 
	  SoftDrop ? (iSub==0 ? h_floats_["AK8_vSubjetIndex0"]->at(imatch_jet) 
		      : h_floats_["AK8_vSubjetIndex1"]->at(imatch_jet)) : 
	  iSub==0 ? h_floats_["AK8_topSubjetIndex0"]->at(imatch_jet) : 
	  iSub==1 ? h_floats_["AK8_topSubjetIndex1"]->at(imatch_jet) : 
	  iSub==2 ? h_floats_["AK8_topSubjetIndex2"]->at(imatch_jet) : 
	  h_floats_["AK8_topSubjetIndex3"]->at(imatch_jet);
	std::vector<int> subjet_keys = h_keys_[SoftDrop? "AK8Sub" : "CmsTTSub"]->at(subjet_index);
	AK8Keys.insert(AK8Keys.end(), subjet_keys.begin(), subjet_keys.end());
	for (size_t itrk=0, ntrk=subjet_keys.size(); itrk<ntrk; ++itrk) 
	  if (h_floats_["mu_Key"]->at(i)==subjet_keys[itrk]) imatch_sj_const = subjet_index;
      }
      if (imatch_sj_const!=(size_t)-1) std::cout<<"closest/matched subjet, index=: "<<imatch_sj<<", "<<imatch_sj_const<<" dR="<<min_DR_sj<<std::endl;
      // Check if the lepton is a jet constituent

      // If lepton is a jet constituent, remove it from the jet (for DeltaR, pt_rel)
      
      
      //+ //bool keymatch = 0;
      //+ std::cout<<"Mu-jet match found, i="<<imatch_jet<<" DR="<<min_DR<<" mu key: "<<h_floats_["mu_Key"]->at(i)<<std::endl;
      //+ std::cout<<" Jet keys n="<<keys.size()<<" :"<<std::endl;
      //+ for (size_t itrk=0, ntrk=keys.size(); itrk<ntrk; ++itrk) {
      //+   //if (keys[itrk]==h_floats_["mu_Key"]->at(i)) keymatch = 1;
      //+   std::cout<<" "<<keys[itrk];
      //+ }
      //+ std::cout<<std::endl;
      //+ // Check subjets
      //+ std::cout<<"  Nsubjet="<<h_floats_["AK8_nSubJets"]->at(imatch_jet)<<std::endl;;
      //+ for (size_t n=0, nsub=h_floats_["AK8_nSubJets"]->at(imatch_jet); n<nsub; ++n) if (n<2) {
      //+   size_t subjet_index = n==0 ? h_floats_["AK8_vSubjetIndex0"]->at(imatch_jet) : h_floats_["AK8_vSubjetIndex1"]->at(imatch_jet);
      //+   if (subjet_index>h_keys_["AK8Sub"]->size()) std::cout<<"Error: Impossible subjet index "<<subjet_index<<std::endl;
      //+   else {
      //+     std::cout<<"  subjet keys, subjet index="<<subjet_index<<"/"<<h_keys_["AK8Sub"]->size();
      //+     std::vector<int> subjet_keys = h_keys_["AK8Sub"]->at(subjet_index);
      //+     std::cout<<" n="<<subjet_keys.size()<<std::endl;
      //+     for (int key : subjet_keys) std::cout<<" "<<key;
      //+     std::cout<<std::endl;
      //+   }
      //+ }
      //+ std::cout<<std::endl;
    }
    // Subjet fraction
    // pt_rel
    
    // Mini isolation
    */

  }
  
  // ---------------------
  // --- Top Selection ---
  // ---------------------
  
  single_int_["evt_NTopHad"] = 0;
  single_int_["evt_NTopLep"] = 0;
  single_int_["evt_NTop"] = 0;
  single_float_["evt_HtTop"] = 0;
  single_float_["evt_Ht"] = 0;
  vector_int_["jetAK8_PassTopTag"].assign(njet,-9999);
  TLorentzVector top1_had;
  TLorentzVector top2_had;
  TLorentzVector top1_lep;
  TLorentzVector top2_lep;
  for (size_t i=0; i<njet; ++i) {
    bool is_top = false;
    vector_int_["jetAK8_PassTopTag"][i] = 0;
    // Hadronic tops (Loose selection)
    if (h_floats_["AK8_Pt"]->at(i) > 400 &&
        h_floats_["AK8_prunedMass"]->at(i) > 140 &&
        ( (h_floats_["AK8_tau2"]->at(i)>0 && h_floats_["AK8_tau3"]->at(i)>0) ?  
          (h_floats_["AK8_tau3"]->at(i)/h_floats_["AK8_tau2"]->at(i)) < 0.75 : 0 )) {
      vector_int_["jetAK8_PassTopTag"][i] = 1;
      ++single_int_["evt_NTopHad"];                                                     /* evt_NTopHad */
      is_top = true;
      if (single_int_["evt_NTopHad"]==1) 
        top1_had.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                              h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
      if (single_int_["evt_NTopHad"]==2) 
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
      ++single_int_["evt_NTopLep"];                                                     /* evt_NTopLep */
      is_top = true;
      TLorentzVector leptop = lep + jet;
      if (single_int_["evt_NTopLep"]==1) top1_lep = leptop;
      if (single_int_["evt_NTopLep"]==2) top2_lep = leptop;
    }
    // HT
    if (is_top) {
      ++single_int_["evt_NTop"];                                                        /* evt_NTop */
      single_float_["evt_HtTop"] += h_floats_["AK8_Pt"]->at(i);                         /* evt_HtTop */
    }
    single_float_["evt_Ht"] += h_floats_["AK8_Pt"]->at(i);                              /* evt_Ht */
  }
  single_float_["evt_HtAll"] = single_float_["evt_Ht"] +                                /* evt_HtAll */
    h_floats_["met_Pt"]->at(0) + single_float_["evt_HtLep"];
  single_float_["evt_HtEx"] = single_float_["evt_HtAll"] - single_float_["evt_HtTop"];  /* evt_HtEx */
  single_float_["evt_HtExFr"] = single_float_["evt_HtEx"] / single_float_["evt_HtAll"]; /* evt_HtExFr */
  single_float_["evt_HtTopFr"] = single_float_["evt_HtTop"]                             /* evt_HtTopFr */
    / single_float_["evt_HtAll"];
  
  // ---------------------
  // --- TT Selection ----
  // ---------------------
  
  // Fully hadronic channel
  single_float_["evt_TTHadDR"]   = -9999;
  single_float_["evt_TTHadDPhi"] = -9999;
  single_float_["evt_TTHadDEta"] = -9999;
  single_float_["evt_TTHadMass"] = -9999;
  single_float_["evt_TTHadPz"]   = -9999;
  single_float_["evt_TTHadHz"]   = -9999;
  single_float_["evt_TTHadDPz"]  = -9999;
  if (single_int_["evt_NTopHad"]==2) {
    single_float_["evt_TTHadDR"]   = top1_had.DeltaR(top2_had);                         /* evt_TTHadDR */
    single_float_["evt_TTHadDPhi"] = top1_had.DeltaPhi(top2_had);                       /* evt_TTHadDPhi */
    single_float_["evt_TTHadDEta"] = fabs(top1_had.Eta() - top2_had.Eta());             /* evt_TTHadDEta */
    single_float_["evt_TTHadMass"] = (top1_had + top2_had).M();                         /* evt_TTHadMass */
    single_float_["evt_TTHadPz"]   = (top1_had + top2_had).Pz();                        /* evt_TTHadPz */
    single_float_["evt_TTHadHz"]   = top1_had.Pz() + top2_had.Pz();                     /* evt_TTHadHz */
    single_float_["evt_TTHadDPz"]  = fabs(top1_had.Pz() - top2_had.Pz());               /* evt_TTHadDPz */
  }
  
  // ---------------------
  // -- Razor variables --
  // ---------------------
  
  // Select the best pair of jets (AK8, pt>40, |eta| < 3.0)
  std::vector<TLorentzVector> jets_AK8;
  for (size_t i=0; i<h_floats_["AK8_Pt"]->size(); ++i) {
    if ((h_floats_["AK8_Pt"]->at(i) > 40) && (h_floats_["AK8_Eta"]->at(i) < 3)) {
      TLorentzVector jl;
      jl.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
                      h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
      jets_AK8.push_back(jl);
    }
  }
  std::vector<TLorentzVector> hemis_AK8 = Razor::CombineJets(jets_AK8);
  
  // Same for AK4 jets
  std::vector<TLorentzVector> jets_AK4;
  for (size_t i=0; i<h_floats_["AK4_Pt"]->size(); ++i) {
    if ((h_floats_["AK4_Pt"]->at(i) > 40) && (h_floats_["AK4_Eta"]->at(i) < 3)) {
      TLorentzVector jl;
      jl.SetPtEtaPhiE(h_floats_["AK4_Pt"]->at(i), h_floats_["AK4_Eta"]->at(i),
                      h_floats_["AK4_Phi"]->at(i), h_floats_["AK4_E"]->at(i));
      jets_AK4.push_back(jl);
    }
  }
  std::vector<TLorentzVector> hemis_AK4 = Razor::CombineJets(jets_AK4);
  
  TVector3 metl;
  metl.SetPtEtaPhi(h_floats_["met_Pt"]->at(0), 0, h_floats_["met_Phi"]->at(0));
  
  // Fully hadronic channel
  single_float_["evt_TTHadMR"]  = -9999;
  single_float_["evt_TTHadMTR"] = -9999;
  single_float_["evt_TTHadR"]   = -9999;
  single_float_["evt_TTHadR2"]  = -9999;
  if (single_int_["evt_NTopHad"]==2) {
    single_float_["evt_TTHadMR"]  = Razor::CalcMR(top1_had, top2_had);                 /* evt_TTHadMR */
    single_float_["evt_TTHadMTR"] = Razor::CalcMTR(top1_had, top2_had, metl);          /* evt_TTHadMTR */
    single_float_["evt_TTHadR"]   = single_float_["evt_TTHadMTR"]                      /* evt_TTHadR */
      / single_float_["evt_TTHadMR"];
    single_float_["evt_TTHadR2"]  = pow(single_float_["evt_TTHadR"], 2);               /* evt_TTHadR2 */
  }
  // Default variables - AK8
  single_float_["evt_MR"]  = -9999;
  single_float_["evt_MTR"] = -9999;
  single_float_["evt_R"]   = -9999;
  single_float_["evt_R2"]  = -9999;
  if (jets_AK8.size() >= 2) {
    single_float_["evt_MR"]  = Razor::CalcMR(hemis_AK8[0], hemis_AK8[1]);              /* evt_MR */
    single_float_["evt_MTR"] = Razor::CalcMTR(hemis_AK8[0], hemis_AK8[1], metl);       /* evt_MTR */
    single_float_["evt_R"]   = single_float_["evt_MTR"] / single_float_["evt_MR"];     /* evt_R */
    single_float_["evt_R2"]  = std::pow(single_float_["evt_R"], 2);                    /* evt_R2 */
  }
  
  // AK4
  single_float_["evt_AK4_MR"]  = -9999;
  single_float_["evt_AK4_MTR"] = -9999;
  single_float_["evt_AK4_R"]   = -9999;
  single_float_["evt_AK4_R2"]  = -9999;
  if (jets_AK4.size() >= 2) {
    single_float_["evt_AK4_MR"]  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);          /* evt_AK4_MR */
    single_float_["evt_AK4_MTR"] = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], metl);   /* evt_AK4_MTR */
    single_float_["evt_AK4_R"]   = single_float_["evt_AK4_MTR"] / single_float_["evt_AK4_MR"]; /* evt_AK4_R */
    single_float_["evt_AK4_R2"]  = std::pow(single_float_["evt_AK4_R"], 2);            /* evt_AK4_R2 */
  }
  
  // ---------------------
  // - Trigger variables -
  // ---------------------
  
  if (first_event_) {
    first_event_=0;
    iEvent.getByLabel(edm::InputTag("TriggerUserData", "triggerNameTree"),      h_strings_["trigger_names"]);
    for ( auto trig : trigger_names_ ) for (size_t i=0, n=h_strings_["trigger_names"]->size(); i<n; ++i)
      if (h_strings_["trigger_names"]->at(i).find(trig+"_v")==0) triggers_[trig] = i;
  }
  iEvent.getByLabel(edm::InputTag("TriggerUserData", "triggerBitTree"),       h_floats_["trigger_bits"]);
  //iEvent.getByLabel(edm::InputTag("TriggerUserData", "triggerPrescaleTree"),  h_ints_["trigger_prescales"]);
  for ( auto trigger : triggers_ ) single_int_[trigger.first]                          /* HLT_* */
    = h_floats_["trigger_bits"]->at(trigger.second);
  
  // ---------------------
  // -  Event variables  -
  // ---------------------
  single_float_["evt_weight"] = event_weight_;                                         /* evt_weight */

}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GEdmExtraVarProducer);
