#include "Projectile.hh"

//
Projectile::Projectile()
{
  projectile_a = ProjectileA; 
  projectile_z = ProjectileZ; 
  projectile_ke = ProjectileKE;

  projectile_tau = 0. *ns;
  projectile_ex = 0. *MeV;

  fc_x = 0.*mm;  
  fc_dx = 0. *mm;
  fc_y = 0. *mm;
  fc_dy = 0. *mm;
  fc_z = -100. *cm;

  max_ata = 0. *mrad;
  max_bta = 0. *mrad;
  ata0 = 0.*mrad;
  bta0 = 0.*mrad;

  v_f = new std::vector<double>;
  v_th = new std::vector<double>;

  for(int i=0;i<projectile_a;i++){
    v_f->push_back(0.);
    v_th->push_back(0.);
  }
}

//
Projectile::~Projectile()
{

}

//
void Projectile::Report()
{
  G4cout << "----> Z of the projectile set to  " << projectile_z << G4endl;
  G4cout << "----> A of the projectile set to  " << projectile_a << G4endl;
  G4cout << "----> Kin. En. of the projectile set to " << projectile_ke/MeV << " MeV" << G4endl;
  G4cout << "----> Excitation energy of the projectile set to " << projectile_ex/MeV << " MeV" << G4endl;
  G4cout << "----> Lifetime for the dexcitation of the projectile set to " << projectile_tau/ns*1000. << " ps" << G4endl;
  G4cout << "----> focal point X position for the projectile set to  " << G4BestUnit(fc_x, "Length") << G4endl;
  G4cout << "----> focal point DX size for the projectile set to  " << G4BestUnit(fc_dx, "Length") << G4endl;
  G4cout << "----> focal point Y position for the projectile set to  " << G4BestUnit(fc_y, "Length") << G4endl;
  G4cout << "----> focal point DY size for the projectile set to  " << G4BestUnit(fc_dy, "Length") << G4endl;
  G4cout << "----> focal point Z position for the projectile set to  " << G4BestUnit(fc_z, "Length") << G4endl;
  G4cout << "----> angular divergence in the x direction for the projectile set to  " << max_ata/mrad << " mrad = " << max_ata/deg << " deg" << G4endl;
  G4cout << "----> angular divergence in the y direction for the projectile set to  " << max_bta/mrad << " mrad = " << max_bta/deg << " deg" << G4endl;
}

//
G4ThreeVector Projectile::GetDirection()
{
  G4ThreeVector direction;
  G4double x, y, z, a, b, r, phi;

  phi = G4UniformRand()*CLHEP::twopi;
  r = G4UniformRand();

  a = r*std::cos(phi)*max_ata;
  b = r*std::sin(phi)*max_bta;
  z = 1./sqrt(1.+std::tan(a)*std::tan(a)+std::tan(b)*std::tan(b));

  x = z*std::tan(a);
  y = z*std::tan(b);

  direction.setX(x);
  direction.setY(y);
  direction.setZ(z);

  direction.rotateY(ata0);
  direction.rotateX(-bta0);

  return direction;
}  

//
G4ThreeVector Projectile::GetPosition()
{
  G4ThreeVector position;
  G4double x, y, r, phi;

  phi = G4UniformRand()*CLHEP::twopi;
  r = G4UniformRand();

  x = fc_x+r*std::cos(phi)*fc_dx/2.;
  y = fc_y+r*std::cos(phi)*fc_dy/2.;

  position.setX(x);
  position.setY(y);
  position.setZ(fc_z);

  return position;
}







