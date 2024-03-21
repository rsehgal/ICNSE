/*
**	Filename : Helpers.cpp
**	2024-01-05
**	username : rsehgal
*/
#include "Helpers.h"
#include "Data.h"
#include "SD.h"
#include <G4Run.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <TFile.h>
#include <iostream>
#include <G4Threading.hh>
#include "G4AutoLock.hh"
#include "DetectorConstruction.h"
#include <mutex>

//G4Mutex myMutex = G4MUTEX_INITIALIZER;
std::mutex myMutex;
/*
void WriteSD(G4String sdName) {
  unsigned int nofEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  // PrintSummary(sdName,nofEvents);
  Write(sdName);
}
*/
/*
void PrintSummary(G4String sdName, unsigned int numOfEvents) {
  unsigned int totalNumOfEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  std::cout << "================== SUMMARY ===========================================" << std::endl;
  std::cout << "Total Number of Event processed: " << numOfEvents << " / " << totalNumOfEvents << std::endl;
  // std::cout << "No of Particles reaches Sensitive Detector Region : " << SD::numOfParticlesReached << std::endl;
  std::cout << "===================Particle breakup are as follow ====================" << std::endl;
  SD *sd = static_cast<SD *>(G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdName));
  std::cout << "No of Particles reaches Sensitive (" << sdName
            << ") Detector Region : " << sd->GetGetNumberOfParticlesReachedSD() << std::endl;
  for (const auto &pair : sd->GetParticleCounter())
  // SD::fParticleCounter)
  {
    std::cout << "Particle : " << pair.first << " , Count : " << pair.second << std::endl;
  }

  std::cout << "======================================================================" << std::endl;
}

void PrintSummary(unsigned int numOfEvents) {
  std::cout << "================== SUMMARY ===========================================" << std::endl;
  std::cout << "Total Number of Event : " << numOfEvents << std::endl;
  // std::cout << "No of Particles reaches Sensitive Detector Region : " << SD::numOfParticlesReached << std::endl;
  std::cout << "===================Particle breakup are as follow ====================" << std::endl;
  // for (const auto &pair : SD::fParticleCounter)
  SD *sd = static_cast<SD *>(G4SDManager::GetSDMpointer()->FindSensitiveDetector("SensitiveHollowSpace"));
  std::cout << "No of Particles reaches Sensitive Detector Region : " << sd->GetGetNumberOfParticlesReachedSD()
            << std::endl;
  for (const auto &pair : sd->GetParticleCounter()) {
    std::cout << "Particle : " << pair.first << " , Count : " << pair.second << std::endl;
  }

  std::cout << "======================================================================" << std::endl;
}


void Write(G4String sdName) {
//G4AutoLock lock(&myMutex);
  // for (const auto &pair : SD::fData) {
  //std::cout << "RAMAN : " << G4Threading::G4GetThreadId() << std::endl;  
  //SD *sd = static_cast<SD *>(G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdName));
  SD *sd =  DetectorConstruction::vecOfSD[G4Threading::G4GetThreadId()];
  sd->GetFilePointer()->cd();
  for (const auto &pair : sd->GetData()) {
     std::cout <<"ThreadID : "<< G4Threading::G4GetThreadId()<< " : Inside WRITE : Particle : " << pair.first << " , Count : " << pair.second->GetCount() << std::endl;
    pair.second->Write();
  }
  sd->GetFilePointer()->Close();
}

void DirectWrite() {
G4AutoLock lock(&myMutex);
  // for (const auto &pair : SD::fData) {
  //std::cout << "RAMAN : " << G4Threading::G4GetThreadId() << std::endl;  
  //SD *sd = static_cast<SD *>(G4SDManager::GetSDMpointer()->FindSensitiveDetector(sdName));
  SD *sd =  DetectorConstruction::vecOfSD[G4Threading::G4GetThreadId()];
  sd->GetFilePointer()->cd();
  for (const auto &pair : sd->GetData()) {
     std::cout <<"ThreadID : "<< G4Threading::G4GetThreadId()<< " : Inside WRITE : Particle : " << pair.first << " , Count : " << pair.second->GetCount() << std::endl;
    pair.second->Write();
  }
  sd->GetFilePointer()->Close();
}
*/
double GetLogicalVolumeWeight(G4LogicalVolume *logicalVolume) {
  // World volume should not be considered for weight calculation
  double weight = (logicalVolume->GetMaterial()->GetDensity() * logicalVolume->GetSolid()->GetCubicVolume()) / kg;
  std::cout << "Volume Name : " << logicalVolume->GetName()
            << " : Material : " << logicalVolume->GetMaterial()->GetName() << " : Weight(Kg) : " << weight << std::endl;
  if (logicalVolume->GetSolid()->GetName() == "World")
    weight = 0.;
  unsigned int noOfDaughters = logicalVolume->GetNoDaughters();
  for (unsigned int i = 0; i < noOfDaughters; i++) {
    weight += GetLogicalVolumeWeight(logicalVolume->GetDaughter(i)->GetLogicalVolume());
  }
  return weight;
}
