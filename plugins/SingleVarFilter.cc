#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"

template <typename T>
class MinMaxFilter : public edm::EDFilter {
  
public:
  explicit MinMaxFilter(const edm::ParameterSet&);
  
private:
  virtual bool filter(edm::Event&, const edm::EventSetup&);

  // ----------member data ---------------------------
  edm::InputTag   srcTag_;
  T min_, max_;
};

template <typename T>
MinMaxFilter<T>::MinMaxFilter(const edm::ParameterSet& iConfig)
{
  srcTag_ = iConfig.getParameter<edm::InputTag>("src");
  min_    = iConfig.getUntrackedParameter<double>("min",-999999);
  max_    = iConfig.getUntrackedParameter<double>("max",-999999);
  
  edm::EDGetTokenT<T>(consumes<T>(srcTag_));
}

template <typename T>
bool MinMaxFilter<T>::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<T> src;
  iEvent.getByLabel(srcTag_, src);

  bool result = true;

  if ( min_ != -999999 && *src < min_ ) result = false;
  if ( max_ != -999999 && *src >= max_ ) result = false;

  return result;
}

typedef MinMaxFilter<float> SingleFloatFilter;
typedef MinMaxFilter<int>   SingleIntFilter;

DEFINE_FWK_MODULE( SingleFloatFilter );
DEFINE_FWK_MODULE( SingleIntFilter );
