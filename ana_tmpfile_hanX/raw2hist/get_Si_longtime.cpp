
//
void get_Si_longtime()
{
  // ring
  int run_list[] = {804, 805, 806, 808, 809, 810, 811, 812, 815, 816, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 832, 833, 834, 835, 836, 837, 839, 840, 841, 842, 843, 845, 846, 847, 848, 849, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871, 872, 875, 876, 877, 878, 879, 880, 881, 882, 883, 884, 885, 886, 887, 888};
  int run_counts = sizeof(run_list)/sizeof(run_list[0]);
  cout << run_counts << endl;

  TFile *fi[run_counts];
  for(int j=0;j<run_counts;j++){
    fi[j] = TFile::Open(TString::Format("/mnt/user/ExpData/2021_IMP_30Si_196Pt/run%05d_tmp.root",run_list[j]).Data());
    if(fi[j]->IsZombie()){
      cout << "can not open the file " << j << "." << endl;
    }
  }
  TTree *tr_ring[24*70];
  TTree *tr_sector[32*70];
  UShort_t energy;

  // ring
  int mod = 0;
  int ch = 0;
  
  TH2D *hh[24+32]; 

  for(int i=0;i<24;i++){
    cout << i << endl;
    mod = 5 + i/16;
    ch = i%16;
    hh[i] = new TH2D(TString::Format("hh_ring%02d",i), "", 70, 0, 70, 16384, 0, 75536);
    for(int j=0;j<run_counts;j++){
      // cout << "ana run" << run_list[j] << endl;
      tr_ring[j+run_counts*i] = (TTree*)fi[j]->Get(TString::Format("tr_XIA_%02d_%02d",mod,ch).Data());
      tr_ring[j+run_counts*i]->SetBranchAddress("Energy", &energy); 
      for(int k=0;k<tr_ring[j+run_counts*i]->GetEntries();k++){
        tr_ring[j+run_counts*i]->GetEntry(k);
        // cout << "energy  " << energy << endl;
        hh[i]->Fill(j, energy);
      }
    }
  }

  for(int i=0;i<32;i++){
    cout << i << endl;
    mod = 7 + i/16;
    ch = i%16;
    if(i==23){
      mod = 6;
      ch =14;
    }
    if(i==31){
      mod = 6;
      ch =15;
    }
    hh[i+24] = new TH2D(TString::Format("hh_sector%02d",i), "", 70, 0, 70, 16384, 0, 75536);
    for(int j=0;j<run_counts;j++){
      // cout << "ana run" << run_list[j] << endl;
      tr_sector[j+run_counts*i] = (TTree*)fi[j]->Get(TString::Format("tr_XIA_%02d_%02d",mod,ch).Data());
      tr_sector[j+run_counts*i]->SetBranchAddress("Energy", &energy); 
      for(int k=0;k<tr_sector[j+run_counts*i]->GetEntries();k++){
        tr_sector[j+run_counts*i]->GetEntry(k);
        // cout << "energy  " << energy << endl;
        hh[i+24]->Fill(j, energy);
      }
    }
  }

  TFile *fo = new TFile("./rootfile/Si_longtime.root", "recreate");
  fo->cd();
  for(int i=0;i<24+32;i++){
    hh[i]->Write();
  }
  fo->Close();
}
