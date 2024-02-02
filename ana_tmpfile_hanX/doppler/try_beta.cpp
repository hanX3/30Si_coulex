void try_beta()
{
  gStyle->SetOptStat(0);

  //
  vector<TString> v_filename;

  v_filename.push_back("./rootfile/rootfile_1/doppler_r804_825.root"); // 0
  v_filename.push_back("./rootfile/rootfile_10/doppler_r804_825.root"); // 10
  v_filename.push_back("./rootfile/rootfile_11/doppler_r804_825.root"); // 11

  int n = v_filename.size();

  TFile *fi[n];
  TH1D *h[n];

  for(int i=0;i<n;i++){
    fi[i] =  TFile::Open(v_filename[i].Data());
    fi[i]->cd();
    h[i] = (TH1D*)gFile->Get("h_event_ge_doppler_all");
    h[i]->Rebin(2);
  }

  TLegend *leg = new TLegend(0.6, 0.75, 0.95, 0.95);
  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 480, 360);
  c1->cd();
  for(int i=0;i<n;i++){
    leg->AddEntry(h[i]);
    h[i]->SetLineColor(i+1);
    if(i==0){
      h[i]->SetTitle("");
      h[i]->GetXaxis()->SetRangeUser(1200, 2700);
      h[i]->Draw();
    }else{
      h[i]->Draw("same");
    }
  }
  leg->Draw();
  
  TLine *l1 = new TLine(2235, 0, 2235., 10e4);
  l1->SetLineWidth(3);
  l1->SetLineColor(2);
  l1->SetLineStyle(3);
  l1->Draw();
}


