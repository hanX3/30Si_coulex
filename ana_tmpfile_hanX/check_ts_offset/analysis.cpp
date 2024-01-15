#include "analysis.h"

#include <vector>
#include "math.h"

//
analysis::analysis(const std::string &filename_in, const std::string &filename_out)
{
  benchmark = new TBenchmark;

  rndm = new TRandom3((Long64_t)time(0));

  file_in = TFile::Open(filename_in.c_str());
  tr = (TTree*)file_in->Get("tree");
  tr->SetBranchAddress("mod", &mod);
  tr->SetBranchAddress("ch", &ch);
  tr->SetBranchAddress("energy", &energy);
  tr->SetBranchAddress("ts", &ts);

  mod = 0;
  ch = 0;
  energy = 0;
  ts = 0;

  v_data.clear();

  file_out = TFile::Open(filename_out.c_str(), "recreate");

  h_ts = new TH1D("h_ts", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_ge_ts = new TH1D("h_ge_ts", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_si_ts = new TH1D("h_si_ts", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_ge_si_ts = new TH1D("h_ge_si_ts", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);

  h_ts2 = new TH1D("h_ts2", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_ge_ts2 = new TH1D("h_ge_ts2", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_si_ts2 = new TH1D("h_si_ts2", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
  h_ge_si_ts2 = new TH1D("h_ge_si_ts2", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
}

//
analysis::~analysis()
{
  file_in->Close();
  file_out->Close();
}

//
void analysis::Process()
{
  Long64_t ts1, ts2;
  ts1 = 0;
  ts2 = 0;

  for(Long64_t i=0;i<tr->GetEntries();i++){
    tr->GetEntry(i);

    if(v_data.size()==0){
      xd.mod = mod;
      xd.ch = ch;
      xd.energy = energy;
      xd.ts = ts;
      v_data.push_back(xd);  
      
      ts1 = ts;
      continue;
    }

    ts2 = ts;
    if(abs(ts1-ts2)<ALIGNMENTWINDOW){
      xd.mod = mod;
      xd.ch = ch;
      xd.energy = energy;
      xd.ts = ts;
      v_data.push_back(xd);  
    }else{
      // std::cout << "v_size " << v_data.size() << std::endl;
      if(v_data.size()==1){
        v_data.clear();  
      }else{
        Vector2Hist();
        v_data.clear();
      }
    }
  }

  file_out->cd();

  h_ts->Write();
  h_ge_ts->Write();
  h_si_ts->Write();
  h_ge_si_ts->Write();

  h_ts2->Write();
  h_ge_ts2->Write();
  h_si_ts2->Write();
  h_ge_si_ts2->Write();
}

//
void analysis::Vector2Hist()
{
  int n = v_data.size();

  std::vector<xia_data> v_xd_ge;
  for(int i=0;i<n;i++){
    if(v_data[i].mod<5){
      v_xd_ge.push_back(v_data[i]);
    }
  }

  std::vector<xia_data> v_xd_si;
  for(int i=0;i<n;i++){
    if(v_data[i].mod>4){
      v_xd_si.push_back(v_data[i]);
    }
  }

  int n_ge = v_xd_ge.size();
  int n_si = v_xd_si.size();

  // std::cout << "n_ge " << n_ge << std::endl;
  // std::cout << "n_si " << n_si << std::endl;

  // h_all
  for(int i=0;i<(n-1);i++){
    for(int j=1;j<n;j++){
      if(rndm->Uniform()>0.5){
        h_ts->Fill(v_data[i].ts-v_data[j].ts);
      }else{
        h_ts->Fill(v_data[j].ts-v_data[i].ts);
      }
    }
  }

  // h_ge_ts
  if(n_ge>1){
    for(int i=0;i<(n_ge-1);i++){
      for(int j=1;j<n_ge;j++){
        if(rndm->Uniform()>0.5){
          h_ge_ts->Fill(v_xd_ge[i].ts-v_xd_ge[j].ts);
        }else{
          h_ge_ts->Fill(v_xd_ge[j].ts-v_xd_ge[i].ts);
        }
      }
    }
  
  }
  // h_si_ts
  if(n_si>1){
    for(int i=0;i<(n_si-1);i++){
      for(int j=1;j<n_si;j++){
        if(rndm->Uniform()>0.5){
          h_si_ts->Fill(v_xd_si[i].ts-v_xd_si[j].ts);
        }else{
          h_si_ts->Fill(v_xd_si[j].ts-v_xd_si[i].ts);
        }
      }
    }  
  }

  // h_ge_si_ts
  if(n_ge>1 && n_si>1){
    for(int i=0;i<n_ge;i++){
      for(int j=0;j<n_si;j++){
        if(rndm->Uniform()>0.5){
          h_ge_si_ts->Fill(v_xd_ge[i].ts-v_xd_si[j].ts);
        }else{
          h_ge_si_ts->Fill(v_xd_si[j].ts-v_xd_ge[i].ts);
        }
      }
    }
  }

  // h_all2
  int k = 0;
  for(int j=0;j<n;j++){
    if(j==k){
      continue;
    }
    if(rndm->Uniform()>0.5){
      h_ts2->Fill(v_data[k].ts-v_data[j].ts);
    }else{
      h_ts2->Fill(v_data[j].ts-v_data[k].ts);
    }
  }
  
  // h_ge_ts2
  k = 0;
  if(n_ge>1){
    for(int j=0;j<n_ge;j++){
      if(j==k){
        continue;
      }
      if(rndm->Uniform()>0.5){
        h_ge_ts2->Fill(v_xd_ge[k].ts-v_xd_ge[j].ts);
      }else{
        h_ge_ts2->Fill(v_xd_ge[j].ts-v_xd_ge[k].ts);
      }
    }
  }

  // h_si_ts2
  k = 0;
  if(n_si>1){
    for(int j=0;j<n_si;j++){
      if(j==k){
        continue;
      }
      if(rndm->Uniform()>0.5){
        h_si_ts2->Fill(v_xd_si[k].ts-v_xd_si[j].ts);
      }else{
        h_si_ts2->Fill(v_xd_si[j].ts-v_xd_si[k].ts);
      }
    }
  }

  // h_ge_si_ts
  k = 0;
  if(n_ge>1 && n_si>1){
    for(int j=0;j<n_si;j++){
      if(rndm->Uniform()>0.5){
        h_ge_si_ts2->Fill(v_xd_ge[k].ts-v_xd_si[j].ts);
      }else{
        h_ge_si_ts2->Fill(v_xd_si[j].ts-v_xd_ge[k].ts);
      }
    }
  }
  
}

//
void analysis::PrintXd(xia_data &x)
{
  std::cout << ">> mod " << x.mod << std::endl;
  std::cout << ">> ch " << x.ch << std::endl;
  std::cout << ">> energy " << x.energy << std::endl;
  std::cout << ">> ts " << x.ts << std::endl;
  std::cout << std::endl;
}
