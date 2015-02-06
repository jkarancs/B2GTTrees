# B2GTTrees
Filter and Convert B2G edm ntuples to TTree ntuples

Latest Recipe:
setenv SCRAM_ARCH slc6_amd64_gcc491
cmsrel CMSSW_7_3_0
cd CMSSW_7_3_0/src
cmsenv
pic rappoccio:RecoJetsFromMiniAOD;
rm -r Alignment; rm -r CalibTracker; rm -r DQM*; rm -r HeavyIonsAnalysis; rm -r L1Trigge*; rm -r RecoHI; rm -r Validation; rm -r Fireworks
mkdir Analysis;
git clone https://github.com/cmsb2g/B2GAnaFW Analysis/B2GAnaFW
git clone https://github.com/jkarancs/B2GTTrees Analysis/B2GTTrees
scram b -j 20

Make B2G EdmNtuple:
cmsRun Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py maxEvts=100 sample="file:/data/store/mc/Phys14DR/TT_Tune4C_13TeV-pythia8-tauola/MINIAODSIM/PU40bx25_tsg_PHYS14_25_V1-v1/00000/06E41ADB-7870-E411-8850-0025905A605E.root" LHE=False

Convert EdmNtuple to TTreeNtuple:
cmsRun Analysis/B2GTTrees/test/B2GEdmtToTTreeNtuple_cfg.py
