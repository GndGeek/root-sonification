{
TFile *f=new TFile("student_t.root","recreate");
int bins=50;
        
        TF1 *g1=new TF1("g1","ROOT::Math::tdistribution_pdf(x,3.0)",0,10);

        TH1F *h1=new TH1F("h1","student_t",bins,0,10);
        

        Double_t number1;

std::vector<Double_t> * volume1=new std::vector<Double_t>;
std::vector<Double_t> * frequency=new std::vector<Double_t>;
std::vector<Double_t> * error1=new std::vector<Double_t>;

        for (int i=0;i<5000;i++)
        {
                
number1=g1->GetRandom(0,10);         
       h1->Fill(number1);


  
      }

        for (int i = 0 ;i<bins;i++)
{
                
//number2 = h2 ->GetBinError(i+1);                 
 int element_volume1=h1->GetBinContent(i+1);


volume1->push_back(element_volume1);
//volume2->push_back(element_volume2);

frequency->push_back(i);       
error1->push_back(number1); 
       
             
        }
  
//h1->Draw();
//h2->Draw("same");  
h1->Write();
//h2->Write();
f->Close();
             
}

