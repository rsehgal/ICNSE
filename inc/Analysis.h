/*
**	Filename : Analysis.h
**	2024-01-09
**	username : rsehgal
*/
#ifndef Analysis_h
#define Analysis_h

#include <string>

class TH1F;
class TFile;

class Analysis{

private : 
static Analysis *s_instance;
Analysis(std::string filename);


//ROOT objects
TH1F *fHistGamma;
TFile *fp;


public:
static Analysis* Instance();
static Analysis* Create(std::string filename);
void FillGammaHistogram(double energy);
void Close();

};
#endif
