{
TFile *f=new TFile("random.root","recreate");
int bins=50;
        
        

        TH1F *h1=new TH1F("h1","random",bins,0,10);
        

        Double_t number1;

std::vector<Double_t> * volume1=new std::vector<Double_t>;
std::vector<Double_t> * frequency=new std::vector<Double_t>;
//std::vector<Double_t> * error1=new std::vector<Double_t>;

        for (int i=0;i<1000;i++)
        {
                
number1=gRandom->Uniform(10);         
       h1->Fill(number1);


        }

        for (int i = 0 ;i<bins;i++)
{
                
//number2 = h2 ->GetBinError(i+1);                 
 int element_volume1=h1->GetBinContent(i+1);


volume1->push_back(element_volume1);
//volume2->push_back(element_volume2);

frequency->push_back(i);       
//error1->push_back(number1); 
       
             
        }
  
//h1->Draw();
//h2->Draw("same");  
h1->Write();
//h2->Write();
f->Close();
             
}

