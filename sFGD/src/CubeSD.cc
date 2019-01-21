#include "CubeSD.hh"
#include "G4SDManager.hh"

CubeSD::CubeSD(G4String name): G4VSensitiveDetector(name)
{
    collectionName.insert("CubeHitKolekcja");
}

CubeSD::~CubeSD() {}

void CubeSD::Initialize(G4HCofThisEvent* hitsCE)
{
    CubeHitKolekcja = new CubeHitsCollection(SensitiveDetectorName, collectionName[0]);
    
    static G4int hitCID = -1;
    if (hitCID<0) 
    {
         hitCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    hitsCE->AddHitsCollection( hitCID, CubeHitKolekcja);
}

G4bool CubeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    G4double enDep = GetEnDep(aStep);
    G4double CubeNumber = GetCubeNumber(aStep);
    CubeHit* aHit = new CubeHit(enDep, CubeNumber);
    CubeHitKolekcja->insert( aHit );
    return true;
}

G4double CubeSD::GetEnDep(G4Step* aStep)
{
    G4double eDep = aStep->GetTotalEnergyDeposit();
    return eDep;
}

G4int CubeSD::GetCubeNumber(G4Step* aStep)
{
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint(); 
    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4int copyNo=0;
    return copyNo = theTouchable->GetVolume()->GetCopyNo();
}

//G4int CubeSD::GetIndex(G4Step* aStep, int depth)
//G4int CubeSD::GetIndex(G4Step* aStep)
//{
  //  G4int copyNr = aStep -> GetPostStepPoint()->GetTouchable()->GetReplicaNumber(2);
    //return copyNr;
//}
