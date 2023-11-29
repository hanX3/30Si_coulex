
// longtime Si
void draw()
{
  TH2D *hh[24+32];

  TCanvas *c1 = new TCanvas("c1", "", 0, 0, 1500, 800);
  c1->Divide(6, 4);
  for(int i=0;i<24;i++){
    hh[i] = (TH2D*)gFile->Get(TString::Format("hh_ring%02d",i).Data());
    c1->cd(i+1);
    gPad->SetLogz();
    hh[i]->Draw("col");
  }

  TCanvas *c2 = new TCanvas("c2", "", 0, 0, 1500, 800);
  c2->Divide(8, 4);
  for(int i=0;i<32;i++){
    hh[i+24] = (TH2D*)gFile->Get(TString::Format("hh_sector%02d",i).Data());
    c2->cd(i+1);
    gPad->SetLogz();
    hh[i+24]->Draw("col");
  }
}
