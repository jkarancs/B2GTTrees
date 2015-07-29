#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Math/interface/LorentzVector.h"

class  B2GEdmExtraVarProducer : public edm::EDProducer {
public:
  B2GEdmExtraVarProducer( const edm::ParameterSet & );
  
private:
  void produce(edm::Event&, const edm::EventSetup& );
  void calculate_variables(const edm::Event&, const edm::EventSetup&);
  
  // Input
  std::string gen_label_;
  std::string gen_prefix_;
  std::string electrons_label_;
  std::string electrons_prefix_;
  std::string muons_label_;
  std::string muons_prefix_;
  std::string met_label_;
  std::string met_prefix_;
  std::string AK4Jets_label_;
  std::string AK4Jets_prefix_;
  std::string AK8Jets_label_;
  std::string AK8Jets_prefix_;
  std::string AK8Subjets_label_;
  std::string AK8Subjets_prefix_;
  std::string CmsTTSubjets_label_;
  std::string CmsTTSubjets_prefix_;
  std::string AK8JetKeys_label_;
  std::string AK8SubjetKeys_label_;
  std::string CmsTTSubjetKeys_label_;
  double event_weight_;
  std::map<std::string, edm::Handle<std::vector<int> > > h_ints_;
  std::map<std::string, edm::Handle<std::vector<float> > > h_floats_;
  std::map<std::string, edm::Handle<std::vector<std::vector<int> > > > h_keys_;
  std::map<std::string, edm::Handle<std::vector<std::string> > > h_strings_;
  // Output
  std::vector<std::string> singleF_;
  std::vector<std::string> singleI_;
  std::vector<std::string> vectorF_;
  std::vector<std::string> vectorI_;
  std::map<std::string, float> single_float_;
  std::map<std::string, int> single_int_;
  std::map<std::string, std::vector<float> > vector_float_;
  std::map<std::string, std::vector<int> > vector_int_;
  std::vector<std::string> trigger_names_;
  std::map<std::string, size_t > triggers_;
  bool first_event_;
};


B2GEdmExtraVarProducer::B2GEdmExtraVarProducer(const edm::ParameterSet& iConfig) :
  gen_label_(iConfig.getUntrackedParameter<std::string>("gen_label")),
  gen_prefix_(iConfig.getUntrackedParameter<std::string>("gen_prefix")),
  electrons_label_(iConfig.getUntrackedParameter<std::string>("electrons_label")),
  electrons_prefix_(iConfig.getUntrackedParameter<std::string>("electrons_prefix")),
  muons_label_(iConfig.getUntrackedParameter<std::string>("muons_label")),
  muons_prefix_(iConfig.getUntrackedParameter<std::string>("muons_prefix")),
  met_label_(iConfig.getUntrackedParameter<std::string>("met_label")),
  met_prefix_(iConfig.getUntrackedParameter<std::string>("met_prefix")),
  AK4Jets_label_(iConfig.getUntrackedParameter<std::string>("AK4Jets_label")),
  AK4Jets_prefix_(iConfig.getUntrackedParameter<std::string>("AK4Jets_prefix")),
  AK8Jets_label_(iConfig.getUntrackedParameter<std::string>("AK8Jets_label")),
  AK8Jets_prefix_(iConfig.getUntrackedParameter<std::string>("AK8Jets_prefix")),
  AK8Subjets_label_(iConfig.getUntrackedParameter<std::string>("AK8Subjets_label")),
  AK8Subjets_prefix_(iConfig.getUntrackedParameter<std::string>("AK8Subjets_prefix")),
  CmsTTSubjets_label_(iConfig.getUntrackedParameter<std::string>("CmsTTSubjets_label")),
  CmsTTSubjets_prefix_(iConfig.getUntrackedParameter<std::string>("CmsTTSubjets_prefix")),
  AK8JetKeys_label_(iConfig.getUntrackedParameter<std::string>("AK8JetKeys_label")),
  AK8SubjetKeys_label_(iConfig.getUntrackedParameter<std::string>("AK8SubjetKeys_label")),
  CmsTTSubjetKeys_label_(iConfig.getUntrackedParameter<std::string>("CmsTTSubjetKeys_label")),
  event_weight_(iConfig.getUntrackedParameter<double>("event_weight",1)),
  singleF_(iConfig.getUntrackedParameter<std::vector<std::string> >("singleF")),
  singleI_(iConfig.getUntrackedParameter<std::vector<std::string> >("singleI")),
  vectorF_(iConfig.getUntrackedParameter<std::vector<std::string> >("vectorF")),
  vectorI_(iConfig.getUntrackedParameter<std::vector<std::string> >("vectorI"))
{
  for ( auto nameF : singleF_ ) {
    size_t f; while ((f=nameF.find("_"))!=std::string::npos) nameF.erase(f,1); // Remove "_" from var name
    produces<float>(nameF);
  }
  for ( auto nameI : singleI_ ) {
    if (nameI.find("HLT_")==0) trigger_names_.push_back(nameI);
    size_t f; while ((f=nameI.find("_"))!=std::string::npos) nameI.erase(f,1); // Remove "_" from var name
    produces<int>(nameI);
  }
  for ( auto nameVF : vectorF_ ) {
    size_t f; while ((f=nameVF.find("_"))!=std::string::npos) nameVF.erase(f,1); // Remove "_" from var name
    produces<std::vector<float> >(nameVF);
  }
  for ( auto nameVI : vectorI_ ) {
    size_t f; while ((f=nameVI.find("_"))!=std::string::npos) nameVI.erase(f,1); // Remove "_" from var name
    produces<std::vector<int> >(nameVI);
  }
  first_event_=1;
}

void B2GEdmExtraVarProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Initialize containers for each variable
  for ( auto nameF : singleF_ ) single_float_[nameF] = -9999.0;
  for ( auto nameI : singleI_ ) single_int_[nameI] = -9999;
  /* size of vectors are not known, therefor they have to be initialized in calculate_varibles() */
  
  calculate_variables(iEvent, iSetup);
  
  // Put new variables to the event
  for ( auto nameF : singleF_ ) {
    std::auto_ptr<float> newF(new float);
    *newF = single_float_[nameF];
    size_t f; while ((f=nameF.find("_"))!=std::string::npos) nameF.erase(f,1); // Remove "_" from var name
    iEvent.put(newF,nameF);
  }
  for ( auto nameI : singleI_ ) {
    std::auto_ptr<int> newI(new int);
    *newI = single_int_[nameI];
    size_t f; while ((f=nameI.find("_"))!=std::string::npos) nameI.erase(f,1); // Remove "_" from var name
    iEvent.put(newI,nameI);
  }
  for ( auto nameVF : vectorF_ ) {
    std::auto_ptr<std::vector<float> > newVF(new std::vector<float>);
    *newVF = vector_float_[nameVF];
    size_t f; while ((f=nameVF.find("_"))!=std::string::npos) nameVF.erase(f,1); // Remove "_" from var name
    iEvent.put(newVF,nameVF);
  }
  for ( auto nameVI : vectorI_ ) {
    std::auto_ptr<std::vector<int> > newVI(new std::vector<int>);
    *newVI = vector_int_[nameVI];
    size_t f; while ((f=nameVI.find("_"))!=std::string::npos) nameVI.erase(f,1); // Remove "_" from var name
    iEvent.put(newVI,nameVI);
  }
}
