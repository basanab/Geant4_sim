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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "B1SteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4RootAnalysisManager.hh"
#include "G4CsvAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction *runAction)
    : G4UserEventAction(),
      fRunAction(runAction),
      fEdep(0.)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event *)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event *)
{
  // accumulate statistics in run action
  // fRunAction->AddEdep(fEdep);
  B1SteppingAction *steppingAction = (B1SteppingAction *)(G4RunManager::GetRunManager()->GetUserSteppingAction());
  if (steppingAction->is_muon_e_event())
  {
    //G4cout<<"mu_e event"<<G4endl;
    G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();
    // G4CsvAnalysisManager *man = G4CsvAnalysisManager::Instance();

    // Get event id from Geant4 step 

    man->FillNtupleDColumn(0,G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
    man->FillNtupleDColumn(1, steppingAction->GetMuPosition().x());
    man->FillNtupleDColumn(2, steppingAction->GetMuPosition().y());
    man->FillNtupleDColumn(3, steppingAction->GetMuPosition().z());

    man->FillNtupleDColumn(4, steppingAction->GetEPosition().x());
    man->FillNtupleDColumn(5, steppingAction->GetEPosition().y());
    man->FillNtupleDColumn(6, steppingAction->GetEPosition().z());
    
    man->FillNtupleDColumn(7, steppingAction->GetMuEnergy());
    man->FillNtupleDColumn(8, steppingAction->GetEEnergy());

    man->FillNtupleDColumn(9, steppingAction->GetMuMomentum().x());
    man->FillNtupleDColumn(10, steppingAction->GetMuMomentum().y());
    man->FillNtupleDColumn(11, steppingAction->GetMuMomentum().z());

    man->FillNtupleDColumn(12, steppingAction->GetEMomentum().x());
    man->FillNtupleDColumn(13, steppingAction->GetEMomentum().y());
    man->FillNtupleDColumn(14, steppingAction->GetEMomentum().z());

  //   man->FillNtupleDColumn(10, step->GetTrack()->GetMuMomentum().y());
  // // man->FillNtupleDColumn("Pz");
  //   man->FillNtupleDColumn(11, step->GetTrack()->GetEMomentum().x());
  //   man->FillNtupleDColumn(12, step->GetTrack()->GetEMomentum().y());
    man->FillNtupleDColumn(15, steppingAction->GetScatteringType());
    
    // man->FillNtupleDColumn(0,0);
    // man->FillNtupleDColumn(1, 1);
    // man->FillNtupleDColumn(2, 2);
    // man->FillNtupleDColumn(3, 3);

    // man->FillNtupleDColumn(4, 1);
    // man->FillNtupleDColumn(5, 2);
    // man->FillNtupleDColumn(6, 3);
    man->AddNtupleRow();
  }

  steppingAction->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
