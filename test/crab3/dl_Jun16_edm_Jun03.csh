if ( $#argv < 1 ) echo "Please specify directory where you want to download files"
alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*"
alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*"

mkdir -p $1/TTJets_amcatnloFXFX-pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_TTJets_amcatnloFXFX-pythia8/150616_082626/0000 $1/TTJets_amcatnloFXFX-pythia8/ --par 4 --run
mkdir -p $1/TTJets_madgraphMLM-pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_madgraphMLM-pythia8/150616_082744/0000 $1/TTJets_madgraphMLM-pythia8/ --par 4 --run
mkdir -p $1/TT_TuneCUETP8M1_pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M1_pythia8/150616_082903/0000 $1/TT_TuneCUETP8M1_pythia8/ --par 4 --run
mkdir -p $1/TT_TuneZ2star_powheg-pythia6-tauola
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneZ2star_13TeV-powheg-pythia6-tauola/crab_TT_TuneZ2star_powheg-pythia6-tauola/150616_083018/0000 $1/TT_TuneZ2star_powheg-pythia6-tauola/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-100To200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-100To200/150616_083203/0000 $1/WJetsToLNu_HT-100To200/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-200To400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-200To400/150616_083342/0000 $1/WJetsToLNu_HT-200To400/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-400To600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-400To600/150616_083536/0000 $1/WJetsToLNu_HT-400To600/ --par 4 --run
mkdir -p $1/WJetsToLNu_HT-600ToInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-600ToInf/150616_083617/0000 $1/WJetsToLNu_HT-600ToInf/ --par 4 --run
mkdir -p $1/WW
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW/150616_083731/0000 $1/WW/ --par 4 --run
mkdir -p $1/WZ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ/150616_083848/0000 $1/WZ/ --par 4 --run
mkdir -p $1/ZZ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ/150616_084623/0000 $1/ZZ/ --par 4 --run
mkdir -p $1/ST_tW_top_5f_DS_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_top_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_top_5f_DS_inclusiveDecays/150617_080523/0000 $1/ST_tW_top_5f_DS_inclusiveDecays/ --par 4 --run
mkdir -p $1/ST_tW_antitop_5f_DS_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_antitop_5f_DS_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_antitop_5f_DS_inclusiveDecays/150617_080658/0000 $1/ST_tW_antitop_5f_DS_inclusiveDecays/ --par 4 --run
mkdir -p $1/ST_t-channel_5f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_t-channel_5f_leptonDecays/150618_090340/0000 $1/ST_t-channel_5f_leptonDecays/ --par 4 --run
mkdir -p $1/ST_s-channel_4f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_s-channel_4f_leptonDecays/150618_105051/0000 $1/ST_s-channel_4f_leptonDecays/ --par 4 --run
