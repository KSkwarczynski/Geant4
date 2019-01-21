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
        void AddEntry(double energy, int cubeNum, int stepNum);
        void AddEntryStep(double energyStep, int cubeNumStep);

    private:
        TFile* outputFile;
   
        TTree* ProtonTree;
        TTree* StepByStepTree;
   
        double enDep;
        int CubeNumber;
        int StepNumber;
   
        double enDepStep;
        int CubeNumberStep;
};
#endif
