{
  gROOT->ProcessLine(".L check_cali.cpp");
  gROOT->ProcessLine("mod0->cd()");
  gROOT->ProcessLine("check_cali(0, 0)");
  gROOT->ProcessLine("check_cali(0, 1)");
  gROOT->ProcessLine("check_cali(0, 2)");
  gROOT->ProcessLine("check_cali(0, 3)");
  gROOT->ProcessLine("check_cali(0, 4)");
  gROOT->ProcessLine("check_cali(0, 5)");
  gROOT->ProcessLine("check_cali(0, 6)");
  gROOT->ProcessLine("check_cali(0, 7)");

  gROOT->ProcessLine("gFile->cd()");
  gROOT->ProcessLine("mod1->cd()");
  gROOT->ProcessLine("check_cali(1, 0)");
  gROOT->ProcessLine("check_cali(1, 1)");
  gROOT->ProcessLine("check_cali(1, 2)");
  gROOT->ProcessLine("check_cali(1, 3)");
  gROOT->ProcessLine("check_cali(1, 4)");
  gROOT->ProcessLine("check_cali(1, 5)");
  gROOT->ProcessLine("check_cali(1, 6)");
  gROOT->ProcessLine("check_cali(1, 7)");

  gROOT->ProcessLine("gFile->cd()");
  gROOT->ProcessLine("mod2->cd()");
  gROOT->ProcessLine("check_cali(2, 0)");
  gROOT->ProcessLine("check_cali(2, 1)");
  gROOT->ProcessLine("check_cali(2, 3)");
  gROOT->ProcessLine("check_cali(2, 4)");
  gROOT->ProcessLine("check_cali(2, 8)");
  gROOT->ProcessLine("check_cali(2, 10)");
  gROOT->ProcessLine("check_cali(2, 11)");

  gROOT->ProcessLine("gFile->cd()");
  gROOT->ProcessLine("mod3->cd()");
  gROOT->ProcessLine("check_cali(3, 0)");
  gROOT->ProcessLine("check_cali(3, 8)");
  gROOT->ProcessLine("check_cali(3, 9)");
  gROOT->ProcessLine("check_cali(3, 10)");
  gROOT->ProcessLine("check_cali(3, 11)");

  gROOT->ProcessLine("gFile->cd()");
  gROOT->ProcessLine("mod4->cd()");
  gROOT->ProcessLine("check_cali(4, 0)");
  gROOT->ProcessLine("check_cali(4, 1)");
  gROOT->ProcessLine("check_cali(4, 2)");
  gROOT->ProcessLine("check_cali(4, 8)");
  gROOT->ProcessLine("check_cali(4, 9)");
  gROOT->ProcessLine("check_cali(4, 10)");
  gROOT->ProcessLine("check_cali(4, 11)");

  gROOT->ProcessLine(".q");
}
