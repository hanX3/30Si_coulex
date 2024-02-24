#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "RootIO.hh"

namespace coulex
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ActionInitialization::ActionInitialization(DetectorConstruction* dc, G4int save)
: G4VUserActionInitialization(),
  detector_construction(dc),
  save_flag(save)
{

}

//
ActionInitialization::~ActionInitialization()
{

}

//
void ActionInitialization::BuildForMaster() const
{
  PrimaryGeneratorAction* pri_gen = new PrimaryGeneratorAction();
  RootIO* root_io = new RootIO(save_flag);

  SetUserAction(new RunAction(pri_gen, root_io));
}

//
void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* pri_gen = new PrimaryGeneratorAction();
  RootIO* root_io = new RootIO(save_flag);

  SetUserAction(pri_gen);
  SetUserAction(new RunAction(pri_gen, root_io));
  SetUserAction(new EventAction(pri_gen, root_io));
  if((MASK&0b010)==0b010){
    SetUserAction(new TrackingAction(detector_construction, root_io));
  }
  if((MASK&0b100)==0b100){
    SetUserAction(new SteppingAction(detector_construction, root_io));
  }
}

//
}

