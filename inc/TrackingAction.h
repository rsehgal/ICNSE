/*
**	Filename : TrackingAction.h
**	2024-01-31
**	username : rsehgal
*/
#ifndef TrackingAction_h
#define TrackingAction_h

#include <G4UserTrackingAction.hh>

class G4Track;
class G4UserTrackingAction;

class TrackingAction : public G4UserTrackingAction {
public:
  TrackingAction();
  ~TrackingAction();
  virtual void PreUserTrackingAction(const G4Track *aTrack);
  virtual void PostUserTrackingAction(const G4Track *aTrack);
};

#endif
