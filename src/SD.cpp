/*
 * SD.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "SD.h"
#include "Analysis.h"
#include "Data.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "Helpers.h"
#include <G4EventManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>
#include <TFile.h>
#include <TH1F.h>
#include <algorithm>

/*unsigned int SD::numOfParticlesReached = 0;
std::map<G4String,unsigned int> SD::fParticleCounter = {};
std::map<G4String,Data*> SD::fData = {};
*/
// int SD::numOfEventsProcessed = 0;

std::vector<G4String> SD::fVecOfSD = {};

SD::~SD() {
  // TODO Auto-generated destructor stub
  // delete fp;
}

SD::SD(const G4String &name) : G4VSensitiveDetector(name), fDetName(name) {
  numOfParticlesReached = 0;
  numOfEventsProcessed = 0;
  fVecOfSD.push_back(fDetName);
  G4String fileName = (name + ".root");
  // fp = new TFile(fileName.c_str(),"RECREATE");
}

void SD::Initialize(G4HCofThisEvent *hce) { fVecOfTrackID.clear(); }

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {

  G4Track *track = aStep->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();
#ifdef ICNSE_TRACK_ONLY_PRIMARY
  bool isPrimary = (track->GetParentID() == 0);
  if (isPrimary) {
    G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    std::cout << "RAMAN Particle Reached : " << particleName << " : VolumeName : " << touchable->GetVolume()->GetName()
              << std::endl;
    numOfParticlesReached++;
    track->SetTrackStatus(fStopAndKill);
    CheckAndCountParticle(particleName);
  }
#else
  std::string trackId = std::to_string(track->GetTrackID()) + "_" + std::to_string(numOfEventsProcessed);

#ifdef AVOID_DUPLICATE_COUNT
  if (!TrackFound(trackId))
#endif
  {
    // std::cout <<"========== Inserting : "<< trackId <<" ==========" << std::endl;
    fVecOfTrackID.push_back(trackId);
    numOfParticlesReached++;
    CheckAndCountParticle(particleName);
    double energy = track->GetKineticEnergy() / keV;
    const G4VProcess *creatorProcess = track->GetCreatorProcess();
    std::string processName = "";
    if (creatorProcess) {
      // std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
      processName = creatorProcess->GetProcessName();
      std::string physicalVolumeName = track->GetOriginTouchable()->GetVolume()->GetName();
      std::string physicalVolumeMaterial =
          track->GetOriginTouchable()->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName();
      CheckAndInsertParticleCreatorProcessAndEnergy(particleName, processName, energy, physicalVolumeName,
                                                    physicalVolumeMaterial);
    }
    // track->SetTrackStatus(fStopAndKill);
  }
  /*
  else{
    std::cout <<"========== NOT Inserting : "<< trackId <<" ==========" << std::endl;
  }
  */

#endif

  return true;
}

bool SD::TrackFound(std::string trackId) {
  bool found = false;
  if (fVecOfTrackID.size()) {
    found = (std::find(fVecOfTrackID.begin(), fVecOfTrackID.end(), trackId) != fVecOfTrackID.end());
  }
  return found;
}

void SD::CheckAndCountParticle(G4String particleName) {
  if (fParticleCounter.count(particleName)) {
    // Particle found
    fParticleCounter[particleName]++;
  } else {
    // Particle not found
    fParticleCounter[particleName] = 1;
  }
}

void SD::CheckAndInsertParticleCreatorProcessAndEnergy(G4String particleName, std::string processName, double energy) {

  if (fData.count(particleName)) {
    // Particle found
    fData[particleName]->Fill(numOfEventsProcessed, processName, energy);
  } else {
    // Particle not found
    fData[particleName] = new Data(particleName + "_" + fDetName);
    // To Fill Tree
    fData[particleName]->Fill(numOfEventsProcessed, processName, energy);
  }
}

void SD::CheckAndInsertParticleCreatorProcessAndEnergy(G4String particleName, std::string processName, double energy,
                                                       std::string physicalVolumeName,
                                                       std::string physicalVolumeMaterial) {

  if (fData.count(particleName)) {
    // Particle found
    fData[particleName]->Fill(numOfEventsProcessed, processName, energy, physicalVolumeName, physicalVolumeMaterial);
  } else {
    // Particle not found
    fData[particleName] = new Data(particleName + "_" + fDetName);
    // To Fill Tree
    fData[particleName]->Fill(numOfEventsProcessed, processName, energy, physicalVolumeName, physicalVolumeMaterial);
  }
}

void SD::CheckAndInsertParticleEnergy(G4String particleName, double energy) {
  if (fData.count(particleName)) {
    // Particle found
    fData[particleName]->Fill(energy);
  } else {
    // Particle not found
    fData[particleName] = new Data(particleName);
    // To Fill Histogram
    // fData[particleName]->Fill(energy);
  }
}

void SD::EndOfEvent(G4HCofThisEvent *) {
  numOfEventsProcessed++;
  if (!(numOfEventsProcessed % 100000) && numOfEventsProcessed != 0) {
    // std::cout << "Number of Events Processed : " << numOfEventsProcessed << std::endl;
    PrintSummary(fDetName, numOfEventsProcessed);
  }
}

// Required Getters
const unsigned int SD::GetGetNumberOfParticlesReachedSD() const { return numOfParticlesReached; }
const std::map<G4String, Data *> SD::GetData() const { return fData; }
const std::map<G4String, unsigned int> SD::GetParticleCounter() const { return fParticleCounter; }

TFile *SD::GetFilePointer() const { return fp; }

std::vector<G4String> SD::GetVecOfSD() const { return fVecOfSD; }