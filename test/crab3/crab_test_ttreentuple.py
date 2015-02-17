from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
config.General.requestName = 'ttreentuple_test'
#config.General.workArea = '<workarea>' # --> <workarea>/crab_'config.General.requestName'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../B2GEdmToTTreeNtupleExtra_cfg.py'


config.section_('Data')
config.Data.outLFN = '/store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple'
config.Data.inputDataset = '/TT_Tune4C_13TeV-pythia8-tauola/jkarancs-B2G_edm_Feb04-8e5d8108d1aad8511a8e2735e858f518/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 5
config.Data.publication = False

config.section_('Site')
config.Site.storageSite = 'T2_HU_Budapest'
