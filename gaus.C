
{
TFile *f=new TFile("oscilation.root","recreate");
int bins=50;
        TF1 *g1 =new TF1("g1","sin(x)*sin(x)",-20,20);
        TF1 *g2=new TF1("g2","gaus",-20,20);
g2->SetParameters(1,0,10);
        TH1F *h1=new TH1F("h1","oscilation",bins,-20,20);
        TH1F *h2=new TH1F("h2","gaus",bins,-20,20);

        Double_t number1,number2;

std::vector<Double_t> * volume1=new std::vector<Double_t>;
std::vector<Double_t> * frequency=new std::vector<Double_t>;
std::vector<Double_t> * error1=new std::vector<Double_t>;
std::vector<Double_t> * volume2=new std::vector<Double_t>;
std::vector<Double_t> * error2=new std::vector<Double_t>;

        for (int i=0;i<1000;i++)
        {
                number1=g1->GetRandom(-20,20);
number2=g2->GetRandom(-20,20);         
       h1->Fill(number1);
h2->Fill(number2);

        }

        for (int i = 0 ;i<bins;i++)
{
                number1 = h1 ->GetBinError(i+1); 
number2 = h2 ->GetBinError(i+1);                 
 int element_volume1=h1->GetBinContent(i+1);
int element_volume2=h2->GetBinContent(i+1);

volume1->push_back(element_volume1);
volume2->push_back(element_volume2);

frequency->push_back(-20+i*40/bins);       
error1->push_back(number1); 
error1->push_back(number1);       
             
        }
  
h1->Draw();
h2->Draw("same");  
h1->Write();
f->Close();
             
}

