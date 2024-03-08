#ifndef HPGeHit_h
#define HPGeHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

//
class HPGeHit : public G4VHit
{
  public:
    HPGeHit() = default;
    HPGeHit(G4int i);
    HPGeHit(const HPGeHit&) = default;
    ~HPGeHit() override = default;

    // operators
    HPGeHit& operator=(const HPGeHit&) = default;
    G4bool operator==(const HPGeHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    void Draw() override;
    void Print() override;

    void SetID(G4int i){ detector_id = i; };
    void SetEdep(G4double de){ e_dep = de; };
    void AddEdep(G4double de){ e_dep += de; };
    void SetPos(G4ThreeVector xyz){ pos = xyz; };

    //
    G4int GetID() const { return detector_id; };
    G4double GetEdep() const { return e_dep; };
    G4ThreeVector GetPos() const { return pos; };

  private:
    G4int detector_id = -1; 
    G4double e_dep = 0.;
    G4ThreeVector pos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
using HPGeHitsCollection = G4THitsCollection<HPGeHit>;
extern G4ThreadLocal G4Allocator<HPGeHit>* HPGeHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* HPGeHit::operator new(size_t)
{
  if(!HPGeHitAllocator) HPGeHitAllocator = new G4Allocator<HPGeHit>;
  return (void *) HPGeHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void HPGeHit::operator delete(void *hit)
{
  HPGeHitAllocator->FreeSingle((HPGeHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
