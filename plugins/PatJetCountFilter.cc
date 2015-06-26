#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CommonTools/UtilAlgos/interface/ObjectCountFilter.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

typedef ObjectCountFilter<pat::JetCollection, StringCutObjectSelector<pat::Jet> >::type PatJetCountFilter;

DEFINE_FWK_MODULE( PatJetCountFilter );
