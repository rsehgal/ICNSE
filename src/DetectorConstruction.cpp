/*
**	Filename : DetectorConstruction.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "DetectorConstruction.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"
#include "SD.h"
#include "Geometry.h"
#include <G4SDManager.hh>

DetectorConstruction::DetectorConstruction(){
fSDMan = G4SDManager::GetSDMpointer();
}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
  
  // G4NistManager* nist = G4NistManager::Instance();
  //     
  // World
  //
  G4bool checkOverlaps = true;
  G4double world_sizeXYZ = 200*cm;
  G4LogicalVolume *logicalWorld = (new Box("World",0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ)
  )->GetLogicalVolume();
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicalWorld,            //its logical volume
                      "PhysicalWorld",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
double sheildingZ = 50*cm;
G4LogicalVolume *logicalShell0 = (new CylindricalShell("Shell0",25*cm,35*cm,sheildingZ,0,2*M_PI))->GetLogicalVolume();
//G4VPhysicalVolume *phyLeadBlock = 
                          new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            logicalShell0,
                            "Shell0_Physical",
                            logicalWorld,
                            false,
                            0,
                            checkOverlaps);

G4LogicalVolume *logicalShell1 = (new CylindricalShell("Shell1",35*cm,45*cm,sheildingZ,0,2*M_PI))->GetLogicalVolume();
//G4VPhysicalVolume *phyLeadBlock = 
                          new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            logicalShell1,
                            "Shell1_Physical",
                            logicalWorld,
                            false,
                            0,
                            checkOverlaps);

G4LogicalVolume *logicalHollowSpace = (new CylindricalShell("HollowSpace",0*cm,25*cm,sheildingZ,0,2*M_PI))->GetLogicalVolume();
//G4VPhysicalVolume *phyLeadBlock = 
                          new G4PVPlacement(0,
                            //G4ThreeVector(),
                            G4ThreeVector(),
                            logicalHollowSpace,
                            "HollowSpace_Physical",
                            logicalWorld,
                            false,
                            0,
                            checkOverlaps);

  SD *hollowSD = new SD("SensitiveHollowSpace");
  fSDMan->AddNewDetector(hollowSD);
  logicalHollowSpace->SetSensitiveDetector(hollowSD);

	return physWorld;

}
