#ifndef EventAction_h
#define EventAction_h 1

// c++
#include <vector>
#include <map>

// geant4
#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction();
	virtual ~EventAction();
	
	virtual void  BeginOfEventAction(const G4Event* event);
	virtual void    EndOfEventAction(const G4Event* event);
	
	void AddPid(int pid);
	void AddKine(int pid, double kine);

private:
	std::vector<int> pids;
	
};

#endif


