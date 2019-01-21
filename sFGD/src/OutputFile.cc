#include "OutputFile.hh"
#include <iostream>


OutputFile::OutputFile(std::string filename)
{
    outputFile = new TFile(filename.c_str(), "recreate");
    
    ProtonTree = new TTree("ProtonTree", "ProtonTree");
    ProtonTree->Branch("enDep", &enDep);
    ProtonTree->Branch("CubeNumber", &CubeNumber);
    ProtonTree->Branch("StepNumber", &StepNumber);
   
    StepByStepTree = new TTree("StepByStepTree", "StepByStepTree");
    StepByStepTree->Branch("enDepStep", &enDepStep);
    StepByStepTree->Branch("CubeNumberStep", &CubeNumberStep);
}

OutputFile::~OutputFile()
{
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}

void OutputFile::AddEntry(double energy, int cubeNum, int stepNum)
{
enDep = energy;
CubeNumber = cubeNum;
StepNumber = stepNum;

ProtonTree->Fill();
}


void OutputFile::AddEntryStep(double energyStep, int cubeNumStep)
{
enDepStep = energyStep;
CubeNumberStep = cubeNumStep;

StepByStepTree->Fill();
}
