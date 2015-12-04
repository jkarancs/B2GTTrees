#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "TH1.h"

class  EventCounter : public edm::EDAnalyzer {
public:
  EventCounter(const edm::ParameterSet& iConfig)
  {
    edm::Service<TFileService> fs;
    h_weightsign_ = fs->make<TH1D>("weightsign",";Weight sign", 2, -1,1);
    h_totweight_ = fs->make<TH1D>("totweight",";Sum of Weights", 1,0,1);
    h_pileup_ = fs->make<TH1D>("pileup",";Pile-up", 100,0,100);
  }

private:
  TH1D* h_weightsign_;
  TH1D* h_totweight_;
  TH1D* h_pileup_;
  void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if ( iEvent.eventAuxiliary().isRealData() ) {
      h_weightsign_->Fill(0);
      h_totweight_->Fill(0);
    } else {
      // Save sign of weights and total weight
      edm::Handle<GenEventInfoProduct> genEvtInfo;
      iEvent.getByLabel("generator", genEvtInfo);
      h_weightsign_->Fill((genEvtInfo->weight()>=0)-1);
      h_totweight_->Fill(genEvtInfo->weight());
      
      // Save Pileup distribution for MC
      edm::Handle<int>  NTrueInt;
      iEvent.getByLabel(edm::InputTag("eventUserData", "puNtrueInt"), NTrueInt);
      h_pileup_->Fill(*NTrueInt);
    }
  }
};

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(EventCounter);
