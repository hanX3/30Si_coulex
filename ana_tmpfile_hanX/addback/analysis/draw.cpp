void draw()
{
  TFile *fi1 = TFile::Open("../../sort/rootfile/run00804_sort.root");
  TTree *tr1 = (TTree*)fi1->Get("tree");

  TFile *fi2 = TFile::Open("../rootfile/run00804_addback.root");
  TTree *tr2 = (TTree*)fi2->Get("tree");

  TH1D *h_c3_1 = new TH1D("h_c3_1", "h_c3_1", 8192, 0, 4096);
  TH1D *h_c3_2 = new TH1D("h_c3_2", "h_c3_2", 8192, 0, 4096);
  TH1D *h_c3_3 = new TH1D("h_c3_3", "h_c3_3", 8192, 0, 4096);
  TH1D *h_c3_6 = new TH1D("h_c3_6", "h_c3_6", 8192, 0, 4096);
  TH1D *h_c3_7 = new TH1D("h_c3_7", "h_c3_7", 8192, 0, 4096);
  TH1D *h_c3_8 = new TH1D("h_c3_8", "h_c3_8", 8192, 0, 4096);

  TH1D *hab_c3_1 = new TH1D("hab_c3_1", "hab_c3_1", 8192, 0, 4096);
  TH1D *hab_c3_2 = new TH1D("hab_c3_2", "hab_c3_2", 8192, 0, 4096);
  TH1D *hab_c3_3 = new TH1D("hab_c3_3", "hab_c3_3", 8192, 0, 4096);
  TH1D *hab_c3_6 = new TH1D("hab_c3_6", "hab_c3_6", 8192, 0, 4096);
  TH1D *hab_c3_7 = new TH1D("hab_c3_7", "hab_c3_7", 8192, 0, 4096);
  TH1D *hab_c3_8 = new TH1D("hab_c3_8", "hab_c3_8", 8192, 0, 4096);

  TCanvas *c3_1 = new TCanvas("c3_1", "", 0, 0, 1200, 400);
  TCanvas *c3_2 = new TCanvas("c3_2", "", 0, 0, 1200, 400);
  TCanvas *c3_3 = new TCanvas("c3_3", "", 0, 0, 1200, 400);
  TCanvas *c3_6 = new TCanvas("c3_6", "", 0, 0, 1200, 400);
  TCanvas *c3_7 = new TCanvas("c3_7", "", 0, 0, 1200, 400);
  TCanvas *c3_8 = new TCanvas("c3_8", "", 0, 0, 1200, 400);

  //3-1
  tr1->Draw("energy>>h_c3_1", "mod==2 && ch>=0 && ch<4", "goff");
  tr2->Draw("energy>>hab_c3_1", "mod==2 && ch>=0 && ch<4", "goff");
  h_c3_1->SetLineColor(4);
  hab_c3_1->SetLineColor(2);
  c3_1->cd();
  c3_1->SetLogy();
  h_c3_1->Draw();
  hab_c3_1->Draw("same");

  //3-2
  tr1->Draw("energy>>h_c3_2", "mod==2 && ch>=4 && ch<8", "goff");
  tr2->Draw("energy>>hab_c3_2", "mod==2 && ch>=4 && ch<8", "goff");
  h_c3_2->SetLineColor(4);
  hab_c3_2->SetLineColor(2);
  c3_2->cd();
  c3_2->SetLogy();
  h_c3_2->Draw();
  hab_c3_2->Draw("same");

  //3-3
  tr1->Draw("energy>>h_c3_3", "mod==2 && ch>=8 && ch<12", "goff");
  tr2->Draw("energy>>hab_c3_3", "mod==2 && ch>=8 && ch<12", "goff");
  h_c3_3->SetLineColor(4);
  hab_c3_3->SetLineColor(2);
  c3_3->cd();
  c3_3->SetLogy();
  h_c3_3->Draw();
  hab_c3_3->Draw("same");

  //3-6
  tr1->Draw("energy>>h_c3_6", "mod==3 && ch>=8 && ch<12", "goff");
  tr2->Draw("energy>>hab_c3_6", "mod==3 && ch>=8 && ch<12", "goff");
  h_c3_6->SetLineColor(4);
  hab_c3_6->SetLineColor(2);
  c3_6->cd();
  c3_6->SetLogy();
  h_c3_6->Draw();
  hab_c3_6->Draw("same");

  //3-7
  tr1->Draw("energy>>h_c3_7", "mod==4 && ch>=0 && ch<4", "goff");
  tr2->Draw("energy>>hab_c3_7", "mod==4 && ch>=0 && ch<4", "goff");
  h_c3_7->SetLineColor(4);
  hab_c3_7->SetLineColor(2);
  c3_7->cd();
  c3_7->SetLogy();
  h_c3_7->Draw();
  hab_c3_7->Draw("same");

  //3-8
  tr1->Draw("energy>>h_c3_8", "mod==4 && ch>=8 && ch<12", "goff");
  tr2->Draw("energy>>hab_c3_8", "mod==4 && ch>=8 && ch<12", "goff");
  h_c3_8->SetLineColor(4);
  hab_c3_8->SetLineColor(2);
  c3_8->cd();
  c3_8->SetLogy();
  h_c3_8->Draw();
  hab_c3_8->Draw("same");
}
