//
void get_si_beta()
{
  ifstream fi;
  fi.open("output.txt");
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
