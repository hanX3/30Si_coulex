#include "S3SiArray.hh"

//
S3SiArray::S3SiArray(G4LogicalVolume *wl)
{
  world_log = wl;

  rings = RingNumber;
  sectors = SectorNumber;
}

//
S3SiArray::~S3SiArray()
{

}

//
void S3SiArray::Construct()
{
  v_s3_si_array.clear();

  for(int i=0;i<rings;i++){
    for(int j=0;j<sectors;j++){
      v_s3_si_array.push_back(new S3SiPixel(world_log));
    }
  }

  std::vector<S3SiPixel*>::iterator it = v_s3_si_array.begin();
  for(int i=0;i<rings;i++){
    for(int j=0;j<sectors;j++){
      (*it)->SetRingId(i);
      (*it)->SetSectorId(j);
      (*it)->Construct();
      (*it)->Place(G4ThreeVector(0., 0., 8.6 *mm));
      (*it)->SetName();
      it++;
    }
  }
}

//
void S3SiArray::Report()
{
  G4cout << "S3 Si array constructed." << G4endl;
  //
  for(int i=0;i<rings;i++){
    for(int j=0;j<sectors;j++){
      // G4cout << G4endl;
    }
  }
}

//
void S3SiArray::MakeSensitive(SiSD *ss)
{
  std::vector<S3SiPixel*>::iterator it = v_s3_si_array.begin();
  for( ;it!=v_s3_si_array.end();it++){
    (*it)->GetLog()->SetSensitiveDetector(ss);
  }
}

