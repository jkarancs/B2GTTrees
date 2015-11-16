#include "Analysis/B2GTTrees/interface/B2GEdmExtraVarProducer.h"
#include "Analysis/B2GTTrees/interface/Razor.h"
#include "Analysis/B2GTTrees/data/GluinoXSec.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

void B2GEdmExtraVarProducer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
  
  if (!isData_) {
    // Weights from scale variations, PDFs etc. are stored in the relative product. 
    // Notice that to be used they need to be renormalized to the central event weight
    // at LHE level which may be different from genEvtInfo->weight()
    
    //int whichWeight = XXX;
    //theWeight *= EvtHandle->weights()[whichWeight].wgt/EvtHandle->originalXWGTUP(); 
    
    //To know which integer XXX corresponds to which weight you can use:
    edm::Handle<LHERunInfoProduct> lheRunInfo;
    iRun.getByLabel(lhe_label_, lheRunInfo);
    
    if (lheRunInfo.isValid()) {
      
      // Check which PDF set was used
      // HEPRUP reference: http://arxiv.org/pdf/hep-ph/0609017.pdf
      // ID reference: https://lhapdf.hepforge.org/pdfsets.html
      lha_pdf_id_ = lheRunInfo->heprup().PDFSUP.first;
      std::cout<<"LHE: LHA PDF ID = "<<lha_pdf_id_<<std::endl;
      std::cout<<"LHE:   --> For more info about the sets, check: https://lhapdf.hepforge.org/pdfsets.html"<<std::endl;
      
      // Check headers
      std::cout<<"LHE: Weight info in header:"<<std::endl;
      LHERunInfoProduct lheRunInfoProduct = *(lheRunInfo.product());
      typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;
      size_t iHead = 0;
      for (headers_const_iterator header=lheRunInfoProduct.headers_begin(); header!=lheRunInfoProduct.headers_end(); header++){
        if (header->tag()=="initrwgt") {
          std::cout<<"LHE: "<<iHead<<" "<<header->tag()<<std::endl;
          for (auto line : header->lines()) {
	    std::cout<<"LHE: "<<line;
	    // Fix buggy powheg samples
	    if (lha_pdf_id_==-1 && line.find("weight id=\"2001\"")!=std::string::npos) {
	      if (line.find("PDF set = 260001")!=std::string::npos) lha_pdf_id_ = 260000;
	      else if (line.find("PDF set = 260401")!=std::string::npos) lha_pdf_id_ = 260400;
	    }
	  }
        }
        iHead++;
      }
      
    }
  }
}

void B2GEdmExtraVarProducer::calculate_variables(edm::Event const& iEvent, edm::EventSetup const& iSetup) {
  // Read variables from EdmNtuple
  iEvent.getByLabel(edm::InputTag(trigger_label_, "triggerNameTree"),      h_strings_["trigger_names"]);
  iEvent.getByLabel(edm::InputTag(trigger_label_, "triggerBitTree"),       h_floats_["trigger_bits"]);
  iEvent.getByLabel(edm::InputTag(trigger_label_, "triggerPrescaleTree"),  h_ints_["trigger_prescales"]);
  iEvent.getByLabel(edm::InputTag(filter_label_,  "triggerNameTree"),      h_strings_["filter_names"]);
  iEvent.getByLabel(edm::InputTag(filter_label_,  "triggerBitTree"),       h_floats_["filter_bits"]);
  
  iEvent.getByLabel(edm::InputTag("fixedGridRhoFastjetAll", ""),   h_double_["evt_rho"]);
  iEvent.getByLabel(edm::InputTag(evt_label_, evt_prefix_+"npv"),  h_int_["evt_npv"]);
  iEvent.getByLabel(edm::InputTag(vtx_label_, vtx_prefix_+"ndof"), h_ints_["vtx_ndof"]);
  iEvent.getByLabel(edm::InputTag(vtx_label_, vtx_prefix_+"z"),    h_floats_["vtx_z"]);
  iEvent.getByLabel(edm::InputTag(vtx_label_, vtx_prefix_+"rho"),  h_floats_["vtx_rho"]);
  
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Pt"),  h_floats_["met_Pt"]);
  iEvent.getByLabel(edm::InputTag(met_label_, met_prefix_+"Phi"), h_floats_["met_Phi"]);
  
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Pt"),         h_floats_["AK4_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Eta"),        h_floats_["AK4_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Phi"),        h_floats_["AK4_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"E"),          h_floats_["AK4_E"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"jecFactor0"), h_floats_["AK4_jecFactor0"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"jetArea"),    h_floats_["AK4_jetArea"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt"),              h_floats_["AK8_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta"),             h_floats_["AK8_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi"),             h_floats_["AK8_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E"),               h_floats_["AK8_E"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau2"),            h_floats_["AK8_tau2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau3"),            h_floats_["AK8_tau3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"softDropMass"),      h_floats_["AK8_softDropMass"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jecFactor0"),      h_floats_["AK8_jecFactor0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jetArea"),         h_floats_["AK8_jetArea"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"nSubJets"),        h_floats_["AK8_nSubJets"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex0"), h_floats_["AK8_topSubjetIndex0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex1"), h_floats_["AK8_topSubjetIndex1"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex2"), h_floats_["AK8_topSubjetIndex2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex3"), h_floats_["AK8_topSubjetIndex3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex0"),   h_floats_["AK8_vSubjetIndex0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex1"),   h_floats_["AK8_vSubjetIndex1"]);

  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Pt"),         h_floats_["CmsTTSub_Pt"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Eta"),        h_floats_["CmsTTSub_Eta"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"Phi"),        h_floats_["CmsTTSub_Phi"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"E"),          h_floats_["CmsTTSub_E"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"jecFactor0"), h_floats_["CmsTTSub_jecFactor0"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjets_label_, CmsTTSubjets_prefix_+"jetArea"),    h_floats_["CmsTTSub_jetArea"]);
  
  iEvent.getByLabel(edm::InputTag(AK4JetKeys_label_),      h_keys_["AK4"]);
  iEvent.getByLabel(edm::InputTag(AK8JetKeys_label_),      h_keys_["AK8"]);
  iEvent.getByLabel(edm::InputTag(AK8SubjetKeys_label_),   h_keys_["AK8Sub"]);
  iEvent.getByLabel(edm::InputTag(CmsTTSubjetKeys_label_), h_keys_["CmsTTSub"]);
  
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
  
  if (!isData_) {
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Pt"),          h_floats_["gen_Pt"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Eta"),         h_floats_["gen_Eta"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Phi"),         h_floats_["gen_Phi"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"E"),           h_floats_["gen_E"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Charge"),      h_floats_["gen_Charge"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"ID"),          h_floats_["gen_ID"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Status"),      h_floats_["gen_Status"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Mom0ID"),      h_floats_["gen_Mom0ID"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Mom0Status"),  h_floats_["gen_Mom0Status"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Mom1ID"),      h_floats_["gen_Mom1ID"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Mom1Status"),  h_floats_["gen_Mom1Status"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Dau0ID"),      h_floats_["gen_Dau0ID"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Dau0Status"),  h_floats_["gen_Dau0Status"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Dau1ID"),      h_floats_["gen_Dau1ID"]);
    iEvent.getByLabel(edm::InputTag(gen_label_, gen_prefix_+"Dau1Status"),  h_floats_["gen_Dau1Status"]);
  }
  
  // ----------------------------
  // -  LHE/Gen/Event weights   -
  // ----------------------------
  
  // Event weight (xsec/nevent in units of fb), 
  // Usage: Multiply this number by the total int luminosity in units of fb^-1
  single_int_["evt_LHA_PDF_ID"] = -9999;                                               /* evt_LHA_PDF_ID */
  single_float_["evt_XSec"] = isData_ ? -9999 : cross_section_;                        /* evt_Xsec */
  single_float_["evt_NEvent_Corr"] = isData_ ? -9999 : num_events_;                    /* evt_NEvent_Corr */
  single_float_["evt_Lumi_Weight"] = isData_ ? 1 : lumi_weight_;                       /* evt_Lumi_Weight */
  single_float_["evt_Gen_Weight"] = -9999;                                             /* evt_Gen_Weight */
  
  // NLO negative weights, see:
  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideDataFormatGeneratorInterface
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LHEReaderCMSSW
  //
  //  Comment:
  //    The previous weight were of course not good, due to negative weights
  //    This will not give the correct weight for 1 fb^-1 either
  //    but s = Sum(weight) / Sum( abs(weight) ) fb^-1 instead
  //    In order to get the correct weight for 1 fb^-1, one has to calculate
  //    s on the whole dataset and multiply the currently set weight with 1/s

  // Gen/LHE info
  // For Run II recommendations see:
  // https://indico.cern.ch/event/459797/contribution/2/attachments/1181555/1710844/mcaod-Nov4-2015.pdf
  vector_float_["scale_Weights"].clear();
  vector_float_["pdf_Weights"].clear();
  vector_float_["alphas_Weights"].clear();
  if (!isData_) {
    edm::Handle<GenEventInfoProduct> genEvtInfo;
    iEvent.getByLabel("generator", genEvtInfo);
    
    edm::Handle<LHEEventProduct> lheEvtInfo;
    iEvent.getByLabel(lhe_label_, lheEvtInfo);
    
    single_int_["evt_LHA_PDF_ID"] = lha_pdf_id_;
    
    if (lheEvtInfo.isValid() && genEvtInfo.isValid()) {
      // We only look for the sign of the gen weight but not it's value
      // The xsec weight is already calculated, but certain NLO samples
      // have negative weights and such events need to be subtracted
      // (and consequently the weight also needs to be corrected with a factor)
      single_float_["evt_Gen_Weight"] = genEvtInfo->weight();
      if (single_float_["evt_Gen_Weight"]<0) single_float_["evt_Xsec_Weight"] *= -1;
      
      // This weight is used to normalize pdf/scale etc weights
      double lheOrigWeight = lheEvtInfo->originalXWGTUP();
      
      // Print factors for an event
      //if (nfilt_!=h_strings_["filter_names"]->size()) for (size_t i=0; i<lheEvtInfo->weights().size(); ++i)
      //  std::cout<<"LHE: weights() - index: "<<i<<" id = "<<lheEvtInfo->weights()[i].id<<" wgt = "<<(lheEvtInfo->weights()[i].wgt/lheOrigWeight)<<std::endl;
      
      // Renormalization/Factorization scale weights
      // These are the first 9 weights for all generators
      // mu_R and mu_F are varied independently (by a factor of 1, 2, 0.5) - check LHE header
      // [0] is the default weight (no variation) - it has worse precision even
      // --> I skip saving it (one can just use 1)
      // --> Also do not save unphysical combinations as recommended
      //    (mu_R = 0.5, mu_F = 2 and mu_R = 2, mu_F = 0.5)
      // Save only: 1,2,3,4,6,8
      if (lheEvtInfo->weights().size()>=9) for (size_t i=0; i<9; ++i) if (i!=0&&i!=5&&i!=7)
        vector_float_["scale_Weights"].push_back(lheEvtInfo->weights()[i].wgt/lheOrigWeight);
      
      // PDF weights
      // Usually a set of 100 weights (excluding default)
      // Only default PDF variation is saved, but if needed
      // likely others are available depending on the generator
      // index of first weight varies, beware!
      // Sometimes first weight is default=1 weight (has to skip!)
      // Additional info: MC2Hessian conversion will soon be provided
      size_t first = 9;
      // Madgraph nf5 - have to skip 1 weight which is default
      if (lha_pdf_id_ == 263000) first = 10;
      // Madgraph nf4 uses NNPDF30_lo_as_0130_nf_4 (ID=263400)
      // Which is the second 101 pdf set, again has to skip first weight
      if (lha_pdf_id_ == 263400) first = 111;
      if (lheEvtInfo->weights().size()>=first+100) for (size_t i=first; i<first+100; ++i)
        vector_float_["pdf_Weights"].push_back(lheEvtInfo->weights()[i].wgt/lheOrigWeight);
      
      // Alpha_s weights (only for NLO!)
      // A set of two weights for 
      // alpha_s = 0.118 - 0.002 and
      // alpha_s = 0.118 + 0.002
      // is given --> scale result uncertainty by 0.75
      if ( lheEvtInfo->weights().size()>=111 &&
            ( (lha_pdf_id_ == 260000) || // Powheg 5nf
             (lha_pdf_id_ == 260400) || // Powheg 4nf 
             (lha_pdf_id_ == 292000) || // aMC@NLO 5nf
             (lha_pdf_id_ == 292200)    // aMC@NLO 5nf
             ) ) {
        vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[109].wgt/lheOrigWeight);
        vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[110].wgt/lheOrigWeight);
      }
    }
  }
  
  // ----------------------------
  // - Trigger/Filter variables -
  // ----------------------------
  
  if (nfilt_!=h_strings_["filter_names"]->size()) {
    nfilt_=h_strings_["filter_names"]->size();
    filters_.clear();
    for ( auto filter : filter_names_ ) for (size_t i=0; i<nfilt_; ++i) 
      if (h_strings_["filter_names"]->at(i).find(filter)==0) filters_[filter] = i;
    std::cout<<"Filters found: "<<std::endl;
    for ( auto filter : filters_ ) std::cout<<filter.first<<std::endl;
  }
  if (ntrig_!=h_strings_["trigger_names"]->size()) {
    ntrig_=h_strings_["trigger_names"]->size();
    triggers_.clear();
    for ( auto trig : trigger_names_ ) for (size_t i=0; i<ntrig_; ++i) 
      if (h_strings_["trigger_names"]->at(i).find(trig+"_v")==0) triggers_[trig] = i;
    std::cout<<"Triggers found: "<<std::endl;
    for ( auto trigger : triggers_ ) std::cout<<trigger.first<<std::endl;
    //for (size_t i=0; i<ntrig_; ++i) std::cout<<h_strings_["trigger_names"]->at(i)<<std::endl;
  }
  for ( auto filter : filters_ ) single_bool_[filter.first]                             /* Flag_* */
      = h_floats_["filter_bits"]->at(filter.second);
  for ( auto trigger : triggers_ ) {
    single_bool_[trigger.first] = h_floats_["trigger_bits"]->at(trigger.second);        /* HLT_* */
    single_int_[trigger.first+"_prescale"]                                              /* HLT_*_prescale */
      = h_ints_["trigger_prescales"]->at(trigger.second);
  }
  
  // ----------------------------
  // -        Vertices          -
  // ----------------------------
  
  single_int_["evt_NGoodVtx"] = 0;
  for (int iVtx=0; iVtx<*h_int_["evt_npv"]; ++iVtx)
    if (h_ints_["vtx_ndof"]->at(iVtx)>=4&&fabs(h_floats_["vtx_z"]->at(iVtx))<24&&fabs(h_floats_["vtx_rho"]->at(iVtx)<2))
      ++single_int_["evt_NGoodVtx"];                                                    /* evt_NGoodVtx */
  
  // ---------------------
  // - Gen Particle Info -
  // ---------------------
  
  // Make a list of Generator level objects and save them to vectors
  vector_int_["gen_ID"].clear();
  vector_int_["gen_Status"].clear();
  vector_int_["gen_Mom0ID"].clear();
  vector_int_["gen_Mom0Status"].clear();
  vector_int_["gen_Mom1ID"].clear();
  vector_int_["gen_Mom1Status"].clear();
  vector_int_["gen_Dau0ID"].clear();
  vector_int_["gen_Dau0Status"].clear();
  vector_int_["gen_Dau1ID"].clear();
  vector_int_["gen_Dau1Status"].clear();
  vector_float_["gen_Pt"].clear();
  vector_float_["gen_Phi"].clear();
  vector_float_["gen_Eta"].clear();
  vector_float_["gen_E"].clear();
  vector_float_["gen_Charge"].clear();
  vector_float_["gen_Mass"].clear();
  
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
  
  bool good_W_matches = true;
  std::vector<TLorentzVector> gen_top_matched_b;
  std::vector<TLorentzVector> gen_top_matched_W;
  std::vector<int> gen_top_matched_W_ID;
  
  std::vector<int> W_type;
  std::vector<TLorentzVector> gen_top_matched_W_matched_lep;
  std::vector<TLorentzVector> gen_top_matched_W_matched_neu;
  
  std::map<size_t, size_t > jet_gentop_index;
  std::map<size_t, size_t > ele_genlep_index;
  std::map<size_t, size_t > mu_genlep_index;
  
  size_t nele = h_floats_["ele_Pt"]->size();
  size_t nmu =  h_floats_["mu_Pt"]->size();
  size_t njet = h_floats_["AK8_Pt"]->size();
  
  if (!isData_) {
    double gluino_mass = -9999;
    double lsp_mass = -9999;
    for (size_t i=0, n=h_floats_["gen_Pt"]->size(); i<n; ++i) {
      // Only saving b,t,W,l,nu
      if (abs(h_floats_["gen_ID"]->at(i))==5||abs(h_floats_["gen_ID"]->at(i))==6||
          (abs(h_floats_["gen_ID"]->at(i))>=11&&abs(h_floats_["gen_ID"]->at(i))<=16)
          ||abs(h_floats_["gen_ID"]->at(i))==24||abs(h_floats_["gen_ID"]->at(i))>1000000) {
        vector_int_["gen_ID"].push_back(h_floats_["gen_ID"]->at(i));                                /* gen_ID  */
        vector_int_["gen_Status"].push_back(h_floats_["gen_Status"]->at(i));			    /* gen_Status */
        vector_int_["gen_Mom0ID"].push_back(h_floats_["gen_Mom0ID"]->at(i));			    /* gen_Mom0ID */
        vector_int_["gen_Mom0Status"].push_back(h_floats_["gen_Mom0Status"]->at(i));		    /* gen_Mom0Status */
        vector_int_["gen_Mom1ID"].push_back(h_floats_["gen_Mom1ID"]->at(i));			    /* gen_Mom1ID */
        vector_int_["gen_Mom1Status"].push_back(h_floats_["gen_Mom1Status"]->at(i));		    /* gen_Mom1Status */
        vector_int_["gen_Dau0ID"].push_back(h_floats_["gen_Dau0ID"]->at(i));			    /* gen_Dau0ID */
        vector_int_["gen_Dau0Status"].push_back(h_floats_["gen_Dau0Status"]->at(i));		    /* gen_Dau0Status */
        vector_int_["gen_Dau1ID"].push_back(h_floats_["gen_Dau0ID"]->at(i));			    /* gen_Dau1ID */
        vector_int_["gen_Dau1Status"].push_back(h_floats_["gen_Dau0Status"]->at(i));		    /* gen_Dau1Status */
        vector_float_["gen_Pt"].push_back(h_floats_["gen_Pt"]->at(i));				    /* gen_Pt */
        vector_float_["gen_Eta"].push_back(h_floats_["gen_Eta"]->at(i));			    /* gen_Eta */
        vector_float_["gen_Phi"].push_back(h_floats_["gen_Phi"]->at(i));			    /* gen_Phi */
        vector_float_["gen_E"].push_back(h_floats_["gen_E"]->at(i));				    /* gen_E */
        vector_float_["gen_Charge"].push_back(h_floats_["gen_Charge"]->at(i));			    /* gen_Charge */
        TLorentzVector genp; genp.SetPtEtaPhiE(h_floats_["gen_Pt"]->at(i), h_floats_["gen_Eta"]->at(i),
					       h_floats_["gen_Phi"]->at(i), h_floats_["gen_E"]->at(i));
	vector_float_["gen_Mass"].push_back(genp.M());				                    /* gen_Mass */
	// Gluino Mass is needef for cross-section
	if (abs(h_floats_["gen_ID"]->at(i))==1000021) {
	  // round because there's a small precision loss
	  // and also for xsec you need to round anyway
	  gluino_mass = std::round(genp.M()/5)*5;
	  // LSP Mass
	} else if (abs(h_floats_["gen_ID"]->at(i))==1000022) {
	  lsp_mass = std::round(genp.M()/5)*5;
	}
      }
      if (h_floats_["gen_Pt"]->at(i)>0) {
        TLorentzVector genp; genp.SetPtEtaPhiE(h_floats_["gen_Pt"]->at(i), h_floats_["gen_Eta"]->at(i),
          				     h_floats_["gen_Phi"]->at(i), h_floats_["gen_E"]->at(i));
        if (h_floats_["gen_ID"]->at(i)!=h_floats_["gen_Mom0ID"]->at(i)) {
          if (abs(h_floats_["gen_ID"]->at(i))==6) { 
            gen_top.push_back(genp);
            gen_top_index.push_back(i);
            gen_top_ID.push_back(h_floats_["gen_ID"]->at(i));
          }
          if (abs(h_floats_["gen_ID"]->at(i))==5&&abs(h_floats_["gen_Mom0ID"]->at(i))==6) gen_b_from_top.push_back(genp);
          if (abs(h_floats_["gen_ID"]->at(i))==24&&abs(h_floats_["gen_Mom0ID"]->at(i))==6) {
            gen_W_from_top.push_back(genp);
            gen_W_from_top_ID.push_back(h_floats_["gen_ID"]->at(i));
          }
          if ((abs(h_floats_["gen_ID"]->at(i))==11||abs(h_floats_["gen_ID"]->at(i))==13
               ||abs(h_floats_["gen_ID"]->at(i))==15)&&(abs(h_floats_["gen_Mom0ID"]->at(i))==24)) {
            gen_lep_from_W.push_back(genp);
            gen_lep_from_W_ID.push_back(h_floats_["gen_ID"]->at(i));
          }
          if ((abs(h_floats_["gen_ID"]->at(i))==12||abs(h_floats_["gen_ID"]->at(i))==14
               ||abs(h_floats_["gen_ID"]->at(i))==16)&&(abs(h_floats_["gen_Mom0ID"]->at(i))==24)) {
            gen_neu_from_W.push_back(genp);
            gen_neu_from_W_ID.push_back(h_floats_["gen_ID"]->at(i));
          }
        } else if (h_floats_["gen_ID"]->at(i)==h_floats_["gen_Mom0ID"]->at(i)&&abs(h_floats_["gen_ID"]->at(i))==6) {
          // tops emit particles and we have to match consecutive tops to the original one
          size_t t=0, t_m_dR = -1, t_m_dE = -1;
          double min_dE = 9999, min_dR = 9999;
          while(t<gen_top.size()) {
            if (gen_top_ID[t]==h_floats_["gen_Mom0ID"]->at(i)) {
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
    
    // Save SUSY Signal related quantities
    if (gluino_mass != -9999) {
      single_float_["SUSY_Gluino_Mass"] = gluino_mass;                                              /* SUSY_Gluino_Mass */
      single_float_["SUSY_LSP_Mass"] = lsp_mass;                                                    /* SUSY_LSP_Mass */
      if (gluino_mass != single_float_["prev_gluino_mass"])
        single_float_["evt_XSec"] = GetGluinoXSec(gluino_mass).first;                               /* evt_XSec */
      single_float_["prev_gluino_mass"] = gluino_mass;
    }
    
    // Find bs and Ws
    // Method: bs and Ws with top parent are combined
    // Best pair with lowest combined mass and DR difference is selected
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
  } // End !isData
  
  // ---------------------
  // -      Jets         -
  // ---------------------
  
  vector_int_["jetAK8_HasNearGenTop"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenTopIsHadronic"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWIsHadronic"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToENu"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToMuNu"].assign(njet,-9999);
  vector_int_["jetAK8_NearGenWToTauNu"].assign(njet,-9999);
  vector_float_["jetAK8_DRNearGenTop"].assign(njet,9999);
  vector_float_["jetAK8_DRNearGenWFromTop"].assign(njet,9999);
  vector_float_["jetAK8_DRNearGenBFromTop"].assign(njet,9999);
  vector_float_["jetAK8_DRNearGenLepFromSLTop"].assign(njet,9999);
  vector_float_["jetAK8_DRNearGenNuFromSLTop"].assign(njet,9999);
  vector_float_["jetAK8_PtNearGenTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenBFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenWFromTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenLepFromSLTop"].assign(njet,-9999);
  vector_float_["jetAK8_PtNearGenNuFromSLTop"].assign(njet,-9999);
  
  if (!isData_) for (size_t i=0; i<njet; ++i) {
    TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
					 h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
    vector_int_["jetAK8_HasNearGenTop"][i]=0;
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
  
  vector_float_["el_DRNearGenEleFromSLTop"].assign(nele,9999);
  vector_float_["el_PtNearGenEleFromSLTop"].assign(nele,-9999);
  vector_float_["el_PtNearGenTop"].assign(nele,-9999);
  vector_int_["el_NearAK4JetIndex"].assign(nele,-9999);
  vector_int_["el_NearAK8JetIndex"].assign(nele,-9999);
  vector_int_["el_NearSubjetIndex"].assign(nele,-9999);
  vector_int_["el_IsPartOfNearAK4Jet"].assign(nele,-9999);
  vector_int_["el_IsPartOfNearAK8Jet"].assign(nele,-9999);
  vector_int_["el_IsPartOfNearSubjet"].assign(nele,-9999);
  vector_float_["el_LepAK4JetFrac"].assign(nele,-9999);
  vector_float_["el_LepAK8JetFrac"].assign(nele,-9999);
  vector_float_["el_LepSubjetFrac"].assign(nele,-9999);
  vector_float_["el_LepAK4JetMassDrop"].assign(nele,-9999);
  vector_float_["el_LepAK8JetMassDrop"].assign(nele,-9999);
  vector_float_["el_LepSubjetMassDrop"].assign(nele,-9999);
  vector_float_["el_AK4JetV1DR"].assign(nele,9999);
  vector_float_["el_AK4JetV2DR"].assign(nele,9999);
  vector_float_["el_AK4JetV3DR"].assign(nele,9999);
  vector_float_["el_AK8JetV1DR"].assign(nele,9999);
  vector_float_["el_AK8JetV2DR"].assign(nele,9999);
  vector_float_["el_AK8JetV3DR"].assign(nele,9999);
  vector_float_["el_SubjetV1DR"].assign(nele,9999);
  vector_float_["el_SubjetV2DR"].assign(nele,9999);
  vector_float_["el_SubjetV3DR"].assign(nele,9999);
  vector_float_["el_AK4JetV1PtRel"].assign(nele,9999);
  vector_float_["el_AK4JetV2PtRel"].assign(nele,9999);
  vector_float_["el_AK4JetV3PtRel"].assign(nele,9999);
  vector_float_["el_AK8JetV1PtRel"].assign(nele,9999);
  vector_float_["el_AK8JetV2PtRel"].assign(nele,9999);
  vector_float_["el_AK8JetV3PtRel"].assign(nele,9999);
  vector_float_["el_SubjetV1PtRel"].assign(nele,9999);
  vector_float_["el_SubjetV2PtRel"].assign(nele,9999);
  vector_float_["el_SubjetV3PtRel"].assign(nele,9999);
  
  // Find good leptons (for letponic tops)
  single_int_["evt_NLep"] = 0;
  single_float_["evt_HtLep"] = 0;
  std::vector<TLorentzVector> goodleps;
  for (size_t iEle=0; iEle<nele; ++iEle) {
    TLorentzVector ele; ele.SetPtEtaPhiE(h_floats_["ele_Pt"]->at(iEle), h_floats_["ele_Eta"]->at(iEle),
					 h_floats_["ele_Phi"]->at(iEle), h_floats_["ele_E"]->at(iEle));
    if (!isData_) if (ele_genlep_index.count(iEle)) {
      size_t genlep_index = ele_genlep_index[iEle];
      vector_float_["el_DRNearGenEleFromSLTop"][iEle] =                                     /* el_DRNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].DeltaR(ele); 
      vector_float_["el_PtNearGenEleFromSLTop"][iEle] =                                     /* el_PtNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].Pt();
      vector_float_["el_PtNearGenTop"][iEle] = gen_top[genlep_index].Pt();                 /* el_PtNearGenTop */
    }
    if (h_floats_["ele_Pt"]->at(iEle) > 35 && 
       fabs(h_floats_["ele_Eta"]->at(iEle)) < 2.5) {
      ++single_int_["evt_NLep"];                                                        /* evt_NLep */
      goodleps.push_back(ele);
      single_float_["evt_HtLep"] += h_floats_["ele_Pt"]->at(iEle);                          /* evt_HtLep */
    }
    
    // ------------------------------------------------------------------------
    //                       Lepton-Jet Disambiguation
    
    const bool SoftDrop = 0; // 1: use W-like SoftDrop subjets (max 2 subjet) or 0: top-like subjets (2-4)
    const bool print_keys = 0;
    TLorentzVector closest_jet[3], prev_jet[3];
    float closest_jet_Area[3], closest_jet_jecFactor0[3];
    bool closest_jet_R08Cone[3];
    
    for (size_t iJet=0, nAK4jet=h_floats_["AK4_Pt"]->size(); iJet<nAK4jet; ++iJet) {
      
      // ----------------- AK4 jet ----------------------
    
      // Check if the lepton exists inside the closest jet
      TLorentzVector jet;
      jet.SetPtEtaPhiE(h_floats_["AK4_Pt"]->at(iJet), h_floats_["AK4_Eta"]->at(iJet),
		       h_floats_["AK4_Phi"]->at(iJet), h_floats_["AK4_E"]->at(iJet));
      float DR_jet = ele.DeltaR(jet);
      if (DR_jet<vector_float_["el_AK4JetV1DR"][iEle]) {
	prev_jet[0] = closest_jet[0];
	closest_jet[0] = jet;
	closest_jet_Area[0] = h_floats_["AK4_jetArea"]->at(iJet);
	closest_jet_jecFactor0[0] = h_floats_["AK4_jecFactor0"]->at(iJet);
	closest_jet_R08Cone[0] = 0;
	vector_int_["el_NearAK4JetIndex"][iEle] = iJet;
	vector_float_["el_AK4JetV1DR"][iEle] = DR_jet;
	// Loop on all keys and check if we need to remove lepton from the jet if the lepton is part of it
	vector_int_["el_IsPartOfNearAK4Jet"][iEle] = 0;
	for (size_t iKey=0, nKey=h_keys_["AK4"]->at(iJet).size(); iKey<nKey; ++iKey)
	  if (h_floats_["ele_Key"]->at(iEle)==h_keys_["AK4"]->at(iJet)[iKey]) 
	    vector_int_["el_IsPartOfNearAK4Jet"][iEle] = 1;
      }
    }
    
    for (size_t iJet=0; iJet<njet; ++iJet) {
      
      // ----------------- AK8 jet ----------------------
      
      // Check if the lepton exists inside the closest fatjet
      size_t nSubjet_SD = 0, nSubjetKeys_SD = 0;
      TLorentzVector fatjet;
      fatjet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(iJet), h_floats_["AK8_Eta"]->at(iJet),
		       h_floats_["AK8_Phi"]->at(iJet), h_floats_["AK8_E"]->at(iJet));
      float DR_fatjet = ele.DeltaR(fatjet);
      // Part of the keys for the fatjet are inside SoftDrop subjets
      std::vector<int> AK8Keys;
      for (size_t isub=0; isub<2; ++isub) {
	size_t iSubjet = isub==0 ? h_floats_["AK8_vSubjetIndex0"]->at(iJet) 
	    : h_floats_["AK8_vSubjetIndex1"]->at(iJet);
	if (iSubjet != (size_t)-1) {
	  ++nSubjet_SD;
	  std::vector<int> subjet_keys = h_keys_["AK8Sub"]->at(iSubjet);
	  AK8Keys.insert(AK8Keys.end(), subjet_keys.begin(), subjet_keys.end());
	  nSubjetKeys_SD += subjet_keys.size();
	}
      }
      // Add rest of the keys, but skip first N subjet keys
      AK8Keys.insert(AK8Keys.end(), h_keys_["AK8"]->at(iJet).begin()+nSubjet_SD, h_keys_["AK8"]->at(iJet).end());
      if (DR_fatjet<vector_float_["el_AK8JetV1DR"][iEle]) {
	prev_jet[1] = closest_jet[1];
	closest_jet[1] = fatjet;
	closest_jet_Area[1] = h_floats_["AK8_jetArea"]->at(iJet);
	closest_jet_jecFactor0[1] = h_floats_["AK8_jecFactor0"]->at(iJet);
	closest_jet_R08Cone[1] = 1;
	vector_int_["el_NearAK8JetIndex"][iEle] = iJet;
	vector_float_["el_AK8JetV1DR"][iEle] = DR_fatjet;
	// Now loop on all keys and check if we need
	// to remove lepton from the fatjet if the lepton is part of it
	vector_int_["el_IsPartOfNearAK8Jet"][iEle] = 0;
	for (size_t iKey=0, nKey=AK8Keys.size(); iKey<nKey; ++iKey)
	  if (h_floats_["ele_Key"]->at(iEle)==AK8Keys[iKey]) vector_int_["el_IsPartOfNearAK8Jet"][iEle] = 1;
      }
      
      // --------------- AK8 Subjets --------------------
      
      // First Loop on and count subjets and check if lepton is part of it
      // In case lepton is found, substract it's 4vec from the jet
      size_t nSubjet = 0, nSubjetKeys = 0;
      for (size_t isub=0, nSub = SoftDrop ? 2 : 4; isub<nSub; ++isub) {
	size_t iSubjet = 
	  SoftDrop ? (isub==0 ? h_floats_["AK8_vSubjetIndex0"]->at(iJet) 
		      : h_floats_["AK8_vSubjetIndex1"]->at(iJet)) : 
	  isub==0 ? h_floats_["AK8_topSubjetIndex0"]->at(iJet) : 
	  isub==1 ? h_floats_["AK8_topSubjetIndex1"]->at(iJet) : 
	  isub==2 ? h_floats_["AK8_topSubjetIndex2"]->at(iJet) : 
	  h_floats_["AK8_topSubjetIndex3"]->at(iJet);
	// If subjet exist calc MinDR and for the closest check if we need
	// to remove lepton from the subjet if the lepton is part of it
	if (isub==0 || iSubjet != (size_t)-1) {
	  ++nSubjet;
	  TLorentzVector subjet;
	  // If SubJet doesn't exist, treat AK8 jet as a subjet
	  std::string prefix = iSubjet!=(size_t)-1 ? "CmsTTSub_" : "AK8_";
	  size_t index = iSubjet!=(size_t)-1 ? iSubjet : iJet;
	  subjet.SetPtEtaPhiE(h_floats_[prefix+"Pt"]->at(index), h_floats_[prefix+"Eta"]->at(index),
			      h_floats_[prefix+"Phi"]->at(index), h_floats_[prefix+"E"]->at(index));
	  float DR_subjet = ele.DeltaR(subjet);
	  if (DR_subjet<vector_float_["el_SubjetV1DR"][iEle]) {
	    prev_jet[2] = closest_jet[2];
	    closest_jet[2] = subjet;
	    closest_jet_Area[2] = h_floats_[prefix+"jetArea"]->at(index);
	    closest_jet_jecFactor0[2] = h_floats_[prefix+"jecFactor0"]->at(index);
	    closest_jet_R08Cone[2] = iSubjet==(size_t)-1;
	    vector_int_["el_NearSubjetIndex"][iEle] = iSubjet;
	    vector_float_["el_SubjetV1DR"][iEle] = DR_subjet;
	    // Check if lepton is part of the subjet
	    vector_int_["el_IsPartOfNearSubjet"][iEle] = 0;
	    std::vector<int> subjet_keys = iSubjet!=(size_t)-1 ? h_keys_[SoftDrop? "AK8Sub" : "CmsTTSub"]->at(iSubjet) : AK8Keys;
	    nSubjetKeys += subjet_keys.size();
	    for (size_t iKey=0, nKey=subjet_keys.size(); iKey<nKey; ++iKey)
	      if (h_floats_["ele_Key"]->at(iEle)==subjet_keys[iKey])
		vector_int_["el_IsPartOfNearSubjet"][iEle] = 1;
	  }
	}
      }
      
      if (print_keys) {
        std::cout<<iJet<<" nSubjet="<<nSubjet<<" nSubjet_SD="<<nSubjet_SD<<" nSubjetKeys="<<nSubjetKeys
        	 <<" nSubjetKeys_SD="<<nSubjetKeys_SD<<" RestKeys="<<h_keys_["AK8"]->at(iJet).size()-nSubjet_SD<<"\n";
        std::vector<int> jet_keys = h_keys_["AK8"]->at(iJet);
        std::cout<<"   rest:";
        for (size_t iKey=nSubjet_SD, nKey=jet_keys.size(); iKey<nKey; ++iKey) if (nSubjet_SD==1) std::cout<<" "<<jet_keys[iKey];
        std::cout<<"\n\n";
      }
      
    } // End of AK8 Jet loop
    //std::cout<<"--> Mu["<<iEle<<"] "<<"jet/subjet-match="<<vector_int_["el_IsPartOfNearAK8Jet"][iEle]<<" "<<vector_int_["el_IsPartOfNearSubjet"][iEle]<<", MinDR="<<vector_float_["el_AK8JetV1DR"][iEle]<<" "<<vector_float_["el_SubjetV1DR"][iEle]<<std::endl;
    
    // Calculate Jet/SubJet pt fraction, Jet mass drop
    for (int iType=0; iType<3; ++iType) {
      std::string JetType = iType==0 ? "AK4Jet" : iType==1 ? "AK8Jet" : "Subjet";
      if (vector_int_["el_Near"+JetType+"Index"][iEle]!=-9999) {
        // LSF/LMD
	bool isNear = closest_jet_R08Cone[0] ? ele.DeltaR(closest_jet[iType])<0.8 : ele.DeltaR(closest_jet[iType])<0.4;
        vector_float_["el_Lep"+JetType+"Frac"][iEle] = isNear ? ele.Pt()/closest_jet[iType].Pt() : -9999;
        vector_float_["el_Lep"+JetType+"MassDrop"][iEle] = isNear ? (closest_jet[iType]-ele).M()/closest_jet[iType].M() : -9999;
        // 1) Revert JEC
        // 2) Remove eleon from jet if it is part of it
	// 3) Reapply JEC
        // 4) If the remaining jet has pt<20 or rem_pt/orig_pt<0.1,
        //    then consider instead the 2nd nearest jet
        TLorentzVector cleaned1_jet = closest_jet[iType], cleaned2_jet = closest_jet[iType], cleaned3_jet = closest_jet[iType];
        if (vector_int_["el_IsPartOfNear"+JetType+""][iEle]) {
	  // Step 1:
	  if (!isData_) cleaned1_jet *= closest_jet_jecFactor0[iType];
	  // Step 2:
	  cleaned1_jet -= ele;
	  // Step 3:
	  if (closest_jet_R08Cone[iType]) {
	    AK8_JetCorrector_->setJetEta(cleaned1_jet.Eta());
	    AK8_JetCorrector_->setJetPt(cleaned1_jet.Perp());
	    AK8_JetCorrector_->setJetE(cleaned1_jet.E());
	    AK8_JetCorrector_->setJetA(closest_jet_Area[iType]);
	    AK8_JetCorrector_->setRho(*h_double_["evt_rho"]);
	    AK8_JetCorrector_->setNPV(*h_int_["evt_npv"]);
	    cleaned1_jet *= AK8_JetCorrector_->getCorrection();
  	    } else {
	    AK4_JetCorrector_->setJetEta(cleaned1_jet.Eta());
	    AK4_JetCorrector_->setJetPt(cleaned1_jet.Perp());
	    AK4_JetCorrector_->setJetE(cleaned1_jet.E());
	    AK4_JetCorrector_->setJetA(closest_jet_Area[iType]);
	    AK4_JetCorrector_->setRho(*h_double_["evt_rho"]);
	    AK4_JetCorrector_->setNPV(*h_int_["evt_npv"]);
	    cleaned1_jet *= AK4_JetCorrector_->getCorrection();
	  }
          cleaned3_jet = cleaned2_jet = cleaned1_jet;
	  // Step 4:
          if (cleaned1_jet.Pt()<20) {
            cleaned2_jet = prev_jet[iType];
          }
          if (cleaned1_jet.Pt()<20 || cleaned1_jet.Pt()/closest_jet[iType].Pt()<0.1) {
            cleaned3_jet = prev_jet[iType];
          }
        }
        // PtRel, DR
        vector_float_["el_"+JetType+"V1DR"][iEle] = cleaned1_jet.E()>0 ? ele.DeltaR(cleaned1_jet) : 9999;
        vector_float_["el_"+JetType+"V2DR"][iEle] = cleaned2_jet.E()>0 ? ele.DeltaR(cleaned2_jet) : 9999;
        vector_float_["el_"+JetType+"V3DR"][iEle] = cleaned3_jet.E()>0 ? ele.DeltaR(cleaned3_jet) : 9999;
        vector_float_["el_"+JetType+"V1PtRel"][iEle] = cleaned1_jet.E()>0 ? ele.Perp(cleaned1_jet.Vect()) : 9999;
        vector_float_["el_"+JetType+"V2PtRel"][iEle] = cleaned2_jet.E()>0 ? ele.Perp(cleaned2_jet.Vect()) : 9999;
        vector_float_["el_"+JetType+"V3PtRel"][iEle] = cleaned3_jet.E()>0 ? ele.Perp(cleaned3_jet.Vect()) : 9999;
        //if (vector_float_["el_DRNearGenEleFromSLTop"][iEle]<0.05&&h_floats_["ele_Pt"]->at(iEle)>45&&vector_float_["el_PtNearGenTop"][iEle]>400) {
        //  std::cout<<"Orig Pt="<<closest_jet[iType].Pt()<<" Remain. Pt="<<cleaned1_jet.Pt()<<" IsPartOfJet="<<vector_int_["el_IsPartOfNear"+JetType][iEle];
        //  std::cout<<" LepFrac="<<vector_float_["el_Lep"+JetType+"Frac"][iEle]<<" MassDrop="<<vector_float_["el_Lep"+JetType+"MassDrop"][iEle]<<std::endl;
        //  std::cout<<"Mu["<<iEle<<"] Jet["<<vector_int_["el_Near"+JetType+"Index"][iEle]<<"] DR="<<vector_float_["el_"+JetType+"V3DR"][iEle]<<" PtRel="<<vector_float_["el_"+JetType+"V3PtRel"][iEle]<<std::endl;
	//  //std::cout<<((vector_float_["el_"+JetType+"V3DR"][iEle]>0.4||vector_float_["el_"+JetType+"V3PtRel"][iEle]>20)?"1":" ");
	//  //if (iType==2) std::cout<<"\n";
        //}
      }
    }
  }

  vector_float_["mu_DRNearGenMuFromSLTop"].assign(nmu,9999);
  vector_float_["mu_PtNearGenMuFromSLTop"].assign(nmu,-9999);
  vector_float_["mu_PtNearGenTop"].assign(nmu,-9999);
  vector_int_["mu_NearAK4JetIndex"].assign(nmu,-9999);
  vector_int_["mu_NearAK8JetIndex"].assign(nmu,-9999);
  vector_int_["mu_NearSubjetIndex"].assign(nmu,-9999);
  vector_int_["mu_IsPartOfNearAK4Jet"].assign(nmu,-9999);
  vector_int_["mu_IsPartOfNearAK8Jet"].assign(nmu,-9999);
  vector_int_["mu_IsPartOfNearSubjet"].assign(nmu,-9999);
  vector_float_["mu_LepAK4JetFrac"].assign(nmu,-9999);
  vector_float_["mu_LepAK8JetFrac"].assign(nmu,-9999);
  vector_float_["mu_LepSubjetFrac"].assign(nmu,-9999);
  vector_float_["mu_LepAK4JetMassDrop"].assign(nmu,-9999);
  vector_float_["mu_LepAK8JetMassDrop"].assign(nmu,-9999);
  vector_float_["mu_LepSubjetMassDrop"].assign(nmu,-9999);
  vector_float_["mu_AK4JetV1DR"].assign(nmu,9999);
  vector_float_["mu_AK4JetV2DR"].assign(nmu,9999);
  vector_float_["mu_AK4JetV3DR"].assign(nmu,9999);
  vector_float_["mu_AK8JetV1DR"].assign(nmu,9999);
  vector_float_["mu_AK8JetV2DR"].assign(nmu,9999);
  vector_float_["mu_AK8JetV3DR"].assign(nmu,9999);
  vector_float_["mu_SubjetV1DR"].assign(nmu,9999);
  vector_float_["mu_SubjetV2DR"].assign(nmu,9999);
  vector_float_["mu_SubjetV3DR"].assign(nmu,9999);
  vector_float_["mu_AK4JetV1PtRel"].assign(nmu,9999);
  vector_float_["mu_AK4JetV2PtRel"].assign(nmu,9999);
  vector_float_["mu_AK4JetV3PtRel"].assign(nmu,9999);
  vector_float_["mu_AK8JetV1PtRel"].assign(nmu,9999);
  vector_float_["mu_AK8JetV2PtRel"].assign(nmu,9999);
  vector_float_["mu_AK8JetV3PtRel"].assign(nmu,9999);
  vector_float_["mu_SubjetV1PtRel"].assign(nmu,9999);
  vector_float_["mu_SubjetV2PtRel"].assign(nmu,9999);
  vector_float_["mu_SubjetV3PtRel"].assign(nmu,9999);
  
  for (size_t iMu=0; iMu<nmu; ++iMu) {
    TLorentzVector mu; mu.SetPtEtaPhiE(h_floats_["mu_Pt"]->at(iMu), h_floats_["mu_Eta"]->at(iMu),
				       h_floats_["mu_Phi"]->at(iMu), h_floats_["mu_E"]->at(iMu));
    if (!isData_) if (mu_genlep_index.count(iMu)) {
      size_t genlep_index = mu_genlep_index[iMu];
      vector_float_["mu_DRNearGenMuFromSLTop"][iMu] =                                     /* mu_DRNearGenMuFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].DeltaR(mu); 
      vector_float_["mu_PtNearGenMuFromSLTop"][iMu] =                                     /* mu_PtNearGenMuFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].Pt();
      vector_float_["mu_PtNearGenTop"][iMu] = gen_top[genlep_index].Pt();                 /* mu_PtNearGenTop */
    }
    if (h_floats_["mu_Pt"]->at(iMu) > 45 && 
        fabs(h_floats_["mu_Eta"]->at(iMu)) < 2.1 &&
        h_floats_["mu_IsTightMuon"]->at(iMu) == 1) {
      ++single_int_["evt_NLep"];                                                        /* evt_NLep */
      goodleps.push_back(mu);
      single_float_["evt_HtLep"] += h_floats_["mu_Pt"]->at(iMu);                          /* evt_HtLep */
    }
    // ------------------------------------------------------------------------
    //                       Lepton-Jet Disambiguation
    
    const bool SoftDrop = 0; // 1: use W-like SoftDrop subjets (max 2 subjet) or 0: top-like subjets (2-4)
    const bool print_keys = 0;
    TLorentzVector closest_jet[3], prev_jet[3];
    float closest_jet_Area[3], closest_jet_jecFactor0[3];
    bool closest_jet_R08Cone[3];
    
    for (size_t iJet=0, nAK4jet=h_floats_["AK4_Pt"]->size(); iJet<nAK4jet; ++iJet) {
      
      // ----------------- AK4 jet ----------------------
    
      // Check if the lepton exists inside the closest jet
      TLorentzVector jet;
      jet.SetPtEtaPhiE(h_floats_["AK4_Pt"]->at(iJet), h_floats_["AK4_Eta"]->at(iJet),
		       h_floats_["AK4_Phi"]->at(iJet), h_floats_["AK4_E"]->at(iJet));
      float DR_jet = mu.DeltaR(jet);
      if (DR_jet<vector_float_["mu_AK4JetV1DR"][iMu]) {
	prev_jet[0] = closest_jet[0];
	closest_jet[0] = jet;
	closest_jet_Area[0] = h_floats_["AK4_jetArea"]->at(iJet);
	closest_jet_jecFactor0[0] = h_floats_["AK4_jecFactor0"]->at(iJet);
	closest_jet_R08Cone[0] = 0;
	vector_int_["mu_NearAK4JetIndex"][iMu] = iJet;
	vector_float_["mu_AK4JetV1DR"][iMu] = DR_jet;
	// Loop on all keys and check if we need to remove lepton from the jet if the lepton is part of it
	vector_int_["mu_IsPartOfNearAK4Jet"][iMu] = 0;
	for (size_t iKey=0, nKey=h_keys_["AK4"]->at(iJet).size(); iKey<nKey; ++iKey)
	  if (h_floats_["mu_Key"]->at(iMu)==h_keys_["AK4"]->at(iJet)[iKey]) 
	    vector_int_["mu_IsPartOfNearAK4Jet"][iMu] = 1;
      }
    }
    
    for (size_t iJet=0; iJet<njet; ++iJet) {
      
      // ----------------- AK8 jet ----------------------
      
      // Check if the lepton exists inside the closest fatjet
      size_t nSubjet_SD = 0, nSubjetKeys_SD = 0;
      TLorentzVector fatjet;
      fatjet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(iJet), h_floats_["AK8_Eta"]->at(iJet),
		       h_floats_["AK8_Phi"]->at(iJet), h_floats_["AK8_E"]->at(iJet));
      float DR_fatjet = mu.DeltaR(fatjet);
      // Part of the keys for the fatjet are inside SoftDrop subjets
      std::vector<int> AK8Keys;
      for (size_t isub=0; isub<2; ++isub) {
	size_t iSubjet = isub==0 ? h_floats_["AK8_vSubjetIndex0"]->at(iJet) 
	    : h_floats_["AK8_vSubjetIndex1"]->at(iJet);
	if (iSubjet != (size_t)-1) {
	  ++nSubjet_SD;
	  std::vector<int> subjet_keys = h_keys_["AK8Sub"]->at(iSubjet);
	  AK8Keys.insert(AK8Keys.end(), subjet_keys.begin(), subjet_keys.end());
	  nSubjetKeys_SD += subjet_keys.size();
	}
      }
      // Add rest of the keys, but skip first N subjet keys
      AK8Keys.insert(AK8Keys.end(), h_keys_["AK8"]->at(iJet).begin()+nSubjet_SD, h_keys_["AK8"]->at(iJet).end());
      if (DR_fatjet<vector_float_["mu_AK8JetV1DR"][iMu]) {
	prev_jet[1] = closest_jet[1];
	closest_jet[1] = fatjet;
	closest_jet_Area[1] = h_floats_["AK8_jetArea"]->at(iJet);
	closest_jet_jecFactor0[1] = h_floats_["AK8_jecFactor0"]->at(iJet);
	closest_jet_R08Cone[1] = 1;
	vector_int_["mu_NearAK8JetIndex"][iMu] = iJet;
	vector_float_["mu_AK8JetV1DR"][iMu] = DR_fatjet;
	// Now loop on all keys and check if we need
	// to remove lepton from the fatjet if the lepton is part of it
	vector_int_["mu_IsPartOfNearAK8Jet"][iMu] = 0;
	for (size_t iKey=0, nKey=AK8Keys.size(); iKey<nKey; ++iKey)
	  if (h_floats_["mu_Key"]->at(iMu)==AK8Keys[iKey]) vector_int_["mu_IsPartOfNearAK8Jet"][iMu] = 1;
      }
      
      // --------------- AK8 Subjets --------------------
      
      // First Loop on and count subjets and check if lepton is part of it
      // In case lepton is found, substract it's 4vec from the jet
      size_t nSubjet = 0, nSubjetKeys = 0;
      for (size_t isub=0, nSub = SoftDrop ? 2 : 4; isub<nSub; ++isub) {
	size_t iSubjet = 
	  SoftDrop ? (isub==0 ? h_floats_["AK8_vSubjetIndex0"]->at(iJet) 
		      : h_floats_["AK8_vSubjetIndex1"]->at(iJet)) : 
	  isub==0 ? h_floats_["AK8_topSubjetIndex0"]->at(iJet) : 
	  isub==1 ? h_floats_["AK8_topSubjetIndex1"]->at(iJet) : 
	  isub==2 ? h_floats_["AK8_topSubjetIndex2"]->at(iJet) : 
	  h_floats_["AK8_topSubjetIndex3"]->at(iJet);
	// If subjet exist calc MinDR and for the closest check if we need
	// to remove lepton from the subjet if the lepton is part of it
	if (isub==0 || iSubjet != (size_t)-1) {
	  ++nSubjet;
	  TLorentzVector subjet;
	  // If SubJet doesn't exist, treat AK8 jet as a subjet
	  std::string prefix = iSubjet!=(size_t)-1 ? "CmsTTSub_" : "AK8_";
	  size_t index = iSubjet!=(size_t)-1 ? iSubjet : iJet;
	  subjet.SetPtEtaPhiE(h_floats_[prefix+"Pt"]->at(index), h_floats_[prefix+"Eta"]->at(index),
			      h_floats_[prefix+"Phi"]->at(index), h_floats_[prefix+"E"]->at(index));
	  float DR_subjet = mu.DeltaR(subjet);
	  if (DR_subjet<vector_float_["mu_SubjetV1DR"][iMu]) {
	    prev_jet[2] = closest_jet[2];
	    closest_jet[2] = subjet;
	    closest_jet_Area[2] = h_floats_[prefix+"jetArea"]->at(index);
	    closest_jet_jecFactor0[2] = h_floats_[prefix+"jecFactor0"]->at(index);
	    closest_jet_R08Cone[2] = iSubjet==(size_t)-1;
	    vector_int_["mu_NearSubjetIndex"][iMu] = iSubjet;
	    vector_float_["mu_SubjetV1DR"][iMu] = DR_subjet;
	    // Check if lepton is part of the subjet
	    vector_int_["mu_IsPartOfNearSubjet"][iMu] = 0;
	    std::vector<int> subjet_keys = iSubjet!=(size_t)-1 ? h_keys_[SoftDrop? "AK8Sub" : "CmsTTSub"]->at(iSubjet) : AK8Keys;
	    nSubjetKeys += subjet_keys.size();
	    for (size_t iKey=0, nKey=subjet_keys.size(); iKey<nKey; ++iKey)
	      if (h_floats_["mu_Key"]->at(iMu)==subjet_keys[iKey])
		vector_int_["mu_IsPartOfNearSubjet"][iMu] = 1;
	  }
	}
      }
      
      if (print_keys) {
        std::cout<<iJet<<" nSubjet="<<nSubjet<<" nSubjet_SD="<<nSubjet_SD<<" nSubjetKeys="<<nSubjetKeys
        	 <<" nSubjetKeys_SD="<<nSubjetKeys_SD<<" RestKeys="<<h_keys_["AK8"]->at(iJet).size()-nSubjet_SD<<"\n";
        std::vector<int> jet_keys = h_keys_["AK8"]->at(iJet);
        std::cout<<"   rest:";
        for (size_t iKey=nSubjet_SD, nKey=jet_keys.size(); iKey<nKey; ++iKey) if (nSubjet_SD==1) std::cout<<" "<<jet_keys[iKey];
        std::cout<<"\n\n";
      }
      
    } // End of AK8 Jet loop
    //std::cout<<"--> Mu["<<iMu<<"] "<<"jet/subjet-match="<<vector_int_["mu_IsPartOfNearAK8Jet"][iMu]<<" "<<vector_int_["mu_IsPartOfNearSubjet"][iMu]<<", MinDR="<<vector_float_["mu_AK8JetV1DR"][iMu]<<" "<<vector_float_["mu_SubjetV1DR"][iMu]<<std::endl;
    
    // Calculate Jet/SubJet pt fraction, Jet mass drop
    for (int iType=0; iType<3; ++iType) {
      std::string JetType = iType==0 ? "AK4Jet" : iType==1 ? "AK8Jet" : "Subjet";
      if (vector_int_["mu_Near"+JetType+"Index"][iMu]!=-9999) {
        // LSF/LMD
	bool isNear = closest_jet_R08Cone[0] ? mu.DeltaR(closest_jet[iType])<0.8 : mu.DeltaR(closest_jet[iType])<0.4;
        vector_float_["mu_Lep"+JetType+"Frac"][iMu] = isNear ? mu.Pt()/closest_jet[iType].Pt() : -9999;
        vector_float_["mu_Lep"+JetType+"MassDrop"][iMu] = isNear ? (closest_jet[iType]-mu).M()/closest_jet[iType].M() : -9999;
	// 1) Revert JEC
        // 2) Remove muon from jet if it is part of it
	// 3) Reapply JEC
        // 4) If the remaining jet has pt<20 or rem_pt/orig_pt<0.1,
        //    then consider instead the 2nd nearest jet
        TLorentzVector cleaned1_jet = closest_jet[iType], cleaned2_jet = closest_jet[iType], cleaned3_jet = closest_jet[iType];
        if (vector_int_["mu_IsPartOfNear"+JetType+""][iMu]) {
	  // Step 1:
	  if (!isData_) cleaned1_jet *= closest_jet_jecFactor0[iType];
	  // Step 2:
	  cleaned1_jet -= mu;
	  // Step 3:
	  if (closest_jet_R08Cone[iType]) {
	    AK8_JetCorrector_->setJetEta(cleaned1_jet.Eta());
	    AK8_JetCorrector_->setJetPt(cleaned1_jet.Perp());
	    AK8_JetCorrector_->setJetE(cleaned1_jet.E());
	    AK8_JetCorrector_->setJetA(closest_jet_Area[iType]);
	    AK8_JetCorrector_->setRho(*h_double_["evt_rho"]);
	    AK8_JetCorrector_->setNPV(*h_int_["evt_npv"]);
	    cleaned1_jet *= AK8_JetCorrector_->getCorrection();
  	    } else {
	    AK4_JetCorrector_->setJetEta(cleaned1_jet.Eta());
	    AK4_JetCorrector_->setJetPt(cleaned1_jet.Perp());
	    AK4_JetCorrector_->setJetE(cleaned1_jet.E());
	    AK4_JetCorrector_->setJetA(closest_jet_Area[iType]);
	    AK4_JetCorrector_->setRho(*h_double_["evt_rho"]);
	    AK4_JetCorrector_->setNPV(*h_int_["evt_npv"]);
	    cleaned1_jet *= AK4_JetCorrector_->getCorrection();
	  }
          cleaned3_jet = cleaned2_jet = cleaned1_jet;
	  // Step 4:
          if (cleaned1_jet.Pt()<20) {
            cleaned2_jet = prev_jet[iType];
          }
          if (cleaned1_jet.Pt()<20 || cleaned1_jet.Pt()/closest_jet[iType].Pt()<0.1) {
            cleaned3_jet = prev_jet[iType];
          }
        }
        // PtRel, DR
        vector_float_["mu_"+JetType+"V1DR"][iMu] = cleaned1_jet.E()>0 ? mu.DeltaR(cleaned1_jet) : 9999;
        vector_float_["mu_"+JetType+"V2DR"][iMu] = cleaned2_jet.E()>0 ? mu.DeltaR(cleaned2_jet) : 9999;
        vector_float_["mu_"+JetType+"V3DR"][iMu] = cleaned3_jet.E()>0 ? mu.DeltaR(cleaned3_jet) : 9999;
        vector_float_["mu_"+JetType+"V1PtRel"][iMu] = cleaned1_jet.E()>0 ? mu.Perp(cleaned1_jet.Vect()) : 9999;
        vector_float_["mu_"+JetType+"V2PtRel"][iMu] = cleaned2_jet.E()>0 ? mu.Perp(cleaned2_jet.Vect()) : 9999;
        vector_float_["mu_"+JetType+"V3PtRel"][iMu] = cleaned3_jet.E()>0 ? mu.Perp(cleaned3_jet.Vect()) : 9999;
        //if (vector_float_["mu_DRNearGenMuFromSLTop"][iMu]<0.05&&h_floats_["mu_Pt"]->at(iMu)>45&&vector_float_["mu_PtNearGenTop"][iMu]>400) {
        //  std::cout<<"Orig Pt="<<closest_jet[iType].Pt()<<" Remain. Pt="<<cleaned1_jet.Pt()<<" IsPartOfJet="<<vector_int_["mu_IsPartOfNear"+JetType][iMu];
        //  std::cout<<" LepFrac="<<vector_float_["mu_Lep"+JetType+"Frac"][iMu]<<" MassDrop="<<vector_float_["mu_Lep"+JetType+"MassDrop"][iMu]<<std::endl;
        //  std::cout<<"Mu["<<iMu<<"] Jet["<<vector_int_["mu_Near"+JetType+"Index"][iMu]<<"] DR="<<vector_float_["mu_"+JetType+"V3DR"][iMu]<<" PtRel="<<vector_float_["mu_"+JetType+"V3PtRel"][iMu]<<std::endl;
	//  //std::cout<<((vector_float_["mu_"+JetType+"V3DR"][iMu]>0.4||vector_float_["mu_"+JetType+"V3PtRel"][iMu]>20)?"1":" ");
	//  //if (iType==2) std::cout<<"\n";
        //}
      }
    }
  }
  
  // ---------------------
  // --- Top Selection ---
  // ---------------------
  
  single_int_["evt_NTopHad"] = 0;
  single_int_["evt_NTopHadPreTag"] = 0;
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
    if (i<2) { // only check two highest pt jets
      if (h_floats_["AK8_Pt"]->at(i) > 400 &&
	  h_floats_["AK8_softDropMass"]->at(i) > 110 &&
	  h_floats_["AK8_softDropMass"]->at(i) < 210) {
	++single_int_["evt_NTopHadPreTag"];                                                 /* evt_NTopHadPreTag */
	if (single_int_["evt_NTopHadPreTag"]==1) 
	  top1_had.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
				h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
	if (single_int_["evt_NTopHadPreTag"]==2) 
	  top2_had.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
				h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
	// Pass n-subjettiness cut
	if (h_floats_["AK8_tau2"]->at(i)>0 ?  
	    (h_floats_["AK8_tau3"]->at(i)/h_floats_["AK8_tau2"]->at(i)) < 0.75 : 0 ) {
	  vector_int_["jetAK8_PassTopTag"][i] = 1;
	  ++single_int_["evt_NTopHad"];                                                     /* evt_NTopHad */
	  is_top = true;
	}
      }
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
  if (single_int_["evt_NTopHadPreTag"]==2) {
    single_float_["evt_TTHadDR"]   = top1_had.DeltaR(top2_had);                         /* evt_TTHadDR */
    single_float_["evt_TTHadDPhi"] = top1_had.DeltaPhi(top2_had);                       /* evt_TTHadDPhi */
    single_float_["evt_TTHadDEta"] = fabs(top1_had.Eta() - top2_had.Eta());             /* evt_TTHadDEta */
    single_float_["evt_TTHadSumPt"] = top1_had.Pt()+top2_had.Pt();                      /* evt_TTHadSumPt */
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
  
  TVector3 metl;
  metl.SetPtEtaPhi(h_floats_["met_Pt"]->at(0), 0, h_floats_["met_Phi"]->at(0));
  
  // Fully hadronic channel
  single_float_["evt_TTHadMR"]  = -9999;
  single_float_["evt_TTHadMTR"] = -9999;
  single_float_["evt_TTHadR"]   = -9999;
  single_float_["evt_TTHadR2"]  = -9999;
  if (single_int_["evt_NTopHadPreTag"]==2) {
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
    if (h_floats_["AK4_Pt"]->size()<60) {
      std::vector<TLorentzVector> hemis_AK8 = Razor::CombineJets(jets_AK8);
      single_float_["evt_MR"]  = Razor::CalcMR(hemis_AK8[0], hemis_AK8[1]);              /* evt_MR */
      single_float_["evt_MTR"] = Razor::CalcMTR(hemis_AK8[0], hemis_AK8[1], metl);       /* evt_MTR */
      single_float_["evt_R"]   = single_float_["evt_MTR"] / single_float_["evt_MR"];     /* evt_R */
      single_float_["evt_R2"]  = std::pow(single_float_["evt_R"], 2);                    /* evt_R2 */
    } else {
      std::cout<<"Too many AK8: "<<jets_AK8.size()<<" "<<h_floats_["AK8_Pt"]->size()<<std::endl;
    }
  }

  // AK4
  single_float_["evt_AK4_MR"]  = -9999;
  single_float_["evt_AK4_MTR"] = -9999;
  single_float_["evt_AK4_R"]   = -9999;
  single_float_["evt_AK4_R2"]  = -9999;
  if (jets_AK4.size() >= 2) {
    if (h_floats_["AK4_Pt"]->size() <60) {
      std::vector<TLorentzVector> hemis_AK4 = Razor::CombineJets(jets_AK4);
      single_float_["evt_AK4_MR"]  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);          /* evt_AK4_MR */
      single_float_["evt_AK4_MTR"] = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], metl);   /* evt_AK4_MTR */
      single_float_["evt_AK4_R"]   = single_float_["evt_AK4_MTR"] / single_float_["evt_AK4_MR"]; /* evt_AK4_R */
      single_float_["evt_AK4_R2"]  = std::pow(single_float_["evt_AK4_R"], 2);            /* evt_AK4_R2 */
    } else {
      std::cout<<"Too many AK4: "<<jets_AK4.size()<<" "<<h_floats_["AK4_Pt"]->size()<<std::endl;
    }
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GEdmExtraVarProducer);
