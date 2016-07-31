void readTree_strength() {
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
  TF1* myHiggs = new TF1("myHiggs","[0]+[1]*x+[2]*x**2+([3]/(0.205*sqrt([4])))*exp(-0.5*(x-[4])**2/(0.205*sqrt([4]))**2)",100.,160.);
  myHiggs->SetParameter(0,2000);
  myHiggs->SetParameter(1,-100.);
  myHiggs->SetParameter(2,0.);
  myHiggs->SetParameter(3,0.);
  TGraphErrors* myGraph = new TGraphErrors(120);
  myGraph->SetTitle("Signal strength");
  for (Int_t i=0; i<120; i++) {
    Double_t massH = 100.+0.5*i;
    myHiggs->FixParameter(4,massH);
    hmass->Fit(myHiggs,"SQ");
    myGraph->SetPoint(i,massH,myHiggs->GetParameter(3));
    myGraph->SetPointError(i,0.,myHiggs->GetParError(3));
  }
  TCanvas *c2 = new TCanvas();
  c2->SetGridy(); 
  myGraph->GetXaxis()->SetTitle("m_{H} [GeV]");
  myGraph->GetXaxis()->SetRangeUser(98.5,161.);
  myGraph->GetYaxis()->SetTitle("Amplitude (a.u.)");
  myGraph->SetFillColor(kCyan);
  myGraph->SetLineColor(kBlack);
  myGraph->SetLineWidth(2);
  myGraph->Draw("A4");
  myGraph->Draw("CXSAME");
  TLine *myLine = new TLine(100.,0.,160.,0.);
  myLine->SetLineColor(kRed);
  myLine->SetLineWidth(2);
  myLine->Draw();
}
