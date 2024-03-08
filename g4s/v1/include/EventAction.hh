#ifndef B2EventAction_h
#define B2EventAction_h 1

#include "Constants.hh"
#include "DataStructure.hh"
#include "SiHit.hh"
#include "RootIO.hh"
#include "globals.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "Projectile.hh"

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

//
class EventAction : public G4UserEventAction
{
public:
  EventAction(RootIO *ri, RunAction *ra, Projectile *pro, DetectorConstruction *dc);
  ~EventAction() override;

  void BeginOfEventAction(const G4Event* ) override;
  void EndOfEventAction(const G4Event* ) override;

private:
  G4int hc_id_si;
  G4int hc_id_hpge;
  G4int hc_id_clover;

private:
  EventData event_data;

  RootIO *root_io;
  RunAction *run_action;
  Projectile *projectile;
  DetectorConstruction *detector_construction;
};


#endif
