//
void draw()
{
  ifstream fi;
  fi.open("./data_lise_q.txt");

  string line;
  getline(fi, line);

  vector<double> v_angle_si;
  vector<double> v_angle_pt;
  vector<double> v_energy_si;
  vector<double> v_energy_pt;

  double a, b, c, d;
  while(1){
    fi >> a >> b >> c >> d;
    //cout << a << " " << b << " " << c << " " << d << " " << endl;
    if(!fi.good()) break;
  
    v_angle_si.push_back(a);
    v_energy_si.push_back(b);
    v_angle_pt.push_back(c);
    v_energy_pt.push_back(d);
  }
  fi.close();

  int n = v_energy_si.size();
  TGraph *gr1 = new TGraph(n);
  TGraph *gr2 = new TGraph(n);
  for(int i=0;i<n;i++){
    gr1->SetPoint(i, v_angle_si[i], 30.*v_energy_si[i]);
    gr2->SetPoint(i, v_angle_pt[i], 196.*v_energy_pt[i]);
  }

  TCanvas *cc = new TCanvas("cc", "", 0, 0, 480, 360);
  cc->cd();
  gr1->SetTitle();
  gr1->GetYaxis()->SetRangeUser(0, 160);
  gr1->GetXaxis()->SetTitle("Angle [degree]");
  gr1->GetYaxis()->SetTitle("Energy [MeV]");
  gr1->SetMarkerColor(2);
  gr2->SetMarkerColor(4);
  gr1->SetLineColor(2);
  gr2->SetLineColor(4);

  gr1->Draw("");
  gr2->Draw("same");

  TLegend *leg = new TLegend(0.6, 0.8, 0.85, 0.9);
  leg->AddEntry(gr1, "30Si");
  leg->AddEntry(gr2, "196Pt");
  leg->Draw("same");

  cc->Update();
  cc->SaveAs("./png/k.png");
}
