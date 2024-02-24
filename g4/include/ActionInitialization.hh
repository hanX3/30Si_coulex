#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "globals.hh"
#include "G4VUserActionInitialization.hh"

namespace coulex
{
class DetectorConstruction;
class RootIO;

/// Action initialization class.
class ActionInitialization : public G4VUserActionInitialization
{
public:
  ActionInitialization(DetectorConstruction* dc, G4int save);
  ~ActionInitialization() override;

  void BuildForMaster() const override;
  void Build() const override;

private:
  DetectorConstruction* detector_construction;
  G4int save_flag;  
};

//
}

#endif


