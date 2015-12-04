if ( $#argv < 1 ) echo "Please specify directory where you want to download files"
alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*"
alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*"

mkdir -p $1/JetHT_50ns_2015B
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_50ns_2015B/151116_135004/0000 $1/JetHT_50ns_2015B --par 4 --run
mkdir -p $1/JetHT_50ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_50ns_2015C/151116_140429/0000 $1/JetHT_50ns_2015C --par 4 --run
mkdir -p $1/JetHT_25ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_25ns_2015C/151116_140600/0000 $1/JetHT_25ns_2015C --par 4 --run
mkdir -p $1/JetHT_25ns_2015D_reMiniAOD
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_25ns_2015D_reMiniAOD/151116_140719/0000 $1/JetHT_25ns_2015D_reMiniAOD --par 4 --run
mkdir -p $1/JetHT_25ns_2015D_Promptv4
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/JetHT/crab_JetHT_25ns_2015D_Promptv4/151116_140918/0000 $1/JetHT_25ns_2015D_Promptv4 --par 4 --run
mkdir -p $1/MET_50ns_2015B
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/MET/crab_MET_50ns_2015B/151116_141109/0000 $1/MET_50ns_2015B --par 4 --run
mkdir -p $1/MET_50ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/MET/crab_MET_50ns_2015C/151116_141402/0000 $1/MET_50ns_2015C --par 4 --run
mkdir -p $1/MET_25ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/MET/crab_MET_25ns_2015C/151116_141534/0000 $1/MET_25ns_2015C --par 4 --run
mkdir -p $1/MET_25ns_2015D_reMiniAOD
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/MET/crab_MET_25ns_2015D_reMiniAOD/151116_141731/0000 $1/MET_25ns_2015D_reMiniAOD --par 4 --run
mkdir -p $1/MET_25ns_2015D_Promptv4
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/MET/crab_MET_25ns_2015D_Promptv4/151116_141858/0000 $1/MET_25ns_2015D_Promptv4 --par 4 --run
mkdir -p $1/SingleElectron_50ns_2015B
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_50ns_2015B/151116_142025/0000 $1/SingleElectron_50ns_2015B --par 4 --run
mkdir -p $1/SingleElectron_50ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_50ns_2015C/151116_142145/0000 $1/SingleElectron_50ns_2015C --par 4 --run
mkdir -p $1/SingleElectron_25ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_25ns_2015C/151116_142517/0000 $1/SingleElectron_25ns_2015C --par 4 --run
mkdir -p $1/SingleElectron_25ns_2015D_reMiniAOD
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_25ns_2015D_reMiniAOD/151116_142636/0000 $1/SingleElectron_25ns_2015D_reMiniAOD --par 4 --run
mkdir -p $1/SingleElectron_25ns_2015D_Promptv4
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleElectron/crab_SingleElectron_25ns_2015D_Promptv4/151116_142757/0000 $1/SingleElectron_25ns_2015D_Promptv4 --par 4 --run
mkdir -p $1/SingleMuon_50ns_2015B
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_50ns_2015B/151116_142917/0000 $1/SingleMuon_50ns_2015B --par 4 --run
mkdir -p $1/SingleMuon_50ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_50ns_2015C/151116_143038/0000 $1/SingleMuon_50ns_2015C --par 4 --run
mkdir -p $1/SingleMuon_25ns_2015C
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_25ns_2015C/151116_143158/0000 $1/SingleMuon_25ns_2015C --par 4 --run
mkdir -p $1/SingleMuon_25ns_2015D_reMiniAOD
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_25ns_2015D_reMiniAOD/151116_143321/0000 $1/SingleMuon_25ns_2015D_reMiniAOD --par 4 --run
mkdir -p $1/SingleMuon_25ns_2015D_Promptv4
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SingleMuon/crab_SingleMuon_25ns_2015D_Promptv4/151116_143441/0000 $1/SingleMuon_25ns_2015D_Promptv4 --par 4 --run
mkdir -p $1/T1tttt_mGluino-625_mLSP-275to375
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-625_mLSP-275to375_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-625_mLSP-275to375/151116_140011/0000 $1/T1tttt_mGluino-625_mLSP-275to375 --par 4 --run
mkdir -p $1/T1tttt_mGluino-625to650_mLSP-200to400
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-625to650_mLSP-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-625to650_mLSP-200to400/151116_143601/0000 $1/T1tttt_mGluino-625to650_mLSP-200to400 --par 4 --run
mkdir -p $1/T1tttt_mGluino-650to675_mLSP-250to425
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-650to675_mLSP-250to425_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-650to675_mLSP-250to425/151116_143721/0000 $1/T1tttt_mGluino-650to675_mLSP-250to425 --par 4 --run
mkdir -p $1/T1tttt_mGluino-700_mLSP-1to450
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-700_mLSP-1to450_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-700_mLSP-1to450/151116_143841/0000 $1/T1tttt_mGluino-700_mLSP-1to450 --par 4 --run
mkdir -p $1/T1tttt_mGluino-700to750_mLSP-200to500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-700to750_mLSP-200to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-700to750_mLSP-200to500/151116_144003/0000 $1/T1tttt_mGluino-700to750_mLSP-200to500 --par 4 --run
mkdir -p $1/T1tttt_mGluino-750to775_mLSP-350to525
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-750to775_mLSP-350to525_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-750to775_mLSP-350to525/151116_144123/0000 $1/T1tttt_mGluino-750to775_mLSP-350to525 --par 4 --run
mkdir -p $1/T1tttt_mGluino-775_mLSP-475to550
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-775_mLSP-475to550_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-775_mLSP-475to550/151116_144243/0000 $1/T1tttt_mGluino-775_mLSP-475to550 --par 4 --run
mkdir -p $1/T1tttt_mGluino-800to825_mLSP-1to575
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-800to825_mLSP-1to575_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-800to825_mLSP-1to575/151116_144613/0000 $1/T1tttt_mGluino-800to825_mLSP-1to575 --par 4 --run
mkdir -p $1/T1tttt_mGluino-825to850_mLSP-200to600
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-825to850_mLSP-200to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-825to850_mLSP-200to600/151116_144733/0000 $1/T1tttt_mGluino-825to850_mLSP-200to600 --par 4 --run
mkdir -p $1/T1tttt_mGluino-875to900_mLSP-1to650
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-875to900_mLSP-1to650_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-875to900_mLSP-1to650/151116_144853/0000 $1/T1tttt_mGluino-875to900_mLSP-1to650 --par 4 --run
mkdir -p $1/T1tttt_mGluino-950to975_mLSP-350to725
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-950to975_mLSP-350to725_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-950to975_mLSP-350to725/151116_145019/0000 $1/T1tttt_mGluino-950to975_mLSP-350to725 --par 4 --run
mkdir -p $1/T1tttt_mGluino-975_mLSP-600to750
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-975_mLSP-600to750_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-975_mLSP-600to750/151116_145140/0000 $1/T1tttt_mGluino-975_mLSP-600to750 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1100_mLSP-1to775
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1100_mLSP-1to775_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1100_mLSP-1to775/151116_145300/0000 $1/T1tttt_mGluino-1100_mLSP-1to775 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1100to1125_mLSP-700to900
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1100to1125_mLSP-700to900_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1100to1125_mLSP-700to900/151116_145420/0000 $1/T1tttt_mGluino-1100to1125_mLSP-700to900 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1150_mLSP-1to800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1150_mLSP-1to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1150_mLSP-1to800/151116_145540/0000 $1/T1tttt_mGluino-1150_mLSP-1to800 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1150to1175_mLSP-750to925
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1150to1175_mLSP-750to925_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1150to1175_mLSP-750to925/151116_145701/0000 $1/T1tttt_mGluino-1150to1175_mLSP-750to925 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1175_mLSP-950
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1175_mLSP-950_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1175_mLSP-950/151116_145821/0000 $1/T1tttt_mGluino-1175_mLSP-950 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1200_mLSP-1to825
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1200_mLSP-1to825_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1200_mLSP-1to825/151116_145940/0000 $1/T1tttt_mGluino-1200_mLSP-1to825 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1200to1225_mLSP-800to1000
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1200to1225_mLSP-800to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1200to1225_mLSP-800to1000/151116_150100/0000 $1/T1tttt_mGluino-1200to1225_mLSP-800to1000 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1275_mLSP-900to975
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1275_mLSP-900to975_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1275_mLSP-900to975/151116_150219/0000 $1/T1tttt_mGluino-1275_mLSP-900to975 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1300to1325_mLSP-700to1100
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1300to1325_mLSP-700to1100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1300to1325_mLSP-700to1100/151116_150340/0000 $1/T1tttt_mGluino-1300to1325_mLSP-700to1100 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1350to1375_mLSP-50to1025
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1350to1375_mLSP-50to1025_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1350to1375_mLSP-50to1025/151116_150500/0000 $1/T1tttt_mGluino-1350to1375_mLSP-50to1025 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1400_mLSP-1to1175
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1400_mLSP-1to1175_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1400_mLSP-1to1175/151116_150622/0000 $1/T1tttt_mGluino-1400_mLSP-1to1175 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1450to1475_mLSP-50to1075
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1450to1475_mLSP-50to1075_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1450to1475_mLSP-50to1075/151116_150744/0000 $1/T1tttt_mGluino-1450to1475_mLSP-50to1075 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1475to1500_mLSP-1to1250
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1475to1500_mLSP-1to1250_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1475to1500_mLSP-1to1250/151116_150904/0000 $1/T1tttt_mGluino-1475to1500_mLSP-1to1250 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1500to1525_mLSP-50to1125
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1500to1525_mLSP-50to1125_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1500to1525_mLSP-50to1125/151116_151024/0000 $1/T1tttt_mGluino-1500to1525_mLSP-50to1125 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1525to1550_mLSP-1to1300
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1525to1550_mLSP-1to1300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1525to1550_mLSP-1to1300/151116_151146/0000 $1/T1tttt_mGluino-1525to1550_mLSP-1to1300 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1600to1650_mLSP-1to1350
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1600to1650_mLSP-1to1350_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1600to1650_mLSP-1to1350/151116_151305/0000 $1/T1tttt_mGluino-1600to1650_mLSP-1to1350 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1700to1750_mLSP-1to1450
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1700to1750_mLSP-1to1450_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1700to1750_mLSP-1to1450/151116_151426/0000 $1/T1tttt_mGluino-1700to1750_mLSP-1to1450 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1800to1850_mLSP-1to1450
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1800to1850_mLSP-1to1450_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1800to1850_mLSP-1to1450/151116_151546/0000 $1/T1tttt_mGluino-1800to1850_mLSP-1to1450 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1850to1900_mLSP-1to1450
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1850to1900_mLSP-1to1450_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1850to1900_mLSP-1to1450/151116_151731/0000 $1/T1tttt_mGluino-1850to1900_mLSP-1to1450 --par 4 --run
mkdir -p $1/T1tttt_mGluino-1950_mLSP-700to950
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1950_mLSP-700to950_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_mGluino-1950_mLSP-700to950/151116_151854/0000 $1/T1tttt_mGluino-1950_mLSP-700to950 --par 4 --run
mkdir -p $1/T1tttt_FullSim_mGluino-1500_mLSP-100
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/SMS-T1tttt_mGluino-1500_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_T1tttt_FullSim_mGluino-1500_mLSP-100/151116_152015/0000 $1/T1tttt_FullSim_mGluino-1500_mLSP-100 --par 4 --run
mkdir -p $1/TT_powheg_pythia8
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_powheg_pythia8/151116_152137/0000 $1/TT_powheg_pythia8 --par 4 --run
mkdir -p $1/TT_powheg_pythia8_ext
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_powheg_pythia8_ext/151116_152259/0000 $1/TT_powheg_pythia8_ext --par 4 --run
mkdir -p $1/TT_amcatnlo
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TT_amcatnlo/151116_152421/0000 $1/TT_amcatnlo --par 4 --run
mkdir -p $1/TT_herwigpp
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TT_TuneEE5C_13TeV-amcatnlo-herwigpp/crab_TT_herwigpp/151116_152541/0000 $1/TT_herwigpp --par 4 --run
mkdir -p $1/TTJets_madgraph
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_madgraph/151116_152701/0000 $1/TTJets_madgraph --par 4 --run
mkdir -p $1/TTJets_madgraph_FastSim
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_madgraph_FastSim/151116_152821/0000 $1/TTJets_madgraph_FastSim --par 4 --run
mkdir -p $1/TTJets_amcatnloFXFX
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_TTJets_amcatnloFXFX/151116_152941/0000 $1/TTJets_amcatnloFXFX --par 4 --run
mkdir -p $1/TTJets_HT-600to800
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-600to800/151116_153101/0000 $1/TTJets_HT-600to800 --par 4 --run
mkdir -p $1/TTJets_HT-800to1200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-800to1200/151116_153220/0000 $1/TTJets_HT-800to1200 --par 4 --run
mkdir -p $1/TTJets_HT-1200to2500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-1200to2500/151116_153341/0000 $1/TTJets_HT-1200to2500 --par 4 --run
mkdir -p $1/TTJets_HT-2500toInf
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets_HT-2500toInf/151116_153501/0000 $1/TTJets_HT-2500toInf --par 4 --run
mkdir -p $1/TTWJetsToLNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTWJetsToLNu/151116_153621/0000 $1/TTWJetsToLNu --par 4 --run
mkdir -p $1/TTWJetsToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTWJetsToQQ/151116_153741/0000 $1/TTWJetsToQQ --par 4 --run
mkdir -p $1/TTZToLLNuNu
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZToLLNuNu/151116_153901/0000 $1/TTZToLLNuNu --par 4 --run
mkdir -p $1/TTZToQQ
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/crab_TTZToQQ/151116_154022/0000 $1/TTZToQQ --par 4 --run
mkdir -p $1/ST_s-channel_4f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_s-channel_4f_leptonDecays/151116_154142/0000 $1/ST_s-channel_4f_leptonDecays --par 4 --run
mkdir -p $1/ST_t-channel_4f_leptonDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_t-channel_4f_leptonDecays/151116_154301/0000 $1/ST_t-channel_4f_leptonDecays --par 4 --run
mkdir -p $1/ST_t-channel_4f_leptonDecays_ext
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/crab_ST_t-channel_4f_leptonDecays_ext/151116_154422/0000 $1/ST_t-channel_4f_leptonDecays_ext --par 4 --run
mkdir -p $1/ST_tW_top_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_top_5f_inclusiveDecays/151116_154542/0000 $1/ST_tW_top_5f_inclusiveDecays --par 4 --run
mkdir -p $1/ST_tW_antitop_5f_inclusiveDecays
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/crab_ST_tW_antitop_5f_inclusiveDecays/151116_154704/0000 $1/ST_tW_antitop_5f_inclusiveDecays --par 4 --run
mkdir -p $1/QCD_HT100to200
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT100to200/151116_154825/0000 $1/QCD_HT100to200 --par 4 --run
mkdir -p $1/QCD_HT200to300
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300/151116_154945/0000 $1/QCD_HT200to300 --par 4 --run
mkdir -p $1/QCD_HT300to500
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500/151116_155105/0000 $1/QCD_HT300to500 --par 4 --run
mkdir -p $1/QCD_HT500to700
se dl_mis T2_HU_Budapest:/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700/151116_155225/0000 $1/QCD_HT500to700 --par 4 --run
mkdir -p $1/QCD_HT700to1000
