/*
**	Filename : SD.h
**	2023-12-29
**	username : rsehgal
*/
#ifndef SD_h
#define SD_h


#include "G4VSensitiveDetector.hh"
#include "vector"

class G4Step;
class G4HCofThisEvent;

class SD : public G4VSensitiveDetector {

public:
	//SD();
	SD(const G4String& name,
	                const G4String& hitsCollectionName);
	virtual ~SD();

	// methods from base class
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
	static int numOfParticlesReached;


};

#endif 
