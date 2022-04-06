#include "analysis.h"
#include <iostream>

int main(int argc, char* argv[])
{
  if(argc!= 6){
    std::cout << "need run number, beta_attenuation, beam_position x, y, z " << std::endl;
    return -1;
  }

  int run_num = atoi(argv[1]);
  double beta_attenuation = atof(argv[2]);
  double x = atof(argv[3]);
  double y = atof(argv[4]);
  double z = atof(argv[5]);

  analysis *ana = new analysis(run_num, beta_attenuation, x, y, z);
  //ana->PrintGeCaliData();
  //ana->PrintSiCaliData();
  //ana->PrintCloverIDMap();

  ana->Process();
  ana->SaveFile();

  return 0;
}
