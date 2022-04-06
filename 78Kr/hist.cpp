
TH1D *h1 = new TH1D("h1", "131-160 angle", 512, 0, 2048);

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

  fi.close();

  return;
}
