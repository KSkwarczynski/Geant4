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
    KostkaSD = 0L;
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

    G4double worldX = 8*m;
    G4double worldY = 8*m;
    G4double worldZ = 8*m;

    G4Material* Air = materials->FindOrBuildMaterial("G4_AIR");


    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, Air,"worldLogic", 0,0,0);

    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;
}




void DetectorConstruction::ConstructCube()
{
    //Polystyrene doped with 1.5% paraterphenyl (PTP) 0.01% POPOP
    G4Element* H = materials->FindOrBuildElement("H");
    G4Element* C = materials->FindOrBuildElement("C");
    
    G4Material* PTerphenyl = new G4Material("PTerphenyl", 1.23*g/cm3, 2);
    PTerphenyl->AddElement(H, 14);
    PTerphenyl->AddElement(C, 18);

    G4Material* Polystyrene = materials->FindOrBuildMaterial("G4_POLYSTYRENE"); 

    G4Material* CubeMaterial=new G4Material("CubeMaterial", 1.06255*g/cm3, 2);
    CubeMaterial->AddMaterial(PTerphenyl,  98.5*perCent);
    CubeMaterial->AddMaterial(Polystyrene, 1.5*perCent);
    
    G4double xsize = 1*cm;
    G4double ysize = 1*cm;
    G4double zsize = 1*cm;
    
    G4Box* CubeSolid = new G4Box("CubeSolid", xsize/2, ysize/2, zsize/2);
    CubeLogVol = new G4LogicalVolume(CubeSolid, CubeMaterial, "CubeLogVol");
    
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
    int optymalization=4; //default equals 1, decrease nr. of cubes for optymalization
    int nrOfDetsZ=48;
    int nrOfDetsX=24/optymalization;
    int nrOfDetsY=8/optymalization;    // 9216 cubes: 48 x 24 x 8 (depth, width, height).

    for(int y = 0; y< nrOfDetsY; ++y)
    {
        for(int x = 0; x< nrOfDetsX; ++x)
        {
            for(int z = 0; z< nrOfDetsZ; ++z)
            {
                G4ThreeVector Cubepos( (x*1-12/(optymalization) )*cm, (y*1-4/(optymalization) )*cm, -z*1*cm );
                new G4PVPlacement(0, Cubepos, CubeLogVol, "Cube", worldLogic, 0, 100000+1 00 00*y+100*x+z);
            }
        }
    }
}


G4LogicalVolume* DetectorConstruction::ConstructWLS( G4double radiusMin, G4double radiusMax, G4double length)
{

    G4Material* Air = materials->FindOrBuildMaterial("G4_AIR");

    G4Tubs* WLSSolid = new G4Tubs("WLSSolid", radiusMin, radiusMax+0.25*mm, length, 0*deg, 360*deg);

    WLSLogVol = new G4LogicalVolume(WLSSolid, Air, "WLSLogVol");

    G4VisAttributes* WLSVisAtt = new G4VisAttributes( G4Colour::White() );
	WLSVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	WLSLogVol->SetVisAttributes(WLSVisAtt);

    return WLSLogVol;
}

G4LogicalVolume* DetectorConstruction::ConstructWLSfiber(G4double radiusMin, G4double radiusMax, G4double length)
{
    G4Tubs* WLSfiberSolid = new G4Tubs("WLSfiberSolid", radiusMin, radiusMax, length, 0*deg, 360*deg);

    G4Material* Polystyrene = materials->FindOrBuildMaterial("G4_POLYSTYRENE"); //Polystyrene y-11 Kuraray

	WLSfiberLogVol = new G4LogicalVolume(WLSfiberSolid, Polystyrene, "WLSfiberLogVol");

	G4VisAttributes* WLSfiberVisAtt = new G4VisAttributes( G4Colour::Green() );
	WLSfiberVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	WLSfiberVisAtt->SetForceSolid(true);
	WLSfiberLogVol->SetVisAttributes(WLSfiberVisAtt);
    return WLSfiberLogVol;
}

void DetectorConstruction::ConstructSDandField()
{
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();

    
    if (!KostkaSD)
    {
        KostkaSD = new CubeSD("KostkaSD");//konstruktor
    }

    SDmanager->AddNewDetector(KostkaSD);//rejestracja w G4SDManager
    CubeLogVol->SetSensitiveDetector(KostkaSD); //przypisanie do log vol
    
}

