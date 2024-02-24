#include "Target.hh"

//
namespace coulex
{
//
Target::Target(G4LogicalVolume *wl)
{
  world_log = wl;

  target_radius = 1.5 *cm;
  target_thickness = 0.606 *um;

  mat_pt196 = new G4Material("Pt196", 78., 195.96*g/mole, 21.45*g/cm3);

  target_z = 78;
  target_a = 196;

  no_rot = new G4RotationMatrix();
  pos = new G4ThreeVector(0.,0.,0.);

  n_tar_step = 20.;
}

//
Target::~Target()
{
  delete target_limits;
}

//
G4VPhysicalVolume *Target::Construct()
{
  G4ThreeVector shift;

  target_solid = new G4Tubs("target_solid", 0., target_radius, target_thickness/2., 0., twopi);
  target_log = new G4LogicalVolume(target_solid, mat_pt196, "target_log");
  target_phys = new G4PVPlacement(G4Transform3D(*no_rot, *pos), target_log, "target_log", world_log, false, 0, true);
  shift.setX(0.);
  shift.setY(0.);
  shift.setZ(-0.5*target_thickness);
  target_phys->SetTranslation(shift);

  // limits
  target_limits= new G4UserLimits();
  target_limits->SetMaxAllowedStep(target_thickness/n_tar_step);
  target_log->SetUserLimits(target_limits);

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(1.0, 0., 0., 0.3));
  vis_att->SetForceSolid(true);
  target_log->SetVisAttributes(vis_att);

  return target_phys;
}

//
void Target::Report()
{
  G4cout << " " << G4endl;
  G4cout << "---->                 Target material set to " << target_log->GetMaterial()->GetName() << G4endl; 
  G4cout << "---->            Target mass number A set to " << target_a << G4endl; 
  G4cout << "---->          Target atomic number Z set to " << target_z << G4endl; 
  // G4cout << "----> Target recoil excitation energy set to " << target_ex/keV << " keV" << G4endl;    
  G4cout << "---->                Target radius is set to " << G4BestUnit(target_solid->GetOuterRadius(), "Length") << G4endl;
  G4cout << "---->             Target thickness is set to " << G4BestUnit(2.*target_solid->GetZHalfLength(), "Length") << G4endl;
  G4cout << "---->             Target density is set to " << target_log->GetMaterial()->GetDensity()/(g/cm3) << " g/cm3." <<G4endl;
  G4cout << "----> Number of simulation steps in the target is set to " << n_tar_step << G4endl;
}

//
}
