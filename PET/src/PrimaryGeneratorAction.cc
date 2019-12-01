
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

    GeneratePositronIncident(anEvent);
    GenerateBackroundIncident(anEvent);
}	

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double thetaMin,
                                      G4double thetaMax, G4double phiMin, G4double phiMax){


    if(thetaMin < 0 || thetaMin > 2.*M_PI || thetaMax < 0 || thetaMax > 2.*M_PI){
        std::cout<<  " tangles not in the limits"<< std::endl;
        return G4ThreeVector(0,0,0);
    }

    if(thetaMin >= thetaMax){
        std::cout <<  " theta min has to be smaller than theta max "<< std::endl;
        return G4ThreeVector(0,0,0);
    }

    G4double randomPhi = G4UniformRand()*(phiMax - phiMin) + phiMin;
    G4double cosThetaMin = cos(thetaMin);
    G4double cosThetaMax = cos(thetaMax);
    G4double randomCosTheta = G4UniformRand()*(cosThetaMin-cosThetaMax)+cosThetaMax;
    G4double randomTheta = acos(randomCosTheta);

    G4double x = sin(randomTheta)*cos(randomPhi);
    G4double y = sin(randomTheta)*sin(randomPhi);
    G4double z = randomCosTheta;
    G4ThreeVector randDir = G4ThreeVector( x, y, z );
    return randDir;
    }

void PrimaryGeneratorAction::GeneratePositronIncident(G4Event* anEvent){
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e+");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
    particleGun->SetParticleMomentumDirection( GenerateIsotropicDirection() );
    particleGun->SetParticleEnergy(587.0*keV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::GenerateBackroundIncident(G4Event* anEvent){
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    particleGun->SetParticleDefinition(particle);

    double x = 10*G4UniformRand()-5;
    double y = 10*G4UniformRand()-5;
    double z = 10*G4UniformRand()-5;

    particleGun->SetParticlePosition( G4ThreeVector(x*m , y*m , z*m) );
    particleGun->SetParticleMomentumDirection( GenerateIsotropicDirection() );

    double losowanie=G4UniformRand()*100;
    double losowanie2=0;
    double losowanie3=0;

    double Energia=0;

    if(losowanie>=0 && losowanie<50){ //40K
        Energia=1461;
    }

    if(losowanie>=50 && losowanie<75){ //208Ti


        Energia=2615;
    }

    if(losowanie>=75 && losowanie<100){ //214Pb

        Energia=352;
    }
    particleGun->SetParticleEnergy(Energia*MeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}
