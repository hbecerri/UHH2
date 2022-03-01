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

void charge_assy(){
 
   TCanvas *c1 = new TCanvas("c1","Exclusion graphs examples",200,10,600,400);
 
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Exclusion graphs");
   mg->SetMaximum(1.);
   mg->SetMinimum(-1.);


   double x[] = {0, 1};
   double y[] = {0.8967, 0.8967};
   double ey[] = {0.02, 0.02};
   double ex[] = {1, 0.5};
   auto ge = new TGraphErrors(2, x, y, ex, ey);

   double xx[] = {1, 2};
   double yy[] = {0.8973, 0.8973};
   double eyy[] = {0.07, 0.07};
   double exx[] = {1, 0.5};
   auto g2 = new TGraphErrors(2, xx, yy, exx, eyy);


   ge->SetFillColor(kRed);
   ge->GetYaxis()->SetRangeUser(-5.,5.);
   ge->GetXaxis()->SetRangeUser(0,2);
   ge->GetYaxis()->SetTitle("A_{c}");
   ge->GetXaxis()->SetLabelOffset(999);
   ge->GetXaxis()->SetLabelSize(0);
   ge->GetXaxis()->SetTitle("M_{t#bar{t}} interval [GeV]");

   g2->SetFillColor(kRed);
   g2->GetYaxis()->SetRangeUser(-5.,5.);
   g2->GetXaxis()->SetRangeUser(0,2);

   double x2[] = {0.56};
   double y2[] = {0.38};
   double ey2[] = {0.7};
   double ex2[] = {0.001};
   auto ge2 = new TGraphErrors(1, x2, y2, ex2, ey2);
   ge2->SetMarkerStyle(21); 

   auto line = new TLine(0,0,1,0);
   line->SetLineStyle(2);

   mg->Add(ge);
   mg->Add(g2);
 
//   mg->Add(ge,"a3");
//   mg->Add(g2,"a3 same");
//   mg->Add(ge2,"AP same"); 
//   mg->Add(ge,"a3 same");
//   mg->Add(ge2,"AP same");
   mg->Draw();
   line->Draw("same");

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(ge2, "Data");
   leg.AddEntry(ge, "QCD NNLO + NLO EW");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   TLatex latex;
   latex.SetTextSize(0.045);
   latex.SetTextAlign(11);  //align at top
   latex.DrawLatex(0.02,5.102,"CMS #font[12]{Preliminary}");

   TLatex latex2;
   latex2.SetTextSize(0.045);
   latex2.SetTextAlign(11);  //align at top
   latex2.DrawLatex(2.9,0.102,"58.8 fb^{-1} (13 TeV)");

   c1->Print("Grazil.pdf");
 
}







