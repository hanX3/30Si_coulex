void get_area_30Si()
{
  //gROOT->SetBatch(true);

  gROOT->ProcessLine(".L gamma_peak.cpp");
  
  //total
  //gROOT->ProcessLine("fit(\"../doppler/rootfile/rootfile_33/doppler_r804_825.root\", 2100, 2400, \"\")");
  
  /*
  TString r_cmd;
  for(int i=0;i<24;i++){
    if(i%4 != 0) continue;
    r_cmd = TString::Format("fit(\"../doppler/rootfile/rootfile_33/doppler_r804_825.root\",%d,%d,340,380,\"Q\")", i, i+3);
    gROOT->ProcessLine(r_cmd.Data());
  }
  */
}
