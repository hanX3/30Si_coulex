#ifndef Target_h
#define Target_h 1

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"

using namespace CLHEP;

namespace coulex
{
//
class Target
{
public:
  Target(G4LogicalVolume *wl);
  ~Target();

public:
  G4LogicalVolume *world_log;

public:
  G4VPhysicalVolume *Construct();

  void SetTargetR(G4double r);
  void SetTarThickness(G4double t);
  void Report();

  G4LogicalVolume *GetTargetLog() { return target_log; };
  G4Tubs *GetTarget() { return target_solid; };
  G4int GetTargetMass() { return target_a; };
  G4int GetTargetCharge() { return target_z; };

  G4VPhysicalVolume *GetTargetPlacement() { return target_phys; }; 
  G4double GetTargetDensity() { return target_log->GetMaterial()->GetDensity()/g*cm3; };
  G4double GetTargetThickness(){return 2.*target_solid->GetZHalfLength()/um;};

private:
  G4double target_radius;
  G4double target_thickness;

  G4Material *mat_pt196;

  G4int target_z, target_a;

  // position
  G4RotationMatrix *no_rot;
  G4ThreeVector *pos;

  // geometry
  G4Tubs *target_solid;
  G4LogicalVolume *target_log;
  G4VPhysicalVolume *target_phys;

  // limits
  G4UserLimits *target_limits;
  G4double n_tar_step;
};

//
}

#endif
