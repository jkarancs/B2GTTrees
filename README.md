# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

setenv SCRAM_ARCH slc6_amd64_gcc491  
cmsrel CMSSW_7_4_5_patch1  
cd CMSSW_7_4_5_patch1/src  
cmsenv  
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW  
git clone https://github.com/jkarancs/B2GTTrees Analysis/B2GTTrees  
scram b -j 20  

Running
=======

- 0) AOD -> MiniAOD  
cmsDriver.py miniAOD-prod -s PAT --eventcontent MINIAODSIM --runUnscheduled  --mc --filein file:AODSIM_input.root --conditions auto:run2_mc -n -1  

- 1/test) MiniAOD -> Common B2G edm ntuple  
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="file:miniAOD-prod_PAT.root" LHE=False  

- 2/a) B2G edm ntuple -> TTree ntuple  
cmsRun Analysis/B2GTTrees/test/B2GEdmtToTTreeNtuple_cfg.py  

- 2/b) Common B2G edm ntuple -> Add ExtraVars -> TTree ntuple  
cmsRun Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py weight=1.0  

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
source crab3_B2GEdmNtuples.csh create Jun03 MINIAODSIM_Jun03_input.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple  
source crab3_B2GEdmNtuples.csh submit Jun03  
source crab3_B2GEdmNtuples.csh status Jun03 --run  
source crab3_B2GEdmNtuples.csh finished Jun03 --run  
source crab3_B2GEdmNtuples.csh report Jun03  
source crab3_B2GEdmNtuples.csh get_datasets Jun03 --run  
source crab3_B2GEdmNtuples.csh make_twiki Jun03 --run  

Optional steps (download edm ntuple and make TTrees locally - parallel background jobs)  

source crab3_B2GEdmNtuples.csh download Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple  
source crab3_B2GEdmNtuples.csh make_ttrees Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple 5  

- 2/crab3) Make TTree ntuples from previous Edm ntuples on grid  
cd $CMSSW_BAS/src/Analysis/B2GTTrees/test/crab3  
source crab3_B2GTTreeNtuples.csh create Jul02_edm_Jun03 EdmNtuple_Jun03_input.txt cross_sections.txt T2_HU_Budapest /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple  
source crab3_B2GTTreeNtuples.csh submit Jul02_edm_Jun03  
source crab3_B2GTTreeNtuples.csh status Jul02_edm_Jun03  
source crab3_B2GTTreeNtuples.csh finished Jul02_edm_Jun03  
source crab3_B2GTTreeNtuples.csh report Jul02_edm_Jun03  
source crab3_B2GTTreeNtuples.csh download Jul02_edm_Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple  

- 1-2/local) MiniAOD -> Common B2G edm ntuple -> TTree ntuple (Not tested with Run II MC)  
cd $CMSSW_BAS/src/Analysis/B2GTTrees/test/crab3  
source ../make_EdmNtuples.csh Jun03 susy3body /data/store/cmst3/group/susy/gpetrucc/13TeV/Phys14DR/MINIAODSIM/T5ttttDeg_mGo1300_mStop300_mCh285_mChi280_23bodydec_v2 10  
source ../make_EdmNtuples.csh Jun03 susy4body /data/store/cmst3/group/susy/gpetrucc/13TeV/Phys14DR/MINIAODSIM/T5ttttDeg_mGo1300_mStop300_mChi280_4bodydec_v2 10  
source crab3_B2GTTreeNtuples.csh make_ttrees Feb18_edm_Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Jun03 /data/gridout/jkarancs/SusyAnalysis/B2G/TTreeNtuple/Feb18_edm_Jun03 5  
