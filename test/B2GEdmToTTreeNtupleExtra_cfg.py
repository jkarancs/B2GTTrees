### *****************************************************************************************
### Usage:
###
### cmsRun B2GEdmtExtraToTTreeNtuple_cfg.py maxEvts=N sample="file:sample.root" ttreeOutputLabel="myoutput.root"
###
### Default values for the options are set:
### maxEvts     = -1
### sample      = 'file:B2GEDMNtupleExtra.root'
### ttreeOutputLabel = 'B2GTTreeNtuple.root'
### *****************************************************************************************
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import os


useMINIAOD = True # True: Use on top of B2GAnaFW to produce TTrees, False: Use already produced B2G Edm ntuple')

if useMINIAOD:
    from Analysis.B2GTTrees.b2gedmntuples_cfg import *
    process.endPath = cms.EndPath()
    process.skimmedPatElectrons.cut = "pt >= 5 && abs(eta) < 2.5"
    process.electronUserData.eleVetoIdFullInfoMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto")
    process.electronUserData.eleLooseIdFullInfoMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose")
    process.electronUserData.eleMediumIdFullInfoMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium")
    process.electronUserData.eleTightIdFullInfoMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight")
    setupAllVIDIdsInModule(process,'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff',setupVIDElectronSelection)
else:
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
    
    options = opts.VarParsing('analysis')
    
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
    
    options.register('isFastSim',
                     False,
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.bool,
                     'Is FastSim?')
    
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
    
    options.register('Era',
                     'Spring16_25nsV6',
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.string,
                     'Directory, where the JEC text files are lcoated')
    
    options.register('usePrivateSQLite',
                     False,
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.bool,
                     'Take Corrections from private SQL file')
    
    options.register('runOnGrid',
                     True,
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.bool,
                     'Specify whether you are running on grid, for private test set to False')
    
    options.register('lheLabel',
                     "",
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.string,
                     'LHE module label, MC sample specific. Can be: externalLHEProducer')
    
    options.register('genHtFilter',
                     False,
                     opts.VarParsing.multiplicity.singleton,
                     opts.VarParsing.varType.bool,
                     'Specify whether you want to add a gen-level HT Filter (for unbinned TTJets sample)')
    
    options.parseArguments()
    
    ### Output Report
    process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
    ### Number of maximum events to process
    process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
    ### Source file
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(options.sample)
    )

# TTree code specific options
ttreeOutputLabel = options.outputLabel
isData = ("Data" in options.DataProcessing) if useMINIAOD else options.isData
isFastSim = ("FastSim" in options.DataProcessing) if useMINIAOD else options.isFastSim
runOnGrid = True
usePrivateSQLite = False
if useMINIAOD:
    Era = ""
    if options.usePrivateSQLite:
        usePrivateSQLite = True
        Era = jec_era
else:
    Era = options.Era + ("_DATA" if isData else "_MC")
JECloc = Era if runOnGrid else os.environ['CMSSW_BASE']+'/src/Analysis/B2GAnaFW/test/'+Era

lheLabel = "externalLHEProducer"
genHtFilter = False

### Output file
process.TFileService = cms.Service("TFileService", fileName = cms.string(ttreeOutputLabel))

### B2GEdmExtraVarProducer
from Analysis.B2GAnaFW.b2gedmntuples_cff import metFull, metFullClean, puppimetFull, genPart, electrons, muons, photons, photonjets, jetsAK4CHS, jetsAK4Puppi, jetsAK8CHS, jetsAK8Puppi, subjetsAK8CHS, subjetsAK8Puppi, genJetsAK8, genJetsAK8SoftDrop, eventInfo # metNoHF off since 76X

# import DB content from sqlite


if usePrivateSQLite and not useMINIAOD:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
		    connect = cms.string( "sqlite_file:"+JECloc+".db" ),
		    toGet =  cms.VPSet(
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK4PF"),
				    label= cms.untracked.string("AK4PF")
				    ),
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK4PFchs"),
				    label= cms.untracked.string("AK4PFchs")
				    ),
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK4PFPuppi"),
				    label= cms.untracked.string("AK4PFPuppi")
				    ),
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK8PF"),
				    label= cms.untracked.string("AK8PF")
				    ),
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK8PFchs"),
				    label= cms.untracked.string("AK8PFchs")
				    ),
			    cms.PSet(
				    record = cms.string("JetCorrectionsRecord"),
				    tag = cms.string("JetCorrectorParametersCollection_"+Era+"_AK8PFPuppi"),
				    label= cms.untracked.string("AK8PFPuppi")
				    ),
			    )
		    )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

# Revert back to CHS - 22 December 2016
usePuppiJets = False # Also make sure B2GTTreeMaker_cff.py is consistent
usePuppiMet  = False # Used for Razor calculation

if usePuppiJets:
    AK4_label     = "jetsAK4Puppi"
    AK4_prefix    = "jetAK4Puppi"
    AK4_key       = "jetKeysAK4Puppi"
    AK8_label     = "jetsAK8Puppi"
    AK8_prefix    = "jetAK8Puppi"
    AK8_key       = "jetKeysAK8Puppi"
    AK8sub_label  = "subjetsAK8Puppi"
    AK8sub_prefix = "subjetAK8Puppi"
    AK8sub_key    = "subjetKeysAK8Puppi"
else:
    AK4_label     = "jetsAK4CHS"
    AK4_prefix    = "jetAK4CHS"
    AK4_key       = "jetKeysAK4CHS"
    AK8_label     = "jetsAK8CHS"
    AK8_prefix    = "jetAK8CHS"
    AK8_key       = "jetKeysAK8CHS"
    AK8sub_label  = "subjetsAK8CHS"
    AK8sub_prefix = "subjetAK8CHS"
    AK8sub_key    = "subjetKeysAK8CHS"
    
if usePuppiMet:
    met_label  = "puppimetFull"
    met_prefix = puppimetFull.prefix
else:
    met_label  = "metFullClean"
    met_prefix = metFullClean.prefix

process.extraVar = cms.EDProducer("B2GEdmExtraVarProducer",
    isData = cms.untracked.bool(isData),
    isFastSim = cms.untracked.bool(isFastSim),
    lhe_label = cms.untracked.string(lheLabel),
    filter_label = cms.untracked.string("METUserData"),
    trigger_label = cms.untracked.string("TriggerUserData"),
    evt_label = cms.untracked.string("eventUserData"),
    evt_prefix = cms.untracked.string(""),
    vtx_label = cms.untracked.string("vertexInfo"),
    vtx_prefix = cms.untracked.string(""),
    met_label  = cms.untracked.string(met_label),
    met_prefix = met_prefix,
    gen_label = cms.untracked.string("genPart"),
    gen_prefix = genPart.prefix,
    photons_label = cms.untracked.string("photons"),
    photons_prefix = photons.prefix,
    electrons_label = cms.untracked.string("electrons"),
    electrons_prefix = electrons.prefix,
    muons_label = cms.untracked.string("muons"),
    muons_prefix = muons.prefix,
    AK4Jets_label  = cms.untracked.string(AK4_label),
    AK4Jets_prefix = cms.untracked.string(AK4_prefix),
    AK4JetKeys_label = cms.untracked.string(AK4_key),
    AK8Jets_label  = cms.untracked.string(AK8_label),
    AK8Jets_prefix = cms.untracked.string(AK8_prefix),
    AK8JetKeys_label = cms.untracked.string(AK8_key),
    AK8Subjets_label  = cms.untracked.string(AK8sub_label),
    AK8Subjets_prefix = cms.untracked.string(AK8sub_prefix),
    AK8SubjetKeys_label = cms.untracked.string(AK8sub_key),
    singleI = cms.untracked.vstring(
        # Event filters (these are automatically picked up)
        "Flag_HBHENoiseFilter",
        "Flag_HBHENoiseIsoFilter",
        "Flag_CSCTightHaloFilter",
        "Flag_CSCTightHaloTrkMuUnvetoFilter",
        "Flag_CSCTightHalo2015Filter",
        "Flag_globalTightHalo2016Filter",
        "Flag_globalSuperTightHalo2016Filter",
        "Flag_HcalStripHaloFilter",
        "Flag_hcalLaserEventFilter",
        "Flag_EcalDeadCellTriggerPrimitiveFilter",
        "Flag_EcalDeadCellBoundaryEnergyFilter",
        "Flag_goodVertices",
        "Flag_eeBadScFilter",
        "Flag_ecalLaserCorrFilter",
        "Flag_trkPOGFilters",
        "Flag_chargedHadronTrackResolutionFilter",
        "Flag_muonBadTrackFilter",
        "Flag_trkPOG_manystripclus53X",
        "Flag_trkPOG_toomanystripclus53X",
        "Flag_trkPOG_logErrorTooManyClusters",
        "Flag_METFilters",
        "Flag_badMuons",
        "Flag_duplicateMuons",
        "Flag_noBadMuons",
        "Flag_isPathologicalFastsimEvent",
        # Add trigger names below (these are automatically picked up)
        # Single Jet
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
        "HLT_AK8PFJet40",
        "HLT_AK8PFJet60",
        "HLT_AK8PFJet80",
        "HLT_AK8PFJet140",
        "HLT_AK8PFJet200",
        "HLT_AK8PFJet260",
        "HLT_AK8PFJet320",
        "HLT_AK8PFJet360_TrimMass30",
        "HLT_AK8PFJet400_TrimMass30",
        "HLT_AK8PFJet400",
        "HLT_AK8PFJet450",
        "HLT_AK8PFJet500",
        # HT
        "HLT_PFHT125",
        "HLT_PFHT200",
        "HLT_PFHT250",
        "HLT_PFHT300",
        "HLT_PFHT350",
        "HLT_PFHT400",
        "HLT_PFHT475",
        "HLT_PFHT600",
        "HLT_PFHT650",
        "HLT_PFHT800",
        "HLT_PFHT900",
        "HLT_AK8PFHT650_TrimR0p1PT0p03Mass50",
        "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",
        "HLT_AK8PFHT750_TrimMass50",
        "HLT_AK8PFHT800_TrimMass50",
        "HLT_PFHT550_4JetPt50",
        "HLT_PFHT650_4JetPt50",
        "HLT_PFHT750_4JetPt50",
        "HLT_PFHT750_4JetPt70",
        "HLT_PFHT750_4JetPt80",
        "HLT_PFHT800_4JetPt50",
        "HLT_PFHT850_4JetPt50",
        # 2 AK8 Jet
        "HLT_AK8DiPFJet250_200_TrimMass30",
        "HLT_AK8DiPFJet280_200_TrimMass30",
        "HLT_AK8DiPFJet300_200_TrimMass30",
        # MET
        "HLT_MET100",
        "HLT_MET150",
        "HLT_MET200",
        "HLT_MET250",
        "HLT_MET300",
        "HLT_MET600",
        "HLT_MET700",
        "HLT_PFMET170_BeamHaloCleaned",
        "HLT_PFMET170_HBHECleaned",
        "HLT_PFMET170_HBHE_BeamHaloCleaned",
        "HLT_PFMET170_JetIdCleaned",
        "HLT_PFMET170_NoiseCleaned",
        "HLT_PFMET170_NotCleaned",
        "HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned",
        "HLT_PFMET300",
        "HLT_PFMET400",
        "HLT_PFMET500",
        "HLT_PFMET600",
        # MHT
        "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067",
        "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight",
        "HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned",
        "HLT_PFMET100_PFMHT100_IDTight",
        "HLT_PFMET110_PFMHT110_IDTight",
        "HLT_PFMET120_PFMHT120_IDTight",
        "HLT_PFMET90_PFMHT90_IDTight",
        "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight",
        "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
        "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
        "HLT_PFMETNoMu90_PFMHTNoMu90_IDTight",
        # Single Mu
        "HLT_Mu17",
        "HLT_Mu20",
        "HLT_Mu27",
        "HLT_Mu50",
        "HLT_Mu55",
        "HLT_TkMu17",
        "HLT_TkMu20",
        "HLT_TkMu27",
        "HLT_TkMu50",
        "HLT_IsoMu18",
        "HLT_IsoMu20",
        "HLT_IsoMu22",
        "HLT_IsoMu24",
        "HLT_IsoMu27",
        "HLT_IsoTkMu18",
        "HLT_IsoTkMu20",
        "HLT_IsoTkMu22",
        "HLT_IsoTkMu24",
        "HLT_IsoTkMu27",
        # Single Ele
        "HLT_Ele17_CaloIdL_GsfTrkIdVL",
        "HLT_Ele22_eta2p1_WPLoose_Gsf",
        "HLT_Ele23_WPLoose_Gsf",
        "HLT_Ele24_eta2p1_WPLoose_Gsf",
        "HLT_Ele25_WPTight_Gsf",
        "HLT_Ele25_eta2p1_WPLoose_Gsf",
        "HLT_Ele25_eta2p1_WPTight_Gsf",
        "HLT_Ele27_WPLoose_Gsf",
        "HLT_Ele27_WPTight_Gsf",
        "HLT_Ele27_eta2p1_WPLoose_Gsf",
        "HLT_Ele27_eta2p1_WPTight_Gsf",
        "HLT_Ele30_WPTight_Gsf",
        "HLT_Ele30_eta2p1_WPLoose_Gsf",
        "HLT_Ele30_eta2p1_WPTight_Gsf",
        "HLT_Ele32_WPTight_Gsf",
        "HLT_Ele32_eta2p1_WPLoose_Gsf",
        "HLT_Ele32_eta2p1_WPTight_Gsf",
        "HLT_Ele35_WPLoose_Gsf",
        "HLT_Ele45_WPLoose_Gsf",
        "HLT_Ele105_CaloIdVT_GsfTrkIdT",
        "HLT_Ele115_CaloIdVT_GsfTrkIdT",
        "HLT_Ele145_CaloIdVT_GsfTrkIdT",
        "HLT_Ele200_CaloIdVT_GsfTrkIdT",
        "HLT_Ele250_CaloIdVT_GsfTrkIdT",
        "HLT_Ele300_CaloIdVT_GsfTrkIdT",
        # Lepton + 2 Jet
        "HLT_Mu30_eta2p1_PFJet150_PFJet50",
        "HLT_Mu40_eta2p1_PFJet200_PFJet50",
        "HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50",
        "HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50",
        # Photon
        "HLT_Photon22",
        "HLT_Photon30",
        "HLT_Photon36",
        "HLT_Photon50",
        "HLT_Photon75",
        "HLT_Photon90",
        "HLT_Photon120",
        "HLT_Photon165_HE10",
        "HLT_Photon175",
        "HLT_Photon250_NoHE",
        "HLT_Photon300_NoHE",
        "HLT_Photon500",
        "HLT_Photon600",
        # end of triggers
        # Event variables
        "evt_NGoodVtx",
        "evt_LHA_PDF_ID",
        "evt_NIsoTrk",
        "evt_NISRJets",
    ),
    singleF = cms.untracked.vstring(
        "evt_MR",
        "evt_MTR",
        "evt_R",
        "evt_R2",
        "evt_MR_Smear",
        "evt_MTR_Smear",
        "evt_XSec",
        "evt_Gen_Weight",
        "evt_Gen_Ht",
        "met_genPt",
        "met_genPhi",
        "SUSY_Stop_Mass",
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
        AK8_prefix+"_HasNearGenTop",
        AK8_prefix+"_NearGenTopIsHadronic",
        AK8_prefix+"_NearGenWIsHadronic",
        AK8_prefix+"_NearGenWToENu",
        AK8_prefix+"_NearGenWToMuNu",
        AK8_prefix+"_NearGenWToTauNu",
        AK4_prefix+"_looseJetID",
        AK4_prefix+"_tightJetID",
        AK4_prefix+"_tightLepVetoJetID",
        AK8_prefix+"_looseJetID",
        AK8_prefix+"_tightJetID",
        AK8_prefix+"_tightLepVetoJetID",
        AK8sub_prefix+"_looseJetID",
        AK8sub_prefix+"_tightJetID",
        AK8sub_prefix+"_tightLepVetoJetID",
        "pho_isPromptDirect",
        "pho_isPromptFrag",
        "pho_isFake",
        "el_IsPartOfNearAK4Jet",
        "el_IsPartOfNearAK8Jet",
        "el_IsPartOfNearSubjet",
        "mu_IsPartOfNearAK4Jet",
        "mu_IsPartOfNearAK8Jet",
        "mu_IsPartOfNearSubjet",
        #"el_mvaIDvalueHZZ",
        #"el_IDVeto_NoIso",
        #"el_IDLoose_NoIso",
        #"el_IDMedium_NoIso",
        #"el_IDTight_NoIso",
        #"el_IsoVeto",
        #"el_IsoLoose",
        #"el_IsoMedium",
        #"el_IsoTight",
        #"el_IDVeto",
        #"el_IDLoose",
        #"el_IDMedium",
        #"el_IDTight",
        "tau_IsLoose",
        "tau_IsMedium",
        "tau_IsTight",
        "tau_passEleVetoLoose",
        "tau_passEleVetoMedium",
        "tau_passEleVetoTight",
        "tau_passMuVetoLoose",
        "tau_passMuVetoTight",
        "tau_ID",
        "tau_eleVetoCategory",
    ),
    vectorF = cms.untracked.vstring(
        "scale_Weights",
        "pdf_Weights",
        "alphas_Weights",
        "metsyst_MuCleanOnly_Pt",
        "metsyst_MuCleanOnly_Phi",
        "metsyst_Pt",
        "metsyst_Phi",
        "puppimetsyst_Pt",
        "puppimetsyst_Phi",
        "gen_Pt",
        "gen_Eta",
        "gen_Phi",
        "gen_E",
        "gen_Mass",
        "gen_Charge",
        AK8_prefix+"_maxSubjetCSVv2",
        AK8_prefix+"_maxSubjetCMVAv2",
        AK8_prefix+"_DRNearGenTop",
        AK8_prefix+"_DRNearGenWFromTop",
        AK8_prefix+"_DRNearGenBFromTop",
        AK8_prefix+"_DRNearGenLepFromSLTop",
        AK8_prefix+"_DRNearGenNuFromSLTop",
        AK8_prefix+"_PtNearGenTop",
        AK8_prefix+"_PtNearGenBFromTop",
        AK8_prefix+"_PtNearGenWFromTop",
        AK8_prefix+"_PtNearGenLepFromSLTop",
        AK8_prefix+"_PtNearGenNuFromSLTop",
        #AK8_prefix+"_softDropMassPuppiUncorr",
        #AK8_prefix+"_softDropMassPuppiCorr",
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
        "tau_eleVetoMVA",
        "tau_E",
        "tau_Pt",
        "tau_Eta",
        "tau_Phi",
        "tau_combinedIsoDeltaBetaCorr3Hits",
        "tau_chargedIsoPtSum",
        "tau_neutralIsoPtSum",
        "tau_puCorrPtSum",
        "tau_isoMVAnewDMwLT",
        "tau_leadCandPt",
        "tau_leadCandID",
        "tau_leadChargedHadrCandPt",
        "tau_leadChargedHadrCandID",
    ),
)

### Filter - Select only events with at least 1 AK8 jet with pt>300
# Filter for MiniAOD Jet collections
process.PtMinAK8JetCountFilter = cms.EDFilter("PatJetCountFilter", # This one works on MiniAOD
    filter = cms.bool(True),
    src = cms.InputTag("slimmedJetsAK8"),
    cut = cms.string("pt>300"),
    minNumber = cms.uint32(1)
)

# Filter For Edm ntuple - Use this here
#process.EdmNtupleCountFilter = cms.EDFilter("EdmNtupleCountFilter", # This one works on EdmNtuple
#    filter = cms.bool(True), # False also filters for some reason (disable in Path instead)
#    src = cms.InputTag(AK8_label,AK8_prefix+"Pt"),
#    #min = cms.double(350),
#    #minNumber = cms.uint32(2)
#    min = cms.double(150),
#    minNumber = cms.uint32(1)
#)
process.Min3AK4JetFilter = cms.EDFilter("EdmNtupleCountFilter", # This one works on EdmNtuple
    filter = cms.bool(True), # False also filters for some reason (disable in Path instead)
    src = cms.InputTag(AK4_label,AK4_prefix+"Pt"),
    min = cms.double(0),
    minNumber = cms.uint32(3)
)
process.Min1AK8JetFilter = cms.EDFilter("EdmNtupleCountFilter", # This one works on EdmNtuple
    filter = cms.bool(True), # False also filters for some reason (disable in Path instead)
    src = cms.InputTag(AK8_label,AK8_prefix+"Pt"),
    min = cms.double(0),
    minNumber = cms.uint32(1)
)
if genHtFilter:
    process.GenHtFilter = cms.EDFilter("SingleFloatFilter",
        src = cms.InputTag("extraVar","evtGenHt"),
        max = cms.untracked.double(600),
    )

### B2GTTreeMaker
process.load("Analysis.B2GTTrees.B2GTTreeMaker_cff")
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

process.B2GTTreeMaker.isData = isData

### EventCounter - to be applied before any filter to count
#   negative and positive weight events (for NLO samples)
#   histo name: NEventNoFilter (bin 1: neg, bin 2: pos weighted events)
process.EventCounter = cms.EDAnalyzer("EventCounter",
    isData = cms.untracked.bool(isData)
)

# Paths
process.analysisPath = cms.Path(
    process.extraVar *
    process.EventCounter *
    #process.Min3AK4JetFilter *
    #process.Min1AK8JetFilter *
    process.B2GTTreeMaker)
