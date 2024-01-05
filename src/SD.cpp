/*
 * SD.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "SD.h"
#include "Helpers.h"
int SD::numOfParticlesReached = 0;
std::map<G4String,unsigned int> SD::fParticleCounter = {};
//int SD::numOfEventsProcessed = 0;


SD::~SD() {
  // TODO Auto-generated destructor stub
}

SD::SD(const G4String &name) : G4VSensitiveDetector(name) {

}

void SD::Initialize(G4HCofThisEvent *hce) { }

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {

  G4Track *track = aStep->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();
  #ifdef TRACK_ONLY_PRIMARY
  bool isPrimary = (track->GetParentID() == 0);
  if (isPrimary) {
    G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    std::cout << "RAMAN Particle Reached : " << particleName << std::endl;
    numOfParticlesReached++;
    track->SetTrackStatus(fStopAndKill);
    CheckAndCountParticle(particleName);
  }
  #else
  numOfParticlesReached++;
  CheckAndCountParticle(particleName);
  #endif

  return true;
}
void SD::CheckAndCountParticle(G4String particleName){
if (fParticleCounter.count(particleName)) {
        // Particle found
        fParticleCounter[particleName]++;
    } else {
        // Particle not found
        fParticleCounter[particleName]=1;
    }
}

void SD::EndOfEvent(G4HCofThisEvent *) {
  numOfEventsProcessed++;
  if(!(numOfEventsProcessed%100000) && numOfEventsProcessed!=0){
    std::cout << "Number of Events Processed : " << numOfEventsProcessed << std::endl;
    PrintSummary(numOfEventsProcessed);
  }
}
