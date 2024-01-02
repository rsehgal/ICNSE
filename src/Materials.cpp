/*
**	Filename : Materials.cpp
**	2024-01-02
**	username : rsehgal
*/
#include "Materials.h"
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>

Materials::Materials() {
  CreateBoratedPolyethylene();
  CreateHighDensityPolyethylene();
}

Materials::~Materials() {}

void Materials::CreateBoratedPolyethylene() {

  G4double density = 0.9 * g / cm3;
  fBP = new G4Material("BoratedPolyethylene", density, 2);
  /* Define elements and materials (if not already defined)
  ** We are trying to define Borated Polyethylene with required % of Boron
  */
  G4Element *elB = new G4Element("Boron", "B", 5, 10.811 * g / mole);
  fBP->AddElement(elB, 0.15); // 15% Boron
  G4NistManager *nistManager = G4NistManager::Instance();
  G4Material *polyethylene = G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE");
  fBP->AddMaterial(polyethylene, 0.85);
}

void Materials::CreateHighDensityPolyethylene() {
  double density = 3.0;
  G4NistManager *nistManager = G4NistManager::Instance();
  nistManager->BuildMaterialWithNewDensity("HDPE", "G4_POLYETHYLENE", density);
  fHDPE = G4NistManager::Instance()->FindOrBuildMaterial("HDPE");
}

G4Material *Materials::GetBP() const { return fBP; }
G4Material *Materials::GetHDPE() const { return fHDPE; }

void RegisterMaterial(G4Material *material) {
  // G4NistManager *nistManager = G4NistManager::Instance();
  // nistManager->RegisterMaterial(material);
}
