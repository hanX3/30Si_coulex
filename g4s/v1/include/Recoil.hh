#ifndef Recoil_h
#define Recoil_h 1

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"
#include "G4Decay.hh"
#include "Randomize.hh"

//
class Recoil
{
public:
  Recoil();
  ~Recoil();

public:
  //
  void SetA(G4int a) { recoil_a = a; };
  void SetZ(G4int z) { recoil_z = z; };
  void SetEx(G4int ex) { recoil_ex = ex; };
  void SetTau(G4int tau) { recoil_tau = tau; };
  //
  G4int GetA() { return recoil_a; };
  G4int GetZ() { return recoil_z; };
  G4int GetEx() { return recoil_ex; };
  G4int GetTau() { return recoil_tau; };
  //
  void Report();

private:
  G4int recoil_a;
  G4int recoil_z;
  G4double recoil_ex;
  G4double recoil_tau;
//
};

#endif
