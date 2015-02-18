import FWCore.ParameterSet.Config as cms
import copy

# Default settings: add all variables from b2gedmntuples_cff
# Set to false, and define your own lists (eg. comment out unused vairables)
getVariablesFromConfig = True

if getVariablesFromConfig:
    from Analysis.B2GAnaFW.b2gedmntuples_cff import met, genPart, electrons, muons, jetsAK4, jetsAK8, subjetsAK8, jetsCmsTopTag, subjetsCmsTopTag
    
    met_var = cms.untracked.vstring()
    for pset in met.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        met_var.append(s)
    
    genPart_var = cms.untracked.vstring()
    for pset in genPart.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        genPart_var.append(s)
    
    electrons_var = cms.untracked.vstring()
    for pset in electrons.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        electrons_var.append(s)
    
    muons_var = cms.untracked.vstring()
    for pset in muons.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        muons_var.append(s)
    
    jetsAK4_var = cms.untracked.vstring()
    for pset in jetsAK4.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK4_var.append(s)
    
    jetsAK8_var = cms.untracked.vstring()
    for pset in jetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK8_var.append(s)
    
    subjetsAK8_var = cms.untracked.vstring()
    for pset in subjetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsAK8_var.append(s)
    
    jetsCmsTopTag_var = cms.untracked.vstring()
    for pset in jetsCmsTopTag.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsCmsTopTag_var.append(s)
    
    subjetsCmsTopTag_var = cms.untracked.vstring()
    for pset in subjetsCmsTopTag.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsCmsTopTag_var.append(s)
    
else:
    # Currrent ver: Version 1 (13 Feb) of B2GAnaFW
    met_var = cms.untracked.vstring(
        "Pt",
        "Px",
        "Py",
        "Phi",
        )
    
    genPart_var = cms.untracked.vstring(
        "Charge",
        "E",
        "Eta",
        "ID",
        "Mass",
        "MomID",
        "Phi",
        "Pt",
        "Status",
        "Y",
    )
    
    basicVars = cms.untracked.vstring(
        "Mass",
        "Pt",
        "Eta",
        "Y",
        "Phi",
        "E",
        "Charge",
        )
    
    electrons_var  = copy.deepcopy(basicVars)
    electrons_var += cms.untracked.vstring(
        "Key",
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
        "scEta",
        )
    
    muons_var  = copy.deepcopy(basicVars)
    muons_var += cms.untracked.vstring(
        "Key",
        "Iso04",
        "D0",
        "D0err",
        "Dxy",
        "Dxyerr",
        "Dz",
        "Dzerr",
        "IsLooseMuon",
        "IsSoftMuon",
        "IsTightMuon",
        "IsPFMuon",
        "IsGlobalMuon",
        "IsTrackerMuon",
        "GlbTrkNormChi2",
        "NumberValidMuonHits",
        "NumberMatchedStations",
        "NumberValidPixelHits",
        "NumberTrackerLayers",
        "NumberOfValidTrackerHits",
        "NumberOfPixelLayers",
        "InTrkNormChi2",
        "SumChargedHadronPt",
        "SumNeutralHadronPt",
        "SumPhotonPt",
        "SumPUPt",
        "GenMuonY",
        "GenMuonEta",
        "GenMuonPhi",
        "GenMuonPt",
        "GenMuonE",
        "GenMuonCharge",
        )
    
    jetVars  = copy.deepcopy(basicVars)
    jetVars += cms.untracked.vstring(
        "CSV",
        "CSVV1",
        "GenPartonY",
        "GenPartonEta",
        "GenPartonPhi",
        "GenPartonPt",
        "GenPartonE",
        "GenPartonCharge",
        "PartonFlavour",
        "HadronFlavour",
        "GenJetY",
        "GenJetEta",
        "GenJetPhi",
        "GenJetPt",
        "GenJetE",
        "GenJetCharge",
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
        "neutralHadronEnergy",
        "neutralEmEnergy",
        "chargedEmEnergy",
        "chargedHadronEnergy",
        "photonMultiplicity",
        "electronMultiplicity",
        "HFHadronMultiplicity",
        "HFEMMultiplicity",
        "ChargeMuEnergy",
        "neutralMultiplicity",
        "jecFactor0",
        "jetArea",
        "SmearedPt",
        "SmearedPEta",
        "SmearedPhi",
        "SmearedE",
        "JERup",
        "JERdown",
        )
    
    fatJetVars  = copy.deepcopy(jetVars)
    fatJetVars += cms.untracked.vstring(
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
        "topMass",
        "wMass",
        "nSubJets",
        "minmass",
        )
    
    subJetVars  = copy.deepcopy(jetVars)
    subJetVars += cms.untracked.vstring(
        "subjetCSV",
        )
    
    jetsAK4_var = copy.deepcopy(jetVars)
    jetsAK8_var = copy.deepcopy(fatJetVars)
    subjetsAK8_var = copy.deepcopy(subJetVars)
    jetsCmsTopTag_var = copy.deepcopy(fatJetVars)
    subjetsCmsTopTag_var = copy.deepcopy(jetVars)


B2GTTreeMaker = cms.EDAnalyzer("B2GTTreeMaker",
    physicsObjects = cms.VPSet(
        # MET
        #template.clone(
        cms.PSet(
            label = cms.string("met"),
            prefix_in = cms.string("met"),
            prefix_out = cms.string("met_"),
            vectorF = met_var,
            ),
        # GenParticles
        cms.PSet(
            label = cms.string("genPart"),
            prefix_in = cms.string("genPart"),
            prefix_out = cms.string("gen_"),
            vectorF = genPart_var,
            ),
        # Electrons
        cms.PSet(
            label = cms.string("electrons"),
            prefix_in = cms.string("el"),
            prefix_out = cms.string("el_"),
            vectorF = electrons_var,
            ),
        # Muons
        cms.PSet(
            label = cms.string("muons"),
            prefix_in = cms.string("mu"),
            prefix_out = cms.string("mu_"),
            vectorF = muons_var,
            ),
        # AK4 Jets
        cms.PSet(
            label = cms.string("jetsAK4"),
            prefix_in = cms.string("jetAK4"),
            prefix_out = cms.string("jetAK4_"),
            vectorF = jetsAK4_var,
            ),
        # AK8 Jets
        cms.PSet(
            label = cms.string("jetsAK8"),
            prefix_in = cms.string("jetAK8"),
            prefix_out = cms.string("jetAK8_"),
            vectorF = jetsAK8_var,
            ),
        # CMS Top-tag Jets
        cms.PSet(
            label = cms.string("jetsCmsTopTag"),
            prefix_in = cms.string("jetsCmsTopTag"),
            prefix_out = cms.string("jetsCmsTopTag_"),
            vectorF = jetsCmsTopTag_var,
            ),
        # Subjets of AK8 Jets
        cms.PSet(
            label = cms.string("subjetsAK8"),
            prefix_in = cms.string("subjetAK8"),
            prefix_out = cms.string("subjetAK8_"),
            vectorF = subjetsAK8_var,
            ),
        # Subjets of CMS Top-tag Jets
        cms.PSet(
            label = cms.string("subjetsCmsTopTag"),
            prefix_in = cms.string("subjetsCmsTopTag"),
            prefix_out = cms.string("subjetsCmsTopTag_"),
            vectorF = subjetsCmsTopTag_var,
            ),
        # Trigger data
        cms.PSet(
            label = cms.string("TriggerUserData"),
            prefix_in = cms.string("trigger"),
            prefix_out = cms.string("trigger_"),
            vectorF = cms.untracked.vstring("BitTree"),
            vectorI = cms.untracked.vstring("PrescaleTree"),
            ),
        # Event data
        cms.PSet(
            label = cms.string("eventUserData"),
            prefix_in = cms.string(""),
            prefix_out = cms.string("evt_"),
            vectorI = cms.untracked.vstring("puBX","puNInt"),
            singleI = cms.untracked.vstring("npv", "puNtrueInt"),
            singleD = cms.untracked.vstring("vx", "vy", "vz"),
            ),
        cms.PSet(
            label = cms.string("eventInfo"),
            prefix_in = cms.string("evtInfo"),
            prefix_out = cms.string("evt_"),
            singleUI = cms.untracked.vstring("RunNumber", "LumiBlock"),
            singleULL = cms.untracked.vstring("EventNumber"),
            ),
        )
    )
