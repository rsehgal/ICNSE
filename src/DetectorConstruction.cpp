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

  G4LogicalVolume *logicalEnvelope =
      (new Box("Envelope", 0.1 * envelopeSizeX, 0.5 * envelopeSizeY, 0.5 * envelopeSizeZ))->GetLogicalVolume();
  G4LogicalVolume *logicalTarget =
      (new Box("Target", 0.5 * targetSizeX, 0.5 * targetSizeY, 0.5 * targetSizeZ, "G4_Fe"))->GetLogicalVolume();
  G4LogicalVolume *logicalScintillator = (new CylindricalShell("Scintillator", 0, 0.5 * scintillatorDiameter,
                                                               0.5 * scintillatorHeight, 0., 2 * M_PI, "ICS_PS"))
                                             ->GetLogicalVolume();

  G4RotationMatrix *rotation = new G4RotationMatrix();
  rotation->rotateX(90 * deg);

  // Placing Target
  new G4PVPlacement(0, G4ThreeVector(0., 0., -0.5 * envelopeSizeY + 0.5 * targetSizeZ), logicalTarget,
                    "Target_Physical", logicalEnvelope, false, 0, checkOverlaps);
  /*new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalTarget, "Target_Physical", logicalEnvelope, false, 0,
                    checkOverlaps);*/

  // Placing Scintillators
  for (unsigned short i = 0; i < 10; i++) {
    new G4PVPlacement(rotation,
                      G4ThreeVector(0., 0.5 * envelopeSizeY - 0.5 * scintillatorHeight,
                                    -0.5 * envelopeSizeZ + (2 * i + 1) * 0.5 * scintillatorDiameter),
                      logicalScintillator, "Scintillator_Physical_" + std::to_string(i), logicalEnvelope, false, i,
                      checkOverlaps);
  }

  new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalEnvelope, "Envelope_Physical", logicalWorld, false, 0,
                    checkOverlaps);

  SD *scintSD = new SD("SensitiveScintillator");
  fSDMan->AddNewDetector(scintSD);
  logicalScintillator->SetSensitiveDetector(scintSD);

#ifdef ICS_INSPECT_SOURCE
  G4LogicalVolume *logicalSource = (new Box("Source", 0.5 * cm, 0.5 * cm, 0.5 * cm))->GetLogicalVolume();
  G4VPhysicalVolume *physSource  = new G4PVPlacement(0,                               // no rotation
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
