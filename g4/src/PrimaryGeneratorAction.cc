#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_of_particles = 1;
  particle_gun = new G4ParticleGun(n_of_particles);

  // default particle
  // info here can be changed in macro file
  G4ParticleDefinition* particle_definition = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  /*
  G4int z = 91, a = 241;
  G4double excit_energy = 0. * keV;
  G4ParticleDefinition* particle_definition = G4IonTable::GetIonTable()->GetIon(z, a, excit_energy);
  */
  particle_gun->SetParticleDefinition(particle_definition);
  particle_gun->SetParticleEnergy(100. * MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particle_gun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* an_event)
{
  // This function is called at the begining of event
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore.
  G4LogicalVolume* logic_world = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* box_world = nullptr;
  if(logic_world) box_world = dynamic_cast<G4Box*>(logic_world->GetSolid());
  if(box_world) { }
  else{
    G4cerr << "world volume of box not found." << G4endl;
    G4cerr << "perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }

  //
  /*
  G4double x, y, z;
  G4double condizione;
  x =  CLHEP::RandFlat::shoot(-0.3,0.3);
  y =  CLHEP::RandFlat::shoot(-0.3,0.3);
  z =  0.3;
  condizione = std::sqrt(x*x + y*y + z*z);
  x = x/condizione;
  y = y/condizione;
  z = z/condizione;
  particle_gun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));
  */
  particle_gun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

  //
  G4double xp, yp, zp;
  xp = CLHEP::RandFlat::shoot(-0.3,0.3);
  yp = CLHEP::RandFlat::shoot(-0.3,0.3);
  zp = PosBeamZ;
  // G4cout << "xp " << xp << " yp " << yp << " zp " << zp << G4endl;
  particle_gun->SetParticlePosition(G4ThreeVector(xp, yp, zp));

  //
  G4double e_ori = particle_gun->GetParticleEnergy();
  G4double e_gauss = std::abs(G4RandGauss::shoot(e_ori, BeamSigma));
  // G4cout << "e_gauss " << e_gauss << G4endl;
  particle_gun->SetParticleEnergy(e_gauss * MeV);
  
  //
  particle_gun->GeneratePrimaryVertex(an_event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

