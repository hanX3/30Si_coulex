void draw(int run_num, int ts_window)
{
  /*
  //x1=0,x2=4096 for source
  double x1 = 0;
  double x2 = 4096;
  */

  //x1=0,x2=32768 for inbeam
  double x1 = 0;
  double x2 = 32768;

  gStyle->SetOptStat(0);

  TFile *file_in;
  TString str_file_in;
  str_file_in = TString::Format("../rootfile/run%05d_build_%dns.root", run_num, ts_window);
  file_in = TFile::Open(str_file_in.Data());

  //read Si_cali data
  std::map<int, vector<double>> map_si_cali_data;
  ifstream file_Si_cali;
  file_Si_cali.open(TString::Format("run%05d_si_cali.txt",run_num).Data());
  if(!file_Si_cali){
    cout << "can not open si_cali.txt" << endl;
    return ;
  }
  int mod, ch;
  double par0, par1;
  int key = 0;
  while(1){
    file_Si_cali >> mod >> ch >> par0 >> par1;
    if(!file_Si_cali.good()){
      break;
    }
    //cout << mod << " " << ch << " " << par0 << " " << par1 << endl;
    key = 100*mod+ch;
    vector<double> value;
    value.push_back(par0);
    value.push_back(par1);
    map_si_cali_data.insert(pair<int, vector<double>>(key, value));
  }

  std::map<int, vector<double>>::iterator it = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    std::cout << it->first << " => " << it->second[0] << " " << it->second[1] << '\n';
  }

  file_Si_cali.close();

  TTree *tr_Si = (TTree*)file_in->Get("tr_Si");

  int n = 0;
  TString str_h1_name, str_h1_title;
  TString str_draw, str_cut;

  TCanvas *c2[24+32];
  TH1D *h1[24+32];

  std::map<int, vector<double>>::iterator itt = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    int mod = it->first/100;
    int ch = it->first%100;

    cout << "mod " << mod << " ch " << ch << endl;
    cout << "par0 " << it->second[0] << " par1 " << it->second[1] << endl;

    h1[n] = new TH1D(TString::Format("h1%02d",n).Data(), TString::Format("h1_mod%02dch%02d",mod,ch).Data(), 2048, x1, x2);
    if(it->first<610){
      str_draw = TString::Format("%lf+%lf*Si_ring_adc>>h1%02d", it->second[0], it->second[1], n);
      str_cut = TString::Format("n_Si_ring==1&&Si_ring_mod==%d&&Si_ring_ch==%d", mod, ch);
      cout << str_draw.Data() << endl;
      cout << str_cut.Data() << endl;
    }else{
      str_draw = TString::Format("%lf+%lf*Si_sector_adc>>h1%02d", it->second[0], it->second[1], n);
      str_cut = TString::Format("n_Si_sector==1&&Si_sector_mod==%d&&Si_sector_ch==%d", mod, ch);
      cout << str_draw.Data() << endl;
      cout << str_cut.Data() << endl;
    }
    tr_Si->Draw(str_draw.Data(), str_cut.Data(), "col");

    c2[n] = new TCanvas(TString::Format("c2%02d",n).Data(), "", 0, 0, 480, 360);
    c2[n]->cd();
    h1[n]->Draw();

    n++;
  }

  TCanvas *c3 = new TCanvas("c3", "", 0, 0, 480, 360);
  c3->cd();
  for(int i=0;i<n;i++){
    if(i==0) h1[i]->Draw();
    else{
      h1[i]->SetLineColor(i+1);
      h1[i]->Draw("same");
    }
  }
}

