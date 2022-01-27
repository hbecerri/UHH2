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

    TChain *chreco_ttbar_antes = new TChain("AnalysisTree","");
    chreco_ttbar_antes->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_24.root/AnalysisTree");
    chreco_ttbar_antes->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2017/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_24.root/AnalysisTree");
    chreco_ttbar_antes->Add("/nfs/dust/cms/user/hugobg/analysis/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_24.root/AnalysisTree");
    TTree *treereco_ttbar_antes = (TTree*) chreco_ttbar_antes;

    TChain *chreco_ttbar_despues = new TChain("AnalysisTree","");
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/workdir_Zprime_Analysis_2018_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");  
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/muon/workdir_Zprime_Analysis_2016_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree"); 
    chreco_ttbar_despues->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/electron/workdir_Zprime_Analysis_2016_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_ttbar_despues = (TTree*) chreco_ttbar_despues;

//array for variable 

    Float_t bins_gen[] = {-10.,0.,10.}; 

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Acc_antes_nominal = new TH1F("Acc_antes_nominal","",binnum_gen,bins_gen);
    TH1F *Acc_antes_nominal_750_900 = new TH1F("Acc_antes_nominal_750_900","",binnum_gen,bins_gen);
    TH1F *Acc_antes_nominal_900 = new TH1F("Acc_antes_nominal_900","",binnum_gen,bins_gen);

    TH1F *Acc_despues_nominal_900_12 = new TH1F("Acc_despues_nominal_900_12","",binnum_gen,bins_gen);
    TH1F *Acc_despues_nominal_900_34 = new TH1F("Acc_despues_nominal_900_34","",binnum_gen,bins_gen);

    TH1F *Acc_despues_nominal_750_900_12 = new TH1F("Acc_despues_nominal_750_900_12","",binnum_gen,bins_gen);
    TH1F *Acc_despues_nominal_750_900_34 = new TH1F("Acc_despues_nominal_750_900_34","",binnum_gen,bins_gen);

    TH1F *Acc_despues_nominal_750_12 = new TH1F("Acc_despues_nominal_750_12","",binnum_gen,bins_gen);
    TH1F *Acc_despues_nominal_750_34 = new TH1F("Acc_despues_nominal_750_34","",binnum_gen,bins_gen);

    string Mttbar_gen_energia = "TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2)";
    string Mttbar_gen_p1 = "TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2)";
    string Mttbar_gen_p2 = "TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2)";
    string Mttbar_gen_p3 = "TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2)";

    string Mttbar_gen = Form("TMath::Sqrt(%s - %s - %s - %s)",Mttbar_gen_energia.c_str(),Mttbar_gen_p1.c_str(),Mttbar_gen_p2.c_str(),Mttbar_gen_p3.c_str());

    string var_gen = "";

    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    string is_muon = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 13) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 13)";
    
    string is_electron = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 11) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 11)";

 
    treereco_ttbar_antes->Project("Acc_antes_nominal",Form("%s",var_gen.c_str()),Form("(%s > 750)",Mttbar_gen.c_str()));
    treereco_ttbar_antes->Project("Acc_antes_nominal_750_900",Form("%s",var_gen.c_str()),Form("(%s > 750 && %s < 900)",Mttbar_gen.c_str(),Mttbar_gen.c_str()));
    treereco_ttbar_antes->Project("Acc_antes_nominal_900",Form("%s",var_gen.c_str()),Form("(%s > 900)",Mttbar_gen.c_str()));

//    treereco_ttbar_despues->Project("Acc_despues_nominal_750_12",Form("%s",var_gen.c_str()),Form("Mttbar > 750 && %s >750 && %s < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));
//    treereco_ttbar_despues->Project("Acc_despues_nominal_750_34",Form("%s",var_gen.c_str()),Form("Mttbar > 750 && %s >900 && %s < 90000 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));

    treereco_ttbar_despues->Project("Acc_despues_nominal_750_900_12",Form("%s",var_gen.c_str()),Form("Mttbar > 750 && Mttbar < 900 && %s >750 && %s < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));
    treereco_ttbar_despues->Project("Acc_despues_nominal_750_900_34",Form("%s",var_gen.c_str()),Form("Mttbar > 750 && Mttbar < 900 && %s >900 && %s < 90000 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));

    treereco_ttbar_despues->Project("Acc_despues_nominal_900_12",Form("%s",var_gen.c_str()),Form("Mttbar > 900 && %s >750 && %s < 900 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));
    treereco_ttbar_despues->Project("Acc_despues_nominal_900_34",Form("%s",var_gen.c_str()),Form("Mttbar > 900 && %s >900 && %s < 90000 && rec_chi2 < 30 && ttagN <=1 && wtagN<=1 && btagN>=1",Mttbar_gen.c_str(),Mttbar_gen.c_str()));


    cout << "Ac_750_900" << endl;
    cout << "1: " << Acc_despues_nominal_750_900_12->GetBinContent(1)/Acc_antes_nominal_750_900->GetBinContent(1) << endl;
    cout << "2: " << Acc_despues_nominal_750_900_12->GetBinContent(2)/Acc_antes_nominal_750_900->GetBinContent(2) << endl;
    cout << "3: " << Acc_despues_nominal_750_900_34->GetBinContent(1)/Acc_antes_nominal_900->GetBinContent(1) << endl;
    cout << "4: " << Acc_despues_nominal_750_900_34->GetBinContent(2)/Acc_antes_nominal_900->GetBinContent(2) << endl;
 
    cout << "Ac_900" << endl;
    cout << "1: " << Acc_despues_nominal_900_12->GetBinContent(1)/Acc_antes_nominal_750_900->GetBinContent(1) << endl;
    cout << "2: " << Acc_despues_nominal_900_12->GetBinContent(2)/Acc_antes_nominal_750_900->GetBinContent(2) << endl;
    cout << "3: " << Acc_despues_nominal_900_34->GetBinContent(1)/Acc_antes_nominal_900->GetBinContent(1) << endl;
    cout << "4: " << Acc_despues_nominal_900_34->GetBinContent(2)/Acc_antes_nominal_900->GetBinContent(2) << endl;



}

 
