#include "CloverDetector.hh"

//
CloverDetector::CloverDetector(G4LogicalVolume *l)
{
  log = l;

  //
  clover_crystal_outer_r = CloverCrystalOuterRadius;
  clover_crystal_inner_r = CloverCrystalInnerRadius;
  clover_crystal_length = CloverCrystalLength;
  clover_crystal_hole_depth = CloverCrystalHoleDepth; 
  clover_distance_of_crs = CloverDistanceOfCrs;
  clover_cr_edge_cut1 = CloverCrEdgeCut1;
  clover_cr_edge_cut2 = CloverCrEdgeCut2;
  clover_cr_edge_depth = CloverCrEdgeDepth;
  clover_cr_edge_angle = CloverCrEdgeAngle;
  clover_cap_width = CloverCapWidth;
  clover_capsule_length = CloverCapsuleLength;
  clover_cr2cap_f = CloverCr2CapF;
  clover_cr2cap_e = CloverCr2CapE;
  clover_front_shield_l = CloverFrontShieldL;
  clover_front_shield_width = CloverFrontShieldWidth;
  clover_front_shield1 = CloverFrontShield1;
  clover_front_shield2 = CloverFrontShield2;
  clover_bgo_shield_width = CloverBGOShieldWidth;
  clover_bgo_shield_edge_depth = CloverBGOShieldEdgeDepth;
  clover_bgo_shield2cap = CloverBGOShield2Cap;
  clover_bgo_shield_offset = CloverBGOShieldOffset;

  //
  G4NistManager* nist_manager = G4NistManager::Instance();
  mat_air = nist_manager->FindOrBuildMaterial("G4_AIR");
  mat_vaccum = nist_manager->FindOrBuildMaterial("G4_Galactic");
  mat_al = nist_manager->FindOrBuildMaterial("G4_Al");
  mat_ge = nist_manager->FindOrBuildMaterial("G4_Ge");
  mat_cu = nist_manager->FindOrBuildMaterial("G4_Cu");
  mat_fe = nist_manager->FindOrBuildMaterial("G4_Fe");
  mat_pb = nist_manager->FindOrBuildMaterial("G4_Pb");

  G4Element* el_bi  = nist_manager->FindOrBuildElement("Bi");
  G4Element* el_ge  = nist_manager->FindOrBuildElement("Ge");
  G4Element* el_o  = nist_manager->FindOrBuildElement("O");
  mat_bgo = new G4Material("BGO", 7.13*g/cm3, 3);
  mat_bgo->AddElement(el_bi, 4);
  mat_bgo->AddElement(el_ge, 3);
  mat_bgo->AddElement(el_o, 12);
}

//
CloverDetector::~CloverDetector()
{

}

//
void CloverDetector::BuildCloverCrystal()
{
  G4double clover_crystal_z[4] = {0. *mm, clover_crystal_hole_depth, clover_crystal_hole_depth+3.*mm, clover_crystal_length};
  G4double clover_crystal_r_min[4] = {0. *mm, 0. *mm, clover_crystal_inner_r, clover_crystal_inner_r};
  G4double clover_crystal_r_max[4] = {clover_crystal_outer_r, clover_crystal_outer_r, clover_crystal_outer_r, clover_crystal_outer_r};

  G4Polycone *coax = new G4Polycone("coax", 0., twopi, 4, clover_crystal_z, clover_crystal_r_min, clover_crystal_r_max);

  // substract boxes
  G4RotationMatrix rot;
  G4double edge[3];
  edge[0] = clover_crystal_outer_r - clover_cr_edge_cut1;
  edge[1] = 1.001*clover_crystal_outer_r;
  edge[2] = 1.001*clover_crystal_length/2.;
  G4Box *cut_edge1 = new G4Box("cut_edge1", edge[0], edge[1], edge[2]);

  edge[0] = clover_crystal_outer_r - clover_cr_edge_cut2;
  edge[1] = 1.001*clover_crystal_outer_r;
  edge[2] = 1.001*clover_crystal_length/2.;
  G4Box *cut_edge2 = new G4Box("cut_edge2", edge[0], edge[1], edge[2]);

  edge[0] = 1.001*clover_crystal_outer_r;
  edge[1] = sin(clover_cr_edge_angle)*clover_cr_edge_depth;
  edge[2] = 1.001*clover_crystal_length/2.;
  G4Box *cut_edge3 = new G4Box("cut_edge3", edge[0], edge[1], edge[2]);

  G4ThreeVector pos1 = G4ThreeVector(-clover_crystal_outer_r, 0.*mm, clover_crystal_length/2.);
  G4SubtractionSolid *coax_cut1 = new G4SubtractionSolid("coax_cut1", coax, cut_edge1, &rot, pos1);
  G4ThreeVector pos2 = G4ThreeVector(clover_crystal_outer_r, 0.*mm, clover_crystal_length/2.);
  G4SubtractionSolid *coax_cut2 = new G4SubtractionSolid("coax_cut2", coax_cut1, cut_edge2, &rot, pos2);
  
  rot.rotateZ(90.*deg);
  G4ThreeVector pos3 = G4ThreeVector(0.*mm, clover_crystal_outer_r, clover_crystal_length/2.);
  G4SubtractionSolid *coax_cut3 = new G4SubtractionSolid("coax_cut3", coax_cut2, cut_edge2, &rot, pos3);
  G4ThreeVector pos4 = G4ThreeVector(0.*mm, -clover_crystal_outer_r, clover_crystal_length/2.);
  G4SubtractionSolid *coax_cut4 = new G4SubtractionSolid("coax_cut4", coax_cut3, cut_edge1, &rot, pos4);

  rot.rotateZ(-90.*deg);
  rot.rotateX(clover_cr_edge_angle);
  G4ThreeVector pos5 = G4ThreeVector(0.*mm, clover_cr_edge_cut2, 0.*mm);
  G4SubtractionSolid *coax_cut5 = new G4SubtractionSolid("coax_cut5", coax_cut4, cut_edge3, &rot, pos5);

  rot.rotateX(-clover_cr_edge_angle);
  rot.rotateZ(90.*deg);
  rot.rotateX(clover_cr_edge_angle);
  G4ThreeVector pos6 = G4ThreeVector(clover_cr_edge_cut2, 0.*mm, 0.*mm);
  G4SubtractionSolid *coax_cut6 = new G4SubtractionSolid("coax_cut6", coax_cut5, cut_edge3, &rot, pos6);

  rot.rotateX(-clover_cr_edge_angle);
  rot.rotateZ(-90.*deg);
  
  clover_crystal_log = new G4LogicalVolume(coax_cut6, mat_ge, "clover_crystal_log", 0, 0, 0);

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0.75, 1., 0.24, 0.3));
  vis_att->SetForceSolid(true);
  clover_crystal_log->SetVisAttributes(vis_att);
}

//
void CloverDetector::BuildCoolRod()
{
  G4double node = 1.001*clover_capsule_length - clover_crystal_length - clover_cr2cap_f;
  
  G4double cool_rod_z[10] = {0.*mm, node, node, node+145.*mm, node+145.*mm, node+150.*mm, node+150.*mm, node+145.*mm+396.*mm, node+145.*mm+396.*mm, node+145.*mm+400.*mm};
  G4double cool_rod_r_min[10] = {5.*mm, 5.*mm, 5.*mm, 10.*mm, 10.*mm, 10.*mm, 110.*mm, 110.*mm, 0.*mm, 0.*mm};
  G4double cool_rod_r_max[10] = {6.*mm, 6.*mm, 21.5*mm, 21.5*mm, 113.*mm, 113*mm, 113.*mm, 113.*mm, 113.*mm, 113.*mm};

  G4Polycone *cool_rod_solid = new G4Polycone("cool_rod_solid", 0., twopi, 10, cool_rod_z, cool_rod_r_min, cool_rod_r_max);
  cool_rod_log = new G4LogicalVolume(cool_rod_solid, mat_cu, "cool_rod_log", 0, 0, 0);
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(1., 0.9, 0.6, 0.3));
  vis_att->SetForceSolid(true);
  cool_rod_log->SetVisAttributes(vis_att);
}

//
void CloverDetector::BuildCuPlate()
{
  G4RotationMatrix rot;
  rot.rotateZ(90.*deg);

  G4double x = clover_distance_of_crs/2.;
  G4double y = clover_cr_edge_cut1+clover_cr_edge_cut2-clover_cr_edge_depth*tan(clover_cr_edge_angle);
  G4double z = (clover_crystal_length-clover_cr_edge_depth)/2.;
  G4Box *cu_plate_solid1 = new G4Box("cu_plate_solid1", x, y, z);
  G4UnionSolid *cu_plate_solid2 = new G4UnionSolid("cu_plate_solid2", cu_plate_solid1, cu_plate_solid1, &rot, G4ThreeVector());

  cu_plate_log = new G4LogicalVolume(cu_plate_solid2, mat_cu, "cu_plate_log", 0, 0, 0);

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(1., 0.84, 0., 0.3));
  vis_att->SetForceSolid(true);
  cu_plate_log->SetVisAttributes(vis_att);
}

//
void CloverDetector::BuildCapsule()
{
  G4double capsule_width1 = 4.*mm;
  G4double capsule_width2 = 0.6*mm;
  G4double capsule_edge_depth = clover_cr_edge_depth + clover_cr2cap_f;
  G4double capsule_edge_width = clover_distance_of_crs/2. + clover_cr_edge_cut1 + clover_cr_edge_cut2 + clover_cr2cap_e;

  G4Tubs *hole = new G4Tubs("hole", 0.*mm, clover_crystal_outer_r+1.*mm, capsule_width1, 0., twopi);
  
  G4double tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
  tmp0 = 0.*mm;
  tmp1 = capsule_width2;
  tmp2 = capsule_width2;
  tmp3 = capsule_edge_depth;
  tmp4 = clover_capsule_length-capsule_width1;
  tmp5 = clover_capsule_length-capsule_width1;
  tmp6 = clover_capsule_length;
  G4double capsule_z[7] = {tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6};

  tmp0 = 0.*mm;
  tmp1 = 0.*mm;
  tmp2 = capsule_edge_width-(capsule_edge_depth-clover_cap_width)*tan(clover_cr_edge_angle);
  tmp3 = capsule_edge_width;
  tmp4 = capsule_edge_width;
  tmp5 = 0.*mm;
  tmp6 = 0.*mm;
  G4double capsule_r_min[7] = {tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6};

  tmp0 = capsule_edge_width+clover_cap_width-capsule_edge_depth*tan(clover_cr_edge_angle);
  tmp1 = capsule_edge_width+clover_cap_width-(capsule_edge_depth-clover_cap_width)*tan(clover_cr_edge_angle);
  tmp2 = capsule_edge_width+clover_cap_width-(capsule_edge_depth-clover_cap_width)*tan(clover_cr_edge_angle);
  tmp3 = capsule_edge_width+clover_cap_width;
  tmp4 = capsule_edge_width+clover_cap_width;
  tmp5 = capsule_edge_width+clover_cap_width;
  tmp6 = capsule_edge_width+clover_cap_width;
  G4double capsule_r_max[7] = {tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6};

  G4Polycone *capsule_solid1 = new G4Polycone("capsule_solid1", 0., twopi, 7, capsule_z, capsule_r_min, capsule_r_max);
  G4SubtractionSolid *capsule_solid2 = new G4SubtractionSolid("capsule_solid2", capsule_solid1, hole, 0, G4ThreeVector(0.,0.,clover_capsule_length-clover_cap_width/2.));
  capsule_log = new G4LogicalVolume(capsule_solid2, mat_fe, "capsule_log", 0, 0, 0 );

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(1., 0.42, 0.42, 0.3));
  vis_att->SetForceSolid(true);
  capsule_log->SetVisAttributes(vis_att);
}

//
void CloverDetector::BuildBGOCrystal()
{
  G4double tmp0, tmp1, tmp2, tmp3;
  tmp0 = 0.*mm;
  tmp1 = clover_bgo_shield_edge_depth;
  tmp2 = clover_bgo_shield_edge_depth;
  tmp3 = clover_capsule_length-clover_cr2cap_f-clover_cr_edge_depth-clover_bgo_shield_offset;
  G4double bgo_crystal_z[4] = {tmp0, tmp1, tmp2, tmp3};
  
  G4double width = clover_distance_of_crs/2.+clover_cr_edge_cut1+clover_cr_edge_cut2+clover_cr2cap_e+clover_cap_width+clover_bgo_shield2cap;
  G4double bgo_crystal_r_min[4] = {width, width, width, width};

  tmp0 = width+clover_bgo_shield_width-clover_bgo_shield_edge_depth*tan(clover_cr_edge_angle); 
  tmp1 = width+clover_bgo_shield_width;
  tmp2 = tmp1;
  tmp3 = tmp2;
  G4double bgo_crystal_r_max[4] = {tmp0, tmp1, tmp2, tmp3};

  G4Polycone *bgo_crystal_solid = new G4Polycone("bgo_solid", 0., twopi, 4, bgo_crystal_z, bgo_crystal_r_min, bgo_crystal_r_max);
  bgo_crystal_log = new G4LogicalVolume(bgo_crystal_solid, mat_bgo, "bgo_crystal_log", 0, 0, 0 );

  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(0.96, 0.96, 0.86, 0.3));
  vis_att->SetForceSolid(true);
  bgo_crystal_log->SetVisAttributes(vis_att);
}

//
G4VPhysicalVolume *CloverDetector::Construct(G4double d, G4double t, G4double p)
{
  BuildCloverCrystal();
  BuildCuPlate();
  BuildCapsule();
  BuildCoolRod();
  BuildBGOCrystal();

  // clover crystal
  G4double x = clover_cr_edge_cut1 + clover_distance_of_crs/2.; 
  G4double y = clover_cr_edge_cut1 + clover_distance_of_crs/2.; 
  G4double z = d + clover_cr2cap_f;
  G4cout << "----> x " << x << " y " << y << " z " << z << G4endl;

  G4RotationMatrix rot_a;
  rot_a.rotateZ(-90.*deg);
  rot_a.rotateY(t);
  rot_a.rotateZ(p);
  rot_a.print(G4cout);
  G4Transform3D transform_clover_crystal_a(rot_a, rot_a*G4ThreeVector(x,y,z));
  clover_crystal_phys = new G4PVPlacement(transform_clover_crystal_a, clover_crystal_log, "clover_crystal_phys_a", log, false, 4*id, true);

  G4RotationMatrix rot_b;
  rot_b.rotateZ(-180.*deg);
  rot_b.rotateY(t);
  rot_b.rotateZ(p);
  rot_b.print(G4cout);
  G4Transform3D transform_clover_crystal_b(rot_b, rot_b*G4ThreeVector(x,y,z));
  clover_crystal_phys = new G4PVPlacement(transform_clover_crystal_b, clover_crystal_log, "clover_crystal_phys_b", log, false, 4*id+1, true);

  G4RotationMatrix rot_c;
  rot_c.rotateZ(-270.*deg);
  rot_c.rotateY(t);
  rot_c.rotateZ(p);
  rot_c.print(G4cout);
  G4Transform3D transform_clover_crystal_c(rot_c, rot_c*G4ThreeVector(x,y,z));
  clover_crystal_phys = new G4PVPlacement(transform_clover_crystal_c, clover_crystal_log, "clover_crystal_phys_c", log, false, 4*id+2, true);

  G4RotationMatrix rot_d;
  rot_d.rotateZ(-360.*deg);
  rot_d.rotateY(t);
  rot_d.rotateZ(p);
  rot_d.print(G4cout);
  G4Transform3D transform_clover_crystal_d(rot_d, rot_d*G4ThreeVector(x,y,z));
  clover_crystal_phys = new G4PVPlacement(transform_clover_crystal_d, clover_crystal_log, "clover_crystal_phys_d", log, false, 4*id+3, true);

  // cu plate
  z = d + clover_cr2cap_f +clover_cr_edge_depth + (clover_crystal_length-clover_cr_edge_depth)/2.;
  G4cout << "----> x " << x << " y " << y << " z " << z << G4endl;

  G4RotationMatrix rot_cu_plate;
  rot_cu_plate.rotateZ(-360.*deg);
  rot_cu_plate.rotateY(t);
  rot_cu_plate.rotateZ(p);
  rot_cu_plate.print(G4cout);
  G4Transform3D transform_cu_plate(rot_cu_plate, rot_cu_plate*G4ThreeVector(0.,0.,z));
  clover_crystal_phys = new G4PVPlacement(transform_cu_plate, cu_plate_log, "cu_plate_phys", log, false, id, true);

  // capsule 
  z = d;
  G4RotationMatrix rot_capsule;
  rot_capsule.rotateZ(45.*deg);
  rot_capsule.rotateY(t);
  rot_capsule.rotateZ(p);
  rot_capsule.print(G4cout);
  G4Transform3D transform_capsule(rot_capsule, rot_capsule*G4ThreeVector(0.,0.,z));
  clover_crystal_phys = new G4PVPlacement(transform_capsule, capsule_log, "capsule_phys", log, false, id, true);

  // cool rod
  z = d + clover_cr2cap_f + clover_crystal_length;
  G4RotationMatrix rot_cool_rod;
  rot_cool_rod.rotateZ(45.*deg);
  rot_cool_rod.rotateY(t);
  rot_cool_rod.rotateZ(p);
  rot_cool_rod.print(G4cout);
  G4Transform3D transform_cool_rod(rot_cool_rod, rot_cool_rod*G4ThreeVector(0.,0.,z));
  clover_crystal_phys = new G4PVPlacement(transform_cool_rod, cool_rod_log, "cool_rod_phys", log, false, id, true);

  // bgo crystal
  z = d;
  G4RotationMatrix rot_bgo_crystal;
  rot_bgo_crystal.rotateZ(45.*deg);
  rot_bgo_crystal.rotateY(t);
  rot_bgo_crystal.rotateZ(p);
  rot_bgo_crystal.print(G4cout);
  G4Transform3D transform_bgo_crystal(rot_bgo_crystal, rot_bgo_crystal*G4ThreeVector(0.,0.,z));
  clover_crystal_phys = new G4PVPlacement(transform_bgo_crystal, bgo_crystal_log, "bgo_crystal_phys", log, false, id, true);

  //
  // clover_crystal_phys = new G4PVPlacement(G4Transform3D(G4RotationMatrix(),G4ThreeVector(0.,0.,0.)), bgo_crystal_log, "bgo_crystal_phys", log, false, id, true);

  return clover_crystal_phys;
}



