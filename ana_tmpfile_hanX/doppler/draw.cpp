
TFile *fi = TFile::Open("rootfile/rootfile_51/doppler_r804_825.root");

//
void draw()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  TH1D *h_no_doppler = (TH1D*)fi->Get("h_event_ge_no_doppler_all"); 
  TH1D *h_doppler = (TH1D*)fi->Get("h_event_ge_doppler_all"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_doppler->GetXaxis()->SetRangeUser(200, 1200);
  h_doppler->GetYaxis()->SetRangeUser(0.1, 1.2*h_doppler->GetMaximum());
  h_doppler->SetLineColor(4);
  h_no_doppler->SetLineColor(2);

  h_doppler->SetTitle("");
  //
  cc->SetLogy();
  h_doppler->Draw();
  h_no_doppler->Draw("same");
}
