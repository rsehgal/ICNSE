/*
**	Filename : Data.cpp
**	2024-01-10
**	username : rsehgal
*/
#include "Data.h"
#include <TH1F.h>
#include <TTree.h>
#include <iostream>

Data::Data() {
  fParticleName = "geantino";
  fHist = new TH1F(fParticleName.c_str(), fParticleName.c_str(), 1000, 0, 8000);
  fTree = new TTree(fParticleName.c_str(), fParticleName.c_str());
  fTree->Branch("EventNum", &fEvNo);
  fTree->Branch("CreatorProcess", &fProcessName);
  fTree->Branch("PhysicalVolumeName", &fPhysicalVolumeName);
  fTree->Branch("Material", &fMaterial);
  fTree->Branch("Energy", &fEnergy);
}

Data::Data(std::string particleName) : fParticleName(particleName) {

  fHist = new TH1F(fParticleName.c_str(), fParticleName.c_str(), 1000, 0, 8000);
  fTree = new TTree(fParticleName.c_str(), fParticleName.c_str());
  fTree->Branch("EventNum", &fEvNo);
  fTree->Branch("CreatorProcess", &fProcessName);
  fTree->Branch("PhysicalVolumeName", &fPhysicalVolumeName);
  fTree->Branch("Material", &fMaterial);
  fTree->Branch("Energy", &fEnergy);
}

Data::~Data() {}

unsigned int Data::GetCount() const { return fHist->GetEntries(); }

void Data::Fill(unsigned int evNo, std::string processName, double energy) {
  fEvNo = evNo;
  fProcessName = processName;
  fEnergy = energy;
  Fill();
}

void Data::Fill(unsigned int evNo, std::string processName, double energy,std::string physicalVolumeName,std::string material) {
  fEvNo = evNo;
  fProcessName = processName;
  fPhysicalVolumeName = physicalVolumeName;
  fMaterial = material;
  fEnergy = energy;
  Fill();
}

void Data::Fill(double energy) { fHist->Fill(energy); }

void Data::Fill() { Fill(fEnergy);fTree->Fill(); }

void Data::Write() {
  // fHist->Write();
  fTree->Write();
}