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
  std::vector<std::string > vectorFloat, vectorInt, singleDouble, singleFloat, singleInt, singleUInt, singleULLong;
  
  TTree* tree;
  
  std::map<std::string, size_t > sizes;
  std::map<std::string, float[500] > vfloats_values;
  std::map<std::string, int[500] > vints_values;
  std::map<std::string, double > double_values;
  std::map<std::string, float > float_values;
  std::map<std::string, int > int_values;
  std::map<std::string, unsigned int > uint_values;
  std::map<std::string, unsigned long long > ullong_values;
  
  std::map<std::string, edm::Handle<std::vector<float> > > h_floats;
  std::map<std::string, edm::Handle<std::vector<int> > > h_ints;
  std::map<std::string, edm::Handle<double> > h_double;
  std::map<std::string, edm::Handle<float> > h_float;
  std::map<std::string, edm::Handle<int> >h_int;
  std::map<std::string, edm::Handle<unsigned int> >h_uint;
  std::map<std::string, edm::Handle<unsigned long long> >h_ullong;
};

B2GTTreeMaker::B2GTTreeMaker(const edm::ParameterSet& iConfig) {
  Service<TFileService> fs;
  tree = fs->make<TTree>("B2GTree", "B2G TTree Ntuple");
  
  physObjects = iConfig.getParameter<std::vector<edm::ParameterSet> >("physicsObjects");
  for (auto pset : physObjects) { 
    std::string label = pset.getUntrackedParameter<std::string >("label");
    std::string prefix_out = pset.getUntrackedParameter<std::string >("prefix_out");
    vectorFloat = pset.getUntrackedParameter<std::vector<std::string > >("vectorF", std::vector<std::string >()); 
    vectorInt = pset.getUntrackedParameter<std::vector<std::string > >("vectorI", std::vector<std::string >()); 
    singleDouble = pset.getUntrackedParameter<std::vector<std::string > >("singleD", std::vector<std::string >()); 
    singleFloat = pset.getUntrackedParameter<std::vector<std::string > >("singleF", std::vector<std::string >()); 
    singleInt = pset.getUntrackedParameter<std::vector<std::string > >("singleI", std::vector<std::string >());
    singleUInt = pset.getUntrackedParameter<std::vector<std::string > >("singleUI", std::vector<std::string >());
    singleULLong = pset.getUntrackedParameter<std::vector<std::string > >("singleULL", std::vector<std::string >());
    
    std::stringstream obj_size;
    obj_size<<prefix_out<<"size";
    if (vectorFloat.size() || vectorInt.size())
      tree->Branch(obj_size.str().c_str(), &sizes[label], (obj_size.str()+"/i").c_str());
    
    for (size_t i=0; i<vectorFloat.size(); ++i) {
      std::string varname_out = prefix_out + vectorFloat[i].c_str();
      tree->Branch(varname_out.c_str(), &vfloats_values[vectorFloat[i]+"_"+label],(varname_out+"["+obj_size.str()+"]/F").c_str());
    }
    
    for (size_t i=0; i<vectorInt.size(); ++i) {
      std::string varname_out = prefix_out + vectorInt[i].c_str();
      tree->Branch(varname_out.c_str(), &vints_values[vectorInt[i]+"_"+label],(varname_out+"["+obj_size.str()+"]/I").c_str());
    }
    
    //Initialize single pset objects
    for (size_t i=0; i<singleDouble.size(); ++i) {
      std::string varname_out = prefix_out + singleDouble[i].c_str();
      tree->Branch(varname_out.c_str(), &double_values[singleDouble[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleFloat.size(); ++i) {
      std::string varname_out = prefix_out + singleFloat[i].c_str();
      tree->Branch(varname_out.c_str(), &float_values[singleFloat[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleInt.size(); ++i) {
      std::string varname_out = prefix_out + singleInt[i].c_str();
      tree->Branch(varname_out.c_str(), &int_values[singleInt[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleUInt.size(); ++i) {
      std::string varname_out = prefix_out + singleUInt[i].c_str();
      tree->Branch(varname_out.c_str(), &uint_values[singleUInt[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleULLong.size(); ++i) {
      std::string varname_out = prefix_out + singleULLong[i].c_str();
      tree->Branch(varname_out.c_str(), &ullong_values[singleULLong[i]+"_"+label]);
    }
  }
}

void B2GTTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  for (auto pset : physObjects) { 
    std::string label = pset.getUntrackedParameter< std::string >("label");
    std::string prefix_in = pset.getUntrackedParameter<std::string >("prefix_in");
    vectorFloat = pset.getUntrackedParameter<std::vector<std::string > >("vectorF", std::vector<std::string >()); 
    vectorInt = pset.getUntrackedParameter<std::vector<std::string > >("vectorI", std::vector<std::string >()); 
    singleDouble = pset.getUntrackedParameter<std::vector<std::string > >("singleD", std::vector<std::string >()); 
    singleFloat = pset.getUntrackedParameter<std::vector<std::string > >("singleF", std::vector<std::string >()); 
    singleInt = pset.getUntrackedParameter<std::vector<std::string > >("singleI", std::vector<std::string >()); 
    singleUInt = pset.getUntrackedParameter<std::vector<std::string > >("singleUI", std::vector<std::string >()); 
    singleULLong = pset.getUntrackedParameter<std::vector<std::string > >("singleULL", std::vector<std::string >()); 
    
    //Vectors of floats
    for (size_t i=0; i<vectorFloat.size(); ++i) {
      std::string varname_in=prefix_in+vectorFloat[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_floats[varname_in]);
      sizes[label]=h_floats[varname_in]->size();
      for (size_t j=0; j<sizes[label]; ++j) 
	vfloats_values[vectorFloat[i]+"_"+label][j] = h_floats[varname_in]->at(j);
    }
    
    //Vectors of ints
    for (size_t i=0; i<vectorInt.size(); ++i) {
      std::string varname_in=prefix_in+vectorInt[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_ints[varname_in]);
      sizes[label]=h_ints[varname_in]->size();
      for (size_t j=0; j<sizes[label]; ++j)
	vints_values[vectorInt[i]+"_"+label][j] = h_ints[varname_in]->at(j);
    }
    
    //Single doubles
    for (size_t i=0; i<singleDouble.size(); ++i) {
      std::string varname_in=prefix_in+singleDouble[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_double[varname_in]);
      double_values[singleDouble[i]+"_"+label]=*h_double[varname_in];
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
      std::string varname_in_nodash = varname_in; // Remove "_" from HLT paths
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_int[varname_in]);
      int_values[singleInt[i]+"_"+label]=*h_int[varname_in];
    }
    
    //Single unsigned ints
    for (size_t i=0; i<singleUInt.size(); ++i) {
      std::string varname_in=prefix_in+singleUInt[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_uint[varname_in]);
      uint_values[singleUInt[i]+"_"+label]=*h_uint[varname_in];
    }

    //Single unsigned longs
    for (size_t i=0; i<singleULLong.size(); ++i) {
      std::string varname_in=prefix_in+singleULLong[i];
      edm::InputTag tag(label, varname_in);
      iEvent.getByLabel(tag, h_ullong[varname_in]);
      ullong_values[singleULLong[i]+"_"+label]=*h_ullong[varname_in];
    }
  }
  
  tree->Fill(); 
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GTTreeMaker);
