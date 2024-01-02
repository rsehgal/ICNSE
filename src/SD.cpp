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
int SD::numOfParticlesReached = 0;


SD::~SD() {
  // TODO Auto-generated destructor stub
}

SD::SD(const G4String &name) : G4VSensitiveDetector(name) {

}

void SD::Initialize(G4HCofThisEvent *hce) {  }

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *) {

  G4Track *track = aStep->GetTrack();
  bool isPrimary = (track->GetParentID() == 0);

  if (isPrimary) {
    G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
    G4String particleName = track->GetDefinition()->GetParticleName();
    std::cout << "RAMAN Particle Reached : " << particleName << std::endl;
    numOfParticlesReached++;
    track->SetTrackStatus(fStopAndKill);
  }

  /*bool isSecondary = (track->GetParentID() == 1);
  G4String particleName = track->GetDefinition()->GetParticleName();
  const G4VProcess *creatorProcess = track->GetCreatorProcess();
  */
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *) {}
