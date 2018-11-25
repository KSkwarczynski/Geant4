//
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp
#include "G4Material.hh" //materiały
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"

DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    CubeLogVol = 0L;
    WLSLogVol = 0L;
    WLSfiberLogVol = 0L;
    materials = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructCube();
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 10.*m;
    G4double worldY = 10.*m;
    G4double worldZ = 10.*m;
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,CLHEP::universe_mean_density,kStateGas, 3.e-18*pascal, 2.73*kelvin);

    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);

    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;
}




void DetectorConstruction::ConstructCube()
{
/////////FANTOM/////////
    G4Material* Plastic = materials->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4double xsize = 1*cm;
    G4double ysize = 1*cm;
    G4double zsize = 1*cm;
    G4Box* CubeSolid = new G4Box("CubeSolid", xsize/2, ysize/2, zsize/2);
    CubeLogVol = new G4LogicalVolume(CubeSolid, Plastic, "CubeLogVol");

    G4VisAttributes* CubeVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	CubeVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	CubeLogVol->SetVisAttributes(CubeVisAtt);

	G4double radiusMin=0*mm;
    G4double radiusMax=0.5*mm;
    G4double length = 1*cm;

    G4LogicalVolume* FiberLog = ConstructWLSfiber(radiusMin, radiusMax, length/2);
    G4LogicalVolume* HoleLog = ConstructWLS(radiusMin, radiusMax, length/2);

    G4ThreeVector FiberPos(0, 0, 0);
    new G4PVPlacement(0, FiberPos, FiberLog, "FIber", HoleLog, 0, 0);

    G4ThreeVector HolePos1(0, 0, 0);
    new G4PVPlacement(0, HolePos1, HoleLog, "Hole", CubeLogVol, 0, 0);

    G4RotationMatrix* RotX = new G4RotationMatrix();
    RotX->rotateX(90*deg);
    G4RotationMatrix* RotY = new G4RotationMatrix();
    RotY->rotateY(90*deg);

    G4ThreeVector HolePos2(1.5*mm, 0, 0);
    new G4PVPlacement(RotX, HolePos2, HoleLog, "Hole", CubeLogVol, 0, 1);

    G4ThreeVector HolePos3(0, -1.5*mm, -1.5*mm);
    new G4PVPlacement(RotY, HolePos3, HoleLog, "Hole", CubeLogVol, 0, 2);

	G4ThreeVector Cubepos(0, 0, 0);
	new G4PVPlacement(0, Cubepos, CubeLogVol, "Cube", worldLogic, 0, 0);
}


G4LogicalVolume* DetectorConstruction::ConstructWLS( G4double radiusMin, G4double radiusMax, G4double length)
{
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,CLHEP::universe_mean_density,kStateGas, 3.e-18*pascal, 2.73*kelvin);

    G4Tubs* WLSSolid = new G4Tubs("WLSSolid", radiusMin, radiusMax+0.25*mm, length, 0*deg, 360*deg);

    WLSLogVol = new G4LogicalVolume(WLSSolid, vaccum, "WLSLogVol");

    G4VisAttributes* WLSVisAtt = new G4VisAttributes( G4Colour::White() );
	WLSVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	WLSLogVol->SetVisAttributes(WLSVisAtt);

    return WLSLogVol;
}

G4LogicalVolume* DetectorConstruction::ConstructWLSfiber(G4double radiusMin, G4double radiusMax, G4double length)
{
    G4Tubs* WLSfiberSolid = new G4Tubs("WLSfiberSolid", radiusMin, radiusMax, length, 0*deg, 360*deg);

    G4Element* C = materials->FindOrBuildElement("C");
    G4Element* H = materials->FindOrBuildElement("H");
    G4Material* WLSmat = new G4Material("WLSmat", 1.0591*g/cm3, 46); //1,4-Bis(2-methylstyryl)benzol
    WLSmat->AddElement(C, 24);
    WLSmat->AddElement(H, 22);

	WLSfiberLogVol = new G4LogicalVolume(WLSfiberSolid, WLSmat, "WLSfiberLogVol");

	G4VisAttributes* WLSfiberVisAtt = new G4VisAttributes( G4Colour::Green() );
	WLSfiberVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	WLSfiberVisAtt->SetForceSolid(true);
	WLSfiberLogVol->SetVisAttributes(WLSfiberVisAtt);
    return WLSfiberLogVol;
}

void DetectorConstruction::ConstructSDandField()
{
//pozniej beda tu detektory
}

