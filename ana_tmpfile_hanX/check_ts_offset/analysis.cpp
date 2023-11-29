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
  tr->SetBranchAddress("ts", &ts);

  ts = 0;

  file_out = TFile::Open(filename_out.c_str(), "recreate");

  h_ts = new TH1D("h_ts", "", 2*ALIGNMENTWINDOW/10, -ALIGNMENTWINDOW, ALIGNMENTWINDOW);
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
  tr->GetEntry(0);
  ts1 = ts;
  for(Long64_t i=1;i<tr->GetEntries();i++){
    tr->GetEntry(i);
    ts2 = ts;

    if(abs(ts1-ts2)<ALIGNMENTWINDOW){
      if(rndm->Uniform()>0.5) h_ts->Fill(ts1-ts2);
      else h_ts->Fill(ts2-ts1);
    }else{
      ts1 = ts2;
    }
  }

  file_out->cd();
  h_ts->Write();
}

