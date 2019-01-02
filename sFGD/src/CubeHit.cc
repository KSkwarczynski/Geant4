#include "CubeHit.hh"

G4ThreadLocal G4Allocator<CubeHit>* CubeHitAllocator=0;

CubeHit::CubeHit(G4double enDepVal, G4int CubeNumberValue)
{
    enDep = enDepVal;
    CubeNumber = CubeNumberValue;
    
}
CubeHit::~CubeHit() {}

CubeHit::CubeHit(const CubeHit &right) : G4VHit()
{
    enDep = right.enDep;
    CubeNumber = right.CubeNumber;
}

//operator przypisania
const CubeHit& CubeHit::operator=(const CubeHit &right)
{
    enDep = right.enDep;
    CubeNumber = right.CubeNumber;
    return *this;
}

//operator porownania
G4int CubeHit::operator==(const CubeHit &right) const
{
    return (this==&right) ? 1 : 0;
}



