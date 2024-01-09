/*
**	Filename : Helpers.cpp
**	2024-01-05
**	username : rsehgal
*/
#include "Helpers.h"
#include "SD.h"
#include <G4SystemOfUnits.hh>
#include <G4VSolid.hh>
#include <iostream>
void PrintSummary(unsigned int numOfEvents) {
  std::cout << "================== SUMMARY ===========================================" << std::endl;
  std::cout << "Total Number of Event : " << numOfEvents << std::endl;
  std::cout << "No of Particles reaches Sensitive Detector Region : " << SD::numOfParticlesReached << std::endl;
  std::cout << "===================Particle breakup are as follow ====================" << std::endl;
  for (const auto &pair : SD::fParticleCounter) {
    std::cout << "Particle : " << pair.first << " , Count : " << pair.second << std::endl;
  }

  std::cout << "======================================================================" << std::endl;
}

double GetLogicalVolumeWeight(G4LogicalVolume *logicalVolume) {
  // World volume should not be considered for weight calculation
  double weight = (logicalVolume->GetMaterial()->GetDensity() * logicalVolume->GetSolid()->GetCubicVolume()) / kg;
  std::cout << "Volume Name : " << logicalVolume->GetName() << " : Material : " << logicalVolume->GetMaterial()->GetName() << " : Weight(Kg) : " << weight << std::endl;
  if (logicalVolume->GetSolid()->GetName() == "World")
    weight = 0.;
  unsigned int noOfDaughters = logicalVolume->GetNoDaughters();
  for (unsigned int i = 0; i < noOfDaughters; i++) {
    weight += GetLogicalVolumeWeight(logicalVolume->GetDaughter(i)->GetLogicalVolume());
  }
  return weight;
}
