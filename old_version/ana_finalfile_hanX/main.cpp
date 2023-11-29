#include "final.h"
#include "analysis.h"

#include <stdlib.h>

int main(int argc, char* argv[])
{
  if(argc!=2){
    std::cout << "need run number " << std::endl;
    return -1;
  }

  int run_num = atoi(argv[1]);

  analysis *ana = new analysis(run_num);

  //ana->CheckOrignalTsWindow();
  ana->ReadCaliPar();
  ana->PrintCaliPar();
  ana->GetGeCaliSpeNoCoin();
  ana->GetSiNoCaliSpeNoCoin();
  ana->GetSiFrontBackCorrelationData();
  ana->GetGeCaliSpeWithCoin();
  ana->SaveFile();

  return 0;
}
