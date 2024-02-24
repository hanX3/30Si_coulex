#include "S3SiPixel.hh"

//
namespace coulex
{
//
S3SiPixel::S3SiPixel(G4LogicalVolume *l)
{
  log = l;

  G4NistManager* nist_manager = G4NistManager::Instance();
  mat_si = nist_manager->FindOrBuildMaterial("G4_Si");

  thickness = S3SiThickness;

  ring_id = 0;
  sector_id = 0;
}

//
S3SiPixel::~S3SiPixel()
{

}

//
G4VPhysicalVolume *S3SiPixel::Construct()
{
  inner_radius = (11. + 1.*ring_id) *mm;
  outer_radius = inner_radius + 1.*mm;
  angle_start = 11.25*sector_id *deg;

  //
  a_s3_si_pixel = new G4Tubs("a_s3_si_pixel_solid", inner_radius, outer_radius, thickness/2., angle_start, 11.25*deg);
  s3_si_pixel_log = new G4LogicalVolume(a_s3_si_pixel, mat_si, "s3_si_pixel_log");
  s3_si_pixel_phys = new G4PVPlacement(nullptr, G4ThreeVector(), s3_si_pixel_log, "s3_si_pixel_log", log, true, 32*ring_id+sector_id, true);

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.3));
  vis_att->SetForceSolid(true);
  s3_si_pixel_log->SetVisAttributes(vis_att);

  return s3_si_pixel_phys;
}

//
void S3SiPixel::Report()
{
  G4cout << "----> build a S3 Si pixel." << G4endl;
  G4cout << "----> S3 Si detector material set to " << s3_si_pixel_log->GetMaterial()->GetName() << G4endl;
}

//
void S3SiPixel::Place(G4ThreeVector p)
{
  s3_si_pixel_phys->SetTranslation(p);

  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

//
void S3SiPixel::SetName()
{
  char name[128];
  sprintf(name, "s3_si_ring%02d_sector%02d", ring_id, sector_id);
  s3_si_pixel_phys->SetName(name);
}

//
}
