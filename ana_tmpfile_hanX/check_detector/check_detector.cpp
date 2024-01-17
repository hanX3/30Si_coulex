
void check_detector(int run, int mod)
{
  TString file_name;
  file_name = Form("../raw2hist/rootfile/run%05d_raw_spe.root", run);
  TFile *fi = TFile::Open(file_name.Data());
  if(fi->IsZombie()){
    cout << "can not open the file." << endl;
    return ;
  }

  stringstream ss;
  ss.str("");
  ss << "mod" << mod;
  gFile->cd(ss.str().c_str());

  TCanvas *cc = new TCanvas("cc", "cc", 0, 0, 1240, 660);
  cc->Divide(4, 3);

  TH1D *h[12];
  for(int i=0;i<12;i++){
    cout << "drawing " << TString::Format("h_raw_mod%d_ch%d", mod, i) << endl;
    h[i] = (TH1D*)gDirectory->Get(TString::Format("h_raw_mod%d_ch%d", mod, i).Data());

    cc->cd(i+1);
    cc->SetLogy();
    h[i]->GetXaxis()->SetRangeUser(0., 4000.);
    h[i]->Draw();
  }
}
