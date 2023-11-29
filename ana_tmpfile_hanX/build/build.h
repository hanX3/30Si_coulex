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
  void GetSiNoCaliSpeNoCoin();
  void GetSiFrontBackCorrelationData();
  void GetGeSiEvent();
  void GetGeSiBackground();
  void SaveFile();

private:

private:
  TBenchmark *benchmark;  
  TRandom3 *rndm;  

private:
  TFile *file_in;
  TTree *tr;
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
