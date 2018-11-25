//
//
//
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "G4UserSteppingAction.hh"

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*); 
  private:
     void PrintStep(const G4Step*);
};

#endif
