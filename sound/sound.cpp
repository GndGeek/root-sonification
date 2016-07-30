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

class acc 
{

vector<double> volume()
{ 

  //Resolution of the histogram
  int bins=50;

  //Amount of events
  int amount=1000;

  Double_t max=20;
  Double_t min=-20;
  Double_t step=max/bins;
  Double_t k=3000/(max-min);
  Double_t b=5000-k*max;

/////////////////////////////////////////////////////

  //Create false data

  TFile *f=new TFile("gaussian.root","recreate");
  TF1 *g1 =new TF1("g1","gaus",-20,20);
  g1->SetParameters(1,-2,2);
  TH1 *h1=new TH1F("h1","gaus",bins,-20,20);
  h1->Sumw2();
  Double_t number;

  //std::vector<Int_t> * volume=new std::vector<Int_t>;
  //std::vector<Int_t> * frequency=new std::vector<Int_t>;
  //std::vector<Double_t> * error=new std::vector<Double_t>;

   std::vector<double> volume;
    std::vector<double> frequency;
     std::vector<double> error;

  for (int i=0;i<amount;i++)
  {
    number=g1->GetRandom(-20,20);         
    h1->Fill(number);
  }

  for (int i = 0 ;i<bins;i++)
    {
      number = h1 ->GetBinError(i+1);                
      double element_volume=h1->GetBinContent(i+1);
      volume.push_back(element_volume);
      //cout<<"volume "<<element_volume<<endl;
      frequency.push_back(i*step*k+b);
      //cout<<"freq "<<i*step*k+b<<endl;        
      error.push_back(number);                      
    }

  // cleanup
  delete f; // automatically deletes "tree" too
  return volume; 
}


vector<double> frequency()
{ 

  //Resolution of the histogram
  int bins=50;

  //Amount of events
  int amount=1000;

  Double_t max=20;
  Double_t min=-20;
  Double_t step=max/bins;
  Double_t k=3000/(max-min);
  Double_t b=5000-k*max;

/////////////////////////////////////////////////////

  //Create false data

  TFile *f=new TFile("gaussian.root","recreate");
  TF1 *g1 =new TF1("g1","gaus",-20,20);
  g1->SetParameters(1,-2,2);
  TH1 *h1=new TH1F("h1","gaus",bins,-20,20);
  h1->Sumw2();
  Double_t number;

  //std::vector<Int_t> * volume=new std::vector<Int_t>;
  //std::vector<Int_t> * frequency=new std::vector<Int_t>;
  //std::vector<Double_t> * error=new std::vector<Double_t>;

   std::vector<double> volume;
    std::vector<double> frequency;
     std::vector<double> error;

  for (int i=0;i<amount;i++)
  {
    number=g1->GetRandom(-20,20);         
    h1->Fill(number);
  }

  for (int i = 0 ;i<bins;i++)
    {
      number = h1 ->GetBinError(i+1);                
      double element_volume=h1->GetBinContent(i+1);
      volume.push_back(element_volume);
      //cout<<"volume "<<element_volume<<endl;
      frequency.push_back(i*step*k+b);
      //cout<<"freq "<<i*step*k+b<<endl;       
      error.push_back(number);                      
    }

  // cleanup
  return frequency; 
}


 int main()
 {
    acc * oj = new acc();
    vector<double> test1 = oj->frequency();
    vector<double> test2 = oj->volume();
   return 0;
 }};