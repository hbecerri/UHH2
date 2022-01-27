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

void twoscales(string var_weight = "1", int aa = 1)
{
Float_t muon_2018_nMl = 0.0005349862;
Float_t muon_2018_pMl = 0.00053098385;
Float_t muon_2018_nMh = 0.00061103166;
Float_t muon_2018_pMh = 0.0005723419;
Float_t electron_2018_nMl = 0.00012407411;
Float_t electron_2018_pMl = 0.00015342497;
Float_t electron_2018_nMh = 0.00019211476;
Float_t electron_2018_pMh = 0.00021282365;
Float_t muon_2017_nMl = 0.00057541538;
Float_t muon_2017_pMl = 0.00056856521;
Float_t muon_2017_nMh = 0.00058021053;
Float_t muon_2017_pMh = 0.00060418615;
Float_t electron_2017_nMl = 0.0001417988;
Float_t electron_2017_pMl = 0.00012261828;
Float_t electron_2017_nMh = 0.00019249014;
Float_t electron_2017_pMh = 0.00021715081;
Float_t muon_2016_nMl = 0.00058647734;
Float_t muon_2016_pMl = 0.00055309862;
Float_t muon_2016_nMh = 0.00060951331;
Float_t muon_2016_pMh = 0.00061397947;
Float_t electron_2016_nMl = 0.0001370406;
Float_t electron_2016_pMl = 0.00011588509;
Float_t electron_2016_nMh = 0.00021249519;
Float_t electron_2016_pMh = 0.00021578604;



   TCanvas *c1 = new TCanvas("c1","different scales hists",600,400);
   //create, fill and draw h1
   gStyle->SetOptStat(kFALSE);
   TH1F *h_muon_2018 = new TH1F("h_muon_2018","",4,0,4);
   h_muon_2018->SetBinContent(1,muon_2018_nMl);
   h_muon_2018->SetBinContent(2,muon_2018_pMl);
   h_muon_2018->SetBinContent(3,muon_2018_nMh);
   h_muon_2018->SetBinContent(4,muon_2018_pMh);
   h_muon_2018->Draw();
   h_muon_2018->GetYaxis()->SetRangeUser(0.00001,0.0008);
   h_muon_2018->SetLineColor(2);
   TAxis* a = h_muon_2018->GetXaxis();
   a->ChangeLabel(2,-1,-1,-1,-1,-1,"nMl");
   a->ChangeLabel(4,-1,-1,-1,-1,-1,"pMl");
   a->ChangeLabel(6,-1,-1,-1,-1,-1,"nMh");
   a->ChangeLabel(8,-1,-1,-1,-1,-1,"pMh");

   a->ChangeLabel(1,-1,-1,-1,-1,-1," ");
   a->ChangeLabel(3,-1,-1,-1,-1,-1," ");
   a->ChangeLabel(5,-1,-1,-1,-1,-1," ");
   a->ChangeLabel(7,-1,-1,-1,-1,-1," ");
   a->ChangeLabel(9,-1,-1,-1,-1,-1," ");
 
   TH1F *h_muon_2017 = new TH1F("h_muon_2017","muon_2017",4,0,4);
   h_muon_2017->SetBinContent(1,muon_2017_nMl);
   h_muon_2017->SetBinContent(2,muon_2017_pMl);
   h_muon_2017->SetBinContent(3,muon_2017_nMh);
   h_muon_2017->SetBinContent(4,muon_2017_pMh);
   h_muon_2017->Draw("same");
   h_muon_2017->SetLineColor(3);

   TH1F *h_muon_2016 = new TH1F("h_muon_2016","muon_2016",4,0,4);
   h_muon_2016->SetBinContent(1,muon_2016_nMl);
   h_muon_2016->SetBinContent(2,muon_2016_pMl);
   h_muon_2016->SetBinContent(3,muon_2016_nMh);
   h_muon_2016->SetBinContent(4,muon_2016_pMh);
   h_muon_2016->Draw("same");
   h_muon_2016->SetLineColor(4);

   c1->Update(); 

   auto legend = new TLegend(0.1,0.75,0.48,0.9);
   legend->SetHeader("Acceptance","C");
   legend->AddEntry(h_muon_2018,"2018_muon","l");
   legend->AddEntry(h_muon_2017,"2017_muon","l");
   legend->AddEntry(h_muon_2016,"2016_muon","l");

   legend->Draw("same");

   c1->Print("Acceptance_muon.pdf");


   TCanvas *c2 = new TCanvas("c2","different scales hists",600,400);
   TH1F *h_electron_2018 = new TH1F("h_electron_2018","",4,0,4);
   h_electron_2018->SetBinContent(1,electron_2018_nMl);
   h_electron_2018->SetBinContent(2,electron_2018_pMl);
   h_electron_2018->SetBinContent(3,electron_2018_nMh);
   h_electron_2018->SetBinContent(4,electron_2018_pMh);
   h_electron_2018->Draw("");
   h_electron_2018->SetLineColor(2);
   h_electron_2018->GetYaxis()->SetRangeUser(0.00005,0.0008);

   TAxis* b = h_electron_2018->GetXaxis();
   b->ChangeLabel(2,-1,-1,-1,-1,-1,"nMl");
   b->ChangeLabel(4,-1,-1,-1,-1,-1,"pMl");
   b->ChangeLabel(6,-1,-1,-1,-1,-1,"nMh");
   b->ChangeLabel(8,-1,-1,-1,-1,-1,"pMh");

   b->ChangeLabel(1,-1,-1,-1,-1,-1," ");
   b->ChangeLabel(3,-1,-1,-1,-1,-1," ");
   b->ChangeLabel(5,-1,-1,-1,-1,-1," ");
   b->ChangeLabel(7,-1,-1,-1,-1,-1," ");
   b->ChangeLabel(9,-1,-1,-1,-1,-1," ");

   TH1F *h_electron_2017 = new TH1F("h_electron_2017","electron_2017",4,0,4);
   h_electron_2017->SetBinContent(1,electron_2017_nMl);
   h_electron_2017->SetBinContent(2,electron_2017_pMl);
   h_electron_2017->SetBinContent(3,electron_2017_nMh);
   h_electron_2017->SetBinContent(4,electron_2017_pMh);
   h_electron_2017->Draw("same");
   h_electron_2017->SetLineColor(3);

   TH1F *h_electron_2016 = new TH1F("h_electron_2016","electron_2016",4,0,4);
   h_electron_2016->SetBinContent(1,electron_2016_nMl);
   h_electron_2016->SetBinContent(2,electron_2016_pMl);
   h_electron_2016->SetBinContent(3,electron_2016_nMh);
   h_electron_2016->SetBinContent(4,electron_2016_pMh);
   h_electron_2016->Draw("same");
   h_electron_2016->SetLineColor(4);

   auto legend2 = new TLegend(0.1,0.75,0.48,0.9);
   legend2->SetHeader("Acceptance","C");
   legend2->AddEntry(h_electron_2018,"2018_electron","l");
   legend2->AddEntry(h_electron_2017,"2017_electron","l");
   legend2->AddEntry(h_electron_2016,"2016_electron","l");

   legend2->Draw("same");

   c2->Update();
   c2->Print("Acceptance_electron.pdf");



}


