// All libraries you could wish for
#include <iostream>                 // class for inputoutput streams
#include <stdio.h>                  // printf, scanf, puts, NULL
#include <stdlib.h>                 // srand, rand, atof
#include <time.h>                   // time
#include <fstream>                  // class for inputoutput file streams
#include <dirent.h>
#include <string.h>           // class to manipulate strings
#include <sstream>                    // class for parsing strings
#include <vector>


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TPaveStats.h>
#include <TPad.h>
#include <TMath.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TString.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TLorentzVector.h>


#include <unistd.h>
#define GetCurrentDir getcwd

#include <TTree.h>
#include <TClonesArray.h>
#include "Math/SMatrix.h"

using namespace std;

//Sonification of root for blind scientist

//Get the volume vector 
std::vector<Double_t> volume(char * filename, char * histoname)
{ 

/////////////////////////////////////////////////////

//Load the file with the histogram
  TFile *f=new TFile(filename,"read");
//Extract the histogram
//the name of the histogram should be a string class variable, but for now it has t be h1
  TH1F *h1=(TH1F*)f->Get(histoname);
  Double_t number;

 //Resolution of the histogram
  Int_t bins=h1->GetSize()-2;

//Maximum value of the histogram
  Double_t max=h1->GetMaximum();

//Minimum value of the histogram  
  Double_t min=h1->GetMinimum();

//Variables to calculate the frequency
  Double_t step=max/bins;
  Double_t k=3000/(max-min);
  Double_t b=5000-k*max;

//Vectors to store what we want
  std::vector<double> volume;
  std::vector<double> frequency;
  std::vector<double> error;

//Loop to store the values
  for (int i = 0 ;i<bins;i++)
    {
      //Get the error
      number = h1 ->GetBinError(i+1);  

      //Get the hight of the bin, this will be maped to sound by other program              
      double element_volume=h1->GetBinContent(i+1);

      //Store the volume
      volume.push_back(element_volume);

      //Store the frequency
      frequency.push_back(i*step*k+b);

      //Store the error       
      error.push_back(number);                      
    }

  // cleanup
  delete f; 
  return volume; 
}


vector<double> frequency(char * filename, char * histoname)
{ 

/////////////////////////////////////////////////////

//Load the file with the histogram
  TFile *f=new TFile(filename,"read");
//Extract the histogram
//the name of the histogram should be a string class variable, but for now it has t be h1
  TH1F *h1=(TH1F*)f->Get(histoname);
  Double_t number;

 //Resolution of the histogram
  Int_t bins=h1->GetSize()-2;

//Maximum value of the histogram
  Double_t max=h1->GetMaximum();

//Minimum value of the histogram  
  Double_t min=h1->GetMinimum();

//Variables to calculate the frequency
  Double_t step=max/bins;
  Double_t k=3000/(max-min);
  Double_t b=5000-k*max;

//Vectors to store what we want
  std::vector<double> volume;
  std::vector<double> frequency;
  std::vector<double> error;

//Loop to store the values
  for (int i = 0 ;i<bins;i++)
    {
      //Get the error
      number = h1 ->GetBinError(i+1);  

      //Get the hight of the bin, this will be maped to sound by other program              
      double element_volume=h1->GetBinContent(i+1);

      //Store the volume
      volume.push_back(element_volume);

      //Store the frequency
      frequency.push_back(i*step*k+b);

      //Store the error       
      error.push_back(number);                      
    }

  // cleanup
  delete f;
  return frequency; 
}

//This returns the vectors we got, don't ask me how
 int main()
 {
   return 0;
 }