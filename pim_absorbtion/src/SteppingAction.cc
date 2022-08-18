//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
#include <fstream>
#include <iomanip>
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "B4Analysis.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleTypes.hh"
#include "g4root.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(
		const DetectorConstruction* detectorConstruction,
		EventAction* eventAction)
: G4UserSteppingAction(),
	fDetConstruction(detectorConstruction),
	fEventAction(eventAction),
	fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	if (!fScoringVolume) { 
		const DetectorConstruction* detectorConstruction
			= static_cast<const DetectorConstruction*>
			(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
		fScoringVolume = detectorConstruction->GetScoringVolume();   

		// Collect energy and track length step by step
	}

	G4LogicalVolume* volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
	//if (volume != fScoringVolume) return;
	// auto Particlename = step->GetTrack()->GetDefinition()->GetParticleName();
	   G4int PDGE = step->GetTrack()->GetDefinition()->GetPDGEncoding();
	// G4double M = step->GetTrack()->GetDefinition()->GetPDGMass();
	// G4ThreeVector P = step->GetTrack() -> GetMomentum();
	G4double kE = step-> GetTrack() -> GetKineticEnergy(); 
	G4int Pid =  step->GetTrack()->GetParentID();
	
	// G4ThreeVector point = step->GetTrack()->GetPosition();
	// G4String processName= step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

	//   G4cout << Particlename << ", " << processName << ", " << kE << ", " << point.x() << ", " << point.y() << ", " << point.z() << ", " << G4endl;
	// get volume of the current step
	// auto volume = step->GetPreStepPoint()-> GetPhysicalVolume()->GetLogicalVolume();
	// energy deposit
	// auto edep = step->GetTotalEnergyDeposit();
	//if (volume == fScoringVolume) {  
	// step length
	// G4double stepLength = 0.;
	//if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
	//stepLength = step->GetStepLength();
	//}
	//if ( volume == fDetConstruction->GetScoringVolume() ) {
	//  fEventAction->AddAbs(edep);
	//}

	//if ( volume == fDetConstruction->GetGapPV() ) {
	// fEventAction->AddGap(edep,stepLength);
	// }
	/* 
	   G4String processName=step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
	   if (PDGE == 2112){
	//  G4String processName=step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
	G4double KinE = step->GetPostStepPoint()->GetKineticEnergy();
	G4double TotE = step->GetPostStepPoint()->GetTotalEnergy();
	G4double edep = step->GetTotalEnergyDeposit();
	G4ThreeVector point = step->GetTrack()->GetPosition();

	std::ofstream diag("diag.txt",std::ios::app);

	diag << "P:" << std::setw(4) << step->GetTrack()->GetParentID();
	diag << ", T:" << std::setw(4) << step->GetTrack()->GetTrackID();
	diag << ", S:" << std::setw(4) << step->GetTrack()->GetCurrentStepNumber();
	diag << ", " << std::setw(5) << Particlename;

	diag << ", E: " << std::setw(5) << G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

	diag << ", " << std::setw(5) << processName;


	diag << ", " << std::setw(4) << G4BestUnit(TotE,"Energy");
	diag << ", " << std::setw(4) << G4BestUnit (KinE, "Energy");

	diag << ", " << std::setw(4) << G4BestUnit(edep,"Energy");

	diag <<", X0 " << std::setw(5) << G4BestUnit(step->GetPreStepPoint()->GetPosition().x(),"Length");
	diag <<", Y0 " << std::setw(5) << G4BestUnit(step->GetPreStepPoint()->GetPosition().y(),"Length");
	diag <<", Z0 " << std::setw(5) << G4BestUnit(step->GetPreStepPoint()->GetPosition().z(),"Length");

	diag << ", X " << std::setw(5) << G4BestUnit(step->GetTrack()->GetPosition().x(),"Length");
	diag << ", Y " << std::setw(5) << G4BestUnit(step->GetTrack()->GetPosition().y(),"Length");
	diag << ", Z " << std::setw(5) << G4BestUnit(step->GetTrack()->GetPosition().z(),"Length") << G4endl;
	diag.close();
	}
*/
	if (volume != fScoringVolume) return;
	if (Pid != 0) {
	auto analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleDColumn(0, PDGE);                     
	//  analysisManager->FillNtupleDColumn(2, M);
	analysisManager->FillNtupleDColumn(1, kE);

	analysisManager->AddNtupleRow();  
	}
	//if (volume != fScoringVolume) return;
//	auto analysisManager = G4AnalysisManager::Instance();
/*
	const G4TrackVector* secondary = step->GetSecondary();
	for( size_t lp=0; lp < (*secondary).size(); lp++ )
	{ 
		analysisManager->FillNtupleSColumn(0, step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
		analysisManager->FillNtupleDColumn(1, (G4double)(*secondary)[lp]->GetKineticEnergy()/CLHEP::keV);
		analysisManager->FillNtupleDColumn(2, (G4double)(*secondary)[lp]->GetPosition().getX());
		analysisManager->FillNtupleDColumn(3, (G4double)(*secondary)[lp]->GetPosition().getY());
		analysisManager->FillNtupleDColumn(4, (G4double)(*secondary)[lp]->GetPosition().getZ());
		analysisManager->FillNtupleDColumn(5, (G4double)(*secondary)[lp]->GetMomentum().getX()/CLHEP::keV);
		analysisManager->FillNtupleDColumn(6, (G4double)(*secondary)[lp]->GetMomentum().getY()/CLHEP::keV);
		analysisManager->FillNtupleDColumn(7, (G4double)(*secondary)[lp]->GetMomentum().getZ()/CLHEP::keV);
		analysisManager->FillNtupleDColumn(8, (G4double)(*secondary)[lp]->GetMomentumDirection().getX());
		analysisManager->FillNtupleDColumn(9, (G4double)(*secondary)[lp]->GetMomentumDirection().getY());
		analysisManager->FillNtupleDColumn(10, (G4double)(*secondary)[lp]->GetMomentumDirection().getZ());
		analysisManager->FillNtupleSColumn(11, (*secondary)[lp]->GetDefinition()->GetParticleName() );
		analysisManager->FillNtupleDColumn(12, (*secondary)[lp]->GetDefinition()->GetPDGEncoding() );
		analysisManager->FillNtupleDColumn(13, (volume == fScoringVolume?1:0));
		analysisManager->AddNtupleRow();
	}*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
