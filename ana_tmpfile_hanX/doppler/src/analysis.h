#ifndef _analysis_h_
#define _analysis_h_

#include "doppler.h"
#include "angle_info.h"

#include <vector>
#include <map>

#include "TH1D.h"
#include "TBenchmark.h"

class analysis
{
public:
  analysis(const std::string &filename_in, const std::string &filename_out, double phi, double x, double y, double z);
  virtual ~analysis();

  void Process();
  void ProcessDoppler(doppler *dp, TString info);
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
  double CaliEnergyWithDopplerNew(int adc_ge, int mod_ge, int ch_ge, int mod_si_ring, int ch_si_ring, int mod_si_sector, int ch_si_sector);
  double NormalizeSi(int adc, int mod, int ch); 

private:
  angle_info *angle;

private:
  TBenchmark *benchmark;
  TFile *file_in;
  TTree *tr_event, *tr_bg;

  


  doppler *doppler_event, *doppler_bg;

  TFile *file_out;
};


#endif
