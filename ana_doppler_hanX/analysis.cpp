#include "analysis.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TH1D.h"

#include "set.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::analysis(int run)
{
  TString str_filename;
  str_filename.Clear();
  str_filename = str_filename.Format("../ana_rootfile/run%05d_ana.root", run);
  file_in = TFile::Open(str_filename.Data());
  if(file_in->IsZombie()){
    std::cout << "open file " << str_filename.Data() << " error!" << std::endl;
    delete file_in;

    return ;
  }

  str_filename.Clear();
  str_filename = str_filename.Format("../ana_rootfile/run%05d_result.root", run);
  file_out = new TFile(str_filename.Data(), "recreate");
  if(!file_out){
    std::cout << "can not create " << str_filename.Data() << std::endl;

    delete file_out;
    return ;
  }

  tr1 = (TTree*)file_in->Get("tr1");
  tr2 = (TTree*)file_in->Get("tr2");
  tr3 = (TTree*)file_in->Get("tr3");
  doppler1 = new doppler(tr1); 
  doppler2 = new doppler(tr2); 
  doppler3 = new doppler(tr3); 

  //map_clover_modch2id
  //mod2
  for(int i=0;i<12;i++){
    int key = 200+i;
    map_clover_modch2id.insert({key, i});
  }
  //mod3
  for(int i=12;i<24;i++){
    if(i==16){
      map_clover_modch2id.insert({300, i});
    }
    if(i>19){
      int key = 300+i-12;
      map_clover_modch2id.insert({key, i});
    }
  }
  //mod4
  for(int i=24;i<32;i++){
    if(i<28){
      int key = 400+i-24;
      map_clover_modch2id.insert({key, i});
    }
    else{
      int key = 400+i-24+4;
      map_clover_modch2id.insert({key, i});
    }
  }

  //read cali dat
  ReadGeCaliData();
  ReadSiCaliData();

  //angle info
  angle = new angle_info();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::~analysis()
{
  delete file_in;
  delete doppler1;
  delete doppler2;
  delete doppler3;
  delete file_out;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::Process()
{
  std::cout << "start Process" << std::endl;

  file_out->cd();
  TH1D *h_ge_no_doppler_ring1[4], *h_ge_no_doppler_ring2[4], *h_ge_no_doppler_ring4[4], *h_ge_no_doppler_ring5[4];
  TH1D *h_clover_no_doppler_ring3[4*8];
  TH1D *h_ge_doppler_ring1[4], *h_ge_doppler_ring2[4], *h_ge_doppler_ring4[4], *h_ge_doppler_ring5[4];
  TH1D *h_clover_doppler_ring3[4*8];
  TH1D *h_ge_no_doppler_ring1_all = new TH1D("h_ge_no_doppler_ring1_all", "h_ge_no_doppler_ring1_all", 8192, 0, 4096);
  TH1D *h_ge_doppler_ring1_all = new TH1D("h_ge_doppler_ring1_all", "h_ge_doppler_ring1_all", 8192, 0, 4096);
  TH1D *h_ge_no_doppler_ring2_all = new TH1D("h_ge_no_doppler_ring2_all", "h_ge_no_doppler_ring2_all", 8192, 0, 4096);
  TH1D *h_ge_doppler_ring2_all = new TH1D("h_ge_doppler_ring2_all", "h_ge_doppler_ring2_all", 8192, 0, 4096);
  TH1D *h_clover_no_doppler_ring3_all = new TH1D("h_clover_no_doppler_ring3_all", "h_clover_no_doppler_ring3_all", 8192, 0, 4096);
  TH1D *h_clover_doppler_ring3_all = new TH1D("h_clover_doppler_ring3_all", "h_clover_doppler_ring3_all", 8192, 0, 4096);
  TH1D *h_ge_no_doppler_ring4_all = new TH1D("h_ge_no_doppler_ring4_all", "h_ge_no_doppler_ring4_all", 8192, 0, 4096);
  TH1D *h_ge_doppler_ring4_all = new TH1D("h_ge_doppler_ring4_all", "h_ge_doppler_ring4_all", 8192, 0, 4096);
  TH1D *h_ge_no_doppler_ring5_all = new TH1D("h_ge_no_doppler_ring5_all", "h_ge_no_doppler_ring5_all", 8192, 0, 4096);
  TH1D *h_ge_doppler_ring5_all = new TH1D("h_ge_doppler_ring5_all", "h_ge_doppler_ring5_all", 8192, 0, 4096);
  TH1D *h_ge_no_doppler_all = new TH1D("h_ge_no_doppler_all", "h_ge_no_doppler_all", 8192, 0, 4096);
  TH1D *h_ge_doppler_all = new TH1D("h_ge_doppler_all", "h_ge_doppler_all", 8192, 0, 4096);

  TString str_hist_name, str_hist_title;
  for(int i=0;i<4;i++){
    str_hist_name = TString::Format("h_ge_no_doppler_ring1_%d", i+1);
    str_hist_title = TString::Format("h_ge_no_doppler_ring1_%d", i+1);
    h_ge_no_doppler_ring1[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_no_doppler_ring2_%d", 2*(i+1));
    str_hist_title = TString::Format("h_ge_no_doppler_ring2_%d", 2*(i+1));
    h_ge_no_doppler_ring2[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_no_doppler_ring4_%d", 2*i+1);
    str_hist_title = TString::Format("h_ge_no_doppler_ring4_%d", 2*i+1);
    h_ge_no_doppler_ring4[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_no_doppler_ring5_%d", i+1);
    str_hist_title = TString::Format("h_ge_no_doppler_ring5_%d", i+1);
    h_ge_no_doppler_ring5[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);

    str_hist_name = TString::Format("h_ge_doppler_ring1_%d", i+1);
    str_hist_title = TString::Format("h_ge_doppler_ring1_%d", i+1);
    h_ge_doppler_ring1[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_doppler_ring2_%d", 2*(i+1));
    str_hist_title = TString::Format("h_ge_doppler_ring2_%d", 2*(i+1));
    h_ge_doppler_ring2[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_doppler_ring4_%d", 2*i+1);
    str_hist_title = TString::Format("h_ge_doppler_ring4_%d", 2*i+1);
    h_ge_doppler_ring4[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
    str_hist_name = TString::Format("h_ge_doppler_ring5_%d", i+1);
    str_hist_title = TString::Format("h_ge_doppler_ring5_%d", i+1);
    h_ge_doppler_ring5[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
  }

  for(int i=0;i<32;i++){
    str_hist_name = TString::Format("h_clover_no_doppler_ring3_%d_%c", i/4+1, (char)(97+i%4));
    str_hist_title = TString::Format("h_clover_no_doppler_ring3_%d_%c", i/4+1, (char)(97+i%4));
    h_clover_no_doppler_ring3[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);

    str_hist_name = TString::Format("h_clover_doppler_ring3_%d_%c", i/4+1, (char)(97+i%4));
    str_hist_title = TString::Format("h_clover_doppler_ring3_%d_%c", i/4+1, (char)(97+i%4));
    h_clover_doppler_ring3[i] = new TH1D(str_hist_name.Data(), str_hist_title.Data(), 8192, 0, 4096);
  }


  for(Long64_t i=0;i<tr1->GetEntries();++i){
    if(i%1000000==0) std::cout << i << "/" << tr1->GetEntries() << std::endl;

    doppler1->GetEntry(i);
    if(doppler1->n_Si_ring==1 && doppler1->n_Si_sector==1){//////
      //doppler1->Show(i);
      double adc_si_ring = NormalizeSi(doppler1->Si_ring_adc[0], doppler1->Si_ring_mod[0], doppler1->Si_ring_ch[0]);
      double adc_si_sector = NormalizeSi(doppler1->Si_sector_adc[0], doppler1->Si_sector_mod[0], doppler1->Si_sector_ch[0]);
      if(abs(adc_si_ring-adc_si_sector) < CUTSIDIFF){
        for(int j=0;j<doppler1->n_Ge;j++){
          double energy_no_doppler = CaliEnergyNoDoppler(doppler1->Ge_adc[j], doppler1->Ge_mod[j], doppler1->Ge_ch[j]);
          double energy_doppler = CaliEnergyWithDoppler(doppler1->Ge_adc[j], doppler1->Ge_mod[j], doppler1->Ge_ch[j], doppler1->Si_ring_mod[0], doppler1->Si_ring_ch[0], doppler1->Si_sector_mod[0], doppler1->Si_sector_ch[0]);
          if(energy_no_doppler < 200.)  continue;
          h_ge_no_doppler_all->Fill(energy_no_doppler);
          h_ge_doppler_all->Fill(energy_doppler);

          if(doppler1->Ge_mod[j] == 0){//ring1 & ring2
            if(doppler1->Ge_ch[j] < 4){
              h_ge_no_doppler_ring1_all->Fill(energy_no_doppler);
              h_ge_doppler_ring1_all->Fill(energy_doppler);
              h_ge_no_doppler_ring1[doppler1->Ge_ch[j]]->Fill(energy_no_doppler);
              h_ge_doppler_ring1[doppler1->Ge_ch[j]]->Fill(energy_doppler);
            }
            else{
              h_ge_no_doppler_ring2_all->Fill(energy_no_doppler);
              h_ge_doppler_ring2_all->Fill(energy_doppler);
              h_ge_no_doppler_ring2[doppler1->Ge_ch[j]-4]->Fill(energy_no_doppler);
              h_ge_doppler_ring2[doppler1->Ge_ch[j]-4]->Fill(energy_doppler);
            }
          }
          else if(doppler1->Ge_mod[j] == 1){//ring 4 & ring5
            if(doppler1->Ge_ch[j] < 4){
              h_ge_no_doppler_ring4_all->Fill(energy_no_doppler);
              h_ge_doppler_ring4_all->Fill(energy_doppler);
              h_ge_no_doppler_ring4[doppler1->Ge_ch[j]]->Fill(energy_no_doppler);
              h_ge_doppler_ring4[doppler1->Ge_ch[j]]->Fill(energy_doppler);
            }
            else{
              h_ge_no_doppler_ring5_all->Fill(energy_no_doppler);
              h_ge_doppler_ring5_all->Fill(energy_doppler);
              h_ge_no_doppler_ring5[doppler1->Ge_ch[j]-4]->Fill(energy_no_doppler);
              h_ge_doppler_ring5[doppler1->Ge_ch[j]-4]->Fill(energy_doppler);
            }
          }else{//ring3, mod 2, 3, 4
            h_clover_no_doppler_ring3_all->Fill(energy_no_doppler);
            h_clover_doppler_ring3_all->Fill(energy_doppler);
            int key = 100*doppler1->Ge_mod[j]+doppler1->Ge_ch[j];
            h_clover_no_doppler_ring3[map_clover_modch2id[key]]->Fill(energy_no_doppler);
            h_clover_doppler_ring3[map_clover_modch2id[key]]->Fill(energy_doppler);
          }
        }
      }
    }
  }
  //write
  file_out->cd();
  h_ge_no_doppler_all->Write();
  h_ge_doppler_all->Write();

  TDirectory *dir_ge[5];//5 rings
  TString str_dir_name;
  for(int i=0;i<5;i++){
    if(i==2){//ring3
      str_dir_name.Clear();
      str_dir_name = TString::Format("clover_ring%d", i+1);
      file_out->cd();
      dir_ge[i] = file_out->mkdir(str_dir_name.Data());
      dir_ge[i]->cd();
      h_clover_no_doppler_ring3_all->Write();
      h_clover_doppler_ring3_all->Write();
      std::map<int, int>::iterator it = map_clover_modch2id.begin();
      for(it=map_clover_modch2id.begin();it!=map_clover_modch2id.end();it++){
        h_clover_no_doppler_ring3[it->second]->Write();
        h_clover_doppler_ring3[it->second]->Write();
      }
    }
    else{
      str_dir_name.Clear();
      str_dir_name = TString::Format("ge_ring%d", i+1);
      file_out->cd();
      dir_ge[i] = file_out->mkdir(str_dir_name.Data());
      dir_ge[i]->cd();
      if(i==0){//ring1
        h_ge_no_doppler_ring1_all->Write();
        h_ge_doppler_ring1_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring1[j]->Write();
          h_ge_doppler_ring1[j]->Write();
        }
      }
      if(i==1){//ring2
        h_ge_no_doppler_ring2_all->Write();
        h_ge_doppler_ring2_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring2[j]->Write();
          h_ge_doppler_ring2[j]->Write();
        }
      }
      if(i==3){//ring4
        h_ge_no_doppler_ring4_all->Write();
        h_ge_doppler_ring4_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring4[j]->Write();
          h_ge_doppler_ring4[j]->Write();
        }
      }
      if(i==4){//ring5
        h_ge_no_doppler_ring5_all->Write();
        h_ge_doppler_ring5_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring5[j]->Write();
          h_ge_doppler_ring5[j]->Write();
        }
      }
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::ReadGeCaliData()
{
  std::cout << "start read Ge cali data" << std::endl;

  std::ifstream ifs;
  ifs.open("ener_cal.dat");
  if(!ifs){
    std::cout << "cannot open ener_cal.dat" << std::endl;
    return ;
  }

  int mod, ch;
  double par0, par1, par2;
  double chi2;
  int key = 0;

  while(1){
    ifs >> mod >> ch >> par0 >> par1 >> par2 >> chi2;
    if(!ifs.good()) break;

    key = 100*mod+ch;
    std::vector<double> value;
    value.push_back(par0);
    value.push_back(par1);
    value.push_back(par2);

    map_ge_cali_data.insert(std::pair<int, std::vector<double>>(key, value));
  }

  ifs.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::PrintGeCaliData()
{
  std::cout << "start read Ge cali data" << std::endl;

  std::map<int, std::vector<double>>::iterator it = map_ge_cali_data.begin();
  for(it=map_ge_cali_data.begin();it!=map_ge_cali_data.end();it++){
    std::cout << it->first << " => " << it->second[0] << " " << it->second[1] << " " << it->second[2] << '\n';
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::ReadSiCaliData()
{
  std::cout << "start read Si cali data" << std::endl;

  std::ifstream ifs;
  ifs.open("si_cali.txt");
  if(!ifs){
    std::cout << "cannot open si_cali.txt." << std::endl;
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
void analysis::PrintSiCaliData()
{
  std::cout << "start read Si cali data" << std::endl;

  std::map<int, std::vector<double>>::iterator it = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    std::cout << it->first << " => " << it->second[0] << " " << it->second[1] << '\n';
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::PrintCloverIDMap()
{
  std::cout << "start read clover id map" << std::endl;

  std::map<int, int>::iterator it = map_clover_modch2id.begin();
  for(it=map_clover_modch2id.begin();it!=map_clover_modch2id.end();it++){
    std::cout << it->first << " => " << it->second << '\n';
  }
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
  int key = 100*mod+ch;

  double energy =  map_ge_cali_data[key][0] + adc*map_ge_cali_data[key][1] + adc*adc*map_ge_cali_data[key][2]*map_ge_cali_data[key][2];

  return energy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double analysis::CaliEnergyWithDoppler(int adc_ge, int mod_ge, int ch_ge, int mod_si_ring, int ch_si_ring, int mod_si_sector, int ch_si_sector)
{
  int key = 100*mod_ge+ch_ge; 
  double energy =  CaliEnergyNoDoppler(adc_ge, mod_ge, ch_ge);
  int ring_id = 16*(mod_si_ring-5) + ch_si_ring;
  int sector_id = 16*(mod_si_sector-7) + ch_si_sector;
  if(key==614){
    sector_id = 23;
  }
  if(key==615){
    sector_id = 31;
  }

  double tmp1 = sin(angle->SITHETA[ring_id])*sin(angle->GETHETADEG[mod_ge][ch_ge]*3.14159/180.)*cos((angle->SIPHIDEG[sector_id]-angle->GEPHIDEG[mod_ge][ch_ge])*3.14159/180.);
  double tmp2 = cos(angle->SITHETADEG[ring_id]*3.14159/180.)*cos(angle->GETHETADEG[mod_ge][ch_ge]*3.14159/180.);
  double energy_doppler = energy*(1-angle->BETA[ring_id]*(tmp1+tmp2))/sqrt(1-angle->BETA[ring_id]*angle->BETA[ring_id]);

  return energy_doppler; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double analysis::NormalizeSi(int adc, int mod, int ch)
{
  int key = 100*mod+ch;

  double adcc = map_si_cali_data[key][0] + adc*map_si_cali_data[key][1];

  return adcc;
}
