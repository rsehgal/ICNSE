/*
**	Filename : Data.h
**	2024-01-10
**	username : rsehgal
*/
#ifndef Data_h
#define Data_h

#include <string>

class TH1F;

class Data{

std::string fParticleName;
TH1F *fHist;

public:

Data();
Data(std::string particleName);
~Data();
unsigned int GetCount () const;
void Fill(double energy);
void Write();

};

#endif
