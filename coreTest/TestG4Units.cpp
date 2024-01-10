/*
**	Filename : TestG4Units.cpp
**	2024-01-09
**	username : rsehgal
*/
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <iostream>

int main() {
  std::cout << "cm : " << cm << std::endl;
  std::cout << "gram : " << g << std::endl;
  std::cout << "keV : " << keV << std::endl;
  std::cout << "MeV : " << MeV << std::endl;
  std::cout << "GeV : " << GeV << std::endl;

  // Example to calculate the weight of a logical volume
  G4Box *box = new G4Box("TestBox", 5 * cm, 5 * cm, 5 * cm);
  G4LogicalVolume *logicalBox =
      new G4LogicalVolume(box, G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb"), "LogicalBox");
  double density = logicalBox->GetMaterial()->GetDensity();
  double cubicVolume = logicalBox->GetSolid()->GetCubicVolume();
  double mass = (density * cubicVolume) / g;
  std::cout << "Mass of the box : " << mass << std::endl;

  return 0;
}
