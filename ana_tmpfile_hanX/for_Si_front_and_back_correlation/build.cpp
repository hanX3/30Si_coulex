#include "build.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
build::build(const std::string &filename_in, const std::string &filename_out)
{
  benchmark = new TBenchmark;

  file_in = TFile::Open(filename_in.c_str());
  if(file_in->IsZombie()){
    std::cout << "open file " << filename_in << " error!" << std::endl;
    delete file_in;

    return ;
  }

  tr = (TTree*)file_in->Get("tree");
  tr->SetBranchAddress("mod", &mod);
  tr->SetBranchAddress("ch", &ch);
  tr->SetBranchAddress("energy", &energy);
  tr->SetBranchAddress("ts", &ts);

  rndm = new TRandom3((Long64_t)time(0));
  file_out = TFile::Open(filename_out.c_str(), "recreate");
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
build::~build()
{
  delete file_in;
  delete file_out;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::Process()
{
  benchmark->Start("build");

  GetSiFrontBackCorrelationData();
  
  benchmark->Show("build");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::GetSiFrontBackCorrelationData()
{
  std::cout << "start get Si front-back correlation data" << std::endl;

  int nMaxSiRing = 24;
  int nMaxSiSector = 32;

  Int_t n_Si_ring = 0;
  Short_t Si_ring_mod[nMaxSiRing];
  Short_t Si_ring_ch[nMaxSiRing];
  Double_t Si_ring_adc[nMaxSiRing];
  Long64_t Si_ring_ts[nMaxSiRing];
  Int_t n_Si_sector = 0;
  Short_t Si_sector_mod[nMaxSiSector];
  Short_t Si_sector_ch[nMaxSiSector];
  Double_t Si_sector_adc[nMaxSiSector];
  Long64_t Si_sector_ts[nMaxSiSector];

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_" << TIMEWINDOW;
  TTree *tr_Si = new TTree("tr_Si", ss.str().c_str());

  memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
  memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
  memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
  memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
  memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
  memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
  memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
  memset(Si_sector_ts, 0, sizeof(Si_sector_ts));

  tr_Si->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr_Si->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/S");
  tr_Si->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/S");
  tr_Si->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr_Si->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/L");
  tr_Si->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr_Si->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/S");
  tr_Si->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/S");
  tr_Si->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr_Si->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/L");

  Long64_t i_start = 0;
  
  Short_t mod1 = 0;
  Short_t ch1 = 0;
  Double_t energy1 = 0;
  Long64_t ts1 = 0;
  Short_t mod2 = 0;
  Short_t ch2 = 0;
  Double_t energy2 = 0;
  Long64_t ts2 = 0;
  while(true){//get first si data
    tr->GetEntry(i_start);
    i_start++;
    if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy>CUTSI){
      mod1 = mod;
      ch1 = ch;
      energy1 = energy;
      ts1 = ts;

      if((mod1*100+ch1)>=500 && (mod1*100+ch1)<=607){
        Si_ring_mod[n_Si_ring] = mod1;
        Si_ring_ch[n_Si_ring] = ch1;
        Si_ring_adc[n_Si_ring] = energy1;
        Si_ring_ts[n_Si_ring] = ts1;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod1;
        Si_sector_ch[n_Si_sector] = ch1;
        Si_sector_adc[n_Si_sector] = energy1;
        Si_sector_ts[n_Si_sector] = ts1;
        n_Si_sector++;
      }

      break;
    }
  }
  std::cout << "i_start " << i_start <<std::endl;

  Long64_t i = i_start;
  while(true){
    if(i==tr->GetEntries()) break;
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    tr->GetEntry(i);
    if(!(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX)){//if Ge data
      i++;
      continue;
    }
    if(energy<=CUTSI){//if small energy
      i++;
      continue;
    }

    mod2 = mod;
    ch2 = ch;
    energy2 = energy;
    ts2 = ts;
    
    if((ts2-ts1)<=TIMEWINDOW){//this coincidence
      if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
        Si_ring_mod[n_Si_ring] = mod2;
        Si_ring_ch[n_Si_ring] = ch2;
        Si_ring_adc[n_Si_ring] = energy2;
        Si_ring_ts[n_Si_ring] = ts2;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod2;
        Si_sector_ch[n_Si_sector] = ch2;
        Si_sector_adc[n_Si_sector] = energy2;
        Si_sector_ts[n_Si_sector] = ts2;
        n_Si_sector++;
      }
    }else{//next coincidence
      //std::cout << "ring " << n_Si_ring << " sector " << n_Si_sector << std::endl;
      if(n_Si_ring*n_Si_sector > 0){
        /*
        for(int m=0;m<n_Si_ring;m++){
          std::cout << Si_ring_mod[m] << " " << Si_ring_ch[m] << " " << Si_ring_adc[m] << " " << Si_ring_ts[m] << std::endl;
        }
        for(int m=0;m<n_Si_sector;m++){
          std::cout << Si_sector_mod[m] << " " << Si_sector_ch[m] << " " << Si_sector_adc[m] << " " << Si_sector_ts[m] << std::endl;
        }
        */
        file_out->cd();
        tr_Si->Fill();
      }
      
      n_Si_ring = 0;
      n_Si_sector = 0;

      memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
      memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
      memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
      memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
      memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
      memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
      memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
      memset(Si_sector_ts, 0, sizeof(Si_sector_ts));

      mod1 = mod2;
      ch1 = ch2;
      energy1 = energy2;
      ts1 = ts2;

      if((mod1*100+ch1)>=500 && (mod1*100+ch1)<=607){
        Si_ring_mod[n_Si_ring] = mod1;
        Si_ring_ch[n_Si_ring] = ch1;
        Si_ring_adc[n_Si_ring] = energy1;
        Si_ring_ts[n_Si_ring] = ts1;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod1;
        Si_sector_ch[n_Si_sector] = ch1;
        Si_sector_adc[n_Si_sector] = energy1;
        Si_sector_ts[n_Si_sector] = ts1;
        n_Si_sector++;
      }
    }

    i++;
  }//while
    
  file_out->cd();
  tr_Si->Write();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::SaveFile()
{
  file_out->cd();
  file_out->Close();
}

