void readTree_background() {
  Char_t *filename = "Background.root";
  // Retrieve the TTree
  TFile* myFile = TFile::Open(filename);
  TTree* tree = (TTree*)(myFile->Get("tree"));
  Double_t Et1, eta1, phi1, Et2, eta2, phi2;
  tree->SetBranchAddress("Et1" ,&Et1 );
  tree->SetBranchAddress("eta1",&eta1);
  tree->SetBranchAddress("phi1",&phi1);
  tree->SetBranchAddress("Et2" ,&Et2 );
  tree->SetBranchAddress("eta2",&eta2);
  tree->SetBranchAddress("phi2",&phi2);
  // Book histograms
  TH1F* hmass = new TH1F("hmass","m_{#gamma#gamma}",60,100.,160.);
  hmass->GetXaxis()->SetTitle("Invariant mass [GeV]");
  hmass->GetYaxis()->SetTitle("Events");
  // Loop over the events
  Long64_t events = tree->GetEntries();  
  for (int i=0; i<events; i++) {
    tree->GetEntry(i);
    TLorentzVector g1,g2;
    g1.SetPtEtaPhiM(Et1,eta1,phi1,0.);
    g2.SetPtEtaPhiM(Et2,eta2,phi2,0.);
    TLorentzVector gg=g1+g2;
    hmass->Fill( gg.M() );
  }
  // Test of different background options
  hmass->DrawClone("e");
  TCanvas* myCanvas = new TCanvas("myCanvas","Background fits",800,800);
  myCanvas->Divide(2,2);
  // Linear background
  TF1* myBack1 = new TF1("myBack1","[0]+[1]*x",100.,160.);
  myBack1->SetParameter(0,events);
  myBack1->SetParameter(1,-100.);
  myCanvas->cd(1);
  hmass->Fit(myBack1);
  hmass->DrawClone("e");
  EvaluatePvalue(myBack1);
  // Quadratic background
  TF1* myBack2 = new TF1("myBack2","[0]+[1]*x+[2]*x**2",100.,160.);
  myBack2->SetParameter(0,events);
  myBack2->SetParameter(1,-100.);
  myBack2->SetParameter(1,0.);
  myCanvas->cd(2);
  hmass->Fit(myBack2);
  hmass->DrawClone("e");
  EvaluatePvalue(myBack2);
  // Exponential background
  TF1* myBack3 = new TF1("myBack3","[0]*exp(-x/[1])",100.,160.);
  myBack3->SetParameter(0,events);
  myBack3->SetParameter(1,100.);
  myCanvas->cd(3);
  hmass->Fit(myBack3);
  hmass->DrawClone("e");
  EvaluatePvalue(myBack3);
  // Cubic background
  TF1* myBack4 = new TF1("myBack4","[0]+[1]*x+[2]*x**2+[3]*x**3",100.,160.);
  myBack4->SetParameter(0,0.);
  myBack4->SetParameter(1,0.);
  myBack4->SetParameter(2,0.);
  myBack4->SetParameter(3,0.);
  myCanvas->cd(4);
  TFitResultPtr fit4 = hmass->Fit(myBack4,"S");
  hmass->DrawClone("e");
  EvaluatePvalue(myBack4);
}

Double_t EvaluatePvalue(TF1* myfunc) {
  Double_t chi2 = myfunc->GetChisquare();
  Int_t NDF = myfunc->GetNDF();
  Double_t pval = TMath::Prob(chi2,NDF);
  std::cout << "Function " << myfunc->GetExpFormula() << " has p-value " << pval << std::endl;
  return pval; 
}
