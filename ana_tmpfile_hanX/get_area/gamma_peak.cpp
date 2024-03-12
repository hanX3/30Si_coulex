
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

