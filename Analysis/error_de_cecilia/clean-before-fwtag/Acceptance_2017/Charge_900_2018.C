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

void Charge_900_2018(string var_weight = "1", int aa = 1)
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar_antes_muon = new TChain("AnalysisTree","");
    chreco_ttbar_antes_muon->Add("/pnfs/desy.de/cms/tier2/store/user/akaravdi/RunII_102X_v1_TEST/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190327_085021/0001/*.root/AnalysisTree");
    TTree *treereco_ttbar_antes_muon = (TTree*) chreco_ttbar_antes_muon;


//array for variable 

    Float_t bins_gen[] = {-10.,0.,10.}; 

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Acc_antes_muon_nominal = new TH1F("Acc_antes_muon_nominal","",binnum_gen,bins_gen);
    TH1F *Acc_antes_electron_nominal = new TH1F("Acc_antes_electron_nominal","",binnum_gen,bins_gen);

    TH1F *Acc_antes_muon_nominal_750 = new TH1F("Acc_antes_muon_nominal_750","",binnum_gen,bins_gen);
    TH1F *Acc_antes_electron_nominal_750 = new TH1F("Acc_antes_electron_nominal_750","",binnum_gen,bins_gen);

    TH1F *Acc_antes_muon_nominal_900 = new TH1F("Acc_antes_muon_nominal_900","",binnum_gen,bins_gen);
    TH1F *Acc_antes_electron_nominal_900 = new TH1F("Acc_antes_electron_nominal_900","",binnum_gen,bins_gen);

    string Mttbar_gen_energia = "TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2)";
    string Mttbar_gen_p1 = "TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2)";
    string Mttbar_gen_p2 = "TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2)";
    string Mttbar_gen_p3 = "TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2)";

    string Mttbar_gen = Form("TMath::Sqrt(%s - %s - %s - %s)",Mttbar_gen_energia.c_str(),Mttbar_gen_p1.c_str(),Mttbar_gen_p2.c_str(),Mttbar_gen_p3.c_str());
    string var_gen = "";

    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    string is_muon = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 13) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 13)";
    
    string is_electron = "(TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]]) == 11) || (TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]]) == 11)";


    treereco_ttbar_antes_muon->Project("Acc_antes_muon_nominal",Form("%s",var_gen.c_str()),Form("(%s >900)",Mttbar_gen.c_str()));

    cout << (Acc_antes_muon_nominal->GetBinContent(2) - Acc_antes_muon_nominal->GetBinContent(1))/(Acc_antes_muon_nominal->GetBinContent(2) + Acc_antes_muon_nominal->GetBinContent(1));  
 

}

 
