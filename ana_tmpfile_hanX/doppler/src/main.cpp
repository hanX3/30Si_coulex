#include "analysis.h"
#include <iostream>

#include "set.h"

int main(int argc, char* argv[])
{
  if(argc!= 6){
    std::cout << "need run number, phi rotation, beam_position x, y, z " << std::endl;
    return -1;
  }

  int run = atoi(argv[1]);
  TString file_in = TString::Format("../../build/rootfile/run%05d_build.root", run);
  std::cout << "analysis " << file_in << std::endl;

  double phi = atof(argv[2]);
  double x = atof(argv[3]);
  double y = atof(argv[4]);
  double z = atof(argv[5]);

  TString file_out = TString::Format("../rootfile/run%05d_doppler.root", run);
  analysis *ana = new analysis(file_in.Data(), file_out.Data(), phi, x, y, z);

  ana->Process();
  ana->SaveFile();

  return 0;
}
