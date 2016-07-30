
{
TFile *f=new TFile("gaussian.root","recreate");
int bins=50;
        TF1 *g1 =new TF1("g1","gaus",-20,20);
        g1->SetParameters(1,-2,2);
        TH1 *h1=new TH1F("h1","gaus",bins,-20,20);
        h1->Sumw2();

        Double_t number;

std::vector<Double_t> * volume=new std::vector<Double_t>;
std::vector<Double_t> * frequency=new std::vector<Double_t>;
std::vector<Double_t> * error=new std::vector<Double_t>;
        for (int i=0;i<1000;i++)
        {
                number=g1->GetRandom(-20,20);         
       h1->Fill(number);

        }

        for (int i = 0 ;i<bins;i++)
{
                number = h1 ->GetBinError(i+1);                
 int element_volume=h1->GetBinContent(i+1);
volume->push_back(element_volume);
frequency->push_back(-20+i*40/bins);       
error->push_back(number);       
                
        }
  
  
h1->Write();
f->Close();
             
}

