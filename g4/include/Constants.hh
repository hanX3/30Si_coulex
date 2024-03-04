#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "cmath"

#include "G4SystemOfUnits.hh"

#define DATAPATH "./data"  // no "/"

// 0b0001 event data
// 0b0010 track data
// 0b0100 step data
constexpr G4int MASK = 0b001;

constexpr G4double WorldSizeX = 5. * m;
constexpr G4double WorldSizeY = 5. * m;
constexpr G4double WorldSizeZ = 5. * m;

// chamber
constexpr G4double ChamberRMin = 125. *mm;
constexpr G4double ChamberRMax = 127. *mm;
constexpr G4double PipeR = 20. *mm;

// target
constexpr G4double TargetR = 15. * mm;
constexpr G4double TargetThickness = 0.606 * um;

// hpge
constexpr G4double HPGeCrystalOuterRadius = 35. *mm;
constexpr G4double HPGeCrystalInnerRadius = 5. *mm;
constexpr G4double HPGeCrystalLength = 80. *mm;
constexpr G4double HPGeCrystalHoleDepth = 15. *mm;
constexpr G4double HPGeCrystalEdgeOffset1 = 26. *mm; 
constexpr G4double HPGeCrystalEdgeOffset2 = 28.5 *mm; 
constexpr G4double HPGeCrToCapF = 3. *mm;
constexpr G4double HPGeBGOtoCap = 25. *mm;

// clover
constexpr G4double CloverCrystalOuterRadius = 30. *mm;
constexpr G4double CloverCrystalInnerRadius = 7. *mm;
constexpr G4double CloverCrystalLength = 90. *mm; 
constexpr G4double CloverCrystalHoleDepth = 15. *mm;
constexpr G4double CloverDistanceOfCrs = 0.6 *mm;
constexpr G4double CloverCrEdgeCut1 = 26. *mm;
constexpr G4double CloverCrEdgeCut2 = 28.5 *mm;
constexpr G4double CloverCrEdgeDepth = 30. *mm;
constexpr G4double CloverCrEdgeAngle = 22.5 *deg;
constexpr G4double CloverCapWidth = 2.5 *mm;
constexpr G4double CloverCapsuleLength = 148. *mm; 
constexpr G4double CloverCr2CapF = 14. *mm;
constexpr G4double CloverCr2CapE = 15. *mm;
constexpr G4double CloverFrontShieldL = 123. *mm;
constexpr G4double CloverFrontShieldWidth = 10. *mm;
constexpr G4double CloverFrontShield1 = -0.3 *mm;
constexpr G4double CloverFrontShield2 = 1. *mm; 
constexpr G4double CloverBGOShieldWidth = 20. *mm;
constexpr G4double CloverBGOShieldEdgeDepth = 0.6*CloverBGOShieldWidth/tan(CloverCrEdgeAngle); 
constexpr G4double CloverBGOShield2Cap = 3.7 *mm;
constexpr G4double CloverBGOShieldOffset = 25. *mm;

// si array
constexpr G4double S3SiThickness = 300. *um;
constexpr G4double S3SiOuterRadius = 35 *mm;
constexpr G4double S3Si2Target = 8.6 *mm;

// au layer
constexpr G4double AuLayerR = 25. * mm;
constexpr G4double AuLayerThickness = 0.5 * um;
constexpr G4double PosAuLayerX = 0. * mm;
constexpr G4double PosAuLayerY = 0. * mm;
constexpr G4double PosAuLayerZ = -(TargetThickness+AuLayerThickness) * mm;

// projectile
constexpr G4int ProjectileA = 30;
constexpr G4int ProjectileZ = 18;
constexpr G4int ProjectileKE = 100. *MeV;

//beam
constexpr G4double PosBeamX = 0. * mm;
constexpr G4double PosBeamY = 0. * mm;
constexpr G4double PosBeamZ = -10. * mm;
constexpr G4double BeamSigma = 1. * MeV;
//step limit

constexpr G4double Ahc = 1.439964535;
constexpr G4double Deg2Rad = 0.01745329252;

#endif
