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

void Acceptance(string var_weight = "", int aa = 1)
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar_full = new TChain("AnalysisTree","");
//    chreco_ttbar_full->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2017/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_24.root/AnalysisTree");
    chreco_ttbar_full->Add("/nfs/dust/cms/user/hugobg/analysis/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_24.root/AnalysisTree");
    chreco_ttbar_full->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2017/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_24.root/AnalysisTree");
    chreco_ttbar_full->Add("/nfs/dust/cms/user/hugobg/analysis/Preselection_Acceptance_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_24.root/AnalysisTree");
    TTree *treereco_ttbar_full = (TTree*) chreco_ttbar_full;

    TChain *chreco_ttbar_despues_muon = new TChain("AnalysisTree","");
//    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/muon/workdir_Zprime_Analysis_2016_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/electron/workdir_Zprime_Analysis_2016_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017v2_0.root/AnalysisTree");
    chreco_ttbar_despues_muon->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/workdir_Zprime_Analysis_2018_electron_CHS_Acceptance/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root/AnalysisTree");
    TTree *treereco_ttbar_despues_muon = (TTree*) chreco_ttbar_despues_muon;
 

//array for variable 

    Float_t bins_gen[] = {-2.,0.,2.}; 

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Acc_antes_muon_nominal = new TH1F("Acc_antes_muon_nominal","",binnum_gen,bins_gen);

    TH1F *Acc_despues_muon_nominal_750 = new TH1F("Acc_despues_muon_nominal_750","",binnum_gen,bins_gen);
    TH1F *Acc_despues_muon_nominal_900 = new TH1F("Acc_despues_muon_nominal_900","",binnum_gen,bins_gen);
    TH1F *Acc_despues_muon_nominal_750_900 = new TH1F("Acc_despues_muon_nominal_750_900","",binnum_gen,bins_gen);

    string var_gen = "";

    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    string is_muon = "1";


    treereco_ttbar_full->Project("Acc_antes_muon_nominal",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("(%s)",is_muon.c_str()));

    treereco_ttbar_despues_muon->Project("Acc_despues_muon_nominal_750",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750");

    treereco_ttbar_despues_muon->Project("Acc_despues_muon_nominal_750_900",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900");

    treereco_ttbar_despues_muon->Project("Acc_despues_muon_nominal_900",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900");



    Float_t Acceptance_muon_ttbar1_nominal_750 = Acc_despues_muon_nominal_750->GetBinContent(1)/Acc_antes_muon_nominal->GetBinContent(1);
    Float_t Acceptance_muon_ttbar2_nominal_750 = Acc_despues_muon_nominal_750->GetBinContent(2)/Acc_antes_muon_nominal->GetBinContent(2);

    Float_t Acceptance_muon_ttbar1_nominal_750_900 = Acc_despues_muon_nominal_750_900->GetBinContent(1)/Acc_antes_muon_nominal->GetBinContent(1);
    Float_t Acceptance_muon_ttbar2_nominal_750_900 = Acc_despues_muon_nominal_750_900->GetBinContent(2)/Acc_antes_muon_nominal->GetBinContent(2);

    Float_t Acceptance_muon_ttbar1_nominal_900 = Acc_despues_muon_nominal_900->GetBinContent(1)/Acc_antes_muon_nominal->GetBinContent(1);
    Float_t Acceptance_muon_ttbar2_nominal_900 = Acc_despues_muon_nominal_900->GetBinContent(2)/Acc_antes_muon_nominal->GetBinContent(2);

    cout << "750" << endl;
    cout << Acceptance_muon_ttbar1_nominal_750 << endl;
    cout << Acceptance_muon_ttbar2_nominal_750 << endl;

    cout << "900" << endl;
    cout << Acceptance_muon_ttbar1_nominal_900 << endl;
    cout << Acceptance_muon_ttbar2_nominal_900 << endl;

    cout << "750-900" << endl;
    cout << Acceptance_muon_ttbar1_nominal_750_900 << endl;
    cout << Acceptance_muon_ttbar2_nominal_750_900 << endl;


}

 
