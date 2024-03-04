#ifndef B2EventAction_h
#define B2EventAction_h 1

#include "Constants.hh"
#include "DataStructure.hh"
#include "SiHit.hh"
#include "RootIO.hh"
#include "globals.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "TMath.h"
#include "TFile.h"


/// Event action class
class EventAction : public G4UserEventAction
{
public:
  EventAction(PrimaryGeneratorAction *pg, RootIO *rio);
  ~EventAction() override;

  void  BeginOfEventAction(const G4Event* ) override;
  void  EndOfEventAction(const G4Event* ) override;

private:
  EventData event_data;

  PrimaryGeneratorAction* primary;
  RootIO* root_io;    
};


#endif
