//
//
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
        void SetUpDefault();
        G4ThreeVector GenerateIsotropicDirection( G4double thetaMin = 0, G4double thetaMax = M_PI, G4double phiMin=0, G4double phiMax=2.*M_PI );
        void GeneratePositronIncident(G4Event* anEvent);
        G4ParticleGun* particleGun;

};


#endif 

