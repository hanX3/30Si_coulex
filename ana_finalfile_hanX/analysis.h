#ifndef _analysis_h_
#define _analysis_h_

#include "set.h"
#include "final.h"

#include "TH1D.h"

#include <iostream>

class analysis
{
public:
  analysis(int run);
  virtual ~analysis();

  void CheckOrignalTsWindow();
  void ReadCaliPar();
  void PrintCaliPar();

  void Ana();
  void GetGeCaliSpeNoCoin();
  void GetSiNoCaliSpeNoCoin();
  void GetSiFrontBackCorrelationData();
  void GetGeCaliSpeWithCoin();
  void SaveFile();

private:
  double CaliEnergyNoDoppler(int adc, int mod, int ch);

private:
  double par_cali[GEMODNUM][16][3];  
  

private:
  TFile *file_in;
  TTree *tr;
  final *final_data;

  TH1D *h_origin_time_diff;
  TFile *file_out;
};


#endif
