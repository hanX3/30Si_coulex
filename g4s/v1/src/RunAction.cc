#include "RunAction.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>


//
RunAction::RunAction(PhysicsList *pl, RootIO *ri, DetectorConstruction *dc)
: G4UserRunAction(),
  physics_list(pl),
  root_io(ri),
  detector_construction(dc)
{
  // set printing event number per each 100000 events
  G4RunManager::GetRunManager()->SetPrintProgress(100000);

  timer = new G4Timer();
}

//
RunAction::~RunAction()
{
  delete timer;
  timer = NULL;
}

//
void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "---> Beginning the run !" << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  physics_list->GetReactionCoulex()->TargetFaceCrossSection();

  if((MASK&0b001)==0b001){
    root_io->OpenEventFile();
    G4cout << "open event root file " << G4endl;
  }
  if((MASK&0b010)==0b010){
    root_io->OpenTrackFile();
    G4cout << "open track root file " << G4endl;
  }
  if((MASK&0b100)==0b100){
    root_io->OpenStepFile();
    G4cout << "open step root file " << G4endl;
  }

  int run_id = run->GetRunID();
  timer->Start();
  G4cout << "======================   RunID = " << run_id << "  ======================" << G4endl;

  G4cout << "1 energy " << G4endl;
  G4cout << "2 track id " << G4endl;
  G4cout << "3 particle name " << G4endl;
  G4cout << "4 pre postion " << G4endl;
  G4cout << "5 post postion " << G4endl;
  G4cout << "6 detector name " << G4endl;
  G4cout << "7 step length " << G4endl;
  G4cout << "8 delat postion " << G4endl;
  G4cout << "9 delat time " << G4endl;
  G4cout << "10 delat energy " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4double p, ddx, dx, nv;
  G4cout << G4endl;
  G4cout << std::setprecision(3);

  G4cout << " Thin target cross section is calculated assuming all reactions with the energy of the particle gun " << G4endl;
  G4cout << " Thick target correction accounts for the projectile energy change while crossing the backing and the target" << G4endl;
  G4cout << " Thin Target Cross Section is : " << physics_list->GetReactionCoulex()->GetTargetFaceCrossSection() << " [b]" << G4endl;
  G4cout << " Thick Target correction is : " << physics_list->GetReactionCoulex()->GetThickTargetCorrection() << G4endl;
  G4cout << " Thick Target Cross Section is : "<< physics_list->GetReactionCoulex()->GetThickTargetCrossSection() << " [b]" << G4endl;

  dx = detector_construction->GetTarget()->GetTargetThickness(); // in cm
  ddx = dx*detector_construction->GetTarget()->GetTargetDensity(); // in g/cm^2
  nv = detector_construction->GetTarget()->GetTargetNV(physics_list->GetReactionCoulex()->getTargetRecoilZ());   // in atoms/cm3
  p = nv*dx*physics_list->GetReactionCoulex()->GetThickTargetCrossSection()*1E-18;

  G4cout << " Target material density in g/cm3 is : " << detector_construction->GetTarget()->GetTargetDensity() <<G4endl;
  G4cout <<" Target thickness in mg/cm2 is : " << ddx*1000. << G4endl;
  // G4cout << " Number of atoms per unit volume : " << nv << " atoms/cm3" << G4endl;
  // G4cout << " Avogadro's number : " << Avogadro << " atoms/mol" << G4endl;
  G4cout << " Number density of recoils in the target is: " << nv/Avogadro*1000. << " [milli-mole/cm3]" << G4endl;
  G4cout << " Number of excitation is : " << p << " per million beam particles" << G4endl;
  G4cout << " Results are based on simulation of : " << physics_list->GetReactionCoulex()->GetNumberOfSimulatedReactions() << " reactions" << G4endl;
  G4cout << " Dropped : " << physics_list->GetReactionCoulex()->GetRxnDroppedE() << " reactions due to energy cutoff" << G4endl;
  G4cout << " Dropped : " << physics_list->GetReactionCoulex()->GetRxnDroppedKsi() << " reactions due to adiabaticity xi out of range" << G4endl;
  G4cout <<" Dropped : " << physics_list->GetReactionCoulex()->GetRxnDroppedRand() << " reactions due to XC RNG" << G4endl;

  //
  if((MASK&0b001)==0b001){
    root_io->CloseEventFile();
  }
  if((MASK&0b010)==0b010){
    root_io->CloseTrackFile();
  }
  if((MASK&0b100)==0b100){
    root_io->CloseStepFile();
  }

  // Print results
  G4cout << "  The run was " << run->GetNumberOfEvent() << " events " << G4endl;

  timer->Stop();
  G4cout << " time:  " << *timer << G4endl;
}

