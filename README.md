# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

```Shell
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily
export SCRAM_ARCH=slc6_amd64_gcc530
cmsrel CMSSW_8_0_24_patch1
cd CMSSW_8_0_24_patch1/src
cmsenv
git cms-init
git cms-merge-topic cms-met:METRecipe_8020
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter
git cms-merge-topic ikrav:egm_id_80X_v2
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_80X_V3
git clone git@github.com:cmsb2g/B2GAnaFW.git Analysis/B2GAnaFW -b v8.0.x_v2.4
git clone git@github.com:jkarancs/B2GTTrees.git Analysis/B2GTTrees -b v8.0.x_v2.4_PR66_Jan12
cd Analysis/B2GAnaFW
git fetch origin pull/66/head:PR66
git checkout PR66
cd ../..
scram b -j 20
cd $CMSSW_BASE/external/slc6_amd64_gcc530
git clone git@github.com:ikrav/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
cd data/RecoEgamma/ElectronIdentification/data
git checkout egm_id_80X_v1
cd $CMSSW_BASE/src
```

Running
=======

First copy sqlite files so you can run conveniently from the src directory
```Shell
ln -s Analysis/B2GAnaFW/test/JECs/*.db .
```

There are two (supported) ways to produce ntuples:

   * 1) MiniAOD -> Common B2G edm ntuple
```Shell
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample=/store/data/Run2016C/JetHT/MINIAOD/23Sep2016-v1/50000/2CD6B039-BA89-E611-931C-0025905A60F4.root outputLabel=B2GEDMNtuple_Data_80X_JetHT_Run2016C.root DataProcessing=Data_80X_Run2016BCD_23Sep2016 wantSummary=False maxEvents=1000

cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample=/store/mc/RunIISummer16MiniAODv2/TT_TuneEE5C_13TeV-powheg-herwigpp/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/60000/0045D9EF-67B5-E611-B736-FA163EEF13C9.root outputLabel=B2GEDMNtuple_MC_80X.root DataProcessing=MC_MiniAODv2_80X_Summer16 wantSummary=False maxEvents=1000
```


   * 2) MiniAOD -> Common B2G edm ntuple -> Add ExtraVars (+Filter) -> TTree ntuple
```Shell
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py sample=/store/data/Run2016C/JetHT/MINIAOD/23Sep2016-v1/50000/2CD6B039-BA89-E611-931C-0025905A60F4.root outputLabel=B2GTTreeNtupleExtra_Data_80X_JetHT_Run2016C.root DataProcessing=Data_80X_Run2016BCD_23Sep2016 wantSummary=False maxEvents=1000

cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py sample=/store/mc/RunIISummer16MiniAODv2/TT_TuneEE5C_13TeV-powheg-herwigpp/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/60000/0045D9EF-67B5-E611-B736-FA163EEF13C9.root outputLabel=B2GTTreeNtupleExtra_MC_80X.root DataProcessing=MC_MiniAODv2_80X_Summer16 wantSummary=False maxEvents=1000
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
source crab3_B2GTTreeNtuples_Merged.csh --help
```

Examples:
   * 1/crab3) Make B2G Edm ntuples from MINIAOD(SIM) on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GEdmNtuples.csh create Jan12 B2GAnaFW_80X_V2p4 MINIAODv2_80X_Jan12_input.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/Jan12
edm make_init_twiki Jan12
Janos
janos.karancsi@cern.ch
v8.0.x_v2.4
source crab3_B2GEdmNtuples.csh submit Jan12
source crab3_B2GEdmNtuples.csh status Jan12
source crab3_B2GEdmNtuples.csh find_missing Jan12
source crab3_B2GEdmNtuples.csh checkup Jan12
source crab3_B2GEdmNtuples.csh get_datasets Jan12 --run
source crab3_B2GEdmNtuples.csh make_twiki Jan12 --run
Janos
janos.karancsi@cern.ch
v8.0.x_v2.4
source crab3_B2GEdmNtuples.csh get_lumi Jan12
```

   * 2/crab3) Make TTree ntuples from MINIAOD(SIM) on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GTTreeNtuples_Merged.csh create Jan12 B2GAnaFW_80X_V2p4_PR66_Jan12 MINIAODv2_80X_Jan12_input.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/Jan12
source crab3_B2GTTreeNtuples_Merged.csh submit Jan12 
source crab3_B2GTTreeNtuples_Merged.csh status Jan12
source crab3_B2GTTreeNtuples_Merged.csh download Jan12 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple --run
source crab3_B2GTTreeNtuples_Merged.csh find_missing Jan12
source crab3_B2GTTreeNtuples_Merged.csh checkup Jan12
source crab3_B2GTTreeNtuples_Merged.csh report Jan12 --run
source crab3_B2GTTreeNtuples_Merged.csh get_lumi Jan12
```

