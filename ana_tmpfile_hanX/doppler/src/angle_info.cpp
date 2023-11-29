#include "angle_info.h"
#include <iostream>

#include <stdlib.h>
#include <cmath>

#include "set.h"

angle_info::angle_info(double phi, double x, double y, double z)
{
  d_target_si = 8.6; 
  r_min = 11.5;
  r_max = 35.5;

  x_bp = x;
  y_bp = y;
  z_bp = z;
  
  phi_rotation = phi;

  InitGeThtea();
  InitGePhi();
  InitBeta();
  InitSiThtea();
  InitSiPhi();

  //PrintAngleInfo();
}

//
angle_info::~angle_info()
{
  
}

//
double angle_info::GetCosThetaParticleGamma(int mod_ge, int ch_ge, int si_ring_id, int si_sector_id)
{
  double rp = sqrt(d_target_si*d_target_si + (r_min+(double)si_ring_id)*(r_min+(double)si_ring_id));
  double xp = rp*sin(si_theta[si_ring_id]*PI/180.)*cos(si_phi[si_sector_id]*PI/180.);
  double yp = rp*sin(si_theta[si_ring_id]*PI/180.)*sin(si_phi[si_sector_id]*PI/180.);
  double zp = rp*cos(si_theta[si_ring_id]*PI/180.);

  double xg = sin(ge_theta[mod_ge][ch_ge]*PI/180.)*cos(ge_phi[mod_ge][ch_ge]*PI/180.);
  double yg = sin(ge_theta[mod_ge][ch_ge]*PI/180.)*sin(ge_phi[mod_ge][ch_ge]*PI/180.);
  double zg = cos(ge_theta[mod_ge][ch_ge]*PI/180.);

  double xx = (xp-x_bp)*xg;
  double yy = (yp-y_bp)*yg;
  double zz = (zp-z_bp)*zg;
  double rr = sqrt((xp-x_bp)*(xp-x_bp)+(yp-y_bp)*(yp-y_bp)+(zp-z_bp)*(zp-z_bp));

  //std::cout << "x_bp " << x_bp << " y_bp " << y_bp << " z_bp " << z_bp << std::endl;
  //std::cout << "rp " << rp << " rr " << rr << " xx+yy+zz " << xx+yy+zz << std::endl;

  return (xx+yy+zz)/rr;
}

//
void angle_info::InitGeThtea()
{
  for(int i=0;i<5;i++){
    for(int j=0;j<16;j++){
      ge_theta[i][j] = 0.;  
    }
  }

  //mod0
  ge_theta[0][0] = 153.85;
  ge_theta[0][1] = 153.85;
  ge_theta[0][2] = 153.85;
  ge_theta[0][3] = 153.85;
  ge_theta[0][4] = 128.30;
  ge_theta[0][5] = 128.30;
  ge_theta[0][6] = 128.30;
  ge_theta[0][7] = 128.30;
  
  //mod1
  ge_theta[1][0] = 51.70;
  ge_theta[1][1] = 51.70;
  ge_theta[1][2] = 51.70;
  ge_theta[1][3] = 51.70;
  ge_theta[1][4] = 26.15;
  ge_theta[1][5] = 26.15;
  ge_theta[1][6] = 26.15;
  ge_theta[1][7] = 26.15;

  //mod2 3-1,3-2,3-3
  ge_theta[2][0] = 90.0;
  ge_theta[2][1] = 90.0;
  ge_theta[2][2] = 90.0;
  ge_theta[2][3] = 90.0;
  ge_theta[2][4] = 90.0;
  ge_theta[2][5] = 90.0;
  ge_theta[2][6] = 90.0;
  ge_theta[2][7] = 90.0;
  ge_theta[2][8] = 90.0;
  ge_theta[2][9] = 90.0;
  ge_theta[2][10] = 90.0;
  ge_theta[2][11] = 90.0;
  
  //mod3 3-4,3-5,3-6
  ge_theta[3][0] = 90.0;
  ge_theta[3][1] = 90.0;
  ge_theta[3][2] = 90.0;
  ge_theta[3][3] = 90.0;
  ge_theta[3][8] = 90.0;
  ge_theta[3][9] = 90.0;
  ge_theta[3][10] = 90.0;
  ge_theta[3][11] = 90.0;
  
  //mod4 3-7,3-8
  ge_theta[4][0] = 90.0;
  ge_theta[4][1] = 90.0;
  ge_theta[4][2] = 90.0;
  ge_theta[4][3] = 90.0;
  ge_theta[4][4] = 90.0;
  ge_theta[4][5] = 90.0;
  ge_theta[4][6] = 90.0;
  ge_theta[4][7] = 90.0;
  ge_theta[4][8] = 90.0;
  ge_theta[4][9] = 90.0;
  ge_theta[4][10] = 90.0;
  ge_theta[4][11] = 90.0;

}

//
void angle_info::InitGePhi()
{
  for(int i=0;i<5;i++){
    for(int j=0;j<16;j++){
      ge_phi[i][j] = 0.;
    }
  }
  
  //mod0
  ge_phi[0][0] = 22.50;
  ge_phi[0][1] = 112.50;
  ge_phi[0][2] = 202.50;
  ge_phi[0][3] = 292.50;
  ge_phi[0][4] = 67.50;
  ge_phi[0][5] = 157.50;
  ge_phi[0][6] = 247.50;
  ge_phi[0][7] = 337.50;
  
  //mod1
  ge_phi[1][0] = 22.50;
  ge_phi[1][1] = 112.50;
  ge_phi[1][2] = 202.50;
  ge_phi[1][3] = 292.50;
  ge_phi[1][4] = 67.50;
  ge_phi[1][5] = 157.50;
  ge_phi[1][6] = 247.50;
  ge_phi[1][7] = 337.50;

  //mod2 clover 3-1,3-2,3-3
  ge_phi[2][0] = 22.50;
  ge_phi[2][1] = 22.50;
  ge_phi[2][2] = 22.50;
  ge_phi[2][3] = 22.50;
  ge_phi[2][4] = 67.50;
  ge_phi[2][5] = 67.50;
  ge_phi[2][6] = 67.50;
  ge_phi[2][7] = 67.50;
  ge_phi[2][8] = 112.50;
  ge_phi[2][9] = 112.50;
  ge_phi[2][10] = 112.50;
  ge_phi[2][11] = 112.50;
  
  //mod3 clover 3-5,3-6
  ge_phi[3][0] = 202.50;
  ge_phi[3][1] = 202.50;
  ge_phi[3][2] = 202.50;
  ge_phi[3][3] = 202.50;
  ge_phi[3][8] = 247.50;
  ge_phi[3][9] = 247.50;
  ge_phi[3][10] = 247.50;
  ge_phi[3][11] = 247.50;
  
  //mod4 clover 3-7,3-8
  ge_phi[4][0] = 292.50;
  ge_phi[4][1] = 292.50;
  ge_phi[4][2] = 292.50;
  ge_phi[4][3] = 292.50;
  ge_phi[4][8] = 337.50;
  ge_phi[4][9] = 337.50;
  ge_phi[4][10] = 337.50;
  ge_phi[4][11] = 337.50;
}

//
void angle_info::InitBeta()
{
  beta[0] = 0.0850104;
  beta[1] = 0.0842222;
  beta[2] = 0.0835307;
  beta[3] = 0.0829372;
  beta[4] = 0.0822243;
  beta[5] = 0.0816107;
  beta[6] = 0.0809897;
  beta[7] = 0.0704709;
  beta[8] = 0.0798328;
  beta[9] = 0.0792996;
  beta[10] = 0.0787599;
  beta[11] = 0.0782138;
  beta[12] = 0.0776624;
  beta[13] = 0.0772186;
  beta[14] = 0.0766544;
  beta[15] = 0.0762019;
  beta[16] = 0.0757438;
  beta[17] = 0.0751612;
  beta[18] = 0.0746938;
  beta[19] = 0.0742205;
  beta[20] = 0.0737427;
  beta[21] = 0.0732602;
  beta[22] = 0.0727731;
  beta[23] = 0.0722811;
}

//
void angle_info::InitSiThtea()
{
  for(int i=0;i<24;i++){
    si_theta[i] = atan((r_min+(double)i)/d_target_si)/PI*180.;
  } 
}

//
void angle_info::InitSiPhi()
{
  for(int i=0;i<32;i++){
    si_phi[i] = 90 + 11.25*(double)i - 20. + phi_rotation;
  }
}

//
void angle_info::PrintAngleInfo()
{
  std::cout << "print Ge info ..." << std::endl;
  for(int i=0;i<5;i++){
    for(int j=0;j<16;j++){
      std::cout << i << " " << j << " " << ge_theta[i][j] << "==>" << ge_phi[i][j] << std::endl;
    }
  }

  std::cout << "print Si info ..." << std::endl;
  for(int i=0;i<24;i++){
    std::cout << i << " ==> " << si_theta[i] << std::endl;
  }

  std::cout << "print Si info ..." << std::endl;
  for(int i=0;i<32;i++){
    std::cout << i << " ==> " << si_phi[i] << std::endl;
  }
}
