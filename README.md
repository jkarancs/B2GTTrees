# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

setenv SCRAM_ARCH slc6_amd64_gcc491  
cmsrel CMSSW_7_4_7_patch2  
cd CMSSW_7_4_7_patch2/src  
cmsenv  
git cms-merge-topic -u cms-met:METCorUnc74X  
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW -b v7.4.x_v6.1_25ns  
git clone https://github.com/jkarancs/B2GTTrees Analysis/B2GTTrees  
scram b -j 20  

Running
=======

- 0) AOD -> MiniAOD  
cmsDriver.py miniAOD-prod -s PAT --eventcontent MINIAODSIM --runUnscheduled  --mc --filein file:AODSIM_input.root --conditions auto:run2_mc -n -1  

- 1/test) MiniAOD -> Common B2G edm ntuple  
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="/store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/022B08C4-C702-E511-9995-D4856459AC30.root" outputLabel=B2GEDMNtuple_MC.root DataProcessing=MC25ns globalTag=MCRUN2_74_V9 maxEvents=-1  

- 2) Common B2G edm ntuple -> Add ExtraVars -> TTree ntuple  
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py isData=False sample="file:B2GEDMNtuple_MC.root" outputLabel=B2GTTreeNtupleExtra_MC.root JECloc=Analysis/B2GTTrees/JECs/Summer15_25nsV2_MC weight=1.0  

CRAB3 Tool
==========
INFO: You can mass produce B2GEdmNtuples similar to multicrab

Usage:  
cd Analysis/B2GTTrees/test/crab3  
cmsenv  
source /cvmfs/cms.cern.ch/crab3/crab.csh  
source crab3_B2GEdmNtuples.csh --help  
source crab3_B2GTTreeNtuples.csh --help  

Examples:  
- 1/crab3) Make Edm ntuples on grid  
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3  
cmsenv  
source /cvmfs/cms.cern.ch/crab3/crab.csh  
voms-proxy-init --voms cms -valid 168:00  
source crab3_B2GEdmNtuples.csh create Sep29 B2GAnaFW_v74x_V6p1_25ns MINIAOD_Sep29_input.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple  
source crab3_B2GEdmNtuples.csh submit Sep29  
source crab3_B2GEdmNtuples.csh status Sep29  
source crab3_B2GEdmNtuples.csh report Sep29 --run  
source crab3_B2GEdmNtuples.csh get_datasets Sep29 --run  
source crab3_B2GEdmNtuples.csh make_twiki Sep29 --run  
Janos  
v7.4.x_V6.1_25ns  
16.34  

# Optional steps (download edm ntuple and make TTrees locally - parallel background jobs)
source crab3_B2GEdmNtuples.csh download Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple
source crab3_B2GEdmNtuples.csh make_ttrees Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple 5

- 2/crab3) Make TTree ntuples from previous Edm ntuples on grid  
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3  
cmsenv  
source /cvmfs/cms.cern.ch/crab3/crab.csh  
voms-proxy-init --voms cms -valid 168:00  
source crab3_B2GTTreeNtuples.csh create Oct02_edm_Sep29 EdmNtuple_Sep29_input.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple  
source crab3_B2GTTreeNtuples.csh submit Oct02_edm_Sep29  
source crab3_B2GTTreeNtuples.csh status Oct02_edm_Sep29  
source crab3_B2GTTreeNtuples.csh report Oct02_edm_Sep29 --run  
source crab3_B2GTTreeNtuples.csh download Oct02_edm_Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple --run  

- 1-2/local) MiniAOD -> Common B2G edm ntuple -> TTree ntuple (Not tested with Run II MC)  
cd $CMSSW_BAS/src/Analysis/B2GTTrees/test/crab3  
source ../make_EdmNtuples.csh Jun03 susy3body /data/store/cmst3/group/susy/gpetrucc/13TeV/Phys14DR/MINIAODSIM/T5ttttDeg_mGo1300_mStop300_mCh285_mChi280_23bodydec_v2 10  
source ../make_EdmNtuples.csh Jun03 susy4body /data/store/cmst3/group/susy/gpetrucc/13TeV/Phys14DR/MINIAODSIM/T5ttttDeg_mGo1300_mStop300_mChi280_4bodydec_v2 10  
source crab3_B2GTTreeNtuples.csh make_ttrees Feb18_edm_Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple/Feb18_edm_Jun03 5  

- 1-2/local)  Local Mass produces step (useful for signal samples not on grid)  
# download MiniAOD signal samples from susy group directory  
# MiniAOD -> Common B2G edm ntuple -> TTree ntuple  
cd $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3  
mkdir susy_signal_dir  
source se_util.csh dl cern:/store/cmst3/group/susy/gpetrucc/13TeV/RunIISpring15DR74/T5ttttDeg_mGo1000_mStop300_mCh285_mChi280_23bodydec susy_signal_dir --par 4 --run  
source ../make_EdmNtuples.csh Sep29 T5ttttDeg_mGo1000_4bodydec susy_signal_dir /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple 5  
source crab3_B2GTTreeNtuples.csh make_ttrees Oct02_edm_Sep29 cross_sections_signal.txt /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Sep29 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple/Oct02_edm_Sep29 5 --run  

