#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "Constants.hh"
#include "S3SiArray.hh"
#include "Chamber.hh"
#include "Target.hh"
#include "SiSD.hh"

#include "globals.hh"
#include "tls.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

//
namespace coulex
{
//
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

public:
  G4VPhysicalVolume* Construct() override;
  S3SiArray *GetS3SiArray() { return s3_si_array; };

  //
  void SetMaxStep(G4double );
  void SetCheckOverlaps(G4bool );

private:
  G4LogicalVolume *world_log;
  G4VPhysicalVolume *world_phys;

  Chamber *chamber;
  Target *target;
  S3SiArray *s3_si_array;

  G4Material* mat_air;
  G4UserLimits* step_limit;
  G4bool check_overlaps;

  // methods
  void DefineMaterials();

  G4VPhysicalVolume* DefineVolumes();

};

}

#endif
