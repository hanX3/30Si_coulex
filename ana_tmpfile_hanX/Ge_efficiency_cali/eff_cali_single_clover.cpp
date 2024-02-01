//
TFile *fi1 = TFile::Open("../sort/rootfile/run01000_sort.root");
TFile *fi2 = TFile::Open("../addback/rootfile/run01000_addback.root");
TTree* tr[2];

//
std::map<int, std::vector<int>> m_id2mch;
std::map<double, double> m_133Ba;
std::map<double, std::pair<double, double>> m_133Ba_x1x2;
std::map<double, double> m_152Eu;
std::map<double, std::pair<double, double>> m_152Eu_x1x2;

//
void init()
{
  //
  tr[0] = (TTree*)fi1->Get("tree");
  tr[1] = (TTree*)fi2->Get("tree");

  m_id2mch.insert(make_pair(1, vector<int>{200,201,202,203}));
  m_id2mch.insert(make_pair(2, vector<int>{204,205,206,207}));
  m_id2mch.insert(make_pair(3, vector<int>{208,209,210,211}));
  m_id2mch.insert(make_pair(4, vector<int>{300,301,302,303}));
  m_id2mch.insert(make_pair(5, vector<int>{304,305,306,307}));
  m_id2mch.insert(make_pair(6, vector<int>{308,309,310,311}));
  m_id2mch.insert(make_pair(7, vector<int>{400,401,402,403}));
  m_id2mch.insert(make_pair(8, vector<int>{408,409,410,411}));

  //
  m_133Ba.insert(std::make_pair(80.999, 34.11));
  m_133Ba.insert(std::make_pair(302.858, 18.30));
  m_133Ba.insert(std::make_pair(356.014, 61.94));
  m_133Ba.insert(std::make_pair(383.859, 8.905));

  m_133Ba_x1x2[80.999] = make_pair(0.98, 1.02);
  m_133Ba_x1x2[276.404] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[302.858] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[356.014] = make_pair(0.99, 1.01);
  m_133Ba_x1x2[383.859] = make_pair(0.99, 1.01);

  //
  m_152Eu.insert(std::make_pair(121.783, 28.37));
  m_152Eu.insert(std::make_pair(244.692, 7.53));
  m_152Eu.insert(std::make_pair(344.275, 26.57));
  m_152Eu.insert(std::make_pair(411.115, 2.238));
  m_152Eu.insert(std::make_pair(443.976, 3.125));
  m_152Eu.insert(std::make_pair(778.303, 12.97));
  m_152Eu.insert(std::make_pair(867.388, 4.214));
  m_152Eu.insert(std::make_pair(964.131, 14.63));
  m_152Eu.insert(std::make_pair(1112.116, 13.54));
  m_152Eu.insert(std::make_pair(1408.001, 20.85));
  
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
}

//
void draw_spec(int clover_id)
{
  init();
  TH1D *h1 = new TH1D("h1", "", 8192, 0, 4096);
  TH1D *h2 = new TH1D("h2", "", 8192, 0, 4096);

  int mod = m_id2mch[clover_id][0]/100;
  int ch = m_id2mch[clover_id][0]%100;
  tr[0]->Draw("energy>>h1", TString::Format("mod==%d&&(ch==%d||ch==%d||ch==%d||ch==%d)",mod,ch,ch+1,ch+2,ch+3).Data(), "goff");
  tr[1]->Draw("energy>>h2", TString::Format("mod==%d&&(ch==%d||ch==%d||ch==%d||ch==%d)",mod,ch,ch+1,ch+2,ch+3).Data(), "goff");
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  h1->SetLineColor(4);
  h2->SetLineColor(2);
  h1->Draw();
  h2->Draw("same");
}

//
double eff_fun(double *x, double *p)
{
  double x1 = log(x[0]/100.);
  double x2 = log(x[0]/1000.);

  double z1 = pow(p[0]+p[1]*x1+p[2]*x1*x1, -p[6]);
  double z2 = pow(p[3]+p[4]*x2+p[5]*x2*x2, -p[6]);

  double eff = exp(pow(z1+z2, -1./p[6]));

  return eff;
}

//
double *eff_fit(map<double, double> &m)
{
  TF1 *tf = new TF1("tf", eff_fun, 50, 2000, 7);
  
  /*
  tf->SetParameters(5.42, 3.73, 0., 7.03, -0.65, -0.14, 15.);
  delete gROOT->GetListOfCanvases()->FindObject("cc");
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  tf->Draw();
  */

  TGraph *gr = new TGraph();

  int i = 0;
  for(auto it=m.begin();it!=m.end();it++){
    gr->SetPoint(i, it->first, it->second);
    i++;
  }

  delete gROOT->GetListOfCanvases()->FindObject("cc");
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  gr->Draw("AP*");

  tf->SetParameter(0, 5.);
  tf->SetParameter(1, 4.);
  tf->FixParameter(2, 0.);
  tf->SetParameter(3, 7.);
  tf->SetParameter(4, -0.5);
  tf->SetParameter(5, -0.1);
  tf->FixParameter(6, 15.);

  gr->Fit("tf");

  double *p = new double[7];
  for(int i=0;i<7;i++){
    p[i] = tf->GetParameter(i);
  }

  return p;
}

//
void eff_cali_single_clover(int clover_id, int tr_id)
{
  init();
  
  delete gROOT->GetListOfCanvases()->FindObject("cc");
  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);

  TH1D *h = new TH1D("h", TString::Format("clover%02d",clover_id).Data(), 8192, 0, 4096);

  int mod = m_id2mch[clover_id][0]/100;
  int ch = m_id2mch[clover_id][0]%100;
  tr[tr_id]->Draw("energy>>h", TString::Format("mod==%d&&(ch==%d||ch==%d||ch==%d||ch==%d)",mod,ch,ch+1,ch+2,ch+3).Data(), "goff");

  TSpectrum *sp = new TSpectrum();
  TH1D *h_back = (TH1D*)sp->Background(h);
  h_back->SetLineColor(1);

  TH1D *h_sub = (TH1D*)h->Clone("h_sub");
  h_sub->Add(h_back, -1);
  h_sub->SetLineColor(4);
  cc->cd();
  h_sub->Draw();

  double sum;
  ofstream fo;
  if(tr_id==0){
    fo.open(TString::Format("./dat/clover%02d_area.txt",clover_id).Data());
  }else{
    fo.open(TString::Format("./dat/clover%02d_area_ab.txt",clover_id).Data());
  }
  map<double, double> m_s;

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

    sum = 0;
    for(int i=b1;i<=b2;i++){
      sum += h_sub->GetBinContent(i);
    }
    m_s.insert(std::make_pair(it->first, sum)); 

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
    if(tr_id==0){
      cc->SaveAs(TString::Format("./png/133Ba_%dkeV.png",(int)it->first).Data());
    }else{
      cc->SaveAs(TString::Format("./png/133Ba_%dkeV_ab.png",(int)it->first).Data());
    }
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

    sum = 0;
    for(int i=b1;i<=b2;i++){
      sum += h_sub->GetBinContent(i);
    }
    m_s.insert(std::make_pair(it->first, sum)); 

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
    if(tr_id==0){
      cc->SaveAs(TString::Format("./png/152Eu_%dkeV.png",(int)it->first).Data());
    }else{
      cc->SaveAs(TString::Format("./png/152Eu_%dkeV_ab.png",(int)it->first).Data());
    }
  }

  //using 356.014(133Ba) and 344.275(152Eu) normlize
  map<double, double> m_s2;
  double frac = (m_s[356.014]/m_133Ba[356.014])/(m_s[344.275]/m_152Eu[344.275]);
  //double frac = 1.;
  cout << "frac " << frac << endl; 
  for(auto it=m_133Ba.begin();it!=m_133Ba.end();it++){
    m_s2.insert(std::make_pair(it->first, m_s[it->first]/it->second));
  }

  for(auto it=m_152Eu.begin();it!=m_152Eu.end();it++){
    m_s2.insert(std::make_pair(it->first, frac*m_s[it->first]/it->second));
  }

  for(auto it=m_s2.begin();it!=m_s2.end();it++){
    fo << it->first << " " << it->second << endl;
  }

  //
  double *par = eff_fit(m_s2);
  for(int i=0;i<7;i++){
    fo << i << " " << par[i] << std::endl; 
  }
  
  fo << endl;
  fo.close();

  delete [] par;
}

//
void eff_compare(int clover_id)
{
  //
  //eff_cali_single_clover(clover_id, 0); 
  //eff_cali_single_clover(clover_id, 1);

  ifstream fi[2];
  fi[0].open(TString::Format("./dat/clover%02d_area.txt",clover_id).Data()); 
  fi[1].open(TString::Format("./dat/clover%02d_area_ab.txt",clover_id).Data()); 

  TGraph *gr[2];
  TF1 *tf[2];

  double par[7];
  double e, s;
  for(int i=0;i<2;i++){
    if(!fi[i]){
      cout << "open file wrong" << endl;
      return;
    }

    //
    gr[i] = new TGraph();

    for(int j=0;j<14;j++){
      fi[i] >> e >> s;
      std::cout << e << " " << s << endl;
      gr[i]->SetPoint(j, e, s);
    }
    for(int j=0;j<7;j++){
      fi[i] >> s >> par[j];
      std::cout << par[j] << endl;
    }

    tf[i] = new TF1(TString::Format("tf%d",i+1).Data(), "eff_fun", 50, 2000, 7);
    tf[i]->SetParameters(par);
    
    gr[i]->SetMarkerStyle(5);
  }

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();

  gr[0]->SetMarkerColor(4);
  gr[1]->SetMarkerColor(2);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr[0]);
  mg->Add(gr[1]);
  tf[0]->SetLineColor(4);
  tf[1]->SetLineColor(2);

  gr[0]->GetYaxis()->SetRangeUser(0, 7000.);
  mg->Draw("ap");
  tf[0]->Draw("same");
  tf[1]->Draw("same");

  cc1->SaveAs("./png/single_clover.png");
}
