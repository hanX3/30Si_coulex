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
  analysis(const std::string &filename_in, const std::string &filename_out, double phi=0., double x=0., double y=0., double z=0.);
  virtual ~analysis();

  void Process();
  void ProcessDoppler(doppler *dp, TString info);
  void SaveFile();

private:
  std::map<int, int> map_clover_modch2id;

public:
  void PrintCloverIDMap();

  double CaliEnergyNoDoppler(int adc, int mod, int ch);
  double CaliEnergyWithDoppler(int adc_ge, int mod_ge, int ch_ge, int si_ring_id, int si_sector_id);
  double CaliEnergyWithDopplerNew(int adc_ge, int mod_ge, int ch_ge, int si_ring_id, int si_sector_id);

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
