
// $Id: PET.cc 15.10.2018 A Fijalkowska $
//
/// \brief Main program of the simple PET project
//

#include "G4String.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"


#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"



int main(int argc, char** argv)
{

  G4RunManager * runManager = new G4RunManager;
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserAction(new PrimaryGeneratorAction());
  runManager->SetUserAction(new RunAction());
  runManager->SetUserAction(new EventAction());
  runManager->SetUserAction(new SteppingAction());
  runManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  //wizualizacja
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();


  //ui - terminal do wpisywania komend
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  UImanager->ApplyCommand("/vis/open OGL 600x600-0+0");
  UImanager->ApplyCommand("/vis/drawVolume");
  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
  UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
  UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
  UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");
  UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2");
  UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 2.0 m");

  ui->SessionStart();
  delete runManager;
  return 0;
}


