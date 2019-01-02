using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <TCanvas.h>
#include "TH1.h"

void RootFileReconstruction(){
    TFile* f1= TFile::Open("StoppingProton.root");
    TTree* ProtonTree;
    f1->GetObject("ProtonTree", ProtonTree);
    
    double enDep;
    int CubeNumber;
    
    ProtonTree->SetBranchAddress("enDep", &enDep);
    ProtonTree->SetBranchAddress("CubeNumber", &CubeNumber);
    
    TFile *plik = new TFile("StoppingProtonReconstructed.root","RECREATE");
    
    TH1F *h_EnergyDeposit = new TH1F("EnergyDepositHist", "Energy Depostied by a stopping proton", 150, 0, 150);
    
    TH1F *h_StoppinPositionX = new TH1F("StoppinPositionX", "Stoppin Position X", 24, 0, 24);
    TH1F *h_StoppinPositionY = new TH1F("StoppinPositionY", "Stoppin Position Y", 8, 0, 8);
    TH1F *h_StoppinPositionZ = new TH1F("StoppinPositionZ", "Stoppin Position Z", 48, 0, 48);
    
    int Eventy = ProtonTree->GetEntries();
    

    for(int i=0; i<Eventy ; i++)
    {
        int NumerPomocniczy=0;
        
        int CubeNumberX[3]={}; // [0-wlasciwa liczba, 1-cyfra dziesietna ,2- cyfra jednosci]
        int CubeNumberY[3]={};
        int CubeNumberZ[3]={};

        ProtonTree->GetEntry(i);
        
        h_EnergyDeposit->Fill(enDep);
        
        NumerPomocniczy = CubeNumber;
        std::string Numer_String;
        std::stringstream kontener;
        kontener << NumerPomocniczy;
        Numer_String = kontener.str();

        CubeNumberZ[1]=Numer_String[5]-'0';
        CubeNumberZ[2]=Numer_String[4]-'0';
        CubeNumberZ[0]=10*CubeNumberZ[1]+CubeNumberZ[2];
        
        CubeNumberX[1]=Numer_String[3]-'0';
        CubeNumberX[2]=Numer_String[2]-'0';
        CubeNumberX[0]=10*CubeNumberZ[1]+CubeNumberZ[2];
        
        CubeNumberY[0]=Numer_String[1]-'0';
        
        h_StoppinPositionZ->Fill(CubeNumberZ[0]);
        h_StoppinPositionX->Fill(CubeNumberX[0]);
        h_StoppinPositionY->Fill(CubeNumberY[0]);
        
    }

    
    h_EnergyDeposit->Write();
    h_StoppinPositionX->Write();
    h_StoppinPositionY->Write();
    h_StoppinPositionZ->Write();
    
    plik->Close();
    delete plik;
}
