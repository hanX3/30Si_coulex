
void yield()
{
  gFile->cd();
  TH1D *h_event_ge_no_doppler_all = (TH1D*)gFile->Get("h_event_ge_no_doppler_all");
  TH1D *h_bg_ge_no_doppler_all = (TH1D*)gFile->Get("h_bg_ge_no_doppler_all");
  TH1D *h_sub_no_doppler_all = (TH1D*)h_event_ge_no_doppler_all->Clone("h_sub_no_doppler_all");

  h_sub_no_doppler_all->Add(h_bg_ge_no_doppler_all, -2.);

  TCanvas *c1_all = new TCanvas("c1_all", "c1_all", 0, 0, 480, 360);
  c1_all->cd();
  h_event_ge_no_doppler_all->SetLineColor(1);
  h_event_ge_no_doppler_all->GetXaxis()->SetRangeUser(1200, 2700);
  h_event_ge_no_doppler_all->Draw();

  h_bg_ge_no_doppler_all->SetLineColor(2);
  h_bg_ge_no_doppler_all->Draw("same");
  h_sub_no_doppler_all->SetLineColor(4);
  h_sub_no_doppler_all->Draw("same");

  //
  TH1D *h_event_ge_doppler_all = (TH1D*)gFile->Get("h_event_ge_doppler_all");
  TH1D *h_bg_ge_doppler_all = (TH1D*)gFile->Get("h_bg_ge_doppler_all");
  TH1D *h_sub_doppler_all = (TH1D*)h_event_ge_doppler_all->Clone("h_sub_doppler_all");

  h_sub_doppler_all->Add(h_bg_ge_doppler_all, -2.);

  TCanvas *c2_all = new TCanvas("c2_all", "c2_all", 0, 0, 480, 360);
  c2_all->cd();
  h_event_ge_doppler_all->SetLineColor(1);
  h_event_ge_doppler_all->GetXaxis()->SetRangeUser(1200, 2700);
  h_event_ge_doppler_all->Draw();

  h_bg_ge_doppler_all->SetLineColor(2);
  h_bg_ge_doppler_all->Draw("same");
  h_sub_doppler_all->SetLineColor(4);
  h_sub_doppler_all->Draw("same");

  // get yield
  h_sub_doppler_all->Fit("expo", "0", "", 2000, 2150);

  TF1 *tf = new TF1("tf", "expo", 2000, 2500);
  
  TF1 *fit = (TF1*)gROOT->GetListOfFunctions()->FindObject("expo");
  tf->SetParameter(0, fit->GetParameter(0));
  tf->SetParameter(1, fit->GetParameter(1));

  tf->Draw("same");

  double area=0;
  double back=0;
  area = h_sub_doppler_all->Integral(2170/2, 2300/2);
  for(int i=2170;i<2300;i++){
    back += tf->Eval((double)i);
  }
  back /= 2.;

  double s = area-back;
  double s_err = sqrt(area+back);
  cout << "area " << s << " error " << s_err << endl;
}

//
void yield_rings()
{
  gStyle->SetOptStat(0);
  gFile->cd();

  TH1D *h_event[24];
  TH1D *h_bg[24];

  for(int i=0;i<24;i++){
    h_event[i] = (TH1D*)gFile->Get(TString::Format("h_event_ge_doppler_all_si_ring%d",i+1).Data());
    h_bg[i] = (TH1D*)gFile->Get(TString::Format("h_bg_ge_doppler_all_si_ring%d",i+1).Data());
    

  }

  TH1D *h_event_add[6];
  TH1D *h_bg_add[6];
  TH1D *h_sub_add[6];

  int j = 0;
  for(int i=0;i<24;i++){
    if(i%4==0){
      j = i/4;
      h_event_add[j] = (TH1D*)h_event[i]->Clone(TString::Format("h_event_ring%d_%d",i+1,i+4).Data());
      h_bg_add[j] = (TH1D*)h_bg[i]->Clone(TString::Format("h_bg_ring%d_%d",i+1,i+4).Data());

      cout << j << endl;
      continue;
    }else{
      h_event_add[j]->Add(h_event[i]);
      h_bg_add[j]->Add(h_bg[i]);
    }
  }

  TLegend *leg = new TLegend(0.6, 0.75, 0.95, 0.95);
  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 480, 360);
  c1->cd();
  for(int i=0;i<6;i++){
    leg->AddEntry(h_event_add[i]);
    h_event_add[i]->SetLineColor(i+1);
    if(i==0){
      h_event_add[i]->SetTitle("");
      h_event_add[i]->GetXaxis()->SetRangeUser(1200, 2700);
      h_event_add[i]->Draw();
    }else{
      h_event_add[i]->Draw("same");
    }
  }
  leg->Draw();

  TLine *l1 = new TLine(2235, 0, 2235., 10e4);
  l1->SetLineWidth(3);
  l1->SetLineColor(2);
  l1->SetLineStyle(3);
  l1->Draw();

  //
  double s[6];
  double s_err[6];
  double s_er6];
  for(int i=0;i<6;i++){
    h_sub_add[i] = (TH1D*)h_event_add[i]->Clone(TString::Format("h_sub_add%d",i+1).Data());
    h_sub_add[i]->Add(h_bg_add[i], -2.);

    h_sub_add[i]->Fit("expo", "0", "", 2000, 2150);

    TF1 *tf = new TF1("tf", "expo", 2000, 2500);
    TF1 *fit = (TF1*)gROOT->GetListOfFunctions()->FindObject("expo");
    tf->SetParameter(0, fit->GetParameter(0));
    tf->SetParameter(1, fit->GetParameter(1));
    tf->Draw("same");

    double area=0;
    double back=0;
    area = h_sub_add[i]->Integral(2170/2, 2300/2);
    for(int j=2170;j<2300;j++){
      back += tf->Eval((double)j);
    }
    back /= 2.;

    s[i] = area-back;
    s_err[i] = sqrt(area+back);

    // if(tf) delete tf;
    // if(fit) delete fit;
  }

  for(int i=0;i<6;i++){
    cout << "s " << s[i] << " error " << s_err[i] << endl;
  }

}

//
void yield_rings_24()
{
  gStyle->SetOptStat(0);
  gFile->cd();

  TH1D *h_event[24];
  TH1D *h_bg[24];
  TH1D *h_sub[24];

  for(int i=0;i<24;i++){
    h_event[i] = (TH1D*)gFile->Get(TString::Format("h_event_ge_doppler_all_si_ring%d",i+1).Data());
    h_bg[i] = (TH1D*)gFile->Get(TString::Format("h_bg_ge_doppler_all_si_ring%d",i+1).Data());
  }

  TLegend *leg = new TLegend(0.6, 0.75, 0.95, 0.95);
  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 480, 360);
  c1->cd();
  for(int i=0;i<24;i++){
    leg->AddEntry(h_event[i]);
    h_event[i]->SetLineColor(i+1);
    if(i==0){
      h_event[i]->SetTitle("");
      h_event[i]->GetXaxis()->SetRangeUser(1200, 2700);
      h_event[i]->Draw();
    }else{
      h_event[i]->Draw("same");
    }
  }
  leg->Draw();

  TLine *l1 = new TLine(2235, 0, 2235., 10e4);
  l1->SetLineWidth(3);
  l1->SetLineColor(2);
  l1->SetLineStyle(3);
  l1->Draw();

  //
  double s[24];
  double s_err[24];
  for(int i=0;i<24;i++){
    h_sub[i] = (TH1D*)h_event[i]->Clone(TString::Format("h_sub%d",i+1).Data());
    h_sub[i]->Add(h_bg[i], -2.);

    h_sub[i]->Fit("expo", "0", "", 2000, 2150);

    TF1 *tf = new TF1("tf", "expo", 2000, 2500);
    TF1 *fit = (TF1*)gROOT->GetListOfFunctions()->FindObject("expo");
    tf->SetParameter(0, fit->GetParameter(0));
    tf->SetParameter(1, fit->GetParameter(1));
    tf->Draw("same");

    double area=0;
    double back=0;
    area = h_sub[i]->Integral(2170/2, 2300/2);
    for(int j=2170;j<2300;j++){
      back += tf->Eval((double)j);
    }
    back /= 2.;

    s[i] = area-back;
    s_err[i] = sqrt(area+back);

    // if(tf) delete tf;
    // if(fit) delete fit;
  }

  for(int i=0;i<24;i++){
    cout << i;
    cout << " s " << s[i] << " error " << s_err[i] << endl;
  }

}
