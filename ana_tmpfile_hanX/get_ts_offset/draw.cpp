// Ge vs. Ge
void draw1()
{
  TH1D *h[16*5];
  for(int i=0;i<16*5;i++){
    // cout << TString::Format("mod%d_ch%02d_vs_mod0_ch00",i/16,i%16) << endl;
    h[i] = (TH1D*)gFile->Get(TString::Format("mod%d_ch%02d_vs_mod0_ch00",i/16,i%16).Data());
  }

  TCanvas *c1 = new TCanvas("c1", "", 0, 0, 1400, 600);
  c1->Divide(4, 2);
  for(int i=0;i<8;i++){
    c1->cd(i+1);
    h[i]->Draw();
  }

  TCanvas *c2 = new TCanvas("c2", "", 0, 0, 1400, 600);
  c2->Divide(4, 2);
  for(int i=16;i<16+8;i++){
    c2->cd(i+1-16);
    h[i]->Draw();
  }

  TCanvas *c3 = new TCanvas("c3", "", 0, 0, 1400, 600);
  c3->Divide(4, 3);
  for(int i=16*2;i<16*2+12;i++){
    c3->cd(i+1-16*2);
    h[i]->Draw();
  }

  TCanvas *c4 = new TCanvas("c4", "", 0, 0, 1400, 600);
  c4->Divide(4, 3);
  for(int i=16*3;i<16*3+12;i++){
    c4->cd(i+1-16*3);
    h[i]->Draw();
  }

  TCanvas *c5 = new TCanvas("c5", "", 0, 0, 1400, 600);
  c5->Divide(4, 3);
  for(int i=16*4;i<16*4+12;i++){
    c5->cd(i+1-16*4);
    h[i]->Draw();
  }
}

// Si ring vs. Si sector
void draw2()
{
  TH1D *h[24*32];
  for(int i=0;i<24*32;i++){
    cout << TString::Format("Si_ring%02d_vs_Si_sector%02d",i/32,i%32) << endl;
    h[i] = (TH1D*)gFile->Get(TString::Format("Si_ring%02d_vs_Si_sector%02d",i/32,i%32).Data());
  }

  TCanvas *cc[24];
  for(int i=0;i<24;i++){
    cc[i] = new TCanvas(TString::Format("cc%02d",i).Data(), TString::Format("cc%02d",i).Data(), 0, 0, 1400, 600);
    cc[i]->Divide(8, 4);
    for(int j=0+32*i;j<32*(i+1);j++){
      cc[i]->cd(j%32+1);
      h[j]->Draw();
    }
  }
}

// Ge vs. Si
void draw3()
{
  TH1D *h[24+32];
  for(int i=0;i<24;i++){
    cout << TString::Format("Si_ring%02d_vs_mod0_ch00",i) << endl;
    h[i] = (TH1D*)gFile->Get(TString::Format("Si_ring%02d_vs_mod0_ch00",i).Data());
  }
  for(int i=0;i<32;i++){
    cout << TString::Format("Si_sector%02d_vs_mod0_ch00",i) << endl;
    h[i+24] = (TH1D*)gFile->Get(TString::Format("Si_sector%02d_vs_mod0_ch00",i).Data());
  }

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 1400, 600);
  c1->Divide(6, 4);
  for(int i=0;i<24;i++){
    c1->cd(i+1);
    h[i]->Draw();
  }

  TCanvas *c2 = new TCanvas("c2", "c2", 0, 0, 1400, 600);
  c2->Divide(8, 4);
  for(int i=0;i<32;i++){
    c2->cd(i+1);
    h[i+24]->Draw();
  }
}
