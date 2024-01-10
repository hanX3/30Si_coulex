#ifndef SORT_H_
#define SORT_H_

#include "set.h"

#include "TBenchmark.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom3.h"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

struct xia_data
{
  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;
};

//
class sort
{
public:
  sort() = default;
  sort(const std::string &filename_in, const std::string &filename_out);
  ~sort();

public:
  void Process();

  void PrintGeCaliPar();
  void PrintSiCaliPar();
  void PrintTsOffsetPar();

private:
  void ReadGeCaliPar();
  void ReadSiCaliPar();
  void ReadTsOffsetPar();

  void SaveFile();

private:
  double CaliGeEnergy(int adc, int mod, int ch);
  double CaliSiEnergy(int adc, int mod, int ch);

private:
  double par_ge_cali[GEMODNUM+SIMODNUM][16][3];
  std::map<int, std::vector<double>> map_si_cali_data;
  double par_ts_offset[GEMODNUM+SIMODNUM][16];

  std::map<Long64_t, xia_data> data;
  std::map<Long64_t, xia_data>::iterator it;

  bool have_data[(GEMODNUM+SIMODNUM)*16];
  Long64_t entries[(GEMODNUM+SIMODNUM)*16];
  Long64_t entry_n[(GEMODNUM+SIMODNUM)*16];
  Long64_t key;
  xia_data map_value;

  TBenchmark *benchmark;
  TRandom3 *rndm;

private:
  //
  UShort_t ch_[(GEMODNUM+SIMODNUM)*16];
  UShort_t energy_[(GEMODNUM+SIMODNUM)*16];
  Long64_t ts_[(GEMODNUM+SIMODNUM)*16];
  
  TTree *tr_[(GEMODNUM+SIMODNUM)*16];
  TFile *file_in;

  //
  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;

  TTree *tr;
  TFile *file_out;
};

#endif
