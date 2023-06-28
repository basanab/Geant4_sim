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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 1*cm, env_sizeZ = 0.5*cm;
  // G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
   
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR"); 
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  
  G4double world_sizeXY = 1.5*env_sizeXY;
  G4double world_sizeZ  = 1.5*env_sizeZ;
  // Get nist material manager (added line below for g4_galactic)
  G4NistManager* manager = G4NistManager::Instance();
  // G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* world_mat = manager->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
      //  0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
        0.5*world_sizeXY, 0.5*world_sizeXY, 0.6*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  
  G4Material* al_mat = nist->FindOrBuildMaterial("G4_Al");
  
  G4Box* solidAluminium =    
    new G4Box("Al_plate",                       //its name
       0.5*env_sizeXY, 0.5*env_sizeXY, 0.15*cm);     //its size
      
  G4LogicalVolume* logicAluminium =                         
    new G4LogicalVolume(solidAluminium,          //its solid
                        al_mat,           //its material
                        "Aluminium Plate");            //its name
                                   
  G4VPhysicalVolume* physAluminium = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicAluminium,            //its logical volume
                      "Al_Plate",               //its name
                      logicWorld,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  // G4Material* Beryllium_mat = nist->FindOrBuildMaterial("G4_Be");
  
  // G4Box* solidBeryllium =    
  //   new G4Box("Beryllium_plate",                       //its name
  //      0.5*env_sizeXY, 0.5*env_sizeXY, 0.0005);     //its size unit in cm
      
  // G4LogicalVolume* logicBeryllium =                         
  //   new G4LogicalVolume(solidBeryllium,          //its solid
  //                       // al_mat,           //its material
  //                       Beryllium_mat,       //its material
  //                       "Beryllium_Plate");            //its name
                                   
  // G4VPhysicalVolume* physBeryllium = 
  //   new G4PVPlacement(0,                     //no rotation
  //                     G4ThreeVector(),       //at (0,0,0)
  //                     logicBeryllium,            //its logical volume
  //                     "BerylliumPlate",               //its name
  //                     logicWorld,                     //its mother  volume
  //                     false,                 //no boolean operation
  //                     0,                     //copy number
  //                     checkOverlaps);        //overlaps checking                        
 
  // G4Material* air_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* glass_mat = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

  G4Box* solidAir =    
    new G4Box("Detector",                       //its name
       0.5*env_sizeXY, 0.5*env_sizeXY, 0.00005*env_sizeZ);     //its size
      
  G4LogicalVolume* logicAir =                         
    new G4LogicalVolume(solidAir,          //its solid
                        // air_mat,           //its material
                         glass_mat,           //its material
                        "Detector");            //its name
                                   
  G4VPhysicalVolume* physAir = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,(-world_sizeZ/2.3) - 0.1 ),       //at (0,0,-0.326cm)
                      logicAir,            //its logical volume
                      "Detector",               //its name
                      logicWorld,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking   
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
