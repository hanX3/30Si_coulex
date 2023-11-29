#ifndef _analysis_h_
#define _analysis_h_

#include "doppler.h"
#include "angle_info.h"

#include <vector>
#include <map>

#include "TH1D.h"

class analysis
{
public:
  analysis(int run);
  virtual ~analysis();

  void Process();
  void SaveFile();

private:
  std::map<int, std::vector<double>> map_ge_cali_data;
  std::map<int, std::vector<double>> map_si_cali_data;
  std::map<int, int> map_clover_modch2id;

private:
  void ReadGeCaliData();
  void ReadSiCaliData();

public:
  void PrintGeCaliData(); 
  void PrintSiCaliData();
  void PrintCloverIDMap();

  double CaliEnergyNoDoppler(int adc, int mod, int ch);
  double CaliEnergyWithDoppler(int adc_ge, int mod_ge, int ch_ge, int mod_si_ring, int ch_si_ring, int mod_si_sector, int ch_si_sector);
  double NormalizeSi(int adc, int mod, int ch); 

private:
  angle_info *angle;

private:
  TFile *file_in;
  TTree *tr1, *tr2, *tr3;
  doppler *doppler1, *doppler2, *doppler3;

  TFile *file_out;
};


#endif
