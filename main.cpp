/*
**	Filename : main.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "DetectorConstruction.h"
#include "ActionInitialization.h"

//#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "QGSP_BERT_HP.hh"
#include <Shielding.hh>
#include "G4OpticalPhysics.hh"


int main(int argc,char** argv)
{
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

G4RunManager *runManager = new G4RunManager;
  runManager->SetUserInitialization(new DetectorConstruction());

  G4VModularPhysicsList* physicsList = new Shielding;//QGSP_BERT_HP;//QBBC;

  runManager->SetUserInitialization(physicsList);

  #ifdef ENABLE_OPTICAL_PHYSICS
  G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  #endif
    
  runManager->SetUserInitialization(new ActionInitialization());

  
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  //Output::instance()->Close();
  delete visManager;
  delete runManager;
  //fp->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
