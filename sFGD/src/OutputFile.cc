#include "OutputFile.hh"
#include <iostream>


OutputFile::OutputFile(std::string filename)
{
   outputFile = new TFile(filename.c_str(), "recreate");
   ProtonTree = new TTree("ProtonTree", "ProtonTree");

}

OutputFile::~OutputFile()
{
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}
