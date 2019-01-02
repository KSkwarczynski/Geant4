#include "OutputFile.hh"
#include <iostream>


OutputFile::OutputFile(std::string filename)
{
   outputFile = new TFile(filename.c_str(), "recreate");
   ProtonTree = new TTree("ProtonTree", "ProtonTree");
   
   ProtonTree->Branch("enDep", &enDep);
   ProtonTree->Branch("CubeNumber", &CubeNumber);

}

OutputFile::~OutputFile()
{
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}

void OutputFile::AddEntry(double energy, int cubeNum)
{
enDep = energy;
CubeNumber = cubeNum;

ProtonTree->Fill();
}
