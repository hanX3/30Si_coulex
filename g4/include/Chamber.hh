#ifndef Chamber_h
#define Chamber_h 1

#include "Constants.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Sphere.hh"
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
#include "G4SubtractionSolid.hh"

using namespace CLHEP;

namespace coulex
{
//
class Chamber
{
public:
  Chamber(G4LogicalVolume *l);
  ~Chamber();

public:
  G4LogicalVolume *log;

  G4VPhysicalVolume *Construct();
  G4VPhysicalVolume *GetChamberPhys() { return chamber_phys; };
  void SetPosZ(G4double z);
  void Report();

private:
  G4Material *mat_al;

  G4double chamber_r_min;
  G4double chamber_r_max;
  G4double pipe_r;

  G4RotationMatrix *no_rot;
  G4ThreeVector *pos;  

  G4Sphere *shell;
  G4Tubs *pipe;

  G4SubtractionSolid *chamber_solid;
  G4LogicalVolume *chamber_log;
  G4VPhysicalVolume *chamber_phys;
};

//
}

#endif
