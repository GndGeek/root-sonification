{
TFile *f=new TFile("tester.root","recreate");
int bins=50;
        TF1 *g1 =new TF1("g1","abs(sin(x)/x)",0,10);
        
        TH1 *h1=new TH1F("h1","tester",bins,0,10);
        h1->Sumw2();

        Double_t number;

std::vector<Double_t> * volume=new std::vector<Double_t>;
std::vector<Double_t> * frequency=new std::vector<Double_t>;
std::vector<Double_t> * error=new std::vector<Double_t>;
        for (int i=0;i<1000;i++)
        {
                number=g1->GetRandom(0,10);         
       h1->Fill(number);

        }

        for (int i = 0 ;i<bins;i++)
{
                number = h1 ->GetBinError(i+1);                
 int element_volume=h1->GetBinContent(i+1);
volume->push_back(element_volume);
frequency->push_back(i*10/bins);       
error->push_back(number);       
                
        }
  
  
h1->Write();
f->Close();
             
}

