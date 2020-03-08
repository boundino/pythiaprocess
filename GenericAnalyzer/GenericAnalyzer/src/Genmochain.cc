// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
// #include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// #include "DataFormats/TrackReco/interface/Track.h"
// #include "DataFormats/TrackReco/interface/TrackFwd.h"
// #include "DataFormats/MuonReco/interface/Muon.h"
// #include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h" 
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
// #include "DataFormats/JetReco/interface/GenJet.h"

#include "TLorentzVector.h"

// #include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
// #include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
// #include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
// #include "SimDataFormats/TrackingHit/interface/PSimHit.h"
// #include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"
// #include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
// #include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
// #include "SimTracker/Records/interface/TrackAssociatorRecord.h"
// #include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
//#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"
//
// class declaration
//

class Genmochain : public edm::EDAnalyzer {
public:
  explicit Genmochain(const edm::ParameterSet&);
  ~Genmochain();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  const reco::Candidate* ffirst;
  const reco::GenParticle* ffirst_gen;
  std::vector<bool> flastll;
  void printline(const reco::Candidate* me);
  void printline(const reco::GenParticle& me);
  void drawline(int layer, bool lastornot, std::vector<bool> lastll);
  void printmo(const reco::GenParticle& me);
  void showmo(const reco::Candidate* me, int layer, std::vector<bool> lastll);
  void showmo(const reco::GenParticle& me, int layer, std::vector<bool> lastll);

  edm::EDGetTokenT< reco::GenParticleCollection > genLabel_;
};

Genmochain::Genmochain(const edm::ParameterSet& iConfig)
{
  genLabel_           = consumes< reco::GenParticleCollection >(iConfig.getParameter<edm::InputTag>("GenLabel"));
  // edm::Service<TFileService> fs;
  ffirst = 0;
}

Genmochain::~Genmochain()
{
}

// ------------ method called for each event  ------------
void
Genmochain::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;
	
  edm::Handle<reco::GenParticleCollection> parts;
  iEvent.getByToken(genLabel_, parts);

  if(parts->size() <= 0) return;
  ffirst = &((*parts)[0]);
  ffirst_gen = &((*parts)[0]);
  for(unsigned int i = 0; i < parts->size(); ++i)
    {
      const reco::GenParticle& p = (*parts)[i];
      int pdg = p.pdgId();

      if(abs(pdg) != 421) continue;
      printmo(p);
    }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
Genmochain::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Genmochain::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
Genmochain::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
Genmochain::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Genmochain::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Genmochain::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Genmochain::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void
Genmochain::printline(const reco::Candidate* me)
{
  std::cout<<"\e[32m"<<int(me-ffirst)<<"\e[0m \e[2m=>\e[0m \e[1m"<<me->pdgId()<<"\e[0m \e[33m("<<me->status()<<")\e[0m \e[34m.. "<<me->pt()<<", "<<me->phi()/M_PI<<"\e[0m"<<std::endl;
}

void
Genmochain::printline(const reco::GenParticle& me)
{
  std::cout<<"\e[32m"<<int(&me-ffirst_gen)<<"\e[0m \e[2m=>\e[0m \e[1m"<<me.pdgId()<<"\e[0m \e[33m("<<me.status()<<")\e[0m \e[34m.. "<<me.pt()<<", "<<me.phi()/M_PI<<"\e[0m"<<std::endl;
}

void
Genmochain::drawline(int layer, bool lastornot, std::vector<bool> lastll)
{
  for(int i=0; i<layer; i++)
    {
      std::cout<<(lastll[i]?"    ":"\u2502   ");
    }
  std::cout<<(lastornot?"\u2514":"\u251C")<<"\u2500\u2500 ";
}

void
Genmochain::printmo(const reco::GenParticle& me)
{
  flastll.clear();
  flastll.push_back(true);

  printline(me);
  showmo(me, 1, flastll);
  std::cout<<std::endl;
}

void
Genmochain::showmo(const reco::GenParticle& me, int layer, std::vector<bool> lastll)
{
  int nmo = me.numberOfMothers();
  if(nmo <= 0) return;

  for(int i=0; i<nmo; i++)
    {
      const reco::Candidate* imo = me.mother(i);
      drawline(layer, i==(nmo-1), lastll);
      printline(imo);
      std::vector<bool> lastmo(lastll); lastmo.push_back(i==(nmo-1));
      showmo(imo, layer+1, lastmo);
    }
}

void
Genmochain::showmo(const reco::Candidate* me, int layer, std::vector<bool> lastll)
{
  int nmo = me->numberOfMothers();
  if(nmo <= 0) return;

  for(int i=0; i<nmo; i++)
    {
      const reco::Candidate* imo = me->mother(i);
      drawline(layer, i==(nmo-1), lastll);
      printline(imo);
      std::vector<bool> lastmo(lastll); lastmo.push_back(i==(nmo-1));
      showmo(imo, layer+1, lastmo);
    }
}

//define this as a plug-in
DEFINE_FWK_MODULE(Genmochain);
