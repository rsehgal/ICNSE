/*
**	Filename : Geometry.cpp
**	2024-01-01
**	username : rsehgal
*/
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4String.hh>
#include <G4Tubs.hh>
#include <G4VSolid.hh>
#include <iostream>
//#include "GeometryMessenger.h"
#include <G4GenericMessenger.hh>
#include <G4RunManager.hh>
#include <vector>
#include <G4LogicalSkinSurface.hh>
#include <G4SurfaceProperty.hh>
#include "Materials.h"

std::vector<G4LogicalVolume *> vecOfLogicalVolumes;

GeometryProperties::GeometryProperties() {}

GeometryProperties::GeometryProperties(G4Material *material, G4VSolid *solid) {
  fLogicalVolume = new G4LogicalVolume(solid, material, solid->GetName() + "_Logical");
}
GeometryProperties::GeometryProperties(G4String material, G4VSolid *solid) {

  G4NistManager *nist = G4NistManager::Instance();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  fLogicalVolume = new G4LogicalVolume(solid, solid_material, solid->GetName() + "_Logical");
  // fGeometryMessenger = new DetectorMessenger(this);
  DefineCommands();
}

void GeometryProperties::DefineCommands() {

  fGeometryMessenger = new G4GenericMessenger(this, "/ICNSE/", "Material Name");
  fGeometryMessenger->DeclareMethod("setMaterial", &GeometryProperties::SetMaterial,
                                    "Set the material of your geometry");
  fGeometryMessenger->DeclareMethod("setInnerRadius", &GeometryProperties::SetInnerRadius,
                                    "Set the Inner Radius of Cylindrical Shell");
  fGeometryMessenger->DeclareMethod("setOuterRadius", &GeometryProperties::SetOuterRadius,
                                    "Set the Outer Radius of Cylindrical Shell");
}
void GeometryProperties::SetProperties(G4String material, G4VSolid *solid) {

  //G4NistManager *nist = G4NistManager::Instance();
  Materials *nist = Materials::Instance();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  fLogicalVolume = new G4LogicalVolume(solid, solid_material, solid->GetName() + "_Logical");
  vecOfLogicalVolumes.push_back(fLogicalVolume);
  DefineCommands();
}

void GeometryProperties::SetProperties(G4Material *material, G4VSolid *solid) {

  fLogicalVolume = new G4LogicalVolume(solid, material, solid->GetName() + "_Logical");
  vecOfLogicalVolumes.push_back(fLogicalVolume);
  //DefineCommands();
}

GeometryProperties::~GeometryProperties() {}

void GeometryProperties::SetInnerRadius(G4String logicalVolumeName, double innerRad) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Tubs *tubs = dynamic_cast<G4Tubs *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      tubs->SetInnerRadius(innerRad);
      // std::cout << "After material change : " << vecOfLogicalVolumes[i]->GetMaterial()->GetName() << std::endl;
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetOuterRadius(G4String logicalVolumeName, double outerRad) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Tubs *tubs = dynamic_cast<G4Tubs *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      tubs->SetOuterRadius(outerRad);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetMaterial(G4String logicalVolumeName, G4String material) {
  //G4NistManager *nist = G4NistManager::Instance();
  Materials *nist = Materials::Instance();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  if (solid_material)
    fMaterial = solid_material;
  else
    std::cout << "Material Not found : " << std::endl;

  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "--------------------------------------" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName)
      vecOfLogicalVolumes[i]->SetMaterial(fMaterial);

      #ifdef ENABLE_OPTICAL_PHYSICS
        //std::cout << "Adding Reflective surfaces" << std::endl;
        G4SurfaceProperty *opticalMirror = Materials::Instance()->GetMirror("opticalMirror");
        //G4LogicalSkinSurface *skin1 = 
        const G4String skinName = logicalVolumeName+"_OpticalSkin";
        new G4LogicalSkinSurface(skinName, vecOfLogicalVolumes[i], opticalMirror);
      #endif
    std::cout << "After material change : " << vecOfLogicalVolumes[i]->GetMaterial()->GetName() << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

G4Material *GeometryProperties::GetMaterial() const { return fMaterial; }

G4LogicalVolume *GeometryProperties::GetLogicalVolume() const { return fLogicalVolume; }

// Cylindrical Shell
CylindricalShell::CylindricalShell() {}

CylindricalShell::~CylindricalShell() {}

CylindricalShell::CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi, G4String material) {
  fSolid = new G4Tubs(name, rmin, rmax, dz, sphi, dphi);
  SetProperties(material, fSolid);
  // GeometryProperties("G4_Al", fSolid);
}

CylindricalShell::CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi, G4Material *material) {
  fSolid = new G4Tubs(name, rmin, rmax, dz, sphi, dphi);
  SetProperties(material, fSolid);
  // GeometryProperties("G4_Al", fSolid);
}