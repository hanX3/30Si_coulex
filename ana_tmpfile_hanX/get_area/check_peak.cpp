
//
void check_si_ring()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  for(int i=0;i<24;i++){
    h[i] = (TH1D*)fi->Get(TString::Format("h_event_ge_doppler_all_si_ring%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_si_sector()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[32];

  Double_t s1[32], s2[32]; //s1(1600,2000);s2(2100,2400)

  for(int i=0;i<32;i++){
    h[i] = (TH1D*)fi->Get(TString::Format("h_event_ge_doppler_all_si_sector%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  /*
  for(int i=0;i<32;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }
  */
  h[30]->Draw();
  h[23]->Draw("same");

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<32;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring1()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[4];

  Double_t s1[4], s2[4]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<4;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_%d",i+1).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<4;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<4;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring2()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[4];

  Double_t s1[4], s2[4]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring2->cd()");
  for(int i=0;i<4;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring2_%d",2*(i+1)).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<4;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<4;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring3()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  Int_t clover_id[6] = {1,2,3,6,7,8};

  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_clover_ring3->cd()");
  for(int i=0;i<24;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_clover_doppler_ring3_%d_%c",clover_id[i/4],(char)(97+i%4)).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring4()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[4];

  Double_t s1[4], s2[4]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring4->cd()");
  for(int i=0;i<4;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring4_%d",2*(i+1)-1).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<4;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<4;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring5()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[4];

  Double_t s1[4], s2[4]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring5->cd()");
  for(int i=0;i<4;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring5_%d",i+1).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }


  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<4;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<4;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

void check_ge_ring1_ring2()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[2];

  Double_t s1[2], s2[2]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  h[0] = (TH1D*)gDirectory->Get("h_event_ge_doppler_ring1_all");

  fi->cd();
  gROOT->ProcessLine("event_ge_ring2->cd()");
  h[1] = (TH1D*)gDirectory->Get("h_event_ge_doppler_ring2_all");

  for(int i=0;i<2;i++){
    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));
    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  //
  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<2;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<2;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring1_1_si_ring()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<24;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_1_si_ring%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}


//
void check_ge_ring1_2_si_ring()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<24;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_2_si_ring%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring1_4_si_ring()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<24;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_4_si_ring%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring1_3_si_ring()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[24];

  Double_t s1[24], s2[24]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<24;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_3_si_ring%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<24;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<24;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}

//
void check_ge_ring1_1_si_sector()
{
  TFile *fi = TFile::Open("../doppler/rootfile/rootfile_33/doppler_r804_825.root");
  
  TH1D *h[32];

  Double_t s1[32], s2[32]; //s1(1600,2000);s2(2100,2400)

  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  for(int i=0;i<32;i++){
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_event_ge_doppler_ring1_1_si_sector%d",i).Data());
    h[i]->Rebin(4);
    h[i]->GetXaxis()->SetRangeUser(1500., 2500.);
    h[i]->SetLineColor(800+2*i);

    s1[i] = h[i]->Integral(1600/h[i]->GetBinWidth(1), 2000/h[i]->GetBinWidth(1));
    s2[i] = h[i]->Integral(2100/h[i]->GetBinWidth(1), 2400/h[i]->GetBinWidth(1));

    cout << i << " " << s1[i] << " " << s2[i] << endl;
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  cc1->SetLogy();
  for(int i=0;i<32;i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }

  //
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();

  TGraph *g1 = new TGraph();
  for(int i=0;i<32;i++){
    if(s1[i]==0 || s2[i]==0) continue;
    g1->SetPoint(i, i+1, s2[i]/s1[i]);
  }

  g1->Draw("AP*");
}
