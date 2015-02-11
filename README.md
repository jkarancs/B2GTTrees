# B2GTTrees
============
INFO: Filter and Convert B2G edm ntuples to TTree ntuples

Checkout Instructions (with B2GAnaFW)
=====================================

setenv SCRAM_ARCH slc6_amd64_gcc491  
cmsrel CMSSW_7_3_0  
cd CMSSW_7_3_0/src  
cmsenv  
git cms-merge-topic rappoccio:RecoJetsFromMiniAOD  
rm -r Alignment; rm -r CalibTracker; rm -r DQM*; rm -r HeavyIonsAnalysis  
rm -r L1Trigge*; rm -r RecoHI; rm -r Validation; rm -r Fireworks  
mkdir Analysis  
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW  
git clone https://github.com/jkarancs/B2GTTrees Analysis/B2GTTrees  
scram b -j 20  

Running
=======

- Make B2G EdmNtuple:

cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py maxEvts=100 sample="file:/data/store/mc/Phys14DR/TT_Tune4C_13TeV-pythia8-tauola/MINIAODSIM/PU40bx25_tsg_PHYS14_25_V1-v1/00000/06E41ADB-7870-E411-8850-0025905A605E.root" LHE=False

- Convert EdmNtuple to TTreeNtuple:

cmsRun Analysis/B2GTTrees/test/B2GEdmtToTTreeNtuple_cfg.py

CRAB3 Tool
==========
INFO: You can mass produce B2GEdmNtuples similar to multicrab

cd Analysis/B2GTTrees/test/crab3  
cmsenv  
source /cvmfs/cms.cern.ch/crab3/crab.csh  

- Print usage:  
source crab3_B2GEdmNtuples.csh --help

- Edit crab3_B2GEdmNtuples.csh:
  Set: SE_SITE, SE_USERDIR, DATASETS variables  
  and optionally DLDIR (if you want to download output too)  
  check if your site is set in se_util.csh (SITE_INFO variable)  

- Then use script (add --run to excecute cmd):  
source crab3_B2GEdmNtuples.csh create <TASKNAME>  
source crab3_B2GEdmNtuples.csh submit <TASKNAME>  
source crab3_B2GEdmNtuples.csh status <TASKNAME>  
source crab3_B2GEdmNtuples.csh report <TASKNAME>  
source crab3_B2GEdmNtuples.csh download <TASKNAME>  
