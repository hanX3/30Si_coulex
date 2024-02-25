#include "HPGeDetector.hh"

namespace coulex
{
//
HPGeDetector::HPGeDetector(G4LogicalVolume *l)
{
  log = l;

  //
  crystal_outer_r = CrystalOuterRadius;
  crystal_inner_r = CrystalInnerRadius;
  crystal_length = CrystalLength;
  crystal_hole_depth = CrystalHoleDepth;
  crystal_edeg_offset_1 = CrystalEdgeOffset1;
  crystal_edeg_offset_2 = CrystalEdgeOffset2;
  capsule_width = CapsuleWidth;
  capsule_length = CapsuleLength;
  cr2capf = CrToCapF;
  bgo2cap = BGOtoCap;
  collimator_width = CollimatorWidth;
  
  //
  G4NistManager* nist_manager = G4NistManager::Instance();
  mat_air = nist_manager->FindOrBuildMaterial("G4_AIR");
  mat_vaccum = nist->FindOrBuildMaterial("G4_Galactic");
  mat_cu = nist->FindOrBuildMaterial("G4_Cu");
  mat_al = nist->FindOrBuildMaterial("G4_Al");
  mat_ge =  nist->FindOrBuildMaterial("G4_Ge");



}

//
HPGeDetector::~HPGeDetector()
{

}

//
void HPGeDetector::BuildHPGeCrystal()
{
  G4double crystal_z[4] = {0. *mm, crystal_hole_depth, crystal_hole_depth, crystal_length};
  G4double crystal_inner_r[4] = {0. *mm, 0. *mm, crystal_inner_r, crystal_inner_r};
  G4double crystal_outer_r[4] = {crystal_outer_r, crystal_outer_r, crystal_outer_r, crystal_outer_r};

  G4Polycone *crystal_solid = new G4Polycone("crystal_solid", 0., twopi, 4, crystal_z, crystal_inner_r, crystal_outer_r); 
}


//
}
