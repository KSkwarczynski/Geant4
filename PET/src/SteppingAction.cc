//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
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

double SteppingAction::spineEnergyDep=0;

void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    ////wyswietl krok tylko jesli mial on miejsce w materiale o nazwie G4_TITANIUM_DIOXIDE
    G4Track* track = theStep->GetTrack();
    G4VPhysicalVolume* physVol = track->GetVolume();
    G4LogicalVolume* logicVolume = physVol -> GetLogicalVolume();
    G4Material* material = logicVolume -> GetMaterial();
    G4String materialName= material->GetName();


    if(materialName=="G4_TITANIUM_DIOXIDE"){
        spineEnergyDep=+theStep->GetTotalEnergyDeposit();
        //std::cout<<spineEnergyDep<<std::endl;
    }
}


void SteppingAction::PrintStep(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();    
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();

    std::cout << " particle: " << particleName
		      << " process: " << processName
		      << " delta en: " << deltaEn
		      << " voulme name: " << volumeName << std::endl;

}


