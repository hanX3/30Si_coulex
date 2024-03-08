#ifndef Projectile_h
#define Projectile_h 1

#include "Constants.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "Randomize.hh"

#include <vector>

//
class Projectile
{
public:
  Projectile();
  ~Projectile();

public:
  void Report();

  void SetA(G4int a) { projectile_a = a; };
  void SetZ(G4int z) { projectile_z = z; };
  void SetKE(G4double k) { projectile_ke = k; };
  void SetEx(G4double e) { projectile_ex = e; };
  void SetTau(G4double t) { projectile_tau = t; };
  void SetFcX(G4double f) { fc_x = f; };
  void SetFcDX(G4double f) { fc_dx = f; };
  void SetFcY(G4double f) { fc_y = f; };
  void SetFcDY(G4double f) { fc_dy = f; }; 
  void SetFcZ(G4double f) { fc_z = f; };
  void SetMaxAta(G4double a) { max_ata = a; };
  void SetMaxBta(G4double b) { max_bta = b; };
  void SetAta0 (G4double a) { ata0 = a; };
  void SetBta0 (G4double b) { bta0 = b; };
  void SetTheF (G4double t) { the_f = t; };

public:
  G4int GetA() { return projectile_a; }
  G4int GetZ() { return projectile_z; }
  G4double GetEx() { return projectile_ex; }
  G4double GetTau() { return projectile_tau; }
  G4double GetKE() { return projectile_ke; };
  G4double GetAta0() { return ata0; }
  G4double GetBta0() { return bta0; }
  G4ThreeVector GetPosition();
  G4ThreeVector GetDirection();
  std::vector<G4double> *GetF() { return v_f; };
  std::vector<G4double> *GetTh() { return v_th; };
  G4double GetTheF() { return the_f; };

private:
  G4int projectile_a;
  G4int projectile_z;
  G4double projectile_ex;
  G4double projectile_tau;
  G4double projectile_ke;
  G4double fc_x;
  G4double fc_dx;
  G4double fc_y;
  G4double fc_dy;
  G4double fc_z;
  G4double max_ata;
  G4double max_bta;
  G4double ata0;
  G4double bta0;
  std::vector<G4double> *v_f;
  std::vector<G4double> *v_th;
  G4double the_f;
 
//
};

#endif
