/*
**	Filename : RadioactiveSource.cpp
**	2024-01-12
**	username : rsehgal
*/
#include<iostream>
#include "RadioactiveSource.h"
#include <G4ParticleDefinition.hh>
#include <G4IonTable.hh>
#include <G4DecayTable.hh>
#include <G4Decay.hh>
#//include <G4DecayChannel.hh>

RadioactiveSource::RadioactiveSource(){}

RadioactiveSource::RadioactiveSource(int z, int a, int q) : fZ(z), fA(a), fQ(q)
{
    G4IonTable* ionTable = G4IonTable::GetIonTable();
    fParticle = ionTable->GetIon(fZ, fA, fQ);  

    G4DecayTable* decayTable = new G4DecayTable();
    fParticle->SetDecayTable(decayTable);

    // Add a beta-minus decay channel
    //Should be in the respective derived class
    //G4VDecayChannel* betaChannel = new G4BetaMinusDecayChannel();
    //decayTable->Insert(betaChannel);

    // Set the decay process for Cs-137
    G4Decay* decay = new G4Decay();
    //fParticle->SetDecay(decay);

}

RadioactiveSource::~RadioactiveSource(){}

G4ParticleDefinition* RadioactiveSource::GetSource() const{
    return fParticle;
}