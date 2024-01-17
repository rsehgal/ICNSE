/*
**	Filename : ActionInitialization.h
**	2023-12-29
**	username : rsehgal
*/
#ifndef ActionInitialization_h
#define ActionInitialization_h

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization {
public:
  ActionInitialization();
  virtual ~ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
