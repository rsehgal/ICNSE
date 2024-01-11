/*
**	Filename : SD.h
**	2023-12-29
**	username : rsehgal
*/
#ifndef SD_h
#define SD_h


#include "G4VSensitiveDetector.hh"
#include "vector"
#include <map>
class G4Step;
class G4HCofThisEvent;
class G4String;
class TH1F;
class Data;
class TFile;

class SD : public G4VSensitiveDetector {
	private:
	//static 
	unsigned int numOfEventsProcessed;

	public:
	//static 
	std::map<G4String,unsigned int> fParticleCounter;
	//static 
	std::map<G4String,Data*> fData;
	//static 
	unsigned int numOfParticlesReached;

	static std::vector<G4String> fVecOfSD;

	std::string fDetName;


	TFile *fp;

public:
	//SD();
	SD(const G4String& name);
	virtual ~SD();

	// methods from base class
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
	void CheckAndCountParticle(G4String particleName );
	void CheckAndInsertParticleEnergy(G4String particleName,double energy );
	void CheckAndInsertParticleCreatorProcessAndEnergy(G4String particleName,std::string processName, double energy );
	

	//Required Getters
	const unsigned int GetGetNumberOfParticlesReachedSD() const ;
	const std::map<G4String,Data*> GetData() const;
	const std::map<G4String,unsigned int> GetParticleCounter() const;
	TFile* GetFilePointer() const;
	std::vector<G4String> GetVecOfSD() const;
	


};

#endif 
