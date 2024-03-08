#include "EventAction.hh"

//
EventAction::EventAction(RootIO *ri, RunAction *ra, Projectile *pro, DetectorConstruction *dc)
: G4UserEventAction(),
  root_io(ri),
  run_action(ra),
  projectile(pro),
  detector_construction(dc)
{
  hc_id_si = -1;
  hc_id_hpge = -1;
  hc_id_clover = -1;

  event_data.Clear();
}

//
EventAction::~EventAction()
{

}

//
void EventAction::BeginOfEventAction(const G4Event*)
{
  G4cout << "in EventAction::BeginOfEventAction() ---> test!" << G4endl;
  auto sd_manager = G4SDManager::GetSDMpointer();

  hc_id_si = sd_manager->GetCollectionID("S3SiSD/SiHitCollection");
  hc_id_hpge = sd_manager->GetCollectionID("HPGeSD/HPGeHitCollection");
  hc_id_clover = sd_manager->GetCollectionID("CloverSD/HPGeHitCollection");
}

//
void EventAction::EndOfEventAction(const G4Event* event)
{
  G4cout << "in EventAction::EndOfEventAction() ---> test!" << G4endl;

  if((MASK&0b001)==0b001){
    auto hce = event->GetHCofThisEvent();

    // s3 si array, id 0-767
    auto hc_si = static_cast<SiHitsCollection*>(hce->GetHC(hc_id_si));
    for(auto i=0;i<hc_si->GetSize();i++){
      event_data.event_id = event->GetEventID(); 
      event_data.detector_id = i;
      event_data.e = (*hc_si)[i]->GetEdep();
      event_data.x = (*hc_si)[i]->GetPos().x();
      event_data.y = (*hc_si)[i]->GetPos().y();
      event_data.z = (*hc_si)[i]->GetPos().z();
      
      if(event_data.e > 0.){
        root_io->FillEventTree(event_data);
        G4cout << "in EventAction::EndOfEventAction() i " << i << G4endl;
      }
    }

    // hpge array id 1000-1015
    auto hc_hpge = static_cast<HPGeHitsCollection*>(hce->GetHC(hc_id_hpge));
    for(auto i=0;i<hc_hpge->GetSize();i++){
      event_data.event_id = event->GetEventID(); 
      event_data.detector_id = (*hc_hpge)[i]->GetID()+1000;
      event_data.e = (*hc_hpge)[i]->GetEdep();
      event_data.x = (*hc_hpge)[i]->GetPos().x();
      event_data.y = (*hc_hpge)[i]->GetPos().y();
      event_data.z = (*hc_hpge)[i]->GetPos().z();
      
      if(event_data.e > 0.){
        root_io->FillEventTree(event_data);
        G4cout << "in EventAction::EndOfEventAction() i " << i << G4endl;
      }
    }

    // clover array id 2000-2031
    auto hc_clover = static_cast<HPGeHitsCollection*>(hce->GetHC(hc_id_clover));
    for(auto i=0;i<hc_clover->GetSize();i++){
      event_data.event_id = event->GetEventID(); 
      event_data.detector_id = (*hc_clover)[i]->GetID()+2000;
      event_data.e = (*hc_clover)[i]->GetEdep();
      event_data.x = (*hc_clover)[i]->GetPos().x();
      event_data.y = (*hc_clover)[i]->GetPos().y();
      event_data.z = (*hc_clover)[i]->GetPos().z();
      
      if(event_data.e > 0.){
        root_io->FillEventTree(event_data);
        G4cout << "in EventAction::EndOfEventAction() i " << i << G4endl;
      }
    }

  }

  // periodic printing
  G4int eventID = event->GetEventID();
  if ( eventID < 10 || eventID % 1000 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
  }
}


