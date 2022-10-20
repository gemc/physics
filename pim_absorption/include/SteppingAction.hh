#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(const DetectorConstruction* detectorConstruction,
						EventAction* eventAction);
	virtual ~SteppingAction();
	
	virtual void UserSteppingAction(const G4Step* step);
	
private:
	const DetectorConstruction* fDetConstruction;
	EventAction*  fEventAction;
	G4LogicalVolume* fScoringVolume;
	
};

#endif