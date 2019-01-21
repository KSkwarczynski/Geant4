#ifndef CubeSD_H
#define CubeSD_H 1

#include "G4VSensitiveDetector.hh"
#include "CubeHit.hh"
class CubeSD : public G4VSensitiveDetector
{
public:
    CubeSD(G4String name);
    virtual ~CubeSD();
    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
private:
    G4double GetEnDep(G4Step* aStep);
    G4int GetCubeNumber(G4Step* aStep);
    //G4int GetIndex(G4Step* aStep, int depth);
    G4int GetIndex(G4Step* aStep);
    CubeHitsCollection* CubeHitKolekcja;
};

#endif
