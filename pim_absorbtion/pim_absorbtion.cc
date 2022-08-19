#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

// geant4 physics
#include "G4PhysListFactory.hh"
#include "QGSP_BERT_HP.hh"

// geant4
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4ChargeExchangePhysics.hh"

namespace {

void PrintUsage() {
	G4cerr << " Usage: " << G4endl;
	G4cerr << " pim_absorbtion [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
	G4cerr << "   note: -t option is available only for multi-threaded mode." << G4endl;
}
}


int main(int argc,char** argv)
{
	// Evaluate arguments
	if ( argc > 7 ) {
		PrintUsage();
		return 1;
	}
	
	G4String macro;
	G4String session;
	G4int nThreads = 4;
	for ( G4int i=1; i<argc; i=i+2 ) {
		if      ( G4String(argv[i]) == "-m" ) macro   = argv[i+1];
		else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
		else if ( G4String(argv[i]) == "-t" ) {
			nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
		} else {
			PrintUsage();
			return 1;
		}
	}
	
	// Detect interactive mode (if no macro provided) and define UI session
	G4UIExecutive* ui = nullptr;
	if ( ! macro.size() ) {
		ui = new G4UIExecutive(argc, argv, session);
	}
	
	// Choose the Random engine
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	
	// Construct the default run manager
	auto runManager = new G4MTRunManager;
	if ( nThreads > 0 ) {
		runManager->SetNumberOfThreads(nThreads);
	}
	
	// Set mandatory initialization classes
	auto detConstruction = new DetectorConstruction();
	runManager->SetUserInitialization(detConstruction);
	
	auto physicsList = new QGSP_BERT_HP;
	runManager->SetUserInitialization( physicsList);
	
	auto actionInitialization = new ActionInitialization(detConstruction);
	runManager->SetUserInitialization(actionInitialization);
	
	// Initialize visualization
	auto visManager = new G4VisExecutive;
	visManager->Initialize();
	
	// Get the pointer to the User Interface manager
	auto UImanager = G4UImanager::GetUIpointer();
	
	// Process macro or start UI session
	if ( macro.size() ) {
		// batch mode
		G4String command = "/control/execute ";
		UImanager->ApplyCommand(command+macro);
	} else  {
		// interactive mode : define UI session
		// assuming the existance of init_vis and gui
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	delete visManager;
	delete runManager;
}

