/*
**	Filename : DetectorConstruction.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "DetectorConstruction.h"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "Geometry.h"
#include "Helpers.h"
#include "Materials.h"
#include "SD.h"
#include <G4LogicalSkinSurface.hh>
#include <G4OpticalSurface.hh>
#include <G4SDManager.hh>

DetectorConstruction::DetectorConstruction() { fSDMan = G4SDManager::GetSDMpointer(); }

DetectorConstruction::~DetectorConstruction() {}

G4LogicalVolume *DetectorConstruction::GetLogicalWorld() const { return logicalWorld; }

G4VPhysicalVolume *DetectorConstruction::Construct() {

  // G4NistManager* nist = G4NistManager::Instance();
  //
  // World
  //
  G4bool checkOverlaps = true;
  G4double world_sizeXYZ = 200 * cm;
  logicalWorld =
      (new Box("World", 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, "G4_AIR"))->GetLogicalVolume();
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0,               // no rotation
                                                   G4ThreeVector(), // at (0,0,0)
                                                   logicalWorld,    // its logical volume
                                                   "PhysicalWorld", // its name
                                                   0,               // its mother  volume
                                                   false,           // no boolean operation
                                                   0,               // copy number
                                                   checkOverlaps);  // overlaps checking

#ifdef ICNSE_CYLINDRICAL_SHIELD
  double sphi = 0.;
  double dphi = 2 * M_PI;
  G4LogicalVolume *logicalHollowSpace =
      (new CylindricalShell("HollowSpace", 0 * cm, 25 * cm, 90 * cm, sphi, dphi))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerCopperShell =
      (new CylindricalShell("InnerCopperShell", 25 * cm, 27 * cm, 90 * cm, sphi, dphi, "G4_Cu"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerPSShell =
      (new CylindricalShell("InnerPSShell", 27 * cm, 31 * cm, 90 * cm, sphi, dphi, "ICNSE_PS"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerHDPEShell =
      (new CylindricalShell("InnerHDPEShell", 31 * cm, 41 * cm, 90 * cm, sphi, dphi, "ICNSE_HDPE"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerPbShell =
      (new CylindricalShell("InnerPbShell", 41 * cm, 51 * cm, 90 * cm, sphi, dphi, "G4_Pb"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerBPShell =
      (new CylindricalShell("InnerBPShell", 51 * cm, 61 * cm, 90 * cm, sphi, dphi, "ICNSE_BP"))->GetLogicalVolume();
  G4LogicalVolume *logicalOuterHDPEShell =
      (new CylindricalShell("OuterHDPEShell", 61 * cm, 71 * cm, 90 * cm, sphi, dphi, "ICNSE_HDPE"))->GetLogicalVolume();
  G4LogicalVolume *logicalOuterPSShell =
      (new CylindricalShell("OuterPSShell", 71 * cm, 75 * cm, 90 * cm, sphi, dphi, "ICNSE_PS"))->GetLogicalVolume();
#else
  G4LogicalVolume *logicalHollowSpace = (new Box("HollowSpace", 25 * cm, 25 * cm, 37.5 * cm))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerCopperShell =
      (new BoxShell("InnerCopperShell", 27 * cm, 27 * cm, 39.5 * cm, 2 * cm, "G4_Cu"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerPSShell =
      (new BoxShell("InnerPSShell", 31 * cm, 31 * cm, 43.5 * cm, 4 * cm, "ICNSE_PS"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerHDPEShell =
      (new BoxShell("InnerHDPEShell", 41 * cm, 41 * cm, 53.5 * cm, 10 * cm, "ICNSE_HDPE"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerPbShell =
      (new BoxShell("InnerPbShell", 51 * cm, 51 * cm, 63.5 * cm, 10 * cm, "G4_Pb"))->GetLogicalVolume();
  G4LogicalVolume *logicalInnerBPShell =
      (new BoxShell("InnerBPShell", 61 * cm, 61 * cm, 73.5 * cm, 10 * cm, "ICNSE_BP"))->GetLogicalVolume();
  G4LogicalVolume *logicalOuterHDPEShell =
      (new BoxShell("OuterHDPEShell", 71 * cm, 71 * cm, 83.5 * cm, 10 * cm, "ICNSE_HDPE"))->GetLogicalVolume();
  G4LogicalVolume *logicalOuterPSShell =
      (new BoxShell("OuterPSShell", 75 * cm, 75 * cm, 87.5 * cm, 4 * cm, "ICNSE_PS"))->GetLogicalVolume();

#endif
  // Physical Placement
  new G4PVPlacement(0, G4ThreeVector(), logicalHollowSpace, "HollowSpace_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalInnerCopperShell, "InnerCopperShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalInnerPSShell, "InnerPSShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalInnerHDPEShell, "InnerHDPEShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalInnerPbShell, "InnerPbShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalInnerBPShell, "InnerBPShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalOuterHDPEShell, "OuterHDPEShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(), logicalOuterPSShell, "OuterPSShell_Physical", logicalWorld, false, 0,
                    checkOverlaps);

  SD *hollowSD = new SD("SensitiveHollowSpace");
  fSDMan->AddNewDetector(hollowSD);
  logicalHollowSpace->SetSensitiveDetector(hollowSD);

  /*
  SD *bpSD = new SD("BoratedPolyEthylene");
  fSDMan->AddNewDetector(bpSD);
  logicalInnerBPShell->SetSensitiveDetector(bpSD);
  */

#ifdef ICNSE_INSPECT_SOURCE
  G4LogicalVolume *logicalSource = (new Box("Source", 0.5 * cm, 0.5 * cm, 0.5 * cm))->GetLogicalVolume();
  G4VPhysicalVolume *physSource = new G4PVPlacement(0,                               // no rotation
                                                    G4ThreeVector(-90 * cm, 0., 0.), // at (0,0,0)
                                                    logicalSource,                   // its logical volume
                                                    "SourceEnvelop",                 // its name
                                                    logicalWorld,                    // its mother  volume
                                                    false,                           // no boolean operation
                                                    0,                               // copy number
                                                    checkOverlaps);                  // overlaps checking

  SD *sourceSD = new SD("RadioactiveSource");
  fSDMan->AddNewDetector(sourceSD);
  logicalSource->SetSensitiveDetector(sourceSD);
#endif

  std::cout << "========== TOTAL WEIGHT of DETECTOR =============" << std::endl;
  std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "=================================================" << std::endl;
  return physWorld;
}
