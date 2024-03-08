#include "PrimaryGeneratorAction.hh"

//
PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *dc, Projectile *pro)
: detector_construction(dc),
  projectile(pro)
{
  n_particle = 1;
  particle_gun = new G4ParticleGun(n_particle);

  G4cout << "!!! test !!!" << G4endl;
}

//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particle_gun;
}

//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* an_event)
{
  G4cout << "!!! test !!!" << G4endl;
  //
  ion_table = G4IonTable::GetIonTable();
  ion = ion_table->GetIon(projectile->GetZ(), projectile->GetA(), 0.);

  particle_gun->SetParticleDefinition(ion);
  position = projectile->GetPosition();
  particle_gun->SetParticlePosition(position);
  direction = projectile->GetDirection();
  particle_gun->SetParticleMomentumDirection(direction);

  ke = projectile->GetKE();
  particle_gun->SetParticleEnergy(ke);

  G4double tt = detector_construction->GetTarget()->GetTarget()->GetZHalfLength();
  G4cout << "!!! test !!!" << G4endl;
  G4double tc = detector_construction->GetTarget()->GetTargetPlacement()->GetTranslation().getZ();
  G4cout << "!!! test !!!" << G4endl;
  G4double depth = tc+tt*(G4UniformRand()-0.5);
  G4cout << "!!! test !!!" << G4endl;
  detector_construction->GetTarget()->SetTargetReactionDepth(depth);
  G4cout << "!!! test !!!" << G4endl;

  //
  G4cout << "---> in PrimaryGeneratorAction ion Z " << projectile->GetZ() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction ion A " << projectile->GetA() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction pos x " << position.x() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction pos y " << position.y() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction pos z " << position.z() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction dir x " << direction.x() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction dir y " << direction.y() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction dir z " << direction.z() << G4endl;
  G4cout << "---> in PrimaryGeneratorAction ke " << ke << G4endl;
  G4cout << "---> in PrimaryGeneratorAction reaction depth " << depth << G4endl;

  //
  particle_gun->GeneratePrimaryVertex(an_event);
}

