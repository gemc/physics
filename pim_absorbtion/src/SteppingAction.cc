// this test
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

// geant4
#include "G4RunManager.hh"

SteppingAction::SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction) : G4UserSteppingAction(),
fDetConstruction(detectorConstruction),
fEventAction(eventAction),
fScoringVolume(0)
{}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	if (!fScoringVolume) {
		const DetectorConstruction* detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
		fScoringVolume = detectorConstruction->GetScoringVolume();		
	}
	
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();

	G4int PDGE  = step->GetTrack()->GetDefinition()->GetPDGEncoding();
	G4double kE = step->GetTrack()-> GetKineticEnergy();
	G4int Pid   = step->GetTrack()->GetParentID();

	if (volume != fScoringVolume) return;
	
	if (Pid != 0) {
		fEventAction->AddPid(PDGE);
		fEventAction->AddKine(PDGE, KE);
	}
	
}

