//modified sector to ring12--mod5ch11
void cali_sector(int run_num, int ts_window)
{
  //x1=200,x2=2000 for source data
  //hx1=0, hx2=4096 for source data
  //hy1=0, hy2=4096 for source data
  /*
  double x1 = 200;
  double x2 = 2000;
  double hx1 = 0; 
  double hx2 = 4096; 
  double hy1 = 0; 
  double hy2 = 4096; 
  */

  //x1=2000,x2=30000 for inbeam data
  //hx1=0, hx2=4096 for source data
  //hy1=0, hy2=4096 for source data
  double x1 = 2000;
  double x2 = 30000;
  double hx1 = 0; 
  double hx2 = 32768; 
  double hy1 = 0; 
  double hy2 = 32768; 

  TFile *file_in;
  TString str_file_in;
  str_file_in = TString::Format("../rootfile/run%05d_build_%dns.root", run_num, ts_window);
  file_in = TFile::Open(str_file_in.Data());

  ofstream file_out;
  TString str_file_out;
  str_file_out = TString::Format("run%05d_si_cali.txt", run_num);
  file_out.open(str_file_out.Data(), std::ofstream::out | std::ofstream::app);
  
  TTree *tr_Si = (TTree*)file_in->Get("tr_Si");
  TH2D *h2[32];
  TCanvas *c2[32];
  TGraph *gr[32];
  TF1 *tf1[32];
  
  int n = 0;

  //sector01--mod07ch00
  //sector02--mod07ch01
  //sector03--mod07ch02
  //sector04--mod07ch03
  //sector05--mod07ch04
  //sector06--mod07ch05
  //sector07--mod07ch06
  //sector08--mod07ch07
  //sector09--mod07ch08
  //sector10--mod07ch09
  //sector11--mod07ch10
  //sector12--mod07ch11
  //sector13--mod07ch12
  //sector14--mod07ch13
  //sector15--mod07ch14
  //sector16--mod07ch15--empty
  //sector17--mod08ch00--empty
  //sector18--mod08ch01
  //sector19--mod08ch02
  //sector20--mod08ch03
  //sector21--mod08ch04
  //sector22--mod08ch05
  //sector23--mod08ch06
  //sector24--mod08ch07--mod06ch14
  //sector25--mod08ch08
  //sector26--mod08ch09
  //sector27--mod08ch10
  //sector28--mod08ch11
  //sector29--mod08ch12
  //sector30--mod08ch13
  //sector31--mod08ch14
  //sector32--mod08ch15--mod06ch15
  
  TString str_h2_name, str_h2_title;
  TString str_draw, str_cut;
  TString str_cc_name, str_cc_title;
  TString str_tf1_name;
  int mod_sector, ch_sector;

  for(int i=0;i<32;i++){
    mod_sector = i/16 + 7;
    ch_sector = i - 16*(mod_sector-7);
    if(mod_sector==8 && ch_sector==7){
      mod_sector = 6;
      ch_sector = 14;
    }
    if(mod_sector==8 && ch_sector==15){
      mod_sector = 6;
      ch_sector = 15;
    }
    cout << "mod_sector " << mod_sector << "  ch_sector " << ch_sector << endl;

    str_h2_name = TString::Format("h2_ring12_sector%02d", i+1);
    str_h2_title = TString::Format("h2_ring12_sector%02d", i+1);

    h2[i] = new TH2D(str_h2_name.Data(), str_h2_title.Data(), 2048, hx1, hx2, 2048, hy1, hy2);
    str_draw = TString::Format("Si_ring_adc:Si_sector_adc>>%s", str_h2_name.Data());
    str_cut = TString::Format("n_Si_ring==1&&n_Si_sector==1&&Si_ring_mod==5&&Si_ring_ch==11&&Si_sector_mod==%d&&Si_sector_ch==%d", mod_sector, ch_sector);
    cout << str_h2_name.Data() << endl;
    cout << str_h2_title.Data() << endl;
    cout << str_draw.Data() << endl;
    cout << str_cut.Data() << endl;
    cout << endl;

    n = tr_Si->Draw(str_draw.Data(), str_cut.Data(), "col");
    cout << "n " << n << endl;
    gr[i] = new TGraph(n, tr_Si->GetV2(), tr_Si->GetV1());

    str_cc_name = TString::Format("cc_ring12_sector%02d", i+1);
    str_cc_title = TString::Format("cc_ring12_sector%02d", i+1);
    c2[i] = new TCanvas(str_cc_name.Data(), str_cc_title.Data(), 0, 0, 480, 360);
    c2[i]->cd();
    gr[i]->Draw("ap");

    str_tf1_name = TString::Format("tf1_ring12_sector%02d", i+1);
    tf1[i] = new TF1(str_tf1_name.Data(), "pol1", x1, x2);
    tf1[i]->SetLineColor(kGray);
    gr[i]->Fit(str_tf1_name.Data(), "ROB");
    tf1[i]->Draw();
    h2[i]->Draw("same colz");
    c2[i]->SaveAs(TString::Format("./png/%s.png", str_cc_name.Data()).Data());

    cout << mod_sector << " " << ch_sector << " " << tf1[i]->GetParameter(0) << " " << tf1[i]->GetParameter(1) << endl;
    file_out << mod_sector << " " << ch_sector << " " << tf1[i]->GetParameter(0) << " " << tf1[i]->GetParameter(1) << endl;
  }

  file_out.close();
}

//modified ring to sector1--mod7ch00
void cali_ring(int run_num, int ts_window)
{
  ifstream fi;
  fi.open(TString::Format("run%05d_si_cali.txt",run_num).Data());
  int a, b;
  double par0, par1;
  fi >> a >> b >> par0 >> par1;
  cout << "par0 " << par0 << " par1 " << par1 << endl;
  fi.close();

  //x1=200,x2=2000 for source data
  //hx1=0, hx2=4096 for source data
  //hy1=0, hy2=4096 for source data
  double x1 = 200;
  double x2 = 2000;

  double hx1 = 0; 
  double hx2 = 4096; 
  double hy1 = 0; 
  double hy2 = 4096; 

  //x1=2000,x2=30000 for inbeam data
  //hx1=0, hx2=4096 for source data
  //hy1=0, hy2=4096 for source data
  /*
  double x1 = 2000;
  double x2 = 30000;
  double hx1 = 0; 
  double hx2 = 32768; 
  double hy1 = 0; 
  double hy2 = 32768; 
  */

  TFile *file_in;
  TString str_file_in;
  str_file_in = TString::Format("../rootfile/run%05d_build_%dns.root", run_num, ts_window);
  file_in = TFile::Open(str_file_in.Data());

  ofstream file_out;
  TString str_file_out;
  str_file_out = TString::Format("run%05d_si_cali.txt", run_num);
  file_out.open(str_file_out.Data(), std::ofstream::out | std::ofstream::app);

  TTree *tr_Si = (TTree*)file_in->Get("tr_Si");

  TH2D *h2[24];
  TCanvas *c2[24];
  TGraph *gr[24];
  TF1 *tf1[24];
  
  int n = 0;

  //ring01--mod05ch00
  //ring02--mod05ch01
  //ring03--mod05ch02
  //ring04--mod05ch03
  //ring05--mod05ch04
  //ring06--mod05ch05
  //ring07--mod05ch06
  //ring08--mod05ch07
  //ring09--mod05ch08
  //ring10--mod05ch09
  //ring11--mod05ch10
  //ring12--mod05ch11
  //ring13--mod05ch12
  //ring14--mod05ch13
  //ring15--mod05ch14
  //ring16--mod05ch15
  //ring17--mod06ch00
  //ring18--mod06ch01
  //ring19--mod06ch02
  //ring20--mod06ch03
  //ring21--mod06ch04
  //ring22--mod06ch05
  //ring23--mod06ch06
  //ring24--mod06ch07

  TString str_h2_name, str_h2_title;
  TString str_draw, str_cut;
  TString str_cc_name, str_cc_title;
  TString str_tf1_name;
  int mod_ring, ch_ring;

  for(int i=0;i<24;i++){
    mod_ring = i/16 + 5;
    ch_ring = i - 16*(mod_ring-5);
    cout << "mod_ring " << mod_ring << "  ch_ring " << ch_ring << endl;

    str_h2_name = TString::Format("h2_ring%02d_sector01", i+1);
    str_h2_title = TString::Format("h2_ring%02d_sector01", i+1);

    h2[i] = new TH2D(str_h2_name.Data(), str_h2_title.Data(), 2048, hx1, hx2, 2048, hy1, hy2);
    str_draw = TString::Format("Si_ring_adc:(%f+%f*Si_sector_adc)>>%s", par0, par1, str_h2_name.Data());
    str_cut = TString::Format("n_Si_ring==1&&n_Si_sector==1&&Si_ring_mod==%d&&Si_ring_ch==%d&&Si_sector_mod==7&&Si_sector_ch==0", mod_ring, ch_ring);
    cout << str_h2_name.Data() << endl;
    cout << str_h2_title.Data() << endl;
    cout << str_draw.Data() << endl;
    cout << str_cut.Data() << endl;
    cout << endl;

    n = tr_Si->Draw(str_draw.Data(), str_cut.Data(), "col");
    cout << "n " << n << endl;
    gr[i] = new TGraph(n, tr_Si->GetV1(), tr_Si->GetV2());//attention

    str_cc_name = TString::Format("cc_ring%02d_sector01", i+1);
    str_cc_title = TString::Format("cc_ring%02d_sector01", i+1);
    c2[i] = new TCanvas(str_cc_name.Data(), str_cc_title.Data(), 0, 0, 480, 360);
    c2[i]->cd();
    gr[i]->Draw("ap");

    str_tf1_name = TString::Format("tf1_ring%02d_sector01", i+1);
    tf1[i] = new TF1(str_tf1_name.Data(), "pol1", x1, x2);
    tf1[i]->SetLineColor(kGray);
    gr[i]->Fit(str_tf1_name.Data(), "ROB");
    tf1[i]->Draw("same");
    //h2[i]->Draw("same colz");//attention
    //c2[i]->SaveAs(TString::Format("%s.png", str_cc_name.Data()).Data());

    cout << mod_ring << " " << ch_ring << " " << tf1[i]->GetParameter(0) << " " << tf1[i]->GetParameter(1) << endl;
    file_out << mod_ring << " " << ch_ring << " " << tf1[i]->GetParameter(0) << " " << tf1[i]->GetParameter(1) << endl;
  }

  file_out << endl;
  file_out.close();
}

