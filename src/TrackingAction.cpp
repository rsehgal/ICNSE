/*
**	Filename : TrackingAction.cpp
**	2024-01-31
**	username : rsehgal
*/
#include "TrackingAction.h"
#include <G4Step.hh>
#include <G4String.hh>
#include <G4TouchableHandle.hh>
#include <G4Track.hh>
#include <G4TrackVector.hh>
#include <G4TrackingManager.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VProcess.hh>
#include <colors.h>
#include <iostream>

TrackingAction::TrackingAction() : G4UserTrackingAction() {}
TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track *aTrack) {}

void TrackingAction::PostUserTrackingAction(const G4Track *aTrack) {
  const G4VProcess *creatorProcess = aTrack->GetCreatorProcess();
  std::string volName = aTrack->GetTouchable()->GetVolume()->GetName();

  if(volName=="InnerCopperShell_Physical"){
  std::string processName = "";

  if (creatorProcess) {
    // std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
    processName = creatorProcess->GetProcessName();
  } else {
    processName = "Starter";
  }

  if(aTrack->GetTrackID()==1)
  std::cout << BLUE << "======= TRACK ID : " << aTrack->GetTrackID() << " : ParentID : " << aTrack->GetParentID()
            << " : Particle : " << aTrack->GetParticleDefinition()->GetParticleName()
            << " : KE : " << aTrack->GetVertexKineticEnergy()
            << " : Creator : " << processName
            << " : Volume : " << aTrack->GetOriginTouchable()->GetVolume()->GetName() << " ========" 
            << RESET
            << std::endl;
  else
  std::cout << GREEN << "======= TRACK ID : " << aTrack->GetTrackID() << " : ParentID : " << aTrack->GetParentID()
            << " : Particle : " << aTrack->GetParticleDefinition()->GetParticleName() 
            << " : KE : " << aTrack->GetVertexKineticEnergy()
            << " : Creator : " << processName
            << " : Volume : " << aTrack->GetOriginTouchable()->GetVolume()->GetName() << " ========" 
            << RESET
            << std::endl;
  G4TrackVector *secTracks = fpTrackingManager->GimmeSecondaries();
#define VERBOSE
#ifdef VERBOSE
  std::cout << RED << "No of Secondaries produced : " << secTracks->size() << RESET << std::endl;
#endif
}

#if (0)
  if (secTracks) {
    for (unsigned int i = 0; i < secTracks->size(); i++) {
      const G4VProcess *creatorProcess = secTracks->at(i)->GetCreatorProcess();
      std::string processName = "";
      if (secTracks->at(i)->GetTrackID() == 1)
        processName = "Sehgal";

      if (creatorProcess) {
        // std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
        processName = creatorProcess->GetProcessName();
      }
#ifdef VERBOSE
      std::cout << GREEN << "Secondary Tracks : TrackID : "
                << secTracks->at(i)->GetTrackID()
                //<< " :: Particle Name : " << particleName
                << " :: ParentID : " << secTracks->at(i)->GetParentID() << " :: ProcessName : " << processName
                << " :: In Volume : " << secTracks->at(i)->GetVolume()->GetName() << RESET << std::endl;
#endif
    }
  }
#endif
  /*
    if (secTracks) {
      for (unsigned int i = 0; i < secTracks->size(); i++) {
        const G4VProcess *creatorProcess = secTracks->at(i)->GetCreatorProcess();
        std::string processName = "";
        if (secTracks->at(i)->GetTrackID() == 1)
          processName = "Sehgal";

        if (creatorProcess) {
          // std::cout << "Process that creates gamma : " << creatorProcess->GetProcessName() << std::endl;
          processName = creatorProcess->GetProcessName();
        }

        std::cout << "Secondary Tracks : " << secTracks->at(i)->GetTrackID()
                << " :: ParentID : " << secTracks->at(i)->GetParentID() << " :: ProcessName : " << processName
                << " :: In Volume : " << secTracks->at(i)->GetVolume()->GetName() << std::endl;
      }
    }
    */
}
