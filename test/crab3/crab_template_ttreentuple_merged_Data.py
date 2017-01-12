from WMCore.Configuration import Configuration
config = Configuration()
import os
b2gana_test_dir = os.environ['CMSSW_BASE']+'/src/Analysis/B2GAnaFW/test/'

# Input .db and .txt files for JEC/JER
import glob
input_files = glob.glob(b2gana_test_dir+'JECs/JEC_ERA*')
input_files.append('XSEC_FILE')

config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = True
config.General.requestName = 'REQNAME'
config.General.workArea = 'TASKDIR'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = os.environ['CMSSW_BASE']+'/src/Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py'
config.JobType.pyCfgParams = ['DataProcessing=DATAPROC', 'wantSummary=False', 'outputLabel=B2GTTreeNtupleExtra.root']
config.JobType.inputFiles = input_files
config.JobType.sendExternalFolder = True

config.section_('Data')
config.Data.outLFNDirBase = 'SE_USERDIR'
config.Data.inputDataset = 'DATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
config.Data.outputDatasetTag = 'PUBNAME' # outLFNDirBase/primary_dataset/outputDatasetTag/timestamp/000X/

config.Data.lumiMask = 'JSON'
config.Data.runRange = 'RUNS'

config.section_('Site')
config.Site.storageSite = 'SE_SITE'
