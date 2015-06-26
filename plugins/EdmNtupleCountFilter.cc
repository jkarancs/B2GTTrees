#include "FWCore/Framework/interface/MakerMacros.h"
#include "CommonTools/UtilAlgos/interface/ObjectCountFilter.h"
#include "PhysicsTools/UtilAlgos/interface/ParameterAdapter.h"

struct FloatMinSelector {
  FloatMinSelector( double min ) : min_( min ) { }
  template<typename T>
  bool operator()( const T & t ) const { return t >= min_; }

private:
  double min_;
};

namespace reco {
  namespace modules {

    template<>
    struct ParameterAdapter<FloatMinSelector> {
      static FloatMinSelector make( const edm::ParameterSet & cfg, edm::ConsumesCollector & iC ) {
        return FloatMinSelector( cfg.getParameter<double>( "min" ) );
      }
    };
  }
}

typedef ObjectCountFilter<std::vector<float>, FloatMinSelector >::type EdmNtupleCountFilter;

DEFINE_FWK_MODULE( EdmNtupleCountFilter );
