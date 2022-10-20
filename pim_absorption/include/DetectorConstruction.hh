#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

// geant4
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace pim_absorbtion {

	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction();
		virtual ~DetectorConstruction();

		virtual G4VPhysicalVolume* Construct();

		G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

	protected:
		G4LogicalVolume*  fScoringVolume;
	};

}

#endif

