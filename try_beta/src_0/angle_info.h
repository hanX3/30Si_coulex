#ifndef angle_info_h
#define angle_info_h

#define PI 3.14159265

class angle_info{
public:
  angle_info(double beta_attenuation, double x, double y, double z);//0.1<beta_attenuation<2.0
  virtual ~angle_info();

private:
  double d_target_si;
  double r_min;
  double r_max;

  double x_bp;
  double y_bp;
  double z_bp;

private:
  double ge_theta[5][16];
  double ge_phi[5][16];

  double beta[24];
  double si_theta[24];
  double si_phi[32];

public:
  void InitGeThtea();
  void InitGePhi();
  void InitBeta(double beta_attenuation);
  void InitSiThtea();
  void InitSiPhi();
  void PrintAngleInfo();

public:
  double GetGeTheta(int mod, int ch) { return ge_theta[mod][ch]*PI/180.; };
  double GetGePhi(int mod, int ch) { return ge_phi[mod][ch]*PI/180; };
  double GetBeta(int ring_id) { return beta[ring_id]; };
  double GetSiTheta(int ring_id) { return si_theta[ring_id]*PI/180; };
  double GetSiPhi(int sector_id) { return si_phi[sector_id]*PI/180; };

public:
  double GetCosThetaParticleGamma(int mod_ge, int ch_ge, int si_ring_id, int si_sector_id);

public:
  void PrintGuess1();
};

#endif
