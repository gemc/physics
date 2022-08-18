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
/// \file PhysicsList.hh
/// \brief Definition of the PhysicsList class
//
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4VModularPhysicsList.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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



