
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

namespace pim_absorption {

    DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

    DetectorConstruction::~DetectorConstruction() {}

    G4VPhysicalVolume *DetectorConstruction::Construct() {
        // Get nist material manager
        G4NistManager *nist = G4NistManager::Instance();

        // Envelope parameters
        G4double env_sizeXY = 500 * cm, env_sizeZ = 500 * cm;
        G4Material *env_mat = nist->FindOrBuildMaterial("G4_Galactic");

        G4Box *solidWorld = new G4Box("World",                       // name
                                      0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);    // size

        G4LogicalVolume *logicWorld =
                new G4LogicalVolume(solidWorld,          // solid
                                    env_mat,             // material
                                    "World");            // name

        G4VPhysicalVolume *physWorld =
                new G4PVPlacement(0,                     // no rotation
                                  G4ThreeVector(),       // at (0,0,0)
                                  logicWorld,            // logical volume
                                  "World",               // name
                                  0,                     // mother  volume
                                  false,                 // no boolean operation
                                  0,                     // copy number
                                  true);                 // overlaps checking


        G4Material *vacuumMaterial = nist->FindOrBuildMaterial("G4_Galactic");
        G4Material *aluminumMaterial = nist->FindOrBuildMaterial("G4_Al");

        G4Tubs *vacuumDetectorSolid = new G4Tubs("vacuumDetectorSolid",   // name
                                                 0 * cm, 60 * cm, 210 * cm, 0 * deg,
                                                 360 * deg);                  // size

        G4LogicalVolume *vacuumDetectorLogical =
                new G4LogicalVolume(vacuumDetectorSolid,           // solid
                                    vacuumMaterial,                // material
                                    "vacuumDetectorLogical");      // name

        vacuumDetectorPV = new G4PVPlacement(0,                       // no rotation
                                             G4ThreeVector(),         // at (0,0,0)
                                             vacuumDetectorLogical,   // logical volume
                                             "vacuumDetector",        // name
                                             logicWorld,              // mother  volume
                                             false,                   // no boolean operation
                                             0,                       // copy number
                                             true);                   // overlaps checking


        G4Tubs *beamDumpSolid =
                new G4Tubs("beamDumpSolid",                                  // name
                           0 * cm, 50 * cm, 200 * cm, 0 * deg, 360 * deg);   // size

        G4LogicalVolume *beamDumpLogical =
                new G4LogicalVolume(beamDumpSolid,        // solid
                                    aluminumMaterial,     // material
                                    "beamDumpLogical");   // name

        new G4PVPlacement(0,                      // no rotation
                          G4ThreeVector(),        // at (0,0,0)
                          beamDumpLogical,        // logical volume
                          "beamDump",             // name
                          vacuumDetectorLogical,  // mother volume
                          false,                  // no boolean operation
                          0,                      // copy number
                          true);                  // overlaps checking


        return physWorld;
    }

}
