#ifndef IMPHPGeArray_h
#define IMPHPGeArray_h 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "HPGeSD.hh"

namespace coulex
{
//

class IMPHPGeArray   
{
public:
  IMPHPGeArray();
  ~IMPHPGeArray();

public:
  void Placement(G4LogicalVolume *wd, G4double ot);

private:
  int n_rings;
  int n_sectors;

  G4double inner_radius;
  G4double outer_radius;
  G4double thickness;


};











}


#endif
