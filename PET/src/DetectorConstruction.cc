//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
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
}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructRing();
    ConstructHumanFantom();
    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 5.*m;
    G4double worldY = 5.*m;
    G4double worldZ = 5.*m;
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density,
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);

    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);

    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

void DetectorConstruction::ConstructRing(){
/////////TORUS///////////
    G4NistManager* man = G4NistManager::Instance();

    G4Material* Polypropylene = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
    G4double TorusradiusMin = 80*cm;
    G4double TorusradiusMax = 100*cm;
    G4double Toruslength = 100*cm;
    G4Tubs* TorusSolid = new G4Tubs("TorusSolid", TorusradiusMin, TorusradiusMax, Toruslength/2., 0*deg, 360*deg);

    G4LogicalVolume* TorusLogVol = new G4LogicalVolume(TorusSolid, Polypropylene, "TorusLogVol");

    G4VisAttributes* TorusVisAtt = new G4VisAttributes( G4Colour::Cyan());
        TorusVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
        TorusLogVol->SetVisAttributes(TorusVisAtt);

        G4ThreeVector Toruspos(0,0,0);
        new G4PVPlacement(0, Toruspos, TorusLogVol, "Torus", worldLogic, 0, 0);

////////////Detector//////////////

    G4Material* Teflon = man->FindOrBuildMaterial("G4_TEFLON");

    G4double pX = 9*cm;
    G4double pY = 9*cm;
    G4double pZ = 31*cm;
    G4Box* DetectorSolid = new G4Box("DetectorSolid", pX, pY, pZ);

    G4LogicalVolume* DetectorLogVol = new G4LogicalVolume(DetectorSolid, Teflon, "DetectorLogVol");

    G4VisAttributes* DetectorVisAtt = new G4VisAttributes( G4Colour::Red() );
        DetectorVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
        DetectorLogVol->SetVisAttributes(DetectorVisAtt);

/////////////////////SubDetector//////////////////////////////
        G4Material* SodiumIodide = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");

        G4double subpX = 8*cm;
        G4double subpY = 8*cm;
        G4double subpZ = 30*cm;
        G4Box* subDetectorSolid = new G4Box("subDetectorSolid", subpX, subpY, subpZ);

        subDetectorLogVol = new G4LogicalVolume(subDetectorSolid, SodiumIodide, "subDetectorLogVol");

        G4VisAttributes* subDetectorVisAtt = new G4VisAttributes( G4Colour::Grey() );
            subDetectorVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
            subDetectorVisAtt->SetForceSolid(true);
            subDetectorLogVol->SetVisAttributes(subDetectorVisAtt);

//////////////LOOP PLACEMENT///////////

for(int i=0;i<18;i++){
    double angle=20;

    G4RotationMatrix* zRot=new G4RotationMatrix();
    zRot->rotateZ(-angle*i*deg);

    G4ThreeVector Detectorpos(90*cos(i*angle*deg)*cm , 90*sin(i*angle*deg)*cm,0);
    G4ThreeVector subDetectorpos(0,0,0);
    new G4PVPlacement(zRot, Detectorpos, DetectorLogVol, "Detector", TorusLogVol, 0, i);


    new G4PVPlacement(0, subDetectorpos, subDetectorLogVol, "subDetector", DetectorLogVol, 0, i);
    }

}


void DetectorConstruction::ConstructHumanFantom()
{
    G4NistManager* man = G4NistManager::Instance();
/////////FANTOM/////////
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);

    G4double radiusMin = 0;
    G4double radiusMax = 60*cm;
    G4double length = 170*cm;
    G4Tubs* fantomSolid = new G4Tubs("fantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4LogicalVolume* fantomLogVol = new G4LogicalVolume(fantomSolid, water, "fantomLogVol");


    G4VisAttributes* fantomVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	fantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	fantomLogVol->SetVisAttributes(fantomVisAtt);

	G4ThreeVector pos(0,0,0);
	new G4PVPlacement(0, pos, fantomLogVol, "fantom", worldLogic, 0, 0);

///////////////SPINE///////
    G4Material* Titanium = man->FindOrBuildMaterial("G4_TITANIUM_DIOXIDE");

    G4double SpineradiusMin = 0*cm;
    G4double SpineradiusMax = 10*cm;
    G4double Spinelength = 100*cm;
    G4Tubs* SpineSolid = new G4Tubs("SpineSolid", SpineradiusMin, SpineradiusMax, Spinelength/2., 0*deg, 360*deg);
    G4LogicalVolume* SpineLogVol = new G4LogicalVolume(SpineSolid, Titanium, "SpineLogVol");


    G4VisAttributes* SpineVisAtt = new G4VisAttributes( G4Colour::White());
        SpineVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
        SpineVisAtt->SetForceSolid(true);
        SpineLogVol->SetVisAttributes(SpineVisAtt);


        G4ThreeVector Spinepos(0, 10*cm ,0);
        new G4PVPlacement(0, Spinepos, SpineLogVol, "Spine", fantomLogVol, 0, 0);
}

void DetectorConstruction::ConstructSDandField()
{
    //ustalanie mierzących elementów detektora
    G4MultiFunctionalDetector* detector=new G4MultiFunctionalDetector("naISensitiveDet");
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);
    subDetectorLogVol->SetSensitiveDetector(detector);
    G4int depth = 1;
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep", depth);
    detector->RegisterPrimitive(energyDepScorer);
}

