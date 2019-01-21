// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//feve
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "CubeHit.hh"

EventAction::EventAction()
{
    PlikZapisu = new OutputFile("StoppingProton.root");
}

EventAction::~EventAction()
{

     delete PlikZapisu;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    //zacznę od znaleziania unikalnego ID naszej kolekcji 
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int CubePolystyreneId = SDmanager->GetCollectionID("CubeHitKolekcja");
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    G4int eventID = anEvent->GetEventID();
    if(!hitsCollOfThisEvent)
        return;
    
    //wyciagamy kolekcje kregoslupowa
    CubeHitsCollection* CubeHitColl = (CubeHitsCollection*)( hitsCollOfThisEvent->GetHC(CubePolystyreneId) );
    
    int Size = CubeHitColl->entries();
    G4double energyDepInEvent = 0;
    G4int CubeNumber = 0;
    for(G4int i=0; i!=Size; i++)
    {
         G4double energyDep = (*CubeHitColl)[i]->GetEnDep();
         energyDepInEvent +=energyDep;
         
         CubeNumber = (*CubeHitColl)[i]->GetCubeNumber();
         //CubeNumber = (*CubeHitColl)[i]->GetIndex();
         
         
         PlikZapisu->AddEntryStep(energyDep,CubeNumber);
    }
    
    PlikZapisu->AddEntry(energyDepInEvent, CubeNumber, Size);
    
    if( eventID % 10 == 0 )
    {
        G4cout << "Finished Running Event # " << eventID << G4endl;
    }

}
