import FWCore.ParameterSet.Config as cms
import copy

# Default settings: add all variables from b2gedmntuples_cff
# Set to false, and define your own lists (eg. comment out unused vairables)
getVariablesFromConfig = False

from Analysis.B2GAnaFW.b2gedmntuples_cff import metNoHF, metFull, genPart, electrons, muons, photons, photonjets, jetsAK4, jetsAK4NoHF, jetsAK8, subjetsAK8, subjetsCmsTopTag, genJetsAK8, genJetsAK8SoftDrop, eventInfo

if getVariablesFromConfig:
    
    metNoHF_var = cms.untracked.vstring()
    for pset in metNoHF.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        metNoHF_var.append(s)
    
    metFull_var = cms.untracked.vstring()
    for pset in metFull.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        metFull_var.append(s)
    
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

    photons_var = cms.untracked.vstring()
    for pset in photons.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        photons_var.append(s)
    
    photonjets_var = cms.untracked.vstring()
    for pset in photonjets.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        photonjets_var.append(s)
    
    jetsAK4_var = cms.untracked.vstring()
    for pset in jetsAK4.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK4_var.append(s)
    
    jetsAK4NoHF_var = cms.untracked.vstring()
    for pset in jetsAK4NoHF.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK4NoHF_var.append(s)
    
    jetsAK8_var = cms.untracked.vstring()
    for pset in jetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK8_var.append(s)
    
    subjetsAK8_var = cms.untracked.vstring()
    for pset in subjetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsAK8_var.append(s)
    
    subjetsCmsTopTag_var = cms.untracked.vstring()
    for pset in subjetsCmsTopTag.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsCmsTopTag_var.append(s)
    
    genJetsAK8_var = cms.untracked.vstring()
    for pset in genJetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        genJetsAK8_var.append(s)

    genJetsAK8SoftDrop_var = cms.untracked.vstring()
    for pset in genJetsAK8SoftDrop.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        genJetsAK8SoftDrop_var.append(s)

else:
    # Currrent B2GAnaFW ver: 10 Nov (v7.4.x_v8.4 ntuple version)
    metNoHF_var = cms.untracked.vstring(
        "Pt",
        "Px",
        "Py",
        "Phi",
        "uncorPt",
        "uncorPhi",
        "uncorSumEt",
    )
    metFull_var    = copy.deepcopy(metNoHF_var)
    
    basicVars = cms.untracked.vstring(
        #"Mass",
        "Pt",
        "Eta",
        #"Y",
        "Phi",
        "E",
        "Charge",
    )
    
    genPartVars = cms.untracked.vstring(
        "ID",
        "Status",
        "Mom0ID",
        "Mom0Status",
        "Mom1ID",
        "Mom1Status",
        "Dau0ID",
        "Dau0Status",
        "Dau1ID",
        "Dau1Status",
    )
    
    electronVars = cms.untracked.vstring(
        "Key",
        "Iso03",
        "Iso03db",
        "MiniIso",
        "rho",
        "EA",
        "sumChargedHadronPt",
        "sumNeutralHadronEt",
        "sumPhotonEt",
        "sumPUPt",
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
        "vidVeto",
        "vidLoose",
        "vidTight",
        "vidMedium",
        "vidHEEP",
        "vidHEEPnoiso",
        "scEta",
    )
    
    muonVars = cms.untracked.vstring(
        "Key",
        "Iso04",
        "MiniIso",
        "D0",
        "D0err",
        "Dxy",
        "Dxyerr",
        "Dz",
        "Dzerr",
        "IsSoftMuon",
        "IsLooseMuon",
        "IsMediumMuon",
        "IsTightMuon",
        "IsHighPtMuon",
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
    
    photonVars = cms.untracked.vstring(
        "SClusterEta",
        "SClusterPhi",
        "Eta",
        "Phi",
        "Pt",
        "Energy",
        "HasPixelSeed",
        "SigmaIEtaIEta",
        "HoverE",
        "R9",
        "ChargedHadronIso",
        "PhotonIso",
        "NeutralHadronIso",
        "ChargedHadronIsoEAcorrected",
        "PhotonIsoEAcorrected",
        "NeutralHadronIsoEAcorrected",
        "PassLooseID",
        "PassMediumID",
        "PassTightID",
    )
    
    photonjetVars = cms.untracked.vstring(
        "JetIndex",
        "PhotonIndex",
        "SubwGammatIndex",
        "PhotonSubjetFrac",
        "SubjetPt0",
        "SubjetPt1",
        "SubjetPt2",
        "SubjetEta0",
        "SubjetEta1",
        "SubjetEta2",
        "SubjetPhi0",
        "SubjetPhi1",
        "SubjetPhi2",
        "SubjetEne0",
        "SubjetEne1",
        "SubjetEne2",
    )
    
    jetVars = cms.untracked.vstring(
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
        "neutralHadronEnergyFrac",
        "neutralEmEnergyFrac",
        "chargedHadronEnergyFrac",
        "muonEnergyFrac",
        "chargedEmEnergyFrac",
        "chargedMultiplicity",
        "NumConstituents",
        "jecFactor0",
        "jecFactorL3Absolute",
        "jetArea",
        "SmearedPt",
        "SmearedPEta",
        "SmearedPhi",
        "SmearedE",
        "JERup",
        "JERdown",
    )

    jetVarsJEC = cms.untracked.vstring(
        "jecFactor0",
        "jecFactorL1FastJet",
        "jecFactorL3Absolute",
        "jetArea",
    )
    
    qglVars = cms.untracked.vstring(
        "QGL",
    )
    
    jetAK8Vars = cms.untracked.vstring(
        "vSubjetIndex0",
        "vSubjetIndex1",
        "topSubjetIndex0",
        "topSubjetIndex1",
        "topSubjetIndex2",
        "topSubjetIndex3",
        "tau1",
        "tau2",
        "tau3",
        "softDropMass",
        "trimmedMass",
        "prunedMass",
        "filteredMass",
        "topMass",
        "wMass",
        "nSubJets",
        "minmass",
    )
    
    genPart_var    = copy.deepcopy(basicVars)
    genPart_var   += genPartVars
    
    electrons_var  = copy.deepcopy(basicVars)
    electrons_var += electronVars
    
    muons_var      = copy.deepcopy(basicVars)
    muons_var     += muonVars
    
    photons_var    = copy.deepcopy(photonVars)
    
    photonjets_var = copy.deepcopy(photonjetVars)
    
    jetsAK4_var      = copy.deepcopy(basicVars)
    jetsAK4_var     += jetVars
    jetsAK4_var     += qglVars
    
    jetsAK4NoHF_var  = copy.deepcopy(basicVars)
    jetsAK4NoHF_var += jetVarsJEC
    jetsAK4NoHF_var += qglVars
    
    jetsAK8_var  = copy.deepcopy(basicVars)
    jetsAK8_var += jetVars
    jetsAK8_var += jetAK8Vars
    
    subjetsAK8_var  = copy.deepcopy(basicVars)
    subjetsAK8_var += jetVars
    
    subjetsCmsTopTag_var  = copy.deepcopy(basicVars)
    subjetsCmsTopTag_var += jetVars
    
    genJetsAK8_var = copy.deepcopy(basicVars)
    
    genJetsAK8SoftDrop_var = copy.deepcopy(basicVars)

B2GTTreeMaker = cms.EDAnalyzer("B2GTTreeMaker",
    isData = cms.untracked.bool(False),
    physicsObjects = cms.VPSet(
        # Event infos
        cms.PSet(
            label = cms.untracked.string("eventUserData"),
            prefix_in = cms.untracked.string(""),
            prefix_out = cms.untracked.string("evt_"),
            singleI = cms.untracked.vstring("npv"),
            singleD = cms.untracked.vstring("vx", "vy", "vz"),
        ),
        cms.PSet(
            label = cms.untracked.string("eventInfo"),
            prefix_in = eventInfo.prefix,
            prefix_out = cms.untracked.string("evt_"),
            singleUI = cms.untracked.vstring("RunNumber", "LumiBlock"),
            singleULL = cms.untracked.vstring("EventNumber"),
        ),
        cms.PSet(
            label = cms.untracked.string("fixedGridRhoFastjetAll"),
            prefix_in = cms.untracked.string(""),
            prefix_out = cms.untracked.string("evt_rho"),
            singleD = cms.untracked.vstring(""),
        ),
        # Pileup
        cms.PSet(
            label = cms.untracked.string("eventUserData"),
            prefix_in = cms.untracked.string("pu"),
            prefix_out = cms.untracked.string("pu_"),
            singleI = cms.untracked.vstring("NtrueInt"),
            vectorI = cms.untracked.vstring("BX","NInt"),
        ),
        # Trigger data
        #cms.PSet(
        #    label = cms.untracked.string("TriggerUserData"),
        #    prefix_in = cms.untracked.string("trigger"),
        #    prefix_out = cms.untracked.string("trig_"),
        #    vectorI = cms.untracked.vstring("PrescaleTree"),
        #    vectorF = cms.untracked.vstring("BitTree"),
        #),
        # Vertices
        cms.PSet(
            label = cms.untracked.string("vertexInfo"),
            prefix_in = cms.untracked.string(""),
            prefix_out = cms.untracked.string("vtx_"),
            vectorI = cms.untracked.vstring("ndof"),
            vectorF = cms.untracked.vstring("z","rho","chi"),
        ),
        # MET
        cms.PSet(
            label = cms.untracked.string("metNoHF"),
            prefix_in = metNoHF.prefix,
            prefix_out = cms.untracked.string("met_NoHF_"),
            vectorF = metNoHF_var,
        ),
        cms.PSet(
            label = cms.untracked.string("metFull"),
            prefix_in = metFull.prefix,
            prefix_out = cms.untracked.string("met_"),
            vectorF = metFull_var,
        ),
        # GenParticles
        #cms.PSet(
        #    label = cms.untracked.string("genPart"),
        #    prefix_in = genPart.prefix,
        #    prefix_out = cms.untracked.string("gen_"),
        #    vectorF = genPart_var,
        #    mc_only = cms.untracked.bool(True),
        #),
        # Electrons
        cms.PSet(
            label = cms.untracked.string("electrons"),
            prefix_in = electrons.prefix,
            prefix_out = cms.untracked.string("el_"),
            vectorF = electrons_var,
        ),
        # Muons
        cms.PSet(
            label = cms.untracked.string("muons"),
            prefix_in = muons.prefix,
            prefix_out = cms.untracked.string("mu_"),
            vectorF = muons_var,
        ),
        # Photons
        #cms.PSet(
        #    label = cms.untracked.string("photons"),
        #    prefix_in = photons.prefix,
        #    prefix_out = cms.untracked.string("pho_"),
        #    vectorF = photons_var,
        #),
        # Photon jets
        #cms.PSet(
        #    label = cms.untracked.string("photonjets"),
        #    prefix_in = photonjets.prefix,
        #    prefix_out = cms.untracked.string("phojet_"),
        #    vectorF = photonjets_var,
        #),
        # AK4 Jets
        cms.PSet(
            label = cms.untracked.string("jetsAK4"),
            key_label = cms.untracked.string("jetKeysAK4"),
            prefix_in = jetsAK4.prefix,
            prefix_out = cms.untracked.string("jetAK4_"),
            vectorF = jetsAK4_var,
        ),
        # AK4 Jets (No HF) - Currently not saved in V6.1
        #cms.PSet(
        #    label = cms.untracked.string("jetsAK4NoHF"),
        #    key_label = cms.untracked.string("jetKeysAK4NoHF"),
        #    prefix_in = jetsAK4.prefix,
        #    prefix_out = cms.untracked.string("jetAK4_NoHF_"),
        #    vectorF = jetsAK4_var,
        #),
        # AK8 Jets
        cms.PSet(
            label = cms.untracked.string("jetsAK8"),
            key_label = cms.untracked.string("jetKeysAK8"),
            prefix_in = jetsAK8.prefix,
            prefix_out = cms.untracked.string("jetAK8_"),
            vectorF = jetsAK8_var,
        ),
        # Subjets of AK8 Jets
        cms.PSet(
            label = cms.untracked.string("subjetsAK8"),
            key_label = cms.untracked.string("subjetKeysAK8"),
            prefix_in = subjetsAK8.prefix,
            prefix_out = cms.untracked.string("subjetAK8_"),
            vectorF = subjetsAK8_var,
        ),
        # Subjets of CMS Top-tag Jets
        cms.PSet(
            label = cms.untracked.string("subjetsCmsTopTag"),
            key_label = cms.untracked.string("subjetsCmsTopTagKeys"),
            prefix_in = subjetsCmsTopTag.prefix,
            prefix_out = cms.untracked.string("subjetsCmsTopTag_"),
            vectorF = subjetsCmsTopTag_var,
        ),
        # AK8 Gen jets
        #cms.PSet(
        #    label = cms.untracked.string("genJetsAK8"),
        #    prefix_in = genJetsAK8.prefix,
        #    prefix_out = cms.untracked.string("genjetAK8_"),
        #    vectorF = genJetsAK8_var,
        #    mc_only = cms.untracked.bool(True),
        #),
        # AK8 Gen jets (with SoftDrop grooming)
        cms.PSet(
            label = cms.untracked.string("genJetsAK8SoftDrop"),
            prefix_in = genJetsAK8SoftDrop.prefix,
            prefix_out = cms.untracked.string("genjetAK8SD_"),
            vectorF = genJetsAK8SoftDrop_var,
            mc_only = cms.untracked.bool(True),
        ),
    )
)
