void get_area_196Pt()
{
  gROOT->SetBatch(true);

  gROOT->ProcessLine(".L gamma_peak.cpp");
  
  //total
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 340, 380, \"Q\")");
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 510, 560, \"Q\")");
  
  //ring1-8 --> id0-7
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 0, 7, 340, 380, \"Q\")");
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 0, 7, 510, 560, \"Q\")");

  //ring10-16 --> id9-15
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 9, 15, 340, 380, \"Q\")");
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 9, 15, 510, 560, \"Q\")");

  //ring17-24 --> id16-23
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 16, 23, 340, 380, \"Q\")");
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\", 16, 23, 510, 560, \"Q\")");

  TString r_cmd;
  for(int i=0;i<24;i++){
    if(i%4 != 0) continue;
    r_cmd = TString::Format("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\",%d,%d,340,380,\"Q\")", i, i+3);
    gROOT->ProcessLine(r_cmd.Data());
  }

  for(int i=0;i<24;i++){
    if(i%4 != 0) continue;
    r_cmd = TString::Format("fit(\"../doppler/rootfile/rootfile_51/doppler_r804_825.root\",%d,%d,510,560,\"Q\")", i, i+3);
    gROOT->ProcessLine(r_cmd.Data());
  }

}
