// Ge vs. Ge
void fit_offset()
{
  ofstream fo;
  fo.open("ts.offset");
  fo << "mod  ch  ts_offset[ns]  chi_square" << endl;
  char str[1024];
  sprintf(str, "%3d  %2d  %13.2f  %10.2f", 0, 0, 0., 0.);
  fo << str << endl;

  int mod, ch;
  double ts, chi2;
  
  // Ge
  TH1D *h_ge[16*5];
  for(int i=1;i<16*5;i++){
    mod = i/16;
    ch = i%16;
    // cout << TString::Format("mod%d_ch%02d_vs_mod0_ch00",i/16,i%16) << endl;
    h_ge[i] = (TH1D*)gFile->Get(TString::Format("mod%d_ch%02d_vs_mod0_ch00",i/16,i%16).Data());
    if(h_ge[i]->GetEntries()==0){
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, 0., 0.);
      fo << str << endl;
      continue;
    }
    h_ge[i]->Fit("gaus", "Q0", "", -200, 200);

    TF1 *fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
    ts = fg->GetParameter(1);
    chi2 = fg->GetChisquare();
    
    sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, ts, chi2);
    fo << str << endl;
    if(fg) delete fg;
  }

  // Si ring
  TH1D *h_si_ring[24];
  for(int i=0;i<24;i++){
    mod = i/16+5;
    ch = i%16;
    // cout << TString::Format("Si_ring%02d_vs_mod0_ch00",i) << endl;
    h_si_ring[i] = (TH1D*)gFile->Get(TString::Format("Si_ring%02d_vs_mod0_ch00",i).Data());
    
    if(h_si_ring[i]->GetEntries()==0){
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, 0., 0.);
      fo << str << endl;
      continue;
    }
    h_si_ring[i]->Fit("gaus", "Q0", "", -200, 200);

    TF1 *fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
    ts = fg->GetParameter(1);
    chi2 = fg->GetChisquare();
    
    sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, ts, chi2);
    fo << str << endl;
    if(fg) delete fg;
  }

  // Si sector
  TH1D *h_si_sector[32];
  for(int i=24;i<32;i++){
    mod = i/16+5;
    ch = i%16;

    if(i==30){
      h_si_sector[23] = (TH1D*)gFile->Get(TString::Format("Si_sector%02d_vs_mod0_ch00",23).Data());
      h_si_sector[23]->Fit("gaus", "Q0", "", -200, 200);

      TF1 *fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
      ts = fg->GetParameter(1);
      chi2 = fg->GetChisquare();
    
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, ts, chi2);
      fo << str << endl;
      
      if(fg) delete fg;

      continue;
    }

    if(i==31){
      h_si_sector[31] = (TH1D*)gFile->Get(TString::Format("Si_sector%02d_vs_mod0_ch00",31).Data());
      h_si_sector[31]->Fit("gaus", "Q0", "", -200, 200);

      TF1 *fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
      ts = fg->GetParameter(1);
      chi2 = fg->GetChisquare();
    
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, ts, chi2);
      fo << str << endl;
      
      if(fg) delete fg;

      continue;
    }
  
    sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, 0., 0.);
    fo << str << endl;
  }

  for(int i=0;i<32;i++){
    mod = i/16+7;
    ch = i%16;

    if(i==23 || i==31){
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, 0., 0.);
      fo << str << endl;

      continue;
    }

    // cout << TString::Format("Si_sector%02d_vs_mod0_ch00",i) << endl;
    h_si_sector[i] = (TH1D*)gFile->Get(TString::Format("Si_sector%02d_vs_mod0_ch00",i).Data());
    
    if(h_si_sector[i]->GetEntries()==0){
      sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, 0., 0.);
      fo << str << endl;
      continue;
    }
    h_si_sector[i]->Fit("gaus", "Q0", "", -200, 200);

    TF1 *fg = (TF1*)gROOT->GetListOfFunctions()->FindObject("gaus");
    
    ts = fg->GetParameter(1);
    chi2 = fg->GetChisquare();
    
    sprintf(str, "%3d  %2d  %13.2f  %10.2f", mod, ch, ts, chi2);
    fo << str << endl;
    if(fg) delete fg;
  }

  fo.close();
}

