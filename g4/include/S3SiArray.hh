#ifndef S3SiArray_h
#define S3SiArray_h 1

#include "S3SiPixel.hh"

#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "SiSD.hh"
#include <iostream>
#include <vector>

//

class S3SiArray
{
public:
  S3SiArray(G4LogicalVolume *wl);
  ~S3SiArray();

public:
  void Construct();
  void Report();
  void MakeSensitive(SiSD *ss);

public:
  G4LogicalVolume *world_log;  

private:
  std::vector<S3SiPixel*> v_s3_si_array;

  //
  G4int rings;
  G4int sectors; 
};  


#endif
