set DLDIR="/data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Feb04"
alias se "source se_util.csh \!*"

mkdir -p $DLDIR
mkdir -p $DLDIR/TT
cd $DLDIR/TT
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TT_Tune4C_13TeV-pythia8-tauola/B2G_edm_Feb04/150209_234755/0000 --par 4 --run
cd -
mkdir -p $DLDIR/T_tW-channel
cd $DLDIR/T_tW-channel
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/B2G_edm_Feb04/150209_235149/0000 --par 4 --run
cd -
mkdir -p $DLDIR/Tbar_tW-channel
cd $DLDIR/Tbar_tW-channel
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/B2G_edm_Feb04/150209_235219/0000 --par 4 --run
cd -
mkdir -p $DLDIR/WJetsToLNu
cd $DLDIR/WJetsToLNu
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_13TeV-madgraph-pythia8-tauola/B2G_edm_Feb04/150209_235253/0000 --par 4 --run
cd -
mkdir -p $DLDIR/WJetsToLNu_HT-100to200
cd $DLDIR/WJetsToLNu_HT-100to200
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-100to200_Tune4C_13TeV-madgraph-tauola/B2G_edm_Feb04/150209_235323/0000 --par 4 --run
cd -
mkdir -p $DLDIR/WJetsToLNu_HT-200to400
cd $DLDIR/WJetsToLNu_HT-200to400
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-200to400_Tune4C_13TeV-madgraph-tauola/B2G_edm_Feb04/150209_235410/0000 --par 4 --run
cd -
mkdir -p $DLDIR/WJetsToLNu_HT-400to600
cd $DLDIR/WJetsToLNu_HT-400to600
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-400to600_Tune4C_13TeV-madgraph-tauola/B2G_edm_Feb04/150209_235441/0000 --par 4 --run
cd -
mkdir -p $DLDIR/WJetsToLNu_HT-600toInf
cd $DLDIR/WJetsToLNu_HT-600toInf
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-600toInf_Tune4C_13TeV-madgraph-tauola/B2G_edm_Feb04/150209_235515/0000 --par 4 --run
cd -
mkdir -p $DLDIR/DYJetsToLL
cd $DLDIR/DYJetsToLL
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/DYJetsToLL_M-50_13TeV-madgraph-pythia8/B2G_edm_Feb04/150209_235545/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_Pt_20to30_bcToE
cd $DLDIR/QCD_Pt_20to30_bcToE
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_Pt_20to30_bcToE_Tune4C_13TeV_pythia8/B2G_edm_Feb04/150209_235616/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_Pt_30to80_bcToE
cd $DLDIR/QCD_Pt_30to80_bcToE
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_Pt_30to80_bcToE_Tune4C_13TeV_pythia8/B2G_edm_Feb04/150209_235646/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_Pt_80to170_bcToE
cd $DLDIR/QCD_Pt_80to170_bcToE
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_Pt_80to170_bcToE_Tune4C_13TeV_pythia8/B2G_edm_Feb04/150209_235720/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_Pt_170toInf_bcToE
cd $DLDIR/QCD_Pt_170toInf_bcToE
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_Pt_170toInf_bcToE_Tune4C_13TeV_pythia8/B2G_edm_Feb04/150209_235750/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_HT-100To250
cd $DLDIR/QCD_HT-100To250
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT-100To250_13TeV-madgraph/B2G_edm_Feb04/150209_235821/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_HT_250To500
cd $DLDIR/QCD_HT_250To500
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT_250To500_13TeV-madgraph/B2G_edm_Feb04/150209_235851/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_HT-500To1000
cd $DLDIR/QCD_HT-500To1000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT-500To1000_13TeV-madgraph/B2G_edm_Feb04/150209_235923/0000 --par 4 --run
cd -
mkdir -p $DLDIR/QCD_HT_1000ToInf
cd $DLDIR/QCD_HT_1000ToInf
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT_1000ToInf_13TeV-madgraph/B2G_edm_Feb04/150209_235953/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-2000To4000
cd $DLDIR/GGJets_M-2000To4000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_000227/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-200To500
cd $DLDIR/GGJets_M-200To500
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-200To500_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_073245/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-500To1000
cd $DLDIR/GGJets_M-500To1000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-500To1000_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_073320/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-1000To2000
cd $DLDIR/GGJets_M-1000To2000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_073353/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-4000To8000
cd $DLDIR/GGJets_M-4000To8000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-4000To8000_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_073426/0000 --par 4 --run
cd -
mkdir -p $DLDIR/GGJets_M-8000To13000
cd $DLDIR/GGJets_M-8000To13000
se dl T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/B2G_edm_Feb04/150210_073457/0000 --par 4 --run
cd -
