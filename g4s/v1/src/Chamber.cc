#include "Chamber.hh"

//
Chamber::Chamber(G4LogicalVolume *l)
{
  log = l;
  
  chamber_r_min = ChamberRMin;
  chamber_r_max = ChamberRMax;
  pipe_r = PipeR;

  G4NistManager* nist_manager = G4NistManager::Instance();
  mat_al = nist_manager->FindOrBuildMaterial("G4_Al");

  no_rot = new G4RotationMatrix();
  pos = new G4ThreeVector(0.*mm, 0.*mm, 0.*mm);
}

//
Chamber::~Chamber()
{

}

//
G4VPhysicalVolume *Chamber::Construct()
{
  shell = new G4Sphere("shell", chamber_r_min, chamber_r_max, 0., twopi, 0., pi);
  pipe = new G4Tubs("pipe", 0., pipe_r, 2.*(chamber_r_max+1.*mm), 0., twopi);
  
  chamber_solid = new G4SubtractionSolid("chamber_solid", shell, pipe, G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.*mm,0.*mm,0.*mm)));
  chamber_log = new G4LogicalVolume(chamber_solid, mat_al, "chamber_log", 0, 0, 0);
  chamber_phys = new G4PVPlacement(G4Transform3D(*no_rot,*pos), chamber_log, "chamber_log", log, false, 0, true);

  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0., 1., 0., 0.3));
  vis_att->SetForceSolid(true);
  chamber_log->SetVisAttributes(vis_att);

  return chamber_phys;
} 

//
void Chamber::Report()
{
   G4cout << "----> Chamber shell material set to     " << mat_al->GetName() << G4endl;     
   G4cout << "----> Chamber shell inner radius set to " << G4BestUnit(chamber_r_min, "Length") << G4endl;
   G4cout << "----> Chamber shell outer radius set to " << G4BestUnit(chamber_r_max, "Length") << G4endl;
   G4cout << "----> Chamber position set to " << "(" << pos->getX()/mm << ", " << pos->getY()/mm << ", " << pos->getZ()/mm << ") mm" << G4endl;
}

//
void Chamber::SetPosZ(G4double z)
{
  pos->setZ(z);
  chamber_phys->SetTranslation(*pos);  
  G4cout << "----> Chamber Z position set to " << G4BestUnit(chamber_phys->GetTranslation().getZ(),"Length") << G4endl;
}

