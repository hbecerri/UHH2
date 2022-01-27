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

void Acceptance(string var_weight = "wgtMC__PDF[1]", int aa = 1)
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar_antes_muon = new TChain("AnalysisTree","");
    chreco_ttbar_antes_muon->Add("/nfs/dust/cms/group/zprime-uhh/Presel_2016/Preselection_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_24.root/AnalysisTree");
    TTree *treereco_ttbar_antes_muon = (TTree*) chreco_ttbar_antes_muon;

    TChain *chreco_ttbar_despues_muon = new TChain("AnalysisTree","");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/muon/workdir_Zprime_Analysis_2016_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_ttbar_despues_muon = (TTree*) chreco_ttbar_despues_muon;
    
    TChain *chreco_ttbar_despues_electron = new TChain("AnalysisTree","");
    chreco_ttbar_despues_electron->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/electron/workdir_Zprime_Analysis_2016_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_ttbar_despues_electron = (TTree*) chreco_ttbar_despues_electron;

//array for variable 

    Float_t bins_gen[] = {-2.,0.,2.}; 

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Acc_antes_muon = new TH1F("Acc_antes_muon","",binnum_gen,bins_gen);
    TH1F *Acc_antes_electron = new TH1F("Acc_antes_electron","",binnum_gen,bins_gen);
    TH1F *Acc_antes_muon_nominal = new TH1F("Acc_antes_muon_nominal","",binnum_gen,bins_gen);
    TH1F *Acc_antes_electron_nominal = new TH1F("Acc_antes_electron_nominal","",binnum_gen,bins_gen);


    TH1F *Acc_despues_muon = new TH1F("Acc_despues_muon","",binnum_gen,bins_gen);
    TH1F *Acc_despues_electron = new TH1F("Acc_despues_electron","",binnum_gen,bins_gen);
    TH1F *Acc_despues_muon_nominal = new TH1F("Acc_despues_muon_nominal","",binnum_gen,bins_gen);
    TH1F *Acc_despues_electron_nominal = new TH1F("Acc_despues_electron_nominal","",binnum_gen,bins_gen);


    string var_gen = "";

    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    string is_muon = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 13) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 13)";
    
    string is_electron = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 11) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 11)";


    treereco_ttbar_antes_muon->Project("Acc_antes_muon_nominal",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(%s)",is_muon.c_str()));
    treereco_ttbar_antes_muon->Project("Acc_antes_electron_nominal",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(%s)",is_electron.c_str()));

    treereco_ttbar_antes_muon->Project("Acc_antes_muon",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(%s)*%s",is_muon.c_str(),var_weight.c_str())); 
    treereco_ttbar_antes_muon->Project("Acc_antes_electron",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(%s)*%s",is_electron.c_str(),var_weight.c_str()));




    treereco_ttbar_despues_muon->Project("Acc_despues_muon",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900)*%s",var_weight.c_str())); 
    treereco_ttbar_despues_electron->Project("Acc_despues_electron",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900)*%s",var_weight.c_str())); 


    treereco_ttbar_despues_muon->Project("Acc_despues_muon_nominal",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900");
    treereco_ttbar_despues_electron->Project("Acc_despues_electron_nominal",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900");


    Float_t Acceptance_muon_ttbar1_nominal = Acc_despues_muon_nominal->GetBinContent(1)/Acc_antes_muon_nominal->GetBinContent(1);
    Float_t Acceptance_muon_ttbar2_nominal = Acc_despues_muon_nominal->GetBinContent(2)/Acc_antes_muon_nominal->GetBinContent(2);
    Float_t Acceptance_electron_ttbar1_nominal = Acc_despues_electron_nominal->GetBinContent(1)/Acc_antes_electron_nominal->GetBinContent(1);
    Float_t Acceptance_electron_ttbar2_nominal = Acc_despues_electron_nominal->GetBinContent(2)/Acc_antes_electron_nominal->GetBinContent(2);

    Float_t Acceptance_muon_ttbar1 = Acc_despues_muon->GetBinContent(1)/Acc_antes_muon->GetBinContent(1);
    Float_t Acceptance_muon_ttbar2 = Acc_despues_muon->GetBinContent(2)/Acc_antes_muon->GetBinContent(2);
    Float_t Acceptance_electron_ttbar1 = Acc_despues_electron->GetBinContent(1)/Acc_antes_electron->GetBinContent(1);
    Float_t Acceptance_electron_ttbar2 = Acc_despues_electron->GetBinContent(2)/Acc_antes_electron->GetBinContent(2);
 
    Double_t variancia_muon_ttbar1 = Acceptance_muon_ttbar1_nominal - Acceptance_muon_ttbar1; 
    Double_t variancia_muon_ttbar2 = Acceptance_muon_ttbar2_nominal - Acceptance_muon_ttbar2;
    Double_t variancia_electron_ttbar1 = Acceptance_electron_ttbar1_nominal - Acceptance_electron_ttbar1;
    Double_t variancia_electron_ttbar2 = Acceptance_electron_ttbar2_nominal - Acceptance_electron_ttbar2;

    ofstream electron1;
    electron1.open ("electron_ttbar1.txt", ios::app);
    electron1 << aa;
    electron1 << "\t";
    electron1 <<  variancia_electron_ttbar1;
    electron1 << "\n";


    ofstream electron2;
    electron2.open ("electron_ttbar2.txt", ios::app);
    electron2 << aa;
    electron2 << "\t";
    electron2 <<  variancia_electron_ttbar2;
    electron2 << "\n";

    ofstream muon1;
    muon1.open ("muon_ttbar1.txt", ios::app);
    muon1 << aa;
    muon1 << "\t";
    muon1 <<  variancia_muon_ttbar1;
    muon1 << "\n";

    ofstream muon2;
    muon2.open ("muon_ttbar2.txt", ios::app);
    muon2 << aa;
    muon2 << "\t";
    muon2 <<  variancia_muon_ttbar2;
    muon2 << "\n";

    cout << Acceptance_muon_ttbar1 << endl;// = Acc_despues_muon->GetBinContent(1)/Acc_antes_muon->GetBinContent(1);
    cout << Acceptance_muon_ttbar2 << endl; //= Acc_despues_muon->GetBinContent(2)/Acc_antes_muon->GetBinContent(2);
    cout << Acceptance_electron_ttbar1 << endl; //= Acc_despues_electron->GetBinContent(1)/Acc_antes_electron->GetBinContent(1);
    cout << Acceptance_electron_ttbar2 << endl; 

}

 
