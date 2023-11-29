#include "analysis.h"

#include <vector>
#include "math.h"

//
analysis::analysis(const std::string &filename_in, const std::string &filename_out)
{
  benchmark = new TBenchmark;

  file_in = TFile::Open(filename_in.c_str());
  for(int i=0;i<9;i++){
    for(int j=0;j<16;j++){
      tr[16*i+j] = (TTree*)file_in->Get(TString::Format("tr_XIA_%02d_%02d",i,j).Data());
      if(!tr[16*i+j]){
        continue;
      }
      tr[16*i+j]->SetBranchAddress("channel", &ch);
      tr[16*i+j]->SetBranchAddress("Energy", &energy);
      tr[16*i+j]->SetBranchAddress("Event_ts", &ts);
    }
  }

  ch = 0;
  energy = 0;
  ts = 0;

  file_out = TFile::Open(filename_out.c_str(), "recreate");

  // time differents with the first Ge detector mod0ch00
  for(int i=0;i<5;i++){
    for(int j=0;j<16;j++){
      h1[i*16+j] = new TH1D(TString::Format("mod%d_ch%02d_vs_mod0_ch00",i,j).Data(), "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
    }
  }
  // time differents between Si ring and Si sector
  for(int i=0;i<24;i++){
    for(int j=0;j<32;j++){
      h2[i*32+j] = new TH1D(TString::Format("Si_ring%02d_vs_Si_sector%02d",i,j).Data(), "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
    }
  }
  // time differents between Ge and Si sector
  for(int i=0;i<56;i++){
    if(i<24)
      h3[i] = new TH1D(TString::Format("Si_ring%02d_vs_mod0_ch00",i).Data(), "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
    else
      h3[i] = new TH1D(TString::Format("Si_sector%02d_vs_mod0_ch00",i-24).Data(), "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  }
}

//
analysis::~analysis()
{
  file_in->Close();
  file_out->Close();
}

//
void analysis::GetTimestampVector(TTree *tr, UShort_t e_cut, std::vector<Long64_t> &vec)
{
  vec.clear();

  for(Long64_t i=0;i<tr->GetEntries();i++){
    tr->GetEntry(i);
    if(energy < e_cut) continue;
    vec.push_back(ts);
  }
}


//
void analysis::ProcessGevsGe()
{
  std::vector<Long64_t> v1;
  std::vector<Long64_t> v2;
  
  v1.clear();
  v2.clear();

  Long64_t ts1, ts2;
  Long64_t j = 0;
  Long64_t k = 0;

  //Ge vs. Ge
  std::cout << "Ge vs. Ge" << std::endl;
  GetTimestampVector(tr[0], CUTGE, v1);
  for(int i=0;i<5*16;i++){
    std::cout << i << std::endl;
    v2.clear();
    j = 0;
    k = 0;

    if(!tr[i]) continue;
    GetTimestampVector(tr[i], CUTGE, v2);
    while(true){
      if(j==(Long64_t)v1.size() || k==(Long64_t)v2.size())  break;
      ts1 = v1[j];
      while(true){
        if(k==(Long64_t)v2.size())  break;
        ts2 = v2[k];
        if(abs(ts1-ts2)<ALIGNMENTWINDOW){
          h1[i]->Fill(ts1-ts2);
          k++;
        }
        else if((ts1-ts2)>ALIGNMENTWINDOW){
          k++;
        }
        else{
          j++;
          break;
        }
      }
    }
  }

  
  file_out->cd();
  for(int i=0;i<5*16;i++){
    h1[i]->Write();
  }
}

//
void analysis::ProcessSiRingvsSiSector()
{
  std::vector<Long64_t> v1;
  std::vector<Long64_t> v2;
  
  v1.clear();
  v2.clear();

  Long64_t ts1, ts2;
  Long64_t j = 0;
  Long64_t k = 0;

  //Si ring vs. Si sector
  std::cout << "Si ring vs. Si sector" << std::endl;
  for(int m=0;m<24;m++){
    GetTimestampVector(tr[5*16+m], CUTSI, v1);
    for(int n=0;n<32;n++){
      std::cout << m*32+n << std::endl;
      v2.clear();
      j = 0;
      k = 0;
      
      GetTimestampVector(tr[7*16+n], CUTSI, v2);
      if(n==23){
        v2.clear();
        GetTimestampVector(tr[6*16+14], CUTSI, v2);
      }
      if(n==31){
        v2.clear();
        GetTimestampVector(tr[6*16+15], CUTSI, v2);
      }
  
      while(true){
        if(j==(Long64_t)v1.size() || k==(Long64_t)v2.size())  break;
        ts1 = v1[j];
        while(true){
          if(k==(Long64_t)v2.size())  break;
          ts2 = v2[k];
          if(abs(ts1-ts2)<ALIGNMENTWINDOW){
            h2[m*32+n]->Fill(ts1-ts2);
            k++;
          }
          else if((ts1-ts2)>ALIGNMENTWINDOW){
            k++;
          }
          else{
            j++;
            break;
          }
        }
      }
    }
  }
  
  file_out->cd();
  for(int i=0;i<24;i++){
    for(int j=0;j<32;j++){
      h2[32*i+j]->Write();
    }
  }
}

//
void analysis::ProcessGevsSi()
{
  std::vector<Long64_t> v1;
  std::vector<Long64_t> v2;
  
  v1.clear();
  v2.clear();

  Long64_t ts1, ts2;
  Long64_t j = 0;
  Long64_t k = 0;

  //Ge vs. Si
  std::cout << "Ge vs. Si" << std::endl;
  GetTimestampVector(tr[0], CUTGE, v1);
  for(int i=0;i<24;i++){
    std::cout << i << std::endl;
    v2.clear();
    j = 0;
    k = 0;

    if(!tr[i]) continue;

    GetTimestampVector(tr[5*16+i], CUTSI, v2); 
    while(true){
      if(j==(Long64_t)v1.size() || k==(Long64_t)v2.size())  break;
      ts1 = v1[j];
      while(true){
        if(k==(Long64_t)v2.size())  break;
        ts2 = v2[k];
        if(abs(ts1-ts2)<ALIGNMENTWINDOW){
          h3[i]->Fill(ts1-ts2);
          k++;
        }
        else if((ts1-ts2)>ALIGNMENTWINDOW){
          k++;
        }
        else{
          j++;
          break;
        }
      }
    }
  }

  for(int i=0;i<32;i++){
    std::cout << i << std::endl;
    v2.clear();
    j = 0;
    k = 0;

    if(!tr[i]) continue;

    GetTimestampVector(tr[7*16+i], CUTSI, v2);
    if(i==23){
      v2.clear();
      GetTimestampVector(tr[6*16+14], CUTSI, v2);
    }
    if(i==31){
      v2.clear();
      GetTimestampVector(tr[6*16+15], CUTSI, v2);
    }
    while(true){
      if(j==(Long64_t)v1.size() || k==(Long64_t)v2.size())  break;
      ts1 = v1[j];
      while(true){
        if(k==(Long64_t)v2.size())  break;
        ts2 = v2[k];
        if(abs(ts1-ts2)<ALIGNMENTWINDOW){
          h3[i+24]->Fill(ts1-ts2);
          k++;
        }
        else if((ts1-ts2)>ALIGNMENTWINDOW){
          k++;
        }
        else{
          j++;
          break;
        }
      }
    }
  }
  file_out->cd();
  for(int i=0;i<56;i++){
    h3[i]->Write();
  }
}
