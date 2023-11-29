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
  TBenchmark *benchmark;
  TRandom3 *rndm;

  TFile *file_in;
  TTree *tr;

  Long64_t ts;

  TFile *file_out;
  TH1D *h_ts;//all
};

#endif
