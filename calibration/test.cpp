
void wait()
{
  if(!gROOT->IsBatch()){
    gPad->WaitPrimitive();
  }
}

void test()
{
  TCanvas c1("c1");
  TObject *obj;
  for(Int_t i=0;i<10;i++){
    wait();
    cout << "i = " << i << endl;
  }
}
