#ifndef ADDBACK_H_
#define ADDBACK_H_

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
  Bool_t ab_flag;
};

//
class addback
{
public:
  addback() = default;
  addback(const std::string &filename_in, const std::string &filename_out);
  ~addback();

public:
  void Process();
  void SaveFile();

private:
  void Analysis();

private:
  TBenchmark *benchmark;

  std::map<Long64_t, xia_data> data;
  std::map<Long64_t, xia_data>::iterator it;

  Long64_t key;
  xia_data map_value;

  Long64_t hit1[CLOVERNUM];
  Long64_t hit2[CLOVERNUM];
  Long64_t hit3[CLOVERNUM];
  Long64_t hit4[CLOVERNUM];

  Long64_t hit2_adj[CLOVERNUM];
  Long64_t hit2_dia[CLOVERNUM];
private:
  Short_t mod_;
  Short_t ch_;
  Double_t energy_;
  Long64_t ts_;

  TTree *tr_in;
  TFile *file_in;

  //
  Short_t mod;
  Short_t ch;
  Double_t energy;
  Long64_t ts;
  Bool_t ab_flag;

  TTree *tr;
  TFile *file_out;
};

#endif
