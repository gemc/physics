#include "G4RunManager.hh"
#include "EventAction.hh"


EventAction::EventAction()
: G4UserEventAction(),
fEnergyAbs(0.),
fEnergyGap(0.),
fTrackLAbs(0.),
fTrackLGap(0.)
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/) {  }

void EventAction::EndOfEventAction(const G4Event* event)
{
	// Print per event (modulo n)
	auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
}  

