#define DEBUG 1

void get_his_raw(int runno)
{
  char filename[256];

  sprintf(filename, "../../../data/run%05d_tmp.root", runno);
  cout << "start ana " << filename << endl;

  TFile *fi;
  TTree *tr[5][16];
  fi = TFile::Open(filename);

  TH1D *h_raw[5][16];
  char tr_name[256];

  stringstream ss1, ss2;
  ss1.str("");
  ss2.str("");

  for(int i=0;i<5;i++){
    for(int j=0;j<16;j++){
      sprintf(tr_name, "tr_XIA_%02d_%02d", i, j);
      tr[i][j] = (TTree*)fi->Get(tr_name);

      ss1.str("");
      ss1 << "h_raw_mod" << i << "_ch" << j;
      h_raw[i][j] = new TH1D(ss1.str().c_str(), ss1.str().c_str(), 65536, 0, 65536);

      ss2.str("");
      ss2 << "Energy>>h_raw_mod" << i << "_ch" << j;
#if DEBUG
      cout << ss2.str() << endl;
#endif

      tr[i][j]->Draw(ss2.str().c_str());
    }
  }


  TDirectory *dir_mod[5];

  sprintf(filename, "./run%05d_raw_spe.root", runno);
  TFile *fo = new TFile(filename, "recreate");

  for(int i=0;i<5;i++){
    fo->cd();
    ss1.str("");
    ss1 << "mod" << i;
    dir_mod[i] = fo->mkdir(ss1.str().c_str());
    dir_mod[i]->cd();
    for(int j=0;j<16;j++){
      h_raw[i][j]->Write();
    }
  }

  fo->Close();
}
