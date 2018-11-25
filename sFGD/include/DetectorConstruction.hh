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

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction(); //konstuktor
    virtual ~DetectorConstruction(); //destruktor
    virtual G4VPhysicalVolume* Construct(); //tu będzie wszystko budowane
    virtual void ConstructSDandField(); //tu póżniej zdefiniujemy czułe elementy detektora

  private:
    G4NistManager* materials;

    G4LogicalVolume* worldLogic; //świat
    G4LogicalVolume* CubeLogVol; //Cube
    G4LogicalVolume* WLSLogVol; //Dziura na WLS
    G4LogicalVolume* WLSfiberLogVol; //WLSfiber

    G4VPhysicalVolume* ConstructWorld(); //metoda w której świat zostanie zbudowany
    void ConstructCube();
    G4LogicalVolume* ConstructWLS( G4double radiusMin, G4double radiusMax, G4double length );
    G4LogicalVolume* ConstructWLSfiber( G4double radiusMin, G4double radiusMax, G4double length);


};

#endif
