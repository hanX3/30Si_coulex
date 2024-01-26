//
using namespace RooFit;

TFile *fi = TFile::Open("../sort/rootfile/run02000_sort.root");
TTree *tr = (TTree*)fi->Get("tree");

//
void draw_spec(int mod, int ch)
{
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  TH1D *h1 = new TH1D("h1", TString::Format("ge_mod%02d_ch%02d",mod,ch).Data(), 8192, 0, 4096);
  tr->Draw("energy>>h1", TString::Format("mod==%d&&ch==%d",mod,ch).Data());
}

//
void get_spec_data(int mod, int ch)
{
  TH1D *h1 = new TH1D("h1", TString::Format("ge_mod%02d_ch%02d",mod,ch).Data(), 8192, 0, 4096);
  tr->Draw("energy>>h1", TString::Format("mod==%d&&ch==%d",mod,ch).Data(), "goff");

  ofstream fo;
  fo.open(TString::Format("hist_mod%02d_ch%02d.txt",mod,ch).Data());
  for(int i=0;i<8192;i++){
    fo << i << " " << h1->GetBinContent(i+1) << endl;
  }

  fo.close();
}

//
void eff_cali_single(int mod, int ch)
{
  //
  map<double, double> m_133Ba;
  m_133Ba.insert(std::make_pair(80.999, 34.06));
  m_133Ba.insert(std::make_pair(276.404, 7.26));
  m_133Ba.insert(std::make_pair(302.858, 18.58));
  m_133Ba.insert(std::make_pair(356.014, 62.1));
  m_133Ba.insert(std::make_pair(383.859, 9.41));
  
  map<double, pair<double, double>> m_133Ba_x1x2;
  m_133Ba_x1x2[80.999] = make_pair(0.98, 1.02);
  m_133Ba_x1x2[276.404] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[302.858] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[356.014] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[383.859] = make_pair(0.99, 1.01);

  //
  map<double, double> m_152Eu;
  m_152Eu.insert(std::make_pair(121.783, 28));
  m_152Eu.insert(std::make_pair(244.692, 7.4));
  m_152Eu.insert(std::make_pair(344.275, 26.2));
  m_152Eu.insert(std::make_pair(411.115, 3.2));
  m_152Eu.insert(std::make_pair(443.976, 3.04));
  m_152Eu.insert(std::make_pair(778.303, 12.7));
  m_152Eu.insert(std::make_pair(867.388, 4.09));
  m_152Eu.insert(std::make_pair(964.131, 14.23));
  m_152Eu.insert(std::make_pair(1112.116, 13.35));
  m_152Eu.insert(std::make_pair(1408.001, 20.57));

  map<double, pair<double, double>> m_152Eu_x1x2;
  m_152Eu_x1x2[121.783] = make_pair(0.99, 1.01);
  m_152Eu_x1x2[244.692] = make_pair(0.99, 1.01);
  m_152Eu_x1x2[344.275] = make_pair(0.99, 1.01);
  m_152Eu_x1x2[411.115] = make_pair(0.991, 1.009);
  m_152Eu_x1x2[443.976] = make_pair(0.991, 1.009);
  m_152Eu_x1x2[778.303] = make_pair(0.992, 1.008);
  m_152Eu_x1x2[867.388] = make_pair(0.994, 1.004);
  m_152Eu_x1x2[964.131] = make_pair(0.994, 1.004);
  m_152Eu_x1x2[1112.116] = make_pair(0.998, 1.002);
  m_152Eu_x1x2[1408.001] = make_pair(0.998, 1.002);


  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);

  TH1D *h1 = new TH1D("h1", TString::Format("ge_mod%02d_ch%02d",mod,ch).Data(), 8192, 0, 4096);
  tr->Draw("energy>>h1", TString::Format("mod==%d&&ch==%d",mod,ch).Data(), "goff");

  TSpectrum *sp = new TSpectrum();
  TH1D *h_back = (TH1D*)sp->Background(h1);
  h_back->SetLineColor(1);

  TH1D *h_sub = (TH1D*)h1->Clone("h_sub");

  h_sub->Add(h_back, -1);
  h_sub->SetLineColor(4);
  cc->cd();
  h_sub->Draw();

  int b1 = 0;
  int b2 = 0;
  int b_max = 0;
  //
  for(auto it=m_133Ba.begin();it!=m_133Ba.end();it++){
    double x1 = it->first-20.;
    double x2 = it->first+20.;
    h_sub->GetXaxis()->SetRangeUser(x1, x2);
    h_sub->Fit("gaus", "", "", it->first*m_133Ba_x1x2[it->first].first, it->first*m_133Ba_x1x2[it->first].second);

    b_max = (int)it->first*2;
    while(1){
      if(h_sub->GetBinContent(b_max) < h_sub->GetBinContent(b_max+1)){
        b_max++;
      }else{
        break;
      }
    }
    while(1){
      if(h_sub->GetBinContent(b_max) < h_sub->GetBinContent(b_max-1)){
        b_max--;
      }else{
        break;
      }
    }
    cout << h_sub->GetBinContent(b_max) << endl;
  
    TF1 *tf = ((TF1*)(gROOT->GetListOfFunctions()->FindObject("gaus")));
    cout << tf->GetParameter(2) << endl; 
    int b1 = (int)((tf->GetParameter(1)-2.0*tf->GetParameter(2)+0.5)*2.);
    int b2 = (int)((tf->GetParameter(1)+2.0*tf->GetParameter(2)+0.5)*2.);
    cout << "b1 " << b1 << " " << h_sub->GetBinContent(b1) << endl;
    cout << "b2 " << b2 << " " << h_sub->GetBinContent(b2) << endl;

    TLine *l1 = new TLine(h_sub->GetBinCenter(b1), 0., h_sub->GetBinCenter(b1), h_sub->GetBinContent(b_max));
    TLine *l2 = new TLine(h_sub->GetBinCenter(b2), 0., h_sub->GetBinCenter(b2), h_sub->GetBinContent(b_max));
    l1->SetLineColor(1);
    l1->SetLineWidth(2);
    l1->SetLineStyle(2);
    l2->SetLineColor(1);
    l2->SetLineWidth(2);
    l2->SetLineStyle(2);
    l1->Draw("same");
    l2->Draw("same");
    
    cc->Update();
    cc->SaveAs(TString::Format("./png/133Ba_%dkeV.png",(int)it->first).Data());
  }

  //
  for(auto it=m_152Eu.begin();it!=m_152Eu.end();it++){
    double x1 = it->first-20.;
    double x2 = it->first+20.;
    h_sub->GetXaxis()->SetRangeUser(x1, x2);
    h_sub->Fit("gaus", "", "", it->first*m_152Eu_x1x2[it->first].first, it->first*m_152Eu_x1x2[it->first].second);

    b_max = (int)it->first*2;
    while(1){
      if(h_sub->GetBinContent(b_max) < h_sub->GetBinContent(b_max+1)){
        b_max++;
      }else{
        break;
      }
    }
    while(1){
      if(h_sub->GetBinContent(b_max) < h_sub->GetBinContent(b_max-1)){
        b_max--;
      }else{
        break;
      }
    }
    cout << h_sub->GetBinContent(b_max) << endl;
  
    TF1 *tf = ((TF1*)(gROOT->GetListOfFunctions()->FindObject("gaus")));
    cout << tf->GetParameter(2) << endl; 
    int b1 = (int)((tf->GetParameter(1)-2.0*tf->GetParameter(2)+0.5)*2.);
    int b2 = (int)((tf->GetParameter(1)+2.0*tf->GetParameter(2)+0.5)*2.);
    cout << "b1 " << b1 << " " << h_sub->GetBinContent(b1) << endl;
    cout << "b2 " << b2 << " " << h_sub->GetBinContent(b2) << endl;

    TLine *l1 = new TLine(h_sub->GetBinCenter(b1), 0., h_sub->GetBinCenter(b1), h_sub->GetBinContent(b_max));
    TLine *l2 = new TLine(h_sub->GetBinCenter(b2), 0., h_sub->GetBinCenter(b2), h_sub->GetBinContent(b_max));
    l1->SetLineColor(1);
    l1->SetLineWidth(2);
    l1->SetLineStyle(2);
    l2->SetLineColor(1);
    l2->SetLineWidth(2);
    l2->SetLineStyle(2);
    l1->Draw("same");
    l2->Draw("same");
    
    cc->Update();
    cc->SaveAs(TString::Format("./png/152Eu_%dkeV.png",(int)it->first).Data());
  }

  //get_spec_data(mod, ch);
  // draw_spec(mod, ch);
}
