// tree convert to hist

TFile *fi;
TTree *tr;

TFile *fo;

//
int init_tree(int run)
{
  fi = TFile::Open(TString::Format("../../addback/rootfile/run%05d_addback.root",run).Data());
  if(!fi){
    cout << "cannot open input file" << endl;
    return -1;
  }

  tr = (TTree*)fi->Get("tree");
  if(!tr){
    cout << "cannot open tree" << endl;
    return -1;
  }
  
  fo = new TFile(TString::Format("./rootfile/run%05d_addback_hist.root",run).Data(), "recreate");
  if(!fo){
    cout << "cannot open input file" << endl;
    return -1;
  }

  return 0;
}

//
int init_tree(TString fi_name, TString fo_name)
{
  fi = TFile::Open(fi_name.Data());
  if(!fi){
    cout << "cannot open input file" << endl;
    return -1;
  }

  tr = (TTree*)fi->Get("tree");
  if(!tr){
    cout << "cannot open tree" << endl;
    return -1;
  }

  fo = new TFile(fo_name.Data(), "recreate");
  if(!fo){
    cout << "cannot open input file" << endl;
    return -1;
  }
  
  return 0;
}

//
void get_hist()
{
  gROOT->SetBatch(1);
  cout << tr->GetEntries() << endl;

  TCut useful_ge_mod0 = "(mod==0&&ch==0)||(mod==0&&ch==1)||(mod==0&&ch==2)||(mod==0&&ch==3)||(mod==0&&ch==4)||(mod==0&&ch==5)||(mod==0&&ch==6)||(mod==0&&ch==7)";
  TCut useful_ge_mod1 = "(mod==1&&ch==0)||(mod==1&&ch==1)||(mod==1&&ch==2)||(mod==1&&ch==3)||(mod==1&&ch==4)||(mod==1&&ch==5)||(mod==1&&ch==6)||(mod==1&&ch==7)";
  TCut useful_ge_mod2 = "(mod==2&&ch==0)||(mod==2&&ch==1)||(mod==2&&ch==4)||(mod==2&&ch==8)||(mod==2&&ch==10)||(mod==2&&ch==11)";
  TCut useful_ge_mod3 = "(mod==3&&ch==0)||(mod==3&&ch==8)||(mod==3&&ch==9)||(mod==3&&ch==10)||(mod==3&&ch==11)";
  TCut useful_ge_mod4 = "(mod==4&&ch==0)||(mod==4&&ch==1)||(mod==4&&ch==2)||(mod==4&&ch==8)||(mod==4&&ch==9)||(mod==4&&ch==10)||(mod==4&&ch==11)";
 
  TCut useful_ge_ring1 = "(mod==0&&ch==0)||(mod==0&&ch==1)||(mod==0&&ch==2)||(mod==0&&ch==3)";
  TCut useful_ge_ring2 = "(mod==0&&ch==4)||(mod==0&&ch==5)||(mod==0&&ch==6)||(mod==0&&ch==7)";
  TCut useful_ge_ring3 = (useful_ge_mod2||useful_ge_mod3||useful_ge_mod4);
  TCut useful_ge_ring4 = "(mod==1&&ch==0)||(mod==1&&ch==1)||(mod==1&&ch==2)||(mod==1&&ch==3)";
  TCut useful_ge_ring5 = "(mod==1&&ch==4)||(mod==1&&ch==5)||(mod==1&&ch==6)||(mod==1&&ch==7)";

  //
  TString draw_command;
  TH1D *h_rings[5];
  for(int i=0;i<5;i++){
    h_rings[i] = new TH1D(TString::Format("h_ring%d",i+1).Data(), TString::Format("h_ring%d",i+1).Data(), 8192, 0, 4096);
    
    switch(i+1){
      case 1:
        tr->Draw("energy>>h_ring1", useful_ge_ring1, "goff");
        break;
      case 2:
        tr->Draw("energy>>h_ring2", useful_ge_ring2, "goff");
        break;
      case 3:
        tr->Draw("energy>>h_ring3", useful_ge_ring3, "goff");
        break;
      case 4:
        tr->Draw("energy>>h_ring4", useful_ge_ring4, "goff");
        break;
      case 5:
        tr->Draw("energy>>h_ring5", useful_ge_ring5, "goff");
        break;

      default:
        cout << "invalid ring number" << endl;
        break;
    }

    fo->cd();
    h_rings[i]->Write();
  }

  TH1D *h_all = (TH1D*)h_rings[0]->Clone("h_all");
  for(int i=1;i<5;i++){
    h_all->Add(h_rings[i]);
  }
  fo->cd();
  h_all->Write();

  fi->Close();
  fo->Close();
}
