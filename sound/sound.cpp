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

int main(int argc, char* argv[])
{ 
  //Essentials

  //Upload the file with the data, make sure the adress of the file matches the one in your computer
  TFile* file = TFile::Open("/Users/Fer/Documents/traajo/samples/NeroNtuples_9.root"); // TFile::Open() instead of a constructor since it works over xrootd etc. =D
  
  //Upload the tree with the event data
  TTree *tree=(TTree*)file->Get("nero/events");

/////////////////////////////////////////////////////

  //MET criteria

  //Create a variable to store all the "met" data
  TClonesArray *metdata = new TClonesArray("metdata");

  //Specify where all the "met" data will be stored
  tree->SetBranchAddress("metP4", &metdata);

  //Sound vector
  std::vector<Double_t> * volume = new std::vector<Double_t>;
  //Frequency vector
  std::vector<Double_t> * freq = new std::vector<Double_t>;
  
  //Resolution of the histogram
  int bins=50;

  //Start of the x axis
  int a=0;
  //End of the x axis
  int d=150;

  //This two constants are used to map mass to frequency 
  Double_t g=3000/d;
  Double_t step=d/bins;

  //Histogram to plot the distribution of the transverse mass 
  TH1F *metmass = new TH1F("metmass", "Missing transverse mass", bins, a, d); 

/////////////////////////////////////////////////////

  //Histogram variables

  //Create the canvas were the histograms will be ploted
  TCanvas* c1 = new TCanvas("c1", "Masses", 600, 600);

/////////////////////////////////////////////////////

  //Variables for the for loop

  //Get how many events we have to loop through
  int nentries = tree->GetEntries();

  //Create a variable to store the mass values
  Double_t mass;

  //Loop through all the events
  for(int ientry = 0; ientry < 50; ientry++) 
  {
    //Reset the met data 
    metdata->Clear();

    //This line stores the proper data in the variables qe specified
    tree->GetEntry(ientry);
    
//Implementation of met criteria 

    //Create a lorentz vector with the matdata of the current entry
    TLorentzVector * lorentz_metdata = (TLorentzVector *) metdata->At(0);

    //Get the invariant transverse mass of that lorentz vector
    mass=lorentz_metdata->Mt();
  
  	//Put the mass in the histogram
    metmass->Fill(mass);
  }

//Loop to fill the mass and frequency vectors
  for (int i = 0; i < bins; ++i)
  {
    //Get the hight of the bin
  	Int_t element_volume=metmass->GetBinContent (i);
  	//Put it in the volume vector 
  	volume->push_back(element_volume);
  	//Fill the frequency vector with the formula that maps mass to frequency depending on the iteration
  	freq->push_back(i*g*step+2000);
  }

  // cleanup
  delete file; // automatically deletes "tree" too
  delete metdata;
  return 0; 
}
