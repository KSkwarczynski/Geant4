#ifndef OutputFile_H
#define OutputFile_H

#include <string>
#include "TFile.h"
#include "TTree.h"

class OutputFile 
{
    public:
    OutputFile(std::string fileName);
   ~OutputFile();
   void AddEntry(double energy, int cubeNum);

private:
   TFile* outputFile;
   TTree* ProtonTree;
   double enDep;
   int CubeNumber;

};
#endif
