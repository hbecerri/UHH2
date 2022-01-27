#include <algorithm>
#include <iterator>
#include <TROOT.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void Acceptance(string var_weight = "1", int aa = 1)
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    std::cout << std::setprecision(8);
//////Full

    TChain *chreco_ttbar_Full_2016 = new TChain("AnalysisTree","");
    chreco_ttbar_Full_2016->Add("/nfs/dust/cms/user/hugobg/analysis/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_24.root/AnalysisTree");
    TTree *treereco_ttbar_Full_2016 = (TTree*) chreco_ttbar_Full_2016;

    TChain *chreco_ttbar_Full_2017 = new TChain("AnalysisTree","");
    chreco_ttbar_Full_2017->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2017/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_24.root/AnalysisTree");
    TTree *treereco_ttbar_Full_2017 = (TTree*) chreco_ttbar_Full_2017;

    TChain *chreco_ttbar_Full_2018 = new TChain("AnalysisTree","");
    chreco_ttbar_Full_2018->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_24.root/AnalysisTree");
    TTree *treereco_ttbar_Full_2018 = (TTree*) chreco_ttbar_Full_2018;

/////reco

    TChain *chreco_ttbar_Reco_2016_ele = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2016_ele->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/electron/workdir_Zprime_Analysis_2016_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_Reco_2016_ele = (TTree*) chreco_ttbar_Reco_2016_ele;

    TChain *chreco_ttbar_Reco_2016_muon = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2016_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/muon/workdir_Zprime_Analysis_2016_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_Reco_2016_muon = (TTree*) chreco_ttbar_Reco_2016_muon;

    TChain *chreco_ttbar_Reco_2017_ele = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2017_ele->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    TTree *treereco_Reco_2017_ele = (TTree*) chreco_ttbar_Reco_2017_ele;

    TChain *chreco_ttbar_Reco_2017_muon = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2017_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    TTree *treereco_Reco_2017_muon = (TTree*) chreco_ttbar_Reco_2017_muon;

    TChain *chreco_ttbar_Reco_2018_ele = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2018_ele->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/workdir_Zprime_Analysis_2018_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    TTree *treereco_Reco_2018_ele = (TTree*) chreco_ttbar_Reco_2018_ele;

    TChain *chreco_ttbar_Reco_2018_muon = new TChain("AnalysisTree","");
    chreco_ttbar_Reco_2018_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    TTree *treereco_Reco_2018_muon = (TTree*) chreco_ttbar_Reco_2018_muon;


//array for variable 

    Float_t bins_gen[] = {-10.,0.,10.}; 

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Acc_Full_2016 = new TH1F("Acc_Full_2016","",binnum_gen,bins_gen);
    TH1F *Acc_Full_2017 = new TH1F("Acc_Full_2017","",binnum_gen,bins_gen);
    TH1F *Acc_Full_2018 = new TH1F("Acc_Full_2018","",binnum_gen,bins_gen);

    TH1F *Acc_nominal_Ml_muon_2016 = new TH1F("Acc_nominal_Ml_muon_2016","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_muon_2016 = new TH1F("Acc_nominal_Mh_muon_2016","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Ml_electron_2016 = new TH1F("Acc_nominal_Ml_electron_2016","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_electron_2016 = new TH1F("Acc_nominal_Mh_electron_2016","",binnum_gen,bins_gen);

    TH1F *Acc_nominal_Ml_muon_2017 = new TH1F("Acc_nominal_Ml_muon_2017","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_muon_2017 = new TH1F("Acc_nominal_Mh_muon_2017","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Ml_electron_2017 = new TH1F("Acc_nominal_Ml_electron_2017","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_electron_2017 = new TH1F("Acc_nominal_Mh_electron_2017","",binnum_gen,bins_gen);

    TH1F *Acc_nominal_Ml_muon_2018 = new TH1F("Acc_nominal_Ml_muon_2018","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_muon_2018 = new TH1F("Acc_nominal_Mh_muon_2018","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Ml_electron_2018 = new TH1F("Acc_nominal_Ml_electron_2018","",binnum_gen,bins_gen);
    TH1F *Acc_nominal_Mh_electron_2018 = new TH1F("Acc_nominal_Mh_electron_2018","",binnum_gen,bins_gen);


    string var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    treereco_ttbar_Full_2016->Project("Acc_Full_2016",Form("%s",var_gen.c_str()));
    treereco_ttbar_Full_2017->Project("Acc_Full_2017",Form("%s",var_gen.c_str()));
    treereco_ttbar_Full_2018->Project("Acc_Full_2018",Form("%s",var_gen.c_str()));
 
    treereco_Reco_2018_muon->Project("Acc_nominal_Ml_muon_2018","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2018_muon->Project("Acc_nominal_Mh_muon_2018","DeltaY"," Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");

    treereco_Reco_2017_muon->Project("Acc_nominal_Ml_muon_2017","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2017_muon->Project("Acc_nominal_Mh_muon_2017","DeltaY"," Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");

    treereco_Reco_2016_muon->Project("Acc_nominal_Ml_muon_2016","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2016_muon->Project("Acc_nominal_Mh_muon_2016","DeltaY"," Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");



    treereco_Reco_2018_ele->Project("Acc_nominal_Ml_electron_2018","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2018_ele->Project("Acc_nominal_Mh_electron_2018","DeltaY","Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");

    treereco_Reco_2017_ele->Project("Acc_nominal_Ml_electron_2017","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2017_ele->Project("Acc_nominal_Mh_electron_2017","DeltaY"," Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");

    treereco_Reco_2016_ele->Project("Acc_nominal_Ml_electron_2016","DeltaY","Mttbar > 750 && Mttbar < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");
    treereco_Reco_2016_ele->Project("Acc_nominal_Mh_electron_2016","DeltaY"," Mttbar > 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1");


    cout << "muon_2018" << endl;
     Float_t Acc_nMl_muon_2018 = Acc_nominal_Ml_muon_2018->GetBinContent(1)/Acc_Full_2018->Integral();
     Float_t Acc_pMl_muon_2018 = Acc_nominal_Ml_muon_2018->GetBinContent(2)/Acc_Full_2018->Integral();
     Float_t Acc_nMh_muon_2018 = Acc_nominal_Mh_muon_2018->GetBinContent(1)/Acc_Full_2018->Integral();
     Float_t Acc_pMh_muon_2018 = Acc_nominal_Mh_muon_2018->GetBinContent(2)/Acc_Full_2018->Integral();

     cout << Acc_nMl_muon_2018 << endl;
     cout << Acc_pMl_muon_2018 << endl;
     cout << Acc_nMh_muon_2018 << endl;
     cout << Acc_pMh_muon_2018 << endl;

    cout << "electron_2018" << endl;
     Float_t Acc_nMl_elec_2018 = Acc_nominal_Ml_electron_2018->GetBinContent(1)/Acc_Full_2018->Integral();
     Float_t Acc_pMl_elec_2018 = Acc_nominal_Ml_electron_2018->GetBinContent(2)/Acc_Full_2018->Integral();
     Float_t Acc_nMh_elec_2018 = Acc_nominal_Mh_electron_2018->GetBinContent(1)/Acc_Full_2018->Integral();
     Float_t Acc_pMh_elec_2018 = Acc_nominal_Mh_electron_2018->GetBinContent(2)/Acc_Full_2018->Integral();

     cout << Acc_nMl_elec_2018 << endl;
     cout << Acc_pMl_elec_2018 << endl;
     cout << Acc_nMh_elec_2018 << endl;
     cout << Acc_pMh_elec_2018 << endl;     

    cout << "muon_2017" << endl;
     Float_t Acc_nMl_muon_2017 = Acc_nominal_Ml_muon_2017->GetBinContent(1)/Acc_Full_2017->Integral();
     Float_t Acc_pMl_muon_2017 = Acc_nominal_Ml_muon_2017->GetBinContent(2)/Acc_Full_2017->Integral();
     Float_t Acc_nMh_muon_2017 = Acc_nominal_Mh_muon_2017->GetBinContent(1)/Acc_Full_2017->Integral();
     Float_t Acc_pMh_muon_2017 = Acc_nominal_Mh_muon_2017->GetBinContent(2)/Acc_Full_2017->Integral();

     cout << Acc_nMl_muon_2017 << endl;
     cout << Acc_pMl_muon_2017 << endl;
     cout << Acc_nMh_muon_2017 << endl;
     cout << Acc_pMh_muon_2017 << endl;

    cout << "electron_2017" << endl;
     Float_t Acc_nMl_elec_2017 = Acc_nominal_Ml_electron_2017->GetBinContent(1)/Acc_Full_2017->Integral();
     Float_t Acc_pMl_elec_2017 = Acc_nominal_Ml_electron_2017->GetBinContent(2)/Acc_Full_2017->Integral();
     Float_t Acc_nMh_elec_2017 = Acc_nominal_Mh_electron_2017->GetBinContent(1)/Acc_Full_2017->Integral();
     Float_t Acc_pMh_elec_2017 = Acc_nominal_Mh_electron_2017->GetBinContent(2)/Acc_Full_2017->Integral();

     cout << Acc_nMl_elec_2017 << endl;
     cout << Acc_pMl_elec_2017 << endl;
     cout << Acc_nMh_elec_2017 << endl;
     cout << Acc_pMh_elec_2017 << endl;

    cout << "muon_2016" << endl;
     Float_t Acc_nMl_muon_2016 = Acc_nominal_Ml_muon_2016->GetBinContent(1)/Acc_Full_2016->Integral();
     Float_t Acc_pMl_muon_2016 = Acc_nominal_Ml_muon_2016->GetBinContent(2)/Acc_Full_2016->Integral();
     Float_t Acc_nMh_muon_2016 = Acc_nominal_Mh_muon_2016->GetBinContent(1)/Acc_Full_2016->Integral();
     Float_t Acc_pMh_muon_2016 = Acc_nominal_Mh_muon_2016->GetBinContent(2)/Acc_Full_2016->Integral();

     cout << Acc_nMl_muon_2016 << endl;
     cout << Acc_pMl_muon_2016 << endl;
     cout << Acc_nMh_muon_2016 << endl;
     cout << Acc_pMh_muon_2016 << endl;

    cout << "electron_2016" << endl;
     Float_t Acc_nMl_elec_2016 = Acc_nominal_Ml_electron_2016->GetBinContent(1)/Acc_Full_2016->Integral();
     Float_t Acc_pMl_elec_2016 = Acc_nominal_Ml_electron_2016->GetBinContent(2)/Acc_Full_2016->Integral();
     Float_t Acc_nMh_elec_2016 = Acc_nominal_Mh_electron_2016->GetBinContent(1)/Acc_Full_2016->Integral();
     Float_t Acc_pMh_elec_2016 = Acc_nominal_Mh_electron_2016->GetBinContent(2)/Acc_Full_2016->Integral();

     cout << Acc_nMl_elec_2016 << endl;
     cout << Acc_pMl_elec_2016 << endl;
     cout << Acc_nMh_elec_2016 << endl;
     cout << Acc_pMh_elec_2016 << endl;


    Float_t N_nMl_2016_muon_750 = 4812;  Float_t N_nMl_2016_muon_750_full = N_nMl_2016_muon_750/Acc_nMl_muon_2016;
    Float_t N_pMl_2016_muon_750 = 4836;  Float_t N_pMl_2016_muon_750_full = N_pMl_2016_muon_750/Acc_pMl_muon_2016;  
    Float_t N_nMh_2016_muon_750 = 1017;  Float_t N_nMh_2016_muon_750_full = N_nMh_2016_muon_750/Acc_nMh_muon_2016;
    Float_t N_pMh_2016_muon_750 = 1012;  Float_t N_pMh_2016_muon_750_full = N_pMh_2016_muon_750/Acc_pMh_muon_2016;
    
    Float_t N_nMl_2016_elec_750 = 1153;  Float_t N_nMl_2016_elec_750_full = N_nMl_2016_elec_750/Acc_nMl_elec_2016;
    Float_t N_pMl_2016_elec_750 = 1139;  Float_t N_pMl_2016_elec_750_full = N_pMl_2016_elec_750/Acc_pMl_elec_2016;
    Float_t N_nMh_2016_elec_750 = 278;  Float_t N_nMh_2016_elec_750_full = N_nMh_2016_elec_750/Acc_nMh_elec_2016;
    Float_t N_pMh_2016_elec_750 = 280;  Float_t N_pMh_2016_elec_750_full = N_pMh_2016_elec_750/Acc_pMh_elec_2016;
                                         
    Float_t N_nMl_2017_muon_750 = 6128;  Float_t N_nMl_2017_muon_750_full = N_nMl_2017_muon_750/Acc_nMl_muon_2017;
    Float_t N_pMl_2017_muon_750 = 6217;  Float_t N_pMl_2017_muon_750_full = N_pMl_2017_muon_750/Acc_pMl_muon_2017;
    Float_t N_nMh_2017_muon_750 = 1417;  Float_t N_nMh_2017_muon_750_full = N_nMh_2017_muon_750/Acc_nMh_muon_2017;
    Float_t N_pMh_2017_muon_750 = 1488;  Float_t N_pMh_2017_muon_750_full = N_pMh_2017_muon_750/Acc_pMh_muon_2017; 

    Float_t N_nMl_2017_elec_750 = 1151;  Float_t N_nMl_2017_elec_750_full = N_nMl_2017_elec_750/Acc_nMl_elec_2017;
    Float_t N_pMl_2017_elec_750 = 1121;  Float_t N_pMl_2017_elec_750_full = N_pMl_2017_elec_750/Acc_pMl_elec_2017;
    Float_t N_nMh_2017_elec_750 = 305;  Float_t N_nMh_2017_elec_750_full = N_nMh_2017_elec_750/Acc_nMh_elec_2017;
    Float_t N_pMh_2017_elec_750 = 314;  Float_t N_pMh_2017_elec_750_full = N_pMh_2017_elec_750/Acc_pMh_elec_2017;

    Float_t N_nMl_2018_muon_750 = 8086;  Float_t N_nMl_2018_muon_750_full = N_nMl_2018_muon_750/Acc_nMl_muon_2018;
    Float_t N_pMl_2018_muon_750 = 8187;  Float_t N_pMl_2018_muon_750_full = N_pMl_2018_muon_750/Acc_pMl_muon_2018;
    Float_t N_nMh_2018_muon_750 = 1945;  Float_t N_nMh_2018_muon_750_full = N_nMh_2018_muon_750/Acc_nMh_muon_2018;
    Float_t N_pMh_2018_muon_750 = 1912;  Float_t N_pMh_2018_muon_750_full = N_pMh_2018_muon_750/Acc_pMh_muon_2018;

    Float_t N_nMl_2018_elec_750 = 1436;  Float_t N_nMl_2018_elec_750_full = N_nMl_2018_elec_750/Acc_nMl_elec_2018;
    Float_t N_pMl_2018_elec_750 = 1462;  Float_t N_pMl_2018_elec_750_full = N_pMl_2018_elec_750/Acc_pMl_elec_2018;
    Float_t N_nMh_2018_elec_750 = 392;  Float_t N_nMh_2018_elec_750_full = N_nMh_2018_elec_750/Acc_nMh_elec_2018; 
    Float_t N_pMh_2018_elec_750 = 410;  Float_t N_pMh_2018_elec_750_full = N_pMh_2018_elec_750/Acc_pMh_elec_2018; 


    Float_t N_nMl_2016_muon_900 = 1925;  Float_t N_nMl_2016_muon_900_full = N_nMl_2016_muon_900/Acc_nMl_muon_2016;
    Float_t N_pMl_2016_muon_900 = 1928;  Float_t N_pMl_2016_muon_900_full = N_pMl_2016_muon_900/Acc_pMl_muon_2016;
    Float_t N_nMh_2016_muon_900 = 4092;  Float_t N_nMh_2016_muon_900_full = N_nMh_2016_muon_900/Acc_nMh_muon_2016;
    Float_t N_pMh_2016_muon_900 = 4176;  Float_t N_pMh_2016_muon_900_full = N_pMh_2016_muon_900/Acc_pMh_muon_2016;

    Float_t N_nMl_2016_elec_900 = 610;  Float_t N_nMl_2016_elec_900_full = N_nMl_2016_elec_900/Acc_nMl_elec_2016;
    Float_t N_pMl_2016_elec_900 = 617;  Float_t N_pMl_2016_elec_900_full = N_pMl_2016_elec_900/Acc_pMl_elec_2016;
    Float_t N_nMh_2016_elec_900 = 1628;  Float_t N_nMh_2016_elec_900_full = N_nMh_2016_elec_900/Acc_nMh_elec_2016;
    Float_t N_pMh_2016_elec_900 = 1672;  Float_t N_pMh_2016_elec_900_full = N_pMh_2016_elec_900/Acc_pMh_elec_2016;

    Float_t N_nMl_2017_muon_900 = 2410;  Float_t N_nMl_2017_muon_900_full = N_nMl_2017_muon_900/Acc_nMl_muon_2017;
    Float_t N_pMl_2017_muon_900 = 2387;  Float_t N_pMl_2017_muon_900_full = N_pMl_2017_muon_900/Acc_pMl_muon_2017;
    Float_t N_nMh_2017_muon_900 = 5224;  Float_t N_nMh_2017_muon_900_full = N_nMh_2017_muon_900/Acc_nMh_muon_2017;
    Float_t N_pMh_2017_muon_900 = 5369;  Float_t N_pMh_2017_muon_900_full = N_pMh_2017_muon_900/Acc_pMh_muon_2017;

    Float_t N_nMl_2017_elec_900 = 574;  Float_t N_nMl_2017_elec_900_full = N_nMl_2017_elec_900/Acc_nMl_elec_2017;
    Float_t N_pMl_2017_elec_900 = 577;  Float_t N_pMl_2017_elec_900_full = N_pMl_2017_elec_900/Acc_pMl_elec_2017;
    Float_t N_nMh_2017_elec_900 = 1557;  Float_t N_nMh_2017_elec_900_full = N_nMh_2017_elec_900/Acc_nMh_elec_2017; 
    Float_t N_pMh_2017_elec_900 = 1651;  Float_t N_pMh_2017_elec_900_full = N_pMh_2017_elec_900/Acc_pMh_elec_2017;

    Float_t N_nMl_2018_muon_900 = 3109;  Float_t N_nMl_2018_muon_900_full = N_nMl_2018_muon_900/Acc_nMl_muon_2018;
    Float_t N_pMl_2018_muon_900 = 3119;  Float_t N_pMl_2018_muon_900_full = N_pMl_2018_muon_900/Acc_pMl_muon_2018;
    Float_t N_nMh_2018_muon_900 = 7055;  Float_t N_nMh_2018_muon_900_full = N_nMh_2018_muon_900/Acc_nMh_muon_2018;
    Float_t N_pMh_2018_muon_900 = 7099;  Float_t N_pMh_2018_muon_900_full = N_pMh_2018_muon_900/Acc_pMh_muon_2018;

    Float_t N_nMl_2018_elec_900 = 750;  Float_t N_nMl_2018_elec_900_full = N_nMl_2018_elec_900/Acc_nMl_elec_2018;
    Float_t N_pMl_2018_elec_900 = 769;  Float_t N_pMl_2018_elec_900_full = N_pMl_2018_elec_900/Acc_pMl_elec_2018;
    Float_t N_nMh_2018_elec_900 = 2095;  Float_t N_nMh_2018_elec_900_full = N_nMh_2018_elec_900/Acc_nMh_elec_2018;
    Float_t N_pMh_2018_elec_900 = 2163;  Float_t N_pMh_2018_elec_900_full = N_pMh_2018_elec_900/Acc_pMh_elec_2018;
 
  /*
   cout << N_nMl_2016_muon_750_full << endl;  
   cout << N_pMl_2016_muon_750_full << endl;
   cout << N_nMh_2016_muon_750_full << endl;
   cout << N_pMh_2016_muon_750_full << endl;

   cout << N_nMl_2016_elec_750_full << endl;
   cout << N_pMl_2016_elec_750_full << endl;
   cout << N_nMh_2016_elec_750_full << endl;
   cout << N_pMh_2016_elec_750_full << endl;

   cout << N_nMl_2017_muon_750_full << endl;
   cout << N_pMl_2017_muon_750_full << endl;
   cout << N_nMh_2017_muon_750_full << endl;
   cout << N_pMh_2017_muon_750_full << endl;

   cout << N_nMl_2017_elec_750_full << endl;
   cout << N_pMl_2017_elec_750_full << endl;
   cout << N_nMh_2017_elec_750_full << endl;
   cout << N_pMh_2017_elec_750_full << endl;

   cout << N_nMl_2018_muon_750_full << endl;
   cout << N_pMl_2018_muon_750_full << endl;
   cout << N_nMh_2018_muon_750_full << endl;
   cout << N_pMh_2018_muon_750_full << endl;

   cout << N_nMl_2018_elec_750_full << endl;
   cout << N_pMl_2018_elec_750_full << endl;
   cout << N_nMh_2018_elec_750_full << endl;
   cout << N_pMh_2018_elec_750_full << endl;


   cout << N_nMl_2016_muon_900_full << endl;
   cout << N_pMl_2016_muon_900_full << endl;
   cout << N_nMh_2016_muon_900_full << endl;
   cout << N_pMh_2016_muon_900_full << endl;

   cout << N_nMl_2016_elec_900_full << endl;
   cout << N_pMl_2016_elec_900_full << endl;
   cout << N_nMh_2016_elec_900_full << endl;
   cout << N_pMh_2016_elec_900_full << endl;

   cout << N_nMl_2017_muon_900_full << endl;
   cout << N_pMl_2017_muon_900_full << endl;
   cout << N_nMh_2017_muon_900_full << endl;
   cout << N_pMh_2017_muon_900_full << endl;

   cout << N_nMl_2017_elec_900_full << endl;
   cout << N_pMl_2017_elec_900_full << endl;
   cout << N_nMh_2017_elec_900_full << endl;
   cout << N_pMh_2017_elec_900_full << endl;

   cout << N_nMl_2018_muon_900_full << endl;
   cout << N_pMl_2018_muon_900_full << endl;
   cout << N_nMh_2018_muon_900_full << endl;
   cout << N_pMh_2018_muon_900_full << endl;

   cout << N_nMl_2018_elec_900_full << endl;
   cout << N_pMl_2018_elec_900_full << endl;
   cout << N_nMh_2018_elec_900_full << endl;
   cout << N_pMh_2018_elec_900_full << endl;

*/

   cout << "--------------------" << endl;
   
   Float_t Ac_750_full = (N_pMl_2016_muon_750_full + N_pMh_2016_muon_750_full + N_pMl_2017_muon_750_full + N_pMh_2017_muon_750_full + N_pMl_2018_muon_750_full + N_pMh_2018_muon_750_full + N_pMl_2016_elec_750_full + N_pMh_2016_elec_750_full + N_pMl_2017_elec_750_full + N_pMh_2017_elec_750_full + N_pMl_2018_elec_750_full + N_pMh_2018_elec_750_full - 
                          N_nMl_2016_muon_750_full - N_nMh_2016_muon_750_full - N_nMl_2017_muon_750_full - N_nMh_2017_muon_750_full - N_nMl_2018_muon_750_full - N_nMh_2018_muon_750_full - N_nMl_2016_elec_750_full - N_nMh_2016_elec_750_full - N_nMl_2017_elec_750_full - N_nMh_2017_elec_750_full - N_nMl_2018_elec_750_full - N_nMh_2018_elec_750_full)/
                          (N_pMl_2016_muon_750_full + N_pMh_2016_muon_750_full + N_pMl_2017_muon_750_full + N_pMh_2017_muon_750_full + N_pMl_2018_muon_750_full + N_pMh_2018_muon_750_full + N_pMl_2016_elec_750_full + N_pMh_2016_elec_750_full + N_pMl_2017_elec_750_full + N_pMh_2017_elec_750_full + N_pMl_2018_elec_750_full + N_pMh_2018_elec_750_full +  
                          N_nMl_2016_muon_750_full + N_nMh_2016_muon_750_full + N_nMl_2017_muon_750_full + N_nMh_2017_muon_750_full + N_nMl_2018_muon_750_full + N_nMh_2018_muon_750_full + N_nMl_2016_elec_750_full + N_nMh_2016_elec_750_full + N_nMl_2017_elec_750_full + N_nMh_2017_elec_750_full + N_nMl_2018_elec_750_full + N_nMh_2018_elec_750_full); 

//  cout << Ac_750_full << endl;
 
   Float_t Ac_900_full = (N_pMl_2016_muon_900_full + N_pMh_2016_muon_900_full + N_pMl_2017_muon_900_full + N_pMh_2017_muon_900_full + N_pMl_2018_muon_900_full + N_pMh_2018_muon_900_full + N_pMl_2016_elec_900_full + N_pMh_2016_elec_900_full + N_pMl_2017_elec_900_full + N_pMh_2017_elec_900_full + N_pMl_2018_elec_900_full - 
                          N_nMl_2016_muon_900_full - N_nMh_2016_muon_900_full - N_nMl_2017_muon_900_full - N_nMh_2017_muon_900_full - N_nMl_2018_muon_900_full - N_nMh_2018_muon_900_full - N_nMl_2016_elec_900_full - N_nMh_2016_elec_900_full - N_nMl_2017_elec_900_full - N_nMh_2017_elec_900_full - N_nMl_2018_elec_900_full)/
                         (N_pMl_2016_muon_900_full + N_pMh_2016_muon_900_full + N_pMl_2017_muon_900_full + N_pMh_2017_muon_900_full + N_pMl_2018_muon_900_full + N_pMh_2018_muon_900_full + N_pMl_2016_elec_900_full + N_pMh_2016_elec_900_full + N_pMl_2017_elec_900_full + N_pMh_2017_elec_900_full + N_pMl_2018_elec_900_full -
                          N_nMl_2016_muon_900_full + N_nMh_2016_muon_900_full + N_nMl_2017_muon_900_full + N_nMh_2017_muon_900_full + N_nMl_2018_muon_900_full + N_nMh_2018_muon_900_full + N_nMl_2016_elec_900_full + N_nMh_2016_elec_900_full + N_nMl_2017_elec_900_full + N_nMh_2017_elec_900_full + N_nMl_2018_elec_900_full );



//  cout << Ac_900_full << endl;


  Float_t a = N_pMl_2016_muon_750_full + N_pMl_2017_muon_750_full + N_pMl_2018_muon_750_full + N_pMl_2016_elec_750_full + N_pMl_2017_elec_750_full + N_pMl_2018_elec_750_full + N_pMh_2016_muon_750_full + N_pMh_2017_muon_750_full + N_pMh_2018_muon_750_full + N_pMh_2016_elec_750_full + N_pMh_2017_elec_750_full + N_pMh_2018_elec_750_full;
  Float_t b = N_nMl_2016_muon_750_full + N_nMl_2017_muon_750_full + N_nMl_2018_muon_750_full + N_nMl_2016_elec_750_full + N_nMl_2017_elec_750_full + N_nMl_2018_elec_750_full + N_nMh_2016_muon_750_full + N_nMh_2017_muon_750_full + N_nMh_2018_muon_750_full + N_nMh_2016_elec_750_full + N_nMh_2017_elec_750_full + N_nMh_2018_elec_750_full; 

  cout << (a-b)/(a+b) << endl;

  cout << "N_nMl_750: " << N_nMl_2016_muon_750_full + N_nMl_2017_muon_750_full + N_nMl_2018_muon_750_full + N_nMl_2016_elec_750_full + N_nMl_2017_elec_750_full + N_nMl_2018_elec_750_full << endl;
  cout << "N_nMh_750: " << N_nMh_2016_muon_750_full + N_nMh_2017_muon_750_full + N_nMh_2018_muon_750_full + N_nMh_2016_elec_750_full + N_nMh_2017_elec_750_full + N_nMh_2018_elec_750_full << endl;
  cout << "N_pMl_750: " << N_pMl_2016_muon_750_full + N_pMl_2017_muon_750_full + N_pMl_2018_muon_750_full + N_pMl_2016_elec_750_full + N_pMl_2017_elec_750_full + N_pMl_2018_elec_750_full << endl;
  cout << "N_pMh_750: " << N_pMh_2016_muon_750_full + N_pMh_2017_muon_750_full + N_pMh_2018_muon_750_full + N_pMh_2016_elec_750_full + N_pMh_2017_elec_750_full + N_pMh_2018_elec_750_full << endl;
  
  cout << "N_nMl_900: " << N_nMl_2016_muon_900_full + N_nMl_2017_muon_900_full + N_nMl_2018_muon_900_full + N_nMl_2016_elec_900_full + N_nMl_2017_elec_900_full + N_nMl_2018_elec_900_full << endl;
  cout << "N_nMh_900: " << N_nMh_2016_muon_900_full + N_nMh_2017_muon_900_full + N_nMh_2018_muon_900_full + N_nMh_2016_elec_900_full + N_nMh_2017_elec_900_full << endl;
  cout << "N_pMl_900: " << N_pMl_2016_muon_900_full + N_pMl_2017_muon_900_full + N_pMl_2018_muon_900_full + N_pMl_2016_elec_900_full + N_pMl_2017_elec_900_full + N_pMl_2018_elec_900_full << endl;
  cout << "N_pMh_900: " << N_pMh_2016_muon_900_full + N_pMh_2017_muon_900_full + N_pMh_2018_muon_900_full + N_pMh_2016_elec_900_full + N_pMh_2017_elec_900_full << endl;

  Float_t c = N_pMl_2016_muon_900_full + N_pMl_2017_muon_900_full + N_pMl_2018_muon_900_full + N_pMl_2016_elec_900_full + N_pMl_2017_elec_900_full + N_pMl_2018_elec_900_full + N_pMh_2016_muon_900_full + N_pMh_2017_muon_900_full + N_pMh_2018_muon_900_full + N_pMh_2016_elec_900_full + N_pMh_2017_elec_900_full;
  Float_t d = N_nMl_2016_muon_900_full + N_nMl_2017_muon_900_full + N_nMl_2018_muon_900_full + N_nMl_2016_elec_900_full + N_nMl_2017_elec_900_full + N_nMl_2018_elec_900_full + N_nMh_2016_muon_900_full + N_nMh_2017_muon_900_full + N_nMh_2018_muon_900_full + N_nMh_2016_elec_900_full + N_nMh_2017_elec_900_full;
 
  cout << (c-d)/(c+d) << endl;


  Float_t A = a+c;
  Float_t B = b+d;

  cout << (A - B)/(A + B); 


}

 
