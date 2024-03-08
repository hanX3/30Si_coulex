#ifndef B2RunAction_h
#define B2RunAction_h 1

#include "Constants.hh"
#include "PhysicsList.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "G4UserRunAction.hh"

#include "globals.hh"
#include "unistd.h"
#include <fstream>
#include <string>
#include <sys/time.h>



//
class RunAction : public G4UserRunAction
{
public:
  RunAction(PhysicsList *pl, RootIO *ri, DetectorConstruction *dc);
  ~RunAction() override;

  void BeginOfRunAction(const G4Run* run) override;
  void EndOfRunAction(const G4Run* run) override;

private:
  G4Timer *timer;
  PhysicsList *physics_list;    
  RootIO *root_io;
  DetectorConstruction *detector_construction;
};

#endif
