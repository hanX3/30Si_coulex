#ifndef B2PrimaryGeneratorAction_h
#define B2PrimaryGeneratorAction_h 1

#include "Constants.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

namespace coulex
{

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* ) override;

    G4ParticleGun* GetParticleGun() {return particle_gun;}

    // Set methods
    void SetRandomFlag(G4bool );

  private:
    G4ParticleGun* particle_gun = nullptr; // G4 particle gun
};

}

#endif
