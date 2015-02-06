import FWCore.ParameterSet.Config as cms
import copy

leptons_size = cms.untracked.int32(5)
jets_size    = cms.untracked.int32(20)
subjets_size = cms.untracked.int32(50)

metVars = cms.vstring(
    "Pt",
    "Px",
    "Py",
    "Phi",
    )

basicVars = cms.vstring(
    "Mass",
    "Pt",
    "Eta",
    "Y",
    "Phi",
    "E",
    "Charge",
    )

eleVars  = copy.deepcopy(basicVars)
eleVars += cms.vstring(
    "Iso03",
    "D0",
    "Dz",
    "dEtaIn",
    "dPhiIn",
    "HoE",
    "full5x5siee",
    "ooEmooP",
    "missHits",
    "hasMatchedConVeto",
    "isEB",
    "isVeto",
    "isLoose",
    "isTight",
    "isMedium",
    )

muVars  = copy.deepcopy(basicVars)
muVars += cms.vstring(
    "Iso03",
    "D0",
    "D0err",
    "Dz",
    "Dzerr",
    ### the following variables need have track embedded in the pat::muon
    "IsLooseMuon",
    "IsSoftMuon",
    "IsTightMuon",
    ## variables used in ID
    ### LOOSE
    "IsPFMuon",
    "IsGlobalMuon",
    "IsTrackerMuon",
    ### TIGHT
    "GlbTrkNormChi2",
    "NumberValidMuonHits",
    "NumberMatchedStations",
    "NumberValidPixelHits",
    "NumberTrackerLayers",
    ### SOFT
    "NumberOfValidTrackerHits",
    "NumberOfPixelLayers",
    "InTrkNormChi2",
    ## variables used in isolation
    "SumChargedHadronPt",
    "SumNeutralHadronPt",
    "SumPhotonPt",
    "SumPUPt",
    ### genLepton
    "GenMuonY",
    "GenMuonEta",
    "GenMuonPhi",
    "GenMuonPt",
    "GenMuonE",
    "GenMuonCharge",
    ### trigger matching
    "HLTmuonDeltaR",
    "HLTmuonPt",
    "HLTmuonEta",
    "HLTmuonPhi",
    "HLTmuonE",
    )

jetVars  = copy.deepcopy(basicVars)
jetVars += cms.vstring(
    ### B-TAGGING
    "CSV",
    "CSVV1",
    ### GEN PARTON
    "GenPartonY",
    "GenPartonEta",
    "GenPartonPhi",
    "GenPartonPt",
    "GenPartonE",
    "GenPartonCharge",
    "PartonFlavour",
    "HadronFlavour",
    ### GEN JET
    "GenJetY",
    "GenJetEta",
    "GenJetPhi",
    "GenJetPt",
    "GenJetE",
    "GenJetCharge",
    ### TRIGGER MATHING
    "HLTjetEta",
    "HLTjetPhi",
    "HLTjetPt",
    "HLTjetE",
    "HLTjetDeltaR",
    ### CONSTITUENTS
    "muonMultiplicity",
    "PhotonEnergy",
    "ElectronEnergy",
    "MuonEnergy",
    "HFHadronEnergy",
    "HFEMEnergy",
    "ChargedHadronMultiplicity",
    "numberOfDaughters",
    "chargedMultiplicity",
    "neutralHadronMultiplicity",
    "neutralHadronEnergyFraction",
    "neutralEmEnergyFraction",
    "chargedEmEnergyFraction",
    "chargedHadronEnergyFraction",
    "photonMultiplicity",
    "electronMultiplicity",
    "HFHadronMultiplicity",
    "HFEMMultiplicity",
    "ChargeMuEnergy",
    "neutralMultiplicity",
    #### FOR JEC
    "jecFactor0",
    #### FOR SYSTEMATICS
    "SmearedPt",
    "SmearedPEta",
    "SmearedPhi",
    "SmearedE",
    "JERup",
    "JERdown",
    )

fatJetVars  = copy.deepcopy(jetVars)
fatJetVars += cms.vstring(
    # AK8Vars
    "subjetIndex0",
    "subjetIndex1",
    "subjetIndex2",
    "subjetIndex4",
    "tau1",
    "tau2",
    "tau3",
    "trimmedMass",
    "prunedMass",
    "filteredMass",
    )

B2GTTreeMaker = cms.EDAnalyzer("B2GTTreeMaker",
    physicsObjects = cms.VPSet(
        # Electrons
        cms.PSet(
            label = cms.string("electrons"),
            prefix_in = cms.string("el"),
            prefix_out = cms.string("el_"),
            maxInstances = leptons_size,
            variablesF = eleVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # Muons
        cms.PSet(
            label = cms.string("muons"),
            prefix_in = cms.string("mu"),
            prefix_out = cms.string("mu_"),
            maxInstances = leptons_size,
            variablesF = muVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # MET
        cms.PSet(
            label = cms.string("met"),
            prefix_in = cms.string("met"),
            prefix_out = cms.string("met_"),
            maxInstances = cms.untracked.int32(1),
            variablesF = metVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # AK4 Jets
        cms.PSet(
            label = cms.string("jetsAK4"),
            prefix_in = cms.string("jetAK4"),
            prefix_out = cms.string("jetAK4_"),
            maxInstances = jets_size,
            variablesF = jetVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # AK8 Jets
        cms.PSet(
            label = cms.string("jetsAK8"),
            prefix_in = cms.string("jetAK8"),
            prefix_out = cms.string("jetAK8_"),
            maxInstances = jets_size,
            variablesF = fatJetVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # CMS Top-tag Jets
        cms.PSet(
            label = cms.string("jetsCmsTopTag"),
            prefix_in = cms.string("jetsCmsTopTag"),
            prefix_out = cms.string("jetsCmsTopTag_"),
            maxInstances = jets_size,
            variablesF = fatJetVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # Subjets of AK8 Jets
        cms.PSet(
            label = cms.string("subjetsAK8"),
            prefix_in = cms.string("subjetAK8"),
            prefix_out = cms.string("subjetAK8_"),
            maxInstances = subjets_size,
            variablesF = jetVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            ),
        # Subjets of CMS Top-tag Jets
        cms.PSet(
            label = cms.string("subjetsCmsTopTag"),
            prefix_in = cms.string("subjetsCmsTopTag"),
            prefix_out = cms.string("subjetsCmsTopTag_"),
            maxInstances = subjets_size,
            variablesF = jetVars,
            variablesI = cms.vstring(),
            singleI = cms.vstring(),
            singleF = cms.vstring(),
            )
        )
    )
