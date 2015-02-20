if ( $#argv < 1 ) echo "Please specify directory where you want to download files"
alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*"

alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*"

mkdir -p $1/TT
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_Tune4C_13TeV-pythia8-tauola/crab_TT/150218_161157/0000 $1/TT/ --par 4 --run
mkdir -p $1/T_tW-channel
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/crab_T_tW-channel/150218_161532/0000 $1/T_tW-channel/ --par 4 --run
mkdir -p $1/Tbar_tW-channel
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/crab_Tbar_tW-channel/150218_161710/0000 $1/Tbar_tW-channel/ --par 4 --run
mkdir -p $1/WJetsToLNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_13TeV-madgraph-pythia8-tauola/crab_WJetsToLNu/150218_162201/0000 $1/WJetsToLNu/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-100to200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-100to200_Tune4C_13TeV-madgraph-tauola/crab_WJetsToLNu_HT-100to200/150218_162412/0000 $1/WJetsToLNu_HT-100to200/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-200to400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-200to400_Tune4C_13TeV-madgraph-tauola/crab_WJetsToLNu_HT-200to400/150218_162619/0000 $1/WJetsToLNu_HT-200to400/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-400to600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-400to600_Tune4C_13TeV-madgraph-tauola/crab_WJetsToLNu_HT-400to600/150218_162813/0000 $1/WJetsToLNu_HT-400to600/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-600toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-600toInf_Tune4C_13TeV-madgraph-tauola/crab_WJetsToLNu_HT-600toInf/150218_163043/0000 $1/WJetsToLNu_HT-600toInf/ --par 4 --run
mkdir -p $1/DYJetsToLL
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/DYJetsToLL_M-50_13TeV-madgraph-pythia8/crab_DYJetsToLL/150218_163731/0000 $1/DYJetsToLL/ --par 4 --run
mkdir -p $1/QCD_Pt_20to30_bcToE
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_Pt_20to30_bcToE_Tune4C_13TeV_pythia8/crab_QCD_Pt_20to30_bcToE/150218_163921/0000 $1/QCD_Pt_20to30_bcToE/ --par 4 --run
mkdir -p $1/QCD_Pt_30to80_bcToE
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_Pt_30to80_bcToE_Tune4C_13TeV_pythia8/crab_QCD_Pt_30to80_bcToE/150218_164221/0000 $1/QCD_Pt_30to80_bcToE/ --par 4 --run
mkdir -p $1/QCD_Pt_80to170_bcToE
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_Pt_80to170_bcToE_Tune4C_13TeV_pythia8/crab_QCD_Pt_80to170_bcToE/150218_164453/0000 $1/QCD_Pt_80to170_bcToE/ --par 4 --run
mkdir -p $1/QCD_Pt_170toInf_bcToE
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_Pt_170toInf_bcToE_Tune4C_13TeV_pythia8/crab_QCD_Pt_170toInf_bcToE/150218_165016/0000 $1/QCD_Pt_170toInf_bcToE/ --par 4 --run
mkdir -p $1/QCD_HT-100To250
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT-100To250_13TeV-madgraph/crab_QCD_HT-100To250/150218_165155/0000 $1/QCD_HT-100To250/ --par 4 --run
mkdir -p $1/QCD_HT_250To500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT_250To500_13TeV-madgraph/crab_QCD_HT_250To500/150218_165434/0000 $1/QCD_HT_250To500/ --par 4 --run
mkdir -p $1/QCD_HT-500To1000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT-500To1000_13TeV-madgraph/crab_QCD_HT-500To1000/150218_165620/0000 $1/QCD_HT-500To1000/ --par 4 --run
mkdir -p $1/QCD_HT_1000ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT_1000ToInf_13TeV-madgraph/crab_QCD_HT_1000ToInf/150218_170336/0000 $1/QCD_HT_1000ToInf/ --par 4 --run
mkdir -p $1/GGJets_M-200To500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500/150218_170537/0000 $1/GGJets_M-200To500/ --par 4 --run
mkdir -p $1/GGJets_M-500To1000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000/150218_171142/0000 $1/GGJets_M-500To1000/ --par 4 --run
mkdir -p $1/GGJets_M-1000To2000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000/150218_171850/0000 $1/GGJets_M-1000To2000/ --par 4 --run
mkdir -p $1/GGJets_M-2000To4000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000/150218_172104/0000 $1/GGJets_M-2000To4000/ --par 4 --run
mkdir -p $1/GGJets_M-4000To8000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-4000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To8000/150218_172244/0000 $1/GGJets_M-4000To8000/ --par 4 --run
mkdir -p $1/GGJets_M-8000To13000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000/150218_172428/0000 $1/GGJets_M-8000To13000/ --par 4 --run
