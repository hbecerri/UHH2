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

void all_unfolding_data(string year = "")
{
    gStyle->SetOptStat(0);
    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTTo*.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TH1F *Top_pt_leading_nominal_boosted = new TH1F("Top_pt_leading_nominal_boosted","",20,0,1800);
    TH1F *Top_pt_leading_up_boosted = new TH1F("Top_pt_leading_up_boosted","",20,0,1800);
    TH1F *Top_pt_leading_down_boosted = new TH1F("Top_pt_leading_down_boosted","",20,0,1800);

    TH1F *Top_pt_leading_nominal_semiresolved = new TH1F("Top_pt_leading_nominal_semiresolved","",20,0,1800);
    TH1F *Top_pt_leading_up_semiresolved = new TH1F("Top_pt_leading_up_semiresolved","",20,0,1800);
    TH1F *Top_pt_leading_down_semiresolved = new TH1F("Top_pt_leading_down_semiresolved","",20,0,1800);

    TH1F *Top_pt_leading_nominal_resolved = new TH1F("Top_pt_leading_nominal_resolved","",20,0,1800);
    TH1F *Top_pt_leading_up_resolved = new TH1F("Top_pt_leading_up_resolved","",20,0,1800);
    TH1F *Top_pt_leading_down_resolved = new TH1F("Top_pt_leading_down_resolved","",20,0,1800); 
 
    TH1F *Top_pt_subleading = new TH1F("Top_pt_subleading","",20,0,1800);
 
    treereco_ttbar->Project("Top_pt_leading_nominal_boosted","tlead_pT","(ttagN == 1 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_up_boosted","tlead_pT","(ttagN == 1 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_down_boosted","tlead_pT","(ttagN == 1 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");

    treereco_ttbar->Project("Top_pt_leading_nominal_semiresolved","tlead_pT","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_up_semiresolved","tlead_pT","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_down_semiresolved","tlead_pT","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");

    treereco_ttbar->Project("Top_pt_leading_nominal_resolved","tlead_pT","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_up_resolved","tlead_pT","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_down_resolved","tlead_pT","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");

    TCanvas* cc = new TCanvas("cc","",800,1200);
    cc->Divide(1,3);

    cc->cd(1);
    Top_pt_leading_up_boosted->SetLineColor(kRed);
    Top_pt_leading_down_boosted->SetLineColor(kBlue);
    Top_pt_leading_up_boosted->Draw("");
    Top_pt_leading_nominal_boosted->Draw("same");
    Top_pt_leading_down_boosted->Draw("same");    

    cc->cd(2);
    Top_pt_leading_up_semiresolved->SetLineColor(kRed);
    Top_pt_leading_down_semiresolved->SetLineColor(kBlue);
    Top_pt_leading_up_semiresolved->Draw("");
    Top_pt_leading_nominal_semiresolved->Draw("same");
    Top_pt_leading_down_semiresolved->Draw("same");

    cc->cd(3);
    Top_pt_leading_up_resolved->SetLineColor(kRed);
    Top_pt_leading_down_resolved->SetLineColor(kBlue);
    Top_pt_leading_up_resolved->Draw();
    Top_pt_leading_nominal_resolved->Draw("same");
    Top_pt_leading_down_resolved->Draw("same");

    cc->Print("Top_pt_rew.pdf");

}


