#include <algorithm>
#include <iterator>
#include <TROOT.h>
#include <TH2.h>
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
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraphAsymmErrors.h>
#include "RooRealVar.h"
#include "TLegend.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"

using namespace RooFit ;
using namespace std;

void new_c(){
 
   auto c44 = new TCanvas("c44","c44",200,10,600,400);
   double ax[] = {750, 900, 1050};
   double ay[] = {0.8967, 0.8973, 1.01233};
   double aexl[] = {75, 75, 75};
   double aexh[] = {75, 75, 75};
   double aeyl[] = {0.014, 0.07, 0.07};
   double aeyh[] = {0.025, 0.06, 0.057};
   auto gae = new TGraphAsymmErrors(5, ax, ay, aexl, aexh, aeyl, aeyh);
   gae->SetFillColor(2);
   gae->GetYaxis()->SetRangeUser(-5.,5.);
   gae->GetXaxis()->SetRangeUser(675,1125);
   gae->GetYaxis()->SetTitle("A_{c}");
   gae->GetXaxis()->SetLabelOffset(999);
   gae->GetXaxis()->SetLabelSize(0);
   gae->GetXaxis()->SetTitle("M_{t#bar{t}} interval [GeV]");
   gae->SetTitle("");


   double x2[] = {750};
   double y2[] = {0.56};
   double ey2[] = {0.7};
   double ex2[] = {0.001};
   auto ge2 = new TGraphErrors(1, x2, y2, ex2, ey2);
   ge2->SetMarkerStyle(21);

   double x3[] = {900};
   double y3[] = {1.78};
   double ey3[] = {1.1};
   double ex3[] = {0.001};
   auto ge3 = new TGraphErrors(1, x3, y3, ex3, ey3);
   ge3->SetMarkerStyle(21);

   double x4[] = {1050};
   double y4[] = {0.148};
   double ey4[] = {0.859};
   double ex4[] = {0.001};
   auto ge4 = new TGraphErrors(1, x4, y4, ex4, ey4);
   ge4->SetMarkerStyle(21);

   auto line = new TLine(675,0,1125,0);
   line->SetLineStyle(2);

   gae->Draw("a2");
   ge2->Draw("p same");
   ge3->Draw("p same");
   ge4->Draw("p same");
   line->Draw("same");

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(ge2, "Data");
   leg.AddEntry(gae, "QCD NNLO + NLO EW");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   TLatex latex;
   latex.SetTextSize(0.045);
   latex.SetTextAlign(11);  //align at top
   latex.DrawLatex(675,5.102,"CMS #font[12]{Preliminary}");

   TLatex latex2;
   latex2.SetTextSize(0.045);
   latex2.SetTextAlign(11);  //align at top
   latex2.DrawLatex(1005,5.102,"138 fb^{-1} (13 TeV)");



   c44->Print("Ac.pdf");

}







