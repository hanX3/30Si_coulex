#include "analysis.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::analysis(int run)
{
  TString str_filename;
  str_filename.Clear();
  str_filename = str_filename.Format("../../data/run%05d_final.root", run);

  file_in = TFile::Open(str_filename.Data());
  if(file_in->IsZombie()){
    std::cout << "open file " << str_filename.Data() << " error!" << std::endl;
    delete file_in;

    return ;
  }

  tr = (TTree*)file_in->Get("tr");
  final_data = new final(tr);

  str_filename.Clear();
  str_filename = str_filename.Format("../ana_rootfile/run%05d_ana.root", run);
  file_out = new TFile(str_filename.Data(), "recreate");
  if(!file_out){
    std::cout << "can not create " << str_filename.Data() << std::endl;

    delete file_out;
    return ;
  }

  //init
  int GEMODNUM = GEMODNUMMAX-GEMODNUMMIN+1;
  for(int i=0;i<GEMODNUM;i++){
    for(int j=0;j<16;j++){
      for(int k=0;k<3;k++){
        par_cali[i][j][k] = 0.;
      }
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::~analysis()
{

  delete file_in;
  delete final_data;
  delete file_out;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::CheckOrignalTsWindow()
{
  std::cout << "start CheckOriginTsWindows" << std::endl;

  h_origin_time_diff = new TH1D("h_origin_time_diff", "h_origin_time_diff", 800, -400, 400);

  for(Long64_t i=0;i<tr->GetEntries();i++){
    final_data->GetEntry(i);
    //std::cout << final_data->nXIA << std::endl;
    if(final_data->nXIA<2)  continue;
    if(i%1000000 == 0)  std::cout << i << "/" << tr->GetEntries() << std::endl;
    for(int j=1;j<final_data->nXIA;j++){
      h_origin_time_diff->Fill(final_data->data_XIA_Event_ts[j]-final_data->data_XIA_Event_ts[0]);
    }
  }

  file_out->cd();
  h_origin_time_diff->Write();

  return ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::ReadCaliPar()
{
  std::cout << "start ReadCalPar" << std::endl;

  std::ifstream cali_file;
  cali_file.open("ener_cal.dat", std::ifstream::in);

  int mod, ch;
  double par0, par1, par2;
  double chi2;
  while(1){
    cali_file >> mod >> ch >> par0 >> par1 >> par2 >> chi2;
    //std::cout << mod << "  " << ch << "  " << par0 << "  " << par1 << "  " << par2 << "  " << chi2 << std::endl;
    if(!cali_file.good()) break;
  
    par_cali[mod][ch][0] = par0;
    par_cali[mod][ch][1] = par1;
    par_cali[mod][ch][2] = par2;
  }

  cali_file.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::PrintCaliPar()
{
  std::cout << "print cali par" << std::endl;

  for(int i=0;i<GEMODNUM;i++){
    for(int j=0;j<16;j++){
      std::cout << i << "  " << j << "  ";
      for(int k=0;k<3;k++){
        std::cout << par_cali[i][j][k] << "  ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  } 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::GetGeCaliSpeNoCoin()
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

  int mod, ch;
  double energy;
  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    final_data->GetEntry(i);
    for(int j=0;j<final_data->nXIA;j++){
      mod = final_data->data_XIA_channel[j];
      ch = mod%100;
      mod = (mod-ch)/100-1;
      //std::cout << final_data->nXIA << " " << mod << " " << ch << " " << final_data->data_XIA_Energy[j] << std::endl;
      if(!(mod>=GEMODNUMMIN && mod<=GEMODNUMMAX)) continue;
      energy = CaliEnergyNoDoppler(final_data->data_XIA_Energy[j], mod, ch);
      if(energy<CUTGE)  continue;
      h_cali_nocoin[mod-GEMODNUMMIN][ch]->Fill(energy);   
    }
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
void analysis::GetSiNoCaliSpeNoCoin()
{
  std::cout << "start get no cali Si spec no coincedence" << std::endl;

  TH1D *h_nocali_nocoin[SIMODNUM][16];
  TString str;
  for(int i=SIMODNUMMIN;i<=SIMODNUMMAX;i++){
    for(int j=0;j<16;j++){
      str.Clear();    
      str = str.Format("h_mod%02d_ch%02d", i, j);
      h_nocali_nocoin[i-SIMODNUMMIN][j] = new TH1D(str.Data(), str.Data(), 16384, 0, 65536);
    }
  }

  int mod, ch;
  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    final_data->GetEntry(i);
    for(int j=0;j<final_data->nXIA;j++){
      mod = final_data->data_XIA_channel[j];
      ch = mod%100;
      mod = (mod-ch)/100-1;
      //std::cout << final_data->nXIA << " " << mod << " " << ch << " " << final_data->data_XIA_Energy[j] << std::endl;
      if(!(mod>=SIMODNUMMIN && mod<=SIMODNUMMAX)) continue;
      h_nocali_nocoin[mod-SIMODNUMMIN][ch]->Fill(final_data->data_XIA_Energy[j]);   
    }
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
void analysis::GetSiFrontBackCorrelationData()
{
  std::cout << "start get Si front-back correlation data" << std::endl;

  int nMaxSiRing = 24;
  int nMaxSiSector = 32;

  Int_t n_Si_ring;
  Int_t Si_ring_mod[nMaxSiRing];
  Int_t Si_ring_ch[nMaxSiRing];
  Double_t Si_ring_adc[nMaxSiRing];
  Double_t Si_ring_ts[nMaxSiRing];
  Int_t n_Si_sector;
  Int_t Si_sector_mod[nMaxSiSector];
  Int_t Si_sector_ch[nMaxSiSector];
  Double_t Si_sector_adc[nMaxSiSector];
  Double_t Si_sector_ts[nMaxSiSector];

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_origin";
  TTree *tr1_Si = new TTree("tr1_Si", ss.str().c_str());
  tr1_Si->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr1_Si->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr1_Si->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr1_Si->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr1_Si->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr1_Si->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr1_Si->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr1_Si->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr1_Si->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr1_Si->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");

  ss.str("");
  ss << "timewindow_" << TIMEWINDOW1;
  TTree *tr2_Si = new TTree("tr2_Si", ss.str().c_str());
  tr2_Si->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr2_Si->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr2_Si->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr2_Si->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr2_Si->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr2_Si->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr2_Si->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr2_Si->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr2_Si->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr2_Si->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");

  ss.str("");
  ss << "timewindow_" << TIMEWINDOW2;
  TTree *tr3_Si = new TTree("tr3_Si", ss.str().c_str());
  tr3_Si->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr3_Si->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr3_Si->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr3_Si->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr3_Si->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr3_Si->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr3_Si->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr3_Si->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr3_Si->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr3_Si->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");

  int mod, ch;
  file_out->cd();
  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    n_Si_ring = 0;
    n_Si_sector = 0;

    final_data->GetEntry(i);
    
    for(int j=0;j<final_data->nXIA;j++){
      mod = final_data->data_XIA_channel[j];
      ch = mod%100;
      mod = (mod-ch)/100-1;
      //std::cout << final_data->nXIA << " " << mod << " " << ch << " " << final_data->data_XIA_Energy[j] << std::endl;
      
      //Fill
      if(final_data->data_XIA_channel[j]>=600 && final_data->data_XIA_channel[j]<=707){
        if(final_data->data_XIA_Energy[j] < CUTSI) continue;
        Si_ring_mod[n_Si_ring] = mod;
        Si_ring_ch[n_Si_ring] = ch;
        Si_ring_adc[n_Si_ring] = final_data->data_XIA_Energy[j];
        Si_ring_ts[n_Si_ring] = final_data->data_XIA_Event_ts[j];
        n_Si_ring++;
      }
      else if(final_data->data_XIA_channel[j]>=714 && final_data->data_XIA_channel[j]<=915){
        if(final_data->data_XIA_Energy[j] < CUTSI) continue;
        Si_sector_mod[n_Si_sector] = mod;
        Si_sector_ch[n_Si_sector] = ch;
        Si_sector_adc[n_Si_sector] = final_data->data_XIA_Energy[j];
        Si_sector_ts[n_Si_sector] = final_data->data_XIA_Event_ts[j];
        n_Si_sector++;
      }
      else{
        continue;
      }
    }
    if(n_Si_ring*n_Si_sector > 0){
      //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
      tr1_Si->Fill();

      //time window1
      for(int ii=1;ii<n_Si_ring;ii++){
        if(abs(Si_ring_ts[ii]-Si_ring_ts[0]) > TIMEWINDOW1){
          n_Si_ring--;
        }
      }
      for(int ii=0;ii<n_Si_sector;ii++){
        if(abs(Si_sector_ts[ii]-Si_ring_ts[0]) > TIMEWINDOW1){
          n_Si_sector--;
        }
      }
      if(n_Si_ring*n_Si_sector > 0){
        //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
        tr2_Si->Fill();

        //time window2
        for(int ii=1;ii<n_Si_ring;ii++){
          if(abs(Si_ring_ts[ii]-Si_ring_ts[0]) > TIMEWINDOW2){
            n_Si_ring--;
          }
        }
        for(int ii=0;ii<n_Si_sector;ii++){
          if(abs(Si_sector_ts[ii]-Si_ring_ts[0]) > TIMEWINDOW2){
            n_Si_sector--;
          }
        }
        if(n_Si_ring*n_Si_sector > 0){
          //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
          tr3_Si->Fill();
        }
      }
    }
  }
  tr1_Si->Write();
  tr2_Si->Write();
  tr3_Si->Write();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::GetGeCaliSpeWithCoin()
{
  std::cout << "start get cali spec with coincedence" << std::endl;
   
  int nMaxSiRing = 24;
  int nMaxSiSector = 32;
  int nMaxGe = 36;

  Int_t n_Si_ring;
  Int_t Si_ring_mod[nMaxSiRing];
  Int_t Si_ring_ch[nMaxSiRing];
  Double_t Si_ring_adc[nMaxSiRing];
  Double_t Si_ring_ts[nMaxSiRing];
  Int_t n_Si_sector;
  Int_t Si_sector_mod[nMaxSiSector];
  Int_t Si_sector_ch[nMaxSiSector];
  Double_t Si_sector_adc[nMaxSiSector];
  Double_t Si_sector_ts[nMaxSiSector];
  Int_t n_Ge;
  Int_t Ge_mod[nMaxGe];
  Int_t Ge_ch[nMaxGe];
  Double_t Ge_adc[nMaxGe];
  Double_t Ge_energy[nMaxGe];
  Double_t Ge_ts[nMaxGe];

  std::stringstream ss;
  ss.str("");
  ss << "timewindow_origin";
  TTree *tr1 = new TTree("tr1", ss.str().c_str());
  tr1->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr1->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr1->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr1->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr1->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr1->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr1->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr1->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr1->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr1->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");
  tr1->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr1->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/I");
  tr1->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/I");
  tr1->Branch("Ge_adc", Ge_adc, "Ge_adc[n_Ge]/D");
  tr1->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr1->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/D");

  ss.str("");
  ss << "timewindow_" << TIMEWINDOW1;
  TTree *tr2 = new TTree("tr2", ss.str().c_str());
  tr2->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr2->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr2->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr2->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr2->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr2->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr2->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr2->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr2->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr2->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");
  tr2->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr2->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/I");
  tr2->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/I");
  tr2->Branch("Ge_adc", Ge_adc, "Ge_adc[n_Ge]/D");
  tr2->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr2->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/D");

  ss.str("");
  ss << "timewindow_" << TIMEWINDOW2;
  TTree *tr3 = new TTree("tr3", ss.str().c_str());
  tr3->Branch("n_Si_ring", &n_Si_ring, "n_Si_ring/I");
  tr3->Branch("Si_ring_mod", Si_ring_mod, "Si_ring_mod[n_Si_ring]/I");
  tr3->Branch("Si_ring_ch", Si_ring_ch, "Si_ring_ch[n_Si_ring]/I");
  tr3->Branch("Si_ring_adc", Si_ring_adc, "Si_ring_adc[n_Si_ring]/D");
  tr3->Branch("Si_ring_ts", Si_ring_ts, "Si_ring_ts[n_Si_ring]/D");
  tr3->Branch("n_Si_sector", &n_Si_sector, "n_Si_sector/I");
  tr3->Branch("Si_sector_mod", Si_sector_mod, "Si_sector_mod[n_Si_sector]/I");
  tr3->Branch("Si_sector_ch", Si_sector_ch, "Si_sector_ch[n_Si_sector]/I");
  tr3->Branch("Si_sector_adc", Si_sector_adc, "Si_sector_adc[n_Si_sector]/D");
  tr3->Branch("Si_sector_ts", Si_sector_ts, "Si_sector_ts[n_Si_sector]/D");
  tr3->Branch("n_Ge", &n_Ge, "n_Ge/I");
  tr3->Branch("Ge_mod", Ge_mod, "Ge_mod[n_Ge]/I");
  tr3->Branch("Ge_ch", Ge_ch, "Ge_ch[n_Ge]/I");
  tr3->Branch("Ge_adc", Ge_adc, "Ge_adc[n_Ge]/D");
  tr3->Branch("Ge_energy", Ge_energy, "Ge_energy[n_Ge]/D");
  tr3->Branch("Ge_ts", Ge_ts, "Ge_ts[n_Ge]/D");

  int mod, ch;
  file_out->cd();
  for(Long64_t i=0;i<tr->GetEntries();i++){
    if(i%1000000==0) std::cout << i << "/" << tr->GetEntries() << std::endl;

    n_Si_ring = 0;
    n_Si_sector = 0;
    n_Ge = 0;

    final_data->GetEntry(i);
    
    for(int j=0;j<final_data->nXIA;j++){
      mod = final_data->data_XIA_channel[j];
      ch = mod%100;
      mod = (mod-ch)/100-1;
      //std::cout << final_data->nXIA << " " << mod << " " << ch << " " << final_data->data_XIA_Energy[j] << std::endl;
      
      //Fill
      if(final_data->data_XIA_channel[j]>=100 && final_data->data_XIA_channel[j]<=515){
        Ge_mod[n_Ge] = mod;
        Ge_ch[n_Ge] = ch;
        Ge_adc[n_Ge] = final_data->data_XIA_Energy[j];
        Ge_energy[n_Ge] = CaliEnergyNoDoppler(final_data->data_XIA_Energy[j], mod, ch);
        Ge_ts[n_Ge] = final_data->data_XIA_Event_ts[j];
        n_Ge++;
      }
      else if(final_data->data_XIA_channel[j]>=600 && final_data->data_XIA_channel[j]<=707){
        if(final_data->data_XIA_Energy[j] < CUTSI) continue;
        Si_ring_mod[n_Si_ring] = mod;
        Si_ring_ch[n_Si_ring] = ch;
        Si_ring_adc[n_Si_ring] = final_data->data_XIA_Energy[j];
        Si_ring_ts[n_Si_ring] = final_data->data_XIA_Event_ts[j];
        n_Si_ring++;
      }
      else{
        if(final_data->data_XIA_Energy[j] < CUTSI) continue;
        Si_sector_mod[n_Si_sector] = mod;
        Si_sector_ch[n_Si_sector] = ch;
        Si_sector_adc[n_Si_sector] = final_data->data_XIA_Energy[j];
        Si_sector_ts[n_Si_sector] = final_data->data_XIA_Event_ts[j];
        n_Si_sector++;
      }
    }
    if(n_Ge*n_Si_ring*n_Si_sector > 0){
      //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
      tr1->Fill();

      //time window1
      for(int ii=1;ii<n_Ge;ii++){
        if(abs(Ge_ts[ii]-Ge_ts[0]) > TIMEWINDOW1){
          n_Ge--;
        }
      }
      for(int ii=0;ii<n_Si_ring;ii++){
        if(abs(Si_ring_ts[ii]-Ge_ts[0]) > TIMEWINDOW1){
          n_Si_ring--;
        }
      }
      for(int ii=0;ii<n_Si_sector;ii++){
        if(abs(Si_sector_ts[ii]-Ge_ts[0]) > TIMEWINDOW1){
          n_Si_sector--;
        }
      }
      if(n_Ge*n_Si_ring*n_Si_sector > 0){
        //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
        tr2->Fill();

        //time window2
        for(int ii=1;ii<n_Ge;ii++){
          if(abs(Ge_ts[ii]-Ge_ts[0]) > TIMEWINDOW2){
            n_Ge--;
          }
        }
        for(int ii=0;ii<n_Si_ring;ii++){
          if(abs(Si_ring_ts[ii]-Ge_ts[0]) > TIMEWINDOW2){
            n_Si_ring--;
          }
        }
        for(int ii=0;ii<n_Si_sector;ii++){
          if(abs(Si_sector_ts[ii]-Ge_ts[0]) > TIMEWINDOW2){
            n_Si_sector--;
          }
        }
        if(n_Ge*n_Si_ring*n_Si_sector > 0){
          //std::cout << i << " n_Ge " << n_Ge << " n_Si_ring " << n_Si_ring << " n_Si_sector " << n_Si_sector << std::endl;
          tr3->Fill();
        }
      }
    }
  }
  tr1->Write();
  tr2->Write();
  tr3->Write();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::SaveFile()
{
  file_out->cd();
  file_out->Close();
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double analysis::CaliEnergyNoDoppler(int adc, int mod, int ch)
{
  double energy = par_cali[mod][ch][0] + adc*par_cali[mod][ch][1] + adc*adc*par_cali[mod][ch][2];

  return energy;
}
