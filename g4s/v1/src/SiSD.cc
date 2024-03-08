#include "SiSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//
SiSD::SiSD(const G4String& name, const G4String& hits_collection_name)
 : G4VSensitiveDetector(name)
{
  collectionName.insert(hits_collection_name);

  hits_collection = nullptr;
  hc_id = -1;
}

//
void SiSD::Initialize(G4HCofThisEvent *hce)
{
  // Create hits collection
  hits_collection = new SiHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  if(hc_id<0){
    hc_id = G4SDManager::GetSDMpointer()->GetCollectionID(hits_collection);
  }
  G4cout << "-----> in SiSD Initialize() function hc_id " << hc_id << G4endl;
  hce->AddHitsCollection(hc_id, hits_collection);

  for(int i=0;i<RingNumber;i++){
    for(int j=0;j<SectorNumber;j++){
      hits_collection->insert(new SiHit());
    }
  } 
}

//
G4bool SiSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  // energy deposit
  G4double e = step->GetTotalEnergyDeposit();
  if(e==0.) return false;

  auto touchable = step->GetPreStepPoint()->GetTouchable();
  auto physical = touchable->GetVolume();
  auto copy_no = physical->GetCopyNo();
  G4cout << "-----> in SiSD ProcessHits function copy_no " << copy_no << G4endl;

  G4int ring_id = copy_no/RingNumber;
  G4int sector_id = copy_no%SectorNumber;
  G4cout << "-----> in SiSD ProcessHits function ring_id " << ring_id << G4endl;
  G4cout << "-----> in SiSD ProcessHits function sector_id " << sector_id << G4endl;
  
  // check if the first touch
  auto hit = (*hits_collection)[copy_no];
  if(hit->GetRingId()<0 || hit->GetSectorId()<0){
    hit->SetRingId(ring_id);
    hit->SetSectorId(sector_id);
    
    auto pre_step_point = step->GetPreStepPoint();
    auto world_pos = pre_step_point->GetPosition();
    auto pos = touchable->GetHistory()->GetTopTransform().TransformPoint(world_pos);
    hit->SetPos(pos);
  }
  hit->AddEdep(e);

  return true;
}

//
void SiSD::EndOfEvent(G4HCofThisEvent*)
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

