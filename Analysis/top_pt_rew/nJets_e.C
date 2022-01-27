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

void nJets_e(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

    gStyle->SetOptStat(0);
    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/uhh2.AnalysisModuleRunner.DATA.*.root/AnalysisTree");
    TTree *treereco_data = (TTree*) chreco_data;

    TH1F *Top_pt_leading_nominal_boosted = new TH1F("Top_pt_leading_nominal_boosted","",20,0,1800);
    TH1F *Top_pt_leading_up_boosted = new TH1F("Top_pt_leading_up_boosted","",20,0,1800);
    TH1F *Top_pt_leading_down_boosted = new TH1F("Top_pt_leading_down_boosted","",20,0,1800);
    TH1F *Top_pt_leading_limit_boosted = new TH1F("Top_pt_leading_limit_boosted","",20,0,1800);
    TH1F *data_pt_leading_nominal_boosted = new TH1F("data_pt_leading_nominal_boosted","",20,0,1800);
  
    TH1F *Top_pt_leading_nominal_semiresolved = new TH1F("Top_pt_leading_nominal_semiresolved","",20,0,1800);
    TH1F *Top_pt_leading_up_semiresolved = new TH1F("Top_pt_leading_up_semiresolved","",20,0,1800);
    TH1F *Top_pt_leading_down_semiresolved = new TH1F("Top_pt_leading_down_semiresolved","",20,0,1800);

    TH1F *Top_pt_leading_nominal_resolved = new TH1F("Top_pt_leading_nominal_resolved","",20,0,1800);
    TH1F *Top_pt_leading_up_resolved = new TH1F("Top_pt_leading_up_resolved","",20,0,1800);
    TH1F *Top_pt_leading_down_resolved = new TH1F("Top_pt_leading_down_resolved","",20,0,1800);

    TH1F *data_pt_leading_nominal_resolved = new TH1F("data_pt_leading_nominal_resolved","",20,0,1800);
    TH1F *data_pt_leading_up_resolved = new TH1F("data_pt_leading_up_resolved","",20,0,1800);
    TH1F *data_pt_leading_down_resolved = new TH1F("data_pt_leading_down_resolved","",20,0,1800);

    treereco_data->Project("data_pt_leading_nominal_boosted","pT_lep","(ttagN>=0 && wtagN >=0 && btagN >=1 && rec_chi2 < 30 && Mttbar>900)");
    treereco_ttbar->Project("Top_pt_leading_nominal_boosted","pT_lep","(ttagN>=0 && wtagN >=0 && btagN >=1 && rec_chi2 < 30 && Mttbar>900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_nolimit*weight_btagdisc_central");
    treereco_ttbar->Project("Top_pt_leading_up_boosted","pT_lep","(ttagN>=0 && wtagN >=0 && btagN >=1 && rec_chi2 < 30 && Mttbar>900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central");
    treereco_ttbar->Project("Top_pt_leading_limit_boosted","pT_lep","(ttagN>=0 && wtagN >=0 && btagN >=1 && rec_chi2 < 30 && Mttbar>900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*weight_pt_rew");
/*    treereco_ttbar->Project("Top_pt_leading_down_boosted","pT_lep","(ttagN == 1 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_nominal_semiresolved","pT_lep","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_up_semiresolved","pT_lep","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_down_semiresolved","pT_lep","(ttagN == 0 && wtagN == 1 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_nominal_resolved","pT_lep","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_up_resolved","pT_lep","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal");
    treereco_ttbar->Project("Top_pt_leading_down_resolved","pT_lep","(ttagN == 0 && wtagN == 0 && btagN >=1 && rec_chi2 < 30 && Mttbar > 900)*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal");
*/
/*
   TCanvas *c = new TCanvas("c", "canvas", 800, 800);
   // Upper plot will be in pad1
   TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0); // Upper and lower plot are joined
   pad1->SetGridx();         // Vertical grid
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
   Top_pt_leading_nominal_boosted->SetStats(0);          // No statistics on upper plot
   Top_pt_leading_up_boosted->Draw();
   Top_pt_leading_nominal_boosted->Draw("same");               // Draw h1
   Top_pt_leading_up_boosted->Draw("same");         // Draw h2 on top of h1
   Top_pt_leading_down_boosted->Draw("same");   // Draw h3 on top of h1 
 
   TAxis *axis = Top_pt_leading_nominal_boosted->GetYaxis();
   axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);

   TLegend leg(.6,.7,.8,.9,"");
   leg.AddEntry(Top_pt_leading_nominal_boosted, "nominal","lp");
   leg.AddEntry(Top_pt_leading_up_boosted,"up","lp");
   leg.AddEntry(Top_pt_leading_down_boosted,"down","lp");
   leg.SetFillStyle(0);
   leg.SetBorderSize(0);
   leg.SetTextSize(0.04);
   leg.SetTextFont(42);
   leg.Draw();   
 
   // lower plot will be in pad
   c->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.2);
   pad2->SetGridx(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad
 
   // Define the ratio plot
   TH1F *h3 = (TH1F*)Top_pt_leading_nominal_boosted->Clone("h3");
   TH1F *h5 = (TH1F*)Top_pt_leading_nominal_boosted->Clone("h5");
   h3->SetLineColor(kRed);
   h5->SetLineColor(kBlack);
   h3->SetMinimum(0.7);  // Define Y ..
   h3->SetMaximum(1.3); // .. range
   h3->Sumw2();
   h3->SetStats(0);      // No statistics on lower plot
   h3->Divide(Top_pt_leading_up_boosted);
   h5->Divide(Top_pt_leading_down_boosted);
   h3->SetMarkerStyle(21);
   h5->SetMarkerStyle(21);
   h3->SetMarkerColor(2);
   h5->SetMarkerColor(1);
   h3->Draw("ep");       // Draw the ratio plot
   h5->Draw("ep same");
 
   // h1 settings
   Top_pt_leading_nominal_boosted->SetLineColor(kBlue+1);
   Top_pt_leading_nominal_boosted->SetLineWidth(2);
 
   // Y axis h1 plot settings
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleSize(20);
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleFont(43);
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleOffset(1.55);
 
   // h2 settings
   Top_pt_leading_up_boosted->SetLineColor(kRed);
   Top_pt_leading_up_boosted->SetLineWidth(2);

   Top_pt_leading_down_boosted->SetLineColor(kBlack);
   Top_pt_leading_down_boosted->SetLineWidth(2);   
 
   // Ratio plot (h3) settings
   h3->SetTitle(""); // Remove the ratio title
 
   // Y axis ratio plot settings
   h3->GetYaxis()->SetTitle("ratio");
   h3->GetYaxis()->SetRangeUser(0.5,1.5);
   h3->GetYaxis()->SetNdivisions(505);
   h3->GetYaxis()->SetTitleSize(20);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.55);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(15);
 
   // X axis ratio plot settings
   h3->GetXaxis()->SetTitle("Top_pT [GeV]");
   h3->GetXaxis()->SetTitleSize(20);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(1);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(15);

   c->Print("c.pdf");
*/

   for(int i = 1; i<=20;i++){
      Top_pt_leading_nominal_boosted->SetBinError(i,Top_pt_leading_nominal_boosted->GetBinContent(i) - Top_pt_leading_up_boosted->GetBinContent(i));
   }
  

   TCanvas *c = new TCanvas("c", "canvas", 800, 800);
   c->SetLogy();
   // Upper plot will be in pad1
   TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0); // Upper and lower plot are joined
   pad1->SetGridx();         // Vertical grid
//   pad1->SetLogy();
   pad1->Draw();             // Draw the upper pad: pad1

   pad1->cd();               // pad1 becomes the current pad
   Top_pt_leading_up_boosted->SetLineColor(kBlack);
   Top_pt_leading_up_boosted->SetLineWidth(2);
Top_pt_leading_limit_boosted->SetLineColor(kGreen);
   Top_pt_leading_nominal_boosted->SetStats(0);          // No statistics on upper plot
   data_pt_leading_nominal_boosted->Draw("e");
//   Top_pt_leading_up_boosted->Draw("same");
   Top_pt_leading_nominal_boosted->Draw("same e");               // Draw h1
//   Top_pt_leading_limit_boosted->Draw("same");
   data_pt_leading_nominal_boosted->Draw("same");         // Draw h2 on top of h1



   TAxis *axis = Top_pt_leading_nominal_boosted->GetYaxis();
   axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);

   TLegend leg(.6,.7,.8,.9,"");
   leg.AddEntry(Top_pt_leading_nominal_boosted, "Top_pt nominal (no limit)","lp");
//   leg.AddEntry(Top_pt_leading_nominal_boosted, "Top_pt nominal (limit 500GeV)","lp");
   leg.AddEntry(data_pt_leading_nominal_boosted,"data","lp");
//   leg.AddEntry(Top_pt_leading_up_boosted,"Top_pt up","lp");

   leg.SetFillStyle(0);
   leg.SetBorderSize(0);
   leg.SetTextSize(0.04);
   leg.SetTextFont(42);
   leg.Draw();

   // lower plot will be in pad
   c->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.2);
   pad2->SetGridx(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad

   // Define the ratio plot
   TH1F *h3 = (TH1F*)data_pt_leading_nominal_boosted->Clone("h3");
   TH1F *h5 = (TH1F*)data_pt_leading_nominal_boosted->Clone("h5");
   TH1F *h7 = (TH1F*)data_pt_leading_nominal_boosted->Clone("h7");
   h3->SetLineColor(kBlack);
   h5->SetLineColor(kBlue);
   h3->SetMinimum(0.7);  // Define Y ..
   h3->SetMaximum(1.3); // .. range
   h3->Sumw2();
   h3->SetStats(0);      // No statistics on lower plot
   h3->Divide(Top_pt_leading_up_boosted);
   h5->Divide(Top_pt_leading_nominal_boosted);
   h7->Divide(Top_pt_leading_limit_boosted);
   h3->SetMarkerStyle(21);
   h5->SetMarkerStyle(21);
   h7->SetMarkerStyle(21);
   h3->SetMarkerColor(kBlack);
   h5->SetMarkerColor(kBlue);
   h7->SetMarkerColor(kGreen);
//   h3->Draw("ep");       // Draw the ratio plot
   h5->Draw("ep same");
//   h7->Draw("ep same");
   // h1 settings
   Top_pt_leading_nominal_boosted->SetLineColor(kBlue+1);
   Top_pt_leading_nominal_boosted->SetLineWidth(2);

   // Y axis h1 plot settings
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleSize(20);
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleFont(43);
   Top_pt_leading_nominal_boosted->GetYaxis()->SetTitleOffset(1.55);

   // h2 settings
   data_pt_leading_nominal_boosted->SetLineColor(kRed);
   data_pt_leading_nominal_boosted->SetLineWidth(2);

   // Ratio plot (h3) settings
   h3->SetTitle(""); // Remove the ratio title

   // Y axis ratio plot settings
   h3->GetYaxis()->SetTitle("ratio");
   h3->GetYaxis()->SetRangeUser(0.3,1.7);
   h3->GetYaxis()->SetNdivisions(505);
   h3->GetYaxis()->SetTitleSize(20);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.55);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h3->GetXaxis()->SetTitle("Top_pT [GeV]");
   h3->GetXaxis()->SetTitleSize(20);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(1);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(15);

   c->Print("c.pdf");



}
