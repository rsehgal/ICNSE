/*
 *	Filename : BoxShell.cpp
 **	2024-01-02
 **	username : rsehgal
 */
#include "Geometry.h"
#include <G4SubtractionSolid.hh>
#include <G4Box.hh>

BoxShell::BoxShell() {}

BoxShell::BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness, G4String material) {
         G4Box* outerBox = new G4Box("OuterBox",halfx,halfy,halfz);
        G4Box* innerBox = new G4Box("InnerBox",halfx-thickness,halfy-thickness,halfz-thickness);
        fSolid = new G4SubtractionSolid(name, outerBox, innerBox, 0, G4ThreeVector(0.,0.,0.));
        SetProperties(material, fSolid);
}

BoxShell::BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness, G4Material *material) {
        G4Box* outerBox = new G4Box("OuterBox",halfx,halfy,halfz);
        G4Box* innerBox = new G4Box("InnerBox",halfx-thickness,halfy-thickness,halfz-thickness);
        fSolid = new G4SubtractionSolid(name, outerBox, innerBox, 0, G4ThreeVector(0.,0.,0.));
        SetProperties(material, fSolid);

}
