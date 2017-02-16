import FWCore.ParameterSet.Config as cms
import copy
import os

# Default settings: add all variables from b2gedmntuples_cff
# Set to false, and define your own lists (eg. comment out unused vairables)
getVariablesFromConfig = False

from Analysis.B2GAnaFW.b2gedmntuples_cff import puppimetFull, metFull, genPart, electrons, muons, photons, photonjets, jetsAK4CHS, jetsAK4Puppi, jetsAK8CHS, subjetsAK8CHS, jetsAK8Puppi, subjetsAK8Puppi, genJetsAK8, genJetsAK8SoftDrop, eventInfo # metNoHF, subjetsCmsTopTag off since 76X

if getVariablesFromConfig:
    
    #metNoHF_var = cms.untracked.vstring()
    #for pset in metNoHF.variables:
    #    s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
    #    metNoHF_var.append(s)
    
    metFull_var = cms.untracked.vstring()
    for pset in metFull.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        metFull_var.append(s)

    puppimetFull_var = cms.untracked.vstring()
    for pset in puppimetFull.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        puppimetFull_var.append(s)

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
    
    jetsAK4CHS_var = cms.untracked.vstring()
    for pset in jetsAK4CHS.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK4CHS_var.append(s)
    
    jetsAK4Puppi_var = cms.untracked.vstring()
    for pset in jetsAK4Puppi.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK4Puppi_var.append(s)
    
    jetsAK8CHS_var = cms.untracked.vstring()
    for pset in jetsAK8CHS.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK8CHS_var.append(s)
    
    jetsAK8Puppi_var = cms.untracked.vstring()
    for pset in jetsAK8Puppi.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        jetsAK8Puppi_var.append(s)
    
    subjetsAK8CHS_var = cms.untracked.vstring()
    for pset in subjetsAK8CHS.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsAK8CHS_var.append(s)
    
    subjetsAK8Puppi_var = cms.untracked.vstring()
    for pset in subjetsAK8Puppi.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        subjetsAK8Puppi_var.append(s)
    
    #subjetsCmsTopTag_var = cms.untracked.vstring()
    #for pset in subjetsCmsTopTag.variables:
    #    s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
    #    subjetsCmsTopTag_var.append(s)
    
    genJetsAK8_var = cms.untracked.vstring()
    for pset in genJetsAK8.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        genJetsAK8_var.append(s)
    
    genJetsAK8SoftDrop_var = cms.untracked.vstring()
    for pset in genJetsAK8SoftDrop.variables:
        s = str(pset.tag).replace("cms.untracked.string('","").replace("')","")
        genJetsAK8SoftDrop_var.append(s)
else:
    # Currrent B2GAnaFW ver: 11 Jan (v8.0.x_v2.4 + PR66 ntuple version)
    metNoHF_var = cms.untracked.vstring(
        "Pt",
        #"Px",
        #"Py",
        "Phi",
        #"uncorPt",
        #"uncorPhi",
        #"uncorSumEt",
    )
    metFull_var      = copy.deepcopy(metNoHF_var)
    puppimetFull_var = copy.deepcopy(metNoHF_var)
    
    basicVars = cms.untracked.vstring(
        "Pt",
        "Eta",
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
        'Key',
        'Iso03',
        'Iso03db',
        'MiniIso',
        #'rho',
        #'EA',
        #'sumChargedHadronPt',
        #'sumNeutralHadronEt',
        #'sumPhotonEt',
        #'sumPUPt',
        'Dxy',
        'Dz',
        'DB',
        'DBerr',
        #'dEtaIn',
        #'dEtaInSeed',
        #'dPhiIn',
        #'HoE',
        #'full5x5siee',
        #'ooEmooP',
        #'missHits',
        #'hasMatchedConVeto',
        'SCEta',
        #'SCPhi',
        'vidVeto',
        'vidLoose',
        'vidMedium',
        'vidTight',
        'vidHEEP',
        'vidVetonoiso',
        'vidLoosenoiso',
        'vidMediumnoiso',
        'vidTightnoiso',
        'vidHEEPnoiso',
    )
    
    muonVars = cms.untracked.vstring(
        'Key',
        'Iso04',
        'MiniIso',
        'Dxy',
        'Dz',
        'DB',
        'DBerr',
        'IsSoftMuon',
        'IsLooseMuon',
        'IsMediumMuon',
        'IsMediumMuon2016',
        'IsTightMuon',
        'IsHighPtMuon',
        #'InnerTrackPt',
        #'TunePMuonBestTrackPt',
        #'IsPFMuon',
        #'IsGlobalMuon',
        #'IsTrackerMuon',
        #'CombQualChi2LocalPos',
        #'CombQualTrkKink',
        #'InTrkValidFraction',
        #'SegmentCompatibility',
        #'GlbTrkNormChi2',
        #'NumberValidMuonHits',
        #'NumberMatchedStations',
        #'NumberValidPixelHits',
        #'NumberTrackerLayers',
        #'NumberOfValidTrackerHits',
        #'NumberOfPixelLayers',
        #'InTrkNormChi2',
        #'SumChargedHadronPt',
        #'SumNeutralHadronPt',
        #'SumPhotonPt',
        #'SumPUPt',
        #'TrackerSumPt',
        #'GenMuonEta',
        #'GenMuonPhi',
        #'GenMuonPt',
        #'GenMuonE',
        #'GenMuonCharge',
    )
    
    photonVars = cms.untracked.vstring(
        'SCEta',
        'SCPhi',
        'SCRawE',
        'HasPixelSeed',
        'ElectronVeto',
        'SigmaIEtaIEta',
        'SigmaIEtaIPhi',
        'SigmaIPhiIPhi',
        'E1x5',
        'E5x5',
        'HoverE',
        'R9',
        'ChargedHadronIso',
        'PhotonIso',
        'NeutralHadronIso',
        'PhotonIsoEAcorrectedsp15',
        'NeutralHadronIsoEAcorrectedsp15',
        'PassLooseID',
        'PassMediumID',
        'PassTightID',
    )
    
    photonjetVars = cms.untracked.vstring(
        'JetIndex',
        'PhotonIndex',
        'SubwGammatIndex',
        'PhotonSubjetFrac',
        'SubjetPt0',
        'SubjetPt1',
        'SubjetPt2',
        'SubjetEta0',
        'SubjetEta1',
        'SubjetEta2',
        'SubjetPhi0',
        'SubjetPhi1',
        'SubjetPhi2',
        'SubjetEne0',
        'SubjetEne1',
        'SubjetEne2',
    )
    
    jetVars = cms.untracked.vstring(
        'CSVv2',
        'CMVAv2',
        'CvsL',
        'CvsB',
        'GenPartonEta',
        'GenPartonPhi',
        'GenPartonPt',
        'GenPartonE',
        'GenPartonCharge',
        'PartonFlavour',
        'HadronFlavour',
        'GenJetEta',
        'GenJetPhi',
        'GenJetPt',
        'GenJetE',
        'GenJetCharge',
        #'muonMultiplicity',
        #'PhotonEnergy',
        #'ElectronEnergy',
        #'MuonEnergy',
        #'neutralEmEnergy',
        #'photonMultiplicity',
        #'electronMultiplicity',
        #'ChargedMuEnergy',
        #'neutralMultiplicity',
        #'neutralHadronEnergyFrac',
        #'neutralEmEnergyFrac',
        #'chargedHadronEnergyFrac',
        #'chargedEmEnergyFrac',
        #'chargedMultiplicity',
        'jecFactor0',
        #'jecFactorL3Absolute',
        #'jetArea',
        #'nSV',
        #'SV0mass',
        #'SV1mass',
    )
    
    jetVarsForSys = cms.untracked.vstring(
        'jecUncertainty',
        #'PtResolution',
        'JERSF',
        'JERSFUp',
        'JERSFDown',
        'SmearedPt',
    )
    
    ## jetVarsJEC = cms.untracked.vstring(
    ##     "jecFactor0",
    ##     "jecFactorL1FastJet",
    ##     "jecFactorL3Absolute",
    ##     "jetArea",
    ## )
    
    qglVars = cms.untracked.vstring(
        #"QGL",
    )
    
    jetAK8Vars = cms.untracked.vstring(
        'vSubjetIndex0',
        'vSubjetIndex1',
        'tau1',
        'tau2',
        'tau3',
        'softDropMass',
        #'trimmedMass',
        #'prunedMass',
        #'filteredMass',
    )

    jetToolboxAK8Vars = cms.untracked.vstring(
        #'DoubleBAK8',
        #'DoubleBCA15',
        'vSubjetIndex0',
        'vSubjetIndex1',
        #'vSubjetPuppiIndex0',
        #'vSubjetPuppiIndex1',
        'tau1CHS',
        'tau2CHS',
        'tau3CHS',
        'softDropMassCHS',
        #'trimmedMassCHS',
        #'prunedMassCHS',
        #'filteredMassCHS',
        'softDropMassPuppi',
        "PtPuppi",
        "EtaPuppi",
        "PhiPuppi",
        "MassPuppi",
        'tau1Puppi',
        'tau2Puppi',
        'tau3Puppi',
    )
    
    jetToolboxAK8PuppiVars = cms.untracked.vstring(
        'DoubleBAK8',
        'DoubleBCA15',
        'vSubjetIndex0',
        'vSubjetIndex1',
        'tau1',
        'tau2',
        'tau3',
        'softDropMass',
        #'trimmedMass',
        #'prunedMass',
        #'filteredMass',
    )
    
    jetToolboxAK8SubjetVars = cms.untracked.vstring(
        #'tau1',
        #'tau2',
        #'tau3',
    )
    
    jetToolboxAK8SubjetPuppiVars = cms.untracked.vstring(
        #'tau1',
        #'tau2',
        #'tau3',
    )
    
    genPart_var    = copy.deepcopy(basicVars)
    genPart_var   += genPartVars
    
    electrons_var  = copy.deepcopy(basicVars)
    electrons_var += electronVars
    
    muons_var      = copy.deepcopy(basicVars)
    muons_var     += muonVars
    
    photons_var    = copy.deepcopy(photonVars)
    
    photonjets_var = copy.deepcopy(photonjetVars)
    
    jetsAK4CHS_var      = copy.deepcopy(basicVars)
    jetsAK4CHS_var     += jetVars
    jetsAK4CHS_var     += qglVars
    jetsAK4CHS_var     += jetVarsForSys
    
    jetsAK4Puppi_var    = copy.deepcopy(basicVars)
    jetsAK4Puppi_var   += jetVars
    jetsAK4Puppi_var   += jetVarsForSys
    
    jetsAK8CHS_var      = copy.deepcopy(basicVars)
    jetsAK8CHS_var     += jetVars
    jetsAK8CHS_var     += jetVarsForSys
    jetsAK8CHS_var     += jetToolboxAK8Vars
    
    jetsAK8Puppi_var    = copy.deepcopy(basicVars)
    jetsAK8Puppi_var   += jetVars
    jetsAK8Puppi_var   += jetVarsForSys
    jetsAK8Puppi_var   += jetToolboxAK8PuppiVars
    
    subjetsAK8CHS_var   = copy.deepcopy(basicVars)
    subjetsAK8CHS_var  += jetVars
    subjetsAK8CHS_var  += jetToolboxAK8SubjetVars
    
    subjetsAK8Puppi_var = copy.deepcopy(subjetsAK8CHS_var)
    
    #subjetsCmsTopTag_var  = copy.deepcopy(basicVars)
    #subjetsCmsTopTag_var += jetVars
    
    genJetsAK8_var = copy.deepcopy(basicVars)
    
    genJetsAK8SoftDrop_var = copy.deepcopy(basicVars)

B2GTTreeMaker = cms.EDAnalyzer("B2GTTreeMaker",
    isData = cms.untracked.bool(False),
    physicsObjects = cms.VPSet(
        # Event infos
        #cms.PSet(
        #    label = cms.untracked.string("eventUserData"),
        #    prefix_in = cms.untracked.string(""),
        #    prefix_out = cms.untracked.string("evt_"),
        #),
        cms.PSet(
            label = cms.untracked.string("eventInfo"),
            prefix_in = eventInfo.prefix,
            prefix_out = cms.untracked.string("evt_"),
            singleUI = cms.untracked.vstring("RunNumber", "LumiBlock"),
            singleULL = cms.untracked.vstring("EventNumber"),
        ),
        #cms.PSet(
        #    label = cms.untracked.string("fixedGridRhoFastjetAll"),
        #    prefix_in = cms.untracked.string(""),
        #    prefix_out = cms.untracked.string("evt_rho"),
        #    singleD = cms.untracked.vstring(""),
        #),
        # Pileup
        cms.PSet(
            label = cms.untracked.string("eventUserData"),
            prefix_in = cms.untracked.string("pu"),
            prefix_out = cms.untracked.string("pu_"),
            singleI = cms.untracked.vstring("NtrueInt"),
            #vectorI = cms.untracked.vstring("BX","NInt"),
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
        #cms.PSet(
        #    label = cms.untracked.string("vertexInfo"),
        #    prefix_in = cms.untracked.string(""),
        #    prefix_out = cms.untracked.string("vtx_"),
        #    singleI = cms.untracked.vstring("npv"),
        #    vectorI = cms.untracked.vstring("ndof"),
        #    vectorF = cms.untracked.vstring("z","rho","chi", "vx", "vy", "vz"),
        #),
        # MET Filters
        cms.PSet(
            label = cms.untracked.string("BadPFMuonFilter"),
            prefix_in = cms.untracked.string(""),
            prefix_out = cms.untracked.string("Flag_BadPFMuonFilter"),
            singleB = cms.untracked.vstring("")
        ),
        cms.PSet(
            label = cms.untracked.string("BadChargedCandidateFilter"),
            prefix_in = cms.untracked.string(""),
            prefix_out = cms.untracked.string("Flag_BadChargedCandidateFilter"),
            singleB = cms.untracked.vstring("")
        ),
        # MET
        #cms.PSet(
        #    label = cms.untracked.string("metNoHF"),
        #    prefix_in = metNoHF.prefix,
        #    prefix_out = cms.untracked.string("met_NoHF_"),
        #    vectorF = metNoHF_var,
        #),
        cms.PSet(
            label = cms.untracked.string("metFull"),
            prefix_in = metFull.prefix,
            prefix_out = cms.untracked.string("met_"),
            vectorF = metFull_var,
        ),
        cms.PSet(
            label = cms.untracked.string("puppimetFull"),
            prefix_in = puppimetFull.prefix,
            prefix_out = cms.untracked.string("puppimet_"),
            vectorF = puppimetFull_var,
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
            label = cms.untracked.string("jetsAK4CHS"),
            key_label = cms.untracked.string("jetKeysAK4CHS"),
            prefix_in = jetsAK4CHS.prefix,
            prefix_out = cms.untracked.string("jetAK4CHS_"),
            vectorF = jetsAK4CHS_var,
        ),
        # AK4 Puppi Jets
        #cms.PSet(
        #    label = cms.untracked.string("jetsAK4Puppi"),
        #    key_label = cms.untracked.string("jetKeysAK4Puppi"),
        #    prefix_in = jetsAK4Puppi.prefix,
        #    prefix_out = cms.untracked.string("jetAK4Puppi_"),
        #    vectorF = jetsAK4Puppi_var,
        #),
        # AK8 CHS Jets
        cms.PSet(
            label = cms.untracked.string("jetsAK8CHS"),
            key_label = cms.untracked.string("jetKeysAK8CHS"),
            prefix_in = jetsAK8CHS.prefix,
            prefix_out = cms.untracked.string("jetAK8CHS_"),
            vectorF = jetsAK8CHS_var,
        ),
        # AK8 Puppi Jets
        #cms.PSet(
        #    label = cms.untracked.string("jetsAK8Puppi"),
        #    key_label = cms.untracked.string("jetKeysAK8Puppi"),
        #    prefix_in = jetsAK8Puppi.prefix,
        #    prefix_out = cms.untracked.string("jetAK8Puppi_"),
        #    vectorF = jetsAK8Puppi_var,
        #),
        # Subjets of AK8 Jets
        cms.PSet(
            label = cms.untracked.string("subjetsAK8CHS"),
            key_label = cms.untracked.string("subjetKeysAK8CHS"),
            prefix_in = subjetsAK8CHS.prefix,
            prefix_out = cms.untracked.string("subjetAK8CHS_"),
            vectorF = subjetsAK8CHS_var,
        ),
        # Subjets of AK8 Puppi Jets
        #cms.PSet(
        #    label = cms.untracked.string("subjetsAK8Puppi"),
        #    key_label = cms.untracked.string("subjetKeysAK8Puppi"),
        #    prefix_in = subjetsAK8Puppi.prefix,
        #    prefix_out = cms.untracked.string("subjetAK8Puppi_"),
        #    vectorF = subjetsAK8Puppi_var,
        #),
        # Subjets of CMS Top-tag Jets
        #cms.PSet(
        #    label = cms.untracked.string("subjetsCmsTopTag"),
        #    key_label = cms.untracked.string("subjetsCmsTopTagKeys"),
        #    prefix_in = subjetsCmsTopTag.prefix,
        #    prefix_out = cms.untracked.string("subjetsCmsTopTag_"),
        #    vectorF = subjetsCmsTopTag_var,
        #),
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
