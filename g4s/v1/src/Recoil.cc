#include "Recoil.hh"

//
Recoil::Recoil()
{
  recoil_a = 9;
  recoil_z = 4;
  recoil_ex = 0. *MeV;
  recoil_tau = 0. *ns;
}

//
Recoil::~Recoil()
{

}

//
void Recoil::Report()
{
  G4cout << "----> Recoil A set to " << recoil_a << G4endl; 
  G4cout << "----> Recoil Z set to " << recoil_z << G4endl; 
  G4cout << "----> Recoil Ex set to " << recoil_ex/MeV << " MeV" << G4endl;
  G4cout << "----> Recoil decay lifetime set to " << recoil_tau/ns*1000. << " ps" << G4endl;
}

