#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "TTree.h"

using namespace edm;

class  B2GTTreeMaker : public edm::EDAnalyzer {
public:
  explicit B2GTTreeMaker( const edm::ParameterSet & );   

private:
  virtual void analyze(const edm::Event &, const edm::EventSetup & );
  
  std::vector<edm::ParameterSet > physObjects;
  std::vector<std::string > variablesFloat, variablesInt, singleFloat, singleInt;
  
  TTree* tree;
  
  std::map<std::string, int > max_instances; 
  std::map<std::string, int > sizes;
  std::map<std::string, float[250] > vfloats_values;
  std::map<std::string, int[250] > vints_values;
  std::map<std::string, float > float_values;
  std::map<std::string, int > int_values;
  
  std::map<std::string, edm::Handle<std::vector<float> > > h_floats;
  std::map<std::string, edm::Handle<std::vector<int> > > h_ints;
  std::map<std::string, edm::Handle<float> > h_float;
  std::map<std::string, edm::Handle<int> >h_int;
  
};

B2GTTreeMaker::B2GTTreeMaker(const edm::ParameterSet& iConfig) {
  
  Service<TFileService> fs;
  
  tree = new TTree("B2GTree", "B2G TTree Ntuple");
  
  physObjects = iConfig.template getParameter<std::vector<edm::ParameterSet> >("physicsObjects");
  std::vector<edm::ParameterSet >::const_iterator itPsets = physObjects.begin();
  
  for (;itPsets!=physObjects.end();++itPsets) { 

    std::string label = itPsets->getParameter<std::string >("label");
    std::string prefix_out = itPsets->getParameter<std::string >("prefix_out");
    variablesFloat = itPsets->template getParameter<std::vector<std::string > >("variablesF"); 
    variablesInt = itPsets->template getParameter<std::vector<std::string > >("variablesI"); 
    singleFloat = itPsets->template getParameter<std::vector<std::string > >("singleF"); 
    singleInt = itPsets->template getParameter<std::vector<std::string > >("singleI"); 
    int maxI = itPsets->getUntrackedParameter<int >("maxInstances",10);
    std::stringstream max_instance_str;
    max_instance_str<<maxI;
    max_instances[label]=maxI;
    
    if (variablesFloat.size() || variablesInt.size())
      tree->Branch((prefix_out+"size").c_str(), &sizes[label]);
    
    for (size_t i=0; i<variablesFloat.size(); ++i) {
      std::string varname_out = prefix_out + variablesFloat[i].c_str();
      tree->Branch(varname_out.c_str(), &vfloats_values[variablesFloat[i]+"_"+label],(varname_out+"["+max_instance_str.str()+"]/F").c_str());
    }
    
    for (size_t i=0; i<variablesInt.size(); ++i) {
      std::string varname_out = prefix_out + variablesInt[i].c_str();
      tree->Branch(varname_out.c_str(), &vints_values[variablesInt[i]+"_"+label],(varname_out+"["+max_instance_str.str()+"]/I").c_str());
    }
    
    //Initialize single pset objects
    for (size_t i=0; i<singleFloat.size(); ++i) {
      std::string varname_out = prefix_out + singleFloat[i].c_str();
      tree->Branch(varname_out.c_str(), &float_values[singleFloat[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleInt.size(); ++i) {
      std::string varname_out = prefix_out + singleInt[i].c_str();
      tree->Branch(varname_out.c_str(), &int_values[singleInt[i]+"_"+label]);
    }
  }
}

void B2GTTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
  std::vector<edm::ParameterSet >::const_iterator itPsets = physObjects.begin();
  
  //Part 1 taking the obs values from the edm file
  for (;itPsets!=physObjects.end();++itPsets) { 
    std::string label = itPsets->getParameter< std::string >("label");
    std::string prefix_in = itPsets->getParameter<std::string >("prefix_in");
    variablesFloat = itPsets->template getParameter<std::vector<std::string > >("variablesF"); 
    variablesInt = itPsets->template getParameter<std::vector<std::string > >("variablesI"); 
    singleFloat = itPsets->template getParameter<std::vector<std::string > >("singleF"); 
    singleInt = itPsets->template getParameter<std::vector<std::string > >("singleI"); 
    std::vector<std::string >::const_iterator itF = variablesFloat.begin();
    std::vector<std::string >::const_iterator itI = variablesInt.begin();
    std::vector<std::string >::const_iterator itsF = singleFloat.begin();
    std::vector<std::string >::const_iterator itsI = singleInt.begin();
    size_t maxInstance=(size_t)max_instances[label];
    
    //Vectors of floats
    for (size_t i=0; i<variablesFloat.size(); ++i) {
      std::string varname_in=prefix_in+variablesFloat[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_floats[varname_in]);
      for (size_t fi = 0;fi < maxInstance; ++fi) 
	vfloats_values[variablesFloat[i]+"_"+label][fi] = (fi <h_floats[varname_in]->size()) ? h_floats[varname_in]->at(fi) : -9999.;
      sizes[label]=h_floats[varname_in]->size();
    }
    
    //Vectors of ints
    for (size_t i=0; i<variablesInt.size(); ++i) {
      std::string varname_in=prefix_in+variablesInt[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_ints[varname_in]);
      for (size_t fi = 0;fi < maxInstance; ++fi)
	vints_values[variablesInt[i]+"_"+label][fi] = (fi <h_ints[varname_in]->size()) ? h_ints[varname_in]->at(fi) : -9999;
      sizes[label]=h_floats[varname_in]->size();
    }  
    
    //Single floats
    for (size_t i=0; i<singleFloat.size(); ++i) {
      std::string varname_in=prefix_in+singleFloat[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_float[varname_in]);
      float_values[singleFloat[i]+"_"+label]=*h_float[varname_in];
    }
    
    //Single ints
    for (size_t i=0; i<singleInt.size(); ++i) {
      std::string varname_in=prefix_in+singleInt[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_int[varname_in]);
      int_values[singleInt[i]+"_"+label]=*h_int[varname_in];
    }
  }
  
  tree->Fill(); 
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GTTreeMaker);
