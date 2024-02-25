#include "HPGeDetector.hh"

namespace coulex
{
//
HPGeDetector::HPGeDetector(G4LogicalVolume *l)
{
  log = l;

  //
  hpge_crystal_outer_r = HPGeCrystalOuterRadius;
  hpge_crystal_inner_r = HPGeCrystalInnerRadius;
  hpge_crystal_length = HPGeCrystalLength;
  hpge_crystal_hole_depth = HPGeCrystalHoleDepth;
  hpge_crystal_edeg_offset_1 = HPGeCrystalEdgeOffset1;
  hpge_crystal_edeg_offset_2 = HPGeCrystalEdgeOffset2;
  capsule_width = CapsuleWidth;
  capsule_length = CapsuleLength;
  cr2capf = CrToCapF;
  bgo2cap = BGOtoCap;
  collimator_width = CollimatorWidth;
  
  //
  G4NistManager* nist_manager = G4NistManager::Instance();
  mat_air = nist_manager->FindOrBuildMaterial("G4_AIR");
  mat_vaccum = nist_manager->FindOrBuildMaterial("G4_Galactic");
  mat_al = nist_manager->FindOrBuildMaterial("G4_Al");
  mat_ge = nist_manager->FindOrBuildMaterial("G4_Ge");
  mat_cu = nist_manager->FindOrBuildMaterial("G4_Cu");
  mat_fe = nist_manager->FindOrBuildMaterial("G4_Fe");

  G4Element* el_bi  = nist_manager->FindOrBuildElement("Bi");
  G4Element* el_ge  = nist_manager->FindOrBuildElement("Ge");
  G4Element* el_o  = nist_manager->FindOrBuildElement("O");
  mat_bgo = new G4Material("BGO", 7.13*g/cm3, 3);
  mat_bgo->AddElement(el_bi, 4);
  mat_bgo->AddElement(el_ge, 3);
  mat_bgo->AddElement(el_o, 12);
}

//
HPGeDetector::~HPGeDetector()
{

}

//
void HPGeDetector::BuildHPGeCrystal()
{
  G4double hpge_crystal_z[4] = {0. *mm, hpge_crystal_hole_depth, hpge_crystal_hole_depth, hpge_crystal_length};
  G4double hpge_crystal_r_min[4] = {0. *mm, 0. *mm, hpge_crystal_inner_r, hpge_crystal_inner_r};
  G4double hpge_crystal_r_max[4] = {hpge_crystal_outer_r, hpge_crystal_outer_r, hpge_crystal_outer_r, hpge_crystal_outer_r};

  G4Polycone *hpge_crystal_solid = new G4Polycone("crystal_solid", 0., twopi, 4, hpge_crystal_z, hpge_crystal_r_min, hpge_crystal_r_max); 
  hpge_crystal_log = new G4LogicalVolume(hpge_crystal_solid, mat_ge, "hpge_crystal_log");

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0., 0., 1.0, 0.3));
  vis_att->SetForceSolid(true);
  hpge_crystal_log->SetVisAttributes(vis_att);
}

//
void HPGeDetector::BuildDetDewar()
{
  G4double det_dewar_z[10] = {0.*mm, 10.*mm, 10.5*mm, 410.*mm, 410.5*mm, 420.*mm, 420.*mm+0.5*mm, 420.*mm+15.*mm, 420.*mm+15.5*mm, 420.*mm+25.*mm};
  G4double det_dewar_r_min[10] = {0.*mm, 0.*mm, 107.*mm, 107.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm };
  G4double det_dewar_r_max[10] = {111.*mm, 111.*mm, 111.*mm, 111.*mm, 111.*mm, 111.*mm, 15.*mm, 15.*mm, 7.*mm, 7.*mm};

  G4Polycone *det_dewar_solid = new G4Polycone("det_dewar_solid", 0., twopi, 10, det_dewar_z, det_dewar_r_min, det_dewar_r_max);
  det_dewar_log = new G4LogicalVolume(det_dewar_solid, mat_cu, "det_dewar_log");

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8, 0.3));
  vis_att->SetForceSolid(true);
  det_dewar_log->SetVisAttributes(vis_att);
}

//
void HPGeDetector::BuildDetCapsule()
{
  G4double det_capsule_z[10] = {0.*mm, 0.3*mm, 0.3*mm, 165.*mm, 165.*mm, 245.*mm, 245.*mm, 255.*mm, 255.*mm, 455.*mm};
  G4double det_capsule_r_min[10] = {0.*mm, 0.*mm, 43.*mm, 43.*mm, 43.*mm, 43.*mm, 15.*mm, 15.*mm, 15.*mm, 0.*mm };
  G4double det_capsule_r_max[10] = {45.*mm, 45.*mm, 45.*mm, 45.*mm, 47.5*mm, 47.5*mm, 47.5*mm, 47.5*mm, 25.*mm, 25.*mm};

  G4Polycone *det_capsule_solid = new G4Polycone("det_capsule_solid", 0., twopi, 10, det_capsule_z, det_capsule_r_min, det_capsule_r_max);
  det_capsule_log = new G4LogicalVolume(det_capsule_solid, mat_al, "det_capsule_log");

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0.4, 0.4, 0.4, 0.3));
  vis_att->SetForceSolid(true);
  det_capsule_log->SetVisAttributes(vis_att);
}

//
void HPGeDetector::BuildBGOCrystal()
{
  G4double bgo_crystal_z[3] = {0.*mm, bgo2cap, 193.*mm};
  G4double bgo_crystal_r_min[3] = {32.*mm, 51.*mm, 51.*mm};
  G4double bgo_crystal_r_max[3] = {(32.+17.)*mm, (51.+17.)*mm, (51.+37.)*mm};

  G4Polycone *bgo_crystal_solid = new G4Polycone("bgo_crystal_solid", 0., twopi, 3, bgo_crystal_z, bgo_crystal_r_min, bgo_crystal_r_max); 
  bgo_crystal_log = new G4LogicalVolume(bgo_crystal_solid, mat_bgo, "bgo_crystal_log");

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0.73, 1.0, 1.0, 0.3));
  vis_att->SetForceSolid(true);
  bgo_crystal_log->SetVisAttributes(vis_att);
}

//
G4VPhysicalVolume *HPGeDetector::Construct(G4ThreeVector p)
{
  BuildHPGeCrystal();
  BuildDetDewar();
  BuildDetCapsule();
  BuildBGOCrystal();

  G4RotationMatrix rot;
  rot.rotateY(p.getTheta());
  rot.rotateZ(p.getPhi());

  G4Transform3D transform(rot, rot(G4ThreeVector(0.,0.,p.getR())));
  hpge_crystal_phys = new G4PVPlacement(transform, hpge_crystal_log, "hpge_crystal_log", log, true, id, true);

  return hpge_crystal_phys;
}

//
void HPGeDetector::Place(G4ThreeVector p)
{
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
} 

//

//
}
