void readTree_combined() {
  Char_t *filename = "Data.root";
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
  // Combined fit
  TF1* myBack  = new TF1("myBack","[0]+[1]*x+[2]*x**2",100.,160.);
  myBack->SetParameter(0,0.);
  myBack->SetParameter(1,0.);
  myBack->SetParameter(2,0.);
  hmass->Fit(myBack,"Q");
  hmass->DrawClone("e");
  Double_t chi2 = myBack->GetChisquare();
  Double_t NDF  = myBack->GetNDF();
  cout << "========================" << endl;
  cout << "Background only p-value: " << TMath::Prob(chi2,NDF) << endl;
  cout << "========================" << endl;
  // Background+signal
  TF1* myHiggs = new TF1("myHiggs","[0]+[1]*x+[2]*x**2+([3]/(0.205*sqrt([4])))*exp(-0.5*(x-[4])**2/(0.205*sqrt([4]))**2)",100.,160.);
  myHiggs->SetParameter(0,myBack->GetParameter(0));
  myHiggs->SetParameter(1,myBack->GetParameter(1));
  myHiggs->SetParameter(2,myBack->GetParameter(2));
  myHiggs->SetParameter(3,0.);
  myHiggs->SetParameter(4,120.);
  TCanvas *c2 = new TCanvas();
  hmass->Fit(myHiggs,"S");
  chi2 = myHiggs->GetChisquare();
  NDF  = myHiggs->GetNDF();
  cout << "==========================" << endl;
  cout << "Background+Signal p-value: " << TMath::Prob(chi2,NDF) << endl;
  cout << "==========================" << endl;
  cout << "Significance of excess is: " << myHiggs->GetParameter(3)/myHiggs->GetParError(3) << endl;
  cout << "Mass value is: " << myHiggs->GetParameter(4) << " +- " << myHiggs->GetParError(4) 
       << " GeV" << endl;
  hmass->Draw("e");
  myBack->SetParameter(0,myHiggs->GetParameter(0));
  myBack->SetParameter(1,myHiggs->GetParameter(1));
  myBack->SetParameter(2,myHiggs->GetParameter(2));
  myBack->SetLineColor(2);
  myBack->SetLineStyle(2);
  myBack->Draw("SAME");
  myFile->Close();
  TFile * output = TFile::Open("Higgs_mass.root", "recreate");
  hmass->Write();
  output->Close();
}
