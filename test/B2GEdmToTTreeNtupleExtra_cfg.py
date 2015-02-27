### *****************************************************************************************
### Usage:
###
### cmsRun B2GEdmtExtraToTTreeNtuple_cfg.py maxEvts=N sample="file:sample.root" outputLabel="myoutput.root"
###
### Default values for the options are set:
### maxEvts     = -1
### sample      = 'file:B2GEDMNtupleExtra.root'
### outputLabel = 'B2GTTreeNtuple.root'
### *****************************************************************************************
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts

options = opts.VarParsing('analysis')

options.register('maxEvts',
                 -1,# default value: process all events
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int,
                 'Number of events to process')

options.register('sample',
                 'file:B2GEDMNtuple.root',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Sample to analyze')

options.register('outputLabel',
                 'B2GTTreeNtupleExtra.root',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Output label')

options.parseArguments()

process = cms.Process("b2gAnalysisTTrees")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('HLTrigReport')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag
process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'auto:startup_GRun')
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
for pset in process.GlobalTag.toGet.value():
    pset.connect = pset.connect.value().replace('frontier://FrontierProd/', 'frontier://FrontierProd/')
    #   Fix for multi-run processing:
    process.GlobalTag.RefreshEachRun = cms.untracked.bool( False )
    process.GlobalTag.ReconnectEachRun = cms.untracked.bool( False )

### Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
### Number of maximum events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvts) )
### Source file
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.sample)
)
### Output file
process.TFileService = cms.Service("TFileService", fileName = cms.string(options.outputLabel))

### B2GEdmExtraVarProducer
process.extraVar = cms.EDProducer("B2GEdmExtraVarProducer",
    electrons_label = cms.string("electrons"),
    electrons_prefix = cms.string("el"),
    muons_label = cms.string("muons"),
    muons_prefix = cms.string("mu"),
    met_label = cms.string("met"),
    met_prefix = cms.string("met"),
    AK8Jets_label = cms.string("jetsAK8"),
    AK8Jets_prefix = cms.string("jetAK8"),
    singleI = cms.untracked.vstring(
        "NLep",
        "NTopHad",
        "NTopLep",
        "NTop",
        ),
    singleF = cms.untracked.vstring(
        "HtLep",
        "HtTop",
        "Ht",
        "HtAll",
        "HtEx",
        "HtExFr",
        "HtTopFr",
        "TTHadDR",
        "TTHadDPhi",
        "TTHadDEta",
        "TTHadMass",
        "TTHadPz",
        "TTHadHz",
        "TTHadDPz",
        "TTHadMR",
        "TTHadMTR",
        "TTHadR",
        "TTHadR2",
        "MR",
        "MTR",
        "R",
        "R2",
        ),
    )

### B2GTTreeMaker
process.load("Analysis.B2GTTrees.B2GTTreeMaker_cff")
# Adding extra Variables
process.B2GTTreeMaker.physicsObjects.append(
    cms.PSet(
        label = cms.string("extraVar"),
        prefix_in = cms.string(""),
        prefix_out = cms.string("evt_"),
        maxInstances = cms.untracked.int32(1),
        singleI = process.extraVar.singleI,
        singleF = process.extraVar.singleF,
        ),
    )



process.edmNtuplesOut = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('B2GEDMNtupleExtra.root'),
    outputCommands = cms.untracked.vstring(
        "keep *",
        ),
    dropMetaData = cms.untracked.string('ALL'),
    )

process.analysisPath = cms.Path(
    process.extraVar
    * process.B2GTTreeMaker
    )

#process.endPath = cms.EndPath( process.edmNtuplesOut )

