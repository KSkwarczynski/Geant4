
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <cmath>
#include <math.h>

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
    losowa = new TRandom3(0);
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}


void PrimaryGeneratorAction::SetUpDefault()
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
    //particleGun->GeneratePrimaryVertex(anEvent);

    GenerateProtonIncident(anEvent);
}


void PrimaryGeneratorAction::GenerateProtonIncident(G4Event* anEvent){

	G4ParticleDefinition* particle = particleTable->FindParticle("proton");
	particleGun->SetParticleDefinition(particle);

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticlePosition( GenerateStartingPosition() );
    particleGun->SetParticleMomentumDirection( GenerateDirection() );
    particleGun->SetParticleEnergy(100*MeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}



G4ThreeVector PrimaryGeneratorAction::GenerateDirection()
{
    G4double randomPhi = G4UniformRand()*2*M_PI;
    G4double randomCosTheta = G4UniformRand()*(-1);
    G4double randomTheta = acos(randomCosTheta);
    G4double x = sin(randomTheta)*sin(randomPhi);
    G4double y = sin(randomTheta)*cos(randomPhi);
    G4double z = cos(randomTheta);
    return G4ThreeVector(x, y, z);
}

G4ThreeVector PrimaryGeneratorAction::GenerateStartingPosition()
{
    G4double x = losowa->Gaus( 0 , 4 );
    G4double y = losowa->Gaus( 0 , 1 );
    G4double z =0;
    
    return G4ThreeVector(x*cm, y*cm, z*cm);    
}
 




