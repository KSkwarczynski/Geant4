#include "CubeSD.hh"
#include "G4SDManager.hh"

CubeSD::CubeSD(G4String name): G4VSensitiveDetector(name)
{
    collectionName.insert("CubeHitKolekcja");
}

CubeSD::~CubeSD() {}

void CubeSD::Initialize(G4HCofThisEvent* hitsCE)
{
    CubeHitKolekcja = new CubeHitsCollection(SensitiveDetectorName,
                                                 collectionName[0]);
    static G4int hitCID = -1;
    if (hitCID<0) 
    {
         hitCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hitsCE->AddHitsCollection( hitCID, CubeHitKolekcja);
}

G4bool CubeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

}


