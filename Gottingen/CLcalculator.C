#include "RooRealVar.h"
#include "RooPoisson.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"

#include "TH1F.h"
#include "TF1.h"
#include "TRandom.h"
#include "TROOT.h"

#include <iostream>

using namespace RooFit;

/******************************************************************************
 * Compute the confidence leve at which a hypothesis woould be discarted.
 * If "exclusion" is true, the usual exclusion limit is computed (confidence level
 * for excluding signals too big) otherwise the usual rejection of backgroud 
 * hypothesis is performed.
 ******************************************************************************/


TH1* ProbabilitySampling(Double_t mu, Double_t smu=0) {
  Int_t nmax = (mu+3*smu)+3.*sqrt(mu+3.*smu)+10;
  RooRealVar iNobs("Nobs","Observed events",0.,Double_t(nmax));
  RooRealVar imu("mu","Expected events",mu,0.,Double_t(nmax));
  RooRealVar fmu("fmu","Central value of mu",mu);
  RooRealVar fsmu("fsmu","Central value of smu",smu);
  RooPoisson observed("observed","Observed events",iNobs,imu);

  RooDataSet *mydata=0;

  const Int_t nEvents = 100000;

  if ( smu ) { //   smu!=0
    RooGaussian mupdf("mupdf","Mu value",imu,fmu,fsmu);  
    RooProdPdf modPoisson("modPoisson","Poisson with uncertainty on mu",
  			mupdf,Conditional(observed,iNobs));
    mydata = modPoisson.generate(RooArgSet(iNobs,imu),nEvents);
  } else {
    mydata = observed.generate(iNobs,nEvents);
  }

  TH1F* myh = new TH1F("myh","N distribution",nmax,-0.5,nmax-.5);
  mydata->fillHistogram(myh,iNobs);
  return myh;
}

/*
TH1* ProbabilitySampling(Double_t mu, Double_t smu=0) {
  TRandom  generator(0);
  Int_t nmax = 3*(mu+3*smu)+6; Int_t nEvents = 100000;
  TH1F* myh = new TH1F("myh","N distribution",nmax,-0.5,nmax-.5);
  for (Int_t i=0; i<nEvents; i++) {
    Double_t nu1 = generator.Gaus(mu,smu);
    myh->Fill(generator.Poisson(nu1));
  }
  return myh;
}
*/

Double_t CL(Int_t Nobs, Double_t mu, Double_t smu=0, Bool_t exclusion=true)
{
  TH1* myh = ProbabilitySampling(mu,smu);
  Double_t nEvents = myh->GetEntries();
  Int_t lowerI=0; Double_t confidence=0.;

  if (Nobs > myh->GetNbinsX()-1 ) {
    if (exclusion) confidence = 0.;
    else confidence = 1.;
  } else {
    for ( Int_t bin=1; bin<=Nobs; bin++) lowerI+=myh->GetBinContent(bin);
    if ( exclusion ) { 
      lowerI+=myh->GetBinContent(Nobs+1);
      confidence = 1.-Double_t(lowerI)/Double_t(nEvents);
    } else {
      confidence = Double_t(lowerI)/Double_t(nEvents);
    } 
  }
  delete myh;
  return confidence;
}

/*
 * Wrapper to CL to be promoted to a TF1
 * x is a mu hypothesis.
 * return value is a confidence level - the required ones
 * p[0] = Nobs
 * p[1] = Uncertainty on Ns
 * p[2] = lower or upper limit
 */
Double_t CL1(Double_t *x, Double_t *p) {
  Bool_t exclusion = p[2]>=0.;
  Int_t Nobs = Int_t(p[0]);
  return CL(Nobs,x[0],p[1],exclusion);
}

TF1 ConfidenceLevelCalculator("CLcalc",CL1,0.,100.,3);

vector<Double_t> ExpectedExclusionLimit(Double_t Nb, Double_t sigma, Double_t alpha, const vector<Double_t>& percentiles) {
  Int_t n = percentiles.size();
  vector<Double_t> exclusion(n);
  vector<Int_t> Nlimit(n);
  for (Int_t i=0; i<n; i++) Nlimit[i]=-1;

  TH1* myh = ProbabilitySampling(Nb,sigma);
  ConfidenceLevelCalculator.SetRange(0.,myh->GetNbinsX());
  ConfidenceLevelCalculator.SetParameter(1,sigma);
  ConfidenceLevelCalculator.SetParameter(2,+1.);

  Double_t entries = Double_t(myh->GetEntries());
  Double_t integral = 0;
  for (Int_t bin=1; bin<=(myh->GetNbinsX())+2; bin++) {
    integral += ( myh->GetBinContent(bin) / entries );
    for (Int_t i=0; i<n; i++) {
      if ( Nlimit[i]==-1 && integral>=percentiles[i] ) {
        Nlimit[i]=bin-1;
	ConfidenceLevelCalculator.SetParameter(0,Nlimit[i]);
        exclusion[i] = ConfidenceLevelCalculator.GetX(alpha,Nlimit[i],myh->GetNbinsX(),0.2);
        if ( exclusion[i]>Nb ) exclusion[i]-=Nb;
        else exclusion[i]=0;
      } 
    }
  } 
  delete myh;
  return exclusion;
}
