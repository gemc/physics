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

	auto thisTrack = step->GetTrack();
	
	int trkID = thisTrack->GetTrackID();
	int PDGE  = thisTrack->GetDefinition()->GetPDGEncoding();
	double KE = thisTrack->GetKineticEnergy();
	int mpid  = thisTrack->GetParentID();

	if (volume != fScoringVolume) return;


	if (mpid != 0) {

//		if (fabs(PDGE) == 12 || fabs(PDGE) == 14 ) {
//			std::cout << "SSS trackID: " << trkID << ", PDGE: " << PDGE << ", kine: " << KE << std::endl;
//		}

		fEventAction->AddPid(trkID, PDGE);
		fEventAction->AddKine(trkID, KE);
	}
	
}

