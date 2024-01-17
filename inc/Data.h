/*
**	Filename : Data.h
**	2024-01-10
**	username : rsehgal
*/
#ifndef Data_h
#define Data_h

#include <string>

class TH1F;
class TTree;

class Data {

  std::string fParticleName;
  std::string fProcessName;
  unsigned int fEvNo;
  double fEnergy;

  TH1F *fHist;
  TTree *fTree;

public:
  Data();
  Data(std::string particleName);
  ~Data();
  unsigned int GetCount() const;
  void Fill(unsigned int evNo, std::string processName, double energy);
  void Fill(double energy);
  void Fill();
  void Write();
};

#endif
