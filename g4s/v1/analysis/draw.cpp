
TFile *fi = TFile::Open("../b/data/event_20240131_16h31m58s.root");
TTree *tr = (TTree*)fi->Get("tr");

void draw_e()
{
  TH1D *h = new TH1D("h", "energy in Si", 3000, 0, 3000);
  tr->Draw("e>>h", "", "goff");

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();

  h->GetXaxis()->SetRangeUser(0, 3000.);
  h->GetXaxis()->SetTitle("Energy [MeV]");
  h->GetYaxis()->SetTitle("Counts");

  h->Draw();
}

void draw_z()
{
  TH1D *h = new TH1D("h", "distribution in depth", 400, 0, 400);
  tr->Draw("(z+5)*1000>>h", "", "goff");

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();

  h->GetXaxis()->SetRangeUser(0, 400.);
  h->GetXaxis()->SetTitle("Depth [um]");
  h->GetYaxis()->SetTitle("Counts");

  h->Draw();
}
