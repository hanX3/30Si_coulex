//
TFile *fi = TFile::Open("rootfile/rootfile_1/doppler_r826_888.root");

//
void draw_ge_1_1()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_1"); 
  
  //
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring1->cd()");
  TH1D *h_bg = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring1_1"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(4);
  h_bg->SetLineColor(2);

  //
  cc->SetLogy();
  h_event->Draw();
  h_bg->Draw("same");
}

//
void draw_ge_2_2()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring2->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_2"); 
  
  //
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring2->cd()");
  TH1D *h_bg = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring2_2"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(4);
  h_bg->SetLineColor(2);

  //
  cc->SetLogy();
  h_event->Draw();
  h_bg->Draw("same");
}

//
void draw_clover_3_6()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_clover_ring3->cd()");
  TH1D *h_event_a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_a"); 
  TH1D *h_event_b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_b"); 
  TH1D *h_event_c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_c"); 
  TH1D *h_event_d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_d"); 
  
  TH1D *h_event = (TH1D*)h_event_a->Clone("h_event");
  h_event->Add(h_event_b);
  h_event->Add(h_event_c);
  h_event->Add(h_event_d);

  //
  fi->cd();
  gROOT->ProcessLine("bg_clover_ring3->cd()");
  TH1D *h_bg_a = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_a"); 
  TH1D *h_bg_b = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_b"); 
  TH1D *h_bg_c = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_c"); 
  TH1D *h_bg_d = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_d"); 

  TH1D *h_bg = (TH1D*)h_bg_a->Clone("h_bg");
  h_bg->Add(h_bg_b);
  h_bg->Add(h_bg_c);
  h_bg->Add(h_bg_d);

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(4);
  h_bg->SetLineColor(2);

  //
  cc->SetLogy();
  h_event->Draw();
  h_bg->Draw("same");
}

//
void draw_ge_4_1()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring4->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_1"); 
  
  //
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring4->cd()");
  TH1D *h_bg = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring4_1"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(4);
  h_bg->SetLineColor(2);

  //
  cc->SetLogy();
  h_event->Draw();
  h_bg->Draw("same");
}

//
void draw_ge_5_1()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring5->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_1"); 
  
  //
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring5->cd()");
  TH1D *h_bg = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring5_1"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(4);
  h_bg->SetLineColor(2);

  //
  cc->SetLogy();
  h_event->Draw();
  h_bg->Draw("same");
}

//
void draw_ge_event_ring1()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_all"); 
  TH1D *h1 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_1"); 
  TH1D *h2 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_2"); 
  TH1D *h3 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_3"); 
  TH1D *h4 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_4"); 
  
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  h4->SetLineColor(6);

  //
  cc->SetLogy();
  h_event->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
}

//
void draw_ge_event_ring2()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring2->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_all"); 
  TH1D *h1 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_2"); 
  TH1D *h2 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_4"); 
  TH1D *h3 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_6"); 
  TH1D *h4 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_8"); 
  
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  h4->SetLineColor(6);

  //
  cc->SetLogy();
  h_event->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
}


//
void draw_clover_event_ring3()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_clover_ring3->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_all"); 
  TH1D *h1a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_1_a"); 
  TH1D *h1b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_1_b"); 
  TH1D *h1c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_1_c"); 
  TH1D *h1d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_1_d"); 
  TH1D *h1 = (TH1D*)h1a->Clone("h1");
  h1->Add(h1b);
  h1->Add(h1c);
  h1->Add(h1d);

  TH1D *h2a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_2_a"); 
  TH1D *h2b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_2_b"); 
  TH1D *h2c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_2_c"); 
  TH1D *h2d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_2_d"); 
  TH1D *h2 = (TH1D*)h2a->Clone("h2");
  h2->Add(h2b);
  h2->Add(h2c);
  h2->Add(h2d);
  
  TH1D *h3a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_3_a"); 
  TH1D *h3b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_3_b"); 
  TH1D *h3c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_3_c"); 
  TH1D *h3d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_3_d"); 
  TH1D *h3 = (TH1D*)h3a->Clone("h3");
  h3->Add(h3b);
  h3->Add(h3c);
  h3->Add(h3d);

  TH1D *h5a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_5_a"); 
  TH1D *h5 = (TH1D*)h5a->Clone("h5");

  TH1D *h6a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_a"); 
  TH1D *h6b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_b"); 
  TH1D *h6c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_c"); 
  TH1D *h6d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_d"); 
  TH1D *h6 = (TH1D*)h6a->Clone("h6");
  h6->Add(h6b);
  h6->Add(h6c);
  h6->Add(h6d);

  TH1D *h7a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_7_a"); 
  TH1D *h7b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_7_b"); 
  TH1D *h7c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_7_c"); 
  TH1D *h7d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_7_d"); 
  TH1D *h7 = (TH1D*)h7a->Clone("h7");
  h7->Add(h7b);
  h7->Add(h7c);
  h7->Add(h7d);

  TH1D *h8a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_8_a"); 
  TH1D *h8b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_8_b"); 
  TH1D *h8c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_8_c"); 
  TH1D *h8d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_8_d"); 
  TH1D *h8 = (TH1D*)h8a->Clone("h8");
  h8->Add(h8b);
  h8->Add(h8c);
  h8->Add(h8d);
  
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  h5->SetLineColor(5);
  h6->SetLineColor(6);
  h7->SetLineColor(7);
  h8->SetLineColor(8);

  //
  cc->SetLogy();
  h_event->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  h5->Draw("same");
  h6->Draw("same");
  h7->Draw("same");
  h8->Draw("same");
}
//
void draw_ge_event_ring4()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring4->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_all"); 
  TH1D *h1 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_1"); 
  TH1D *h2 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_3"); 
  TH1D *h3 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_5"); 
  TH1D *h4 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_7"); 
  
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  h4->SetLineColor(6);

  //
  cc->SetLogy();
  h_event->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
}

//
void draw_ge_event_ring5()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring5->cd()");
  TH1D *h_event = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_all"); 
  TH1D *h1 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_1"); 
  TH1D *h2 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_2"); 
  TH1D *h3 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_3"); 
  TH1D *h4 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_4"); 
  
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_event->GetXaxis()->SetRangeUser(0, 1200);
  h_event->GetYaxis()->SetRangeUser(0.1, 1.2*h_event->GetMaximum());
  h_event->SetLineColor(1);
  h1->SetLineColor(2);
  h2->SetLineColor(3);
  h3->SetLineColor(4);
  h4->SetLineColor(6);

  //
  cc->SetLogy();
  h_event->Draw();
  h1->Draw("same");
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
}

//
void draw_diff_ring_event()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("event_ge_ring1->cd()");
  TH1D *h_ring1 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring1_1"); 
  
  fi->cd();
  gROOT->ProcessLine("event_ge_ring2->cd()");
  TH1D *h_ring2 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring2_2"); 
  
  fi->cd();
  gROOT->ProcessLine("event_clover_ring3->cd()");
  TH1D *h_ring3a = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_a"); 
  TH1D *h_ring3b = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_b"); 
  TH1D *h_ring3c = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_c"); 
  TH1D *h_ring3d = (TH1D*)gDirectory->Get("h_event_clover_no_doppler_ring3_6_d"); 
  TH1D *h_ring3 = (TH1D*)h_ring3a->Clone("h_ring3");
  h_ring3->Add(h_ring3b);
  h_ring3->Add(h_ring3c);
  h_ring3->Add(h_ring3d);
  
  fi->cd();
  gROOT->ProcessLine("event_ge_ring4->cd()");
  TH1D *h_ring4 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring4_1"); 
  
  fi->cd();
  gROOT->ProcessLine("event_ge_ring5->cd()");
  TH1D *h_ring5 = (TH1D*)gDirectory->Get("h_event_ge_no_doppler_ring5_1"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_ring1->GetXaxis()->SetRangeUser(0, 1200);
  h_ring1->GetYaxis()->SetRangeUser(0.1, 12.*h_ring1->GetMaximum());
  h_ring1->SetLineColor(2);
  h_ring2->SetLineColor(3);
  h_ring3->SetLineColor(4);
  h_ring4->SetLineColor(5);
  h_ring5->SetLineColor(6);

  //
  cc->SetLogy();
  h_ring1->Draw();
  h_ring2->Draw("same");
  h_ring3->Draw("same");
  h_ring4->Draw("same");
  h_ring5->Draw("same");
}

//
void draw_diff_ring_bg()
{
  if(!fi || fi->IsZombie()){
    cout << "cannot open file" << endl;
    delete fi;
    return;
  }

  //
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring1->cd()");
  TH1D *h_ring1 = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring1_1"); 
  
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring2->cd()");
  TH1D *h_ring2 = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring2_2"); 
  
  fi->cd();
  gROOT->ProcessLine("bg_clover_ring3->cd()");
  TH1D *h_ring3a = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_a"); 
  TH1D *h_ring3b = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_b"); 
  TH1D *h_ring3c = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_c"); 
  TH1D *h_ring3d = (TH1D*)gDirectory->Get("h_bg_clover_no_doppler_ring3_6_d"); 
  TH1D *h_ring3 = (TH1D*)h_ring3a->Clone("h_ring3");
  h_ring3->Add(h_ring3b);
  h_ring3->Add(h_ring3c);
  h_ring3->Add(h_ring3d);
  
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring4->cd()");
  TH1D *h_ring4 = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring4_1"); 
  
  fi->cd();
  gROOT->ProcessLine("bg_ge_ring5->cd()");
  TH1D *h_ring5 = (TH1D*)gDirectory->Get("h_bg_ge_no_doppler_ring5_1"); 

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 900, 400);
  cc->cd();
  h_ring1->GetXaxis()->SetRangeUser(0, 1200);
  h_ring1->GetYaxis()->SetRangeUser(0.1, 12.*h_ring1->GetMaximum());
  h_ring1->SetLineColor(2);
  h_ring2->SetLineColor(3);
  h_ring3->SetLineColor(4);
  h_ring4->SetLineColor(5);
  h_ring5->SetLineColor(6);

  //
  cc->SetLogy();
  h_ring1->Draw();
  h_ring2->Draw("same");
  h_ring3->Draw("same");
  h_ring4->Draw("same");
  h_ring5->Draw("same");
}


