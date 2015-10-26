#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "TH1.h"

class  EventCounter : public edm::EDAnalyzer {
public:
  EventCounter(const edm::ParameterSet& iConfig) :
    isData_(iConfig.getUntrackedParameter<bool>("isData", false))
  {
    edm::Service<TFileService> fs;
    h_ = fs->make<TH1D>("NEventNoFilter",";NLO Weight sign", 2, -1,1);
  }
  
private:
  bool isData_;
  TH1D* h_;
  void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (isData_) h_->Fill(0);
    else {
      edm::Handle<GenEventInfoProduct> genEvtInfo;
      iEvent.getByLabel("generator", genEvtInfo);
      h_->Fill((genEvtInfo->weight()>=0)-1);
    }
  }
};

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(EventCounter);
