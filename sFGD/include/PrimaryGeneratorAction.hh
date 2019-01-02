//
//
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "TRandom3.h"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
        void SetUpDefault();
        G4ParticleGun* particleGun;
        G4ParticleTable* particleTable;
        TRandom3 * losowa;
        void GenerateProtonIncident(G4Event* anEvent);
        G4ThreeVector GenerateDirection();
        G4ThreeVector GenerateStartingPosition();

};


#endif

