//
TFile *fi = TFile::Open("../rootfile/build_r804_825.root");
TTree *tr_event = (TTree*)fi->Get("tr_event");

//
void draw_ring()
{

  TH1D *h1_ring[24];
  for(int i=0;i<24;i++){
    h1_ring[i] = new TH1D(TString::Format("h1_ring%02d",i).Data(), TString::Format("h1_ring%02d",i).Data(), 2000, 0, 40000);

    tr_event->Draw(TString::Format("Si_ring_adc>>h1_ring%02d",i).Data(), TString::Format("n_Si_ring==1&&n_Si_sector==1&&Si_ring_id==%d",i).Data(), "goff");
    
  }

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  for(int i=0;i<24;i++){
    h1_ring[i]->SetLineColor(20+i);
    if(i==0){
      h1_ring[0]->Draw();
    }else{
      h1_ring[i]->Draw("same");
    }
  }
}

//
void draw_sector()
{

  TH1D *h1_sector[32];
  for(int i=0;i<32;i++){
    h1_sector[i] = new TH1D(TString::Format("h1_sector%02d",i).Data(), TString::Format("h1_sector%02d",i).Data(), 2000, 0, 40000);

    tr_event->Draw(TString::Format("Si_sector_adc>>h1_sector%02d",i).Data(), TString::Format("n_Si_sector==1&&n_Si_sector==1&&Si_sector_id==%d",i).Data(), "goff");
    
  }

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  for(int i=0;i<32;i++){
    h1_sector[i]->SetLineColor(20+i);
    if(i==0){
      h1_sector[0]->Draw();
    }else{
      h1_sector[i]->Draw("same");
    }
  }
}
