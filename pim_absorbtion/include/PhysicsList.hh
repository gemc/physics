
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();
	//explicit ModularPhysicsList();
	//virtual ~ModularPhysicsList();
	
	// This is the one method we're overridding to include the code
	// for the parallel geometry.
	//   virtual void ConstructProcess();
	
	// Non-virtual methods in G4VModularPhysicsList.  Just call the
	// method with the same name in G4VModularPhysicsList.
	void RegisterPhysics(G4VPhysicsConstructor* g)
	{
		G4VModularPhysicsList::RegisterPhysics(g);
	}
	//const G4VPhysicsConstructor* GetPhysics(G4int index) const
	//{
	//  return G4VModularPhysicsList::GetPhysics(index);
	//}
	//const G4VPhysicsConstructor* GetPhysics(const G4String& name) const
	//{
	//  return G4VModularPhysicsList::GetPhysics(name);
	//}
protected:
	// Construct particle and physics
	
	virtual void SetCuts();   
};
//typedef TConfigurablePhysicsList<ModularPhysicsList> PhysicsList;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



