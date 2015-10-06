if ( $#argv < 1 ) echo "Please specify directory where you want to download files"
alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*"
alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*"

mkdir -p $1/JetHT_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_Run2015C-PromptReco/151003_184738/0000 $1/JetHT_Run2015C-PromptReco/ --par 4 --run
mkdir -p $1/SingleElectron_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_Run2015C-PromptReco/151003_185029/0000 $1/SingleElectron_Run2015C-PromptReco/ --par 4 --run
mkdir -p $1/SingleElectron_Run2015D-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_Run2015D-PromptReco/151003_185157/0000 $1/SingleElectron_Run2015D-PromptReco/ --par 4 --run
mkdir -p $1/SingleMuon_Run2015C-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_Run2015C-PromptReco/151003_185320/0000 $1/SingleMuon_Run2015C-PromptReco/ --par 4 --run
mkdir -p $1/TT_powheg_pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_powheg_pythia8/151003_190232/0000 $1/TT_powheg_pythia8/ --par 4 --run
mkdir -p $1/TT_herwigpp_TuneEE5C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneEE5C_13TeV-amcatnlo-herwigpp/crab_TT_herwigpp_TuneEE5C/151003_191031/0000 $1/TT_herwigpp_TuneEE5C/ --par 4 --run
mkdir -p $1/TTJets_amcatnloFXFX
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_TTJets_amcatnloFXFX/151003_191202/0000 $1/TTJets_amcatnloFXFX/ --par 4 --run
mkdir -p $1/TT_amcatnlo
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TT_amcatnlo/151003_191326/0000 $1/TT_amcatnlo/ --par 4 --run
mkdir -p $1/TTJets_HT-1200to2500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-1200to2500/151003_192220/0000 $1/TTJets_HT-1200to2500/ --par 4 --run
mkdir -p $1/TTJets_HT-2500toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-2500toInf/151003_192346/0000 $1/TTJets_HT-2500toInf/ --par 4 --run
mkdir -p $1/ST_t-channel_top_4f_powheg
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_t-channel_top_4f_powheg/151003_192606/0000 $1/ST_t-channel_top_4f_powheg/ --par 4 --run
mkdir -p $1/ST_t-channel_antitop_4f_powheg
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_t-channel_antitop_4f_powheg/151003_192733/0000 $1/ST_t-channel_antitop_4f_powheg/ --par 4 --run
mkdir -p $1/ST_tW_top_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_top_5f_inclusiveDecays/151003_192827/0000 $1/ST_tW_top_5f_inclusiveDecays/ --par 4 --run
mkdir -p $1/TTZToLLNuNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZToLLNuNu/151003_193254/0000 $1/TTZToLLNuNu/ --par 4 --run
mkdir -p $1/TTWJetsToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTWJetsToQQ/151003_193421/0000 $1/TTWJetsToQQ/ --par 4 --run
mkdir -p $1/tZq_ll
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_tZq_ll/151003_193600/0000 $1/tZq_ll/ --par 4 --run
mkdir -p $1/tZq_nunu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/tZq_nunu_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_tZq_nunu/151003_193725/0000 $1/tZq_nunu/ --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-100To200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_ZJetsToNuNu_HT-100To200/151003_193847/0000 $1/ZJetsToNuNu_HT-100To200/ --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-200To400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_ZJetsToNuNu_HT-200To400/151003_194010/0000 $1/ZJetsToNuNu_HT-200To400/ --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-600ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/crab_ZJetsToNuNu_HT-600ToInf/151003_194229/0000 $1/ZJetsToNuNu_HT-600ToInf/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-200To400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-200To400/151003_195038/0000 $1/WJetsToLNu_HT-200To400/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-800To1200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-800To1200/151003_200406/0000 $1/WJetsToLNu_HT-800To1200/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-1200To2500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-1200To2500/151003_200529/0000 $1/WJetsToLNu_HT-1200To2500/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-2500ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-2500ToInf/151003_200655/0000 $1/WJetsToLNu_HT-2500ToInf/ --par 4 --run
mkdir -p $1/QCD_HT500to700
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700/151003_201656/0000 $1/QCD_HT500to700/ --par 4 --run
mkdir -p $1/QCD_HT1000to1500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1000to1500/151003_202323/0000 $1/QCD_HT1000to1500/ --par 4 --run
mkdir -p $1/QCD_HT1500to2000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1500to2000/151003_202446/0000 $1/QCD_HT1500to2000/ --par 4 --run
mkdir -p $1/QCD_HT2000toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT2000toInf/151003_202535/0000 $1/QCD_HT2000toInf/ --par 4 --run
mkdir -p $1/WWTo4Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WWTo4Q_13TeV-powheg/crab_WWTo4Q/151003_202655/0000 $1/WWTo4Q/ --par 4 --run
mkdir -p $1/WZTo1L1Nu2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/crab_WZTo1L1Nu2Q/151003_203004/0000 $1/WZTo1L1Nu2Q/ --par 4 --run
mkdir -p $1/WZTo1L3Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/crab_WZTo1L3Nu/151003_203134/0000 $1/WZTo1L3Nu/ --par 4 --run
mkdir -p $1/ZZTo2Q2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/crab_ZZTo2Q2Nu/151003_204637/0000 $1/ZZTo2Q2Nu/ --par 4 --run
mkdir -p $1/ZZTo2L2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZTo2L2Nu_13TeV_powheg_pythia8/crab_ZZTo2L2Nu/151003_204802/0000 $1/ZZTo2L2Nu/ --par 4 --run
mkdir -p $1/SingleMuon_Run2015D-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_Run2015D-PromptReco/151003_222351/0000 $1/SingleMuon_Run2015D-PromptReco/ --par 4 --run
mkdir -p $1/TTZToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZToQQ/151003_223749/0000 $1/TTZToQQ/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-600To800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-600To800/151003_224455/0000 $1/WJetsToLNu_HT-600To800/ --par 4 --run
mkdir -p $1/QCD_HT700to1000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT700to1000/151003_225228/0000 $1/QCD_HT700to1000/ --par 4 --run
mkdir -p $1/WZTo3LNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/crab_WZTo3LNu/151003_230652/0000 $1/WZTo3LNu/ --par 4 --run
mkdir -p $1/ZZTo4L
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZTo4L_13TeV_powheg_pythia8/crab_ZZTo4L/151003_230935/0000 $1/ZZTo4L/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-100To200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-100To200/151003_231344/0000 $1/WJetsToLNu_HT-100To200/ --par 4 --run
mkdir -p $1/ST_s-channel_4f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_s-channel_4f_leptonDecays/151003_231421/0000 $1/ST_s-channel_4f_leptonDecays/ --par 4 --run
mkdir -p $1/ZJetsToNuNu_HT-400To600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZJetsToNuNu_HT-400To600_13TeV-madgraph/crab_ZJetsToNuNu_HT-400To600/151003_231436/0000 $1/ZJetsToNuNu_HT-400To600/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-400To600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-400To600/151003_231850/0000 $1/WJetsToLNu_HT-400To600/ --par 4 --run
mkdir -p $1/WWToLNuQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WWToLNuQQ_13TeV-powheg/crab_WWToLNuQQ/151003_232618/0000 $1/WWToLNuQQ/ --par 4 --run
mkdir -p $1/WWTo2L2Nu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WWTo2L2Nu_13TeV-powheg/crab_WWTo2L2Nu/151003_233430/0000 $1/WWTo2L2Nu/ --par 4 --run
mkdir -p $1/JetHT_Run2015D-PromptReco
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_Run2015D-PromptReco/151005_224926/0000 $1/JetHT_Run2015D-PromptReco/ --par 4 --run
mkdir -p $1/TTJets_madgraph
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_madgraph/151005_224947/0000 $1/TTJets_madgraph/ --par 4 --run
mkdir -p $1/TTJets_HT-800to1200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-800to1200/151005_225004/0000 $1/TTJets_HT-800to1200/ --par 4 --run
mkdir -p $1/TTWJetsToLNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTWJetsToLNu/151005_225020/0000 $1/TTWJetsToLNu/ --par 4 --run
mkdir -p $1/QCD_HT200to300
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300/151005_225037/0000 $1/QCD_HT200to300/ --par 4 --run
mkdir -p $1/QCD_HT300to500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500/151005_225054/0000 $1/QCD_HT300to500/ --par 4 --run
mkdir -p $1/ZZTo4Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZTo4Q_13TeV_amcatnloFXFX_madspin_pythia8/crab_ZZTo4Q/151005_225110/0000 $1/ZZTo4Q/ --par 4 --run
mkdir -p $1/TT_powheg_pythia6
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneZ2star_13TeV-powheg-pythia6-tauola/crab_TT_powheg_pythia6/151005_225128/0000 $1/TT_powheg_pythia6/ --par 4 --run
mkdir -p $1/TTJets_HT-600to800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-600to800/151005_225146/0000 $1/TTJets_HT-600to800/ --par 4 --run
mkdir -p $1/ST_tW_antitop_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_antitop_5f_inclusiveDecays/151005_225204/0000 $1/ST_tW_antitop_5f_inclusiveDecays/ --par 4 --run
mkdir -p $1/WZTo2L2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/crab_WZTo2L2Q/151005_225220/0000 $1/WZTo2L2Q/ --par 4 --run
mkdir -p $1/ZZTo2L2Q
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/crab_ZZTo2L2Q/151005_225237/0000 $1/ZZTo2L2Q/ --par 4 --run
mkdir -p $1/QCD_HT100to200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT100to200/151005_225259/0000 $1/QCD_HT100to200/ --par 4 --run
