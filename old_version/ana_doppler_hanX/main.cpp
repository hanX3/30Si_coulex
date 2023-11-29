#include "analysis.h"
#include <iostream>

int main(int argc, char* argv[])
{
  if(argc!=2){
    std::cout << "need run number " << std::endl;
    return -1;
  }

  int run_num = atoi(argv[1]);

  analysis *ana = new analysis(run_num);
  ana->PrintGeCaliData();
  ana->PrintSiCaliData();
  ana->PrintCloverIDMap();

  ana->Process();
  ana->SaveFile();

  return 0;
}
