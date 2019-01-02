//
/// \file DetectorConstruction.hh
/// \brief Class holding detector geometry
//
//
#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "CubeSD.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    G4NistManager* materials;

    void ConstructCube();
        
    G4LogicalVolume* worldLogic; //świat
    G4LogicalVolume* CubeLogVol; //Cube
    G4LogicalVolume* WLSLogVol; //Dziura na WLS
    G4LogicalVolume* WLSfiberLogVol; //WLSfiber

    G4VPhysicalVolume* ConstructWorld(); //metoda w której świat zostanie zbudowany

    G4LogicalVolume* ConstructWLS( G4double radiusMin, G4double radiusMax, G4double length );
    G4LogicalVolume* ConstructWLSfiber( G4double radiusMin, G4double radiusMax, G4double length);
    
    CubeSD* KostkaSD;


};

#endif
