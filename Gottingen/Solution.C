{
  gROOT->LoadMacro("CLcalculator.C+"); // or execute .L CLcalculator.C+ before running this macro
  std::cout << fixed;
  std::cout.precision(4);
  // CL of rejection of bacground hypothesis, no uncertainties
  std::cout << "CL of rejection of background-only hypothesis:" << std::endl;
  std::cout << "2011 data 2 bkg events expected, 4 observed: CL=" 
	    << CL(4,2.,0.,false) << std::endl;
  std::cout << "2012 data 3 bkg events expected, 9 observed: CL=" 
	    << CL(9,3.,0.,false) << std::endl;
  std::cout << "Total data 5.1 bkg events expected, 13 observed: CL=" 
	    << CL(13,5.1,0.,false) << std::endl;
  // CL of rejection of Higgs hypotesis if observing exactly the expected number of background events
  std::cout << "CL of rejection of Higgs hypothesis:" << std::endl;
  std::cout << "2011 data 2 bkg+2 Higgs events expected, assuming 2 observed: CL=" 
	    << CL(2,4.,0.,true) << std::endl;
  std::cout << "2012 data 3 bkg+3 Higgs events expected, assuming 3 observed: CL=" 
	    << CL(3,6.,0.,true) << std::endl;
  std::cout << "Total data 5.1 bkg+5.3 Higgs events expected, assuming 5 observed: CL=" 
	    << CL(5,10.4,0.,true) << std::endl;
  // CL of rejection of bacground hypothesis, with uncertainty on Nb
  std::cout << "CL of rejection of background-only hypothesis (with systematics):" << std::endl;
  std::cout << "2011 data 2 bkg events expected, 4 observed: CL=" 
	    << CL(4,2.,0.3,false) << std::endl;
  std::cout << "2012 data 3 bkg events expected, 9 observed: CL=" 
	    << CL(9,3.,0.4,false) << std::endl;
  std::cout << "Total data 5.1 bkg events expected, 13 observed: CL=" 
	    << CL(13,5.1,0.8,false) << std::endl;
  // CL of rejection of Higgs hypotesis if observing exactly the expected number of background events
  // with systematic uncertainties
  std::cout << "CL of rejection of Higgs hypothesis (with systematics):" << std::endl;
  std::cout << "2011 data 2 bkg+2 Higgs events expected, assuming 2 observed: CL=" 
	    << CL(2,4.,0.6,true) << std::endl;
  std::cout << "2012 data 3 bkg+3 Higgs events expected, assuming 3 observed: CL=" 
	    << CL(3,6.,0.9,true) << std::endl;
  std::cout << "Total data 5.1 bkg+5.3 Higgs events expected, assuming 5 observed: CL=" 
	    << CL(5,10.4,1.6,true) << std::endl;

  // expected and observed exclusion limit on Ns
  vector<Double_t> percentiles(5);
  percentiles[0]=0.50;
  percentiles[1]=0.16;
  percentiles[2]=0.84;
  percentiles[3]=0.0225;
  percentiles[4]=0.9775;

  std::cout.precision(1);

  std::cout << "Using 2011 data" << std::endl;
  ConfidenceLevelCalculator.SetParameter(0,4.);
  ConfidenceLevelCalculator.SetParameter(1,0.3);
  ConfidenceLevelCalculator.SetParameter(2,+1.);
  std::cout << "Excluded value at 95% CL: Ns>" <<   ConfidenceLevelCalculator.GetX(0.95) << std::endl;
  vector<Double_t> exclusion = ExpectedExclusionLimit(2,0.3,0.95,percentiles);
  std::cout << "Expected limits. NS > " << exclusion[0]
	    << "  +" << exclusion[2] <<"-"<<exclusion[1]
	    << "  +" << exclusion[4] <<"-"<<exclusion[3] << std::endl;

  std::cout << "Using 2012 data" << std::endl;
  ConfidenceLevelCalculator.SetParameter(0,9.);
  ConfidenceLevelCalculator.SetParameter(1,0.4);
  ConfidenceLevelCalculator.SetParameter(2,+1.);
  std::cout << "Excluded value at 95% CL: Ns>" <<   ConfidenceLevelCalculator.GetX(0.95) << std::endl;
  exclusion = ExpectedExclusionLimit(3,0.4,0.95,percentiles);
  std::cout << "Expected limits. NS > " << exclusion[0]
	    << "  +" << exclusion[2] <<"-"<<exclusion[1]
	    << "  +" << exclusion[4] <<"-"<<exclusion[3] << std::endl;

  std::cout << "Using all data" << std::endl;
  ConfidenceLevelCalculator.SetParameter(0,13.);
  ConfidenceLevelCalculator.SetParameter(1,0.8);
  ConfidenceLevelCalculator.SetParameter(2,+1.);
  std::cout << "Excluded value at 95% CL: Ns>" <<   ConfidenceLevelCalculator.GetX(0.95) << std::endl;
  exclusion = ExpectedExclusionLimit(5.1,0.8,0.95,percentiles);
  std::cout << "Expected limits. NS > " << exclusion[0]
	    << "  +" << exclusion[2] <<"-"<<exclusion[1]
	    << "  +" << exclusion[4] <<"-"<<exclusion[3] << std::endl;
}
