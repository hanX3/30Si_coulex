#ifndef IMPHPGeArray_h
#define IMPHPGeArray_h 1

#include "HPGeSD.hh"
#include "HPGeDetector.hh"

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include <iostream>
#include <vector>

namespace coulex
{
//

class IMPHPGeArray   
{
public:
  IMPHPGeArray(G4LogicalVolume *wl);
  ~IMPHPGeArray();

public:
  G4LogicalVolume *log;

public:
  void Construct();
  void Report();
  void MakeSensitive(HPGeSD *sd);

private:
  G4LogicalVolume *world_log;
  std::vector<HPGeDetector*> v_hpge;

  G4double distance_hpge;
  G4double distance_clover;
  G4double theta_hpge[4];
  G4double phi_hpge[4][4];

};











}


#endif
