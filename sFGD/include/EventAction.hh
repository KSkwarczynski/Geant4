//
/// \file EventAction.hh
/// \brief Definition of the EventAction class
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "OutputFile.hh"
#include <fstream>

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
  private:
      OutputFile* PlikZapisu;


};

#endif
