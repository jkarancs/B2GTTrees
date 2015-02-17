from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
config.General.requestName = 'edmntuple_test'
#config.General.workArea = '<workarea>' # --> <workarea>/crab_'config.General.requestName'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../../../../Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py'
config.JobType.pyCfgParams = ['isData=False', 'maxEvts=-1', 'LHE=False']

config.section_('Data')
config.Data.outLFN = '/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple'
config.Data.inputDataset = '/TT_Tune4C_13TeV-pythia8-tauola/Phys14DR-PU40bx25_tsg_PHYS14_25_V1-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#config.Data.totalUnits = 1
config.Data.publication = False
#config.Data.publishDataName = 'PUBNAME'

config.section_('Site')
config.Site.storageSite = 'T2_HU_Budapest'
