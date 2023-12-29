/*
**	Filename : Run.h
**	2023-12-29
**	username : rsehgal
*/
#ifndef Run_h
#define Run_h

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

    // method from the base class
    virtual void Merge(const G4Run*);
    
    void AddEdep (G4double edep); 
    void AddDivergence(double div){fTotalDivergence += div;}

    double GetDivergence(){return fTotalDivergence;}

    // get methods
    G4double GetEdep()  const { return fEdep; }
    G4double GetEdep2() const { return fEdep2; }

  private:
    G4double  fEdep;
    G4double  fEdep2;
    double fTotalDivergence;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


