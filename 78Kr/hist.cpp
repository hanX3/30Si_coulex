
//fitroutine(400, 500, 1000, 450, 5);
//fitroutine(500, 600, 1000, 562, 5);
//fitroutine(600, 680, 1000, 664, 5);
//fitroutine(680, 760, 1000, 693, 5);
//fitroutine(800, 900, 1000, 859, 5);
//fitroutine(1100, 1200, 1000, 1148, 5);
//fitroutine(1250, 1350, 1000, 1301, 5);


TH1D *h1 = new TH1D("h1", "131-160 angle", 512, 0, 2048);
TH1D *h2 = new TH1D("h2", "131-160 angle", 512, 0, 2048);

// Function parameters are passed as an array to TF1. Here, we
// define the position of each parameter in this array.
// Note: N_PAR will give us the total number of parameters. Make
// sure it is always the last entry!
enum ParIndex_t
{
  bkg0=0, bkg1=1, bkg2,
  sig_scale, sig_mean, sig_sigma,
  n_par
};

// Quadratic background function
Double_t background(Double_t *x, Double_t *par)
{
  return par[bkg0] + par[bkg1]*x[0] + par[bkg2]*x[0]*x[0];
}

//Gauss Peak function
Double_t signal(Double_t *x, Double_t *par)
{
  return par[sig_scale]*TMath::Gaus(x[0], par[sig_mean], par[sig_sigma], true);
}

//Sum of background and peak function. We pass x and the fit parameters
//down to the signal and background functions
Double_t fitfunction(Double_t *x, Double_t *par)
{
  return background(x, par) + signal(x, par);
}

//
void hist()
{
  ifstream fi;
  fi.open("../../data/78Kr/78Kr.txt");
  if(!fi){
    cout << "cannot open file." << endl;
  }

  vector<double> v_a;
  vector<double> v_b;
  double a, b;
  while(1){
    fi >> a >> b;
    if(!fi.good())  break;
    v_a.push_back(a);
    v_b.push_back(b);
  }

  cout << v_a.size() << endl;
  for(int i=0;i<v_a.size();i++){
    for(int j=0;j<v_b[i];j++){
      h1->Fill(v_a[i]); 
    }
  }

  TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 490, 360);
  c1->cd();
  h1->Draw();

  for(int i=0;i<512;i++){
    h2->SetBinContent(i+1, h1->GetBinContent(i+1));
  }

  fi.close();

  return;
}

void fitroutine(float fit_xmin, float fit_xmax, float fit_scale, float fit_mean, float fit_sigma)
{
  TF1 fit_fcn("fit_fcn", fitfunction, fit_xmin, fit_xmax, n_par);

  fit_fcn.SetParameter(0, 0.);
  fit_fcn.SetParameter(1, 0.);
  fit_fcn.SetParameter(2, 0.);
  fit_fcn.SetParameter(3, fit_scale);
  fit_fcn.SetParameter(4, fit_mean);
  fit_fcn.SetParameter(5, fit_sigma);
  h1->Fit("fit_fcn", "VR+", "");

  //
  TF1 back_fcn("back_fcn", background, fit_xmin, fit_xmax, n_par);
  back_fcn.SetLineColor(kGreen);
  TF1 signal_fcn("signal_fcn", signal, fit_xmin, fit_xmax, n_par);
  signal_fcn.SetLineColor(kBlue);

  Double_t par[n_par];
  fit_fcn.GetParameters(par);
  back_fcn.SetParameters(par);
  signal_fcn.SetParameters(par);
  back_fcn.DrawCopy("same");
  signal_fcn.DrawCopy("same");

  double binwidth = h1->GetXaxis()->GetBinWidth(1);
  double integral = signal_fcn.Integral(fit_xmin, fit_xmax);
  double integral_error = signal_fcn.IntegralError(fit_xmin, fit_xmax);
  cout << "number of signal events = " << integral/binwidth << "  " << integral_error/binwidth << endl;

  return;
}

















