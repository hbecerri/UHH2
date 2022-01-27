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

void Migration_matrix(string year = "2016", string channel = "muon")
{

    gStyle->SetOptStat(0);

    TFile* f_2016_900 = TFile::Open(Form("/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/%s_%s/DeltaY.root",year.c_str(),channel.c_str()));
    TH1 *h_2016_900_Ttbar1 = (TH1*)f_2016_900->Get("Ttbar_1_nominal");
    TH1 *h_2016_900_Ttbar2 = (TH1*)f_2016_900->Get("Ttbar_2_nominal");
    TH1 *h_2016_900_Ttbar3 = (TH1*)f_2016_900->Get("Ttbar_3_nominal");
    TH1 *h_2016_900_Ttbar4 = (TH1*)f_2016_900->Get("Ttbar_4_nominal");
    TFile* f_2016_750 = TFile::Open(Form("/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/%s_%s_750_900/DeltaY.root",year.c_str(),channel.c_str()));
    TH1 *h_2016_750_Ttbar1 = (TH1*)f_2016_750->Get("Ttbar_1_nominal");
    TH1 *h_2016_750_Ttbar2 = (TH1*)f_2016_750->Get("Ttbar_2_nominal");
    TH1 *h_2016_750_Ttbar3 = (TH1*)f_2016_750->Get("Ttbar_3_nominal");
    TH1 *h_2016_750_Ttbar4 = (TH1*)f_2016_750->Get("Ttbar_4_nominal");

    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","",4,0,4,4,0,4);

    Migration_Matrix->SetBinContent(1,1,h_2016_750_Ttbar1->GetBinContent(1));      
    Migration_Matrix->SetBinContent(2,1,h_2016_750_Ttbar1->GetBinContent(2));
    Migration_Matrix->SetBinContent(3,1,h_2016_900_Ttbar1->GetBinContent(1));
    Migration_Matrix->SetBinContent(4,1,h_2016_900_Ttbar1->GetBinContent(2));
    Migration_Matrix->SetBinContent(1,2,h_2016_750_Ttbar2->GetBinContent(1));
    Migration_Matrix->SetBinContent(2,2,h_2016_750_Ttbar2->GetBinContent(2));
    Migration_Matrix->SetBinContent(3,2,h_2016_900_Ttbar2->GetBinContent(1));
    Migration_Matrix->SetBinContent(4,2,h_2016_900_Ttbar2->GetBinContent(2));
    Migration_Matrix->SetBinContent(1,3,h_2016_750_Ttbar3->GetBinContent(1));
    Migration_Matrix->SetBinContent(2,3,h_2016_750_Ttbar3->GetBinContent(2));
    Migration_Matrix->SetBinContent(3,3,h_2016_900_Ttbar3->GetBinContent(1));
    Migration_Matrix->SetBinContent(4,3,h_2016_900_Ttbar3->GetBinContent(2));
    Migration_Matrix->SetBinContent(1,4,h_2016_750_Ttbar4->GetBinContent(1));
    Migration_Matrix->SetBinContent(2,4,h_2016_750_Ttbar4->GetBinContent(2));
    Migration_Matrix->SetBinContent(3,4,h_2016_900_Ttbar4->GetBinContent(1));
    Migration_Matrix->SetBinContent(4,4,h_2016_900_Ttbar4->GetBinContent(2));
 
    Migration_Matrix->GetXaxis()->SetBinLabel(1,"#Delta|y|^{rec} < 0;M_{t#bar{t}}^{rec} < 750");
    Migration_Matrix->GetXaxis()->SetBinLabel(2,"#Delta|y|^{rec} > 0;M_{t#bar{t}}^{rec} < 750");
    Migration_Matrix->GetXaxis()->SetBinLabel(3,"#Delta|y|^{rec} < 0;M_{t#bar{t}}^{rec} < 900");
    Migration_Matrix->GetXaxis()->SetBinLabel(4,"#Delta|y|^{rec} > 0;M_{t#bar{t}}^{rec} < 900");

    Migration_Matrix->GetYaxis()->SetBinLabel(1,"#Delta|y|^{gen} < 0;M_{t#bar{t}}^{gen} < 750");
    Migration_Matrix->GetYaxis()->SetBinLabel(2,"#Delta|y|^{gen} > 0;M_{t#bar{t}}^{gen} < 750");
    Migration_Matrix->GetYaxis()->SetBinLabel(3,"#Delta|y|^{gen} < 0;M_{t#bar{t}}^{gen} < 900");
    Migration_Matrix->GetYaxis()->SetBinLabel(4,"#Delta|y|^{gen} > 0;M_{t#bar{t}}^{gen} < 900");

    TCanvas* cc = new TCanvas("cc","",2400,1600);
    cc->Divide(1,1);
    cc->cd(1);
    gPad->SetLeftMargin(0.2);
    gPad->SetRightMargin(0.2);
    Migration_Matrix->Draw("colz");
    Migration_Matrix->GetYaxis()->LabelsOption("v");
    cc->Modified();

    cc->Update();

    cc->Print(Form("Migration_Matrix_%s_%s.pdf",year.c_str(),channel.c_str()));
  
}




