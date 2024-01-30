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

  tr_in = (TTree*)file_in->Get("tree");
  tr_in->SetBranchAddress("mod", &mod);
  tr_in->SetBranchAddress("ch", &ch);
  tr_in->SetBranchAddress("energy", &energy);
  tr_in->SetBranchAddress("ts", &ts);

  //read Si dat
  ReadSiCaliData();
  ReadSiThresholdData();
  //PrintSiCaliData();
  //PrintSiThresholdData();

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
  GetGeSiData("tr_event", 0, 150);
  GetGeSiData("tr_bg", 600, 750);
  
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

  for(Long64_t i=0;i<tr_in->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr_in->GetEntries() << std::endl;

    tr_in->GetEntry(i);
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
void build::GetSiNormalizeSpeNoCoin()
{
  TH1D *h_normalize_nocoin[SIMODNUM][16];
  std::cout << "start get no cali Si spec no coincedence" << std::endl;

  TString str;
  for(int i=SIMODNUMMIN;i<=SIMODNUMMAX;i++){
    for(int j=0;j<16;j++){
      str.Clear();    
      str = str.Format("h_mod%02d_ch%02d", i, j);
      h_normalize_nocoin[i-SIMODNUMMIN][j] = new TH1D(str.Data(), str.Data(), 16384, 0, 65536);
    }
  }

  for(Long64_t i=0;i<tr_in->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr_in->GetEntries() << std::endl;

    tr_in->GetEntry(i);
    if(!(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX)) continue;
    h_normalize_nocoin[mod-SIMODNUMMIN][ch]->Fill(energy);   
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
      h_normalize_nocoin[i-SIMODNUMMIN][j]->Write();     
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
  Short_t Si_ring_id[nMaxSiRing]; // 0-23
  Double_t Si_ring_adc[nMaxSiRing];
  Long64_t Si_ring_ts[nMaxSiRing];
  Int_t n_Si_sector = 0;
  Short_t Si_sector_mod[nMaxSiSector];
  Short_t Si_sector_ch[nMaxSiSector];
  Short_t Si_sector_id[nMaxSiSector]; // 0-31
  Double_t Si_sector_adc[nMaxSiSector];
  Long64_t Si_sector_ts[nMaxSiSector];

  Short_t id = 0;

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_" << TIMEWINDOW;
  TTree *tr_Si = new TTree("tr_Si", ss.str().c_str());

  memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
  memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
  memset(Si_ring_id, 0, sizeof(Si_ring_id));
  memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
  memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
  memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
  memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
  memset(Si_sector_id, 0, sizeof(Si_sector_id));
  memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
  memset(Si_sector_ts, 0, sizeof(Si_sector_ts));

  tr_Si->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr_Si->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/S");
  tr_Si->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/S");
  tr_Si->Branch("Si_ring_id", Si_ring_id, "Si_ring_id[n_Si_ring]/S");
  tr_Si->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr_Si->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/L");
  tr_Si->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr_Si->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/S");
  tr_Si->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/S");
  tr_Si->Branch("Si_sector_id", Si_sector_id, "Si_sector_id[n_Si_sector]/S");
  tr_Si->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr_Si->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/L");

  Long64_t i_start = 0;
  
  id = 0;

  Short_t mod1 = 0;
  Short_t ch1 = 0;
  Short_t id1 = 0;
  Double_t energy1 = 0;
  Long64_t ts1 = 0;
  Short_t mod2 = 0;
  Short_t ch2 = 0;
  Short_t id2 = 0;
  Double_t energy2 = 0;
  Long64_t ts2 = 0;
  while(true){//get first si data
    tr_in->GetEntry(i_start);
    i_start++;

    if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX){
      energy = CaliSiEnergy(energy, mod, ch);
      id = GetSiID(mod, ch);
    }

    if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy>GetSiThreshold(mod,ch)){
      mod1 = mod;
      ch1 = ch;
      id1 = id;
      energy1 = energy;
      ts1 = ts;

      if((mod1*100+ch1)>=500 && (mod1*100+ch1)<=607){
        Si_ring_mod[n_Si_ring] = mod1;
        Si_ring_ch[n_Si_ring] = ch1;
        Si_ring_id[n_Si_ring] = id1;
        Si_ring_adc[n_Si_ring] = energy1;
        Si_ring_ts[n_Si_ring] = ts1;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod1;
        Si_sector_ch[n_Si_sector] = ch1;
        Si_sector_id[n_Si_sector] = id1;
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
    if(i==tr_in->GetEntries()) break;
    if(i%1000000==0){
      std::cout << "\r" << i << "/" << tr_in->GetEntries();
      std::cout << std::flush;
    }

    tr_in->GetEntry(i);

    if(!(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX)){//if Ge data
      i++;
      continue;
    }

    if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX){
      energy = CaliSiEnergy(energy, mod, ch);
      id = GetSiID(mod, ch);
    }
    if(energy<=GetSiThreshold(mod,ch)){//if small energy
      i++;
      continue;
    }

    mod2 = mod;
    ch2 = ch;
    id2 = id;
    energy2 = energy;
    ts2 = ts;
    
    if((ts2-ts1)<=TIMEWINDOW){//this coincidence
      if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
        Si_ring_mod[n_Si_ring] = mod2;
        Si_ring_ch[n_Si_ring] = ch2;
        Si_ring_id[n_Si_ring] = id2;
        Si_ring_adc[n_Si_ring] = energy2;
        Si_ring_ts[n_Si_ring] = ts2;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod2;
        Si_sector_ch[n_Si_sector] = ch2;
        Si_sector_id[n_Si_sector] = id2;
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

        /*
        if(n_Si_ring==2 && n_Si_sector==1 && TMath::Abs(Si_ring_id[0]-Si_ring_id[1])==1){
          if(Si_ring_adc[0]>Si_ring_adc[1]){
            Si_ring_adc[0] += Si_ring_adc[1];
          }else{
            Si_ring_adc[0] += Si_ring_adc[1];
            Si_ring_mod[0] = Si_ring_mod[1];
            Si_ring_ch[0] = Si_ring_ch[1];
            Si_ring_id[0] = Si_ring_id[1];
            Si_ring_ts[0] = Si_ring_ts[1];
          }
          n_Si_ring--;
        }
        if(n_Si_ring==1 && n_Si_sector==2 && (TMath::Abs(Si_sector_id[0]-Si_sector_id[1])==1||(TMath::Abs(Si_sector_id[0]-Si_sector_id[1]))==31)){
          if(Si_sector_adc[0]>Si_sector_adc[1]){
            Si_sector_adc[0] += Si_sector_adc[1];
          }else{
            Si_sector_adc[0] += Si_sector_adc[1];
            Si_sector_mod[0] = Si_sector_mod[1];
            Si_sector_ch[0] = Si_sector_ch[1];
            Si_sector_id[0] = Si_sector_id[1];
            Si_sector_ts[0] = Si_sector_ts[1];
          }
          n_Si_sector--;
        }
        */

        //
        file_out->cd();
        tr_Si->Fill();
      }
      
      n_Si_ring = 0;
      n_Si_sector = 0;

      id = 0;

      memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
      memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
      memset(Si_ring_id, 0, sizeof(Si_ring_id));
      memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
      memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
      memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
      memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
      memset(Si_sector_id, 0, sizeof(Si_sector_id));
      memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
      memset(Si_sector_ts, 0, sizeof(Si_sector_ts));

      mod1 = mod2;
      ch1 = ch2;
      id1 = id2;
      energy1 = energy2;
      ts1 = ts2;

      if((mod1*100+ch1)>=500 && (mod1*100+ch1)<=607){
        Si_ring_mod[n_Si_ring] = mod1;
        Si_ring_ch[n_Si_ring] = ch1;
        Si_ring_id[n_Si_ring] = id1;
        Si_ring_adc[n_Si_ring] = energy1;
        Si_ring_ts[n_Si_ring] = ts1;
        n_Si_ring++;
      }else{
        Si_sector_mod[n_Si_sector] = mod1;
        Si_sector_ch[n_Si_sector] = ch1;
        Si_sector_id[n_Si_sector] = id1;
        Si_sector_adc[n_Si_sector] = energy1;
        Si_sector_ts[n_Si_sector] = ts1;
        n_Si_sector++;
      }
    }

    i++;
  }//while
  std::cout << std::endl;
    
  file_out->cd();
  tr_Si->Write();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::GetGeSiData(TString tr_name, double abs_time1, double abs_time2)
{
  std::cout << "start get ge si data" << std::endl;

  int nMaxSiRing = 24;
  int nMaxSiSector = 32;
  int nMaxGe = 36;

  Int_t n_Si_ring = 0;
  Short_t Si_ring_mod[nMaxSiRing];
  Short_t Si_ring_ch[nMaxSiRing];
  Short_t Si_ring_id[nMaxSiRing]; // 0-23
  Double_t Si_ring_adc[nMaxSiRing];
  Long64_t Si_ring_ts[nMaxSiRing];
  Int_t n_Si_sector = 0;
  Short_t Si_sector_mod[nMaxSiSector];
  Short_t Si_sector_ch[nMaxSiSector];
  Short_t Si_sector_id[nMaxSiSector]; // 0-31
  Double_t Si_sector_adc[nMaxSiSector];
  Long64_t Si_sector_ts[nMaxSiSector];
  Int_t n_Ge = 0;
  Short_t Ge_mod[nMaxGe];
  Short_t Ge_ch[nMaxGe];
  Double_t Ge_energy[nMaxGe];
  Long64_t Ge_ts[nMaxGe];

  Short_t id = 0;

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_" << TIMEWINDOW;
  TTree *tr = new TTree(tr_name.Data(), ss.str().c_str());

  memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
  memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
  memset(Si_ring_id, 0, sizeof(Si_ring_id));
  memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
  memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
  memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
  memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
  memset(Si_sector_id, 0, sizeof(Si_sector_id));
  memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
  memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
  memset(Ge_mod, 0, sizeof(Ge_mod));
  memset(Ge_ch, 0, sizeof(Ge_ch));
  memset(Ge_energy, 0, sizeof(Ge_energy));
  memset(Ge_ts, 0, sizeof(Ge_ts));

  tr->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/S");
  tr->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/S");
  tr->Branch("Si_ring_id", Si_ring_id, "Si_ring_id[n_Si_ring]/S");
  tr->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/L");
  tr->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/S");
  tr->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/S");
  tr->Branch("Si_sector_id", Si_sector_id, "Si_sector_id[n_Si_sector]/S");
  tr->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/L");
  tr->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/S");
  tr->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/S");
  tr->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/L");

  Long64_t i_start = 0;

  id = 0;
  
  Short_t mod1 = 0;
  Short_t ch1 = 0;
  Double_t energy1 = 0;
  Long64_t ts1 = 0;
  Short_t mod2 = 0;
  Short_t ch2 = 0;
  Short_t id2 = 0;
  Double_t energy2 = 0;
  Long64_t ts2 = 0;

  while(true){//get first Ge data
    tr_in->GetEntry(i_start);
    i_start++;
    if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
      break;
    }
  }
  
  Long64_t n_evt = 0;
  Long64_t i = i_start;
  Long64_t i_current = i-1;
  while(true){
    if(i==tr_in->GetEntries()) break;

    tr_in->GetEntry(i_current);
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
      tr_in->GetEntry(i_current);
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX){
        energy = CaliSiEnergy(energy, mod, ch);
        id = GetSiID(mod, ch);
      }
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i_current--;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=GetSiThreshold(mod,ch)){//if Si data and small energy
        i_current--;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
      if((mod2*100+ch2)>=500){
        id2 = id;
      }
    
      if((abs(ts2-ts1))>abs_time1 && abs(ts2-ts1)<abs_time2){//this coincidence
        if((mod2*100+ch2)>=0 && (mod2*100+ch2)<=415){
          Ge_mod[n_Ge] = mod2; 
          Ge_ch[n_Ge] = ch2; 
          Ge_energy[n_Ge] = energy2; 
          Ge_ts[n_Ge] = ts2; 
          n_Ge++;
        }else if((mod2*100+ch2)>=500 && (mod2*100+ch2)<=607){
          Si_ring_mod[n_Si_ring] = mod2;
          Si_ring_ch[n_Si_ring] = ch2;
          Si_ring_id[n_Si_ring] = id2;
          Si_ring_adc[n_Si_ring] = energy2;
          Si_ring_ts[n_Si_ring] = ts2;
          n_Si_ring++;
        }else{
          Si_sector_mod[n_Si_sector] = mod2;
          Si_sector_ch[n_Si_sector] = ch2;
          Si_sector_id[n_Si_sector] = id2;
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
      if(i>=tr_in->GetEntries()) break;
      tr_in->GetEntry(i);
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX){
        energy = CaliSiEnergy(energy, mod, ch);
        id = GetSiID(mod, ch);
      }
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy<=CUTGE){//if Ge data and small energy
        i++;
        continue;
      }
      if(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX && energy<=GetSiThreshold(mod,ch)){//if Si data and small energy
        i++;
        continue;
      }

      mod2 = mod;
      ch2 = ch;
      energy2 = energy;
      ts2 = ts;
      if((mod2*100+ch2)>=500){
        id2 = id;
      }
    
      if(abs(ts2-ts1)>abs_time1 && abs(ts2-ts1)<abs_time2){//this coincidence
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
          Si_ring_id[n_Si_ring] = id2;
          Si_ring_adc[n_Si_ring] = energy2;
          Si_ring_ts[n_Si_ring] = ts2;
          n_Si_ring++;
        }else{
          Si_sector_mod[n_Si_sector] = mod2;
          Si_sector_ch[n_Si_sector] = ch2;
          Si_sector_id[n_Si_sector] = id2;
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

      //
      if(n_Si_ring==2 && n_Si_sector==1 && TMath::Abs(Si_ring_id[0]-Si_ring_id[1])==1){
        if(Si_ring_adc[0]>Si_ring_adc[1]){
          Si_ring_adc[0] += Si_ring_adc[1];
        }else{
          Si_ring_adc[0] += Si_ring_adc[1];
          Si_ring_mod[0] = Si_ring_mod[1];
          Si_ring_ch[0] = Si_ring_ch[1];
          Si_ring_id[0] = Si_ring_id[1];
          Si_ring_ts[0] = Si_ring_ts[1];
        }
        n_Si_ring--;
      }
      if(n_Si_ring==1 && n_Si_sector==2 && (TMath::Abs(Si_sector_id[0]-Si_sector_id[1])==1||(TMath::Abs(Si_sector_id[0]-Si_sector_id[1]))==31)){
        if(Si_sector_adc[0]>Si_sector_adc[1]){
          Si_sector_adc[0] += Si_sector_adc[1];
        }else{
          Si_sector_adc[0] += Si_sector_adc[1];
          Si_sector_mod[0] = Si_sector_mod[1];
          Si_sector_ch[0] = Si_sector_ch[1];
          Si_sector_id[0] = Si_sector_id[1];
          Si_sector_ts[0] = Si_sector_ts[1];
        }
        n_Si_sector--;
      }

      file_out->cd();
      tr->Fill();

      if(n_evt%1000==0){
        std::cout << "\r" << n_evt << "  " << i << "/" << tr_in->GetEntries();
        std::cout << std::flush;
      }
    }

    n_Si_ring = 0;
    memset(Si_ring_mod, 0, sizeof(Si_ring_mod));
    memset(Si_ring_ch, 0, sizeof(Si_ring_ch));
    memset(Si_ring_id, 0, sizeof(Si_ring_id));
    memset(Si_ring_adc, 0, sizeof(Si_ring_adc));
    memset(Si_ring_ts, 0, sizeof(Si_ring_ts));
    n_Si_sector = 0;
    memset(Si_sector_mod, 0, sizeof(Si_sector_mod));
    memset(Si_sector_ch, 0, sizeof(Si_sector_ch));
    memset(Si_sector_id, 0, sizeof(Si_sector_id));
    memset(Si_sector_adc, 0, sizeof(Si_sector_adc));
    memset(Si_sector_ts, 0, sizeof(Si_sector_ts));
    n_Ge = 0;
    memset(Ge_mod, 0, sizeof(Ge_mod));
    memset(Ge_ch, 0, sizeof(Ge_ch));
    memset(Ge_energy, 0, sizeof(Ge_energy));
    memset(Ge_ts, 0, sizeof(Ge_ts));

    while(true){//get next Ge data
      if(i>=tr_in->GetEntries()) break;
      tr_in->GetEntry(i);
      i++;
      if(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX && energy>CUTGE){
        break;
      }
    }
    i_current = i-1;

  }//while

  std::cout << std::endl;

  file_out->cd();
  tr->Write();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::ReadSiCaliData()
{
  std::cout << "start read Si cali data" << std::endl;

  std::ifstream ifs;
  ifs.open("../for_Si_front_and_back_correlation/analysis/run00804_si_cali.txt");
  if(!ifs){
    std::cout << "cannot open si_cali.dat." << std::endl;
    return ;
  }

  int mod, ch;
  double par0, par1;
  int key = 0;

  while(1){
    ifs >> mod >> ch >> par0 >> par1;
    if(!ifs.good()) break;

    key = 100*mod+ch;
    std::vector<double> value;
    value.push_back(par0);
    value.push_back(par1);

    map_si_cali_data.insert(std::pair<int, std::vector<double>>(key, value));
  }

  ifs.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::PrintSiCaliData()
{
  std::cout << "start read Si cali data" << std::endl;

  std::map<int, std::vector<double>>::iterator it = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    std::cout << it->first << " => " << it->second[0] << " " << it->second[1] << '\n';
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double build::CaliSiEnergy(int adc, int mod, int ch)
{
  int key = 100*mod+ch;

  auto it = map_si_cali_data.find(key);
  if(it==map_si_cali_data.end()) return 0;

  double adcc = map_si_cali_data[key][0] + adc*map_si_cali_data[key][1];
  return adcc;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::ReadSiThresholdData()
{
  std::cout << "start read Si threshold data" << std::endl;

  std::ifstream ifs;
  ifs.open("./threshold_si.txt");
  if(!ifs){
    std::cout << "cannot open si_threshold dat." << std::endl;
    return ;
  }

  int mod, ch;
  double th;
  int key = 0;

  while(1){
    ifs >> mod >> ch >> th;
    if(!ifs.good()) break;

    key = mod*100+ch;

    map_si_threshold_data.insert(std::pair<int, double>(key, th));
  }

  ifs.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::PrintSiThresholdData()
{
  std::cout << "start read Si threhold data" << std::endl;

  std::map<int, double>::iterator it = map_si_threshold_data.begin();
  for(it=map_si_threshold_data.begin();it!=map_si_threshold_data.end();it++){
    std::cout << it->first << " => " << it->second << '\n';
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Short_t build::GetSiID(int mod, int ch)
{
  if((mod*100+ch)>=500 && (mod*100+ch)<=607){
    return 16*(mod-5)+ch;
  }else{
    if(mod==6&&ch==14){
      return 23;
    }
    if(mod==6&&ch==15){
      return 31;
    }
    
    return 16*(mod-7)+ch;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t build::GetSiThreshold(int mod, int ch)
{
  int key = mod*100+ch;
  return map_si_threshold_data[key];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void build::SaveFile()
{
  file_out->cd();
  file_out->Close();
}
