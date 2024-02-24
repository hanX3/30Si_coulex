#ifndef S3SiPixel_h
#define S3SiPixel_h 1

#include "Constants.hh"
#include "SiSD.hh"

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4RunManager.hh"

namespace coulex
{
//

class S3SiPixel
{
public:
  S3SiPixel(G4LogicalVolume *l);
  ~S3SiPixel();

public:
  G4LogicalVolume *log;

public:  
  G4VPhysicalVolume *Construct();
  void SetRingId(G4int i) {ring_id = i;};
  void SetSectorId(G4int i) {sector_id = i;};
  void SetName();
  void Report();
  void Place(G4ThreeVector p);

  G4LogicalVolume *GetLog() { return s3_si_pixel_log; };

private:
  // dimensions
  G4double inner_radius;
  G4double outer_radius;
  G4double angle_start;
  G4double thickness;

  // materials
  G4Material *mat_si;

  // default position
  G4ThreeVector *pos;

  // detector
  G4Tubs *a_s3_si_pixel;
  G4LogicalVolume *s3_si_pixel_log;
  G4VPhysicalVolume *s3_si_pixel_phys;

  G4int ring_id; // 0-24
  G4int sector_id; // 0-32
};

//
}

#endif
