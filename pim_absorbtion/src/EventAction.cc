// this test
#include "EventAction.hh"
#include "Analysis.hh"

// geant4
#include "G4RunManager.hh"

// c++
using namespace std;


EventAction::EventAction() : G4UserEventAction(){}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event* event) {
	pids.clear();
}

void EventAction::EndOfEventAction(const G4Event* event)
{
	int evn = event->GetEventID();
	
	// Print per event (modulo n)
	auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
	
	auto analysisManager = G4AnalysisManager::Instance();
	
	for ( auto pid: pids ) {
		analysisManager->FillNtupleDColumn(0, pid);
	}
	
	analysisManager->FillNtupleDColumn(2, evn);
	analysisManager->AddNtupleRow();

}  

void EventAction::AddPid(int pid) {
	if ( find(pids.begin(), pids.end(), pid) == pids.end() ) {
		pids.push_back(pid);
	}
}

