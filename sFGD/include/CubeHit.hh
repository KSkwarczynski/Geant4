#ifndef CubeHit_H
#define CubeHit_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class CubeHit : public G4VHit
{
public:
    CubeHit(G4double enDep, G4int CubeNumber);
    virtual ~CubeHit();
    //konstruktor kopiujący
    CubeHit(const CubeHit &right);
    //operator przypisania
    const CubeHit& operator=(const CubeHit &right);
    //operator porównania 
    G4int operator==(const CubeHit &right) const;
   
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    
    G4double GetEnDep(){return enDep;}
    G4int GetCubeNumber(){return CubeNumber;}
private:
    G4double enDep;
    G4int CubeNumber;
    
};


//WAZNE i OBOWIĄZKOWE, zawsze wyglada tak samo
typedef G4THitsCollection<CubeHit> CubeHitsCollection;

extern G4ThreadLocal G4Allocator<CubeHit>* CubeHitAllocator;

inline void* CubeHit::operator new(size_t)
{
    if(!CubeHitAllocator)
        CubeHitAllocator = new G4Allocator<CubeHit>;
    return (void *) CubeHitAllocator->MallocSingle();
}
inline void CubeHit::operator delete(void *aHit)
{
    CubeHitAllocator->FreeSingle((CubeHit*) aHit);
}

#endif
