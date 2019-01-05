using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <TCanvas.h>
#include "TH1.h"

void RootFileReconstruction(){
    TFile* fileTree= TFile::Open("/home/kamil/Pulpit/Geant4/sFGD/build/StoppingProton.root");
    
    TTree* ProtonTree;
    fileTree->GetObject("ProtonTree", ProtonTree);
    
    TTree* StepByStepTree;
    fileTree->GetObject("StepByStepTree", StepByStepTree);
    
    double enDep;
    int CubeNumber;
    int StepNumber;
    
    ProtonTree->SetBranchAddress("enDep", &enDep);
    ProtonTree->SetBranchAddress("CubeNumber", &CubeNumber);
    ProtonTree->SetBranchAddress("StepNumber", &StepNumber);
    
    double enDepStep;
    int CubeNumberStep;
    
    StepByStepTree->SetBranchAddress("enDepStep", &enDepStep);
    StepByStepTree->SetBranchAddress("CubeNumberStep", &CubeNumberStep);
    
    
    TFile *plik = new TFile("StoppingProtonReconstructed.root","RECREATE");
    
    TH1F *h_EnergyDeposit = new TH1F("EnergyDepositHist", "Energy Depostied by a stopping proton", 150, 0, 150);
    
    TH1F *h_StepCounter = new TH1F("h_StepCounter", "Number of steps in one event", 1000, 0, 1000);
    
    TH1F *h_StoppinPositionX = new TH1F("StoppinPositionX", "Stoppin Position X", 24, 0, 24);
    TH1F *h_StoppinPositionY = new TH1F("StoppinPositionY", "Stoppin Position Y", 8, 0, 8);
    TH1F *h_StoppinPositionZ = new TH1F("StoppinPositionZ", "Stoppin Position Z", 48, 0, 48);
    
    TDirectory *events2D = plik->mkdir("events2D");
    TCanvas *DisplayCanvas = new TCanvas("DisplayCanvas","DisplayCanvas", 1400, 1000);
    int Eventy = ProtonTree->GetEntries();

    int liczbaStepow[Eventy];
    for(int i=0; i<Eventy ; i++)
    {
        int NumerPomocniczy=0;
        
        int CubeNumberX[3]={}; // [0-wlasciwa liczba, 1-cyfra dzisietna ,2- cyfra jednosci]
        int CubeNumberY[3]={};
        int CubeNumberZ[3]={};

        ProtonTree->GetEntry(i);
        
        h_EnergyDeposit->Fill(enDep);
        
        NumerPomocniczy = CubeNumber;
        std::string Numer_String;
        std::stringstream kontener;
        kontener << NumerPomocniczy;
        Numer_String = kontener.str();

        CubeNumberZ[1]=Numer_String[4]-'0';
        CubeNumberZ[2]=Numer_String[5]-'0';
        CubeNumberZ[0]=10*CubeNumberZ[1]+CubeNumberZ[2];
        
        CubeNumberX[1]=Numer_String[2]-'0';
        CubeNumberX[2]=Numer_String[3]-'0';
        CubeNumberX[0]=10*CubeNumberX[1]+CubeNumberX[2];
        
        CubeNumberY[0]=Numer_String[1]-'0';
        
        h_StoppinPositionZ->Fill(CubeNumberZ[0]);
        h_StoppinPositionX->Fill(CubeNumberX[0]);
        h_StoppinPositionY->Fill(CubeNumberY[0]);
        liczbaStepow[i]=StepNumber;
    }

    ostringstream sEventnum;
    string sEvent;
    
    TH2F* event_XY[Eventy];
    for (Int_t ih=0; ih < Eventy;ih++)
    {
       sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XY_"+sEventnum.str();
        event_XY[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 8,0,8);
        event_XY[ih]->GetYaxis()->SetTitle("Y axis");
        event_XY[ih]->GetXaxis()->SetTitle("X axis");
    }
    
    TH2F *event_YZ[Eventy];
    for (Int_t ih=0; ih < Eventy;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_YZ_"+sEventnum.str();
        event_YZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,0,48, 8,0,8);
        event_YZ[ih]->GetYaxis()->SetTitle("Y axis");
        event_YZ[ih]->GetXaxis()->SetTitle("Z axis");
    }

    TH2F *event_XZ[Eventy];
    for (Int_t ih=0; ih < Eventy;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XZ_"+sEventnum.str();
        event_XZ[ih] = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,0,24, 48,0,48);
        event_XZ[ih]->GetYaxis()->SetTitle("Z axis");
        event_XZ[ih]->GetXaxis()->SetTitle("X axis");
    }
    TH1F *energy_Z[Eventy];
    for (Int_t ih=0; ih < Eventy;ih++)
    {
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "energy_Z_"+sEventnum.str();
        energy_Z[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(),48,0,48);
        energy_Z[ih]->GetYaxis()->SetTitle("Energy deposit [p.e.]");
        energy_Z[ih]->GetXaxis()->SetTitle("Z axis");
    }
    int StepEventy = StepByStepTree->GetEntries();
    int NumerObecnegoEventu=0;
    int StepCounterInLoop=0;
    
    double energyDepZ[48]={};
     
    for(int i=0; i<StepEventy ; i++)
    //for(int i=0; i<7000 ; i++)
    {
        StepByStepTree->GetEntry(i);
        
        if(StepCounterInLoop==liczbaStepow[NumerObecnegoEventu])
        {
            StepCounterInLoop=0;
            NumerObecnegoEventu++;
            for(int ik = 0; ik < 48; ik++ )
            {
                energy_Z[NumerObecnegoEventu]->Fill(ik,energyDepZ[ik]);
                energyDepZ[ik]=0;
            }
        }
        
        int NumerPomocniczy=0;
        int CubeNumberX[3]={}; // [0-wlasciwa liczba, 1-cyfra dziesietna ,2- cyfra jednosci]
        int CubeNumberY[3]={};
        int CubeNumberZ[3]={};
        
        NumerPomocniczy = CubeNumberStep;
        std::string Numer_String;
        std::stringstream kontener;
        kontener << NumerPomocniczy;
        Numer_String = kontener.str();

        CubeNumberZ[1]=Numer_String[4]-'0';
        CubeNumberZ[2]=Numer_String[5]-'0';
        CubeNumberZ[0]=10*CubeNumberZ[1]+CubeNumberZ[2];
        
        CubeNumberX[1]=Numer_String[2]-'0';
        CubeNumberX[2]=Numer_String[3]-'0';
        CubeNumberX[0]=10*CubeNumberX[1]+CubeNumberX[2];
        
        CubeNumberY[0]=Numer_String[1]-'0';
        
        event_XY[NumerObecnegoEventu]->Fill( CubeNumberX[0], CubeNumberY[0],enDepStep );
        event_YZ[NumerObecnegoEventu]->Fill( CubeNumberZ[0], CubeNumberY[0],enDepStep );
        event_XZ[NumerObecnegoEventu]->Fill( CubeNumberX[0], CubeNumberZ[0],enDepStep );
        
        energyDepZ[CubeNumberZ[0]]+=enDepStep;
        
        StepCounterInLoop++;
    }
    
    for(int iEvent=0; iEvent<Eventy ; iEvent++)
    //for(int iEvent=0; iEvent<15 ; iEvent++)
    {
        DisplayCanvas->Clear();
        DisplayCanvas->Divide(2,2);
        
        DisplayCanvas -> cd(1);
        event_XZ[iEvent]-> Draw("colorz");

        DisplayCanvas -> cd(2);
        event_YZ[iEvent]-> Draw("colorz");

        DisplayCanvas -> cd(3);
        event_XY[iEvent]-> Draw("colorz");
        
        DisplayCanvas -> cd(4);
        energy_Z[iEvent]-> Draw("HIST");
        
        DisplayCanvas->Update();
        events2D -> cd();

        DisplayCanvas->Write();
    }
        
    plik->cd();
    h_EnergyDeposit->Write();
    h_StoppinPositionX->Write();
    h_StoppinPositionY->Write();
    h_StoppinPositionZ->Write();
    
    fileTree->Close();
    
    plik->Close();
    
    delete plik;
}
