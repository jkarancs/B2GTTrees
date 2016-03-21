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
git clone https://github.com/dmajumder/JetToolbox JMEAnalysis/JetToolbox -b jetToolbox_763
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW -b CMSSW_7_6_X_V1
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
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="file:/data/store/mc/RunIIFall15MiniAODv2/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00547C97-2FCC-E511-8D75-002590DB91D2.root" outputLabel=B2GEDMNtuple_MC_25ns_76X.root DataProcessing=MC25ns_MiniAOD_76X wantSummary=False maxEvents=1000

cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="file:/data/store/data/Run2015D/JetHT/MINIAOD/16Dec2015-v1/00000/301A497D-70B0-E511-9630-002590D0AFA8.root" outputLabel=B2GEDMNtuple_Data_25ns_76X_JetHT.root DataProcessing=Data25ns_76X wantSummary=False maxEvents=1000
```

   * 2) Common B2G edm ntuple -> Add ExtraVars -> TTree ntuple
```Shell
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py runOnGrid=False isData=False sample="file:B2GEDMNtuple_MC_25ns_76X.root" outputLabel=B2GTTreeNtupleExtra_MC_25ns_76X.root lheLabel="externalLHEProducer"

cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py runOnGrid=False isData=True sample="file:B2GEDMNtuple_Data_25ns_76X_JetHT.root" outputLabel=B2GTTreeNtupleExtra_Data_25ns_76X_JetHT.root
```

CRAB3 Tools (Recipe might need to be updated for 76X)
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
source crab3_B2GEdmNtuples.csh create Nov18 B2GAnaFW_v74x_V8p4 MINIAODv2_Nov18_input.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple
source crab3_B2GEdmNtuples.csh submit Nov18
source crab3_B2GEdmNtuples.csh make_init_twiki Nov18
Janos
v7.4.x_v8.4
source crab3_B2GEdmNtuples.csh status Nov18
source crab3_B2GEdmNtuples.csh find_missing Nov18
source crab3_B2GEdmNtuples.csh get_datasets Nov18 --run
source crab3_B2GEdmNtuples.csh make_twiki Nov18 --run
Janos
v7.4.x_v8.4
```

   * Optional steps (download edm ntuple and make TTrees locally - parallel background jobs)

```Shell
source crab3_B2GEdmNtuples.csh download Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple
source crab3_B2GEdmNtuples.csh make_ttrees Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple/Oct02 5
```

   * 2/crab3) Make TTree ntuples from previous Edm ntuples on grid
```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
voms-proxy-init --voms cms -valid 168:00
source crab3_B2GTTreeNtuples.csh create Nov30_edm_Nov18 EdmNtuple_Nov18_input.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple
source crab3_B2GTTreeNtuples.csh submit Nov30_edm_Nov18
source crab3_B2GTTreeNtuples.csh status Nov30_edm_Nov18
source crab3_B2GTTreeNtuples.csh download Nov30_edm_Nov18 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple --run
source crab3_B2GTTreeNtuples.csh find_missing Nov30_edm_Nov18
```

   * 1-2/local)  Local Mass produces step (useful for signal samples not on grid)
    download MiniAOD signal samples from susy group directory  
    MiniAOD -> Common B2G edm ntuple -> TTree ntuple
    (Might need to update script)


```Shell
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3
mkdir susy_signal_dir
source se_util.csh dl cern:/store/cmst3/group/susy/gpetrucc/13TeV/RunIISpring15DR74/T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_23bodydec susy_signal_dir --par 4 --run
source ../make_EdmNtuples.csh Sep29 T5ttttDeg_mGo1000_4bodydec susy_signal_dir /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple 5
source crab3_B2GTTreeNtuples.csh make_ttrees Oct02_edm_Sep29 cross_sections_signal.txt /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple/Oct02_edm_Sep29 5 --run
```
