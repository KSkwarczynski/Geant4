#include "CubeHit.hh"

G4ThreadLocal G4Allocator<CubeHit>* CubeHitAllocator=0;

CubeHit::CubeHit()
{

}
CubeHit::~CubeHit() {}

CubeHit::CubeHit(const CubeHit &right) : G4VHit()
{

}

//operator przypisania
const CubeHit& CubeHit::operator=(const CubeHit &right)
{

    return *this;
}

//operator porownania
G4int CubeHit::operator==(const CubeHit &right) const
{
    return (this==&right) ? 1 : 0;
}



