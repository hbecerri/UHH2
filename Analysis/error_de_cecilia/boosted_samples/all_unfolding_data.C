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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2017")
{

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    TChain *chreco_ttbar_semi_boosted = new TChain("AnalysisTree","");
    chreco_ttbar_semi_boosted->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_boosted_ttbar/*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_boosted = (TTree*) chreco_ttbar_semi_boosted;


    cout << treereco_ttbar_semi_boosted->GetEntries() << endl;

//array for variable 

    int len = 0; int len_rec = 0;
    if(var_name == "DeltaY") len = 3, len_rec = 3;
    Float_t bins_gen[len];
    Float_t new_rec[len_rec];

    if(var_name == "DeltaY"){ 
        Float_t Bins_gen[] = {-2.,0.,2.};
        Float_t New_rec[] = {-2.,0.,2.};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);
    }

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_boosted = new TH2F("Migration_Matrix_boosted","",newrec,new_rec,binnum_gen,bins_gen);

    Float_t mistag_nominal = 0.9;
    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900)*%f*weight",mistag_nominal);

//Matrices
 
    treereco_ttbar_semi->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s",selcuts_boosted_central.c_str()));


    treereco_ttbar_semi_boosted->Project("Migration_Matrix_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s",selcuts_boosted_central.c_str()));


    cout << Migration_Matrix->GetBinContent(1,1) << endl;
    cout << Migration_Matrix->GetBinError(1,1) << endl;


/*
    TH1F *Ttbar_1_nominal = new TH1F("Ttbar_1_nominal","",binnum_gen,bins_gen);   Ttbar_1_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,1)); Ttbar_1_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,1));
    TH1F *Ttbar_2_nominal = new TH1F("Ttbar_2_nominal","",binnum_gen,bins_gen);   Ttbar_2_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,2)); Ttbar_2_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,2));

    TH1F *Ttbar_1_nominal_boosted = new TH1F("Ttbar_1_nominal_boosted","",binnum_gen,bins_gen);   Ttbar_1_nominal_boosted->SetBinContent(1,Migration_Matrix_boosted->GetBinContent(1,1)); Ttbar_1_nominal_boosted->SetBinContent(2,Migration_Matrix_boosted->GetBinContent(2,1));
    TH1F *Ttbar_2_nominal_boosted = new TH1F("Ttbar_2_nominal_boosted","",binnum_gen,bins_gen);   Ttbar_2_nominal_boosted->SetBinContent(1,Migration_Matrix_boosted->GetBinContent(1,2)); Ttbar_2_nominal_boosted->SetBinContent(2,Migration_Matrix_boosted->GetBinContent(2,2));
 
TFile out("Input_undfolding_data_.root","recreate");

    cout << Ttbar_1_nominal->GetBinContent(1) << endl;
    cout << Ttbar_1_nominal_boosted->GetBinContent(1) << endl;

    cout << Ttbar_1_nominal->GetBinContent(2) << endl;
    cout << Ttbar_1_nominal_boosted->GetBinContent(2) << endl;

    cout << Ttbar_2_nominal->GetBinContent(1) << endl;
    cout << Ttbar_2_nominal_boosted->GetBinContent(1) << endl;

    cout << Ttbar_2_nominal->GetBinContent(2) << endl;
    cout << Ttbar_2_nominal_boosted->GetBinContent(2) << endl;


auto c1    = new TCanvas("c1","c1",600,400);
c1->cd();
c1->Divide(2,2);
c1->cd(1);
Ttbar_1_nominal->Draw();
c1->cd(2);
Ttbar_1_nominal_boosted->Draw();
c1->cd(3);
Ttbar_2_nominal->Draw();
c1->cd(4);
Ttbar_2_nominal_boosted->Draw();
c1->Print("boost.pdf");

*/

}


