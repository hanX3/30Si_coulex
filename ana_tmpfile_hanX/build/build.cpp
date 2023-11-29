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

  //GetGeCaliSpeNoCoin();
  //GetSiNoCaliSpeNoCoin();
  //GetSiFrontBackCorrelationData();
  GetGeSiEvent();
  GetGeSiBackground();
  
  benchmark->Show("build");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::GetGeCaliSpeNoCoin()
{
  std::cout << "start get cali spec no coincedence" << std::endl;

  TH1D *h_cali_nocoin[GEMODNUM][16];
  TString str;
  for(int i=0;i<GEMODNUM;i++){
    for(int j=0;j<16;j++){
      str.Clear();    
      str = str.Format("h_mod%02d_ch%02d", i, j);
      h_cali_nocoin[i][j] = new TH1D(str.Data(), str.Data(), 8192, 0, 4096);
    }
  }

  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    tr->GetEntry(i);
    if(!(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX)) continue;
    if(energy<CUTGE)  continue;
    h_cali_nocoin[mod-GEMODNUMMIN][ch]->Fill(energy);
  }
  
  TDirectory *dir_mod[GEMODNUM];
  std::stringstream ss;
  for(int i=GEMODNUMMIN;i<=GEMODNUMMAX;i++){
    file_out->cd();
    ss.str("");
    ss << "mod" << i;
    dir_mod[i-GEMODNUMMIN] = file_out->mkdir(ss.str().c_str());
    dir_mod[i-GEMODNUMMIN]->cd();
    for(int j=0;j<16;j++){
      h_cali_nocoin[i-GEMODNUMMIN][j]->Write();     
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::GetSiNoCaliSpeNoCoin()
{
  TH1D *h_nocali_nocoin[SIMODNUM][16];
  std::cout << "start get no cali Si spec no coincedence" << std::endl;

  TString str;
  for(int i=SIMODNUMMIN;i<=SIMODNUMMAX;i++){
    for(int j=0;j<16;j++){
      str.Clear();    
      str = str.Format("h_mod%02d_ch%02d", i, j);
      h_nocali_nocoin[i-SIMODNUMMIN][j] = new TH1D(str.Data(), str.Data(), 16384, 0, 65536);
    }
  }

  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    tr->GetEntry(i);
    if(!(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX)) continue;
    h_nocali_nocoin[mod-SIMODNUMMIN][ch]->Fill(energy);   
  }
  
  TDirectory *dir_mod[SIMODNUM];
  std::stringstream ss;
  for(int i=SIMODNUMMIN;i<=SIMODNUMMAX;i++){
    file_out->cd();
    ss.str("");
    ss << "mod" << i;
    dir_mod[i-SIMODNUMMIN] = file_out->mkdir(ss.str().c_str());
    dir_mod[i-SIMODNUMMIN]->cd();
    for(int j=0;j<16;j++){
      h_nocali_nocoin[i-SIMODNUMMIN][j]->Write();     
    }
  }
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
void build::GetGeSiEvent()
{
  std::cout << "start get ge si event" << std::endl;

  int nMaxSiRing = 24;
  int nMaxSiSector = 32;
  int nMaxGe = 36;

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
  Int_t n_Ge = 0;
  Short_t Ge_mod[nMaxGe];
  Short_t Ge_ch[nMaxGe];
  Double_t Ge_energy[nMaxGe];
  Long64_t Ge_ts[nMaxGe];

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_" << TIMEWINDOW;
  TTree *tr_event = new TTree("tr_event", ss.str().c_str());

  memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
  memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
  memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
  memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
  memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
  memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
  memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
  memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
  memset(Ge_mod, 0, sizeof(Ge_mod));
  memset(Ge_ch, 0, sizeof(Ge_ch));
  memset(Ge_energy, 0, sizeof(Ge_energy));
  memset(Ge_ts, 0, sizeof(Ge_ts));

  tr_event->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr_event->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/S");
  tr_event->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/S");
  tr_event->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr_event->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/L");
  tr_event->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr_event->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/S");
  tr_event->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/S");
  tr_event->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr_event->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/L");
  tr_event->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr_event->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/S");
  tr_event->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/S");
  tr_event->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr_event->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/L");

  Long64_t i_start = 0;
  
  Short_t mod1 = 0;
  Short_t ch1 = 0;
  Double_t energy1 = 0;
  Long64_t ts1 = 0;
  Short_t mod2 = 0;
  Short_t ch2 = 0;
  Double_t energy2 = 0;
  Long64_t ts2 = 0;

  while(true){//get first Ge data
    tr->GetEntry(i_start);
    i_start++;
    if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
      break;
    }
  }
  std::cout << "i_start " << i_start <<std::endl;
  
  Long64_t n_evt = 0;
  Long64_t i = i_start;
  Long64_t i_current = i-1;
  while(true){
    if(i==tr->GetEntries()) break;

    tr->GetEntry(i_current);
    mod1 = mod;
    ch1 = ch;
    energy1 = energy;
    ts1 = ts;

    Ge_mod[n_Ge] = mod1; 
    Ge_ch[n_Ge] = ch1; 
    Ge_energy[n_Ge] = energy1; 
    Ge_ts[n_Ge] = ts1; 
    n_Ge++;

    while(true){//search backward
      if(i_current--<0) break;
      tr->GetEntry(i_current);
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i_current--;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=CUTSI){//if Si data and small energy
        i_current--;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
    
      if((abs(ts2-ts1))<=TIMEWINDOW){//this coincidence
        if((mod2*100+ch2)>=0 && (mod2*100+ch2)<=415){
          Ge_mod[n_Ge] = mod2; 
          Ge_ch[n_Ge] = ch2; 
          Ge_energy[n_Ge] = energy2; 
          Ge_ts[n_Ge] = ts2; 
          n_Ge++;
        }else if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
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
      }else{
        //std::cout << abs(ts2-ts1) << " ring " << n_Si_ring << " sector " << n_Si_sector << std::endl;
        break;
      }
    }//while search backward
    
    while(true){//search forward
      if(i>=tr->GetEntries()) break;
      tr->GetEntry(i);
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i++;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=CUTSI){//if Si data and small energy
        i++;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
    
      if(abs(ts2-ts1)<=TIMEWINDOW){//this coincidence
        i++;
        if((mod2*100+ch2)>=0 && (mod2*100+ch2)<=415){
          Ge_mod[n_Ge] = mod2; 
          Ge_ch[n_Ge] = ch2; 
          Ge_energy[n_Ge] = energy2; 
          Ge_ts[n_Ge] = ts2; 
          n_Ge++;
        }else if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
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
      }else{
        //std::cout << "ring " << n_Si_ring << " sector " << n_Si_sector << std::endl;
        break;
      }
    }

    // std::cout << "n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
    if(n_Ge*n_Si_ring*n_Si_sector > 0){
      n_evt++;
      file_out->cd();
      tr_event->Fill();

      if(n_evt%1000==0){
        std::cout << n_evt << std::endl;
        std::cout << i << "/" << tr->GetEntries() << std::endl;
      }
    }

    n_Si_ring = 0;
    memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
    memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
    memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
    memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
    n_Si_sector = 0;
    memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
    memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
    memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
    memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
    n_Ge = 0;
    memset(Ge_mod, 0, sizeof(Ge_mod));
    memset(Ge_ch, 0, sizeof(Ge_ch));
    memset(Ge_energy, 0, sizeof(Ge_energy));
    memset(Ge_ts, 0, sizeof(Ge_ts));

    while(true){//get next Ge data
      if(i>=tr->GetEntries()) break;
      tr->GetEntry(i);
      i++;
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
        break;
      }
    }
    i_current = i-1;

  }//while

  tr_event->Write();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::GetGeSiBackground()
{
  std::cout << "start get ge si background" << std::endl;

  int nMaxSiRing = 24;
  int nMaxSiSector = 32;
  int nMaxGe = 36;

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
  Int_t n_Ge = 0;
  Short_t Ge_mod[nMaxGe];
  Short_t Ge_ch[nMaxGe];
  Double_t Ge_energy[nMaxGe];
  Long64_t Ge_ts[nMaxGe];

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_" << TIMEWINDOW;
  TTree *tr_bg = new TTree("tr_bg", ss.str().c_str());

  memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
  memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
  memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
  memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
  memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
  memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
  memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
  memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
  memset(Ge_mod, 0, sizeof(Ge_mod));
  memset(Ge_ch, 0, sizeof(Ge_ch));
  memset(Ge_energy, 0, sizeof(Ge_energy));
  memset(Ge_ts, 0, sizeof(Ge_ts));

  tr_bg->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr_bg->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/S");
  tr_bg->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/S");
  tr_bg->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr_bg->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/L");
  tr_bg->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr_bg->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/S");
  tr_bg->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/S");
  tr_bg->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr_bg->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/L");
  tr_bg->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr_bg->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/S");
  tr_bg->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/S");
  tr_bg->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr_bg->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/L");

  Long64_t i_start = 0;
  
  Short_t mod1 = 0;
  Short_t ch1 = 0;
  Double_t energy1 = 0;
  Long64_t ts1 = 0;
  Short_t mod2 = 0;
  Short_t ch2 = 0;
  Double_t energy2 = 0;
  Long64_t ts2 = 0;

  while(true){//get first Ge data
    tr->GetEntry(i_start);
    i_start++;
    if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
      break;
    }
  }
  std::cout << "i_start " << i_start <<std::endl;
  
  Long64_t n_evt = 0;
  Long64_t i = i_start;
  Long64_t i_current = i-1;
  while(true){
    if(i==tr->GetEntries()) break;

    tr->GetEntry(i_current);
    mod1 = mod;
    ch1 = ch;
    energy1 = energy;
    ts1 = ts;

    Ge_mod[n_Ge] = mod1; 
    Ge_ch[n_Ge] = ch1; 
    Ge_energy[n_Ge] = energy1; 
    Ge_ts[n_Ge] = ts1; 
    n_Ge++;

    while(true){//search backward
      if(i_current--<0) break;
      tr->GetEntry(i_current);
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i_current--;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=CUTSI){//if Si data and small energy
        i_current--;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
    
      if(abs(ts2-ts1)>=TIMEJUMP && abs(ts2-ts1)<=(TIMEJUMP+TIMEWINDOW)){//this coincidence
        if((mod2*100+ch2)>=0 && (mod2*100+ch2)<=415){
          Ge_mod[n_Ge] = mod2; 
          Ge_ch[n_Ge] = ch2; 
          Ge_energy[n_Ge] = energy2; 
          Ge_ts[n_Ge] = ts2; 
          n_Ge++;
        }else if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
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
      }else{
        //std::cout << abs(ts2-ts1) << " ring " << n_Si_ring << " sector " << n_Si_sector << std::endl;
        break;
      }
    }//while search backward
    
    while(true){//search forward
      if(i>=tr->GetEntries()) break;
      tr->GetEntry(i);
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i++;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=CUTSI){//if Si data and small energy
        i++;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
    
      if(abs(ts2-ts1)>=TIMEJUMP && abs(ts2-ts1)<=(TIMEJUMP+TIMEWINDOW)){//this coincidence
        i++;
        if((mod2*100+ch2)>=0 && (mod2*100+ch2)<=415){
          Ge_mod[n_Ge] = mod2; 
          Ge_ch[n_Ge] = ch2; 
          Ge_energy[n_Ge] = energy2; 
          Ge_ts[n_Ge] = ts2; 
          n_Ge++;
        }else if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
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
      }else{
        //std::cout << "ring " << n_Si_ring << " sector " << n_Si_sector << std::endl;
        break;
      }
    }

    // std::cout << "n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
    if(n_Ge*n_Si_ring*n_Si_sector > 0){
      n_evt++;
      file_out->cd();
      tr_bg->Fill();

      if(n_evt%1000==0){
        std::cout << n_evt << std::endl;
        std::cout << i << "/" << tr->GetEntries() << std::endl;
      }
    }

    n_Si_ring = 0;
    memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
    memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
    memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
    memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
    n_Si_sector = 0;
    memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
    memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
    memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
    memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
    n_Ge = 0;
    memset(Ge_mod, 0, sizeof(Ge_mod));
    memset(Ge_ch, 0, sizeof(Ge_ch));
    memset(Ge_energy, 0, sizeof(Ge_energy));
    memset(Ge_ts, 0, sizeof(Ge_ts));

    while(true){//get next Ge data
      if(i>=tr->GetEntries()) break;
      tr->GetEntry(i);
      i++;
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
        break;
      }
    }
    i_current = i-1;

  }//while

  tr_bg->Write();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::SaveFile()
{
  file_out->cd();
  file_out->Close();
}

