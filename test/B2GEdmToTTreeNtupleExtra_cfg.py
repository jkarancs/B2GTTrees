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
import os

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

options.register('isData',
                 True,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.bool,
                 'Is data?')

#options.register('globalTag',
#                 '',
#                 opts.VarParsing.multiplicity.singleton,
#                 opts.VarParsing.varType.string,
#                 'GlobalTag (empty = auto)')

options.register('xsec',
                 0,# default value: 0
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.float,
                 'Cross section (with k-factor applied, in units of pb)')

options.register('nevent',
                 0,# default value: 0
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.float,
                 'Number of events (corrected for neg weights)')

options.register('lumiWeight',
                 1,# default value: 1
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.float,
                 'Event weight = (xsec*k_factor)*lumi(1fb^-1)/(num_event(neg weight corr))')

options.register('JECloc',
                 os.environ['CMSSW_BASE']+'/src/Analysis/B2GTTrees/JECs/Summer15_25nsV2_DATA',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Directory, where the JEC text files are lcoated')

options.register('lheLabel',
                 "",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'LHE module label, MC sample specific. Can be: externalLHEProducer')

options.parseArguments()

process = cms.Process("b2gAnalysisTTrees")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('HLTrigReport')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#if options.globalTag != '':
#    process.GlobalTag.globaltag = options.globalTag
#else:
#    from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag
#    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'auto:run2_mc')
#    print "Automatically selected GlobalTag: "+str(process.GlobalTag.globaltag)

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
from Analysis.B2GAnaFW.b2gedmntuples_cff import metNoHF, genPart, electrons, muons, jetsAK4, jetsAK8, subjetsAK8, subjetsCmsTopTag, eventInfo

process.extraVar = cms.EDProducer("B2GEdmExtraVarProducer",
    isData = cms.untracked.bool(options.isData),
    JEC_location = cms.untracked.string(options.JECloc),
    cross_section = cms.untracked.double(options.xsec),
    num_events = cms.untracked.double(options.nevent),
    lumi_weight = cms.untracked.double(options.lumiWeight),
    lhe_label = cms.untracked.string(options.lheLabel),
    filter_label = cms.untracked.string("METUserData"),
    trigger_label = cms.untracked.string("TriggerUserData"),
    evt_label = cms.untracked.string("eventUserData"),
    evt_prefix = cms.untracked.string(""),
    vtx_label = cms.untracked.string("vertexInfo"),
    vtx_prefix = cms.untracked.string(""),
    met_label = cms.untracked.string("metNoHF"), # This now excludes HF (07 Aug 2015 recommendation)
    met_prefix = metNoHF.prefix,
    gen_label = cms.untracked.string("genPart"),
    gen_prefix = genPart.prefix,
    electrons_label = cms.untracked.string("electrons"),
    electrons_prefix = electrons.prefix,
    muons_label = cms.untracked.string("muons"),
    muons_prefix = muons.prefix,
    AK4Jets_label = cms.untracked.string("jetsAK4"),
    AK4Jets_prefix = jetsAK4.prefix,
    AK8Jets_label = cms.untracked.string("jetsAK8"),
    AK8Jets_prefix = jetsAK8.prefix,
    AK8Subjets_label = cms.untracked.string("subjetsAK8"),
    AK8Subjets_prefix = subjetsAK8.prefix,
    CmsTTSubjets_label = cms.untracked.string("subjetsCmsTopTag"),
    CmsTTSubjets_prefix = subjetsCmsTopTag.prefix,
    AK4JetKeys_label = cms.untracked.string("jetKeysAK4"),
    AK8JetKeys_label = cms.untracked.string("jetKeysAK8"),
    AK8SubjetKeys_label = cms.untracked.string("subjetKeysAK8"),
    CmsTTSubjetKeys_label = cms.untracked.string("subjetsCmsTopTagKeys"),
    singleI = cms.untracked.vstring(
        # Event filters (these are automatically picked up)
        "Flag_trackingFailureFilter",
        "Flag_goodVertices",
        "Flag_CSCTightHaloFilter",
        "Flag_trkPOGFilters",
        "Flag_trkPOG_logErrorTooManyClusters",
        "Flag_EcalDeadCellTriggerPrimitiveFilter",
        "Flag_ecalLaserCorrFilter",
        "Flag_trkPOG_manystripclus53X",
        "Flag_eeBadScFilter",
        "Flag_METFilters",
        "Flag_HBHENoiseFilter",
        "Flag_trkPOG_toomanystripclus53X",
        "Flag_hcalLaserEventFilter",
        # Add trigger names below (these are automatically picked up)
        # Hadronic
        "HLT_AK8PFJet360_TrimMass30",
        "HLT_PFJet40",
        "HLT_PFJet60",
        "HLT_PFJet80",
        "HLT_PFJet140",
        "HLT_PFJet200",
        "HLT_PFJet260",
        "HLT_PFJet320",
        "HLT_PFJet400",
        "HLT_PFJet450",
        "HLT_PFJet500",
        "HLT_DiPFJetAve40",
        "HLT_DiPFJetAve60",
        "HLT_DiPFJetAve80",
        "HLT_DiPFJetAve140",
        "HLT_DiPFJetAve200",
        "HLT_DiPFJetAve260",
        "HLT_DiPFJetAve320",
        "HLT_DiPFJetAve400",
        "HLT_DiPFJetAve500",
        "HLT_DiPFJetAve60_HFJEC",
        "HLT_DiPFJetAve80_HFJEC",
        "HLT_DiPFJetAve100_HFJEC",
        "HLT_DiPFJetAve160_HFJEC",
        "HLT_DiPFJetAve220_HFJEC",
        "HLT_DiPFJetAve300_HFJEC",
        "HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV0p45",
        "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p45",
        "HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45",
        "HLT_AK8PFHT650_TrimR0p1PT0p03Mass50",
        "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",
        "HLT_PFHT550_4Jet",
        "HLT_PFHT650_4Jet",
        "HLT_PFHT750_4Jet",
        "HLT_PFHT750_4JetPt50",
        "HLT_ECALHT800",
        "HLT_PFHT600",
        "HLT_PFHT650",
        "HLT_PFHT800",
        "HLT_PFHT900",
        "HLT_PFHT200",
        "HLT_PFHT250",
        "HLT_PFHT300",
        "HLT_PFHT350",
        "HLT_PFHT400",
        "HLT_PFHT475",
        # Razor
        "HLT_Rsq0p25",
        "HLT_Rsq0p30",
        "HLT_RsqMR240_Rsq0p09_MR200_4jet",
        "HLT_RsqMR240_Rsq0p09_MR200",
        "HLT_RsqMR270_Rsq0p09_MR200_4jet",
        "HLT_RsqMR270_Rsq0p09_MR200",
        # Lepton + Jet
        "HLT_Mu40_eta2p1_PFJet200_PFJet50",
        "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50",
        "HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele12_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele18_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele33_CaloIdM_TrackIdM_PFJet30",
        "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v1",
        # Lepton + B-tag
        "HLT_Mu10_CentralPFJet30_BTagCSV0p5PF",
        "HLT_Mu10_CentralPFJet30_BTagCSV0p54PF",
        "HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p5PF",
        "HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV0p54PF",
        "HLT_Ele15_IsoVVVL_BTagtop8CSV07_PFHT400",
        "HLT_Ele15_IsoVVVL_BTagCSV0p72_PFHT400",
        "HLT_Ele15_IsoVVVL_PFHT600",
        "HLT_Ele15_PFHT300",
        "HLT_Mu15_IsoVVVL_BTagCSV07_PFHT400",
        "HLT_Mu15_IsoVVVL_BTagCSV0p72_PFHT400",
        "HLT_Mu15_IsoVVVL_PFHT600",
        "HLT_Mu15_PFHT300",
        # Lepton - Non-isolated
        "HLT_Mu8",
        "HLT_Mu17",
        "HLT_Mu20",
        "HLT_Mu24",
        "HLT_Mu24_eta2p1",
        "HLT_Mu27",
        "HLT_Mu34",
        "HLT_Mu45_eta2p1",
        "HLT_Mu50",
        "HLT_Mu55",
        "HLT_Mu300",
        "HLT_Mu350",
        "HLT_TkMu20",
        "HLT_TkMu24_eta2p1",
        "HLT_TkMu27",
        "HLT_Ele105_CaloIdVT_GsfTrkIdT",
        "HLT_Ele115_CaloIdVT_GsfTrkIdT",
        # Lepton - Isolated
        "HLT_IsoMu17_eta2p1",
        "HLT_IsoMu20",
        "HLT_IsoMu20_eta2p1",
        "HLT_IsoMu24_eta2p1",
        "HLT_IsoMu27",
        "HLT_IsoTkMu24_eta2p1",
        "HLT_IsoTkMu27",
        "HLT_Mu8_TrkIsoVVL",
        "HLT_Mu17_TrkIsoVVL",
        "HLT_Mu24_TrkIsoVVL",
        "HLT_Mu34_TrkIsoVVL",
        "HLT_Ele22_eta2p1_WPLoose_Gsf",
        "HLT_Ele22_eta2p1_WPTight_Gsf",
        "HLT_Ele27_eta2p1_WPLoose_Gsf",
        "HLT_Ele27_eta2p1_WPTight_Gsf",
        "HLT_Ele32_eta2p1_WPLoose_Gsf",
        "HLT_Ele32_eta2p1_WPTight_Gsf",
        "HLT_Ele12_CaloIdL_TrackIdL_IsoVL",
        "HLT_Ele17_CaloIdL_TrackIdL_IsoVL",
        "HLT_Ele23_CaloIdL_TrackIdL_IsoVL",
        # event variables
        "evt_NGoodVtx",
        "evt_NLep",
        "evt_NTopHad",
        "evt_NTopHadPreTag",
        "evt_NTopLep",
        "evt_NTop",
        "evt_LHA_PDF_ID",
    ),
    singleF = cms.untracked.vstring(
        "evt_HtLep",
        "evt_HtTop",
        "evt_Ht",
        "evt_HtAll",
        "evt_HtEx",
        "evt_HtExFr",
        "evt_HtTopFr",
        "evt_TTHadDR",
        "evt_TTHadDPhi",
        "evt_TTHadDEta",
        "evt_TTHadMass",
        "evt_TTHadSumPt",
        "evt_TTHadPz",
        "evt_TTHadHz",
        "evt_TTHadDPz",
        "evt_TTHadMR",
        "evt_TTHadMTR",
        "evt_TTHadR",
        "evt_TTHadR2",
        "evt_MR",
        "evt_MTR",
        "evt_R",
        "evt_R2",
        "evt_AK4_MR",
        "evt_AK4_MTR",
        "evt_AK4_R",
        "evt_AK4_R2",
        "evt_XSec",
        "evt_NEvent_Corr",
        "evt_Lumi_Weight",
        "evt_Gen_Weight",
        "SUSY_Gluino_Mass",
        "SUSY_LSP_Mass",
    ),
    vectorI = cms.untracked.vstring(
        "gen_ID",
        "gen_Status",
        "gen_Mom0ID",
        "gen_Mom0Status",
        "gen_Mom1ID",
        "gen_Mom1Status",
        "gen_Dau0ID",
        "gen_Dau0Status",
        "gen_Dau1ID",
        "gen_Dau1Status",
        "jetAK8_HasNearGenTop",
        "jetAK8_NearGenTopIsHadronic",
        "jetAK8_NearGenWIsHadronic",
        "jetAK8_NearGenWToENu",
        "jetAK8_NearGenWToMuNu",
        "jetAK8_NearGenWToTauNu",
        "jetAK8_PassTopTag",
        "el_IsPartOfNearAK4Jet",
        "el_IsPartOfNearAK8Jet",
        "el_IsPartOfNearSubjet",
        "mu_IsPartOfNearAK4Jet",
        "mu_IsPartOfNearAK8Jet",
        "mu_IsPartOfNearSubjet",
    ),
    vectorF = cms.untracked.vstring(
        "scale_Weights",
        "pdf_Weights",
        "alphas_Weights",
        "gen_Pt",
        "gen_Eta",
        "gen_Phi",
        "gen_E",
        "gen_Mass",
        "gen_Charge",
        "jetAK8_DRNearGenTop",
        "jetAK8_DRNearGenWFromTop",
        "jetAK8_DRNearGenBFromTop",
        "jetAK8_DRNearGenLepFromSLTop",
        "jetAK8_DRNearGenNuFromSLTop",
        "jetAK8_PtNearGenTop",
        "jetAK8_PtNearGenBFromTop",
        "jetAK8_PtNearGenWFromTop",
        "jetAK8_PtNearGenLepFromSLTop",
        "jetAK8_PtNearGenNuFromSLTop",
        "el_DRNearGenEleFromSLTop",
        "el_PtNearGenEleFromSLTop",
        "el_PtNearGenTop",
        "el_LepAK4JetFrac",
        "el_LepAK8JetFrac",
        "el_LepSubjetFrac",
        "el_LepAK4JetMassDrop",
        "el_LepAK8JetMassDrop",
        "el_LepSubjetMassDrop",
        "el_AK4JetV1DR",
        "el_AK4JetV2DR",
        "el_AK4JetV3DR",
        "el_AK8JetV1DR",
        "el_AK8JetV2DR",
        "el_AK8JetV3DR",
        "el_SubjetV1DR",
        "el_SubjetV2DR",
        "el_SubjetV3DR",
        "el_AK4JetV1PtRel",
        "el_AK4JetV2PtRel",
        "el_AK4JetV3PtRel",
        "el_AK8JetV1PtRel",
        "el_AK8JetV2PtRel",
        "el_AK8JetV3PtRel",
        "el_SubjetV1PtRel",
        "el_SubjetV2PtRel",
        "el_SubjetV3PtRel",
        "mu_DRNearGenMuFromSLTop",
        "mu_PtNearGenMuFromSLTop",
        "mu_PtNearGenTop",
        "mu_LepAK4JetFrac",
        "mu_LepAK8JetFrac",
        "mu_LepSubjetFrac",
        "mu_LepAK4JetMassDrop",
        "mu_LepAK8JetMassDrop",
        "mu_LepSubjetMassDrop",
        "mu_AK4JetV1DR",
        "mu_AK4JetV2DR",
        "mu_AK4JetV3DR",
        "mu_AK8JetV1DR",
        "mu_AK8JetV2DR",
        "mu_AK8JetV3DR",
        "mu_SubjetV1DR",
        "mu_SubjetV2DR",
        "mu_SubjetV3DR",
        "mu_AK4JetV1PtRel",
        "mu_AK4JetV2PtRel",
        "mu_AK4JetV3PtRel",
        "mu_AK8JetV1PtRel",
        "mu_AK8JetV2PtRel",
        "mu_AK8JetV3PtRel",
        "mu_SubjetV1PtRel",
        "mu_SubjetV2PtRel",
        "mu_SubjetV3PtRel",
    ),
)

### Filter - Select only events with at least 1 AK8 jet with pt>300
# Filter for MiniAOD Jet collections
#process.PtMinAK8JetCountFilter = cms.EDFilter("PatJetCountFilter", # This one works on MiniAOD
#    src = cms.InputTag("slimmedJetsAK8"),
#    filter = cms.bool(True),
#    cut = cms.string("pt>300"),
#    minNumber = cms.uint32(1)
#)

# Filter For Edm ntuple - Use this here
process.EdmNtupleCountFilter = cms.EDFilter("EdmNtupleCountFilter", # This one works on EdmNtuple
    src = cms.InputTag("jetsAK8","jetAK8Pt"),
    filter = cms.bool(True), # False also filters for some reason (disable in Path instead)
    min = cms.double(350),
    minNumber = cms.uint32(2)
)

### B2GTTreeMaker
process.load("Analysis.B2GTTrees.B2GTTreeMaker_cff")
# Adding HBHE Noise (MET) filter results
process.B2GTTreeMaker.physicsObjects.append(
    cms.PSet(
        label = cms.untracked.string("HBHENoiseFilterResultProducer"),
        prefix_in = cms.untracked.string(""),
        prefix_out = cms.untracked.string("Flag_"),
        singleB = cms.untracked.vstring(
            "HBHEIsoNoiseFilterResult",
            "HBHENoiseFilterResult",
            "HBHENoiseFilterResultRun1",
            "HBHENoiseFilterResultRun2Loose",
            "HBHENoiseFilterResultRun2Tight"),
    )
)
# Adding extra Variables
process.B2GTTreeMaker.physicsObjects.append(
    cms.PSet(
        label = cms.untracked.string("extraVar"),
        prefix_in = cms.untracked.string(""),
        prefix_out = cms.untracked.string(""),
        singleI = process.extraVar.singleI,
        singleF = process.extraVar.singleF,
        vectorI = process.extraVar.vectorI,
        vectorF = process.extraVar.vectorF,
    )
)

process.B2GTTreeMaker.isData = options.isData

### EventCounter - to be applied before any filter to count
#   negative and positive weight events (for NLO samples)
#   histo name: NEventNoFilter (bin 1: neg, bin 2: pos weighted events)
process.EventCounter = cms.EDAnalyzer("EventCounter",
    isData = cms.untracked.bool(options.isData)
)


process.edmNtuplesOut = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(options.outputLabel),
    outputCommands = cms.untracked.vstring(
        "keep *",
    ),
    dropMetaData = cms.untracked.string('ALL'),
)

process.analysisPath = cms.Path(
    process.EventCounter *
    process.EdmNtupleCountFilter *
    process.extraVar *
    process.B2GTTreeMaker
)

#process.endPath = cms.EndPath( process.edmNtuplesOut )
