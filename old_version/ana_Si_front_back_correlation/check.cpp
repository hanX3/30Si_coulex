//modified sector to ring12--mod5ch11

void check()
{
  TFile *file_in;
  TString str_file_in;
  str_file_in = TString::Format("../ana_rootfile/run00804_ana.root");
  file_in = TFile::Open(str_file_in.Data());

  //read Si_cali data

  std::map<int, vector<double>> map_si_cali_data;
  ifstream file_Si_cali;
  file_Si_cali.open("run00804_si_cali.txt");
  if(!file_Si_cali){
    cout << "can not open run00804_si_cali.txt" << endl;
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

  TTree *tr1_Si = (TTree*)file_in->Get("tr1_Si");

  int n = 0;
  TString str_h1_name, str_h1_title;
  TString str_draw, str_cut;
  TCanvas *c2 = new TCanvas("c2", "c2", 0, 0, 480, 360);
  TCanvas *c3 = new TCanvas("c3", "c3", 0, 0, 480, 360);

  std::map<int, vector<double>>::iterator itt = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    if(it->first>610) continue;
    for(itt=map_si_cali_data.begin();itt!=map_si_cali_data.end();itt++){
      if(itt->first<610) continue;

      int mod1 = it->first/100;
      int ch1 = it->first%100;
      int mod2 = itt->first/100;
      int ch2 = itt->first%100;
      TH1D *h1 = new TH1D("h1", TString::Format("h1_mod%02dch%02d_mod%02dch%02d", mod1, ch1, mod2, ch2).Data(), 1000, -500, 500);
      TH2D *h2 = new TH2D("h2", TString::Format("h1_mod%02dch%02d_mod%02dch%02d", mod1, ch1, mod2, ch2).Data(), 1000, -500, 500, 2048, 0, 32768);
      str_draw = TString::Format("%lf+%lf*Si_ring_adc-%lf-%lf*Si_sector_adc>>h1", it->second[0], it->second[1], itt->second[0], itt->second[1]);
      str_cut = TString::Format("n_Si_ring==1&&n_Si_sector==1&&Si_ring_mod==%d&&Si_ring_ch==%d&&Si_sector_mod==%d&&Si_sector_ch==%d", mod1, ch1, mod2, ch2);
      tr1_Si->Draw(str_draw.Data(), str_cut.Data(), "col");
      c2->cd();
      h1->Draw();
      c2->SaveAs(TString::Format("h1_mod%02dch%02d_mod%02dch%02d.png", mod1, ch1, mod2, ch2).Data());
      if(h1) delete h1;

      str_draw = TString::Format("%lf+%lf*Si_sector_adc:(%lf+%lf*Si_ring_adc-%lf-%lf*Si_sector_adc)>>h2", itt->second[0], itt->second[1], it->second[0], it->second[1], itt->second[0], itt->second[1]);
      tr1_Si->Draw(str_draw.Data(), str_cut.Data(), "col");
      c3->cd();
      h2->Draw("col");
      c3->SaveAs(TString::Format("h2_mod%02dch%02d_mod%02dch%02d.png", mod1, ch1, mod2, ch2).Data());
      if(h2) delete h2;
    }
  }
}

