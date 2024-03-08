#ifndef SiHit_h
#define SiHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Si hit class
/// It defines data members to store the trackID, energy deposit, and position of charged particles in a selected volume:
/// - tarck_id, e_dep, pos

class SiHit : public G4VHit
{
public:
  SiHit() = default;
  SiHit(const SiHit&) = default;
  ~SiHit() override = default;

  // operators
  SiHit& operator=(const SiHit&) = default;
  G4bool operator==(const SiHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  void Draw() override;
  void Print() override;

  // Set methods
  void SetTrackID(G4int tid){ track_id = tid; };
  void SetEdep(G4double de){ e_dep = de; };
  void AddEdep(G4double de){ e_dep += de; };
  void SetPos(G4ThreeVector xyz){ pos = xyz; };

  // Get methods
  G4int GetTrackID() const { return track_id; };
  G4double GetEdep() const { return e_dep; };
  G4ThreeVector GetPos() const { return pos; };

private:
  G4int track_id = -1;
  G4double e_dep = 0.;
  G4ThreeVector pos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using SiHitsCollection = G4THitsCollection<SiHit>;
extern G4ThreadLocal G4Allocator<SiHit>* SiHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* SiHit::operator new(size_t)
{
  if(!SiHitAllocator) SiHitAllocator = new G4Allocator<SiHit>;
  return (void *) SiHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void SiHit::operator delete(void *hit)
{
  SiHitAllocator->FreeSingle((SiHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
