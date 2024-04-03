#include "Constants.hh"
#include "DetectorConstruction.hh"
#include "Projectile.hh"
#include "Recoil.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "sys/stat.h" //  mkdir
#include "TROOT.h"

//
int main(int argc, char** argv)
{
  gROOT->Reset();

  // creat file
  G4int save_flag = 1;
  mkdir(DATAPATH, 0777);

  //
  G4UIExecutive* ui = 0;
  if(argc == 1){
    ui = new G4UIExecutive(argc, argv);
  }

  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);

  //
  G4RunManager* run_manager = new G4RunManager;
  DetectorConstruction *detector = new DetectorConstruction();
  run_manager->SetUserInitialization(detector);
  
  Projectile *projectile = new Projectile();
  projectile->SetZ(12);
  projectile->SetA(20);
  projectile->SetKE(50. *MeV);
  projectile->SetEx(1.598 *MeV);
  projectile->SetTau(2.2 *ps);
  projectile->SetFcX(0. *mm);
  projectile->SetFcY(8. *mm);
  projectile->SetFcDX(0. *mm);
  projectile->SetFcDY(0. *mm);
  projectile->Report();

  Recoil *recoil = new Recoil();
  recoil->SetZ(4);
  recoil->SetA(9);
  recoil->SetEx(0. *MeV);
  recoil->SetTau(0. *ps);
  recoil->Report();

  PhysicsList *physcis_list = new PhysicsList(projectile, recoil, detector);
  run_manager->SetUserInitialization(physcis_list);

  PrimaryGeneratorAction *generator_action = new PrimaryGeneratorAction(detector, projectile);
  run_manager->SetUserAction(generator_action);

  RootIO *root_io = new RootIO(save_flag);
  RunAction *run_action = new RunAction(physcis_list, root_io, detector);
  run_manager->SetUserAction(run_action);

  G4cout << "!! in main function test !!" << G4endl;
  EventAction *event_action = new EventAction(root_io, run_action, projectile, detector);
  run_manager->SetUserAction(event_action);

  if((MASK&0b010)==0b010){
    TrackingAction *tracking_action = new TrackingAction(detector, root_io);
    run_manager->SetUserAction(tracking_action);
  }
  if((MASK&0b100)==0b100){
    SteppingAction *stepping_action = new  SteppingAction(detector, root_io);
    run_manager->SetUserAction(stepping_action);
  }

  // Initialize visualization
  G4VisManager* vis_manager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  vis_manager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* ui_manager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if(!ui){
    // batch mode
    G4String command = "/control/execute ";
    G4String file_name = argv[1];
    ui_manager->ApplyCommand(command+file_name);
  }
  else{
    // interactive mode
    ui_manager->ApplyCommand("/control/execute init_vis.mac");
    if(ui->IsGUI()) {
      ui_manager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !
  //
  delete vis_manager;
  delete run_manager;
}

