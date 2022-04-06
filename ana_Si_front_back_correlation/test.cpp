void test()
{
  TFile *file_in;
  file_in = TFile::Open("../ana_rootfile/run00804_ana.root");
  
  TTree *tr1_Si = (TTree*)file_in->Get("tr1_Si");
  TH2D *h2 = new TH2D("h2", "h2", 2048,0,32768,2048,0,32768);
  
  int n = 0;
  n = tr1_Si->Draw("Si_ring_adc:Si_sector_adc>>h2", "n_Si_ring==1&&n_Si_sector==1&&Si_ring_mod==6&&Si_ring_ch==7&&Si_sector_mod==7&&Si_sector_ch==4", "col");
  cout << "n " << n << endl;
  TGraph *gr = new TGraph(n, tr1_Si->GetV2(), tr1_Si->GetV1());

  TCanvas *c2 = new TCanvas("c2", "c2", 0, 0, 480, 360);
  c2->cd();
  gr->Draw("ap");

  TF1 *tf1 = new TF1("tf1", "pol1", 2000, 32768);
  tf1->SetLineColor(kGray);
  gr->Fit(tf1, "");
  tf1->Draw();
  h2->Draw("same colz");
  c2->SaveAs("c2.pdf");

  TCanvas *c3 = new TCanvas("c3", "c3", 0, 0, 480, 360);
  c3->cd();
  gr->Draw("ap");

  TF1 *tf2 = new TF1("tf2", "pol1", 2000, 32768);
  tf2->SetLineColor(kGray);
  gr->Fit(tf2, "ROB");
  tf2->Draw();
  h2->Draw("same colz");
  c3->SaveAs("c3.pdf");
}
