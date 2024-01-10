/*
**	Filename : Data.cpp
**	2024-01-10
**	username : rsehgal
*/
#include<iostream>
#include "Data.h"
#include <TH1F.h>

Data::Data(){
    fParticleName = "geantino";
    fHist = new TH1F(fParticleName.c_str(),fParticleName.c_str(),1000,0,8000);
}

Data::Data(std::string particleName) : fParticleName(particleName){

    fHist = new TH1F(fParticleName.c_str(),fParticleName.c_str(),1000,0,8000);
}

Data::~Data(){}

unsigned int Data::GetCount() const {
    return fHist->GetEntries();
}

void Data::Fill(double energy){
    fHist->Fill(energy);
}

void Data::Write(){
    fHist->Write();
}