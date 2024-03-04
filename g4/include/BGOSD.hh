#ifndef BGOSD_h
#define BGOSD_h 1

#include "G4VSensitiveDetector.hh"

#include "BGOHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

/// BGO sensitive detector class
///
/// The hits are accounted in hits in ProcessHits() function which is called by Geant4 kernel at each step. A hit is created with each step with non zero energy deposit.

class BGOSD : public G4VSensitiveDetector
{
  public:
    BGOSD(const G4String& name, const G4String& hits_collection_name);
    ~BGOSD() override = default;

    // methods from base class
    void   Initialize(G4HCofThisEvent* ) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void   EndOfEvent(G4HCofThisEvent* ) override;

  private:
    BGOHitsCollection* hits_collection = nullptr;
};

#endif
