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
//#include "sigma.h"
//#include "mean.h"
#include "TRandom3.h"

void all_unfolding_data(string year = "")
{

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/matching/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TH1F *TTbar_t = new TH1F("TTbar_t","",5,-2,2);
    TH1F *TTbar_w = new TH1F("TTbar_w","",5,-2,2);

    TH1F *TTbar_t_b = new TH1F("TTbar_t_b","",5,-2,2);
    TH1F *TTbar_w_b = new TH1F("TTbar_w_b","",5,-2,2);

    TH1F *TTbar_t_w = new TH1F("TTbar_t_w","",5,-2,2);
    TH1F *TTbar_w_w = new TH1F("TTbar_w_w","",5,-2,2);

    TH1F *TTbar_t_t = new TH1F("TTbar_t_t","",5,-2,2);
    TH1F *TTbar_w_t = new TH1F("TTbar_w_t","",5,-2,2);

    treereco_ttbar->Project("TTbar_t","match","match > 0 && ttagN<=1 && wtagN<=1 &&  M_tt > 750 && M_tt < 900");
    treereco_ttbar->Project("TTbar_w","match","match < 0 && ttagN<=1 && wtagN<=1 &&  M_tt > 750 && M_tt < 900");

    treereco_ttbar->Project("TTbar_t_b","match","match > 0 && ttagN==0 && wtagN==0 &&  M_tt > 750 && M_tt < 900");
    treereco_ttbar->Project("TTbar_w_b","match","match < 0 && ttagN==0 && wtagN==0 &&  M_tt > 750 && M_tt < 900");

    treereco_ttbar->Project("TTbar_t_t","match","match > 0 && ttagN==1 && wtagN==0 &&  M_tt > 750 && M_tt < 900");
    treereco_ttbar->Project("TTbar_w_t","match","match < 0 && ttagN==1 && wtagN==0 &&  M_tt > 750 && M_tt < 900");     

    treereco_ttbar->Project("TTbar_t_w","match","match > 0 && ttagN==0 && wtagN==1 &&  M_tt > 750 && M_tt < 900");
    treereco_ttbar->Project("TTbar_w_w","match","match < 0 && ttagN==0 && wtagN==1 &&  M_tt > 750 && M_tt < 900");


   cout << TTbar_t->Integral() << endl;
   cout << TTbar_w->Integral() << endl;
   cout << "--------" << endl;

   cout << TTbar_t_b->Integral() << endl;
   cout << TTbar_w_b->Integral() << endl;
   cout << "--------" << endl;

   cout << TTbar_t_w->Integral() << endl;
   cout << TTbar_w_w->Integral() << endl;
   cout << "--------" << endl;

   cout << TTbar_t_t->Integral() << endl;
   cout << TTbar_w_t->Integral() << endl;
   cout << "--------" << endl;

/*
    TH1F *TTbar_t = new TH1F("TTbar_t","",5,-2,2);
    TH1F *TTbar_w = new TH1F("TTbar_w","",5,-2,2);
    TH1F *M_tohad_dr_wtag_rebin = new TH1F("M_tohad_dr_wtag_rebin","",5,-2,2);

    gStyle->SetOptStat(1111111);
    gStyle->SetOptFit();
    gStyle->SetTitleSize(0.06,"x");
    gStyle->SetTitleSize(0.06,"y");
    gStyle->SetOptTitle(0);


    treereco_ttbar->Project("M_tohad_dr_wtag_rebin","M_had_wtag - 4");
    M_tohad_dr_wtag_rebin->SetMarkerStyle(4);
    M_tohad_dr_wtag_rebin->Draw();     

    M_tohad_dr_wtag_rebin->Fit("gaus", "R", "same",150, 200);

    TCanvas* cc = new TCanvas("cc","",800,600);
    cc->Divide(1,1);
    cc->cd(1);
    M_tohad_dr_wtag_rebin->GetYaxis()->SetTitle("Events");
    M_tohad_dr_wtag_rebin->GetXaxis()->SetTitle("M_{t}^{had, wtag} (correctly matched) [GeV]");
    M_tohad_dr_wtag_rebin->GetXaxis()->SetTitleSize(0.04);
    M_tohad_dr_wtag_rebin->GetYaxis()->SetTitleSize(0.04);
    M_tohad_dr_wtag_rebin->SetMarkerStyle(4);
    M_tohad_dr_wtag_rebin->Draw("p");
    cc->Print(Form("w_%s.pdf",year.c_str()));
*/
}


