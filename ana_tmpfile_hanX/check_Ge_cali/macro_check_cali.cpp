void macro_check_cali(int run)
{
  gROOT->SetBatch(1);
  gROOT->ProcessLine(".L check_cali.cpp");

  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 0)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 1)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 2)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 3)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 4)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 5)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 6)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 0, 7)",run).Data());

  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 0)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 1)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 2)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 3)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 4)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 5)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 6)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 1, 7)",run).Data());

  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 0)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 1)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 3)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 4)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 8)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 10)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 2, 11)",run).Data());

  gROOT->ProcessLine(TString::Format("check_cali(%d, 3, 0)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 3, 8)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 3, 9)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 3, 10)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 3, 11)",run).Data());

  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 0)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 1)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 2)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 8)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 9)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 10)",run).Data());
  gROOT->ProcessLine(TString::Format("check_cali(%d, 4, 11)",run).Data());

  gROOT->ProcessLine(".q");
}
