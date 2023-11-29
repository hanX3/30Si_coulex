//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 28 10:36:20 2023 by ROOT version 6.24/02
// from TTree tr_event/timewindow_40
// found on file: run00804_build_40ns.root
//////////////////////////////////////////////////////////

#ifndef doppler_h
#define doppler_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class doppler {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           n_Si_ring;
   Short_t         Si_ring_mod[5];   //[n_Si_ring]
   Short_t         Si_ring_ch[5];   //[n_Si_ring]
   Double_t        Si_ring_adc[5];   //[n_Si_ring]
   Long64_t        Si_ring_ts[5];   //[n_Si_ring]
   Int_t           n_Si_sector;
   Short_t         Si_sector_mod[5];   //[n_Si_sector]
   Short_t         Si_sector_ch[5];   //[n_Si_sector]
   Double_t        Si_sector_adc[5];   //[n_Si_sector]
   Long64_t        Si_sector_ts[5];   //[n_Si_sector]
   Int_t           n_Ge;
   Short_t         Ge_mod[5];   //[n_Ge]
   Short_t         Ge_ch[5];   //[n_Ge]
   Double_t        Ge_energy[5];   //[n_Ge]
   Long64_t        Ge_ts[5];   //[n_Ge]

   // List of branches
   TBranch        *b_n_Si_ring;   //!
   TBranch        *b_Si_ring_mod;   //!
   TBranch        *b_Si_ring_ch;   //!
   TBranch        *b_Si_ring_adc;   //!
   TBranch        *b_Si_ring_ts;   //!
   TBranch        *b_n_Si_sector;   //!
   TBranch        *b_Si_sector_mod;   //!
   TBranch        *b_Si_sector_ch;   //!
   TBranch        *b_Si_sector_adc;   //!
   TBranch        *b_Si_sector_ts;   //!
   TBranch        *b_n_Ge;   //!
   TBranch        *b_Ge_mod;   //!
   TBranch        *b_Ge_ch;   //!
   TBranch        *b_Ge_energy;   //!
   TBranch        *b_Ge_ts;   //!

   doppler(TTree *tree=0);
   virtual ~doppler();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual Long64_t GetEntries();
};

#endif

#ifdef doppler_cxx
doppler::doppler(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   Init(tree);
}

doppler::~doppler()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t doppler::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t doppler::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void doppler::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("n_Si_ring", &n_Si_ring, &b_n_Si_ring);
   fChain->SetBranchAddress("Si_ring_mod", Si_ring_mod, &b_Si_ring_mod);
   fChain->SetBranchAddress("Si_ring_ch", Si_ring_ch, &b_Si_ring_ch);
   fChain->SetBranchAddress("Si_ring_adc", Si_ring_adc, &b_Si_ring_adc);
   fChain->SetBranchAddress("Si_ring_ts", Si_ring_ts, &b_Si_ring_ts);
   fChain->SetBranchAddress("n_Si_sector", &n_Si_sector, &b_n_Si_sector);
   fChain->SetBranchAddress("Si_sector_mod", Si_sector_mod, &b_Si_sector_mod);
   fChain->SetBranchAddress("Si_sector_ch", Si_sector_ch, &b_Si_sector_ch);
   fChain->SetBranchAddress("Si_sector_adc", Si_sector_adc, &b_Si_sector_adc);
   fChain->SetBranchAddress("Si_sector_ts", Si_sector_ts, &b_Si_sector_ts);
   fChain->SetBranchAddress("n_Ge", &n_Ge, &b_n_Ge);
   fChain->SetBranchAddress("Ge_mod", Ge_mod, &b_Ge_mod);
   fChain->SetBranchAddress("Ge_ch", Ge_ch, &b_Ge_ch);
   fChain->SetBranchAddress("Ge_energy", Ge_energy, &b_Ge_energy);
   fChain->SetBranchAddress("Ge_ts", Ge_ts, &b_Ge_ts);
   Notify();
}

Bool_t doppler::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void doppler::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t doppler::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
Long64_t doppler::GetEntries()
{
  return fChain->GetEntriesFast();
}
#endif // #ifdef doppler_cxx
