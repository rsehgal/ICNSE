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

  
  unsigned int fEvNo;
  double fEnergy;
  unsigned int fScintId;
  
  TTree *fTree;

public:
  Data();
  ~Data();
  unsigned int GetCount() const;
  void Fill(unsigned int evNo, unsigned int scintId, double energy);
  void Fill();
  void Write();
};

#endif
