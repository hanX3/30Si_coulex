#include "BGOSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BGOSD::BGOSD(const G4String& name, const G4String& hits_collection_name)
 : G4VSensitiveDetector(name)
{
  // collectionName var inherit from G4VSensitiveDetector, do not change
  // collectionName must be set
  collectionName.insert(hits_collection_name);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void BGOSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  hits_collection = new BGOHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hc_id = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hc_id, hits_collection);

  hits_collection->insert(new BGOHit());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool BGOSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  // energy deposit
  G4double e = step->GetTotalEnergyDeposit();
  if(e==0.) return false;

  BGOHit *hit = (*hits_collection)[0];
  hit->SetTrackID(step->GetTrack()->GetTrackID());
  hit->AddEdep(e);
  hit->SetPos(step->GetPostStepPoint()->GetPosition());

  // hit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void BGOSD::EndOfEvent(G4HCofThisEvent*)
{
  if(verboseLevel>1){
     G4int n_of_hits = hits_collection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << n_of_hits
            << " hits in the tracker chambers: " << G4endl;
     for(G4int i=0;i<n_of_hits;i++){ 
       (*hits_collection)[i]->Print();
     }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

