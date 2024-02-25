#ifndef HPGeDetector_h
#define HPGeDetector_h 1

#include "Constants.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"

using namespace CLHEP;

namespace coulex
{
//
class HPGeDetector
{
public:
  HPGeDetector(G4LogicalVolume *l);
  ~HPGeDetector();

public:
  G4LogicalVolume *log;

public:
  G4VPhysicalVolume *Construct(G4ThreeVector p);
  void Place(G4ThreeVector p);
  void Report();

  G4LogicalVolume *GetLog() { return hpge_log; };

  void SetId(G4int i) { id = i; };
  void SetRingId(G4int i) { ring_id = i};
  void SetName();

private:
  void BuildHPGeCrystal();
  void BuildDetCapsule();
  void BuildRearAbsorber();

private:
  G4Material *mat_air;
  G4Material *mat_vaccum;
  G4Material *mat_al;
  G4Material *mat_fe;
  G4Material *mat_cu;

  G4double crystal_outer_r; 
  G4double crystal_inner_r; 
  G4double crystal_length;
  G4double crystal_hole_depth;
  G4double crystal_edeg_offset_1;
  G4double crystal_edeg_offset_2;
  G4double capsule_width;
  G4double capsule_length;
  G4double collimator_width;

  //
  G4LogicalVolume *hpge_crystal_log;
  G4LogicalVolume *det_capsule_log;

  G4VPhysicalVolume *hpge_crystal_phys;
  G4VPhysicalVolume *det_capsule_phys;
//
};



//
}


#endif
