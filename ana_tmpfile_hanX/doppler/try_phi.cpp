void try_phi()
{
  gStyle->SetOptStat(0);

  TFile *fi[5];
  TH1D *h[5];

  for(int i=0;i<5;i++){
    fi[i] =  TFile::Open(TString::Format("./rootfile/rootfile_%d/all.root",i+6).Data());
    fi[i]->cd();
    h[i] = (TH1D*)gFile->Get("h_event_ge_doppler_all");
  }

  TLegend *leg = new TLegend(0.6, 0.75, 0.95, 0.95);
  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 480, 360);
  c1->cd();
  for(int i=0;i<5;i++){
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
