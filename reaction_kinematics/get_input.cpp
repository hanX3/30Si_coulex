//
vector<double> v_angle_si;
vector<double> v_angle_pt;
vector<double> v_energy_si;
vector<double> v_energy_pt;
vector<double> v_angle2_si;
vector<double> v_angle2_pt;

//
double ring_angle_down_stream[24];
double ring_angle_up_stream[24];

//
void get_data()
{
  //
  ifstream fi1;
  // fi1.open("./data_lise.txt");
  fi1.open("./data_lise_q.txt");

  string line;
  getline(fi1, line);

  double a, b, c, d;
  while(1){
    fi1 >> a >> b >> c >> d;
    // cout << a << " " << b << " " << c << " " << d << " " << endl;
    if(!fi1.good()) break;
  
    v_angle_si.push_back(a);
    v_energy_si.push_back(b);
    v_angle_pt.push_back(c);
    v_energy_pt.push_back(d);
  }
  fi1.close();

  //
  ifstream fi2;
  fi2.open("./data_angle_lise.txt");
  
  getline(fi2, line);
  while(1){
    fi2 >> a >> b;
    // cout << a << " " << b << endl;
    if(!fi2.good()) break;

    v_angle2_si.push_back(a);
    v_angle2_pt.push_back(b);
  }
  fi2.close();
}

//
void get_angle_info_down_stream(double dis)
{
  // downstream
  for(int i=0;i<24;i++){
    ring_angle_down_stream[i] = atan((11.+0.5*(double)i)/dis)/3.14159*180.;
  }
}

//
void get_angle_info_up_stream(double dis)
{
  // upstream
  for(int i=0;i<24;i++){
    ring_angle_up_stream[i] = 180. - atan((11.+0.5*(double)i)/dis)/3.14159*180.;
  }
}

//
void get_input_si()
{
  get_data();
  get_angle_info_down_stream(8.6);

  int n = v_energy_si.size();
  TGraph *gr = new TGraph(n);
  for(int i=0;i<n;i++){
    cout << v_angle_si[i] << " " << v_energy_si[i]  << endl;
    gr->SetPoint(i, v_angle_si[i], 30.*v_energy_si[i]);
  }
  gr->SetTitle("");
  gr->GetXaxis()->SetTitle("Angle 30Si in Lab");
  gr->GetYaxis()->SetTitle("Energy of 30Si [MeV]");

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  gr->Draw();

  gr->Fit("pol9");
  TF1 *tf = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol9");

  //
  ofstream fo;
  fo.open("input_si.txt");
  for(int i=0;i<24;i++){
    cout << ring_angle_down_stream[i] << endl;
    fo << ring_angle_down_stream[i] << " " << tf->Eval(ring_angle_down_stream[i]) << endl;
  }

  fo.close();
}

//
void get_input_pt()
{
  get_data();
  get_angle_info_down_stream(8.6);

  // gr1 30Si angle vs. 196Pt angle
  int n1 = v_angle2_si.size();
  TGraph *gr1 = new TGraph(n1);
  for(int i=0;i<n1;i++){
    // cout << v_angle2_si[i] << " " << v_angle2_pt[i] << endl;
    gr1->SetPoint(i, v_angle2_si[i], v_angle2_pt[i]);
  }
  gr1->SetTitle("");
  gr1->GetXaxis()->SetTitle("Angle 30Si in Lab");
  gr1->GetYaxis()->SetTitle("Angle 196Pt in Lab");

  TCanvas *cc1 = new TCanvas("cc1", "", 0, 0, 480, 360);
  cc1->cd();
  gr1->Draw();

  gr1->Fit("pol9", "", "", 20., 90.);
  TF1 *tf1 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol9");

  vector<double> v_angle3_pt;
  for(int i=0;i<24;i++){
    v_angle3_pt.push_back(tf1->Eval(ring_angle_down_stream[i]));
  }
  
  for(int i=0;i<24;i++){
    cout << v_angle3_pt[i] << endl;
  }

  //
  int n2 = v_energy_pt.size();
  vector<double> v_angle4_pt;
  vector<double> v_energy4_pt;
  for(int i=0;i<n2;i++){
    if(196.*v_energy_pt[i] < 1.0){
      continue;
    }else{
      v_angle4_pt.push_back(v_angle_pt[i]);
      v_energy4_pt.push_back(196.*v_energy_pt[i]); 
    }
  }

  int n4 = v_energy4_pt.size();
  TGraph *gr2 = new TGraph(n4);
  for(int i=0;i<n4;i++){
    gr2->SetPoint(i, v_angle4_pt[i], v_energy4_pt[i]);
  }

  gr2->SetTitle("");
  gr2->GetXaxis()->SetTitle("Angle 196Pt in Lab");
  gr2->GetYaxis()->SetTitle("Energy of 196Pt [MeV]");
  TCanvas *cc2 = new TCanvas("cc2", "", 0, 0, 480, 360);
  cc2->cd();
  gr2->Draw();
  
  gr2->Fit("pol9", "", "", 20., 80.);
  TF1 *tf2 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol9");

  //
  ofstream fo;
  fo.open("input_pt.txt");
  for(int i=0;i<24;i++){
    cout << v_angle3_pt[i] << " " << tf2->Eval(v_angle3_pt[i]) << endl;
    fo << v_angle3_pt[i] << " " << tf2->Eval(v_angle3_pt[i]) << endl;
  }

  fo.close();
}

