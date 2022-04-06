#ifndef angle_info_h
#define angle_info_h

class angle_info{
public:
  angle_info();
  virtual ~angle_info();

public:
  double GETHETADEG[5][16];
  double GEPHIDEG[5][16];

  double BETA[24];
  double SITHETA[24];
  double SITHETADEG[24];
  double SIPHI[32];
  double SIPHIDEG[32];
};

#endif
