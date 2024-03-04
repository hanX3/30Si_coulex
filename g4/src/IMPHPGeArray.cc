#include "IMPHPGeArray.hh"

//
IMPHPGeArray::IMPHPGeArray(G4LogicalVolume *wl)
{
  world_log = wl;

  //
  distance_hpge = 20. *cm;

  theta_hpge[0] = 26.15 *deg;
  theta_hpge[1] = 51.7 *deg;
  theta_hpge[2] = 128.3 *deg;
  theta_hpge[3] = 153.85 *deg;

  phi_hpge[0][0] = 22.5 *deg;
  phi_hpge[0][1] = 112.5 *deg;
  phi_hpge[0][2] = 202.5 *deg;
  phi_hpge[0][3] = 292.5 *deg;
  phi_hpge[1][0] = 67.5 *deg;
  phi_hpge[1][1] = 157.5 *deg;
  phi_hpge[1][2] = 247.5 *deg;
  phi_hpge[1][3] = 337.5 *deg;
  phi_hpge[2][0] = 22.5 *deg;
  phi_hpge[2][1] = 112.5 *deg;
  phi_hpge[2][2] = 202.5 *deg;
  phi_hpge[2][3] = 292.5 *deg;
  phi_hpge[3][0] = 67.5 *deg;
  phi_hpge[3][1] = 157.5 *deg;
  phi_hpge[3][2] = 247.5 *deg;
  phi_hpge[3][3] = 337.5 *deg;

  //
  distance_clover = 24. *cm;
  
  theta_clover = 90.*deg;
  phi_clover[0] = 22.5 *deg;
  phi_clover[1] = 67.5 *deg;
  phi_clover[2] = 112.5 *deg;
  phi_clover[3] = 157.5 *deg;
  phi_clover[4] = 202.5 *deg;
  phi_clover[5] = 247.5 *deg;
  phi_clover[6] = 292.5 *deg;
  phi_clover[7] = 337.5 *deg;
}

//
IMPHPGeArray::~IMPHPGeArray()
{

}

//
void IMPHPGeArray::Construct()
{
  //
  v_hpge.clear();

  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      v_hpge.push_back(new HPGeDetector(world_log));
    }
  }
  std::vector<HPGeDetector*>::iterator it_hpge = v_hpge.begin();

  G4ThreeVector pos_hpge;
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      pos_hpge.setRThetaPhi(distance_hpge, theta_hpge[i], phi_hpge[i][j]);
      (*it_hpge)->SetId(4*i+j);
      (*it_hpge)->Construct(pos_hpge);
      it_hpge++;
    }
  }

  //
  v_clover.clear();
  
  for(int i=0;i<8;i++){
    for(int j=0;j<4;j++){
      v_clover.push_back(new CloverDetector(world_log));
    }
  }
  std::vector<CloverDetector*>::iterator it_clover = v_clover.begin();
  
  for(int i=0;i<8;i++){
    (*it_clover)->SetId(i);
    (*it_clover)->Construct(distance_clover, theta_clover, phi_clover[i]);
    it_clover++;
  }

}

//
void IMPHPGeArray::Report()
{

}

//
void IMPHPGeArray::MakeSensitive(HPGeSD *sd)
{

}

