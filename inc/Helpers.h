/*
**	Filename : Helpers.h
**	2024-01-05
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h

#include <vector>
#include <G4String.hh>
class G4LogicalVolume;

extern void PrintSummary(unsigned int numOfEvents);
extern void PrintSummary(G4String sdName, unsigned int numOfEvents);
extern double GetLogicalVolumeWeight(G4LogicalVolume *logicalVolume);
extern void Write(G4String sdName);
extern void WriteSD(G4String sdName);

#endif
