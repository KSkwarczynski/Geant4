
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
    particleGun->SetParticlePosition(G4ThreeVector(0*cm,0*cm, 100*cm));
    particleGun->SetParticleMomentumDirection( GenerateDirection() );
    particleGun->SetParticleEnergy(2.0*GeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector PrimaryGeneratorAction::GenerateDirection()
{
    //Metoda ktora urozmaica troche kierunek wiazki
    //Wartosci nie sa koncowe tylko wstepne
    G4double DirectionX=0;
    G4double DirectionY=0;
    G4double DirectionZ=0;
    G4double SignX=0;
    G4double SignY=0;
    G4double Randomization=0;
    
    DirectionX= G4UniformRand()/30;
    DirectionY= G4UniformRand()/30;
    
    Randomization=G4UniformRand();
    if(Randomization>0.5)
    {
        SignX = 1;
    }
    else
    {
        SignX = -1;
    } 
    
    Randomization=G4UniformRand();
    if(Randomization>0.5)
    {
        SignY = 1;
    }
    else
    {
        SignY = -1;
    } 
    
    DirectionZ=1-DirectionY-DirectionX;
    
    return G4ThreeVector(SignX*DirectionX, SignY*DirectionY, -DirectionZ);
}







