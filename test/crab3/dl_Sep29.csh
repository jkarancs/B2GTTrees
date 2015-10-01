if ( $#argv < 1 ) echo "Please specify directory where you want to download files"
alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*"
alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*"

mkdir -p $1/JetHT_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/JetHT/B2GAnaFW_v74x_V6p1_25ns_Run2015C-PromptReco-v1/150929_123509/0000 $1/JetHT_Run2015C-PromptReco --par 4 --run
mkdir -p $1/SingleElectron_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/SingleElectron/B2GAnaFW_v74x_V6p1_25ns_Run2015C-PromptReco-v1/150929_123634/0000 $1/SingleElectron_Run2015C-PromptReco --par 4 --run
mkdir -p $1/SingleMuon_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/SingleMuon/B2GAnaFW_v74x_V6p1_25ns_Run2015C-PromptReco-v1/150929_123803/0000 $1/SingleMuon_Run2015C-PromptReco --par 4 --run
mkdir -p $1/TTJets_madgraph
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_123931/0000 $1/TTJets_madgraph --par 4 --run
mkdir -p $1/TT_powheg_pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TT_TuneCUETP8M1_13TeV-powheg-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_124259/0000 $1/TT_powheg_pythia8 --par 4 --run
mkdir -p $1/TT_powheg_pythia6
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TT_TuneZ2star_13TeV-powheg-pythia6-tauola/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_124456/0000 $1/TT_powheg_pythia6 --par 4 --run
mkdir -p $1/TT_herwigpp_TuneEE5C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TT_TuneEE5C_13TeV-amcatnlo-herwigpp/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_124653/0000 $1/TT_herwigpp_TuneEE5C --par 4 --run
mkdir -p $1/TTJets_amcatnloFXFX
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_124821/0000 $1/TTJets_amcatnloFXFX --par 4 --run
mkdir -p $1/TT_amcatnlo
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125021/0000 $1/TT_amcatnlo --par 4 --run
mkdir -p $1/TTJets_HT-600to800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125146/0000 $1/TTJets_HT-600to800 --par 4 --run
mkdir -p $1/TTJets_HT-800to1200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125310/0000 $1/TTJets_HT-800to1200 --par 4 --run
mkdir -p $1/TTJets_HT-1200to2500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125433/0000 $1/TTJets_HT-1200to2500 --par 4 --run
mkdir -p $1/TTJets_HT-2500toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125554/0000 $1/TTJets_HT-2500toInf --par 4 --run
mkdir -p $1/ST_s-channel_4f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125717/0000 $1/ST_s-channel_4f_leptonDecays --par 4 --run
mkdir -p $1/ST_t-channel_top_4f_powheg
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_125840/0000 $1/ST_t-channel_top_4f_powheg --par 4 --run
mkdir -p $1/ST_t-channel_antitop_4f_powheg
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130006/0000 $1/ST_t-channel_antitop_4f_powheg --par 4 --run
mkdir -p $1/ST_tW_top_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130134/0000 $1/ST_tW_top_5f_inclusiveDecays --par 4 --run
mkdir -p $1/ST_tW_antitop_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130258/0000 $1/ST_tW_antitop_5f_inclusiveDecays --par 4 --run
mkdir -p $1/TTZToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130421/0000 $1/TTZToQQ --par 4 --run
mkdir -p $1/TTZToLLNuNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130547/0000 $1/TTZToLLNuNu --par 4 --run
mkdir -p $1/TTWJetsToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130711/0000 $1/TTWJetsToQQ --par 4 --run
mkdir -p $1/TTWJetsToLNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_130834/0000 $1/TTWJetsToLNu --par 4 --run
mkdir -p $1/tZq_ll
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_131000/0000 $1/tZq_ll --par 4 --run
mkdir -p $1/tZq_nunu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_131123/0000 $1/tZq_nunu --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-100To200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZJetsToNuNu_HT-100To200_13TeV-madgraph/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131249/0000 $1/ZJetsToNuNu_HT-100To200 --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-200To400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZJetsToNuNu_HT-200To400_13TeV-madgraph/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131416/0000 $1/ZJetsToNuNu_HT-200To400 --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-400To600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZJetsToNuNu_HT-400To600_13TeV-madgraph/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131540/0000 $1/ZJetsToNuNu_HT-400To600 --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-600ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131703/0000 $1/ZJetsToNuNu_HT-600ToInf --par 4 --run
mkdir -p $1/WJetsToLNu_HT-100To200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131827/0000 $1/WJetsToLNu_HT-100To200 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-200To400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_131956/0000 $1/WJetsToLNu_HT-200To400 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-400To600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/150929_132121/0000 $1/WJetsToLNu_HT-400To600 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-600To800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_132243/0000 $1/WJetsToLNu_HT-600To800 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-800To1200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_132405/0000 $1/WJetsToLNu_HT-800To1200 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-1200To2500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_132530/0000 $1/WJetsToLNu_HT-1200To2500 --par 4 --run
mkdir -p $1/WJetsToLNu_HT-2500ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_132655/0000 $1/WJetsToLNu_HT-2500ToInf --par 4 --run
mkdir -p $1/QCD_HT100to200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_132922/0000 $1/QCD_HT100to200 --par 4 --run
mkdir -p $1/QCD_HT200to300
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_133120/0000 $1/QCD_HT200to300 --par 4 --run
mkdir -p $1/QCD_HT300to500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_133242/0000 $1/QCD_HT300to500 --par 4 --run
mkdir -p $1/QCD_HT500to700
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_133410/0000 $1/QCD_HT500to700 --par 4 --run
mkdir -p $1/QCD_HT700to1000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_133548/0000 $1/QCD_HT700to1000 --par 4 --run
mkdir -p $1/QCD_HT1000to1500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_133729/0000 $1/QCD_HT1000to1500 --par 4 --run
mkdir -p $1/QCD_HT1500to2000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_133933/0000 $1/QCD_HT1500to2000 --par 4 --run
mkdir -p $1/QCD_HT2000toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_134100/0000 $1/QCD_HT2000toInf --par 4 --run
mkdir -p $1/WWTo4Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WWTo4Q_13TeV-powheg/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/150929_134300/0000 $1/WWTo4Q --par 4 --run
mkdir -p $1/WWToLNuQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WWToLNuQQ_13TeV-powheg/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_134422/0000 $1/WWToLNuQQ --par 4 --run
mkdir -p $1/WWTo2L2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WWTo2L2Nu_13TeV-powheg/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_134548/0000 $1/WWTo2L2Nu --par 4 --run
mkdir -p $1/WZTo1L1Nu2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_134747/0000 $1/WZTo1L1Nu2Q --par 4 --run
mkdir -p $1/WZTo1L3Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_134953/0000 $1/WZTo1L3Nu --par 4 --run
mkdir -p $1/WZTo2L2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/150929_135116/0000 $1/WZTo2L2Q --par 4 --run
mkdir -p $1/WZTo3LNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_135607/0000 $1/WZTo3LNu --par 4 --run
mkdir -p $1/ZZTo4Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZZTo4Q_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_135806/0000 $1/ZZTo4Q --par 4 --run
mkdir -p $1/ZZTo2Q2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_140003/0000 $1/ZZTo2Q2Nu --par 4 --run
mkdir -p $1/ZZTo2L2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZZTo2L2Nu_13TeV_powheg_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_140138/0000 $1/ZZTo2L2Nu --par 4 --run
mkdir -p $1/ZZTo2L2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_140308/0000 $1/ZZTo2L2Q --par 4 --run
mkdir -p $1/ZZTo4L
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple/ZZTo4L_13TeV_powheg_pythia8/B2GAnaFW_v74x_V6p1_25ns_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/150929_140508/0000 $1/ZZTo4L --par 4 --run
