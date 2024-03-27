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
//#include <G4ThreadLocal.hh>
#include <G4Threading.hh>
#include "SD.h"
#include <cmath>
#include <algorithm>

#define inch 2.54 * cm

std::vector<SD *> DetectorConstruction::vecOfSD = {};

DetectorConstruction::DetectorConstruction()
{
  fSDMan = G4SDManager::GetSDMpointer();
}

DetectorConstruction::~DetectorConstruction() {}

G4LogicalVolume *DetectorConstruction::GetLogicalWorld() const
{
  return logicalWorld;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

  // G4NistManager* nist = G4NistManager::Instance();
  //
  // World
  //
  vecOfSD.resize(G4Threading::G4GetNumberOfCores());
  G4bool checkOverlaps   = true;
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

  // All the required dimensions

  // Envelope holding the whole thing
  double envelopeSizeX = 50. * inch;
  double envelopeSizeY = envelopeSizeX;
  double envelopeSizeZ = envelopeSizeX;

  // Target Dimensions
  double targetSizeX = 5. * inch;
  double targetSizeY = targetSizeX;
  double targetSizeZ = targetSizeX;

  // Scintillator Dimensions
  double scintillatorDiameter = 5. * inch;
  double scintillatorHeight   = 5. * inch;

  double tubeRadius     = 1.5 * inch;
  double tubeHalfHeight = 1.5 * inch;

  double envelopHalfHeight = 4.5 * inch;

  G4LogicalVolume *logicalEnvelop1 = (new CylindricalShell("LogicalEnvelope1", 8 * inch, 8 * inch + 10 * cm,
                                                           envelopHalfHeight, 0., 2 * M_PI, "G4_Pb"))
                                         ->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicalEnvelop1, "LogicalEnvelop1_Physical", logicalWorld, false, 0,
                    checkOverlaps);


G4LogicalVolume *logicalEnvelop2 = (new CylindricalShell("LogicalEnvelope2", 8 * inch+10*cm, 8 * inch + 20 * cm,
                                                           envelopHalfHeight, 0., 2 * M_PI, "ICS_BP"))
                                         ->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicalEnvelop2, "LogicalEnvelop2_Physical", logicalWorld, false, 0,
                    checkOverlaps);

  unsigned short numOfLayers = 3;
  G4LogicalVolume *logicalScintillator =
      (new CylindricalShell("NaI", 0., tubeRadius, tubeHalfHeight, 0., 2 * M_PI, "ICS_PS"))->GetLogicalVolume();
  // Placing Scintillators
  for (int layer = numOfLayers - 1; layer < numOfLayers; layer++) {

    for (int q = -layer; q < layer + 1; q++) {
      short r1 = std::max(-layer, -q - layer);
      short r2 = std::min(layer, -q + layer);
      std::cout << "== Layer : " << layer << " : Q : " << q << " : === R1 : " << r1 << " : R2 : " << r2
                << " =====================" << std::endl;
      for (short r = r1; r < r2 + 1; r++) {

        double x = tubeRadius * 2 * (q + r / 2.);
        double y = tubeRadius * 2 / std::sqrt(3) * 1.5 * r;

        std::cout << "x : " << x <<" : y : " << y << std::endl;

        new G4PVPlacement(0, G4ThreeVector(x, y, 0.), logicalScintillator, "Scintillator_Physical", logicalWorld, false,
                          0, checkOverlaps);
      }
    }
  }

  SD *scintSD = new SD("SensitiveScintillator");
  fSDMan->AddNewDetector(scintSD);
  logicalScintillator->SetSensitiveDetector(scintSD);

  std::cout << "========== TOTAL WEIGHT of DETECTOR =============" << std::endl;
  std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "=================================================" << std::endl;
  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  /*
  SD *hollowSD = new SD("SensitiveHollowSpace");

  G4int threadId = G4Threading::G4GetThreadId();
  std::cout <<"AYUSH PUShing SD for thread : " << threadId << std::endl;
  vecOfSD[threadId]=hollowSD;
  fSDMan->AddNewDetector(hollowSD);
  logicalHollowSpace->SetSensitiveDetector(hollowSD);
  */
}
