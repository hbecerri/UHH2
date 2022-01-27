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

void Acceptance_2018_electron()
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TFile* file = TFile::Open("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/electron/Btag_Eff_ele_2018/BtagEff.root");

    TH2 *BTagMCEffFlavBPassing = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavBPassing");
    TH2 *BTagMCEffFlavBTotal = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavBTotal");
    TH2 *BTagMCEffFlavCPassing = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavCPassing");
    TH2 *BTagMCEffFlavCTotal = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavCTotal");
    TH2 *BTagMCEffFlavUDSGPassing = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavUDSGPassing");
    TH2 *BTagMCEffFlavUDSGTotal = (TH2*)file->Get("BTagMCEfficiency/BTagMCEffFlavUDSGTotal");

    BTagMCEffFlavBPassing->Divide(BTagMCEffFlavBTotal);
    BTagMCEffFlavCPassing->Divide(BTagMCEffFlavCTotal);
    BTagMCEffFlavUDSGPassing->Divide(BTagMCEffFlavUDSGTotal);

    TFile out("BTagMCEfficiencyHists_electron2018.root","recreate");
    BTagMCEffFlavBPassing->Write("BTagMCEffFlavBEff");
    BTagMCEffFlavCPassing->Write("BTagMCEffFlavCEff");
    BTagMCEffFlavUDSGPassing->Write("BTagMCEffFlavUDSGEff");    

    auto c1 = new TCanvas("c1","c1",600,400);
    c1->cd();
    c1->SetLogx();
    BTagMCEffFlavBPassing->Draw("colz TEXT1");
    c1->Print("BTagMCEffFlavB_2018electron.pdf");

    auto c2 = new TCanvas("c2","c2",600,400);
    c2->cd();
    c2->SetLogx();
    BTagMCEffFlavUDSGPassing->Draw("colz TEXT1");
    c2->Print("BTagMCEffFlavUDSGP_2018electron.pdf");

}

