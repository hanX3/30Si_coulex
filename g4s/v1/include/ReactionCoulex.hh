#ifndef ReactionCoulex_h
#define ReactionCoulex_h 1

#include "DetectorConstruction.hh"
#include "GammaDecayChannel.hh"
#include "Recoil.hh"
#include "Projectile.hh"

#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4VParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"
#include "G4DecayTable.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4Track.hh"
#include "G4Decay.hh"

#include "globals.hh"
#include <math.h>
#include <vector>

//
class ReactionCoulex : public G4VProcess
{
public:
  ReactionCoulex(Projectile *p, Recoil *r, const G4String& process_name = "ReactionCoulex");
  virtual ~ReactionCoulex();

public:
  G4bool reaction_here;

public:
  virtual G4double PostStepGetPhysicalInteractionLength(const G4Track &track, G4double previous_step_size, G4ForceCondition *condition);
  virtual G4VParticleChange *PostStepDoIt(const G4Track &track, const G4Step &step);
  // no operation in AtRestGPIL
  virtual G4double AtRestGetPhysicalInteractionLength(const G4Track &track, G4ForceCondition *condition) { return -1.; };
  // no operation in AtRestDoIt
  virtual G4VParticleChange *AtRestDoIt(const G4Track &track, const G4Step &step) { return nullptr; };
  // no operation in AlongStepGPIL
  virtual G4double AlongStepGetPhysicalInteractionLength(const G4Track &, G4double, G4double, G4double&, G4GPILSelection *) { return -1.; };
  // no operation in AlongStepDoIt
  virtual G4VParticleChange *AlongStepDoIt(const G4Track &track, const G4Step &step) { return nullptr; };

public:
  void TargetFaceCrossSection();
  G4int GetTargetRecoilA() { return recoil_a; };
  G4int GetTargetRecoilZ() { return recoil_z; };
  G4double GetTargetFaceCrossSection() { return sigma_face; };
  G4double GetThickTargetCorrection() { return sum_weights/(sum_proj+drop_rand); };
  G4double GetThickTargetCrossSection() { return sum_weights/(sum_proj+drop_rand)*sigma_face;};
  G4int GetNumberOfSimulatedReactions() { return sum_proj; };
  G4int GetRxnDroppedE() { return drop_e; };
  G4int GetRxnDroppedKsi() { return drop_ksi; };
  G4int GetRxnDroppedRand() { return drop_rand; };
  G4bool GetProjExFlag() { return projectile_ex_flag; };

  void ReportDCmin() { printf("Minimum istnace of closest approach = %.2f fm\n", dc_min); };
  void SetDCmin(G4double d) { dc_min = d; };

  Projectile *GetProjectile() { return projectile; };
  Recoil *GetRecoil() { return recoil; };

private:
  ReactionCoulex &operator=(const ReactionCoulex &) { return *this; };

  Recoil *recoil;
  Projectile *projectile;

  G4int CalcFthKsi(double, std::vector<G4double> *);
  void SetupLookupGenerator(G4double fksi);
  G4double GetTheta();
  G4double FineThetaFunction(G4double, G4double, G4double, G4double, G4double, G4double, G4double);
  G4bool SetupReactionProducts(const G4Track &track, G4DynamicParticle *po, G4DynamicParticle *ro);
  G4double GetKsi(G4double);
  G4double GetFKsi(G4double);
  G4double DfdOmega(G4double, G4double);
  G4double DfofTheta(G4double, std::vector<G4double> *);

private:
  G4ThreeVector pos_in;
  G4int reaction_flag;

  std::vector<G4double> v_ksi_array;
  std::vector<G4double> v_fksi_array;
  std::vector<G4double> v_theta_array;

  std::vector<G4double> v_th000;
  std::vector<G4double> v_th010;
  std::vector<G4double> v_th020;
  std::vector<G4double> v_th030;
  std::vector<G4double> v_th040;
  std::vector<G4double> v_th050;
  std::vector<G4double> v_th060;
  std::vector<G4double> v_th070;
  std::vector<G4double> v_th080;
  std::vector<G4double> v_th090;
  std::vector<G4double> v_th100;
  std::vector<G4double> v_th110;
  std::vector<G4double> v_th120;
  std::vector<G4double> v_th130;
  std::vector<G4double> v_th140;
  std::vector<G4double> v_th150;
  std::vector<G4double> v_th160;
  std::vector<G4double> v_th170;
  std::vector<G4double> v_th180;

  std::vector<std::vector<G4double>> v_v_fthksi;
  std::vector<G4double> v_thefth;
  std::vector<G4double> v_thbin;
  std::vector<G4double> v_fbin;
  std::vector<G4int> v_thlookup;
  
  G4double the_f;
  G4double sigma_face; // in barns
  G4double sum_weights;
  G4int sum_proj;
  G4int drop_rand, drop_e, drop_ksi; // reasons of drop reaction
  G4double ksi_face;
  G4double e_prime_face;
  G4double projectile_a, projectile_z, recoil_a, recoil_z;
  G4bool projectile_ex_flag; // true if the projectile is excited (and decays), false if the recoil is excited
  G4double projectile_ex, recoil_ex;
  G4double be2;
  G4double de, dep;

  // standard decy
  G4Decay *decay;
  // custom decay
  // static Decay decay;

  // minimum allowed distance of closest approach in fm
  G4double dc_min;

  //
  G4ParticleDefinition *particle_projectile;
  G4ParticleDefinition *particle_recoil;

  G4double the_weight;
};

#endif
