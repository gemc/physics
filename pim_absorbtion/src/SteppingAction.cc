#include <fstream>
#include <iomanip>
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleTypes.hh"

//#include "g4root.hh"

SteppingAction::SteppingAction(
										 const DetectorConstruction* detectorConstruction,
										 EventAction* eventAction)
: G4UserSteppingAction(),
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

	G4int PDGE = step->GetTrack()->GetDefinition()->GetPDGEncoding();
	G4double kE = step-> GetTrack() -> GetKineticEnergy();
	G4int Pid =  step->GetTrack()->GetParentID();
	
	
	if (volume != fScoringVolume) return;
	if (Pid != 0) {
		auto analysisManager = G4AnalysisManager::Instance();
		analysisManager->FillNtupleDColumn(0, PDGE);
		analysisManager->FillNtupleDColumn(1, kE);
		
		analysisManager->AddNtupleRow();
	}
	
}

