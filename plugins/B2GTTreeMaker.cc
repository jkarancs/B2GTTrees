#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "TTree.h"
#include <iostream>

// Set to 1 to use arrays instead of vectors (smaller size)
#define USE_ARRAYS 1

using namespace edm;

class  B2GTTreeMaker : public edm::EDAnalyzer {
public:
  explicit B2GTTreeMaker( const edm::ParameterSet & );   

private:
  virtual void analyze(const edm::Event &, const edm::EventSetup & );
  
  bool isData;
  std::vector<edm::ParameterSet > physObjects;
  std::vector<std::string > singleBool, singleInt, singleUInt, singleULong, singleULLong, singleFloat, singleDouble, vectorInt, vectorFloat;
  
  TTree* tree;
  
  std::map<std::string, int > int_values;
  std::map<std::string, unsigned int > uint_values;
  std::map<std::string, unsigned long > ulong_values;
  std::map<std::string, unsigned long long > ullong_values;
  std::map<std::string, float > float_values;
  std::map<std::string, double > double_values;
  std::map<std::string, size_t > sizes;
#if USE_ARRAYS
  std::map<std::string, int[500] > vints_values;
  std::map<std::string, float[500] > vfloats_values;
#else
  std::map<std::string, std::vector<int> > vints_values;
  std::map<std::string, std::vector<float> > vfloats_values;
#endif
  std::map<std::string, std::vector<std::vector<int> > > keys;
  
  std::map<std::string, edm::Handle<bool> >h_bool;
  std::map<std::string, edm::Handle<int> >h_int;
  std::map<std::string, edm::Handle<unsigned int> >h_uint;
  std::map<std::string, edm::Handle<unsigned long> >h_ulong;
  std::map<std::string, edm::Handle<unsigned long long> >h_ullong;
  std::map<std::string, edm::Handle<float> > h_float;
  std::map<std::string, edm::Handle<double> > h_double;
  std::map<std::string, edm::Handle<std::vector<int> > > h_ints;
  std::map<std::string, edm::Handle<std::vector<float> > > h_floats;
  std::map<std::string, edm::Handle<std::vector<std::vector<int> > > > h_keys;
};

B2GTTreeMaker::B2GTTreeMaker(const edm::ParameterSet& iConfig) {
  Service<TFileService> fs;
  tree = fs->make<TTree>("B2GTree", "B2G TTree Ntuple");
  
  isData = iConfig.getUntrackedParameter<bool>("isData", false);
  physObjects = iConfig.getParameter<std::vector<edm::ParameterSet> >("physicsObjects");
  for (auto pset : physObjects) if (!(isData && pset.getUntrackedParameter<bool>("mc_only", false))) {
    std::string label = pset.getUntrackedParameter<std::string >("label");
    std::string prefix_out = pset.getUntrackedParameter<std::string >("prefix_out");
    singleBool = pset.getUntrackedParameter<std::vector<std::string > >("singleB", std::vector<std::string >());
    singleInt = pset.getUntrackedParameter<std::vector<std::string > >("singleI", std::vector<std::string >());
    singleUInt = pset.getUntrackedParameter<std::vector<std::string > >("singleUI", std::vector<std::string >());
    singleULong = pset.getUntrackedParameter<std::vector<std::string > >("singleUL", std::vector<std::string >());
    singleULLong = pset.getUntrackedParameter<std::vector<std::string > >("singleULL", std::vector<std::string >());
    singleFloat = pset.getUntrackedParameter<std::vector<std::string > >("singleF", std::vector<std::string >());
    singleDouble = pset.getUntrackedParameter<std::vector<std::string > >("singleD", std::vector<std::string >());
    vectorInt = pset.getUntrackedParameter<std::vector<std::string > >("vectorI", std::vector<std::string >());
    vectorFloat = pset.getUntrackedParameter<std::vector<std::string > >("vectorF", std::vector<std::string >());
    std::string key_label = pset.getUntrackedParameter<std::string >("key_label", "");
    
    // Initialize single pset objects
    for (size_t i=0; i<singleBool.size(); ++i) {
      std::string varname_out = prefix_out + singleBool[i];
      tree->Branch(varname_out.c_str(), &int_values[singleBool[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleInt.size(); ++i) {
      std::string varname_out = prefix_out + singleInt[i];
      tree->Branch(varname_out.c_str(), &int_values[singleInt[i]+"_"+label]);
      if (singleInt[i].find("HLT_")==0) {
	varname_out += "_prescale";
	tree->Branch(varname_out.c_str(), &int_values[singleInt[i]+"_prescale_"+label]);
      }
    }
    
    for (size_t i=0; i<singleUInt.size(); ++i) {
      std::string varname_out = prefix_out + singleUInt[i];
      tree->Branch(varname_out.c_str(), &uint_values[singleUInt[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleULong.size(); ++i) {
      std::string varname_out = prefix_out + singleULong[i];
      tree->Branch(varname_out.c_str(), &ulong_values[singleULong[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleULLong.size(); ++i) {
      std::string varname_out = prefix_out + singleULLong[i];
      tree->Branch(varname_out.c_str(), &ullong_values[singleULLong[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleFloat.size(); ++i) {
      std::string varname_out = prefix_out + singleFloat[i];
      tree->Branch(varname_out.c_str(), &float_values[singleFloat[i]+"_"+label]);
    }
    
    for (size_t i=0; i<singleDouble.size(); ++i) {
      std::string varname_out = prefix_out + singleDouble[i];
      tree->Branch(varname_out.c_str(), &double_values[singleDouble[i]+"_"+label]);
    }
    
    // Adding vector variables
    std::string size_var;
    if (prefix_out!=""&&(vectorInt.size() || vectorFloat.size())) {
      std::stringstream obj_size;
      obj_size<<prefix_out<<"size";
      size_var = obj_size.str();
      tree->Branch(size_var.c_str(), &sizes[size_var], (size_var+"/i").c_str());
    }

    for (size_t i=0; i<vectorInt.size(); ++i) {
      std::string varname_out = prefix_out + vectorInt[i];
      if (prefix_out=="") {
        size_var = vectorInt[i].substr(0,vectorInt[i].find("_"))+"_size";
        if (sizes.count(size_var)==0) tree->Branch(size_var.c_str(), &sizes[size_var], (size_var+"/i").c_str());	  
      }
#if USE_ARRAYS
      tree->Branch(varname_out.c_str(), &vints_values[vectorInt[i]+"_"+label], (varname_out+"["+size_var+"]/I").c_str());
#else
      tree->Branch(varname_out.c_str(), &vints_values[vectorInt[i]+"_"+label]);
#endif
    }
    
    for (size_t i=0; i<vectorFloat.size(); ++i) {
      std::string varname_out = prefix_out + vectorFloat[i];
      if (prefix_out=="") {
        size_var = vectorFloat[i].substr(0,vectorFloat[i].find("_"))+"_size";
        if (sizes.count(size_var)==0) tree->Branch(size_var.c_str(), &sizes[size_var], (size_var+"/i").c_str());
      }
#if USE_ARRAYS
      tree->Branch(varname_out.c_str(), &vfloats_values[vectorFloat[i]+"_"+label], (varname_out+"["+size_var+"]/F").c_str());
#else
      tree->Branch(varname_out.c_str(), &vfloats_values[vectorFloat[i]+"_"+label]);
#endif
    }
    
    // Adding keys
    if (key_label.size()) tree->Branch((prefix_out+"Keys").c_str(), &keys[label]);
  }
}

void B2GTTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  for (auto& pair : sizes) pair.second = 0;
  
  for (auto pset : physObjects) if (!(isData && pset.getUntrackedParameter<bool>("mc_only", false))) {
    std::string label = pset.getUntrackedParameter< std::string >("label");
    std::string prefix_in = pset.getUntrackedParameter<std::string >("prefix_in");
    std::string prefix_out = pset.getUntrackedParameter<std::string >("prefix_out");
    singleBool = pset.getUntrackedParameter<std::vector<std::string > >("singleB", std::vector<std::string >()); 
    singleInt = pset.getUntrackedParameter<std::vector<std::string > >("singleI", std::vector<std::string >()); 
    singleUInt = pset.getUntrackedParameter<std::vector<std::string > >("singleUI", std::vector<std::string >()); 
    singleULong = pset.getUntrackedParameter<std::vector<std::string > >("singleUL", std::vector<std::string >()); 
    singleULLong = pset.getUntrackedParameter<std::vector<std::string > >("singleULL", std::vector<std::string >()); 
    singleFloat = pset.getUntrackedParameter<std::vector<std::string > >("singleF", std::vector<std::string >()); 
    singleDouble = pset.getUntrackedParameter<std::vector<std::string > >("singleD", std::vector<std::string >()); 
    vectorInt = pset.getUntrackedParameter<std::vector<std::string > >("vectorI", std::vector<std::string >()); 
    vectorFloat = pset.getUntrackedParameter<std::vector<std::string > >("vectorF", std::vector<std::string >()); 
    std::string key_label = pset.getUntrackedParameter< std::string >("key_label", "");
    
    //Single ints
    for (size_t i=0; i<singleBool.size(); ++i) {
      std::string varname_in=prefix_in+singleBool[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_bool[varname_in]);
      if (h_bool[varname_in].isValid()) int_values[singleBool[i]+"_"+label]=*h_bool[varname_in];
      else int_values[singleBool[i]+"_"+label]=-9999;
    }

    for (size_t i=0; i<singleInt.size(); ++i) {
      std::string varname_in=prefix_in+singleInt[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_int[varname_in]);
      int_values[singleInt[i]+"_"+label]=*h_int[varname_in];
      if (varname_in.find("HLT")==0) {
	edm::InputTag tag(label, varname_in_nodash+"prescale");
	iEvent.getByLabel(tag, h_int[varname_in+"_prescale"]);
	int_values[singleInt[i]+"_prescale_"+label]=*h_int[varname_in+"_prescale"];
      }
    }
    
    //Single unsigned ints
    for (size_t i=0; i<singleUInt.size(); ++i) {
      std::string varname_in=prefix_in+singleUInt[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_uint[varname_in]);
      uint_values[singleUInt[i]+"_"+label]=*h_uint[varname_in];
    }
    
    //Single unsigned longs
    for (size_t i=0; i<singleULong.size(); ++i) {
      std::string varname_in=prefix_in+singleULong[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_ulong[varname_in]);
      ulong_values[singleULong[i]+"_"+label]=*h_ulong[varname_in];
    }
    
    //Single unsigned long longs
    for (size_t i=0; i<singleULLong.size(); ++i) {
      std::string varname_in=prefix_in+singleULLong[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_ullong[varname_in]);
      ullong_values[singleULLong[i]+"_"+label]=*h_ullong[varname_in];
    }
    
    //Single floats
    for (size_t i=0; i<singleFloat.size(); ++i) {
      std::string varname_in=prefix_in+singleFloat[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_float[varname_in]);
      float_values[singleFloat[i]+"_"+label]=*h_float[varname_in];
    }
    
    //Single doubles
    for (size_t i=0; i<singleDouble.size(); ++i) {
      std::string varname_in=prefix_in+singleDouble[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_double[varname_in]);
      double_values[singleDouble[i]+"_"+label]=*h_double[varname_in];
    }
    
    //Vectors of ints
    for (size_t i=0; i<vectorInt.size(); ++i) {
      std::string varname_in=prefix_in+vectorInt[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_ints[varname_in]);
      std::string size_var = (prefix_out=="") ? vectorInt[i].substr(0,vectorInt[i].find("_")) + "_size" : prefix_out+"size";
      if (sizes[size_var]==0) sizes[size_var]=h_ints[varname_in]->size();
      else if (sizes[size_var] != h_ints[varname_in]->size()) throw cms::Exception("B2GTTreeMaker")
        <<"B2GTTreeMaker: size variable "<<size_var<<"="<<sizes[size_var]<<" but size of vector for "<<varname_in<<"="<<h_ints[varname_in]->size()
        <<"\nCheck variable in B2GExtraVarProducer/config file"<<std::endl;
#if USE_ARRAYS
      for (size_t j=0; j<sizes[size_var]; ++j)
        vints_values[vectorInt[i]+"_"+label][j] = h_ints[varname_in]->at(j);
#else
      vints_values[vectorInt[i]+"_"+label] = *h_ints[varname_in];
#endif
    }
    
    //Vectors of floats
    for (size_t i=0; i<vectorFloat.size(); ++i) {
      std::string varname_in=prefix_in+vectorFloat[i];
      std::string varname_in_nodash = varname_in; // Remove "_" from var name
      size_t f; while ((f=varname_in_nodash.find("_"))!=std::string::npos) varname_in_nodash.erase(f,1);
      edm::InputTag tag(label, varname_in_nodash);
      iEvent.getByLabel(tag, h_floats[varname_in]);
      std::string size_var = (prefix_out=="") ? vectorFloat[i].substr(0,vectorFloat[i].find("_")) + "_size" : prefix_out+"size";
      if (sizes[size_var]==0) sizes[size_var]=h_floats[varname_in]->size();
      else if (sizes[size_var] != h_floats[varname_in]->size()) throw cms::Exception("B2GTTreeMaker")
        <<"B2GTTreeMaker: size variable "<<size_var<<"="<<sizes[size_var]<<" but size of vector "<<varname_in<<"="<<h_floats[varname_in]->size()
        <<"\nCheck variable in B2GExtraVarProducer/config file"<<std::endl;
#if USE_ARRAYS
      for (size_t j=0; j<sizes[size_var]; ++j) 
        vfloats_values[vectorFloat[i]+"_"+label][j] = h_floats[varname_in]->at(j);
#else
      vfloats_values[vectorFloat[i]+"_"+label] = *h_floats[varname_in];
#endif
    }
    
    // Keys (strored in std::vector<std::vector<int> >)
    if (key_label.size()) {
      iEvent.getByLabel(edm::InputTag(key_label, ""), h_keys[label]);
      keys[label] = *h_keys[label];
    }
  }
  
  tree->Fill(); 
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(B2GTTreeMaker);
