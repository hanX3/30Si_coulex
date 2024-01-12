#include "sort.h"

#include <vector>
#include <string>
#include "math.h"

//
sort::sort(const std::string &filename_in, const std::string &filename_out)
{
  benchmark = new TBenchmark;

  //
  ReadGeCaliPar();
  ReadSiCaliPar();
  ReadTsOffsetPar();

  memset(have_data, 0, sizeof(have_data));
  memset(entries, 0, sizeof(entries));
  memset(entry_n, 0, sizeof(entry_n));

  file_in = TFile::Open(filename_in.c_str());
  for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
    for(int j=0;j<16;j++){
      tr_[16*i+j] = (TTree*)file_in->Get(TString::Format("tr_XIA_%02d_%02d",i,j).Data());
      if(!tr_[16*i+j]){
        entries[16*i+j] = 0;
        have_data[16*i+j] = false;
        continue;
      }

      entries[16*i+j] = tr_[16*i+j]->GetEntries();
      have_data[16*i+j] = true;

      tr_[16*i+j]->SetBranchAddress("channel", &ch_[16*i+j]);
      tr_[16*i+j]->SetBranchAddress("Energy", &energy_[16*i+j]);
      tr_[16*i+j]->SetBranchAddress("Event_ts", &ts_[16*i+j]);
    }
  }

  memset(ch_, 0, sizeof(ch_));
  memset(energy_, 0, sizeof(energy_));
  memset(ts_, 0, sizeof(ts_));

  file_out = TFile::Open(filename_out.c_str(), "recreate");
  tr = new TTree("tree", "XIA sort data");
  tr->Branch("mod", &mod, "mod/S");
  tr->Branch("ch", &ch, "ch/S");
  tr->Branch("energy", &energy, "energy/D");
  tr->Branch("ts", &ts, "ts/L");

  rndm = new TRandom3((Long64_t)time(0));

  //
  /*
  for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
    for(int j=0;j<16;j++){
      std::cout << i << " " << j << " " << entries[16*i+j] << std::endl;
    }
  }
  */
}

//
sort::~sort()
{
  file_in->Close();
  file_out->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::Process()
{
  benchmark->Start("sorting");

  unsigned int len;
  bool flag_data = false;
  int s = 0;

  Long64_t time = TIMING; 
  
  while(true){
    flag_data = false;
    for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
      for(int j=0;j<16;j++){
        if(have_data[16*i+j]) flag_data = true;
      }
    }
    if(!flag_data){//last data
      std::cout << "last data " << std::endl;
      while(data.size() > 0){
        it = data.begin();
        mod = it->second.mod;
        ch = it->second.ch;
        energy = it->second.energy;
        ts = it->second.ts;

        data.erase(it);
        if(energy<20.)  continue;
        file_out->cd();
        tr->Fill();
      }//while
      break;
    }

    for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
      for(int j=0;j<16;j++){
        if(!have_data[16*i+j]) continue;
        if(entry_n[16*i+j]==entries[16*i+j]){
          have_data[16*i+j] = false;
          continue;
        }
        while(true){
          if(entry_n[16*i+j]==entries[16*i+j]){
            have_data[16*i+j] = false;
            break;
          }
          tr_[16*i+j]->GetEntry(entry_n[16*i+j]);
          ts_[16*i+j] += par_ts_offset[i][j];
          if(ts_[16*i+j] < time){
            map_value.mod = (ch_[16*i+j]/100)-1;
            map_value.ch = ch_[16*i+j]%100;
            if(i<5){
              map_value.energy = CaliGeEnergy(energy_[16*i+j], i, j);
            }else{
              map_value.energy = CaliSiEnergy(energy_[16*i+j], i, j);
            }
            map_value.ts = ts_[16*i+j];

            key = ((((ts_[16*i+j])<<4)+map_value.mod)<<4)+map_value.ch;
            data.insert(std::make_pair(key, map_value)); 

            entry_n[16*i+j]++;
          }else break; //if < time
        }//while
      }
    }

    time += TIMING;
    len = data.size()*PROCESSPERCENT;
    for(unsigned int i=0;i<len;i++){
      it = data.begin();
      mod = it->second.mod;
      ch = it->second.ch;
      energy = it->second.energy;
      ts = it->second.ts;

      data.erase(it);
      if(energy<20.)  continue;
      file_out->cd();
      tr->Fill();
    }

    s++;
    /*
    for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
      for(int j=0;j<16;j++){
        std::cout << i << " " << j << " " << entry_n[16*i+j] << " " << entries[16*i+j] << std::endl;
      }
    }
    */
    std::cout << "\r" << "time: " << s << "s";
    std::cout << std::flush;
  }

  file_out->cd();
  tr->Write();

  benchmark->Show("sorting"); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::SaveFile()
{
  file_out->cd();
  file_out->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::ReadGeCaliPar()
{
  std::cout << "start ReadCalPar" << std::endl;

  std::ifstream cali_file;
  cali_file.open("ener_cal.dat", std::ifstream::in);

  int mod, ch;
  double par0, par1, par2;
  double chi2;
  while(1){
    cali_file >> mod >> ch >> par0 >> par1 >> par2 >> chi2;
    //std::cout << mod << "  " << ch << "  " << par0 << "  " << par1 << "  " << par2 << "  " << chi2 << std::endl;
    if(!cali_file.good()) break;

    par_ge_cali[mod][ch][0] = par0;
    par_ge_cali[mod][ch][1] = par1;
    par_ge_cali[mod][ch][2] = par2;
  }

  cali_file.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::PrintGeCaliPar()
{
  std::cout << "print cali par" << std::endl;

  for(int i=0;i<(GEMODNUM);i++){
    for(int j=0;j<16;j++){
      std::cout << i << "  " << j << "  ";
      for(int k=0;k<3;k++){
        std::cout << par_ge_cali[i][j][k] << "  ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::ReadSiCaliPar()
{
  std::cout << "start read Si cali data" << std::endl;

  std::ifstream ifs;
  ifs.open("si_cali.dat");
  if(!ifs){
    std::cout << "cannot open si_cali.dat." << std::endl;
    return ;
  }

  int mod, ch;
  double par0, par1;
  int key = 0;

  while(1){
    ifs >> mod >> ch >> par0 >> par1;
    if(!ifs.good()) break;

    key = 100*mod+ch;
    std::vector<double> value;
    value.push_back(par0);
    value.push_back(par1);

    map_si_cali_data.insert(std::pair<int, std::vector<double>>(key, value));
  }

  ifs.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::PrintSiCaliPar()
{
  std::cout << "start read Si cali data" << std::endl;

  std::map<int, std::vector<double>>::iterator it = map_si_cali_data.begin();
  for(it=map_si_cali_data.begin();it!=map_si_cali_data.end();it++){
    std::cout << it->first << " => " << it->second[0] << " " << it->second[1] << '\n';
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::ReadTsOffsetPar()
{
  std::cout << "start ReadTsOffsetPar" << std::endl;

  std::ifstream ts_offset_file;
  ts_offset_file.open("../get_ts_offset/ts.offset", std::ifstream::in);

  std::string line;
  std::getline(ts_offset_file, line);

  int mod, ch;
  double par;
  double chi2;
  while(1){
    ts_offset_file >> mod >> ch >> par >> chi2;
    //std::cout << mod << "  " << ch << "  " << par << "  " << chi2 << std::endl;
    if(!ts_offset_file.good()) break;

    par_ts_offset[mod][ch] = par;
  }

  ts_offset_file.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void sort::PrintTsOffsetPar()
{
  std::cout << "print ts offset par" << std::endl;

  for(int i=0;i<(GEMODNUM+SIMODNUM);i++){
    for(int j=0;j<16;j++){
      std::cout << i << "  " << j << "  ";
      std::cout << par_ts_offset[i][j] << "  ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double sort::CaliGeEnergy(int adc, int mod, int ch)
{
  double energy = par_ge_cali[mod][ch][0] + adc*par_ge_cali[mod][ch][1] + adc*adc*par_ge_cali[mod][ch][2];
  energy += rndm->Uniform(-0.5, 0.5);

  return energy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double sort::CaliSiEnergy(int adc, int mod, int ch)
{
  int key = 100*mod+ch;

  auto it = map_si_cali_data.find(key);
  if(it==map_si_cali_data.end()) return 0;

  double adcc = map_si_cali_data[key][0] + adc*map_si_cali_data[key][1];
  return adcc;
}

