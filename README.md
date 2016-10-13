# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

```Shell
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily
export SCRAM_ARCH=slc6_amd64_gcc530
cmsrel CMSSW_8_0_20
cd CMSSW_8_0_20/src
cmsenv
git cms-init
git cms-merge-topic ikrav:egm_id_80X_v1
git cms-merge-topic cms-met:METRecipe_8020
git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_80X_V2
git clone git@github.com:cmsb2g/B2GAnaFW.git Analysis/B2GAnaFW -b v8.0.x_v2.1
git clone git@github.com:jkarancs/B2GTTrees.git Analysis/B2GTTrees
scram b -j 20
```

Running
=======

First copy sqlite files so you can run conveniently from the src directory
```Shell
cp Analysis/B2GAnaFW/test/JECs/* .
```

There are two (supported) ways to produce ntuples:

   * 1) MiniAOD -> Common B2G edm ntuple
```Shell
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/FABEEFDE-A328-E611-B251-848F69FD29AF.root" outputLabel=B2GEDMNtuple_MC_25ns_80X.root DataProcessing=MC_MiniAODv2_80X wantSummary=False maxEvents=1000

cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="/store/data/Run2016B/JetHT/MINIAOD/PromptReco-v2/000/275/375/00000/A0AD9B85-5639-E611-A51E-02163E0133CC.root" outputLabel=B2GEDMNtuple_Data_25ns_80X_JetHT.root DataProcessing=Data_80X wantSummary=False maxEvents=1000
```

   * 2) MiniAOD -> Common B2G edm ntuple -> Add ExtraVars (+Filter) -> TTree ntuple
```Shell
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py sample="/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/FABEEFDE-A328-E611-B251-848F69FD29AF.root" outputLabel=B2GTTreeNtupleExtra_MC_25ns_80X.root DataProcessing=MC_MiniAODv2_80X wantSummary=False maxEvents=1000

cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py sample="/store/data/Run2016B/JetHT/MINIAOD/PromptReco-v2/000/275/375/00000/A0AD9B85-5639-E611-A51E-02163E0133CC.root" outputLabel=B2GTTreeNtupleExtra_Data_25ns_80X_JetHT.root DataProcessing=Data_80X wantSummary=False maxEvents=1000
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
   * 1/crab3) Make B2G Edm ntuples from MINIAOD(SIM) on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GEdmNtuples.csh create Sep04 B2GAnaFW_80X_V2p1 MINIAODv2_80X_Sep04_T2tt.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/Sep04
edm make_init_twiki Sep04
Janos
janos.karancsi@cern.ch
v8.0.x_v2.1
source crab3_B2GEdmNtuples.csh submit Sep04
source crab3_B2GEdmNtuples.csh status Sep04
source crab3_B2GEdmNtuples.csh find_missing Sep04
source crab3_B2GEdmNtuples.csh checkup Sep04
source crab3_B2GEdmNtuples.csh get_datasets Sep04 --run
source crab3_B2GEdmNtuples.csh make_twiki Sep04 --run
Janos
janos.karancsi@cern.ch
v8.0.x_v2.1
source crab3_B2GEdmNtuples.csh get_lumi Sep04
```

   * 2/crab3) Make TTree ntuples from previous MINIAOD(SIM) on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GTTreeNtuples_Merged.csh create Sep04 B2GAnaFW_80X_V2p1_Sep04 MINIAODv2_80X_Sep04_T2tt.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/Sep04
source crab3_B2GTTreeNtuples_Merged.csh submit Sep04 
source crab3_B2GTTreeNtuples_Merged.csh status Sep04
source crab3_B2GTTreeNtuples_Merged.csh download Sep04 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple --run
source crab3_B2GTTreeNtuples_Merged.csh find_missing Sep04
source crab3_B2GTTreeNtuples_Merged.csh checkup Sep04
source crab3_B2GTTreeNtuples_Merged.csh report Sep04 --run
source crab3_B2GTTreeNtuples_Merged.csh get_lumi Sep04
```

