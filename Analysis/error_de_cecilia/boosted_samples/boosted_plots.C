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
#include "TUnfoldDensity.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void boosted_plots(string var_name = "", string var_gen = "", string region = "", string year = "2017")
{

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    TChain *chreco_ttbar_semi_boosted = new TChain("AnalysisTree","");
    chreco_ttbar_semi_boosted->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_boosted_ttbar/*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_boosted = (TTree*) chreco_ttbar_semi_boosted;

//--------Unfold----------??


    Float_t mistag_nominal = 0.9;
    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900)*%f",mistag_nominal);

    TH1F *Ttbar_lepton_pt = new TH1F("Ttbar_lepton_pt","",10,50,400);
    TH1F *Ttbar_jet_pt = new TH1F("Ttbar_jet_pt","",10,50,400);
    TH1F *Ttbar_njets = new TH1F("Ttbar_njets","",10,2,11);

    TH1F *Ttbar_lepton_pt_boosted = new TH1F("Ttbar_lepton_pt_boosted","",10,50,400);
    TH1F *Ttbar_jet_pt_boosted = new TH1F("Ttbar_jet_pt_boosted","",10,50,400);
    TH1F *Ttbar_njets_boosted = new TH1F("Ttbar_njets_boosted","",10,2,11);

    treereco_ttbar_semi->Project("Ttbar_lepton_pt","lep1_pt",Form("%s",selcuts_boosted_central.c_str())); 
    treereco_ttbar_semi->Project("Ttbar_jet_pt","Ak8_j1_pt",Form("%s",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Ttbar_njets","N_Ak4",Form("%s",selcuts_boosted_central.c_str()));

    treereco_ttbar_semi_boosted->Project("Ttbar_lepton_pt_boosted","lep1_pt",Form("%s",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_boosted->Project("Ttbar_jet_pt_boosted","Ak8_j1_pt",Form("%s",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_boosted->Project("Ttbar_njets_boosted","N_Ak4",Form("%s",selcuts_boosted_central.c_str()));


   
   THStack *hs = new THStack("hs","");
   Ttbar_lepton_pt->SetFillColor(kRed);
   hs->Add(Ttbar_lepton_pt);
   Ttbar_lepton_pt_boosted->SetFillColor(kBlue);
   hs->Add(Ttbar_lepton_pt_boosted);
   TCanvas *cs = new TCanvas("cs","cs",10,10,700,900);
   cs->Divide(1,1);
   cs->cd(1); hs->Draw("PLC h"); 
   cs->Print("stack.pdf");

   THStack *hs2 = new THStack("hs2","");
   Ttbar_jet_pt->SetFillColor(kRed);
   hs2->Add(Ttbar_jet_pt);
   Ttbar_jet_pt_boosted->SetFillColor(kBlue);
   hs2->Add(Ttbar_jet_pt_boosted);
   TCanvas *cs2 = new TCanvas("cs2","cs2",10,10,700,900);
   cs2->Divide(1,1);
   cs2->cd(1); hs2->Draw("PLC h");
   cs2->Print("stack2.pdf");


   THStack *hs3 = new THStack("hs3","");
   Ttbar_njets->SetFillColor(kRed);
   hs3->Add(Ttbar_njets);
   Ttbar_njets_boosted->SetFillColor(kBlue);
   hs3->Add(Ttbar_njets_boosted);
   TCanvas *cs3 = new TCanvas("cs3","cs3",10,10,700,900);
   cs3->Divide(1,1);
   cs3->cd(1); hs3->Draw("PLC h");
   cs3->Print("stack3.pdf");


}


