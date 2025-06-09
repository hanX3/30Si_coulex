#ifndef _build_h_
#define _build_h_

#include "set.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TBenchmark.h"

#include "TSystem.h"

#include <iostream>

class build
{
public:
  build(const std::string &filename_in, const std::string &filename_out);
  virtual ~build();

  void Process();
  void GetGeCaliSpeNoCoin();
  void GetSiNormalizeSpeNoCoin();
  void GetSiFrontBackCorrelationData();
  void GetGeSiDataPrompt();
  void GetGeSiDataRandom();
  void SaveFile();

private:
  std::map<int, std::vector<double>> map_si_cali_data;
  std::map<int, double> map_si_threshold_data;

private:
  void ReadSiCaliData();
  void PrintSiCaliData();

private:
  double CaliSiEnergy(int adc, int mod, int ch);
  Short_t GetSiID(int mod, int ch);

private:
  TBenchmark *benchmark;  
  TRandom3 *rndm;  

private:
  TFile *file_in;
  TTree *tr_in;
  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;

  TH1D *h_nocali_nocoin[SIMODNUM][16];
  TH2D *hh_si_2d_spec;
  TH2D *hh_si_ring_2d_spec;

  TFile *file_out;
};

#endif
