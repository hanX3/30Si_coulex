#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "set.h"

#include "TBenchmark.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include <vector>
#include <iostream>

//
class analysis
{
public:
  analysis() = default;
  analysis(const std::string &filename_in, const std::string &filename_out);
  ~analysis();

public:
  void ProcessGevsGe();
  void ProcessSiRingvsSiSector();
  void ProcessGevsSi();

private:
  void GetTimestampVector(TTree *tr, UShort_t e_cut, std::vector<Long64_t> &vec);

private:
  TBenchmark *benchmark;

  TFile *file_in;
  TTree *tr[16*9];

  UShort_t ch;
  UShort_t energy;
  Long64_t ts;

  Int_t id_Ge;//the first ge channel with data
  Int_t id_Si_ring;//the first Si ring channel with data
  Int_t id_Si_sector;//the first Si sector channel with data
  TFile *file_out;
  TH1D *h1[5*16];//Ge vs. Ge
  TH1D *h2[24*32];//Si ring vs. Si sector
  TH1D *h3[24+32];//Ge vs. Si
};

#endif
