//
void get_beta_si()
{
  ifstream fi;
  fi.open("output_si.txt");
  if(!fi){
    cout << "can not open the file" << endl;
    return;
  }

  ofstream fo;
  fo.open("beta_si.txt");
  double e, beta[24];
  for(int i=0;i<24;i++){
    fi >> e;
    beta[i] = sqrt(e*2./931.5/29.973770136);
    cout << "beta " << beta[i] << endl;
    fo << beta[i] << endl;
  }
  fo << endl;

  fo.close();
  fi.close();
}

//
void get_beta(_pt)
{
  ifstream fi1;
  fi1.open("input_pt.txt");
  if(!fi1){
    cout << "can not open the file" << endl;
    return;
  }

  ifstream fi2;
  fi2.open("output_pt.txt");
  if(!fi2){
    cout << "can not open the file" << endl;
    return;
  }

  ofstream fo;
  fo.open("theta_beta_pt.txt");
  double angle, e, beta[24];
  for(int i=0;i<24;i++){
    fi1 >> angle >> e;
    fi2 >> e;
    beta[i] = sqrt(e*2./931.5/195.964954675);
    cout << "angle " << angle << " beta " << beta[i] << endl;
    fo << angle << " " << beta[i] << endl;
  }
  fo << endl;

  fo.close();
  fi1.close();
  fi2.close();
}
