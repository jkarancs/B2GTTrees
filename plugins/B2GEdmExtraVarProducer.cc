#include "Analysis/B2GTTrees/interface/B2GEdmExtraVarProducer.h"
#include "Analysis/B2GTTrees/interface/Razor.h"
#include "Analysis/B2GTTrees/data/GluinoXSec.h"
#include "Analysis/B2GTTrees/data/StopXSec.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/deltaR.h"

void B2GEdmExtraVarProducer::init_tokens_() {
  edm::EDGetTokenT<std::vector<std::string> >(mayConsume<std::vector<std::string>, edm::InRun>(edm::InputTag(trigger_label_, "triggerNameTree")));
  edm::EDGetTokenT<std::vector<std::string> >(mayConsume<std::vector<std::string>, edm::InRun>(edm::InputTag(filter_label_,  "triggerNameTree")));
  edm::EDGetTokenT<std::vector<int> >(consumes<std::vector<int> >(edm::InputTag(trigger_label_, "triggerPrescaleTree")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(trigger_label_, "triggerBitTree")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(filter_label_,  "triggerBitTree")));
  
  edm::EDGetTokenT<double>(consumes<double>(edm::InputTag("fixedGridRhoFastjetAll", "")));
  edm::EDGetTokenT<int>(consumes<int>(edm::InputTag(vtx_label_, vtx_prefix_+"npv")));
  edm::EDGetTokenT<std::vector<int> >(consumes<std::vector<int> >(edm::InputTag(vtx_label_, vtx_prefix_+"ndof")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(vtx_label_, vtx_prefix_+"z")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(vtx_label_, vtx_prefix_+"rho")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(met_label_, met_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(met_label_, met_prefix_+"Phi")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Eta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"Phi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"E")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"jecFactor0")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"jetArea")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"SmearedPt")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau2")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau3")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"softDropMassPuppi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jecFactor0")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jetArea")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"nSubJets")));
  //edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex0")));
  //edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex1")));
  //edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex2")));
  //edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex3")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex0")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex1")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Eta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Phi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"E")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"jecFactor0")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"jetArea")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"CSVv2")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"CMVAv2")));
  
  // Jet ID variables
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"MuonEnergy")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"MuonEnergy")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedHadronEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedEmEnergyFrac")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralMultiplicity")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"MuonEnergy")));
  
  edm::EDGetTokenT<std::vector<std::vector<int> > >(consumes<std::vector<std::vector<int> > >(edm::InputTag(AK4JetKeys_label_,"")));
  edm::EDGetTokenT<std::vector<std::vector<int> > >(consumes<std::vector<std::vector<int> > >(edm::InputTag(AK8JetKeys_label_,"")));
  edm::EDGetTokenT<std::vector<std::vector<int> > >(consumes<std::vector<std::vector<int> > >(edm::InputTag(AK8SubjetKeys_label_,"")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Eta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Phi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"E")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Charge")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Key")));
  
  // Electron ID variables
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"SCEta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"full5x5siee")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"dEtaInSeed")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"dPhiIn")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"HoE")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Iso03")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"ooEmooP")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Dxy")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"Dz")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"missHits")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"hasMatchedConVeto")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(electrons_label_, electrons_prefix_+"vidLoosenoiso")));
  
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"Pt")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"Eta")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"Phi")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"E")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"Charge")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"IsTightMuon")));
  edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(muons_label_, muons_prefix_+"Key")));

  edm::EDGetTokenT<reco::VertexCollection>(consumes<reco::VertexCollection>(edm::InputTag("offlineSlimmedPrimaryVertices")));
  edm::EDGetTokenT<pat::PackedCandidateCollection>(consumes<pat::PackedCandidateCollection>(edm::InputTag("packedPFCandidates")));
  edm::EDGetTokenT<pat::METCollection>(consumes<pat::METCollection>(edm::InputTag("slimmedMETs")));
  edm::EDGetTokenT<pat::METCollection>(consumes<pat::METCollection>(edm::InputTag("slimmedMETsPuppi")));
  //edm::EDGetTokenT<pat::JetCollection>(consumes<pat::JetCollection>(edm::InputTag("slimmedJetsAK8")));
  
  if (!isData_) {
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Pt")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Eta")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Phi")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"E")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Charge")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"ID")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Status")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Mom0ID")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Mom0Status")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Mom1ID")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Mom1Status")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Dau0ID")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Dau0Status")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Dau1ID")));
    edm::EDGetTokenT<std::vector<float> >(consumes<std::vector<float> >(edm::InputTag(gen_label_, gen_prefix_+"Dau1Status")));
    
    edm::EDGetTokenT<LHERunInfoProduct>(mayConsume<LHERunInfoProduct, edm::InRun>(edm::InputTag(lhe_label_, "")));
    edm::EDGetTokenT<LHEEventProduct>(consumes<LHEEventProduct>(edm::InputTag(lhe_label_, "")));
    
    edm::EDGetTokenT<GenLumiInfoHeader>(mayConsume<GenLumiInfoHeader, edm::InLumi>(edm::InputTag("generator")));
    edm::EDGetTokenT<GenEventInfoProduct>(consumes<GenEventInfoProduct>(edm::InputTag("generator")));
    
    edm::EDGetTokenT<reco::GenParticleCollection>(consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles")));
  }
}

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

  // ----------------------------
  // - Trigger/Filter names     -
  // ----------------------------
  
  iRun.getByLabel(edm::InputTag(trigger_label_, "triggerNameTree"),      h_strings_["trigger_names"]);
  iRun.getByLabel(edm::InputTag(filter_label_,  "triggerNameTree"),      h_strings_["filter_names"]);
  bool print_all = false;
  
  nfilt_=h_strings_["filter_names"]->size();
  filters_.clear();
  for ( auto filter : filter_names_ ) for (size_t i=0; i<nfilt_; ++i) 
    if (h_strings_["filter_names"]->at(i).find(filter)==0) filters_[filter] = i;
  std::cout<<"Filters found: "<<std::endl;
  if (print_all) for (size_t i=0; i<nfilt_; ++i) std::cout<<h_strings_["filter_names"]->at(i)<<std::endl;
  else for ( auto filter : filters_ ) std::cout<<filter.first<<std::endl;
  
  ntrig_=h_strings_["trigger_names"]->size();
  triggers_.clear();
  for ( auto trig : trigger_names_ ) for (size_t i=0; i<ntrig_; ++i) 
    if (h_strings_["trigger_names"]->at(i).find(trig+"_v")==0) triggers_[trig] = i;
  std::cout<<"Triggers found: "<<std::endl;
  if (print_all) for (size_t i=0; i<ntrig_; ++i) std::cout<<h_strings_["trigger_names"]->at(i)<<std::endl;
  else for ( auto trigger : triggers_ ) std::cout<<trigger.first<<std::endl;
}

void B2GEdmExtraVarProducer::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup) {
  if (!isData_) {
    // SUSY signal specific info in 80X
    edm::Handle<GenLumiInfoHeader> genLumiInfo;
    iLumi.getByLabel(edm::InputTag("generator"), genLumiInfo);
    
    if (genLumiInfo.isValid()) {
      
      // Check which PDF set was used
      lha_pdf_id_ = 263000;
      std::cout<<"GEN: LHA PDF ID = "<<lha_pdf_id_<<std::endl;
      std::cout<<"GEN:   --> For more info about the sets, check: https://lhapdf.hepforge.org/pdfsets.html"<<std::endl;
      
      // Print headers
      //std::cout<<"GEN: Weight info in Lumi:"<<std::endl;
      //for (auto wname : genLumiInfo->weightNames()) std::cout<<"GEN:   "<<wname<<std::endl;
      //std::cout<<"GEN: Header info in Lumi:"<<std::endl;
      //for (auto header : genLumiInfo->lheHeaders()) std::cout<<header.first<<"\n"<<header.second<<std::endl;
    }
  }
}

void B2GEdmExtraVarProducer::calculate_variables(edm::Event const& iEvent, edm::EventSetup const& iSetup) {
  // Read variables from EdmNtuple
  iEvent.getByLabel(edm::InputTag(trigger_label_, "triggerBitTree"),       h_floats_["trigger_bits"]);
  iEvent.getByLabel(edm::InputTag(trigger_label_, "triggerPrescaleTree"),  h_ints_["trigger_prescales"]);
  iEvent.getByLabel(edm::InputTag(filter_label_,  "triggerBitTree"),       h_floats_["filter_bits"]);
  
  iEvent.getByLabel(edm::InputTag("fixedGridRhoFastjetAll", ""),   h_double_["evt_rho"]);
  iEvent.getByLabel(edm::InputTag(vtx_label_, vtx_prefix_+"npv"),  h_int_["vtx_npv"]);
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
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"SmearedPt"),  h_floats_["AK4_SmearedPt"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Pt"),                h_floats_["AK8_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Eta"),               h_floats_["AK8_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"Phi"),               h_floats_["AK8_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"E"),                 h_floats_["AK8_E"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau2"),              h_floats_["AK8_tau2"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"tau3"),              h_floats_["AK8_tau3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"softDropMassPuppi"), h_floats_["AK8_softDropMassPuppi"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jecFactor0"),        h_floats_["AK8_jecFactor0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"jetArea"),           h_floats_["AK8_jetArea"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"nSubJets"),          h_floats_["AK8_nSubJets"]);
  //iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex0"),   h_floats_["AK8_topSubjetIndex0"]);
  //iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex1"),   h_floats_["AK8_topSubjetIndex1"]);
  //iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex2"),   h_floats_["AK8_topSubjetIndex2"]);
  //iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"topSubjetIndex3"),   h_floats_["AK8_topSubjetIndex3"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex0"),     h_floats_["AK8_vSubjetIndex0"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"vSubjetIndex1"),     h_floats_["AK8_vSubjetIndex1"]);
  
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Pt"),         h_floats_["AK8Sub_Pt"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Eta"),        h_floats_["AK8Sub_Eta"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"Phi"),        h_floats_["AK8Sub_Phi"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"E"),          h_floats_["AK8Sub_E"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"jecFactor0"), h_floats_["AK8Sub_jecFactor0"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"jetArea"),    h_floats_["AK8Sub_jetArea"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"CSVv2"),      h_floats_["AK8Sub_CSVv2"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"CMVAv2"),     h_floats_["AK8Sub_CMVAv2"]);
  
  iEvent.getByLabel(edm::InputTag(AK4JetKeys_label_),      h_keys_["AK4"]);
  iEvent.getByLabel(edm::InputTag(AK8JetKeys_label_),      h_keys_["AK8"]);
  iEvent.getByLabel(edm::InputTag(AK8SubjetKeys_label_),   h_keys_["AK8Sub"]);
  
  // JET ID
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralHadronEnergyFrac"), h_floats_["AK4_neutralHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralEmEnergyFrac"),     h_floats_["AK4_neutralEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedHadronEnergyFrac"), h_floats_["AK4_chargedHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedEmEnergyFrac"),     h_floats_["AK4_chargedEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"chargedMultiplicity"),     h_floats_["AK4_chargedMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"neutralMultiplicity"),     h_floats_["AK4_neutralMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK4Jets_label_, AK4Jets_prefix_+"MuonEnergy"),              h_floats_["AK4_MuonEnergy"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralHadronEnergyFrac"), h_floats_["AK8_neutralHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralEmEnergyFrac"),     h_floats_["AK8_neutralEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedHadronEnergyFrac"), h_floats_["AK8_chargedHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedEmEnergyFrac"),     h_floats_["AK8_chargedEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"chargedMultiplicity"),     h_floats_["AK8_chargedMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"neutralMultiplicity"),     h_floats_["AK8_neutralMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK8Jets_label_, AK8Jets_prefix_+"MuonEnergy"),              h_floats_["AK8_MuonEnergy"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralHadronEnergyFrac"), h_floats_["AK8Sub_neutralHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralEmEnergyFrac"),     h_floats_["AK8Sub_neutralEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedHadronEnergyFrac"), h_floats_["AK8Sub_chargedHadronEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedEmEnergyFrac"),     h_floats_["AK8Sub_chargedEmEnergyFrac"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"chargedMultiplicity"),     h_floats_["AK8Sub_chargedMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"neutralMultiplicity"),     h_floats_["AK8Sub_neutralMultiplicity"]);
  iEvent.getByLabel(edm::InputTag(AK8Subjets_label_, AK8Subjets_prefix_+"MuonEnergy"),              h_floats_["AK8Sub_MuonEnergy"]);
  
  // Leptons
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Pt"),     h_floats_["ele_Pt"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Eta"),    h_floats_["ele_Eta"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Phi"),    h_floats_["ele_Phi"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"E"),      h_floats_["ele_E"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Charge"), h_floats_["ele_Charge"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Key"),    h_floats_["ele_Key"]);

  // Electron ID variables
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"SCEta"),             h_floats_["ele_SCEta"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"full5x5siee"),       h_floats_["ele_full5x5siee"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"dEtaInSeed"),        h_floats_["ele_dEtaInSeed"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"dPhiIn"),            h_floats_["ele_dPhiIn"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"HoE"),               h_floats_["ele_HoE"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Iso03"),             h_floats_["ele_Iso03"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"ooEmooP"),           h_floats_["ele_ooEmooP"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Dxy"),               h_floats_["ele_Dxy"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"Dz"),                h_floats_["ele_Dz"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"missHits"),          h_floats_["ele_missHits"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"hasMatchedConVeto"), h_floats_["ele_hasMatchedConVeto"]);
  iEvent.getByLabel(edm::InputTag(electrons_label_, electrons_prefix_+"vidLoosenoiso"),     h_floats_["ele_vidLoosenoiso"]);
  
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
  single_float_["evt_Gen_Weight"] = -9999;                                             /* evt_Gen_Weight */
  single_float_["evt_Gen_Ht"] = -9999;                                                 /* evt_Gen_Ht */
  
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
  // https://indico.cern.ch/event/459797/contributions/1961581/attachments/1181555/1800214/mcaod-Feb15-2016.pdf
  vector_float_["scale_Weights"].clear();
  vector_float_["pdf_Weights"].clear();
  vector_float_["alphas_Weights"].clear();
  if (!isData_) {
    edm::Handle<GenEventInfoProduct> genEvtInfo;
    iEvent.getByLabel("generator", genEvtInfo);
    
    edm::Handle<LHEEventProduct> lheEvtInfo;
    iEvent.getByLabel(lhe_label_, lheEvtInfo);
    
    single_int_["evt_LHA_PDF_ID"] = lha_pdf_id_;
    
    // Generator level HT
    if (lheEvtInfo.isValid()) {
      lhef::HEPEUP lheParticleInfo = lheEvtInfo->hepeup();
      // Get the five vector (Px, Py, Pz, E and M in GeV)
      std::vector<lhef::HEPEUP::FiveVector> allParticles = lheParticleInfo.PUP;
      std::vector<int> statusCodes = lheParticleInfo.ISTUP;
      single_float_["evt_Gen_Ht"] = 0;
      for (unsigned int i = 0; i < allParticles.size(); i++) {
	auto absId = abs(lheParticleInfo.IDUP[i]);
	if (statusCodes[i] == 1 && ( absId < 11 || absId > 16 ) && absId != 22 && !hasAncestor_(i, lheParticleInfo, 6))
	  single_float_["evt_Gen_Ht"] += std::sqrt(std::pow(allParticles[i][0], 2) + std::pow(allParticles[i][1], 2));
      }
    }
    
    if (lheEvtInfo.isValid() && genEvtInfo.isValid()) {
      // GenHT
      //const lhef::HEPEUP& lheEvent = lheEvtInfo->hepeup();
      //std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
      //single_float_["evt_Gen_Ht"] = 0;
      //for ( size_t idxParticle = 0, numParticles = lheParticles.size(); idxParticle < numParticles; ++idxParticle ) {
      //  int absPdgId = TMath::Abs(lheEvent.IDUP[idxParticle]);
      //  int status = lheEvent.ISTUP[idxParticle];
      //  if ( status == 1 && ((absPdgId >= 1 && absPdgId <= 6) || absPdgId == 21) )   // quarks and gluons
      //    single_float_["evt_Gen_Ht"] += TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + 
      //  					     TMath::Power(lheParticles[idxParticle][1], 2.)); // first entry is px, second py
      //}
      
      // We only look for the sign of the gen weight but not it's value
      // The xsec weight is already calculated, but certain NLO samples
      // have negative weights and such events need to be subtracted
      // (and consequently the weight also needs to be corrected with a factor)
      single_float_["evt_Gen_Weight"] = genEvtInfo->weight();
      
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
      // FastSim indices are larger by 1
      if (isFastSim_) ++first;
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
	if (isFastSim_) {
	  vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[110].wgt/lheOrigWeight);
	  vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[111].wgt/lheOrigWeight);
	} else {
	  vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[109].wgt/lheOrigWeight);
	  vector_float_["alphas_Weights"].push_back(lheEvtInfo->weights()[110].wgt/lheOrigWeight);
	}
      }
    } else if (genEvtInfo.isValid()) {
      // SUSY MC only has genEvtInfo
      // nominal weight is 1
      // --> weight should be weights()[1] = weights()[10] = typically 0.0003*
      single_float_["evt_Gen_Weight"] = genEvtInfo->weight();
      
      // This weight is used to normalize pdf/scale etc weights
      double genNomWeight = genEvtInfo->weights()[1];
      
      // Print factors in an event
      //std::cout<<"GEN: weight() = "<<genEvtInfo->weight()<<std::endl;
      //for (size_t i=0; i<genEvtInfo->weights().size(); ++i)
      //  std::cout<<"GEN: weights() - index: "<<i<<" wgt = "<<genEvtInfo->weights()[i]<<" wgtNorm = "<<(genEvtInfo->weights()[i]/genNomWeight)<<std::endl;
      
      // Renormalization/Factorization scale weights
      // These are the first 9 weights for all generators
      // mu_R and mu_F are varied independently (by a factor of 1, 2, 0.5) - check GEN header
      // [1] is the default weight (no variation)
      // --> I skip saving it (one can just use 1)
      // --> Also do not save unphysical combinations as recommended
      //    (mu_R = 0.5, mu_F = 2 and mu_R = 2, mu_F = 0.5)
      // Save only ids: 2,3,4,5,7,9
      if (genEvtInfo->weights().size()>=10) for (size_t i=1; i<10; ++i) if (i!=1&&i!=6&&i!=8)
        vector_float_["scale_Weights"].push_back(genEvtInfo->weights()[i]/genNomWeight);
      
      // PDF weights
      // Usually a set of 100 weights (excluding default)
      // Only default PDF variation is saved, but if needed
      // likely others are available depending on the generator
      // index of first weight varies, beware!
      // Sometimes first weight is default=1 weight (has to skip!)
      // Additional info: MC2Hessian conversion will soon be provided
      // NNPDF30_lo_as_0130 (SUSY signals has +1 weight weights()[0])
      size_t first = 11;
      if (genEvtInfo->weights().size()>=first+100) for (size_t i=first; i<first+100; ++i)
        vector_float_["pdf_Weights"].push_back(genEvtInfo->weights()[i]/genNomWeight);
      
      // Alpha_s weights (only given for NLO!)
    }
  }
  
  // ----------------------------
  // - Trigger/Filter decisions -
  // ----------------------------
  for ( auto filter : filters_ ) single_int_[filter.first]                              /* Flag_* */
      = h_floats_["filter_bits"]->at(filter.second);
  for ( auto trigger : triggers_ ) {
    single_int_[trigger.first] = h_floats_["trigger_bits"]->at(trigger.second);         /* HLT_* */
    single_int_[trigger.first+"_prescale"]                                              /* HLT_*_prescale */
      = h_ints_["trigger_prescales"]->at(trigger.second);
  }
  
  // ----------------------------
  // -        Vertices          -
  // ----------------------------
  
  single_int_["evt_NGoodVtx"] = 0;
  for (int iVtx=0; iVtx<*h_int_["vtx_npv"]; ++iVtx)
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
  std::vector<TLorentzVector> gen_q_from_top;
  std::vector<bool>           gen_b_from_top;
  std::vector<TLorentzVector> gen_lep_from_W;
  std::vector<TLorentzVector> gen_neu_from_W;
  std::vector<int> gen_top_ID;
  std::vector<int> gen_W_from_top_ID;
  std::vector<int> gen_lep_from_W_ID;
  std::vector<int> gen_neu_from_W_ID;
  
  bool good_W_matches = true;
  std::vector<TLorentzVector> gen_top_matched_q;
  std::vector<bool>           gen_top_matched_b;
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
  size_t njet_AK4 = h_floats_["AK4_Pt"]->size();
  size_t njet_AK8 = h_floats_["AK8_Pt"]->size();
  size_t njet_AK8Sub = h_floats_["AK8Sub_Pt"]->size();
  bool useGenParticles = true;

  if (!isData_) {
    // Using GenParticles
    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByLabel(edm::InputTag("prunedGenParticles"),  genParticles);
    const bool print = false;
    if (print) for(size_t i=0; i<genParticles->size(); ++i) {
      const reco::GenParticle& p = (*genParticles)[i];
      int momId = p.numberOfMothers() ? p.mother()->pdgId() : 0;
      std::cout<<i<<" id="<<p.pdgId()<<" ("<<p.status()<<") mom="<<momId<<", daughters=";
      for(size_t j = 0, n=p.numberOfDaughters(); j<n; ++j) std::cout<<p.daughter(j)->pdgId()<<(j+1<n?", ":"\n");
    }
    
    size_t ngen =  h_floats_["gen_Pt"]->size();
    double stop_mass = -9999, gluino_mass = -9999, lsp_mass = -9999;
    for (size_t i=0; i<ngen; ++i) {
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
        vector_int_["gen_Dau1ID"].push_back(h_floats_["gen_Dau1ID"]->at(i));			    /* gen_Dau1ID */
        vector_int_["gen_Dau1Status"].push_back(h_floats_["gen_Dau1Status"]->at(i));		    /* gen_Dau1Status */
        vector_float_["gen_Pt"].push_back(h_floats_["gen_Pt"]->at(i));				    /* gen_Pt */
        vector_float_["gen_Eta"].push_back(h_floats_["gen_Eta"]->at(i));			    /* gen_Eta */
        vector_float_["gen_Phi"].push_back(h_floats_["gen_Phi"]->at(i));			    /* gen_Phi */
        vector_float_["gen_E"].push_back(h_floats_["gen_E"]->at(i));				    /* gen_E */
        vector_float_["gen_Charge"].push_back(h_floats_["gen_Charge"]->at(i));			    /* gen_Charge */
        TLorentzVector genp; genp.SetPtEtaPhiE(h_floats_["gen_Pt"]->at(i), h_floats_["gen_Eta"]->at(i),
					       h_floats_["gen_Phi"]->at(i), h_floats_["gen_E"]->at(i));
	vector_float_["gen_Mass"].push_back(genp.M());				                    /* gen_Mass */
	if (abs(h_floats_["gen_ID"]->at(i))==1000006||abs(h_floats_["gen_ID"]->at(i))==2000006) {
	  // Stop Mass
	  stop_mass = std::round(genp.M());
	} else if (abs(h_floats_["gen_ID"]->at(i))==1000021) {
	  // Gluino Mass is needef for cross-section
	  // round because there's a small precision loss
	  // and also for xsec you need to round anyway
	  gluino_mass = std::round(genp.M()/5)*5;
	} else if (abs(h_floats_["gen_ID"]->at(i))==1000022) {
	  // LSP Mass
	  lsp_mass = std::round(genp.M()/5)*5;
	}
      }
      if (!useGenParticles&&h_floats_["gen_Pt"]->at(i)>0) {
        TLorentzVector genp; genp.SetPtEtaPhiE(h_floats_["gen_Pt"]->at(i), h_floats_["gen_Eta"]->at(i),
          				     h_floats_["gen_Phi"]->at(i), h_floats_["gen_E"]->at(i));
        if (h_floats_["gen_ID"]->at(i)!=h_floats_["gen_Mom0ID"]->at(i)) {
          if (abs(h_floats_["gen_ID"]->at(i))==6) { 
            gen_top.push_back(genp);
            gen_top_index.push_back(i);
            gen_top_ID.push_back(h_floats_["gen_ID"]->at(i));
          }
          if (abs(h_floats_["gen_ID"]->at(i))==5&&abs(h_floats_["gen_Mom0ID"]->at(i))==6) {
	    if (abs(h_floats_["gen_ID"]->at(i))==1) {
	      gen_q_from_top.push_back(genp);
	      gen_b_from_top.push_back(0);
	    } else if (abs(h_floats_["gen_ID"]->at(i))==3) {
	      gen_q_from_top.push_back(genp);
	      gen_b_from_top.push_back(0);
	    } else if (abs(h_floats_["gen_ID"]->at(i))==5) {
	      gen_q_from_top.push_back(genp);
	      gen_b_from_top.push_back(1);
	    }
	  }
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
    
    if (useGenParticles) for(size_t i=0; i<genParticles->size(); ++i) {
      const reco::GenParticle& p = (*genParticles)[i];
      int momId = p.numberOfMothers() ? p.mother()->pdgId() : 0;
      int Id = p.pdgId();
      TLorentzVector p4; p4.SetPtEtaPhiE(p.pt(), p.eta(), p.phi(), p.mass());
      // Exclude radiations
      bool sameDau = 0;
      for (size_t j=0, ndau=p.numberOfDaughters(); j<ndau; ++j) if (p.daughter(j)->pdgId()==Id) sameDau = 1;
      if (!sameDau) {
	if (abs(Id)==6) {
	  gen_top.push_back(p4);
	  gen_top_ID.push_back(Id);
	  //bool bWDecay = false;
	  //if (p.numberOfDaughters()==2)
	  //  if ((abs(p.daughter(0)->pdgId())==24&&abs(p.daughter(1)->pdgId())==5) ||
	  //      (abs(p.daughter(0)->pdgId())==5&&abs(p.daughter(1)->pdgId())==24)) bWDecay = true;
	  //if (!bWDecay) {
	  //  std::cout<<"id="<<p.pdgId()<<" mom="<<momId<<", daughters=";
	  //  for(size_t j = 0, n=p.numberOfDaughters(); j<n; ++j) std::cout<<p.daughter(j)->pdgId()<<(j+1<n?", ":"\n");
	  //}
	  // top daughters
	} else if (abs(momId)==6) {
	  if (abs(Id)==1) {
	    gen_q_from_top.push_back(p4);
	    gen_b_from_top.push_back(0);
	  } else if (abs(Id)==3) {
	    gen_q_from_top.push_back(p4);
	    gen_b_from_top.push_back(0);
	  } else if (abs(Id)==5) {
	    gen_q_from_top.push_back(p4);
	    gen_b_from_top.push_back(1);
	  } else if (abs(Id)==24) {
	    gen_W_from_top.push_back(p4);
	    gen_W_from_top_ID.push_back(Id);
	  }
	  // leptons from W
	} else if ((abs(Id)==11||abs(Id)==13||abs(Id)==15)&&abs(momId)==24) {
	  gen_lep_from_W.push_back(p4);
	  gen_lep_from_W_ID.push_back(Id);
	} else if ((abs(Id)==12||abs(Id)==14||abs(Id)==16)&&abs(momId)==24) {
	  gen_neu_from_W.push_back(p4);
	  gen_neu_from_W_ID.push_back(Id);
	}
      }
    }
    
    // Save SUSY Signal related quantities
    if (lsp_mass != -9999) {
      single_float_["SUSY_Stop_Mass"] = stop_mass;                                                  /* SUSY_Stop_Mass */
      single_float_["SUSY_Gluino_Mass"] = gluino_mass;                                              /* SUSY_Gluino_Mass */
      single_float_["SUSY_LSP_Mass"] = lsp_mass;                                                    /* SUSY_LSP_Mass */
      if (stop_mass != single_float_["prev_stop_mass"])
        single_float_["evt_XSec"] = GetStopXSec(stop_mass).first;                                   /* evt_XSec */
      single_float_["prev_stop_mass"] = stop_mass;
      if (gluino_mass != single_float_["prev_gluino_mass"])
        single_float_["evt_XSec"] = GetGluinoXSec(gluino_mass).first;                               /* evt_XSec */
      single_float_["prev_gluino_mass"] = gluino_mass;
    }
    
    // Find bs and Ws
    // Method: bs and Ws with top parent are combined
    // Best pair with lowest combined mass and DR difference is selected
    for (size_t i=0; i<gen_top.size(); ++i) {
      // Match b and W to t
      size_t j_q = -1, k_W = -1;
      double min_DM = 9999, min_DR = 9999;
      if (gen_q_from_top.size()<gen_top.size()||gen_W_from_top.size()<gen_top.size()) {
        good_W_matches = false;
      } else {
        for (size_t j=0; j<gen_q_from_top.size(); ++j) {
          for (size_t k=0; k<gen_W_from_top.size(); ++k) {
            TLorentzVector bW_comb = gen_q_from_top[j]+gen_W_from_top[k];
            double DR = gen_top[i].DeltaR(bW_comb);
            double DM = fabs(gen_top[i].M()-bW_comb.M());
            if (DR<0.8) {
              if (DM<min_DM) {
                min_DM = DM;
                min_DR = DR;
                j_q = j;
                k_W = k;
              }
            }
          }
        }
        if (min_DR<0.8&&min_DM<1) {
	  gen_top_matched_q.push_back(gen_q_from_top[j_q]);
	  gen_top_matched_b.push_back(gen_b_from_top[j_q]);
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
        for (size_t j=0; j<njet_AK8; ++j) {
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
      } else if (njet_AK8) {
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
  
  // Read jet correction parameters from DB
  edm::ESHandle<JetCorrectorParametersCollection> JetCorrParColl_AK4, JetCorrParColl_AK8;
  iSetup.get<JetCorrectionsRecord>().get(TString(AK4Jets_label_).Contains("Puppi") ? "AK4PFPuppi" : "AK4PFchs", JetCorrParColl_AK4);
  iSetup.get<JetCorrectionsRecord>().get(TString(AK8Jets_label_).Contains("Puppi") ? "AK8PFPuppi" : "AK8PFchs", JetCorrParColl_AK8);

  // JEC Uncertainty
  // NB: JEC/JER variables are already there in the new versions of B2G ntuples
  /*
  JetCorrectionUncertainty jecUnc_AK4((*JetCorrParColl_AK4)["Uncertainty"]);
  JetCorrectionUncertainty jecUnc_AK8((*JetCorrParColl_AK8)["Uncertainty"]);
  
  // JER
  // Twiki: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyResolution#Scale_factors
  // Recipe taken from: https://github.com/blinkseb/cmssw/blob/jer_fix_76x/JetMETCorrections/Modules/plugins/JetResolutionDemo.cc
  JME::JetParameters jetParam;
  JME::JetResolution resolution_AK4 = JME::JetResolution(JER_location_+"_PtResolution_AK4PFchs.txt");
  JME::JetResolution resolution_AK8 = JME::JetResolution(JER_location_+"_PtResolution_AK8PFchs.txt");
  JME::JetResolutionScaleFactor res_sf_AK4 = JME::JetResolutionScaleFactor(JER_location_+"_SF_AK4PFchs.txt");
  JME::JetResolutionScaleFactor res_sf_AK8 = JME::JetResolutionScaleFactor(JER_location_+"_SF_AK8PFchs.txt");
  
  vector_float_[AK4Jets_prefix_+"_jecUncertainty"].assign(njet_AK4,-9999);
  vector_float_[AK4Jets_prefix_+"_PtResolution"].assign(njet_AK4,-9999);
  vector_float_[AK4Jets_prefix_+"_JERSF"].assign(njet_AK4,-9999);
  vector_float_[AK4Jets_prefix_+"_JERSFDown"].assign(njet_AK4,-9999);
  vector_float_[AK4Jets_prefix_+"_JERSFUp"].assign(njet_AK4,-9999);
  for (size_t iJet=0; iJet<njet_AK4; ++iJet) {
    jecUnc_AK4.setJetPt(h_floats_["AK4_Pt"]->at(iJet));
    jecUnc_AK4.setJetEta(h_floats_["AK4_Eta"]->at(iJet));
    jetParam.setJetPt(h_floats_["AK4_Pt"]->at(iJet)).setJetEta(h_floats_["AK4_Eta"]->at(iJet)).setRho(*h_double_["evt_rho"]);
    vector_float_[AK4Jets_prefix_+"_jecUncertainty"][iJet] = jecUnc_AK4.getUncertainty(true);
    vector_float_[AK4Jets_prefix_+"_PtResolution"][iJet] = resolution_AK4.getResolution(jetParam);
    vector_float_[AK4Jets_prefix_+"_JERSF"][iJet]     = res_sf_AK4.getScaleFactor(jetParam);
    vector_float_[AK4Jets_prefix_+"_JERSFDown"][iJet] = res_sf_AK4.getScaleFactor(jetParam, Variation::UP);
    vector_float_[AK4Jets_prefix_+"_JERSFUp"][iJet]   = res_sf_AK4.getScaleFactor(jetParam, Variation::DOWN);
  }
  vector_float_[AK8Jets_prefix_+"_jecUncertainty"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_PtResolution"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_JERSF"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_JERSFDown"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_JERSFUp"].assign(njet_AK8,-9999);
  for (size_t iJet=0; iJet<njet_AK8; ++iJet) {
    jecUnc_AK8.setJetPt(h_floats_["AK8_Pt"]->at(iJet));
    jecUnc_AK8.setJetEta(h_floats_["AK8_Eta"]->at(iJet));
    jetParam.setJetPt(h_floats_["AK8_Pt"]->at(iJet)).setJetEta(h_floats_["AK8_Eta"]->at(iJet)).setRho(*h_double_["evt_rho"]);
    vector_float_[AK8Jets_prefix_+"_jecUncertainty"][iJet] = jecUnc_AK8.getUncertainty(true);
    vector_float_[AK8Jets_prefix_+"_PtResolution"][iJet] = resolution_AK8.getResolution(jetParam);
    vector_float_[AK8Jets_prefix_+"_JERSF"][iJet]     = res_sf_AK8.getScaleFactor(jetParam);
    vector_float_[AK8Jets_prefix_+"_JERSFDown"][iJet] = res_sf_AK8.getScaleFactor(jetParam, Variation::UP);
    vector_float_[AK8Jets_prefix_+"_JERSFUp"][iJet]   = res_sf_AK8.getScaleFactor(jetParam, Variation::DOWN);
  }
  */
  
  // Jet Correctors (Recalculate after lepton cleaning, or do on-the-fly correction)
  std::vector<JetCorrectorParameters> AK4_vPar;
  AK4_vPar.push_back((*JetCorrParColl_AK4)["L1FastJet"]);
  AK4_vPar.push_back((*JetCorrParColl_AK4)["L2Relative"]);
  AK4_vPar.push_back((*JetCorrParColl_AK4)["L3Absolute"]);
  if (isData_) AK4_vPar.push_back((*JetCorrParColl_AK4)["L2L3Residual"]);
  FactorizedJetCorrector AK4_JetCorrector(AK4_vPar);
  std::vector<JetCorrectorParameters> AK8_vPar;
  AK8_vPar.push_back((*JetCorrParColl_AK8)["L1FastJet"]);
  AK8_vPar.push_back((*JetCorrParColl_AK8)["L2Relative"]);
  AK8_vPar.push_back((*JetCorrParColl_AK8)["L3Absolute"]);
  if (isData_) AK8_vPar.push_back((*JetCorrParColl_AK8)["L2L3Residual"]);
  FactorizedJetCorrector AK8_JetCorrector(AK8_vPar);
  
  // GEN infos
  vector_int_[AK8Jets_prefix_+"_HasNearGenTop"].assign(njet_AK8,-9999);
  vector_int_[AK8Jets_prefix_+"_NearGenTopIsHadronic"].assign(njet_AK8,-9999);
  vector_int_[AK8Jets_prefix_+"_NearGenWIsHadronic"].assign(njet_AK8,-9999);
  vector_int_[AK8Jets_prefix_+"_NearGenWToENu"].assign(njet_AK8,-9999);
  vector_int_[AK8Jets_prefix_+"_NearGenWToMuNu"].assign(njet_AK8,-9999);
  vector_int_[AK8Jets_prefix_+"_NearGenWToTauNu"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_DRNearGenTop"].assign(njet_AK8,9999);
  vector_float_[AK8Jets_prefix_+"_DRNearGenWFromTop"].assign(njet_AK8,9999);
  vector_float_[AK8Jets_prefix_+"_DRNearGenBFromTop"].assign(njet_AK8,9999);
  vector_float_[AK8Jets_prefix_+"_DRNearGenLepFromSLTop"].assign(njet_AK8,9999);
  vector_float_[AK8Jets_prefix_+"_DRNearGenNuFromSLTop"].assign(njet_AK8,9999);
  vector_float_[AK8Jets_prefix_+"_PtNearGenTop"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_PtNearGenBFromTop"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_PtNearGenWFromTop"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_PtNearGenLepFromSLTop"].assign(njet_AK8,-9999);
  vector_float_[AK8Jets_prefix_+"_PtNearGenNuFromSLTop"].assign(njet_AK8,-9999);
  
  if (!isData_) for (size_t i=0; i<njet_AK8; ++i) {
    TLorentzVector jet; jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
					 h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
    vector_int_[AK8Jets_prefix_+"_HasNearGenTop"][i]=0;
    // Unsing Gen Particle Info
    if (jet_gentop_index.count(i)) {
      size_t top_index = jet_gentop_index[i];
      vector_int_[AK8Jets_prefix_+"_HasNearGenTop"][i]=1;                                                  /* jetAK8_HasNearGenTop */
      vector_float_[AK8Jets_prefix_+"_PtNearGenTop"][i] = gen_top[top_index].Pt();			      /* jetAK8_PtNearGenTop */
      vector_float_[AK8Jets_prefix_+"_DRNearGenTop"][i] = gen_top[top_index].DeltaR(jet);		      /* jetAK8_DRNearGenTop */
      // If W matching was successful, more information is available
      if (good_W_matches) {
        vector_float_[AK8Jets_prefix_+"_DRNearGenWFromTop"][i] = gen_top_matched_W[top_index].DeltaR(jet); /* jetAK8_DRNearGenWFromTop */
	if (gen_top_matched_b[top_index])
	  vector_float_[AK8Jets_prefix_+"_DRNearGenBFromTop"][i] = gen_top_matched_q[top_index].DeltaR(jet); /* jetAK8_DRNearGenBFromTop */
        vector_float_[AK8Jets_prefix_+"_DRNearGenLepFromSLTop"][i] = 				      /* jetAK8_DRNearGenLepFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_lep[top_index].DeltaR(jet) : -9999;
        vector_float_[AK8Jets_prefix_+"_DRNearGenNuFromSLTop"][i]  = 				      /* jetAK8_DRNearGenNuFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_neu[top_index].DeltaR(jet) : -9999;
        vector_float_[AK8Jets_prefix_+"_PtNearGenWFromTop"][i] = gen_top_matched_W[top_index].Pt();	      /* jetAK8_PtNearGenWFromTop */
	if (gen_top_matched_b[top_index])
	  vector_float_[AK8Jets_prefix_+"_PtNearGenBFromTop"][i] = gen_top_matched_q[top_index].Pt();      /* jetAK8_PtNearGenBFromTop */
        vector_float_[AK8Jets_prefix_+"_PtNearGenLepFromSLTop"][i] = 				      /* jetAK8_PtNearGenLepFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_lep[top_index].Pt() : -9999;
        vector_float_[AK8Jets_prefix_+"_PtNearGenNuFromSLTop"][i]  = 				      /* jetAK8_PtNearGenNuFromSLTop */
	  W_type[top_index] ? gen_top_matched_W_matched_neu[top_index].Pt() : -9999;
	vector_int_[AK8Jets_prefix_+"_NearGenTopIsHadronic"][i] = !W_type[top_index];		      /* jetAK8_NearGenTopIsHadronic */
	vector_int_[AK8Jets_prefix_+"_NearGenWIsHadronic"][i] = !W_type[top_index];			      /* jetAK8_NearGenWIsHadronic */
	vector_int_[AK8Jets_prefix_+"_NearGenWToENu"][i] = W_type[top_index]==1;			      /* jetAK8_NearGenWToENu */
	vector_int_[AK8Jets_prefix_+"_NearGenWToMuNu"][i] = W_type[top_index]==2;			      /* jetAK8_NearGenWToMuNu */
	vector_int_[AK8Jets_prefix_+"_NearGenWToTauNu"][i] = W_type[top_index]==3;			      /* jetAK8_NearGenWToTauNu */
      }
    }
  }
  
  /*
    Jet ID
    https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016?rev=4
        
    For |eta|<=2.7 Apply
    looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || abs(eta)>2.4) && abs(eta)<=2.7
    tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || abs(eta)>2.4) && abs(eta)<=2.7
    tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.90) || abs(eta)>2.4) && abs(eta)<=2.7

    For 2.7<|eta|<= 3.0 Apply
    looseJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2 && abs(eta)>2.7 && abs(eta)<=3.0 )
    tightJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2 && abs(eta)>2.7 && abs(eta)<=3.0 )

    For |eta|> 3.0 Apply
    looseJetID = (NEMF<0.90 && NumNeutralParticle>10 && abs(eta)>3.0 )
    tightJetID = (NEMF<0.90 && NumNeutralParticle>10 && abs(eta)>3.0 ) 
  */
  
  vector_int_[AK4Jets_prefix_+"_looseJetID"].clear();
  vector_int_[AK4Jets_prefix_+"_tightJetID"].clear();
  vector_int_[AK4Jets_prefix_+"_tightLepVetoJetID"].clear();
  for (size_t i=0; i<njet_AK4; ++i) {
    float eta  = h_floats_["AK4_Eta"]->at(i);
    float NHF  = h_floats_["AK4_neutralHadronEnergyFrac"]->at(i);
    float NEMF = h_floats_["AK4_neutralEmEnergyFrac"]->at(i);
    float MUF = h_floats_["AK4_MuonEnergy"]->at(i) / h_floats_["AK4_E"]->at(i);
    float CHF  = h_floats_["AK4_chargedHadronEnergyFrac"]->at(i);
    float CEMF = h_floats_["AK4_chargedEmEnergyFrac"]->at(i);
    int CHM  = h_floats_["AK4_chargedMultiplicity"]->at(i);
    int NumNeutralParticle   = h_floats_["AK4_neutralMultiplicity"]->at(i);
    int NumConst = CHM + NumNeutralParticle;
    bool looseJetID = 0, tightJetID = 0, tightLepVetoJetID = 0;
    if (std::abs(eta)<=2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.90) || std::abs(eta)>2.4);
    } else if (std::abs(eta)>2.7&&std::abs(eta)<=3.0) {
      looseJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
      tightJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
    } else {
      looseJetID = (NEMF<0.90 && NumNeutralParticle>10);
      tightJetID = (NEMF<0.90 && NumNeutralParticle>10);
    }
    vector_int_[AK4Jets_prefix_+"_looseJetID"].push_back(looseJetID);                       /* jetAK4_looseJetID  */
    vector_int_[AK4Jets_prefix_+"_tightJetID"].push_back(tightJetID);                       /* jetAK4_tightJetID  */
    vector_int_[AK4Jets_prefix_+"_tightLepVetoJetID"].push_back(tightLepVetoJetID);         /* jetAK4_tightLepVetoJetID  */
  }
  
  vector_int_[AK8Jets_prefix_+"_looseJetID"].clear();
  vector_int_[AK8Jets_prefix_+"_tightJetID"].clear();
  vector_int_[AK8Jets_prefix_+"_tightLepVetoJetID"].clear();
  vector_float_[AK8Jets_prefix_+"_maxSubjetCSVv2"].clear();
  vector_float_[AK8Jets_prefix_+"_maxSubjetCMVAv2"].clear();
  for (size_t i=0; i<njet_AK8; ++i) {
    float eta  = h_floats_["AK8_Eta"]->at(i);
    float NHF  = h_floats_["AK8_neutralHadronEnergyFrac"]->at(i);
    float NEMF = h_floats_["AK8_neutralEmEnergyFrac"]->at(i);
    float MUF = h_floats_["AK8_MuonEnergy"]->at(i) / h_floats_["AK8_E"]->at(i);
    float CHF  = h_floats_["AK8_chargedHadronEnergyFrac"]->at(i);
    float CEMF = h_floats_["AK8_chargedEmEnergyFrac"]->at(i);
    int CHM  = h_floats_["AK8_chargedMultiplicity"]->at(i);
    int NumNeutralParticle   = h_floats_["AK8_neutralMultiplicity"]->at(i);
    int NumConst = CHM + NumNeutralParticle;
    bool looseJetID = 0, tightJetID = 0, tightLepVetoJetID = 0;
    if (std::abs(eta)<=2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.90) || std::abs(eta)>2.4);
    } else if (std::abs(eta)>2.7&&std::abs(eta)<=3.0) {
      looseJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
      tightJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
    } else {
      looseJetID = (NEMF<0.90 && NumNeutralParticle>10);
      tightJetID = (NEMF<0.90 && NumNeutralParticle>10);
    }
    vector_int_[AK8Jets_prefix_+"_looseJetID"].push_back(looseJetID);                       /* jetAK8_looseJetID  */
    vector_int_[AK8Jets_prefix_+"_tightJetID"].push_back(tightJetID);                       /* jetAK8_tightJetID  */
    vector_int_[AK8Jets_prefix_+"_tightLepVetoJetID"].push_back(tightLepVetoJetID);         /* jetAK8_tightLepVetoJetID  */

    // Subjet btag info
    int i_sj0 = h_floats_["AK8_vSubjetIndex0"]->at(i), i_sj1 = h_floats_["AK8_vSubjetIndex1"]->at(i);
    float maxCSVv2 = -9999, maxCMVAv2 = -9999;
    if (i_sj0 != -1) if (h_floats_["AK8Sub_CSVv2"]->at(i_sj0) > maxCSVv2) maxCSVv2 = h_floats_["AK8Sub_CSVv2"]->at(i_sj0);
    if (i_sj1 != -1) if (h_floats_["AK8Sub_CSVv2"]->at(i_sj1) > maxCSVv2) maxCSVv2 = h_floats_["AK8Sub_CSVv2"]->at(i_sj1);
    if (i_sj0 != -1) if (h_floats_["AK8Sub_CMVAv2"]->at(i_sj0) > maxCMVAv2) maxCMVAv2 = h_floats_["AK8Sub_CMVAv2"]->at(i_sj0);
    if (i_sj1 != -1) if (h_floats_["AK8Sub_CMVAv2"]->at(i_sj1) > maxCMVAv2) maxCMVAv2 = h_floats_["AK8Sub_CMVAv2"]->at(i_sj1);
    vector_float_[AK8Jets_prefix_+"_maxSubjetCSVv2"].push_back(maxCSVv2);
    vector_float_[AK8Jets_prefix_+"_maxSubjetCMVAv2"].push_back(maxCMVAv2);
  }
  
  vector_int_[AK8Subjets_prefix_+"_looseJetID"].clear();
  vector_int_[AK8Subjets_prefix_+"_tightJetID"].clear();
  vector_int_[AK8Subjets_prefix_+"_tightLepVetoJetID"].clear();
  for (size_t i=0; i<njet_AK8Sub; ++i) {
    float eta  = h_floats_["AK8Sub_Eta"]->at(i);
    float NHF  = h_floats_["AK8Sub_neutralHadronEnergyFrac"]->at(i);
    float NEMF = h_floats_["AK8Sub_neutralEmEnergyFrac"]->at(i);
    float MUF = h_floats_["AK8Sub_MuonEnergy"]->at(i) / h_floats_["AK8Sub_E"]->at(i);
    float CHF  = h_floats_["AK8Sub_chargedHadronEnergyFrac"]->at(i);
    float CEMF = h_floats_["AK8Sub_chargedEmEnergyFrac"]->at(i);
    int CHM  = h_floats_["AK8Sub_chargedMultiplicity"]->at(i);
    int NumNeutralParticle   = h_floats_["AK8Sub_neutralMultiplicity"]->at(i);
    int NumConst = CHM + NumNeutralParticle;
    bool looseJetID = 0, tightJetID = 0, tightLepVetoJetID = 0;
    if (std::abs(eta)<=2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || std::abs(eta)>2.4);
      tightLepVetoJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1 && MUF<0.8) && ((std::abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.90) || std::abs(eta)>2.4);
    } else if (std::abs(eta)>2.7&&std::abs(eta)<=3.0) {
      looseJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
      tightJetID = (NHF<0.98 && NEMF>0.01 && NumNeutralParticle>2);
    } else {
      looseJetID = (NEMF<0.90 && NumNeutralParticle>10);
      tightJetID = (NEMF<0.90 && NumNeutralParticle>10);
    }
    vector_int_[AK8Subjets_prefix_+"_looseJetID"].push_back(looseJetID);                       /* subjetAK8_looseJetID  */
    vector_int_[AK8Subjets_prefix_+"_tightJetID"].push_back(tightJetID);                       /* subjetAK8_tightJetID  */
    vector_int_[AK8Subjets_prefix_+"_tightLepVetoJetID"].push_back(tightLepVetoJetID);         /* subjetAK8_tightLepVetoJetID  */
  }

  // Get (un)corrected Puppi softdrop mass and match jets to B2G jet collection
  //edm::Handle<pat::JetCollection> AK8_handle;
  //iEvent.getByLabel(edm::InputTag("slimmedJetsAK8"), AK8_handle);
  //
  //// Match to B2G collection
  //vector_float_[AK8Jets_prefix_+"_softDropMassPuppiUncorr"].clear(); // For W Tagging
  //vector_float_[AK8Jets_prefix_+"_softDropMassPuppiCorr"].clear();   // For top tagging
  //for (size_t i=0; i<njet_AK8; ++i) {
  //  TLorentzVector jet;
  //  jet.SetPtEtaPhiE(h_floats_["AK8_Pt"]->at(i), h_floats_["AK8_Eta"]->at(i),
  //      	     h_floats_["AK8_Phi"]->at(i), h_floats_["AK8_E"]->at(i));
  //  float minDR = 9999;
  //  float softDropMassPuppiUncorr = -9999, softDropMassPuppiCorr = -9999;
  //  for (const pat::Jet& j : *AK8_handle) {
  //    TLorentzVector jet_MINIAOD;
  //    jet_MINIAOD.SetPtEtaPhiE(j.pt(),j.eta(),j.phi(),j.energy());
  //    float DR = jet.DeltaR(jet_MINIAOD);
  //    if (DR<0.8 && DR<minDR) {
  //      minDR = DR;
  //      TLorentzVector puppi_softdrop_uncorr, puppi_softdrop_subjet_uncorr;
  //      TLorentzVector puppi_softdrop_corr, puppi_softdrop_subjet_corr;
  //      auto const & sdSubjetsPuppi = j.subjets("SoftDropPuppi");
  //      for ( auto const & it : sdSubjetsPuppi ) {
  //        puppi_softdrop_subjet_uncorr.SetPtEtaPhiM(it->correctedP4(0).pt(),it->correctedP4(0).eta(),it->correctedP4(0).phi(),it->correctedP4(0).mass());
  //        puppi_softdrop_uncorr+=puppi_softdrop_subjet_uncorr;
  //        puppi_softdrop_subjet_corr.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
  //        puppi_softdrop_corr+=puppi_softdrop_subjet_corr;
  //      }
  //      softDropMassPuppiUncorr = puppi_softdrop_uncorr.M();
  //      softDropMassPuppiCorr   = puppi_softdrop_corr.M();
  //    }
  //  }
  //  vector_float_[AK8Jets_prefix_+"_softDropMassPuppiUncorr"].push_back(softDropMassPuppiUncorr);
  //  vector_float_[AK8Jets_prefix_+"_softDropMassPuppiCorr"]  .push_back(softDropMassPuppiCorr);
  //}


  // ---------------------
  // -        MET        -
  // ---------------------
  
  // Uncertainties
  edm::Handle<pat::METCollection> mets;
  iEvent.getByLabel(edm::InputTag("slimmedMETs"), mets);
  const pat::MET &met = mets->front();
  edm::Handle<pat::METCollection> puppimets;
  iEvent.getByLabel(edm::InputTag("slimmedMETsPuppi"), puppimets);
  const pat::MET &puppimet = puppimets->front();
  
  vector_float_["metsyst_Pt"].clear();
  vector_float_["metsyst_Phi"].clear();
  vector_float_["puppimetsyst_Pt"].clear();
  vector_float_["puppimetsyst_Phi"].clear();
  for (int shift=0; shift<pat::MET::METUncertainty::METUncertaintySize; ++shift)
    if (shift != pat::MET::METUncertainty::NoShift) {
      float met_shiftedPt  = met.shiftedPt ((pat::MET::METUncertainty)shift, pat::MET::METCorrectionLevel::Type1);
      float met_shiftedPhi = met.shiftedPhi((pat::MET::METUncertainty)shift, pat::MET::METCorrectionLevel::Type1);
      float puppimet_shiftedPt  = puppimet.shiftedPt ((pat::MET::METUncertainty)shift, pat::MET::METCorrectionLevel::Type1);
      float puppimet_shiftedPhi = puppimet.shiftedPhi((pat::MET::METUncertainty)shift, pat::MET::METCorrectionLevel::Type1);
      vector_float_["metsyst_Pt"].push_back(met_shiftedPt);
      vector_float_["metsyst_Phi"].push_back(met_shiftedPhi);
      vector_float_["puppimetsyst_Pt"].push_back(puppimet_shiftedPt);
      vector_float_["puppimetsyst_Phi"].push_back(puppimet_shiftedPhi);
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
  
  vector_int_["el_IDVeto_NoIso"].clear();
  vector_int_["el_IDLoose_NoIso"].clear();
  vector_int_["el_IDMedium_NoIso"].clear();
  vector_int_["el_IDTight_NoIso"].clear();
  vector_int_["el_IsoVeto"].clear();
  vector_int_["el_IsoLoose"].clear();
  vector_int_["el_IsoMedium"].clear();
  vector_int_["el_IsoTight"].clear();
  vector_int_["el_IDVeto"].clear();
  vector_int_["el_IDLoose"].clear();
  vector_int_["el_IDMedium"].clear();
  vector_int_["el_IDTight"].clear();
  
  // Loop on leptons
  for (size_t iEle=0; iEle<nele; ++iEle) {
    // ------------------------------------------------------------------------
    //                            Electron IDs
    
    float abs_eta                  = std::abs(h_floats_["ele_SCEta"]->at(iEle));
    //float full5x5_sigmaIetaIeta    = h_floats_["ele_full5x5siee"]->at(iEle);
    //float abs_dEtaInSeed           = std::abs(h_floats_["ele_dEtaInSeed"]->at(iEle));
    //float abs_dPhiIn               = std::abs(h_floats_["ele_dPhiIn"]->at(iEle));		
    //float hOverE                   = h_floats_["ele_HoE"]->at(iEle);                
    //float ooEmooP                  = h_floats_["ele_ooEmooP"]->at(iEle);
    //float expectedMissingInnerHits = h_floats_["ele_missHits"]->at(iEle);
    //float pass_conversion_veto     = (h_floats_["ele_hasMatchedConVeto"]->at(iEle)==0.);
    //
    //bool el_IDVeto_NoIso   = pass_ele_ID_ (0, abs_eta, full5x5_sigmaIetaIeta, abs_dEtaInSeed, abs_dPhiIn, hOverE, ooEmooP, expectedMissingInnerHits, pass_conversion_veto, 0);
    //bool el_IDLoose_NoIso  = pass_ele_ID_ (1, abs_eta, full5x5_sigmaIetaIeta, abs_dEtaInSeed, abs_dPhiIn, hOverE, ooEmooP, expectedMissingInnerHits, pass_conversion_veto, 0);
    //bool el_IDMedium_NoIso = pass_ele_ID_ (2, abs_eta, full5x5_sigmaIetaIeta, abs_dEtaInSeed, abs_dPhiIn, hOverE, ooEmooP, expectedMissingInnerHits, pass_conversion_veto, 0);
    //bool el_IDTight_NoIso  = pass_ele_ID_ (3, abs_eta, full5x5_sigmaIetaIeta, abs_dEtaInSeed, abs_dPhiIn, hOverE, ooEmooP, expectedMissingInnerHits, pass_conversion_veto, 0);
    
    float relIsoWithEA             = h_floats_["ele_Iso03"]->at(iEle);
    
    bool el_IsoVeto   = pass_ele_ISO_(0, abs_eta, relIsoWithEA, 0);
    bool el_IsoLoose  = pass_ele_ISO_(1, abs_eta, relIsoWithEA, 0);
    bool el_IsoMedium = pass_ele_ISO_(2, abs_eta, relIsoWithEA, 0);
    bool el_IsoTight  = pass_ele_ISO_(3, abs_eta, relIsoWithEA, 0);
    
    //bool el_IDVeto    = el_IDVeto_NoIso   && el_IsoVeto;
    //bool el_IDLoose   = el_IDLoose_NoIso  && el_IsoLoose;
    //bool el_IDMedium  = el_IDMedium_NoIso && el_IsoMedium;
    //bool el_IDTight   = el_IDTight_NoIso  && el_IsoTight;
    
    //vector_int_["el_IDVeto_NoIso"]  .push_back(el_IDVeto_NoIso);                            /* el_IDVeto_NoIso   */
    //vector_int_["el_IDLoose_NoIso"] .push_back(el_IDLoose_NoIso);                           /* el_IDLoose_NoIso  */
    //vector_int_["el_IDMedium_NoIso"].push_back(el_IDMedium_NoIso);                          /* el_IDMedium_NoIso */
    //vector_int_["el_IDTight_NoIso"] .push_back(el_IDTight_NoIso);                           /* el_IDTight_NoIso  */
    vector_int_["el_IsoVeto"]  .push_back(el_IsoVeto);                                      /* el_IsoVeto   */
    vector_int_["el_IsoLoose"] .push_back(el_IsoLoose);                                     /* el_IsoLoose  */
    vector_int_["el_IsoMedium"].push_back(el_IsoMedium);                                    /* el_IsoMedium */
    vector_int_["el_IsoTight"] .push_back(el_IsoTight);                                     /* el_IsoTight  */
    //vector_int_["el_IDVeto"]   .push_back(el_IDVeto);                                       /* el_IDVeto    */
    //vector_int_["el_IDLoose"]  .push_back(el_IDLoose);                                      /* el_IDLoose   */
    //vector_int_["el_IDMedium"] .push_back(el_IDMedium);                                     /* el_IDMedium  */
    //vector_int_["el_IDTight"]  .push_back(el_IDTight);                                      /* el_IDTight   */
    
    // Debug: Match with vid
    //bool vidLoosenoiso = h_floats_["ele_vidLoosenoiso"]->at(iEle)==1.0;
    //if (vidLoosenoiso!=el_IDLoose_NoIso) {
    //  std::cout<<"Electron ID mismatch found!"<<std::endl;
    //  std::cout<<"VID: "<<vidLoosenoiso<<" ("<<h_floats_["ele_vidLoosenoiso"]->at(iEle)<<") Cut: "<<el_IDLoose_NoIso<<std::endl;
    //  pass_ele_ID_ (1, abs_eta, full5x5_sigmaIetaIeta, abs_dEtaInSeed, abs_dPhiIn, hOverE, ooEmooP, expectedMissingInnerHits, pass_conversion_veto, 1);
    //}
    
    // ------------------------------------------------------------------------
    //                              GEN INFO
    TLorentzVector ele; ele.SetPtEtaPhiE(h_floats_["ele_Pt"]->at(iEle), h_floats_["ele_Eta"]->at(iEle),
					 h_floats_["ele_Phi"]->at(iEle), h_floats_["ele_E"]->at(iEle));
    if (!isData_) if (ele_genlep_index.count(iEle)) {
      size_t genlep_index = ele_genlep_index[iEle];
      vector_float_["el_DRNearGenEleFromSLTop"][iEle] =                                     /* el_DRNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].DeltaR(ele); 
      vector_float_["el_PtNearGenEleFromSLTop"][iEle] =                                     /* el_PtNearGenEleFromSLTop */
	gen_top_matched_W_matched_lep[genlep_index].Pt();
      vector_float_["el_PtNearGenTop"][iEle] = gen_top[genlep_index].Pt();                  /* el_PtNearGenTop */
    }
    
    // ------------------------------------------------------------------------
    //                       Lepton-Jet Disambiguation
    
    // CMS Top-tag subjets currently not used in B2G ntuples, SoftDrop subjets are available only
    const bool SoftDrop = 1; // 1: use W-like SoftDrop subjets (max 2 subjet) or 0: top-like subjets (2-4)
    const bool print_keys = 0;
    TLorentzVector closest_jet[3], prev_jet[3];
    float closest_jet_Area[3], closest_jet_jecFactor0[3];
    bool closest_jet_R08Cone[3];
    
    for (size_t iJet=0; iJet<njet_AK4; ++iJet) {
      
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
    
    for (size_t iJet=0; iJet<njet_AK8; ++iJet) {
      
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
      // Add rest of the keys
      AK8Keys.insert(AK8Keys.end(), h_keys_["AK8"]->at(iJet).begin(), h_keys_["AK8"]->at(iJet).end());
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
	  std::string prefix = iSubjet==(size_t)-1 ? "AK8_" : SoftDrop ? "AK8Sub_" : "CmsTTSub_";
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
	    std::vector<int> subjet_keys = iSubjet!=(size_t)-1 ? h_keys_[SoftDrop ? "AK8Sub" : "CmsTTSub"]->at(iSubjet) : AK8Keys;
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
	  reco::Particle::LorentzVector rawP4(cleaned1_jet.Px(), cleaned1_jet.Py(), cleaned1_jet.Pz(), cleaned1_jet.E());
	  // Step 3:
	  if (closest_jet_R08Cone[iType]) {
	    AK8_JetCorrector.setJetEta(cleaned1_jet.Eta());
	    AK8_JetCorrector.setJetPt(cleaned1_jet.Perp());
	    AK8_JetCorrector.setJetE(cleaned1_jet.E());
	    AK8_JetCorrector.setJetA(closest_jet_Area[iType]);
	    AK8_JetCorrector.setRho(*h_double_["evt_rho"]);
	    AK8_JetCorrector.setNPV(*h_int_["vtx_npv"]);
	    cleaned1_jet *= AK8_JetCorrector.getCorrection();
  	    } else {
	    AK4_JetCorrector.setJetEta(cleaned1_jet.Eta());
	    AK4_JetCorrector.setJetPt(cleaned1_jet.Perp());
	    AK4_JetCorrector.setJetE(cleaned1_jet.E());
	    AK4_JetCorrector.setJetA(closest_jet_Area[iType]);
	    AK4_JetCorrector.setRho(*h_double_["evt_rho"]);
	    AK4_JetCorrector.setNPV(*h_int_["vtx_npv"]);
	    cleaned1_jet *= AK4_JetCorrector.getCorrection();
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
    // ------------------------------------------------------------------------
    //                       Lepton-Jet Disambiguation
    
    // CMS Top-tag subjets currently not used in B2G ntuples, SoftDrop subjets are available only
    const bool SoftDrop = 1; // 1: use W-like SoftDrop subjets (max 2 subjet) or 0: top-like subjets (2-4)
    const bool print_keys = 0;
    TLorentzVector closest_jet[3], prev_jet[3];
    float closest_jet_Area[3], closest_jet_jecFactor0[3];
    bool closest_jet_R08Cone[3];
    
    for (size_t iJet=0; iJet<njet_AK4; ++iJet) {
      
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
    
    for (size_t iJet=0; iJet<njet_AK8; ++iJet) {
      
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
      // Add rest of the keys
      AK8Keys.insert(AK8Keys.end(), h_keys_["AK8"]->at(iJet).begin(), h_keys_["AK8"]->at(iJet).end());
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
	  std::string prefix = iSubjet==(size_t)-1 ? "AK8_" : SoftDrop ? "AK8Sub_" : "CmsTTSub_";
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
	  reco::Particle::LorentzVector rawP4(cleaned1_jet.Px(), cleaned1_jet.Py(), cleaned1_jet.Pz(), cleaned1_jet.E());
	  // Step 3:
	  if (closest_jet_R08Cone[iType]) {
	    AK8_JetCorrector.setJetEta(cleaned1_jet.Eta());
	    AK8_JetCorrector.setJetPt(cleaned1_jet.Perp());
	    AK8_JetCorrector.setJetE(cleaned1_jet.E());
	    AK8_JetCorrector.setJetA(closest_jet_Area[iType]);
	    AK8_JetCorrector.setRho(*h_double_["evt_rho"]);
	    AK8_JetCorrector.setNPV(*h_int_["vtx_npv"]);
	    cleaned1_jet *= AK8_JetCorrector.getCorrection();
  	    } else {
	    AK4_JetCorrector.setJetEta(cleaned1_jet.Eta());
	    AK4_JetCorrector.setJetPt(cleaned1_jet.Perp());
	    AK4_JetCorrector.setJetE(cleaned1_jet.E());
	    AK4_JetCorrector.setJetA(closest_jet_Area[iType]);
	    AK4_JetCorrector.setRho(*h_double_["evt_rho"]);
	    AK4_JetCorrector.setNPV(*h_int_["vtx_npv"]);
	    cleaned1_jet *= AK4_JetCorrector.getCorrection();
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
  // -- Isolated tracks --
  // ---------------------
  
  edm::Handle<pat::PackedCandidateCollection> packedPFCands;
  iEvent.getByLabel(edm::InputTag("packedPFCandidates"), packedPFCands);
  const pat::PackedCandidateCollection& pfCands = *packedPFCands.product();
  
  single_int_["evt_NIsoTrk"] = 0;
  for (size_t i=0, n=pfCands.size(); i<n; ++i) {
    if (pfCands[i].charge()==0) continue;
    if (pfCands[i].pt()<5) continue;
    if (std::abs(pfCands[i].dz())>=0.1) continue;
    
    // Calculate track isolation
    float iso_trk = 0;
    for (size_t j=0; j<n; ++j) {
      if (j==i) continue;
      if (pfCands[j].charge()==0) continue;
      float dR = reco::deltaR(pfCands[i].eta(), pfCands[i].phi(), pfCands[j].eta(), pfCands[j].phi());
      if (dR >= 0.3) continue;
      if (std::abs(pfCands[j].dz())>=0.1) continue;
      iso_trk += pfCands[j].pt();
    }
    iso_trk /= pfCands[i].pt();
    if (std::abs(pfCands[i].pdgId())==11||std::abs(pfCands[i].pdgId())==13) {
      if (iso_trk<0.2) ++single_int_["evt_NIsoTrk"];
    } else {
      if (iso_trk<0.1 && pfCands[i].pt()>=10) ++single_int_["evt_NIsoTrk"];
    }
  }
  
  // ---------------------
  // -- Razor variables --
  // ---------------------
  
  // Jet selection for jet combiner
  std::vector<TLorentzVector> jets_AK4, jets_AK4_smear;
  for (size_t i=0; i<njet_AK4; ++i) {
    // Cut in MINIAOD: pt>20
    // 2016/10/14: JetID cut added, pt lowered from 40 to 30, |eta| lowered to 2.4
    if (std::abs(h_floats_["AK4_Eta"]->at(i)) < 2.4 && vector_int_[AK4Jets_prefix_+"_looseJetID"][i]) {
      TLorentzVector jl;
      jl.SetPtEtaPhiE(h_floats_["AK4_Pt"]->at(i), h_floats_["AK4_Eta"]->at(i),
                      h_floats_["AK4_Phi"]->at(i), h_floats_["AK4_E"]->at(i));
      float pt = h_floats_["AK4_Pt"]->at(i), smeared_pt = h_floats_["AK4_SmearedPt"]->at(i);
      if (pt >= 30) jets_AK4.push_back(jl);
      // Use also JER Smeared jets in order to propagate the uncertainty
      if (smeared_pt >= 30) jets_AK4_smear.push_back(jl*(smeared_pt/pt));
    }
  }
  
  TVector3 metl;
  metl.SetPtEtaPhi(h_floats_["met_Pt"]->at(0), 0, h_floats_["met_Phi"]->at(0));
  
  // Razor calculation
  single_float_["evt_MR"]  = -9999;
  single_float_["evt_MTR"] = -9999;
  single_float_["evt_R"]   = -9999;
  single_float_["evt_R2"]  = -9999;
  single_float_["evt_MR_Smear"] = -9999;
  single_float_["evt_MTR_Smear"] = -9999;
  if (njet_AK4<60) {
    if (jets_AK4.size() >= 2) {
      std::vector<TLorentzVector> hemis_AK4 = Razor::CombineJets(jets_AK4);
      single_float_["evt_MR"]  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);          /* evt_MR */
      single_float_["evt_MTR"] = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], metl);   /* evt_MTR */
      single_float_["evt_R"]   = single_float_["evt_MTR"] / single_float_["evt_MR"]; /* evt_R */
      single_float_["evt_R2"]  = std::pow(single_float_["evt_R"], 2);                /* evt_R2 */
    }
    // JER Smearing propagated to MR
    if (jets_AK4_smear.size() >= 2) {
      std::vector<TLorentzVector> hemis_AK4 = Razor::CombineJets(jets_AK4_smear);
      single_float_["evt_MR_Smear"]  = Razor::CalcMR(hemis_AK4[0], hemis_AK4[1]);        /* evt_MR_Smear */
      single_float_["evt_MTR_Smear"] = Razor::CalcMTR(hemis_AK4[0], hemis_AK4[1], metl); /* evt_MTR_Smear */
    }
  } else {
    std::cout<<"Too many AK4: "<<jets_AK4.size()<<" "<<njet_AK4<<std::endl;
  }

}

// Electron ID
// https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2?rev=37#Offline_selection_criteria

/*
  80X-tuned selection, barrel cuts ( |eta supercluster| <= 1.479)
  					Veto 	Loose 	Medium 	Tight
  full5x5_sigmaIetaIeta < 		0.0115 	0.011 	0.00998 0.00998
  abs(dEtaInSeed) < 	 		0.00749 0.00477 0.00311 0.00308
  abs(dPhiIn) < 			0.228 	0.222 	0.103 	0.0816
  H/E < 				0.356 	0.298 	0.253 	0.0414
  Rel. comb. PF iso with EA corr < 	0.175 	0.0994 	0.0695 	0.0588
  abs(1/E-1/p) < 			0.299 	0.241 	0.134 	0.0129
  expected missing inner hits <= 	2 	1 	1 	1

  80X-tuned selection, endcap cuts ( |eta supercluster| > 1.479) |
  					Veto 	Loose 	Medium 	Tight
  full5x5_sigmaIetaIeta < 		0.037 	0.0314 	0.0298 	0.0292
  abs(dEtaInSeed) < 			0.00895 0.00868 0.00609	0.00605
  abs(dPhiIn) < 			0.213 	0.213 	0.045 	0.0394
  H/E < 				0.211 	0.101 	0.0878 	0.0641
  Rel. comb. PF iso with EA corr < 	0.159 	0.107 	0.0821 	0.0571
  abs(1/E-1/p) < 			0.15 	0.14 	0.13 	0.0129
  expected missing inner hits <= 	3 	1 	1 	1
*/

bool B2GEdmExtraVarProducer::pass_ele_ID_(int id_index, const float& abs_eta, const float& full5x5_sigmaIetaIeta,
					  const float& abs_dEtaInSeed, const float& abs_dPhiIn, const float& hOverE,
					  const float& ooEmooP, const float& expectedMissingInnerHits,
					  const float& pass_conversion_veto, bool verbose) {
  if (abs_eta>=2.5) return 0;
  float cuts[2][7][4] = 
    {
      { // Barrel
        { 0.0115 , 0.011  , 0.00998, 0.00998 },
        { 0.00749, 0.00477, 0.00311, 0.00308 },
        { 0.228  , 0.222  , 0.103  , 0.0816  },
        { 0.356  , 0.298  , 0.253  , 0.0414  },
        { 0.299  , 0.241  , 0.134  , 0.0129  },
        { 2 	 , 1 	  , 1 	   , 1       },
        { 1      , 1      , 1      , 1       }
      },
      { // Endcap
        { 0.037  , 0.0314 , 0.0298 , 0.0292 },
        { 0.00895, 0.00868, 0.00609, 0.00605},
        { 0.213  , 0.213  , 0.045  , 0.0394 },
        { 0.211  , 0.101  , 0.0878 , 0.0641 },
        { 0.15 	 , 0.14   , 0.13   , 0.0129 },
        { 3 	 , 1 	  , 1 	   , 1      },
        { 1      , 1      , 1      , 1      }
      }
    };

  int endcap = abs_eta>1.479;
  if (verbose) {
    std::cout<<"full5x5_sigmaIetaIeta    "<<full5x5_sigmaIetaIeta   <<", decision: "<<!(full5x5_sigmaIetaIeta    >= cuts[endcap][0][id_index])<<std::endl;
    std::cout<<"abs_dEtaInSeed           "<<abs_dEtaInSeed          <<", decision: "<<!(abs_dEtaInSeed           >= cuts[endcap][1][id_index])<<std::endl;
    std::cout<<"abs_dPhiIn               "<<abs_dPhiIn              <<", decision: "<<!(abs_dPhiIn               >= cuts[endcap][2][id_index])<<std::endl;
    std::cout<<"hOverE                   "<<hOverE                  <<", decision: "<<!(hOverE                   >= cuts[endcap][3][id_index])<<std::endl;
    std::cout<<"ooEmooP                  "<<ooEmooP                 <<", decision: "<<!(ooEmooP                  >= cuts[endcap][4][id_index])<<std::endl;
    std::cout<<"expectedMissingInnerHits "<<expectedMissingInnerHits<<", decision: "<<!(expectedMissingInnerHits >  cuts[endcap][5][id_index])<<std::endl;
    std::cout<<"pass_conversion_veto     "<<pass_conversion_veto    <<", decision: "<<!(pass_conversion_veto     != cuts[endcap][6][id_index])<<std::endl;
  }
  if (full5x5_sigmaIetaIeta    >= cuts[endcap][0][id_index]) return 0;
  if (abs_dEtaInSeed           >= cuts[endcap][1][id_index]) return 0;
  if (abs_dPhiIn               >= cuts[endcap][2][id_index]) return 0;
  if (hOverE                   >= cuts[endcap][3][id_index]) return 0;
  if (ooEmooP                  >= cuts[endcap][4][id_index]) return 0;
  if (expectedMissingInnerHits >  cuts[endcap][5][id_index]) return 0;
  if (pass_conversion_veto     != cuts[endcap][6][id_index]) return 0;
  return 1;
}

bool B2GEdmExtraVarProducer::pass_ele_ISO_(int id_index, const float& abs_eta, const float& relIsoWithEA, bool verbose) {
  if (abs_eta>=2.5) return 0;

  float cuts[2][4] = 
    {
      { 0.175  , 0.0994 , 0.0695 , 0.0588  },
      { 0.159  , 0.107  , 0.0821 , 0.0571 },
    };
  int endcap = abs_eta>1.479;
  if (verbose)
    std::cout<<"relIsoWithEA             "<<relIsoWithEA             <<", decision: "<<!(relIsoWithEA             >= cuts[endcap][id_index])<<std::endl;
  if (relIsoWithEA             >= cuts[endcap][id_index]) return 0;
  return 1;
}

// checks if a particle has a special mother. Treats anti-particles as particles
bool B2GEdmExtraVarProducer::hasAncestor_(int index, const lhef::HEPEUP& info, int searchId) {
   if (index < 2 || index > info.NUP) return false;
   else if (std::abs(info.IDUP[index]) == searchId) return true;
   else {
     auto mothers = info.MOTHUP[index];
     return
       (index != mothers.first-1 && hasAncestor_(mothers.first-1, info, searchId)) ||
       (index != mothers.second-1 && hasAncestor_(mothers.second-1, info, searchId));
   }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GEdmExtraVarProducer);
