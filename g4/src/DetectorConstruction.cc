#include "DetectorConstruction.hh"

//
namespace coulex
{
//
DetectorConstruction::DetectorConstruction()
{
  world_log = nullptr;
  world_phys = nullptr;

  mat_air = nullptr;
  step_limit = nullptr;
  check_overlaps = true;
}

//
DetectorConstruction::~DetectorConstruction()
{
  delete step_limit;
}

//
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();
  return DefineVolumes();
}

//
void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nist_manager = G4NistManager::Instance();

  mat_air = nist_manager->FindOrBuildMaterial("G4_AIR");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // world
  G4Box *world_solid = new G4Box("World", 0.5*WorldSizeX, 0.5*WorldSizeY, 0.5*WorldSizeZ);
  world_log = new G4LogicalVolume(world_solid, mat_air, "World");
  world_phys = new G4PVPlacement(nullptr, G4ThreeVector(), world_log, "World", 0, false, 0, check_overlaps);

  // chamber
  chamber = new Chamber(world_log);
  chamber->Construct();
  chamber->Report();

  // target
  target = new Target(world_log);
  target->Construct();
  target->Report();

  // imp hpge array
  G4Box *imp_array_solid = new G4Box("imp_array_solid", 0.2*WorldSizeX, 0.2*WorldSizeY, 0.2*WorldSizeZ);
  G4LogicalVolume *imp_array_log = new G4LogicalVolume(imp_array_solid, mat_air, "imp_array_log", nullptr, nullptr, nullptr);
  new G4PVPlacement(nullptr, G4ThreeVector(), imp_array_log, "imp_array_log", world_log, false, 0, false);

  imp_hpge_array = new IMPHPGeArray(imp_array_log);
  imp_hpge_array->Construct();
  imp_hpge_array->Report(); 

  // s3 si array
  G4Tubs *si_solid = new G4Tubs("si_solid", 0., 2.*(S3SiOuterRadius+1.*mm), (S3Si2Target+1.*mm), 0., twopi);
  G4LogicalVolume *si_log = new G4LogicalVolume(si_solid, mat_air, "si_log", nullptr, nullptr, nullptr);
  new G4PVPlacement(nullptr, G4ThreeVector(), si_log, "si_log", world_log, false, 0, check_overlaps);

  s3_si_array = new S3SiArray(si_log);
  s3_si_array->Construct();
  s3_si_array->Report();

  // Example of User Limits
  // Below is an example of how to set tracking constraints in a given logical volume
  // Sets a max step length in the tracker region, with G4StepLimiter
  G4double max_step = 1. * um;
  step_limit = new G4UserLimits(max_step);
  // logic_target->SetUserLimits(step_limit);

  /// Set additional contraints on the track, with G4UserSpecialCuts
  /// G4double max_length = 2*TargetThickness, max_time = 0.1*ns, min_ekin = 10*MeV;
  /// trackerLV->SetUserLimits(new G4UserLimits(max_step, max_length, max_time, min_ekin));

  // Sensitive detectors
  G4SDManager* sd_manager = G4SDManager::GetSDMpointer();
  SiSD *si_sd = new SiSD("SiSD", "SiHitCollection");
  sd_manager->AddNewDetector(si_sd);

  // Always return the physical world
  return world_phys;
}

//
void DetectorConstruction::SetMaxStep(G4double max_step)
{
  if ((step_limit)&&(max_step>0.)) step_limit->SetMaxAllowedStep(max_step);
}

//
void DetectorConstruction::SetCheckOverlaps(G4bool co)
{
  check_overlaps = co;
}

//

}
