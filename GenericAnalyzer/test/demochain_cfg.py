import FWCore.ParameterSet.Config as cms
process = cms.Process("Demo")
process.load("FWCore.MessageService.MessageLogger_cfi")

process.demo = cms.EDAnalyzer('Genmochain',
							  GenLabel = cms.InputTag('genParticles'),
							  pdgId = cms.int32(22),
							  collisionId = cms.int32(-1), # -1: all, 0: ==0, 1: !=0
							  status = cms.int32(-1),
							  maxlayer = cms.int32(2),
							  motherOrdaughter = cms.int32(0), # mother: 0, daughter: 1
)

process.p = cms.Path(process.demo)
process.schedule = cms.Schedule(process.p)

##
import FWCore.ParameterSet.VarParsing as VarParsing
ivars = VarParsing.VarParsing('analysis')

ivars.register('firstEvent',
			   0, # default value
			   VarParsing.VarParsing.multiplicity.singleton, # singleton or list
			   VarParsing.VarParsing.varType.int,          # string, int, or float
)

##
ivars.firstEvent = 0
# ivars.inputFiles = 'file:step2_reco_1370.root'
ivars.inputFiles='file:A62F3E6D-1D80-E911-B8F9-842B2B181788.root'
ivars.parseArguments()

process.source = cms.Source("PoolSource",
							fileNames = cms.untracked.vstring(ivars.inputFiles),
							skipEvents = cms.untracked.uint32(ivars.firstEvent)
)

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(1)
)
