#ifndef CloverDetector_h
#define CloverDetector_h 1

#include "Constants.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
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

//
class CloverDetector
{
public:
  CloverDetector(G4LogicalVolume *l);
  ~CloverDetector();

public:
  G4LogicalVolume *log;

public:
  G4VPhysicalVolume *Construct(G4double d, G4double t, G4double p);
  void Place(G4ThreeVector p);
  void Report();

  G4LogicalVolume *GetLog() { return clover_crystal_log; };

  void SetId(G4int i) { id = i; };
  void SetName();

private:
  void BuildCloverCrystal();
  void BuildCoolRod();
  void BuildCuPlate();
  void BuildCapsule();
  void BuildBGOCrystal();

private:
  G4int id;

private:
  G4Material *mat_air;
  G4Material *mat_vaccum;
  G4Material *mat_ge;
  G4Material *mat_al;
  G4Material *mat_fe;
  G4Material *mat_cu;
  G4Material *mat_bgo;
  G4Material *mat_pb;

  //
  G4double clover_crystal_outer_r;
  G4double clover_crystal_inner_r;
  G4double clover_crystal_length;
  G4double clover_crystal_hole_depth;
  G4double clover_distance_of_crs;
  G4double clover_cr_edge_cut1;
  G4double clover_cr_edge_cut2;
  G4double clover_cr_edge_depth;
  G4double clover_cr_edge_angle;
  G4double clover_cap_width;
  G4double clover_capsule_length;
  G4double clover_cr2cap_f;
  G4double clover_cr2cap_e;
  G4double clover_front_shield_l;
  G4double clover_front_shield_width;
  G4double clover_front_shield1;
  G4double clover_front_shield2;
  G4double clover_bgo_shield_width;
  G4double clover_bgo_shield_edge_depth;
  G4double clover_bgo_shield2cap;
  G4double clover_bgo_shield_offset;

  //
  G4LogicalVolume *clover_crystal_log;
  G4LogicalVolume *cool_rod_log;
  G4LogicalVolume *cu_plate_log;
  G4LogicalVolume *capsule_log;
  G4LogicalVolume *bgo_crystal_log;

  G4VPhysicalVolume *clover_crystal_phys;
  G4VPhysicalVolume *cool_rod_phys;
  G4VPhysicalVolume *cu_plate_phys;
  G4VPhysicalVolume *capsule_phys;
  G4VPhysicalVolume *bgo_crystal_phys;
//
};


#endif
