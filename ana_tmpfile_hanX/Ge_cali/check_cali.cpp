
void check_cali(int mod, int ch)
{
  stringstream ss;
  ss.str("");

  char hist_name[256];
  sprintf(hist_name, "h_mod%02d_ch%02d", mod, ch);
  cout << hist_name << endl;

  TH1D *h = (TH1D*)gDirectory->Get(hist_name);

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

  ss.str("");
  ss << "mod" << mod << "ch" << ch << ".png";
  cc->SaveAs(ss.str().c_str());
}

//
void check_cali_longtime(int mod, int ch)
{
  stringstream ss;

  char file_name[256];

  int run_num[5] = {804, 834, 875, 899, 924};
  TFile *fi[5];
  for(int i=0;i<5;i++){
    sprintf(file_name, "run%05d_ana.root", run_num[i]);
    cout << file_name << endl;
    fi[i] = TFile::Open(file_name);
    if(!fi[i]){
      cout << "cannot open " << file_name << endl;
      return;
    }
  }
  
  TCanvas *cc = new TCanvas("cc", "cc", 0, 0, 1240, 1600);
  cc->Divide(3, 6);
   
  char hist_name[256];
  sprintf(hist_name, "h_mod%d_ch%d", mod, ch);
  cout << hist_name << endl;

  TH1D *h1[5];
  TH1D *h2[5];
  TH1D *h3[5];
  TLegend *legend1 = new TLegend(0.68,0.6,0.86,0.88);
  TLegend *legend2 = new TLegend(0.68,0.6,0.86,0.88);
  TLegend *legend3 = new TLegend(0.68,0.6,0.86,0.88);
  TLine *l1 = new TLine(511.,0,511.,10e100);
  l1->SetLineWidth(3);
  l1->SetLineColor(2);
  l1->SetLineStyle(3);
  TLine *l2 = new TLine(1460.8,0,1460.0,10e100);
  l2->SetLineWidth(3);
  l2->SetLineColor(2);
  l2->SetLineStyle(3);
  TLine *l3 = new TLine(2614.5,0,2614.5,10e100);
  l3->SetLineWidth(3);
  l3->SetLineColor(2);
  l3->SetLineStyle(3);

  TH1D *hh1[5];
  TH1D *hh2[5];
  TH1D *hh3[5];
  TF1 *tf1 = new TF1("tf1", "gaus", 511.-6., 511.+6.);
  TF1 *tf2 = new TF1("tf2", "gaus", 1460.-6., 1460.+6.);
  TF1 *tf3 = new TF1("tf3", "gaus", 2614.-6., 2614.+6.);

  ss.str(""); 
  ss << "mod" << mod;
  for(int i=0;i<5;i++){
    if(!fi[i]->cd(ss.str().c_str())){
      cout << "can not enter " << ss.str() << "directionary of run " << run_num[i] << endl;
      return ;
    }

    TH1D *h = (TH1D*)gDirectory->Get(hist_name);
    stringstream ss_temp;

    cc->cd(1);
    gPad->SetLogy();
    ss_temp.str("");
    ss_temp << h1 << "_" << i;
    h1[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    h1[i]->GetXaxis()->SetRangeUser(480., 540.);
    h1[i]->SetLineColor(i+2);
    h1[i]->SetLineWidth(2);
    ss_temp.str("");
    ss_temp << "run" << run_num[i];
    legend1->AddEntry(h1[i], ss_temp.str().c_str());
    legend1->Draw();
    if(i==0){
      h1[i]->SetTitle("Total");
      h1[i]->Draw();
    }
    else{
      h1[i]->Scale(h1[0]->GetBinContent(511)/h1[i]->GetBinContent(511));
      h1[i]->Draw("same hist");
    }
    l1->Draw();

    cc->cd(2);
    gPad->SetLogy();
    ss_temp.str("");
    ss_temp << h2 << "_" << i;
    h2[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    h2[i]->GetXaxis()->SetRangeUser(1430., 1490.);
    h2[i]->SetLineColor(i+2);
    h2[i]->SetLineWidth(2);
    ss_temp.str("");
    ss_temp << "run" << run_num[i];
    legend2->AddEntry(h2[i], ss_temp.str().c_str());
    legend2->Draw();
    if(i==0){
      h2[i]->SetTitle("Total");
      h2[i]->Draw();
    }
    else{
      h2[i]->Scale(h2[0]->GetBinContent(1461)/h2[i]->GetBinContent(1461));
      h2[i]->Draw("same hist");
    }
    l2->Draw();

    cc->cd(3);
    gPad->SetLogy();
    ss_temp.str("");
    ss_temp << h3 << "_" << i;
    h3[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    h3[i]->GetXaxis()->SetRangeUser(2580., 2640.);
    h3[i]->SetLineColor(i+2);
    h3[i]->SetLineWidth(2);
    ss_temp.str("");
    ss_temp << "run" << run_num[i];
    legend3->AddEntry(h3[i], ss_temp.str().c_str());
    legend3->Draw();
    if(i==0){
      h3[i]->SetTitle("Total");
      h3[i]->Draw();
    }
    else{
      h3[i]->Scale(h3[0]->GetBinContent(2614)/h3[i]->GetBinContent(2614));
      h3[i]->Draw("same hist");
    }
    l3->Draw();

    //
    ss_temp.str("");
    ss_temp << hh1 << "_" << i;
    hh1[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    cc->cd(3*(i+1)+1);
    gPad->SetLogy();
    hh1[i]->GetXaxis()->SetRangeUser(480., 540.);
    ss_temp.str("");
    ss_temp << "run_" << run_num[i] << "_" << hist_name;
    hh1[i]->SetTitle(ss_temp.str().c_str());
    hh1[i]->Fit("tf1", "R");
    hh1[i]->Draw();
    ss_temp.str("");
    ss_temp << tf1->GetParameter(1) << "(511.0) keV";
    TPaveLabel *pp1 = new TPaveLabel(0.6,0.6,0.90,0.7,ss_temp.str().c_str(),"brNDC");
    pp1->SetTextColor(kRed+3);
    pp1->Draw();
    l1->Draw();


    hh2[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    cc->cd(3*(i+1)+2);
    gPad->SetLogy();
    hh2[i]->GetXaxis()->SetRangeUser(1430., 1490.);
    ss_temp.str("");
    ss_temp << "run_" << run_num[i] << "_" << hist_name;
    hh2[i]->SetTitle(ss_temp.str().c_str());
    hh2[i]->Fit("tf2", "R");
    hh2[i]->Draw();
    ss_temp.str("");
    ss_temp << tf2->GetParameter(1) << "(1460.8) keV";
    TPaveLabel *pp2 = new TPaveLabel(0.6,0.6,0.90,0.7,ss_temp.str().c_str(),"brNDC");
    pp2->SetTextColor(kRed+3);
    pp2->Draw();
    l2->Draw();

    hh3[i] = (TH1D*)h->Clone(ss_temp.str().c_str());
    cc->cd(3*(i+1)+3);
    gPad->SetLogy();
    hh3[i]->GetXaxis()->SetRangeUser(2580., 2640.);
    ss_temp.str("");
    ss_temp << "run_" << run_num[i] << "_" << hist_name;
    hh3[i]->SetTitle(ss_temp.str().c_str());
    hh3[i]->Fit("tf3", "R");
    hh3[i]->Draw();
    ss_temp.str("");
    ss_temp << tf3->GetParameter(1) << "(2614.5) keV";
    TPaveLabel *pp3 = new TPaveLabel(0.6,0.6,0.90,0.7,ss_temp.str().c_str(),"brNDC");
    pp3->SetTextColor(kRed+3);
    pp3->Draw();
    l3->Draw();
  }

  ss.str("");
  ss << "longtime_mod" << mod << "_ch" << ch << ".pdf";
  cc->SaveAs(ss.str().c_str());

  delete cc;
}
