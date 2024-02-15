#include "Constants.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

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

using namespace example;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  gROOT->Reset();

  //  creat file
  G4int save_flag = 1;
  mkdir(DATAPATH, 0777);

  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Set the Random engine and the seed
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);

  // Construct the default run manager
  G4RunManager* run_manager = new G4RunManager;

  // Set mandatory initialization classes
  DetectorConstruction* detector = new example::DetectorConstruction();

  run_manager->SetUserInitialization(detector);
  G4VModularPhysicsList* physics_list = new FTFP_BERT;
  physics_list->RegisterPhysics(new G4StepLimiterPhysics());
  run_manager->SetUserInitialization(physics_list);
  // Set user action classes
  run_manager->SetUserInitialization(new example::ActionInitialization(detector, save_flag));

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
