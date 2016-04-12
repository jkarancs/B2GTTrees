# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

```Shell
setenv SCRAM_ARCH slc6_amd64_gcc493
cmsrel CMSSW_7_6_3_patch2
cd CMSSW_7_6_3_patch2/src
cmsenv
git cms-init
git remote add btv-cmssw https://github.com/cms-btv-pog/cmssw.git
git fetch --tags btv-cmssw
git cms-merge-topic cms-btv-pog:fixTMVAEvaluatorMemoryProblem-from-CMSSW_7_6_3 
git clone https://github.com/dmajumder/JetToolbox JMEAnalysis/JetToolbox -b jetToolbox_763
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW -b v7.6.x_v1.2
git clone https://github.com/jkarancs/B2GTTrees Analysis/B2GTTrees
scram b -j 20
```

Running
=======

First copy JEC/JER db/txt files so you can run conveniently from the src directory
```Shell
cp Analysis/B2GAnaFW/test/Fall15_25nsV2_* .
```

   * 1/test) MiniAOD -> Common B2G edm ntuple
```Shell
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="/store/mc/RunIIFall15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00547C97-2FCC-E511-8D75-002590DB91D2.root" outputLabel=B2GEDMNtuple_MC_25ns_76X.root DataProcessing=MC25ns_MiniAOD_76X wantSummary=False maxEvents=1000

cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="/store/data/Run2015D/JetHT/MINIAOD/16Dec2015-v1/00000/301A497D-70B0-E511-9630-002590D0AFA8.root" outputLabel=B2GEDMNtuple_Data_25ns_76X_JetHT.root DataProcessing=Data25ns_76X wantSummary=False maxEvents=1000
```

   * 2) Common B2G edm ntuple -> Add ExtraVars -> TTree ntuple
```Shell
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py runOnGrid=False isData=False sample="file:B2GEDMNtuple_MC_25ns_76X.root" outputLabel=B2GTTreeNtupleExtra_MC_25ns_76X.root lheLabel="externalLHEProducer"

cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py runOnGrid=False isData=True sample="file:B2GEDMNtuple_Data_25ns_76X_JetHT.root" outputLabel=B2GTTreeNtupleExtra_Data_25ns_76X_JetHT.root
```

CRAB3 Tools
==========
INFO: You can mass produce B2GEdmNtuples similar to multicrab

Usage:
```Shell
cd Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
source crab3_B2GEdmNtuples.csh --help
source crab3_B2GTTreeNtuples.csh --help
```

Examples:
   * 1/crab3) Make Edm ntuples on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GEdmNtuples.csh create Apr01 B2GAnaFW_76X_V1p1 MINIAODv2_Apr01_input.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple
edm make_init_twiki Apr01
Janos
janos.karancsi@cern.ch
v7.6.x_v1.2
source crab3_B2GEdmNtuples.csh submit Apr01
source crab3_B2GEdmNtuples.csh status Apr01
source crab3_B2GEdmNtuples.csh find_missing Apr01
source crab3_B2GEdmNtuples.csh checkup Apr01
source crab3_B2GEdmNtuples.csh get_datasets Apr01 --run
source crab3_B2GEdmNtuples.csh make_twiki Apr01 --run
Janos
janos.karancsi@cern.ch
v7.6.x_v1.2
source crab3_B2GEdmNtuples.csh get_lumi Apr01
```

   * 2/crab3) Make TTree ntuples from previous Edm ntuples on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GTTreeNtuples.csh create Apr12_edm_Apr01 Apr12_B2GAnaFW_76X_V1p2 EdmNtuple_Apr01_input.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple
source crab3_B2GTTreeNtuples.csh submit Apr12_edm_Apr01 
source crab3_B2GTTreeNtuples.csh status Apr12_edm_Apr01
source crab3_B2GTTreeNtuples.csh download Apr12_edm_Apr01 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple --run
source crab3_B2GTTreeNtuples.csh find_missing Apr12_edm_Apr01
source crab3_B2GTTreeNtuples.csh report Apr12_edm_Apr01 --run
```
