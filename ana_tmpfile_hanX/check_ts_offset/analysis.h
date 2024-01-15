#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "set.h"

#include "TBenchmark.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom3.h"

#include <vector>
#include <iostream>

struct xia_data
{
  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;
};

//
class analysis
{
public:
  analysis() = default;
  analysis(const std::string &filename_in, const std::string &filename_out);
  ~analysis();

public:
  void Process();

private:
  void Vector2Hist();
  void PrintXd(xia_data &x);

private:
  TBenchmark *benchmark;
  TRandom3 *rndm;

  xia_data xd;
  std::vector<xia_data> v_data;

  TFile *file_in;
  TTree *tr;

  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;

  TFile *file_out;
  TH1D *h_ts; // all
  TH1D *h_ge_ts; // ge vs. ge
  TH1D *h_si_ts; // si vs. si
  TH1D *h_ge_si_ts; // ge vs. si

  TH1D *h_ts2; // all
  TH1D *h_ge_ts2; // ge vs. ge
  TH1D *h_si_ts2; // si vs. si
  TH1D *h_ge_si_ts2; // ge vs. si
};

#endif
