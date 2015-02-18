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
  std::string electrons_label_;
  std::string electrons_prefix_;
  std::string muons_label_;
  std::string muons_prefix_;
  std::string met_label_;
  std::string met_prefix_;
  std::string AK8Jets_label_;
  std::string AK8Jets_prefix_;
  std::map<std::string, edm::Handle<std::vector<float> > > h_floats_;
  // Output
  std::vector<std::string> singleF_;
  std::vector<std::string> singleI_;
  std::map<std::string, float> single_float_;
  std::map<std::string, int> single_int_;

};


B2GEdmExtraVarProducer::B2GEdmExtraVarProducer(const edm::ParameterSet& iConfig) :
  electrons_label_(iConfig.getParameter<std::string>("electrons_label")),
  electrons_prefix_(iConfig.getParameter<std::string>("electrons_prefix")),
  muons_label_(iConfig.getParameter<std::string>("muons_label")),
  muons_prefix_(iConfig.getParameter<std::string>("muons_prefix")),
  met_label_(iConfig.getParameter<std::string>("met_label")),
  met_prefix_(iConfig.getParameter<std::string>("met_prefix")),
  AK8Jets_label_(iConfig.getParameter<std::string>("AK8Jets_label")),
  AK8Jets_prefix_(iConfig.getParameter<std::string>("AK8Jets_prefix")),
  singleF_(iConfig.getUntrackedParameter<std::vector<std::string> >("singleF")),
  singleI_(iConfig.getUntrackedParameter<std::vector<std::string> >("singleI"))
{
  for ( auto nameF : singleF_ ) produces<float>(nameF);
  for ( auto nameI : singleI_ ) produces<int>(nameI);
}

void B2GEdmExtraVarProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  // Initialize containers for each variable
  for ( auto nameF : singleF_ ) single_float_[nameF] = -9999.0;
  for ( auto nameI : singleI_ ) single_int_[nameI] = -9999;
  
  calculate_variables(iEvent, iSetup);
  
  // Put new variables to the event
  for ( auto nameF : singleF_ ) {
    std::auto_ptr<float> newF(new float);
    *newF = single_float_[nameF];
    iEvent.put(newF,nameF);
  }
  for ( auto nameI : singleI_ ) {
    std::auto_ptr<int> newI(new int);
    *newI = single_int_[nameI];
    iEvent.put(newI,nameI);
  }
}
