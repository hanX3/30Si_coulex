
//
Double_t LinFit(Double_t *dim, Double_t *par);
Double_t QuadFit(Double_t *dim, Double_t *par);  
Double_t PolyBg(Double_t *dim, Double_t *par, Int_t order);

Double_t StepBG(Double_t *dim, Double_t *par);
Double_t StepFunction(Double_t *dim, Double_t *par);

Double_t Gaus(Double_t *dim, Double_t *par);
Double_t DoubleGaus(Double_t *dim, Double_t *par);
Double_t SkewedGaus(Double_t *dim, Double_t *par);
Double_t Efficiency(Double_t *dim, Double_t *par);
Double_t PhotoPeak(Double_t *dim, Double_t *par);
Double_t PhotoPeakBG(Double_t *dim, Double_t *par);
Double_t PhotoPeakBGExcludeRegion(Double_t *dim, Double_t *par);

//
void fit(TString file_name, Double_t x_low, Double_t x_high, Option_t *opt = "");
void fit(TString file_name, Int_t r0, Int_t r1, Double_t x_low, Double_t x_high, Option_t *opt = "");
//
TH1D *GetHistTotal(TString file_name);
TH1D *GetHistRings(TString file_name, Int_t r0, Int_t r1);
void Fit(TH1D *h1, Double_t x_low, Double_t x_high, Double_t &area, Double_t &area_error, Option_t *opt = "");
bool InitParams(TF1 *tf, TH1 *h);

//
void gamma_peak()
{
  TF1 *tf_peak_bg = new TF1("photo_peak_bg", PhotoPeakBG, 400, 600, 10);
  TF1 *tf_peak = new TF1("photo_peak", Gaus, 400, 600, 10);
  TF1 *tf_skewed_gaus = new TF1("skewed_gaus", SkewedGaus, 400, 600, 10);
  TF1 *tf_step_func = new TF1("step_function", StepBG, 400, 600, 10);
  TF1 *tf_bg = new TF1("background", LinFit, 400, 600, 10);

  Double_t xlow, xhigh;
  tf_peak_bg->GetRange(xlow, xhigh);
  cout << "xlow " << xlow << " xhigh " << xhigh << endl;

  Double_t height, cent, sigma, R, beta, step, offset;
  height = 100000.;
  cent = 500.;
  sigma = 10.;
  R = 20.;
  step = 5.;
  beta = 5.;
  offset = 10.;

  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: R:    relative height of skewed gaus to gaus
  // - par[4]: beta: "skewedness" of the skewed gaussin
  // - par[5]: step: size of stepfunction step.
  // - par[6]: base bg height.
  tf_peak_bg->SetParameter(0, height);
  tf_peak_bg->SetParameter(1, cent);
  tf_peak_bg->SetParameter(2, sigma);
  tf_peak_bg->SetParameter(3, R);
  tf_peak_bg->SetParameter(4, beta);
  tf_peak_bg->SetParameter(5, step);
  tf_peak_bg->SetParameter(6, offset);

  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: R:    relative height of skewed gaus to gaus
  tf_peak->SetParameter(0, height);
  tf_peak->SetParameter(1, cent);
  tf_peak->SetParameter(2, sigma);
  tf_peak->SetParameter(3, R);

  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: relative height of skewed gaus to gaus
  // - par[4]: "skewedness" of the skewed gaussin
  tf_skewed_gaus->SetParameter(0, height);
  tf_skewed_gaus->SetParameter(1, cent);
  tf_skewed_gaus->SetParameter(2, sigma);
  tf_skewed_gaus->SetParameter(3, R);
  tf_skewed_gaus->SetParameter(4, beta);
  
  //  -par[0]: height of peak
  //  -par[1]: centroid of peak
  //  -par[2]: sigma of peak
  //  -par[3]: size of step in step function.
  tf_step_func->SetParameter(0, height);
  tf_step_func->SetParameter(1, cent);
  tf_step_func->SetParameter(2, sigma);
  tf_step_func->SetParameter(3, step);


  tf_bg->SetParameter(0, offset);


  TCanvas * cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  tf_peak_bg->SetLineColor(1);
  tf_peak->SetLineColor(2);
  tf_skewed_gaus->SetLineColor(4);
  tf_step_func->SetLineColor(8);
  tf_bg->SetLineColor(9);

  tf_peak_bg->Draw();
  tf_peak->Draw("same");
  tf_skewed_gaus->Draw("same");
  tf_step_func->Draw("same");
  tf_bg->Draw("same");

  //
  TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg->AddEntry(tf_peak_bg, "total");
  leg->AddEntry(tf_peak, "gaus");
  leg->AddEntry(tf_skewed_gaus, "skewed gaus");
  leg->AddEntry(tf_step_func, "step function");
  leg->AddEntry(tf_bg, "background");

  leg->Draw();
}

//
void fit(TString file_name, Double_t x_low, Double_t x_high,  Option_t *opt = "")
{
  TH1D *h1 = GetHistTotal(file_name.Data());

  Double_t area, area_error;
  Fit(h1, x_low, x_high, area, area_error, opt);

  printf("area: %02f\n", area);
  printf("area_error: %02f\n", area_error);
}

//
void fit(TString file_name, Int_t r0, Int_t r1, Double_t x_low, Double_t x_high,  Option_t *opt = "")
{
  TH1D *h1 = GetHistRings(file_name.Data(), r0, r1);

  Double_t area, area_error;
  Fit(h1, x_low, x_high, area, area_error, opt);

  printf("area: %02f\n", area);
  printf("area_error: %02f\n", area_error);
}

//
void Fit(TH1D *h1, Double_t x_low, Double_t x_high, Double_t &area, Double_t &area_error, Option_t *opt = "")
{
  TF1 *tf_peak_bg = new TF1("photo_peak_bg", PhotoPeakBG, x_low, x_high, 7);
  TF1 *tf_bg = new TF1("background", StepBG, x_low, x_high, 5);
  InitParams(tf_peak_bg, h1);

  TCanvas *cc2;
  if(gROOT->GetListOfCanvases()->FindObject("cc2")){
    cc2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("cc2");
  }else{
    cc2 = new TCanvas("cc2", "cc2", 0, 0, 480, 360);
  }
  cc2->cd();
  h1->Draw("hist");

  TVirtualFitter::SetMaxIterations(100000);
  
  TString options = opt;
  bool verbose = !options.Contains("Q");
  bool no_print = options.Contains("no-print");
  if(no_print) {
    options.ReplaceAll("no-print","");
  }

  if(h1->GetSumw2()->fN != h1->GetNbinsX()+2){
    h1->Sumw2();
  }

  TFitResultPtr fit_res = h1->Fit(tf_peak_bg, Form("%sLRSME", options.Data()));

  //fit_res.Get()->Print();
  printf("chi^2/NDF = %.02f\n", tf_peak_bg->GetChisquare()/(double)tf_peak_bg->GetNDF());

  if(!fit_res.Get()->IsValid()){
    printf("fit has failed, trying refit... ");
    //SetParameter(3,0.1);
    //SetParameter(4,0.01);
    //SetParameter(5,0.0);
    h1->GetListOfFunctions()->Last()->Delete();
    fit_res = h1->Fit(tf_peak_bg, Form("%sLRSME",options.Data())); //,Form("%sRSM",options.Data()))
    if(fit_res.Get()->IsValid()){
      printf("refit passed! \n");
    }else{
      printf(" refit also failed :( \n");
    }
  }

  //
  double bg_pars[5];
  bg_pars[0] = tf_peak_bg->GetParameters()[0];
  bg_pars[1] = tf_peak_bg->GetParameters()[1];
  bg_pars[2] = tf_peak_bg->GetParameters()[2];
  bg_pars[3] = tf_peak_bg->GetParameters()[5];
  bg_pars[4] = tf_peak_bg->GetParameters()[6];

  tf_bg->SetParameters(bg_pars);
  h1->GetListOfFunctions()->Print();
  tf_peak_bg->SetLineColor(2);
  tf_peak_bg->Draw("same");
  tf_bg->SetLineColor(1);
  tf_bg->Draw("same");

  area = tf_peak_bg->Integral(x_low,x_high) / h1->GetBinWidth(1);
  double bg_area = tf_bg->Integral(x_low, x_high) / h1->GetBinWidth(1);
  area -= bg_area;
  area_error = 0.;

  if(x_low>x_high){
    std::swap(x_low, x_high);
  }
  Double_t sum = h1->Integral(h1->GetXaxis()->FindBin(x_low), h1->GetXaxis()->FindBin(x_high)); // * h1->GetBinWidth(1);
  Double_t sum_error = TMath::Sqrt(sum);
  sum -= bg_area;

  area = sum;
  area_error = TMath::Sqrt(sum + bg_area);

  if(!verbose) {
    printf("hist: %s\n",h1->GetName());
    tf_peak_bg->Print();
  }

  tf_peak_bg->Copy(*h1->GetListOfFunctions()->FindObject(tf_peak_bg->GetName()));
  h1->GetListOfFunctions()->Add(tf_bg->Clone()); //use to be a clone.
  h1->GetListOfFunctions()->Print();

  tf_peak_bg->SetParent(0); //h1;
}

//
TH1D *GetHistTotal(TString file_name)
{
  TFile *fi = TFile::Open(file_name.Data());
  if(!fi){
    cout << "can not open root file" << endl;
    return nullptr;
  }

  TH1D *h, *h_bg;
  fi->cd();
  h = (TH1D*)gFile->Get("h_event_ge_doppler_all");
  h_bg = (TH1D*)gFile->Get("h_bg_ge_doppler_all");

  TH1D *hh = (TH1D*)h->Clone("h_event_sub_ge_doppler_all");
  hh->Add(h_bg, -1);

  TCanvas *cc;
  if(gROOT->GetListOfCanvases()->FindObject("cc")){
    cc = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("cc");
  }else{
    cc = new TCanvas("cc", "cc", 0, 0, 480, 360);
  }
  cc->cd();
  h->SetLineColor(1);
  h_bg->SetLineColor(4);
  hh->SetLineColor(2);
  h->Draw("");
  h_bg->Draw("same");
  hh->Draw("same");
  
  return hh;
}

//
TH1D *GetHistRings(TString file_name, Int_t r0, Int_t r1)
{
  TFile *fi = TFile::Open(file_name.Data());
  if(!fi){
    cout << "can not open root file" << endl;
    return nullptr;
  }

  TH1D *h[24], *h_bg[24];
  fi->cd();
  for(int i=r0;i<=r1;i++){
    h[i] = (TH1D*)gFile->Get(TString::Format("h_event_ge_doppler_all_si_ring%d",i).Data());
    h_bg[i] = (TH1D*)gFile->Get(TString::Format("h_bg_ge_doppler_all_si_ring%d",i).Data());
  }

  for(int i=r0;i<r1;i++){
    h[r1]->Add(h[i], 1.);
    h_bg[r1]->Add(h_bg[i], 1.);
  }

  TH1D *hh = (TH1D*)h[r1]->Clone(TString::Format("h_event_sub_ge_doppler_ring%d_ring%d",r0,r1).Data());
  hh->Add(h_bg[r1], -1);

  TCanvas *cc;
  if(gROOT->GetListOfCanvases()->FindObject("cc")){
    cc = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("cc");
  }else{
    cc = new TCanvas("cc", "cc", 0, 0, 480, 360);
  }
  cc->cd();
  h[r1]->SetLineColor(1);
  h_bg[r1]->SetLineColor(4);
  hh->SetLineColor(2);
  h[r1]->Draw("");
  h_bg[r1]->Draw("same");
  hh->Draw("same");
  
  return hh;
}

//
bool InitParams(TF1 *tf, TH1 *h)
{
  if(!h){
    printf("No histogram is associated yet, no initial guesses made\n");
    return false;
  }

  Double_t x_low, x_high;
  tf->GetRange(x_low, x_high);

  Int_t bin_low = h->GetXaxis()->FindBin(x_low);
  Int_t bin_high = h->GetXaxis()->FindBin(x_high);

  Double_t y_high = h->GetBinContent(bin_low);
  Double_t y_low = h->GetBinContent(bin_high);
  for(int x=1;x<5;x++) {
    y_high += h->GetBinContent(bin_low-x);
    y_low += h->GetBinContent(bin_high+x);
  }
  y_high /= 5.0;
  y_low /= 5.0;

  if(y_low>y_high){
    std::swap(y_low, y_high);
  }

  double x_largest = 0.;
  double y_largest = 0.;
  int i = bin_low;
  for(;i<=bin_high;i++) {
    if(h->GetBinContent(i) > y_largest) {
      y_largest = h->GetBinContent(i);
      x_largest = h->GetXaxis()->GetBinCenter(i);
    }
  }

  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: R:    relative height of skewed gaus to gaus
  // - par[4]: beta: "skewedness" of the skewed gaussin
  // - par[5]: step: size of stepfunction step.
  // - par[6]: base bg height.

  //limits.
  tf->SetParLimits(0, 0, y_largest*2);
  tf->SetParLimits(1, x_low, x_high);
  tf->SetParLimits(2, 0.1, x_high-x_low);
  tf->SetParLimits(3, 0.0, 40);
  tf->SetParLimits(4, 0.01, 5);
  double step = (y_high-y_low)/y_largest*50;
  tf->SetParLimits(5, 0., step+step);
  printf(" y_high = %.02f \t y_low = %.02f \t step = %.02f\n", y_high, y_low, step); fflush(stdout);
  double offset = y_low;
  tf->SetParLimits(6, offset-0.5*offset, offset+offset);

  //Make initial guesses
  tf->SetParameter(0, y_largest);         //h->GetBinContent(bin));
  tf->SetParameter(1, x_largest);         //GetParameter("centroid"));
  tf->SetParameter(2, (x_largest*.01)/2.35);  //2,(x_high-x_low));     //2.0/bin_width); //
  tf->SetParameter(3, 5.);
  tf->SetParameter(4, 1.);
  tf->SetParameter(5, step);
  tf->SetParameter(6, offset);

  tf->SetParError(0, 0.10 * y_largest);
  tf->SetParError(1, 0.25);
  tf->SetParError(2, 0.10 *((x_largest*.01)/2.35));
  tf->SetParError(3, 5);
  tf->SetParError(4, 0.5);
  tf->SetParError(5, 0.10 * step);
  tf->SetParError(6, 0.10 * offset);

  return true;
}

//
Double_t PolyBg(Double_t *dim, Double_t *par, Int_t order)
{
  Double_t result = 0.0;
  int j=0;
  for(Int_t i=0;i<=order;i++) {
    result += *(par+j) *TMath::Power(dim[0],i);
    j++;
  }
  //result += par[i]*TMath::Power(dim[0]-par[order+1],i);
  return result;
}

//
Double_t LinFit(Double_t *dim, Double_t *par)
{
  return PolyBg(dim,par,1);
}

//
Double_t QuadFit(Double_t *dim, Double_t *par)
{
  return PolyBg(dim,par,2);
}

//
Double_t StepBG(Double_t *dim, Double_t *par)
{
  return StepFunction(dim,par) + PolyBg(dim,(par+4),0);
}

//
Double_t StepFunction(Double_t *dim, Double_t *par)
{
  //  -dim[0]: channels to fit
  //  -par[0]: height of peak
  //  -par[1]: centroid of peak
  //  -par[2]: sigma of peak
  //  -par[3]: size of step in step function.

  Double_t x       = dim[0];
  
  Double_t height  = par[0];
  Double_t cent    = par[1];
  Double_t sigma   = par[2];
  //Double_t R       = par[4];
  Double_t step    = par[3];

  //return TMath::Abs(step)*height/100.0*TMath::Erfc((x-cent)/(TMath::Sqrt(2.0)*sigma));
  return height*(step/100.0) *TMath::Erfc((x-cent)/(TMath::Sqrt(2.0)*sigma));
}

//
Double_t Gaus(Double_t *dim, Double_t *par)
{
  // - dim[0]: channels to fit
  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: relative height of skewed gaus to gaus

  Double_t x      = dim[0];
  Double_t height = par[0];
  Double_t cent   = par[1];
  Double_t sigma  = par[2];
  Double_t R      = par[3];

  return height*(1.0-R/100.0)*TMath::Gaus(x,cent,sigma);
}

//
Double_t DoubleGaus(Double_t *dim, Double_t *par)
{
  // - dim[0]: channels to fit
  // - par[0]: height of peak1
  // - par[1]: cent of peak1
  // - par[2]: height of peak2
  // - par[3]: cent of peak2
  // - par[4]: shared sigma
  // - par[5]: bg offset
  // - par[6]: bg slope

  Double_t x      = dim[0];
  Double_t height1 = par[0];
  Double_t cent1   = par[1];

  Double_t height2 = par[2];
  Double_t cent2   = par[3];
  
  Double_t sigma   = par[4];

  return height1*TMath::Gaus(x,cent1,sigma) + height2*TMath::Gaus(x,cent2,sigma) + PolyBg(dim,(par+5),2);
}


//
Double_t SkewedGaus(Double_t *dim,Double_t *par)
{

  // StepFunction(dim,par) + PolyBg
  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: relative height of skewed gaus to gaus
  // - par[4]: "skewedness" of the skewed gaussin

  Double_t x      = dim[0]; //channel number used for fitting
  Double_t height = par[0]; //height of photopeak
  Double_t cent   = par[1]; //Peak Centroid of non skew gaus
  Double_t sigma  = par[2]; //standard deviation of gaussian
  Double_t R      = par[3]; //relative height of skewed gaussian
  Double_t beta   = par[4]; //"skewedness" of the skewed gaussian

  double scaling = R*height/100.0;
  //double x_rel = (x - cent)/sigma;

  double fterm = (x-cent)/(sigma*TMath::Sqrt(2.));
  double sterm = sigma /  (beta *TMath::Sqrt(2.));

  return scaling * TMath::Exp((x-cent)/beta) * TMath::Erfc(fterm + sterm); 
}

//
Double_t PhotoPeakBG(Double_t *dim, Double_t *par)
{
  // - dim[0]: channels to fit
  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: relative height of skewed gaus to gaus
  // - par[4]: "skewedness" of the skewed gaussin
  // - par[5]: size of stepfunction step.
  // - par[6]: base bg height.
  // - par[7]: slope of bg.
  
  double spar[4];
  spar[0] = par[0];
  spar[1] = par[1];
  spar[2] = par[2];
  spar[3] = par[5];  //stepsize;

  return Gaus(dim,par) + SkewedGaus(dim,par) + StepFunction(dim,spar) + PolyBg(dim,par+6,0);
}

//
Double_t PhotoPeakBGExcludeRegion(Double_t *dim, Double_t *par)
{
  // - dim[0]: channels to fit
  // - par[0]: height of peak
  // - par[1]: cent of peak
  // - par[2]: sigma
  // - par[3]: relative height of skewed gaus to gaus
  // - par[4]: "skewedness" of the skewed gaussin
  // - par[5]: size of stepfunction step.
  
  // - par[6]: base bg height.
  
  // - par[7]: exclude low;
  // - par[8]: exclude high;

  if(dim[0]>par[7] && dim[0]<par[8]) {
    TF1::RejectPoint();
    return 0;
  }
  double spar[4];
  spar[0] = par[0];
  spar[1] = par[1];
  spar[2] = par[2];
  spar[3] = par[5];  //stepsize;
  return Gaus(dim,par) + SkewedGaus(dim,par) + StepFunction(dim,spar) + PolyBg(dim,par+6,0);
}

