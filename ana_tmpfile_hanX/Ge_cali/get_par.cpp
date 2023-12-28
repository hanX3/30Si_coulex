
void get_par_single(int run, int mod, int ch)
{
  TString str_tmp, str_out;
  TH1D *h1;

  stringstream ss;

  str_tmp = Form("../raw2hist/rootfile/run%05d_raw_spe.root", run);
  TFile *f = new TFile(str_tmp.Data());
  if(f==NULL){
    cout << "open file " << str_tmp.Data() << " error!!!" << endl;
    return -1;
  }


  ss.str("");
  ss << "mod" << mod;
  gFile->cd(ss.str().c_str());

  str_tmp = Form("h_raw_mod%d_ch%d", mod, ch);
  cout << "analysis " << str_tmp << endl;
  h1 = (TH1D*)gDirectory->Get(str_tmp.Data());
  Float_t par[4] = {0.0};
  auto_cali(h1, par);
  str_out = Form("%-d\t%-2d\t%-10.6f\t%-10.6f\t%-12.9f\t%-g", mod, ch, par[0], par[1], par[2], par[3]);

  cout << str_out << endl;
}

void get_par_all(int run)
{
  ofstream ofs("ener_cal.dat");
  TString str_tmp, str_out;
  TH1D *h1;

  stringstream ss;

  str_tmp = Form("./raw2hist/rootfile/run%05d_raw_spe.root", run);
  TFile *f = new TFile(str_tmp.Data());
  if(f==NULL){
    cout << "open file " << str_tmp.Data() << " error!!!" << endl;
    return -1;
  }
  for(int i=0;i<5;i++){
    ss.str("");
    ss << "mod" << i;
    gFile->cd(ss.str().c_str());

    for(int j=0;j<16;j++){
      str_tmp = Form("h_raw_mod%d_ch%d", i, j);
      cout << "analysis " << str_tmp << endl;
      h1 = (TH1D*)gDirectory->Get(str_tmp.Data());
      Float_t par[4] = {0.0};
      auto_cali(h1, par);
      //cal and save pars into files
      str_out = Form("%-d\t%-2d\t%-10.6f\t%-10.6f\t%-12.9f\t%-g", i, j, par[0], par[1], par[2], par[3]);
      ofs << str_out << endl;
    }
  }
  ofs.close();
}
