#ifndef B2PrimaryGeneratorAction_h
#define B2PrimaryGeneratorAction_h 1

#include "Constants.hh"
#include "DetectorConstruction.hh"
#include "Projectile.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include "G4LorentzVector.hh"
#include "G4DynamicParticle.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include "globals.hh"
#include <vector>

//
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction *dc, Projectile *pro);
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* ) override;

  G4ParticleGun* GetParticleGun() {return particle_gun;}

  // Set methods
  void SetRandomFlag(G4bool );

private:
  G4int n_particle;
  G4ParticleGun* particle_gun = nullptr; // G4 particle gun

  G4IonTable *ion_table;
  G4ParticleDefinition *ion;
  G4ThreeVector direction;
  G4ThreeVector position;
  G4double ke;

  Projectile *projectile;
  DetectorConstruction *detector_construction;
};

#endif
