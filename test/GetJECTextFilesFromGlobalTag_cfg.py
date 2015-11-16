import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts

options = opts.VarParsing('analysis')

options.register('jetColl',
                 'AK4PFchs',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Name of the jet collaction payload')

options.register('globalTag',
                 "",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'GlobalTag')

options.register('DataProcessing',
                 "",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Data processing types. Options are: MC50ns, MC25ns, Data50ns, Data25ns')

options.register('usePrivateSQLite',
                 True,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.bool,
                 'Take Corrections from private SQL file')

options.register('era',
                 "",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Data acquisition era')


options.parseArguments()

process = cms.Process("jectxt")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = options.globalTag

if options.globalTag == "": 
  if options.DataProcessing=="MC50ns":
    options.globalTag="MCRUN2_74_V9A"
  elif options.DataProcessing=="MC25ns":
    options.globalTag="MCRUN2_74_V9"
  elif options.DataProcessing=="Data50ns":
    options.globalTag="74X_dataRun2_Prompt_v0"
  elif options.DataProcessing=="Data25ns":
    options.globalTag="74X_dataRun2_Prompt_v1"

gtName = options.globalTag

# Use private JEC sqlite file
if options.usePrivateSQLite:
    from CondCore.DBCommon.CondDBSetup_cfi import *
    if options.era == "":
        if options.DataProcessing=="Data50ns":
            options.era="Summer15_50nsV5_DATA"
        elif options.DataProcessing=="Data25ns":
            options.era="Summer15_25nsV6_DATA"
        elif options.DataProcessing=="MC50ns":
            options.era="Summer15_50nsV5_DATA"
        elif options.DataProcessing=="MC25ns":
            options.era="Summer15_25nsV6_MC"
    gtName = options.era
    dBFile = options.era+".db"
    print "\nUsing private SQLite file", dBFile, "\n"
    process.jec = cms.ESSource("PoolDBESSource",
        CondDBSetup,
        connect = cms.string( "sqlite_file:"+dBFile ),
        toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+options.era+"_AK4PF"),
                label= cms.untracked.string("AK4PF")
                ),
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+options.era+"_AK4PFchs"),
                label= cms.untracked.string("AK4PFchs")
                ),
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+options.era+"_AK8PF"),
                label= cms.untracked.string("AK8PF")
                ),
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+options.era+"_AK8PFchs"),
                label= cms.untracked.string("AK8PFchs")
                ),
            )
        )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source("EmptySource")
process.readFromGT = cms.EDAnalyzer('JetCorrectorDBReader',  
      # below is the communication to the database 
      payloadName    = cms.untracked.string(options.jetColl),
      # this is used ONLY for the name of the printed txt files. You can use any name that you like, 
      # but it is recommended to use the GT name that you retrieved the files from.
      globalTag      = cms.untracked.string(gtName),
      printScreen    = cms.untracked.bool(False),
      createTextFile = cms.untracked.bool(True)
)
process.p = cms.Path(process.readFromGT)
