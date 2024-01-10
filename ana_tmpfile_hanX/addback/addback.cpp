#include "addback.h"

#include <vector>
#include <string>
#include "math.h"

//
addback::addback(const std::string &filename_in, const std::string &filename_out)
{
  benchmark = new TBenchmark;

  //
  file_in = TFile::Open(filename_in.c_str());
  tr_in = (TTree*)file_in->Get("tree");
  tr_in->SetBranchAddress("mod", &mod_);
  tr_in->SetBranchAddress("ch", &ch_);
  tr_in->SetBranchAddress("energy", &energy_);
  tr_in->SetBranchAddress("ts", &ts_);

  mod_ = 0;
  ch_ = 0;
  energy_ = 0;
  ts_ = 0;

  file_out = TFile::Open(filename_out.c_str(), "recreate");
  tr = new TTree("tree", "XIA addback data");
  tr->Branch("mod", &mod, "mod/S");
  tr->Branch("ch", &ch, "ch/S");
  tr->Branch("energy", &energy, "energy/D");
  tr->Branch("ts", &ts, "ts/L");
  tr->Branch("ab_flag", &ab_flag, "ab_flag/O");

  mod = 0;
  ch = 0;
  energy = 0;
  ts = 0;
  ab_flag = 0;

  memset(hit1, 0, sizeof(hit1));
  memset(hit2, 0, sizeof(hit2));
  memset(hit3, 0, sizeof(hit3));
  memset(hit4, 0, sizeof(hit4));

  memset(hit2_adj, 0, sizeof(hit2_adj));
  memset(hit2_dia, 0, sizeof(hit2_dia));
}

//
addback::~addback()
{
  file_in->Close();
  file_out->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void addback::Process()
{
  benchmark->Start("addback");

  Long64_t n = tr_in->GetEntries();

  std::cout << n << std::endl;
  for(Long64_t i=0; i<n;i++){
    tr_in->GetEntry(i);

    if(i==0){
      map_value.mod = mod_;
      map_value.ch = ch_;
      map_value.energy = energy_;
      map_value.ts = ts_;
      map_value.ab_flag = 0;
      key = (((ts_<<4)+mod_)<<4)+ch_;;

      data.insert(std::make_pair(key, map_value));
      continue;
    }

    it = data.begin();
    if(ts_-(it->second.ts) > ADDBACKCOINTIME){
      Analysis();

      while(data.size() > 0){
        it = data.begin();
        mod = it->second.mod;
        ch = it->second.ch;
        energy = it->second.energy;
        ts = it->second.ts;
        ab_flag = it->second.ab_flag;

        data.erase(it);

        file_out->cd();
        tr->Fill();
      }
    }
    map_value.mod = mod_;
    map_value.ch = ch_;
    map_value.energy = energy_;
    map_value.ts = ts_;
    map_value.ab_flag = 0;
    key = (((ts_<<4)+mod_)<<4)+ch_;

    data.insert(std::make_pair(key, map_value));

    if(i%Long64_t(1e5) == 0){
      std::cout << "\r" << "entries: " << i;
      std::cout << std::flush;
    }
  } 

  std::cout << std::endl;

  while(data.size() > 0){
    it = data.begin();
    mod = it->second.mod;
    ch = it->second.ch;
    energy = it->second.energy;
    ts = it->second.ts;
    ab_flag = it->second.ab_flag;

    data.erase(it);

    file_out->cd();
    tr->Fill();
  }

  file_out->cd();
  tr->Write();

  std::cout << ">>>hit info" << std::endl;
  for(int i=0;i<CLOVERNUM;i++){
    std::cout << ">>>clover " << i << std::endl;
    std::cout << "hit 1 " << hit1[i] << std::endl;
    std::cout << "hit 2 " << hit2[i] << std::endl;
    std::cout << "hit 2 adjacent " << hit2_adj[i] << std::endl;
    std::cout << "hit 2 diagonal " << hit2_dia[i] << std::endl;
    std::cout << "hit 3 " << hit3[i] << std::endl;
    std::cout << "hit 4 " << hit4[i] << std::endl;
    std::cout << std::endl;
  }

  benchmark->Show("addback"); 
}

//
void addback::Analysis()
{
  /*
   * n_hit_clover=0; mark=0
   * n_hit_clover=1; mark=0,1,2,3
   * n_hit_clover=2; mark=1,2,3,3,4,5
   * n_hit_clover=3; mark=3,4,5,6
   * n_hit_clover=4; mark=6
  */

  xia_data clover[CLOVERNUM][4];
  int n_hit_clover[CLOVERNUM];
  int mark_clover[CLOVERNUM];//add fired crystals id


  memset(clover, 0, sizeof(clover));
  memset(n_hit_clover, 0, sizeof(n_hit_clover));
  memset(mark_clover, 0, sizeof(mark_clover));

  /*
  for(int i=0;i<CLOVERNUM;i++){
    std::cout << ">>> clover " << i << std::endl;
    for(int j=0;j<4;j++){
      std::cout << "mod " << clover[i][j].mod << std::endl;
      std::cout << "ch " << clover[i][j].ch << std::endl;
      std::cout << "energy " << clover[i][j].energy << std::endl;
      std::cout << "ts " << clover[i][j].ts << std::endl;
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  */

  std::vector<Long64_t> v_key;
  for(it=data.begin();it!=data.end();it++){
    if(it->second.mod==2 && it->second.ch>=0 && it->second.ch<4){//3-1
      clover[0][it->second.ch%4] = it->second;
      n_hit_clover[0]++;
      mark_clover[0] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }
    if(it->second.mod==2 && it->second.ch>=4 && it->second.ch<8){//3-2
      clover[1][it->second.ch%4] = it->second;
      n_hit_clover[1]++;
      mark_clover[1] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }
    if(it->second.mod==2 && it->second.ch>=8 && it->second.ch<12){//3-3
      clover[2][it->second.ch%4] = it->second;
      n_hit_clover[2]++;
      mark_clover[2] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }

    if(it->second.mod==3 && it->second.ch>=8 && it->second.ch<12){//3-6
      clover[3][it->second.ch%4] = it->second;
      n_hit_clover[3]++;
      mark_clover[3] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }

    if(it->second.mod==4 && it->second.ch>=0 && it->second.ch<4){//3-7
      clover[4][it->second.ch%4] = it->second;
      n_hit_clover[4]++;
      mark_clover[4] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }

    if(it->second.mod==4 && it->second.ch>=8 && it->second.ch<12){//3-8
      clover[5][it->second.ch%4] = it->second;
      n_hit_clover[5]++;
      mark_clover[5] += it->second.ch%4;
      v_key.push_back(it->first);
      continue;
    }
  }

  for(auto &k:v_key){
    data.erase(k);
  }

  for(int i=0;i<CLOVERNUM;i++){
    if(n_hit_clover[i]==0){
      continue;
    }
    if(n_hit_clover[i]==1 || (n_hit_clover[i]==2&&mark_clover[i]==3) || n_hit_clover[i]==3 || n_hit_clover[i]==4){
      for(int j=0;j<4;j++){
        if(clover[i][j].energy>0){
          key = (((clover[i][j].ts<<4)+clover[i][j].mod)<<4)+clover[i][j].ch;
          data.insert(std::make_pair(key, clover[i][j]));
        }else continue;
      }
    }else{
      xia_data xd;
      xd.mod = 0;
      xd.ch = 0;
      xd.energy = 0;
      xd.ts = 0;
      xd.ab_flag = 1;

      for(int j=0;j<4;j++){
        if(clover[i][j].energy>0){
          key = (((clover[i][j].ts<<4)+clover[i][j].mod)<<4)+clover[i][j].ch;
          xd.mod = clover[i][j].mod; 
          xd.ch = clover[i][j].ch; 
          xd.ts = clover[i][j].ts; 
        }else break;;
      }

      for(int j=0;j<4;j++) xd.energy += clover[i][j].energy;
      data.insert(std::make_pair(key, xd));
    }
  }

  for(int i=0;i<CLOVERNUM;i++){
    if(n_hit_clover[i]==0){
      continue;
    }
    if(n_hit_clover[i]==1){
      hit1[i]++;
      continue;
    }
    if(n_hit_clover[i]==2){
      hit2[i]++;
      if(mark_clover[i]==3){
        hit2_dia[i]++;
      }else{
        hit2_adj[i]++;
      }
      continue;
    }
    if(n_hit_clover[i]==3){
      hit3[i]++;
      continue;
    }
    if(n_hit_clover[i]==4){
      hit4[i]++;
      continue;
    }
  }

  /*
  for(int i=0;i<CLOVERNUM;i++){
    std::cout << ">>> clover " << i << " n_hit " << n_hit_clover[i] << std::endl;
    std::cout << ">>> clover " << i << " mark " << mark_clover[i] << std::endl;
    for(int j=0;j<4;j++){
      std::cout << "mod " << clover[i][j].mod << std::endl;
      std::cout << "ch " << clover[i][j].ch << std::endl;
      std::cout << "energy " << clover[i][j].energy << std::endl;
      std::cout << "ts " << clover[i][j].ts << std::endl;
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  for(it=data.begin();it!=data.end();it++){
    std::cout << "key " << it->first << std::endl;
    std::cout << ">>> mod " << it->second.mod << std::endl;
    std::cout << ">>> ch " << it->second.ch << std::endl;
    std::cout << ">>> energy " << it->second.energy << std::endl;
    std::cout << ">>> ts " << it->second.ts << std::endl;
    std::cout << ">>> ab_flag " << it->second.ab_flag << std::endl;
    std::cout << std::endl;
  }
  */
}
