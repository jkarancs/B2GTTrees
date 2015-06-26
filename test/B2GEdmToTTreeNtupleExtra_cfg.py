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

options.register('globalTag',
                 '',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'GlobalTag (empty = auto)')

options.parseArguments()

process = cms.Process("b2gAnalysisTTrees")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('HLTrigReport')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
if options.globalTag != '':
    process.GlobalTag.globaltag = options.globalTag
else:
    from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag
    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'auto:run2_mc')
    process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
    process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
    print "Automatically selected GlobalTag: "+str(process.GlobalTag.globaltag)

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
from Analysis.B2GAnaFW.b2gedmntuples_cff import met, genPart, electrons, muons, jetsAK4, jetsAK8, subjetsAK8, subjetsCmsTopTag, eventInfo

process.extraVar = cms.EDProducer("B2GEdmExtraVarProducer",
    electrons_label = cms.untracked.string("electrons"),
    electrons_prefix = electrons.prefix,
    muons_label = cms.untracked.string("muons"),
    muons_prefix = muons.prefix,
    met_label = cms.untracked.string("met"),
    met_prefix = met.prefix,
    AK8Jets_label = cms.untracked.string("jetsAK8"),
    AK8Jets_prefix = jetsAK8.prefix,
    singleI = cms.untracked.vstring(
        "NLep",
        "NTopHad",
        "NTopLep",
        "NTop",
        # Add trigger names below (these are automatically picked up)
        # Hadronic
        "HLT_AK8PFJet360_TrimMass30",
        "HLT_PFJet450",
        "HLT_PFJet500",
        "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",
        "HLT_PFHT750_4Jet",
        "HLT_PFHT750_4JetPt50",
        "HLT_ECALHT800",
        "HLT_PFHT800",
        "HLT_PFHT900",
        # Hadronic - Prescaled Auxilary
        "HLT_PFHT350",
        "HLT_PFHT400",
        "HLT_PFHT475",
        "HLT_PFHT600",
        "HLT_PFHT650",
        "HLT_PFHT550_4Jet",
        "HLT_PFHT650_4Jet",
        # Razor
        "HLT_Rsq0p25",
        "HLT_Rsq0p30",
        "HLT_RsqMR240_Rsq0p09_MR200_4jet",
        "HLT_RsqMR240_Rsq0p09_MR200",
        "HLT_RsqMR270_Rsq0p09_MR200_4jet",
        "HLT_RsqMR270_Rsq0p09_MR200",
        # Lepton + B-tag
        "HLT_Mu10_CentralPFJet30_BTagCSV0p5PF",
        "HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p5PF",
        "HLT_Ele15_IsoVVVL_BTagtop8CSV07_PFHT400",
        "HLT_Ele15_IsoVVVL_PFHT600",
        "HLT_Ele15_PFHT300",
        "HLT_Mu15_IsoVVVL_BTagCSV07_PFHT400",
        "HLT_Mu15_IsoVVVL_PFHT600",
        "HLT_Mu15_PFHT300",
        # Lepton - Non-isolated
        "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50",
        "HLT_Mu40_eta2p1_PFJet200_PFJet50",
        "HLT_Mu45_eta2p1",
        "HLT_Mu50",
        # Lepton - Isolated
        "HLT_Ele32_eta2p1_WPLoose_Gsf",
        "HLT_Ele32_eta2p1_WPTight_Gsf",
        "HLT_IsoMu24_eta2p1",
        "HLT_IsoMu27",
        "HLT_IsoTkMu24_eta2p1",
        "HLT_IsoTkMu27",
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
    trigger_names = cms.untracked.vstring(
        )
    )

### Filter - Select only events with at least 1 AK8 jet with pt>300
# Filter for MiniAOD Jet collections
#process.PtMinAK8JetCountFilter = cms.EDFilter("PatJetCountFilter", # This one works on MiniAOD
#    src = cms.InputTag("slimmedJetsAK8"),
#    filter = cms.bool(True),
#    cut = cms.string("pt>300"),
#    minNumber = cms.uint32(1)
#    )

# Filter For Edm ntuple - Use this here
process.EdmNtupleCountFilter = cms.EDFilter("EdmNtupleCountFilter", # This one works on EdmNtuple
    src = cms.InputTag("jetsAK8","jetAK8Pt"),
    filter = cms.bool(True), # False also filters for some reason (disable in Path instead)
    min = cms.double(350),
    minNumber = cms.uint32(1)
    )

### B2GTTreeMaker
process.load("Analysis.B2GTTrees.B2GTTreeMaker_cff")
# Adding extra Variables
process.B2GTTreeMaker.physicsObjects.append(
    cms.PSet(
        label = cms.untracked.string("extraVar"),
        prefix_in = cms.untracked.string(""),
        prefix_out = cms.untracked.string("evt_"),
        maxInstances = cms.untracked.int32(1),
        singleI = process.extraVar.singleI,
        singleF = process.extraVar.singleF,
        ),
    )

process.edmNtuplesOut = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(options.outputLabel),
    outputCommands = cms.untracked.vstring(
        "keep *",
        ),
    dropMetaData = cms.untracked.string('ALL'),
    )

process.analysisPath = cms.Path(
    process.extraVar *
    process.EdmNtupleCountFilter *
    process.B2GTTreeMaker
    )

#process.endPath = cms.EndPath( process.edmNtuplesOut )

