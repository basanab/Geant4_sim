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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),
      fScoringVolume(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step *step)
{
  // if (!fScoringVolume) {
  // const B1DetectorConstruction* detectorConstruction
  //   = static_cast<const B1DetectorConstruction*>
  //     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //   fScoringVolume = detectorConstruction->GetScoringVolume();
  // }

  // // get volume of the current step
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // G4cout<<"volume name: "<<volume->GetName()<<G4endl;
  // if (step->GetPreStepPoint() != NULL)
  // {
  //   if (step->GetPreStepPoint()->GetProcessDefinedStep() != NULL)
  //   {
  //     G4cout << "ProcName: " << step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
  //   }
  // }

  if (volume->GetName() == "Detector")
  {
    // G4cout << "The particle ID is " << step->GetTrack()->GetDefinition()->GetPDGEncoding() << G4endl;
    if (step->GetTrack()->GetDefinition()->GetPDGEncoding() == 13)
      SetMuPosition(step->GetTrack()->GetPosition(),step->GetTrack()->GetKineticEnergy(),step->GetTrack()->GetMomentum());//.x(),step->GetTrack()->GetMomentum().y());

      // SetMuPosition(step->GetTrack()->GetPosition(),step->GetTrack()->GetKineticEnergy(),step->GetTrack()->GetMomentumDirection());//.x(),step->GetTrack()->GetMomentum().y());
    else if (step->GetTrack()->GetDefinition()->GetPDGEncoding() == 11)
      SetEPosition(step->GetTrack()->GetPosition(),step->GetTrack()->GetKineticEnergy(),step->GetTrack()->GetMomentum());//.x(),step->GetTrack()->GetMomentum().y());

      // SetEPosition(step->GetTrack()->GetPosition(),step->GetTrack()->GetKineticEnergy(),step->GetTrack()->GetMomentumDirection());//.x(),step->GetTrack()->GetMomentum().y());
    if(step->GetTrack()->GetDefinition()->GetPDGEncoding() != 13 && step->GetTrack()->GetDefinition()->GetPDGEncoding() != 11)
      SetScatteringType(step->GetTrack()->GetDefinition()->GetPDGEncoding());
  }
  // // check if we are in scoring volume
  // if (volume != fScoringVolume) return;

  // // collect energy deposited in this step
  // G4double edepStep = step->GetTotalEnergyDeposit();
  // fEventAction->AddEdep(edepStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
