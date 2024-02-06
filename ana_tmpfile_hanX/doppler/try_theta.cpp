//
void try_theta()
{
  gStyle->SetOptStat(0);

  //
  vector<TString> v_filename;

  v_filename.push_back("./rootfile/rootfile_29/doppler_r804_825.root"); // 
  v_filename.push_back("./rootfile/rootfile_31/doppler_r804_825.root"); //
  v_filename.push_back("./rootfile/rootfile_32/doppler_r804_825.root"); //
  v_filename.push_back("./rootfile/rootfile_33/doppler_r804_825.root"); //


  int n = v_filename.size();

  TFile *fi[n];
  TH1D *h[n];

  for(int i=0;i<n;i++){
    fi[i] =  TFile::Open(v_filename[i].Data());
    fi[i]->cd();
    h[i] = (TH1D*)gFile->Get("h_event_ge_doppler_all");
    h[i]->Rebin(4);
  }

  TLegend *leg = new TLegend(0.6, 0.75, 0.95, 0.95);
  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 480, 360);
  c1->cd();
  for(int i=0;i<n;i++){
    leg->AddEntry(h[i]);
    h[i]->SetLineColor(i+1);
    if(i==0){
      h[i]->SetTitle("");
      h[i]->GetXaxis()->SetRangeUser(2100, 2400);
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

  c1->Update();
  c1->SaveAs("png/phi.png");
}

//
void try_theta_single_clover(int clover_id)
{
  gStyle->SetOptStat(0);

  //
  vector<TString> v_filename;

  v_filename.push_back("./rootfile/rootfile_33/doppler_r804_825.root"); //


  int n = v_filename.size();

  TFile *fi[n];
  TH1D *h[n], *ha[n], *hb[n], *hc[n], *hd[n];
  TLegend *leg[n];
  TCanvas *cc[n];
  TLine *l1 = new TLine(2235, 0, 2235., 10e4);
  l1->SetLineWidth(3);
  l1->SetLineColor(2);
  l1->SetLineStyle(3);

  for(int i=0;i<n;i++){
    fi[i] =  TFile::Open(v_filename[i].Data());
    fi[i]->cd();
    gROOT->ProcessLine("event_clover_ring3->cd()");
    ha[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_clover_doppler_ring3_%d_a",clover_id).Data());
    hb[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_clover_doppler_ring3_%d_b",clover_id).Data());
    hc[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_clover_doppler_ring3_%d_c",clover_id).Data());
    hd[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_clover_doppler_ring3_%d_d",clover_id).Data());
    h[i] = (TH1D*)ha[i]->Clone(TString::Format("h%d",i).Data());
    h[i]->Add(hb[i]);
    h[i]->Add(hc[i]);
    h[i]->Add(hd[i]);
    h[i]->Rebin(2);

    //
    leg[i] = new TLegend(0.6, 0.75, 0.95, 0.95);
    cc[i] = new TCanvas(TString::Format("cc%d",i).Data(), "", 0, 0, 480, 360);
    cc[i]->cd();
    leg[i]->AddEntry(h[i]);
    leg[i]->AddEntry(ha[i]);
    leg[i]->AddEntry(hb[i]);
    leg[i]->AddEntry(hc[i]);
    leg[i]->AddEntry(hd[i]);
    
    h[i]->SetTitle("");
    h[i]->GetXaxis()->SetRangeUser(2100, 2400);
    
    h[i]->SetLineColor(1);
    ha[i]->SetLineColor(2);
    hb[i]->SetLineColor(3);
    ha[i]->SetLineColor(4);
    ha[i]->SetLineColor(6);

    h[i]->Draw();
    ha[i]->Draw("same");
    hb[i]->Draw("same");
    hc[i]->Draw("same");
    hd[i]->Draw("same");
    
    l1->Draw();
  }

}
