#include "analysis.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TH1D.h"

#include "set.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::analysis(const std::string &filename_in, const std::string &filename_out, double phi, double x, double y, double z)
{
  benchmark = new TBenchmark;

  file_in = TFile::Open(filename_in.c_str());
  if(file_in->IsZombie()){
    std::cout << "open file " << filename_in.c_str() << " error!" << std::endl;
    delete file_in;

    return ;
  }
  tr_event = (TTree*)file_in->Get("tr_event");
  tr_bg = (TTree*)file_in->Get("tr_bg");

  file_out = new TFile(filename_out.c_str(), "recreate");
  if(!file_out){
    std::cout << "can not create " << filename_out << std::endl;

    delete file_out;
    return ;
  }

  doppler_event = new doppler(tr_event); 
  doppler_bg = new doppler(tr_bg); 

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

  //PrintCloverIDMap();
  
  //angle info
  angle = new angle_info(phi, x, y, z);
  //angle->PrintAngleInfo();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
analysis::~analysis()
{
  delete file_in;
  delete doppler_event;
  delete doppler_bg;
  delete file_out;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::Process()
{
  benchmark->Start("build");

  ProcessDoppler(doppler_event, "event");
  ProcessDoppler(doppler_bg, "bg");

  benchmark->Show("doppler");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void analysis::ProcessDoppler(doppler *dp, TString info)
{
  file_out->cd();
  TH1D *h_ge_no_doppler_ring1[4], *h_ge_no_doppler_ring2[4], *h_ge_no_doppler_ring4[4], *h_ge_no_doppler_ring5[4];
  TH1D *h_clover_no_doppler_ring3[4*8];
  TH1D *h_ge_doppler_ring1[4], *h_ge_doppler_ring2[4], *h_ge_doppler_ring4[4], *h_ge_doppler_ring5[4];
  TH1D *h_clover_doppler_ring3[4*8];

  TString str_hist;
  str_hist = TString::Format("h_%s_ge_no_doppler_ring1_all", info.Data());
  TH1D *h_ge_no_doppler_ring1_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_ge_doppler_ring1_all", info.Data());
  TH1D *h_ge_doppler_ring1_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

  str_hist = TString::Format("h_%s_ge_no_doppler_ring2_all", info.Data());
  TH1D *h_ge_no_doppler_ring2_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_ge_doppler_ring2_all", info.Data());
  TH1D *h_ge_doppler_ring2_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

  str_hist = TString::Format("h_%s_clover_no_doppler_ring3_all", info.Data());
  TH1D *h_clover_no_doppler_ring3_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_clover_doppler_ring3_all", info.Data());
  TH1D *h_clover_doppler_ring3_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

  str_hist = TString::Format("h_%s_ge_no_doppler_ring4_all", info.Data());
  TH1D *h_ge_no_doppler_ring4_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_ge_doppler_ring4_all", info.Data());
  TH1D *h_ge_doppler_ring4_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

  str_hist = TString::Format("h_%s_ge_no_doppler_ring5_all", info.Data());
  TH1D *h_ge_no_doppler_ring5_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_ge_doppler_ring5_all", info.Data());
  TH1D *h_ge_doppler_ring5_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

  str_hist = TString::Format("h_%s_ge_no_doppler_all", info.Data());
  TH1D *h_ge_no_doppler_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  str_hist = TString::Format("h_%s_ge_doppler_all", info.Data());
  TH1D *h_ge_doppler_all = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);


  //for ring24
  TH1D *h_ge_no_doppler_all_si_ring[24];
  TH1D *h_ge_doppler_all_si_ring[24];
#ifdef SIGLEGEVSSINGLESI
  TH1D *h_ge_no_doppler_ring1_1_si_ring[24], *h_ge_no_doppler_ring1_2_si_ring[24], *h_ge_no_doppler_ring1_3_si_ring[24], *h_ge_no_doppler_ring1_4_si_ring[24];
  TH1D *h_ge_doppler_ring1_1_si_ring[24], *h_ge_doppler_ring1_2_si_ring[24], *h_ge_doppler_ring1_3_si_ring[24], *h_ge_doppler_ring1_4_si_ring[24];
  TH1D *h_ge_no_doppler_ring2_2_si_ring[24], *h_ge_no_doppler_ring2_4_si_ring[24], *h_ge_no_doppler_ring2_6_si_ring[24], *h_ge_no_doppler_ring2_8_si_ring[24];
  TH1D *h_ge_doppler_ring2_2_si_ring[24], *h_ge_doppler_ring2_4_si_ring[24], *h_ge_doppler_ring2_6_si_ring[24], *h_ge_doppler_ring2_8_si_ring[24];
  TH1D *h_ge_no_doppler_ring4_1_si_ring[24], *h_ge_no_doppler_ring4_3_si_ring[24], *h_ge_no_doppler_ring4_5_si_ring[24], *h_ge_no_doppler_ring4_7_si_ring[24];
  TH1D *h_ge_doppler_ring4_1_si_ring[24], *h_ge_doppler_ring4_3_si_ring[24], *h_ge_doppler_ring4_5_si_ring[24], *h_ge_doppler_ring4_7_si_ring[24];
  TH1D *h_ge_no_doppler_ring5_1_si_ring[24], *h_ge_no_doppler_ring5_2_si_ring[24], *h_ge_no_doppler_ring5_3_si_ring[24], *h_ge_no_doppler_ring5_4_si_ring[24];
  TH1D *h_ge_doppler_ring5_1_si_ring[24], *h_ge_doppler_ring5_2_si_ring[24], *h_ge_doppler_ring5_3_si_ring[24], *h_ge_doppler_ring5_4_si_ring[24];
  TH1D *h_ge_no_doppler_ring3_1a_si_ring[24], *h_ge_no_doppler_ring3_1b_si_ring[24], *h_ge_no_doppler_ring3_1c_si_ring[24], *h_ge_no_doppler_ring3_1d_si_ring[24];
  TH1D *h_ge_doppler_ring3_1a_si_ring[24], *h_ge_doppler_ring3_1b_si_ring[24], *h_ge_doppler_ring3_1c_si_ring[24], *h_ge_doppler_ring3_1d_si_ring[24];
#endif

  for(int i=0;i<24;i++){
    //all
    str_hist = TString::Format("h_%s_ge_no_doppler_all_si_ring%d", info.Data(), i);
    h_ge_no_doppler_all_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_all_si_ring%d", info.Data(), i);
    h_ge_doppler_all_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    
#ifdef SIGLEGEVSSINGLESI
    //ring1
    str_hist = TString::Format("h_%s_ge_no_doppler_ring1_1_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring1_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring1_1_si_ring%d", info.Data(), i);
    h_ge_doppler_ring1_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring1_2_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring1_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring1_2_si_ring%d", info.Data(), i);
    h_ge_doppler_ring1_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring1_3_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring1_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring1_3_si_ring%d", info.Data(), i);
    h_ge_doppler_ring1_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring1_4_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring1_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring1_4_si_ring%d", info.Data(), i);
    h_ge_doppler_ring1_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    //ring2
    str_hist = TString::Format("h_%s_ge_no_doppler_ring2_2_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring2_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring2_2_si_ring%d", info.Data(), i);
    h_ge_doppler_ring2_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring2_4_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring2_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring2_4_si_ring%d", info.Data(), i);
    h_ge_doppler_ring2_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring2_6_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring2_6_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring2_6_si_ring%d", info.Data(), i);
    h_ge_doppler_ring2_6_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring2_8_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring2_8_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring2_8_si_ring%d", info.Data(), i);
    h_ge_doppler_ring2_8_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    //ring4
    str_hist = TString::Format("h_%s_ge_no_doppler_ring4_1_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring4_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring4_1_si_ring%d", info.Data(), i);
    h_ge_doppler_ring4_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring4_3_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring4_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring4_3_si_ring%d", info.Data(), i);
    h_ge_doppler_ring4_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring4_5_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring4_5_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring4_5_si_ring%d", info.Data(), i);
    h_ge_doppler_ring4_5_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring4_7_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring4_7_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring4_7_si_ring%d", info.Data(), i);
    h_ge_doppler_ring4_7_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    //ring5
    str_hist = TString::Format("h_%s_ge_no_doppler_ring5_1_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring5_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring5_1_si_ring%d", info.Data(), i);
    h_ge_doppler_ring5_1_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring5_2_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring5_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring5_2_si_ring%d", info.Data(), i);
    h_ge_doppler_ring5_2_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring5_3_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring5_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring5_3_si_ring%d", info.Data(), i);
    h_ge_doppler_ring5_3_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring5_4_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring5_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring5_4_si_ring%d", info.Data(), i);
    h_ge_doppler_ring5_4_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    //ring3
    str_hist = TString::Format("h_%s_ge_no_doppler_ring3_1a_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring3_1a_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring3_1a_si_ring%d", info.Data(), i);
    h_ge_doppler_ring3_1a_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring3_1b_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring3_1b_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring3_1b_si_ring%d", info.Data(), i);
    h_ge_doppler_ring3_1b_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring3_1c_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring3_1c_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring3_1c_si_ring%d", info.Data(), i);
    h_ge_doppler_ring3_1c_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  
    str_hist = TString::Format("h_%s_ge_no_doppler_ring3_1d_si_ring%d", info.Data(), i);
    h_ge_no_doppler_ring3_1d_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring3_1d_si_ring%d", info.Data(), i);
    h_ge_doppler_ring3_1d_si_ring[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
#endif
  }

  //for sector32
  TH1D *h_ge_no_doppler_all_si_sector[32];
  TH1D *h_ge_doppler_all_si_sector[32];

#ifdef SIGLEGEVSSINGLESI
  TH1D *h_ge_no_doppler_ring1_si_sector[4*32], *h_ge_doppler_ring1_si_sector[4*32];
  TH1D *h_ge_no_doppler_ring2_si_sector[4*32], *h_ge_doppler_ring2_si_sector[4*32];
  TH1D *h_clover_no_doppler_ring3_1_si_sector[4*32], *h_clover_doppler_ring3_1_si_sector[4*32];
  TH1D *h_clover_no_doppler_ring3_6_si_sector[4*32], *h_clover_doppler_ring3_6_si_sector[4*32];
  TH1D *h_ge_no_doppler_ring4_si_sector[4*32], *h_ge_doppler_ring4_si_sector[4*32];
  TH1D *h_ge_no_doppler_ring5_si_sector[4*32], *h_ge_doppler_ring5_si_sector[4*32];
#endif

  for(int i=0;i<32;i++){
    //all
    str_hist = TString::Format("h_%s_ge_no_doppler_all_si_sector%d", info.Data(), i);
    h_ge_no_doppler_all_si_sector[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_all_si_sector%d", info.Data(), i);
    h_ge_doppler_all_si_sector[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  }  

#ifdef SIGLEGEVSSINGLESI
  for(int i=0;i<4;i++){
    for(int j=0;j<32;j++){
      str_hist = TString::Format("h_%s_ge_no_doppler_ring1_%d_si_sector%d", info.Data(), i+1, j);
      h_ge_no_doppler_ring1_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_ge_doppler_ring1_%d_si_sector%d", info.Data(), i+1, j);
      h_ge_doppler_ring1_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

      str_hist = TString::Format("h_%s_ge_no_doppler_ring2_%d_si_sector%d", info.Data(), 2*(i+1), j);
      h_ge_no_doppler_ring2_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_ge_doppler_ring2_%d_si_sector%d", info.Data(), 2*(i+1), j);
      h_ge_doppler_ring2_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

      str_hist = TString::Format("h_%s_clover_no_doppler_ring3_1_%c_si_sector%d", info.Data(), (char)(97+i), j);
      h_clover_no_doppler_ring3_1_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_clover_doppler_ring3_1_%c_si_sector%d", info.Data(), (char)(97+i), j);
      h_clover_doppler_ring3_1_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

      str_hist = TString::Format("h_%s_clover_no_doppler_ring3_6_%c_si_sector%d", info.Data(), (char)(97+i), j);
      h_clover_no_doppler_ring3_6_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_clover_doppler_ring3_6_%c_si_sector%d", info.Data(), (char)(97+i), j);
      h_clover_doppler_ring3_6_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

      str_hist = TString::Format("h_%s_ge_no_doppler_ring4_%d_si_sector%d", info.Data(), 2*i+1, j);
      h_ge_no_doppler_ring4_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_ge_doppler_ring4_%d_si_sector%d", info.Data(), 2*i+1, j);
      h_ge_doppler_ring4_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

      str_hist = TString::Format("h_%s_ge_no_doppler_ring5_%d_si_sector%d", info.Data(), i+1, j);
      h_ge_no_doppler_ring5_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
      str_hist = TString::Format("h_%s_ge_doppler_ring5_%d_si_sector%d", info.Data(), i+1, j);
      h_ge_doppler_ring5_si_sector[32*i+j] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    }
  }
#endif

  //
  for(int i=0;i<4;i++){
    str_hist = TString::Format("h_%s_ge_no_doppler_ring1_%d", info.Data(), i+1);
    h_ge_no_doppler_ring1[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_no_doppler_ring2_%d", info.Data(), 2*(i+1));
    h_ge_no_doppler_ring2[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_no_doppler_ring4_%d", info.Data(), 2*i+1);
    h_ge_no_doppler_ring4[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_no_doppler_ring5_%d", info.Data(), i+1);
    h_ge_no_doppler_ring5[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    str_hist = TString::Format("h_%s_ge_doppler_ring1_%d", info.Data(), i+1);
    h_ge_doppler_ring1[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring2_%d", info.Data(), 2*(i+1));
    h_ge_doppler_ring2[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring4_%d", info.Data(), 2*i+1);
    h_ge_doppler_ring4[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
    str_hist = TString::Format("h_%s_ge_doppler_ring5_%d", info.Data(), i+1);
    h_ge_doppler_ring5[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  }

  for(int i=0;i<32;i++){
    str_hist = TString::Format("h_%s_clover_no_doppler_ring3_%d_%c", info.Data(), i/4+1, (char)(97+i%4));
    h_clover_no_doppler_ring3[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);

    str_hist = TString::Format("h_%s_clover_doppler_ring3_%d_%c", info.Data(), i/4+1, (char)(97+i%4));
    h_clover_doppler_ring3[i] = new TH1D(str_hist.Data(), str_hist.Data(), BINNUMBER, 0, 4096);
  }

  //
  bool valid_event = 0;
  for(Long64_t i=0;i<dp->GetEntries();++i){
    if(i%10000==0){ 
      std::cout << "\r" << i << "/" << dp->GetEntries();
      std::cout << std::flush;
    }

    valid_event = 0;
    dp->GetEntry(i);

    if(dp->n_Si_ring==1 && dp->n_Si_sector==1){
      if(dp->Si_ring_adc[0]>CUTSIADC && dp->Si_sector_adc[0]>CUTSIADC && abs(dp->Si_ring_adc[0]-dp->Si_sector_adc[0])<CUTSIDIFF){
        valid_event = 1;
      }
    }
    if(dp->n_Si_ring==2 && dp->n_Si_sector==1){
      double m = (dp->Si_ring_adc[0]>dp->Si_ring_adc[1]) ? dp->Si_ring_adc[0] : dp->Si_ring_adc[1];
      if(m==dp->Si_ring_adc[1]){
        dp->Si_ring_id[0] = dp->Si_ring_id[1]; 
      }
      if(m>CUTSIADC && dp->Si_sector_adc[0]>CUTSIADC && abs(m-dp->Si_sector_adc[0])<CUTSIDIFF){
        valid_event = 1;
      }
    }
    if(dp->n_Si_ring==1 && dp->n_Si_sector==2){
      double m = (dp->Si_sector_adc[0]>dp->Si_sector_adc[1]) ? dp->Si_sector_adc[0] : dp->Si_sector_adc[1];
      if(m==dp->Si_sector_adc[1]){
        dp->Si_sector_id[0] = dp->Si_sector_id[1]; 
      }
      if(dp->Si_ring_adc[0]>CUTSIADC && m>CUTSIADC && abs(dp->Si_ring_adc[0]-m)<CUTSIDIFF){
        valid_event = 1;
      }
    }
    if(dp->n_Si_ring==1 && dp->n_Si_sector==2){
      double m1 = (dp->Si_ring_adc[0]>dp->Si_ring_adc[1]) ? dp->Si_ring_adc[0] : dp->Si_ring_adc[1];
      double m2 = (dp->Si_sector_adc[0]>dp->Si_sector_adc[1]) ? dp->Si_sector_adc[0] : dp->Si_sector_adc[1];

      if(m1==dp->Si_ring_adc[1]){
        dp->Si_ring_id[0] = dp->Si_ring_id[1]; 
      }
      if(m2==dp->Si_sector_adc[1]){
        dp->Si_sector_id[0] = dp->Si_sector_id[1]; 
      }

      if(m1>CUTSIADC && m2>CUTSIADC && abs(m1-m2)<CUTSIDIFF){
        valid_event = 1;
      }
    }

    //
    if(valid_event){//////
      for(int j=0;j<dp->n_Ge;j++){
        double energy_no_doppler = dp->Ge_energy[j];
        // double energy_doppler = CaliEnergyWithDoppler(dp->Ge_energy[j], dp->Ge_mod[j], dp->Ge_ch[j], dp->Si_ring_id[0], dp->Si_sector_id[0]);
        double energy_doppler = CaliEnergyWithDopplerNew(dp->Ge_energy[j], dp->Ge_mod[j], dp->Ge_ch[j], dp->Si_ring_id[0], dp->Si_sector_id[0]);
        //std::cout << i << " ==> " << dp->Ge_mod[j] << " " << dp->Ge_ch[j] << " " << energy_no_doppler << " " << energy_doppler << std::endl;
        if(energy_no_doppler < CUTGEENERGY)  continue;
        h_ge_no_doppler_all->Fill(energy_no_doppler);
        h_ge_doppler_all->Fill(energy_doppler);

        int ring_idd = dp->Si_ring_id[0];
        int sector_idd = dp->Si_sector_id[0];
        //std::cout << " ring_idd " << ring_idd << std::endl;
        //std::cout << " sector_idd " << sector_idd << std::endl;

        //for si ring
        h_ge_no_doppler_all_si_ring[ring_idd]->Fill(energy_no_doppler);
        h_ge_doppler_all_si_ring[ring_idd]->Fill(energy_doppler);
        //for si sector
        h_ge_no_doppler_all_si_sector[sector_idd]->Fill(energy_no_doppler);
        h_ge_doppler_all_si_sector[sector_idd]->Fill(energy_doppler);

        if(dp->Ge_mod[j] == 0){//ring1 & ring2
          if(dp->Ge_ch[j] < 4){
            h_ge_no_doppler_ring1_all->Fill(energy_no_doppler);
            h_ge_doppler_ring1_all->Fill(energy_doppler);
            h_ge_no_doppler_ring1[dp->Ge_ch[j]]->Fill(energy_no_doppler);
            h_ge_doppler_ring1[dp->Ge_ch[j]]->Fill(energy_doppler);

#ifdef SIGLEGEVSSINGLESI
            //for si ring
            if(dp->Ge_ch[j] == 0){
              h_ge_no_doppler_ring1_1_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring1_1_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 1){
              h_ge_no_doppler_ring1_2_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring1_2_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 2){
              h_ge_no_doppler_ring1_3_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring1_3_si_ring[ring_idd]->Fill(energy_doppler);
            }else{
              h_ge_no_doppler_ring1_4_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring1_4_si_ring[ring_idd]->Fill(energy_doppler);
            }
            //for si sector
            h_ge_no_doppler_ring1_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring1_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_doppler);
#endif
          }
          else{
            h_ge_no_doppler_ring2_all->Fill(energy_no_doppler);
            h_ge_doppler_ring2_all->Fill(energy_doppler);
            h_ge_no_doppler_ring2[dp->Ge_ch[j]-4]->Fill(energy_no_doppler);
            h_ge_doppler_ring2[dp->Ge_ch[j]-4]->Fill(energy_doppler);

#ifdef SIGLEGEVSSINGLESI
            //for si ring
            if(dp->Ge_ch[j] == 4){
              h_ge_no_doppler_ring2_2_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring2_2_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 5){
              h_ge_no_doppler_ring2_4_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring2_4_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 6){
              h_ge_no_doppler_ring2_6_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring2_6_si_ring[ring_idd]->Fill(energy_doppler);
            }else{
              h_ge_no_doppler_ring2_8_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring2_8_si_ring[ring_idd]->Fill(energy_doppler);
            }
            //for si sector
            h_ge_no_doppler_ring2_si_sector[32*(dp->Ge_ch[j]-4)+sector_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring2_si_sector[32*(dp->Ge_ch[j]-4)+sector_idd]->Fill(energy_doppler);
#endif
          }
        }
        else if(dp->Ge_mod[j] == 1){//ring 4 & ring5
          if(dp->Ge_ch[j] < 4){
            h_ge_no_doppler_ring4_all->Fill(energy_no_doppler);
            h_ge_doppler_ring4_all->Fill(energy_doppler);
            h_ge_no_doppler_ring4[dp->Ge_ch[j]]->Fill(energy_no_doppler);
            h_ge_doppler_ring4[dp->Ge_ch[j]]->Fill(energy_doppler);

#ifdef SIGLEGEVSSINGLESI
            //for si ring
            if(dp->Ge_ch[j] == 0){
              h_ge_no_doppler_ring4_1_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring4_1_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 1){
              h_ge_no_doppler_ring4_3_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring4_3_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 2){
              h_ge_no_doppler_ring4_5_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring4_7_si_ring[ring_idd]->Fill(energy_doppler);
            }else{
              h_ge_no_doppler_ring1_4_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring1_4_si_ring[ring_idd]->Fill(energy_doppler);
            }

            //for si sector
            h_ge_no_doppler_ring4_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring4_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_doppler);
#endif
          }
          else{
            h_ge_no_doppler_ring5_all->Fill(energy_no_doppler);
            h_ge_doppler_ring5_all->Fill(energy_doppler);
            h_ge_no_doppler_ring5[dp->Ge_ch[j]-4]->Fill(energy_no_doppler);
            h_ge_doppler_ring5[dp->Ge_ch[j]-4]->Fill(energy_doppler);

#ifdef SIGLEGEVSSINGLESI
            //for si ring
            if(dp->Ge_ch[j] == 4){
              h_ge_no_doppler_ring5_1_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring5_1_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 5){
              h_ge_no_doppler_ring5_2_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring5_2_si_ring[ring_idd]->Fill(energy_doppler);
            }else if(dp->Ge_ch[j] == 6){
              h_ge_no_doppler_ring5_3_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring5_3_si_ring[ring_idd]->Fill(energy_doppler);
            }else{
              h_ge_no_doppler_ring5_4_si_ring[ring_idd]->Fill(energy_no_doppler);
              h_ge_doppler_ring5_4_si_ring[ring_idd]->Fill(energy_doppler);
            }

            //for si sector
            h_ge_no_doppler_ring5_si_sector[32*(dp->Ge_ch[j]-4)+sector_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring5_si_sector[32*(dp->Ge_ch[j]-4)+sector_idd]->Fill(energy_doppler);
#endif
          }
        }else{//ring3, mod 2, 3, 4
          h_clover_no_doppler_ring3_all->Fill(energy_no_doppler);
          h_clover_doppler_ring3_all->Fill(energy_doppler);
          int key = 100*dp->Ge_mod[j]+dp->Ge_ch[j];
          h_clover_no_doppler_ring3[map_clover_modch2id[key]]->Fill(energy_no_doppler);
          h_clover_doppler_ring3[map_clover_modch2id[key]]->Fill(energy_doppler);

#ifdef SIGLEGEVSSINGLESI
          //for si ring
          if(key == 200){
            h_ge_no_doppler_ring3_1a_si_ring[ring_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring3_1a_si_ring[ring_idd]->Fill(energy_doppler);
          }
          if(key == 201){
            h_ge_no_doppler_ring3_1b_si_ring[ring_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring3_1b_si_ring[ring_idd]->Fill(energy_doppler);
          }
          if(key == 202){
            h_ge_no_doppler_ring3_1c_si_ring[ring_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring3_1c_si_ring[ring_idd]->Fill(energy_doppler);
          }
          if(key == 203){
            h_ge_no_doppler_ring3_1d_si_ring[ring_idd]->Fill(energy_no_doppler);
            h_ge_doppler_ring3_1d_si_ring[ring_idd]->Fill(energy_doppler);
          }

          //for si sector
          if(key>=200 && key<=203){
            h_clover_no_doppler_ring3_1_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_no_doppler);
            h_clover_doppler_ring3_1_si_sector[32*dp->Ge_ch[j]+sector_idd]->Fill(energy_doppler);
          }

          if(key>=308 && key<=311){
            h_clover_no_doppler_ring3_6_si_sector[32*(dp->Ge_ch[j]-8)+sector_idd]->Fill(energy_no_doppler);
            h_clover_doppler_ring3_6_si_sector[32*(dp->Ge_ch[j]-8)+sector_idd]->Fill(energy_doppler);
          }
#endif
        }
      }
    }
  }
  std::cout << std::endl;

  //write
  file_out->cd();
  h_ge_no_doppler_all->Write();
  h_ge_doppler_all->Write();

  for(int i=0;i<24;i++){
    h_ge_no_doppler_all_si_ring[i]->Write();
    h_ge_doppler_all_si_ring[i]->Write();
  }

  for(int i=0;i<32;i++){
    h_ge_no_doppler_all_si_sector[i]->Write();
    h_ge_doppler_all_si_sector[i]->Write();
  }

#ifdef SIGLEGEVSSINGLESI
  TDirectory *dir_ge[5];//5 rings
  TString str_dir_name;
  for(int i=0;i<5;i++){
    if(i==2){//ring3
      str_dir_name.Clear();
      str_dir_name = TString::Format("%s_clover_ring%d", info.Data(), i+1);
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

      for(int j=0;j<24;j++){
        h_ge_no_doppler_ring3_1a_si_ring[j]->Write();
        h_ge_doppler_ring3_1a_si_ring[j]->Write();
        h_ge_no_doppler_ring3_1b_si_ring[j]->Write();
        h_ge_doppler_ring3_1b_si_ring[j]->Write();
        h_ge_no_doppler_ring3_1c_si_ring[j]->Write();
        h_ge_doppler_ring3_1c_si_ring[j]->Write();
        h_ge_no_doppler_ring3_1d_si_ring[j]->Write();
        h_ge_doppler_ring3_1d_si_ring[j]->Write();
      }
      for(int m=0;m<4;m++){
        for(int n=0;n<32;n++){
          h_clover_no_doppler_ring3_1_si_sector[32*m+n]->Write();
          h_clover_doppler_ring3_1_si_sector[32*m+n]->Write();

          h_clover_no_doppler_ring3_6_si_sector[32*m+n]->Write();
          h_clover_doppler_ring3_6_si_sector[32*m+n]->Write();
        }
      }

    }
    else{
      str_dir_name.Clear();
      str_dir_name = TString::Format("%s_ge_ring%d", info.Data(), i+1);
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
        for(int j=0;j<24;j++){
          h_ge_no_doppler_ring1_1_si_ring[j]->Write();
          h_ge_doppler_ring1_1_si_ring[j]->Write();
          h_ge_no_doppler_ring1_2_si_ring[j]->Write();
          h_ge_doppler_ring1_2_si_ring[j]->Write();
          h_ge_no_doppler_ring1_3_si_ring[j]->Write();
          h_ge_doppler_ring1_3_si_ring[j]->Write();
          h_ge_no_doppler_ring1_4_si_ring[j]->Write();
          h_ge_doppler_ring1_4_si_ring[j]->Write();
        }
        for(int m=0;m<4;m++){
          for(int n=0;n<32;n++){
            h_ge_no_doppler_ring1_si_sector[32*m+n]->Write();
            h_ge_doppler_ring1_si_sector[32*m+n]->Write();
          }
        }
      }
      if(i==1){//ring2
        h_ge_no_doppler_ring2_all->Write();
        h_ge_doppler_ring2_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring2[j]->Write();
          h_ge_doppler_ring2[j]->Write();
        }
        for(int j=0;j<24;j++){
          h_ge_no_doppler_ring2_2_si_ring[j]->Write();
          h_ge_doppler_ring2_2_si_ring[j]->Write();
          h_ge_no_doppler_ring2_4_si_ring[j]->Write();
          h_ge_doppler_ring2_4_si_ring[j]->Write();
          h_ge_no_doppler_ring2_6_si_ring[j]->Write();
          h_ge_doppler_ring2_6_si_ring[j]->Write();
          h_ge_no_doppler_ring2_8_si_ring[j]->Write();
          h_ge_doppler_ring2_8_si_ring[j]->Write();
        }
        for(int m=0;m<4;m++){
          for(int n=0;n<32;n++){
            h_ge_no_doppler_ring2_si_sector[32*m+n]->Write();
            h_ge_doppler_ring2_si_sector[32*m+n]->Write();
          }
        }
      }
      if(i==3){//ring4
        h_ge_no_doppler_ring4_all->Write();
        h_ge_doppler_ring4_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring4[j]->Write();
          h_ge_doppler_ring4[j]->Write();
        }
        for(int j=0;j<24;j++){
          h_ge_no_doppler_ring4_1_si_ring[j]->Write();
          h_ge_doppler_ring4_1_si_ring[j]->Write();
          h_ge_no_doppler_ring4_3_si_ring[j]->Write();
          h_ge_doppler_ring4_3_si_ring[j]->Write();
          h_ge_no_doppler_ring4_5_si_ring[j]->Write();
          h_ge_doppler_ring4_5_si_ring[j]->Write();
          h_ge_no_doppler_ring4_7_si_ring[j]->Write();
          h_ge_doppler_ring4_7_si_ring[j]->Write();
        }
        for(int m=0;m<4;m++){
          for(int n=0;n<32;n++){
            h_ge_no_doppler_ring4_si_sector[32*m+n]->Write();
            h_ge_doppler_ring4_si_sector[32*m+n]->Write();
          }
        }
      }
      if(i==4){//ring5
        h_ge_no_doppler_ring5_all->Write();
        h_ge_doppler_ring5_all->Write();
        for(int j=0;j<4;j++){
          h_ge_no_doppler_ring5[j]->Write();
          h_ge_doppler_ring5[j]->Write();
        }
        for(int j=0;j<24;j++){
          h_ge_no_doppler_ring5_1_si_ring[j]->Write();
          h_ge_doppler_ring5_1_si_ring[j]->Write();
          h_ge_no_doppler_ring5_2_si_ring[j]->Write();
          h_ge_doppler_ring5_2_si_ring[j]->Write();
          h_ge_no_doppler_ring5_3_si_ring[j]->Write();
          h_ge_doppler_ring5_3_si_ring[j]->Write();
          h_ge_no_doppler_ring5_4_si_ring[j]->Write();
          h_ge_doppler_ring5_4_si_ring[j]->Write();
        }
        for(int m=0;m<4;m++){
          for(int n=0;n<32;n++){
            h_ge_no_doppler_ring5_si_sector[32*m+n]->Write();
            h_ge_doppler_ring5_si_sector[32*m+n]->Write();
          }
        }
      }
    }
  }
#endif
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
double analysis::CaliEnergyWithDoppler(int adc_ge, int mod_ge, int ch_ge, int si_ring_id, int si_sector_id)
{
  double tmp1 = sin(angle->GetSiTheta(si_ring_id))*sin(angle->GetGeTheta(mod_ge, ch_ge))*cos(angle->GetSiPhi(si_sector_id)-angle->GetGePhi(mod_ge, ch_ge));
  double tmp2 = cos(angle->GetSiTheta(si_ring_id))*cos(angle->GetGeTheta(mod_ge, ch_ge));

  //std::cout << "old ... " << tmp1+tmp2 << " si " << angle->GetSiTheta(si_ring_id) << " " << angle->GetSiPhi(si_sector_id) << " ge " << angle->GetGeTheta(mod_ge, ch_ge) << " " << angle->GetGePhi(mod_ge, ch_ge) << std::endl;
  double energy_doppler = adc_ge*(1-angle->GetBeta(si_ring_id)*(tmp1+tmp2))/sqrt(1-angle->GetBeta(si_ring_id)*angle->GetBeta(si_ring_id));

  return energy_doppler;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double analysis::CaliEnergyWithDopplerNew(int adc_ge, int mod_ge, int ch_ge, int si_ring_id, int si_sector_id)
{
  //std::cout << "new ... " << angle->GetCosThetaParticleGamma(mod_ge, ch_ge, si_ring_id, si_sector_id) << " si " << angle->GetSiTheta(si_ring_id) << " " << angle->GetSiPhi(si_sector_id) << " ge " << angle->GetGeTheta(mod_ge, ch_ge) << " " << angle->GetGePhi(mod_ge, ch_ge) << std::endl;
  double energy_doppler = adc_ge*(1-angle->GetBeta(si_ring_id)*angle->GetCosThetaParticleGamma(mod_ge, ch_ge, si_ring_id, si_sector_id))/sqrt(1-angle->GetBeta(si_ring_id)*angle->GetBeta(si_ring_id));

  return energy_doppler; 
}

