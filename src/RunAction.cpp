
#include "RunAction.h"
#include "PrimaryGeneratorAction.h"
#include "DetectorConstruction.h"
#include "Run.h"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <G4FastStep.hh>
#include <string.h>
//#include "B1EventAction.hh"
#include "SD.h"
#include "Helpers.h"
#include <G4VUserDetectorConstruction.hh>
#include <TFile.h>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//ofstream* RunAction::myfile=NULL;

RunAction::RunAction()
: G4UserRunAction()
{ 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{
  return new Run; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  const DetectorConstruction *userDetectorConstruction = 
  static_cast<const DetectorConstruction*>(
    G4RunManager::GetRunManager()->GetUserDetectorConstruction()
    );
  G4LogicalVolume *logicalWorld = userDetectorConstruction->GetLogicalWorld();
  std::cout << "@@@@@@@@@@@@@ Weight of Complete Detector @@@@@@@@@@@@" << std::endl;
  std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

  fOutFile = new TFile("icnse_data.root","RECREATE");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  PrintSummary(nofEvents);
  fOutFile->cd();
  Write();
  fOutFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

