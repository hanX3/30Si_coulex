#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4VUserPhysicsList.hh"

// gamma
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

// e-/e+
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eplusAnnihilation.hh"

// ions
#include "G4CoulombScattering.hh"
#include "G4IonConstructor.hh"
#include "G4IonCoulombScatteringModel.hh"
#include "G4IonTable.hh"
#include "G4StepLimiter.hh"
#include "G4hIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"
#include "G4IonDEDXScalingICRU73.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4IonStoppingData.hh"
#include "G4NuclearStopping.hh"

// neutrons
#include "G4LFission.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronCaptureProcess.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronFissionProcess.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4HadronInelasticProcess.hh"

//
#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"

//
#include "Recoil.hh"
#include "Projectile.hh"
#include "ReactionCoulex.hh"
#include "DetectorConstruction.hh"

using namespace CLHEP;

class PhysicsList : public G4VUserPhysicsList
{
public:
  PhysicsList(Projectile *p, Recoil *r, DetectorConstruction *dc);
  ~PhysicsList();

public:
  int GetReactionType() { return reaction_type; };
  ReactionCoulex *GetReactionCoulex() { return reaction_coulex; };

  void SetStepSize(double ss) { step_size = ss; };
  void SetCS() { custom_stopping = true; };
  void SetCSPath(const char *csp) { strcpy(cs_path, csp); };
  void SetUseNeutrons(bool val) { use_neutrons = val; };
  void SetReactionType(int val) { reaction_type = val; };

protected:
  void ConstructParticle();
  void ConstructProcess();
  void ConstructEM();
  void SetCuts();

private:
  Projectile *projectile;
  Recoil *recoil;
  DetectorConstruction *detector_construction;
  ReactionCoulex *reaction_coulex;

  double step_size;
  bool custom_stopping;
  bool use_neutrons = true;
  int reaction_type;
  char cs_path[256];
};

#endif 
