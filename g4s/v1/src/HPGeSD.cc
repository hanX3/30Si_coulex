#include "HPGeSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HPGeSD::HPGeSD(const G4String& name, const G4String& hits_collection_name)
 : G4VSensitiveDetector(name)
{
  collectionName.insert(hits_collection_name);

  hits_collection = nullptr;
  hc_id = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HPGeSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  hits_collection = new HPGeHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  if(hc_id<0){
    hc_id = G4SDManager::GetSDMpointer()->GetCollectionID(hits_collection);
  }
  G4cout << "----> in HPGeSD Initialize function hc_id " << hc_id << G4endl;
  hce->AddHitsCollection(hc_id, hits_collection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool HPGeSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  auto e = step->GetTotalEnergyDeposit();
  if (e==0.) return true;

  auto touchable = step->GetPreStepPoint()->GetTouchable();
  auto physical = touchable->GetVolume();
  auto copy_no = physical->GetCopyNo();
  G4cout << "-----> in HPGeSD ProcessHits function copy_no " << copy_no << G4endl;

  // check if this detector already has a hit
  auto ix = -1;
  for(auto i=0;i<hits_collection->entries();++i){
    if((*hits_collection)[i]->GetID()==copy_no){
      ix = i;
      break;
    }
  }
 
  if(ix>=0){
    // if it has
    (*hits_collection)[ix]->AddEdep(e);
  }else{
    // if not, create a new hit and set it to the collection
    auto hit = new HPGeHit();
    hit->SetID(copy_no);
    hit->AddEdep(e);
   
    auto pre_step_point = step->GetPreStepPoint();
    auto world_pos = pre_step_point->GetPosition();
    auto pos = touchable->GetHistory()->GetTopTransform().TransformPoint(world_pos);
    hit->SetPos(pos);
 
    hits_collection->insert(hit);
  }

  // hit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HPGeSD::EndOfEvent(G4HCofThisEvent*)
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


