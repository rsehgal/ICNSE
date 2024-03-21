/*
**	Filename : Data.cpp
**	2024-01-10
**	username : rsehgal
*/
#include "Data.h"
#include <TTree.h>
#include <iostream>
#include "RunAction.h"
#include <G4RunManager.hh>
#include <TFile.h>

Data::Data()
{
  fTree = new TTree("data", "data");
  fTree->Branch("EventNum", &fEvNo);
  fTree->Branch("ScintId", &fScintId);
  fTree->Branch("Energy", &fEnergy);
}

Data::~Data()
{
  const G4UserRunAction *constRunAction = G4RunManager::GetRunManager()->GetUserRunAction();
  RunAction *runAction                  = const_cast<RunAction *>(dynamic_cast<const RunAction *>(constRunAction));
  //runAction->fOutFile->cd();
  //Write();
}

unsigned int Data::GetCount() const
{
  // return fHist->GetEntries();
  return fTree->GetEntries();
}

void Data::Fill(unsigned int evNo, unsigned int scintId, double energy)
{
  fEvNo    = evNo;
  fScintId = scintId;
  fEnergy  = energy;
  Fill();
}

void Data::Fill()
{
  fTree->Fill();
}

void Data::Write()
{
  fTree->Write();
}