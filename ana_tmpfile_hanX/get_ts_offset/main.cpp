#include "analysis.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>

#include "TString.h"

int main(int argc, char const *argv[])
{
  if(argc != 2){
    std::cout << "need parameter" << std::endl;
    std::cout << "like: analysis 33" << std::endl;
    return -1;
  }

  int run = atoi(argv[1]);
  TString file_in = TString::Format("/mnt/user/ExpData/2021_IMP_30Si_196Pt/run%05d_tmp.root", run);
  std::cout << "analysis " << file_in << std::endl;
  
  TString file_out = TString::Format("./rootfile/run%05d_ts.root", run);

  analysis *ana = new analysis(file_in.Data(), file_out.Data());
  ana->ProcessGevsGe();
  ana->ProcessSiRingvsSiSector();
  ana->ProcessGevsSi();

  delete ana;

  return 0;
}
