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
#include <G4Threading.hh>
#include <G4RunManager.hh>
#include "G4UserRunAction.hh"
#include "RunAction.h"

SD::~SD()
{
  // TODO Auto-generated destructor stub
  // delete fData;
}

SD::SD(const G4String &name) : G4VSensitiveDetector(name), fDetName(name)
{
  /*numOfParticlesReached = 0;
  numOfEventsProcessed = 0;
  fVecOfSD.push_back(fDetName);
  G4String fileName = (name+"_"+std::to_string(G4Threading::G4GetThreadId()) + ".root");
  std::cout << "Filename for Thread : " << G4Threading::G4GetThreadId() <<" : " << fileName << std::endl;
  fp = new TFile(fileName.c_str(),"RECREATE");
  */
  fData = new Data();
}

void SD::Initialize(G4HCofThisEvent *hce)
{
  // clear the map
  fEventData.clear();
}

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  G4Track *track              = aStep->GetTrack();
  G4String particleName       = track->GetDefinition()->GetParticleName();
  double dE                   = aStep->GetTotalEnergyDeposit();
  G4TouchableHandle touchable = track->GetTouchableHandle();
  unsigned short copyNo       = touchable->GetCopyNumber();
  // std::cout << "DE : " << dE << std::endl;
  // Storing only if the energy deposited in a step is greater than 0
  if (dE * 1000. > 0.) {
    if (fEventData.count(copyNo)) {
      // copy number found
      fEventData[copyNo] += dE;
    } else {
      // insert the energy for the new copy number
      fEventData[copyNo] = dE;
    }
  }
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *)
{
  const G4UserRunAction *constRunAction = G4RunManager::GetRunManager()->GetUserRunAction();
  RunAction *runAction                  = const_cast<RunAction *>(dynamic_cast<const RunAction *>(constRunAction));
  runAction->fEventNo++;

  if (!(runAction->fEventNo % 100000) && runAction->fEventNo != 0)
    std::cout << "Event Processed : " << runAction->fEventNo << std::endl;
  // std::cout <<"======== Event Number : " << runAction->fEventNo << "=========" << std::endl;
  for (const auto &pair : fEventData) {
    // std::cout << "CopyNumber : " << pair.first << " , Energy : " << pair.second << std::endl;
    fData->Fill(runAction->fEventNo, pair.first, pair.second / keV);
  }
}
