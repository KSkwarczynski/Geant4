//
//
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include <iostream>

SteppingAction::SteppingAction():G4UserSteppingAction()
{


}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{

}


void SteppingAction::PrintStep(const G4Step* theStep)
{


}


