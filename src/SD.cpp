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
#include "Analysis.h"
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>
#include <G4EventManager.hh>
#include <TH1F.h>
#include "Data.h"

int SD::numOfParticlesReached = 0;
std::map<G4String,unsigned int> SD::fParticleCounter = {};
std::map<G4String,Data*> SD::fData = {};
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
    std::cout << "RAMAN Particle Reached : " << particleName << " : VolumeName : "<< touchable->GetVolume()->GetName() << std::endl;
    numOfParticlesReached++;
    track->SetTrackStatus(fStopAndKill);
    CheckAndCountParticle(particleName);
  }
  #else
  numOfParticlesReached++;
  if(particleName=="gamma"){

    /*const G4VProcess *creatorProcess = track->GetCreatorProcess();
    if(creatorProcess){
      std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
      const G4Track* parentTrack = G4EventManager::GetEventManager()->GetTrackingManager()->GetTrack(track->GetParentID());
      G4String parentParticleName = parentTrack->GetDefinition()->GetParticleName();
      std::cout << "Parent Particle name : " << parentParticleName << std::endl;
      std::cout <<"------------------------------------------------" << std::endl;
    }*/
  // std::cout << "Energy of Gamma : " << track->GetKineticEnergy()/keV << std::endl;
  //Analysis::Instance()->FillGammaHistogram(track->GetKineticEnergy()/keV);
  }
  CheckAndCountParticle(particleName);
  double energy = track->GetKineticEnergy()/keV;
  //CheckAndInsertParticleEnergy(particleName,energy);

  const G4VProcess *creatorProcess = track->GetCreatorProcess();
  std::string processName = "";
  if(creatorProcess){
      //std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
       processName = creatorProcess->GetProcessName() ;
  }
  CheckAndInsertParticleCreatorProcessAndEnergy(particleName,processName,energy);
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

void SD::CheckAndInsertParticleCreatorProcessAndEnergy(G4String particleName,
std::string processName, double energy ){

if (fData.count(particleName)) {
        // Particle found
        fData[particleName]->Fill(numOfEventsProcessed,processName,energy);
    } else {
        // Particle not found
        fData[particleName]=new Data(particleName);
        //To Fill Tree
        fData[particleName]->Fill(numOfEventsProcessed,processName,energy);
    }

}
void SD::CheckAndInsertParticleEnergy(G4String particleName, double energy){
if (fData.count(particleName)) {
        // Particle found
        fData[particleName]->Fill(energy);
    } else {
        // Particle not found
        fData[particleName]=new Data(particleName);
        //To Fill Histogram
        //fData[particleName]->Fill(energy);
    }
}

void SD::EndOfEvent(G4HCofThisEvent *) {
  numOfEventsProcessed++;
  if(!(numOfEventsProcessed%100000) && numOfEventsProcessed!=0){
    std::cout << "Number of Events Processed : " << numOfEventsProcessed << std::endl;
    PrintSummary(numOfEventsProcessed);
  }
}
