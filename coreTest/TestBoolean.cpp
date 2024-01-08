/*
**	Filename : TestBoolean.cpp
**	2024-01-08
**	username : rsehgal
*/
#include <G4Box.hh>
#include <G4String.hh>
#include <G4SubtractionSolid.hh>
#include <G4SystemOfUnits.hh>
#include <G4VSolid.hh>
#include <iostream>
int main(int argc, char *argv[]) {

  G4String name = "TestBoolean";
  double fHalfX = 80 * cm;
  double fHalfY = 80 * cm;
  double fHalfZ = 80 * cm;
  double fThickness = 10 * cm;
  G4Box *outerBox = new G4Box("OuterBox", fHalfX, fHalfY, fHalfZ);
  G4Box *innerBox = new G4Box("InnerBox", fHalfX - fThickness, fHalfY - fThickness, fHalfZ - fThickness);
  G4SubtractionSolid *boxShell = new G4SubtractionSolid(name, outerBox, innerBox);//, 0, G4ThreeVector(0., 0., 0.));

  G4VSolid *boxOuter = boxShell->GetConstituentSolid(0);
  G4VSolid *boxInner = boxShell->GetConstituentSolid(1);
  G4Box *boxOuterSolid = static_cast<G4Box *>(boxOuter);
  G4Box *boxInnerSolid = static_cast<G4Box *>(boxInner);

  std::cout << "Outer Solid " << std::endl;
  std::cout << boxOuterSolid->GetXHalfLength() << std::endl;

  std::cout << "Inner Solid " << std::endl;
  std::cout << boxInnerSolid->GetXHalfLength() << std::endl;

  std::cout << "Raw Inner Solid " << std::endl;
  std::cout << innerBox->GetXHalfLength() << std::endl;

  return 0;
}
