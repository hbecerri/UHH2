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

void all_unfolding_data_l(string year = "")
{

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/matching/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic*.root/AnalysisTree",year.c_str()));
    chreco_ttbar->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/matching/electron/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic*.root/AnalysisTree",year.c_str()));

    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TH1F *TTbar_t = new TH1F("TTbar_t","",50,100,350);
    TH1F *TTbar_w = new TH1F("TTbar_w","",50,100,350);
    TH1F *M_lep_rebin = new TH1F("M_lep_rebin","",50,100,350);

    gStyle->SetOptStat(1111111);
    gStyle->SetOptFit();
    gStyle->SetTitleSize(0.06,"x");
    gStyle->SetTitleSize(0.06,"y");
    gStyle->SetOptTitle(0);


    treereco_ttbar->Project("M_lep_rebin","M_lep");
    M_lep_rebin->SetMarkerStyle(4);
    M_lep_rebin->Draw();     

    M_lep_rebin->Fit("gaus", "R", "same",150, 200);

    TCanvas* cc = new TCanvas("cc","",800,600);
    cc->Divide(1,1);
    cc->cd(1);
    M_lep_rebin->GetYaxis()->SetTitle("Events");
    M_lep_rebin->GetXaxis()->SetTitle("M_{t}^{had, wtag} (correctly matched) [GeV]");
    M_lep_rebin->GetXaxis()->SetTitleSize(0.04);
    M_lep_rebin->GetYaxis()->SetTitleSize(0.04);
    M_lep_rebin->SetMarkerStyle(4);
    M_lep_rebin->Draw("p");
    cc->Print(Form("l_%s.pdf",year.c_str()));

}


