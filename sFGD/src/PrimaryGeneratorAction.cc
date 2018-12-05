
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
    particleGun->SetParticlePosition(G4ThreeVector(0*cm,0*cm,1*m));
    particleGun->SetParticleMomentumDirection( G4ThreeVector( 0, 0, 1 ) );
    particleGun->SetParticleEnergy(2.0*MeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}


