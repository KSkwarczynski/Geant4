
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
EventAction::EventAction()
{
    outputFile.open("spineEDep.txt");
}
 
EventAction::~EventAction(){
    outputFile.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    ///zaczne od znalezienia unikalnego ID naszej kolekcji
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int collId = SDmanager->GetCollectionID("naISensitiveDet/eDep");

    G4HCofThisEvent* hitsCollOfThisEvent = anEvent->GetHCofThisEvent();


    if(!hitsCollOfThisEvent){
        return;
    }
    G4THitsMap<G4double>* myEnDepMap = static_cast <G4THitsMap<G4double>* > (hitsCollOfThisEvent->GetHC(collId));
    int nrOfDets = 17;

    for(int i=0; i!=nrOfDets; ++i){
        if( (*myEnDepMap)[i] != 0L ){
            G4double depozytEnergii =*((*myEnDepMap)[i]);
            std::cout << "numer kopii: " << i << " enDep " << depozytEnergii <<std::endl;
        }
    }

    ///tu chcemy wyciągnac informacje o całkowitym depozycie energi i wpisac ja do pliku i wyzerowac
    ///std::cout << SteppingAction::spineEnergyDep/kev <<std::endl;

  G4int eventID = anEvent->GetEventID();

  outputFile<<eventID<<" "<<SteppingAction::spineEnergyDep / CLHEP::keV <<std::endl;
  if( eventID % 10 == 0 )
  {
    G4cout << "Finished Running Event # " << eventID << G4endl;
  }
  
}
