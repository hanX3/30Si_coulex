
void check_cali(int run, int mod, int ch)
{
  TFile *fi = TFile::Open(TString::Format("../sort/rootfile/run%05d_sort.root",run).Data());
  if(fi->IsZombie()){
    cout << "can not open the file" << endl;
    return;
  }

  TTree *tree = (TTree*)fi->Get("tree");


  stringstream ss;
  ss.str("");

  char hist_name[256];
  sprintf(hist_name, "h_mod%02d_ch%02d", mod, ch);
  cout << hist_name << endl;

  TH1D *h = new TH1D(hist_name, "", 8192, 0, 4096);
  
  TString str_draw, str_cut;
  str_draw = TString::Format("energy>>%s", hist_name);
  str_cut = TString::Format("mod==%d&&ch==%d", mod, ch);
  tree->Draw(str_draw.Data(), str_cut.Data(), "goff");

  TCanvas *cc = new TCanvas("cc", "cc", 0, 0, 1240, 360);
  cc->Divide(3, 1);

  //
  cc->cd(1);
  gPad->SetLogy();
  TH1D *h1 = (TH1D*)h->Clone("h1");
  h1->GetXaxis()->SetRangeUser(480., 540.);
  TF1 *tf1 = new TF1("tf1", "gaus", 511.-4., 511.+4.);
  h1->Fit("tf1", "R");
  h1->Draw();
  
  ss.str("");
  ss << tf1->GetParameter(1) << "(511.0) keV";
  TPaveLabel *pp1 = new TPaveLabel(0.6,0.6,0.90,0.7,ss.str().c_str(),"brNDC");
  pp1->SetTextColor(kRed+3);
  pp1->Draw();

  //
  cc->cd(2);
  gPad->SetLogy();
  TH1D *h2 = (TH1D*)h->Clone("h2");
  h2->GetXaxis()->SetRangeUser(1430., 1490.);
  h2->SetTitle(hist_name);
  h2->SetTitleSize(0.04);
  TF1 *tf2 = new TF1("tf2", "gaus", 1460.-6., 1460.+6.);
  h2->Fit("tf2", "R");
  h2->Draw();
  
  ss.str("");
  ss << tf2->GetParameter(1) << "(1460.8) keV";
  TPaveLabel *pp2 = new TPaveLabel(0.6,0.6,0.90,0.7,ss.str().c_str(),"brNDC");
  pp2->SetTextColor(kRed+3);
  pp2->Draw();

  //
  cc->cd(3);
  gPad->SetLogy();
  TH1D *h3 = (TH1D*)h->Clone("h3");
  h3->GetXaxis()->SetRangeUser(2580., 2640.);
  TF1 *tf3 = new TF1("tf3", "gaus", 2614.-6., 2614.+10.);
  h3->Fit("tf3", "R");
  h3->Draw();
  
  ss.str("");
  ss << tf3->GetParameter(1) << "(2614.5) keV";
  TPaveLabel *pp3 = new TPaveLabel(0.6,0.6,0.90,0.7,ss.str().c_str(),"brNDC");
  pp3->SetTextColor(kRed+3);
  pp3->Draw();

  cc->SaveAs(TString::Format("./png/run%05d_mod%02dch%02d.png",run,mod,ch).Data());

  delete h;
}

