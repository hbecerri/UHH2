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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

        gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    //jec
    TChain *chreco_ttbar_semi_jecup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/workdir_Zprime_Analysis_%s_electron_CHS_JECup/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecup = (TTree*) chreco_ttbar_semi_jecup;

    TChain *chreco_ttbar_semi_jecdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/workdir_Zprime_Analysis_%s_electron_CHS_JECdown/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecdown = (TTree*) chreco_ttbar_semi_jecdown;

    //jer
/*    TChain *chreco_ttbar_semi_jerup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jerup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/workdir_Zprime_Analysis_%s_electron_CHS_JERup/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jerup = (TTree*) chreco_ttbar_semi_jerup;

    TChain *chreco_ttbar_semi_jerdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jerdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/workdir_Zprime_Analysis_%s_electron_CHS_JERdown/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jerdown = (TTree*) chreco_ttbar_semi_jerdown;
*/
    //hdamp

    TChain *chreco_ttbar_semi_hdampup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/hdamp_up/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi_hdampup = (TTree*) chreco_ttbar_semi_hdampup;

    TChain *chreco_ttbar_semi_hdampdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/electron/hdamp_down/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi_hdampdown = (TTree*) chreco_ttbar_semi_hdampdown;


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

    TH2F *Migration_Matrix_pileupUp = new TH2F("Migration_Matrix_pileupUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_eleIDUp = new TH2F("Migration_Matrix_eleIDUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_eleHLTUp = new TH2F("Migration_Matrix_eleHLTUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewUp = new TH2F("Migration_Matrix_Top_pT_rewUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagUp = new TH2F("Migration_Matrix_mistagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagUp = new TH2F("Migration_Matrix_toptagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ele_recUp = new TH2F("Migration_Matrix_ele_recUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRUp = new TH2F("Migration_Matrix_ISRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRUp = new TH2F("Migration_Matrix_FSRUp","",newrec,new_rec,binnum_gen,bins_gen);
//    TH2F *Migration_Matrix_jecUp = new TH2F("Migration_Matrix_jecUp","",newrec,new_rec,binnum_gen,bins_gen);
//    TH2F *Migration_Matrix_jerUp = new TH2F("Migration_Matrix_jerUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampUp = new TH2F("Migration_Matrix_hdampUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_cferr1Up = new TH2F("Migration_Matrix_cferr1Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_cferr2Up = new TH2F("Migration_Matrix_cferr2Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfUp = new TH2F("Migration_Matrix_hfUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfUp = new TH2F("Migration_Matrix_lfUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfstats1Up = new TH2F("Migration_Matrix_hfstats1Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfstats2Up = new TH2F("Migration_Matrix_hfstats2Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfstats1Up = new TH2F("Migration_Matrix_lfstats1Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfstats2Up = new TH2F("Migration_Matrix_lfstats2Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jesUp = new TH2F("Migration_Matrix_jesUp","",newrec,new_rec,binnum_gen,bins_gen);


    TH2F *Migration_Matrix_pileupDown = new TH2F("Migration_Matrix_pileupDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_eleIDDown = new TH2F("Migration_Matrix_eleIDDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_eleHLTDown = new TH2F("Migration_Matrix_eleHLTDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewDown = new TH2F("Migration_Matrix_Top_pT_rewDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagDown = new TH2F("Migration_Matrix_mistagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagDown = new TH2F("Migration_Matrix_toptagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ele_recDown = new TH2F("Migration_Matrix_ele_recDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRDown = new TH2F("Migration_Matrix_ISRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRDown = new TH2F("Migration_Matrix_FSRDown","",newrec,new_rec,binnum_gen,bins_gen);
//    TH2F *Migration_Matrix_jecDown = new TH2F("Migration_Matrix_jecDown","",newrec,new_rec,binnum_gen,bins_gen);
//    TH2F *Migration_Matrix_jerDown = new TH2F("Migration_Matrix_jerDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampDown = new TH2F("Migration_Matrix_hdampDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_cferr1Down = new TH2F("Migration_Matrix_cferr1Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_cferr2Down = new TH2F("Migration_Matrix_cferr2Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfDown = new TH2F("Migration_Matrix_hfDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfDown = new TH2F("Migration_Matrix_lfDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfstats1Down = new TH2F("Migration_Matrix_hfstats1Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hfstats2Down = new TH2F("Migration_Matrix_hfstats2Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfstats1Down = new TH2F("Migration_Matrix_lfstats1Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_lfstats2Down = new TH2F("Migration_Matrix_lfstats2Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jesDown = new TH2F("Migration_Matrix_jesDown","",newrec,new_rec,binnum_gen,bins_gen);

    string  pileupUp = "(weight_sfelec_TightID)*(weight_pu_up)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  pileupDown = "(weight_sfelec_TightID)*(weight_pu_down)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  eleIDUp = "(weight_sfelec_TightID_up)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  eleIDDown = "(weight_sfelec_TightID_down)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  eleHLTUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  eleHLTDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  cferr1Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1up)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  cferr1Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  cferr2Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2up)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  cferr2Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfup)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfdown)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfstats1Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfstats1Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfstats2Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hfstats2Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  jesUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesup)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  jesDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesdown)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfup)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfdown)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfstats1Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1up)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfstats1Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfstats2Up = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2up)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  lfstats2Down = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  Top_pT_rewUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(1)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  Top_pT_rewDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_down_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  mistagUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*1.02*(weight_HT_HT)";
    string  mistagDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*0.98*(weight_HT_HT)";
    string  toptagUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  toptagDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  ele_recUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_up)*(weight_HT_HT)";
    string  ele_recDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_down)*(weight_HT_HT)";
    string  HTUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_up)";
    string  HTDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_down)";
    string  ISRUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*ISRup";
    string  ISRDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*ISRdown";
    string  FSRUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*FSRup";
    string  FSRDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*FSRdown";
//    string  jecUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
//    string  jecDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
//    string  jerUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
//    string  jerDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)";
    string  hdampUp = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84";
    string  hdampDown = "(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84";

    Float_t mistag_nominal = 0.86;

    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900)*%f",mistag_nominal);

//Matrices
    treereco_ttbar_semi->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_nolimit*weight_btagdisc_central*weight_sfelec_Rec*(weight_HT_HT)",selcuts_boosted_central.c_str()));

    treereco_ttbar_semi->Project("Migration_Matrix_pileupUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_eleIDUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",eleIDUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_eleHLTUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",eleHLTUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ele_recUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ele_recUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRUp.c_str(),selcuts_boosted_central.c_str()));
//    treereco_ttbar_semi_jecup->Project("Migration_Matrix_jecUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
//    treereco_ttbar_semi_jerup->Project("Migration_Matrix_jerUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_hdampup->Project("Migration_Matrix_hdampUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampUp.c_str(),selcuts_boosted_central.c_str()));

///btagging 
 
    treereco_ttbar_semi->Project("Migration_Matrix_cferr1Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",cferr1Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_cferr2Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",cferr2Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfstats1Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfstats1Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfstats2Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfstats2Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfstats1Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfstats1Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfstats2Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfstats2Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jesUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jesUp.c_str(),selcuts_boosted_central.c_str()));



//Down
    treereco_ttbar_semi->Project("Migration_Matrix_pileupDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_eleIDDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",eleIDDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_eleHLTDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",eleHLTDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ele_recDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ele_recDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRDown.c_str(),selcuts_boosted_central.c_str()));
//    treereco_ttbar_semi_jecdown->Project("Migration_Matrix_jecDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
//    treereco_ttbar_semi_jerdown->Project("Migration_Matrix_jerDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_hdampdown->Project("Migration_Matrix_hdampDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampDown.c_str(),selcuts_boosted_central.c_str()));


//btagging

    treereco_ttbar_semi->Project("Migration_Matrix_cferr1Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",cferr1Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_cferr2Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",cferr2Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfstats1Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfstats1Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hfstats2Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hfstats2Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfstats1Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfstats1Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_lfstats2Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",lfstats2Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jesDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jesDown.c_str(),selcuts_boosted_central.c_str()));


    TH1F *Ttbar_1_nominal = new TH1F("Ttbar_1_nominal","",binnum_gen,bins_gen);   Ttbar_1_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,1)); Ttbar_1_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,1));
    TH1F *Ttbar_2_nominal = new TH1F("Ttbar_2_nominal","",binnum_gen,bins_gen);   Ttbar_2_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,2)); Ttbar_2_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,2));
 
    TH1F *Ttbar_1_pileupUp = new TH1F("Ttbar_1_pileupUp","",newrec,new_rec);  Ttbar_1_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,1)); Ttbar_1_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,1));
    TH1F *Ttbar_2_pileupUp = new TH1F("Ttbar_2_pileupUp","",newrec,new_rec);  Ttbar_2_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,2)); Ttbar_2_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,2));
    TH1F *Ttbar_1_eleIDUp = new TH1F("Ttbar_1_eleIDUp","",newrec,new_rec);      Ttbar_1_eleIDUp->SetBinContent(1,Migration_Matrix_eleIDUp->GetBinContent(1,1)); Ttbar_1_eleIDUp->SetBinContent(2,Migration_Matrix_eleIDUp->GetBinContent(2,1));
    TH1F *Ttbar_2_eleIDUp = new TH1F("Ttbar_2_eleIDUp","",newrec,new_rec);      Ttbar_2_eleIDUp->SetBinContent(1,Migration_Matrix_eleIDUp->GetBinContent(1,2)); Ttbar_2_eleIDUp->SetBinContent(2,Migration_Matrix_eleIDUp->GetBinContent(2,2));
    TH1F *Ttbar_1_eleHLTUp = new TH1F("Ttbar_1_eleHLTUp","",newrec,new_rec);    Ttbar_1_eleHLTUp->SetBinContent(1,Migration_Matrix_eleHLTUp->GetBinContent(1,1)); Ttbar_1_eleHLTUp->SetBinContent(2,Migration_Matrix_eleHLTUp->GetBinContent(2,1));
    TH1F *Ttbar_2_eleHLTUp = new TH1F("Ttbar_2_eleHLTUp","",newrec,new_rec);    Ttbar_2_eleHLTUp->SetBinContent(1,Migration_Matrix_eleHLTUp->GetBinContent(1,2)); Ttbar_2_eleHLTUp->SetBinContent(2,Migration_Matrix_eleHLTUp->GetBinContent(2,2));
    TH1F *Ttbar_1_Top_pT_rewUp = new TH1F("Ttbar_1_Top_pT_rewUp","",newrec,new_rec);   Ttbar_1_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,1)); Ttbar_1_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,1));
    TH1F *Ttbar_2_Top_pT_rewUp = new TH1F("Ttbar_2_Top_pT_rewUp","",newrec,new_rec);   Ttbar_2_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,2)); Ttbar_2_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,2)); 
    TH1F *Ttbar_1_mistagUp = new TH1F("Ttbar_1_mistagUp","",newrec,new_rec);   Ttbar_1_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,1)); Ttbar_1_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,1));
    TH1F *Ttbar_2_mistagUp = new TH1F("Ttbar_2_mistagUp","",newrec,new_rec);   Ttbar_2_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,2)); Ttbar_2_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,2));
    TH1F *Ttbar_1_toptagUp = new TH1F("Ttbar_1_toptagUp","",newrec,new_rec);   Ttbar_1_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,1)); Ttbar_1_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,1));
    TH1F *Ttbar_2_toptagUp = new TH1F("Ttbar_2_toptagUp","",newrec,new_rec);    Ttbar_2_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,2)); Ttbar_2_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,2));
    TH1F *Ttbar_1_ele_recUp = new TH1F("Ttbar_1_ele_recUp","",newrec,new_rec);    Ttbar_1_ele_recUp->SetBinContent(1,Migration_Matrix_ele_recUp->GetBinContent(1,1)); Ttbar_1_ele_recUp->SetBinContent(2,Migration_Matrix_ele_recUp->GetBinContent(2,1));
    TH1F *Ttbar_2_ele_recUp = new TH1F("Ttbar_2_ele_recUp","",newrec,new_rec);    Ttbar_2_ele_recUp->SetBinContent(1,Migration_Matrix_ele_recUp->GetBinContent(1,2)); Ttbar_2_ele_recUp->SetBinContent(2,Migration_Matrix_ele_recUp->GetBinContent(2,2));
    TH1F *Ttbar_1_ISRUp = new TH1F("Ttbar_1_ISRUp","",newrec,new_rec);   Ttbar_1_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,1)); Ttbar_1_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,1));
    TH1F *Ttbar_2_ISRUp = new TH1F("Ttbar_2_ISRUp","",newrec,new_rec);   Ttbar_2_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,2)); Ttbar_2_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,2));
    TH1F *Ttbar_1_FSRUp = new TH1F("Ttbar_1_FSRUp","",newrec,new_rec);    Ttbar_1_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,1)); Ttbar_1_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,1));
    TH1F *Ttbar_2_FSRUp = new TH1F("Ttbar_2_FSRUp","",newrec,new_rec);    Ttbar_2_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,2)); Ttbar_2_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,2));
//    TH1F *Ttbar_1_jecUp = new TH1F("Ttbar_1_jecUp","",newrec,new_rec);    Ttbar_1_jecUp->SetBinContent(1,Migration_Matrix_jecUp->GetBinContent(1,1)); Ttbar_1_jecUp->SetBinContent(2,Migration_Matrix_jecUp->GetBinContent(2,1));
//    TH1F *Ttbar_2_jecUp = new TH1F("Ttbar_2_jecUp","",newrec,new_rec);    Ttbar_2_jecUp->SetBinContent(1,Migration_Matrix_jecUp->GetBinContent(1,2)); Ttbar_2_jecUp->SetBinContent(2,Migration_Matrix_jecUp->GetBinContent(2,2));
//    TH1F *Ttbar_1_jerUp = new TH1F("Ttbar_1_jerUp","",newrec,new_rec);   Ttbar_1_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,1)); Ttbar_1_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,1));
//    TH1F *Ttbar_2_jerUp = new TH1F("Ttbar_2_jerUp","",newrec,new_rec);   Ttbar_2_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,2)); Ttbar_2_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,2));
    TH1F *Ttbar_1_hdampUp = new TH1F("Ttbar_1_hdampUp","",newrec,new_rec);   Ttbar_1_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,1)); Ttbar_1_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,1));
    TH1F *Ttbar_2_hdampUp = new TH1F("Ttbar_2_hdampUp","",newrec,new_rec);   Ttbar_2_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,2)); Ttbar_2_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,2));
    TH1F *Ttbar_1_cferr1Up = new TH1F("Ttbar_1_cferr1Up","",newrec,new_rec);   Ttbar_1_cferr1Up->SetBinContent(1,Migration_Matrix_cferr1Up->GetBinContent(1,1)); Ttbar_1_cferr1Up->SetBinContent(2,Migration_Matrix_cferr1Up->GetBinContent(2,1));
    TH1F *Ttbar_2_cferr1Up = new TH1F("Ttbar_2_cferr1Up","",newrec,new_rec);   Ttbar_2_cferr1Up->SetBinContent(1,Migration_Matrix_cferr1Up->GetBinContent(1,2)); Ttbar_2_cferr1Up->SetBinContent(2,Migration_Matrix_cferr1Up->GetBinContent(2,2));
    TH1F *Ttbar_1_cferr2Up = new TH1F("Ttbar_1_cferr2Up","",newrec,new_rec);   Ttbar_1_cferr2Up->SetBinContent(1,Migration_Matrix_cferr2Up->GetBinContent(1,1)); Ttbar_1_cferr2Up->SetBinContent(2,Migration_Matrix_cferr2Up->GetBinContent(2,1));
    TH1F *Ttbar_2_cferr2Up = new TH1F("Ttbar_2_cferr2Up","",newrec,new_rec);   Ttbar_2_cferr2Up->SetBinContent(1,Migration_Matrix_cferr2Up->GetBinContent(1,2)); Ttbar_2_cferr2Up->SetBinContent(2,Migration_Matrix_cferr2Up->GetBinContent(2,2));
    TH1F *Ttbar_1_hfUp = new TH1F("Ttbar_1_hfUp","",newrec,new_rec);   Ttbar_1_hfUp->SetBinContent(1,Migration_Matrix_hfUp->GetBinContent(1,1)); Ttbar_1_hfUp->SetBinContent(2,Migration_Matrix_hfUp->GetBinContent(2,1));
    TH1F *Ttbar_2_hfUp = new TH1F("Ttbar_2_hfUp","",newrec,new_rec);   Ttbar_2_hfUp->SetBinContent(1,Migration_Matrix_hfUp->GetBinContent(1,2)); Ttbar_2_hfUp->SetBinContent(2,Migration_Matrix_hfUp->GetBinContent(2,2));
    TH1F *Ttbar_1_lfUp = new TH1F("Ttbar_1_lfUp","",newrec,new_rec);   Ttbar_1_lfUp->SetBinContent(1,Migration_Matrix_lfUp->GetBinContent(1,1)); Ttbar_1_lfUp->SetBinContent(2,Migration_Matrix_lfUp->GetBinContent(2,1));
    TH1F *Ttbar_2_lfUp = new TH1F("Ttbar_2_lfUp","",newrec,new_rec);   Ttbar_2_lfUp->SetBinContent(1,Migration_Matrix_lfUp->GetBinContent(1,2)); Ttbar_2_lfUp->SetBinContent(2,Migration_Matrix_lfUp->GetBinContent(2,2));
    TH1F *Ttbar_1_hfstats1Up = new TH1F("Ttbar_1_hfstats1Up","",newrec,new_rec);   Ttbar_1_hfstats1Up->SetBinContent(1,Migration_Matrix_hfstats1Up->GetBinContent(1,1)); Ttbar_1_hfstats1Up->SetBinContent(2,Migration_Matrix_hfstats1Up->GetBinContent(2,1));
    TH1F *Ttbar_2_hfstats1Up = new TH1F("Ttbar_2_hfstats1Up","",newrec,new_rec);   Ttbar_2_hfstats1Up->SetBinContent(1,Migration_Matrix_hfstats1Up->GetBinContent(1,2)); Ttbar_2_hfstats1Up->SetBinContent(2,Migration_Matrix_hfstats1Up->GetBinContent(2,2));
    TH1F *Ttbar_1_hfstats2Up = new TH1F("Ttbar_1_hfstats2Up","",newrec,new_rec);   Ttbar_1_hfstats2Up->SetBinContent(1,Migration_Matrix_hfstats2Up->GetBinContent(1,1)); Ttbar_1_hfstats2Up->SetBinContent(2,Migration_Matrix_hfstats2Up->GetBinContent(2,1));
    TH1F *Ttbar_2_hfstats2Up = new TH1F("Ttbar_2_hfstats2Up","",newrec,new_rec);   Ttbar_2_hfstats2Up->SetBinContent(1,Migration_Matrix_hfstats2Up->GetBinContent(1,2)); Ttbar_2_hfstats2Up->SetBinContent(2,Migration_Matrix_hfstats2Up->GetBinContent(2,2));
    TH1F *Ttbar_1_lfstats1Up = new TH1F("Ttbar_1_lfstats1Up","",newrec,new_rec);   Ttbar_1_lfstats1Up->SetBinContent(1,Migration_Matrix_lfstats1Up->GetBinContent(1,1)); Ttbar_1_lfstats1Up->SetBinContent(2,Migration_Matrix_lfstats1Up->GetBinContent(2,1));
    TH1F *Ttbar_2_lfstats1Up = new TH1F("Ttbar_2_lfstats1Up","",newrec,new_rec);   Ttbar_2_lfstats1Up->SetBinContent(1,Migration_Matrix_lfstats1Up->GetBinContent(1,2)); Ttbar_2_lfstats1Up->SetBinContent(2,Migration_Matrix_lfstats1Up->GetBinContent(2,2));
    TH1F *Ttbar_1_lfstats2Up = new TH1F("Ttbar_1_lfstats2Up","",newrec,new_rec);   Ttbar_1_lfstats2Up->SetBinContent(1,Migration_Matrix_lfstats2Up->GetBinContent(1,1)); Ttbar_1_lfstats2Up->SetBinContent(2,Migration_Matrix_lfstats2Up->GetBinContent(2,1));
    TH1F *Ttbar_2_lfstats2Up = new TH1F("Ttbar_2_lfstats2Up","",newrec,new_rec);   Ttbar_2_lfstats2Up->SetBinContent(1,Migration_Matrix_lfstats2Up->GetBinContent(1,2)); Ttbar_2_lfstats2Up->SetBinContent(2,Migration_Matrix_lfstats2Up->GetBinContent(2,2));
    TH1F *Ttbar_1_jesUp = new TH1F("Ttbar_1_jesUp","",newrec,new_rec);   Ttbar_1_jesUp->SetBinContent(1,Migration_Matrix_jesUp->GetBinContent(1,1)); Ttbar_1_jesUp->SetBinContent(2,Migration_Matrix_jesUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jesUp = new TH1F("Ttbar_2_jesUp","",newrec,new_rec);   Ttbar_2_jesUp->SetBinContent(1,Migration_Matrix_jesUp->GetBinContent(1,2)); Ttbar_2_jesUp->SetBinContent(2,Migration_Matrix_jesUp->GetBinContent(2,2));





    TH1F *Ttbar_1_pileupDown = new TH1F("Ttbar_1_pileupDown","",newrec,new_rec);  Ttbar_1_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,1)); Ttbar_1_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,1));
    TH1F *Ttbar_2_pileupDown = new TH1F("Ttbar_2_pileupDown","",newrec,new_rec);  Ttbar_2_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,2)); Ttbar_2_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,2));
    TH1F *Ttbar_1_eleIDDown = new TH1F("Ttbar_1_eleIDDown","",newrec,new_rec);      Ttbar_1_eleIDDown->SetBinContent(1,Migration_Matrix_eleIDDown->GetBinContent(1,1)); Ttbar_1_eleIDDown->SetBinContent(2,Migration_Matrix_eleIDDown->GetBinContent(2,1));
    TH1F *Ttbar_2_eleIDDown = new TH1F("Ttbar_2_eleIDDown","",newrec,new_rec);      Ttbar_2_eleIDDown->SetBinContent(1,Migration_Matrix_eleIDDown->GetBinContent(1,2)); Ttbar_2_eleIDDown->SetBinContent(2,Migration_Matrix_eleIDDown->GetBinContent(2,2));
    TH1F *Ttbar_1_eleHLTDown = new TH1F("Ttbar_1_eleHLTDown","",newrec,new_rec);    Ttbar_1_eleHLTDown->SetBinContent(1,Migration_Matrix_eleHLTDown->GetBinContent(1,1)); Ttbar_1_eleHLTDown->SetBinContent(2,Migration_Matrix_eleHLTDown->GetBinContent(2,1));
    TH1F *Ttbar_2_eleHLTDown = new TH1F("Ttbar_2_eleHLTDown","",newrec,new_rec);    Ttbar_2_eleHLTDown->SetBinContent(1,Migration_Matrix_eleHLTDown->GetBinContent(1,2)); Ttbar_2_eleHLTDown->SetBinContent(2,Migration_Matrix_eleHLTDown->GetBinContent(2,2));
    TH1F *Ttbar_1_Top_pT_rewDown = new TH1F("Ttbar_1_Top_pT_rewDown","",newrec,new_rec);   Ttbar_1_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,1)); Ttbar_1_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,1));
    TH1F *Ttbar_2_Top_pT_rewDown = new TH1F("Ttbar_2_Top_pT_rewDown","",newrec,new_rec);   Ttbar_2_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,2)); Ttbar_2_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,2));
    TH1F *Ttbar_1_mistagDown = new TH1F("Ttbar_1_mistagDown","",newrec,new_rec);   Ttbar_1_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,1)); Ttbar_1_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,1));
    TH1F *Ttbar_2_mistagDown = new TH1F("Ttbar_2_mistagDown","",newrec,new_rec);   Ttbar_2_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,2)); Ttbar_2_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,2));
    TH1F *Ttbar_1_toptagDown = new TH1F("Ttbar_1_toptagDown","",newrec,new_rec);   Ttbar_1_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,1)); Ttbar_1_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,1));
    TH1F *Ttbar_2_toptagDown = new TH1F("Ttbar_2_toptagDown","",newrec,new_rec);    Ttbar_2_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,2)); Ttbar_2_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,2));
    TH1F *Ttbar_1_ele_recDown = new TH1F("Ttbar_1_ele_recDown","",newrec,new_rec);    Ttbar_1_ele_recDown->SetBinContent(1,Migration_Matrix_ele_recDown->GetBinContent(1,1)); Ttbar_1_ele_recDown->SetBinContent(2,Migration_Matrix_ele_recDown->GetBinContent(2,1));
    TH1F *Ttbar_2_ele_recDown = new TH1F("Ttbar_2_ele_recDown","",newrec,new_rec);    Ttbar_2_ele_recDown->SetBinContent(1,Migration_Matrix_ele_recDown->GetBinContent(1,2)); Ttbar_2_ele_recDown->SetBinContent(2,Migration_Matrix_ele_recDown->GetBinContent(2,2));
    TH1F *Ttbar_1_ISRDown = new TH1F("Ttbar_1_ISRDown","",newrec,new_rec);   Ttbar_1_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,1)); Ttbar_1_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,1));
    TH1F *Ttbar_2_ISRDown = new TH1F("Ttbar_2_ISRDown","",newrec,new_rec);   Ttbar_2_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,2)); Ttbar_2_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,2));
    TH1F *Ttbar_1_FSRDown = new TH1F("Ttbar_1_FSRDown","",newrec,new_rec);    Ttbar_1_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,1)); Ttbar_1_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,1));
    TH1F *Ttbar_2_FSRDown = new TH1F("Ttbar_2_FSRDown","",newrec,new_rec);    Ttbar_2_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,2)); Ttbar_2_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,2));
//    TH1F *Ttbar_1_jecDown = new TH1F("Ttbar_1_jecDown","",newrec,new_rec);    Ttbar_1_jecDown->SetBinContent(1,Migration_Matrix_jecDown->GetBinContent(1,1)); Ttbar_1_jecDown->SetBinContent(2,Migration_Matrix_jecDown->GetBinContent(2,1));
//    TH1F *Ttbar_2_jecDown = new TH1F("Ttbar_2_jecDown","",newrec,new_rec);    Ttbar_2_jecDown->SetBinContent(1,Migration_Matrix_jecDown->GetBinContent(1,2)); Ttbar_2_jecDown->SetBinContent(2,Migration_Matrix_jecDown->GetBinContent(2,2));
//    TH1F *Ttbar_1_jerDown = new TH1F("Ttbar_1_jerDown","",newrec,new_rec);   Ttbar_1_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,1)); Ttbar_1_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,1));
//    TH1F *Ttbar_2_jerDown = new TH1F("Ttbar_2_jerDown","",newrec,new_rec);   Ttbar_2_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,2)); Ttbar_2_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,2));
    TH1F *Ttbar_1_hdampDown = new TH1F("Ttbar_1_hdampDown","",newrec,new_rec);   Ttbar_1_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,1)); Ttbar_1_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,1));
    TH1F *Ttbar_2_hdampDown = new TH1F("Ttbar_2_hdampDown","",newrec,new_rec);   Ttbar_2_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,2)); Ttbar_2_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,2));
    TH1F *Ttbar_1_cferr1Down = new TH1F("Ttbar_1_cferr1Down","",newrec,new_rec);   Ttbar_1_cferr1Down->SetBinContent(1,Migration_Matrix_cferr1Down->GetBinContent(1,1)); Ttbar_1_cferr1Down->SetBinContent(2,Migration_Matrix_cferr1Down->GetBinContent(2,1));
    TH1F *Ttbar_2_cferr1Down = new TH1F("Ttbar_2_cferr1Down","",newrec,new_rec);   Ttbar_2_cferr1Down->SetBinContent(1,Migration_Matrix_cferr1Down->GetBinContent(1,2)); Ttbar_2_cferr1Down->SetBinContent(2,Migration_Matrix_cferr1Down->GetBinContent(2,2));
    TH1F *Ttbar_1_cferr2Down = new TH1F("Ttbar_1_cferr2Down","",newrec,new_rec);   Ttbar_1_cferr2Down->SetBinContent(1,Migration_Matrix_cferr2Down->GetBinContent(1,1)); Ttbar_1_cferr2Down->SetBinContent(2,Migration_Matrix_cferr2Down->GetBinContent(2,1));
    TH1F *Ttbar_2_cferr2Down = new TH1F("Ttbar_2_cferr2Down","",newrec,new_rec);   Ttbar_2_cferr2Down->SetBinContent(1,Migration_Matrix_cferr2Down->GetBinContent(1,2)); Ttbar_2_cferr2Down->SetBinContent(2,Migration_Matrix_cferr2Down->GetBinContent(2,2));
    TH1F *Ttbar_1_hfDown = new TH1F("Ttbar_1_hfDown","",newrec,new_rec);   Ttbar_1_hfDown->SetBinContent(1,Migration_Matrix_hfDown->GetBinContent(1,1)); Ttbar_1_hfDown->SetBinContent(2,Migration_Matrix_hfDown->GetBinContent(2,1));
    TH1F *Ttbar_2_hfDown = new TH1F("Ttbar_2_hfDown","",newrec,new_rec);   Ttbar_2_hfDown->SetBinContent(1,Migration_Matrix_hfDown->GetBinContent(1,2)); Ttbar_2_hfDown->SetBinContent(2,Migration_Matrix_hfDown->GetBinContent(2,2));
    TH1F *Ttbar_1_lfDown = new TH1F("Ttbar_1_lfDown","",newrec,new_rec);   Ttbar_1_lfDown->SetBinContent(1,Migration_Matrix_lfDown->GetBinContent(1,1)); Ttbar_1_lfDown->SetBinContent(2,Migration_Matrix_lfDown->GetBinContent(2,1));
    TH1F *Ttbar_2_lfDown = new TH1F("Ttbar_2_lfDown","",newrec,new_rec);   Ttbar_2_lfDown->SetBinContent(1,Migration_Matrix_lfDown->GetBinContent(1,2)); Ttbar_2_lfDown->SetBinContent(2,Migration_Matrix_lfDown->GetBinContent(2,2));
    TH1F *Ttbar_1_hfstats1Down = new TH1F("Ttbar_1_hfstats1Down","",newrec,new_rec);   Ttbar_1_hfstats1Down->SetBinContent(1,Migration_Matrix_hfstats1Down->GetBinContent(1,1)); Ttbar_1_hfstats1Down->SetBinContent(2,Migration_Matrix_hfstats1Down->GetBinContent(2,1));
    TH1F *Ttbar_2_hfstats1Down = new TH1F("Ttbar_2_hfstats1Down","",newrec,new_rec);   Ttbar_2_hfstats1Down->SetBinContent(1,Migration_Matrix_hfstats1Down->GetBinContent(1,2)); Ttbar_2_hfstats1Down->SetBinContent(2,Migration_Matrix_hfstats1Down->GetBinContent(2,2));
    TH1F *Ttbar_1_hfstats2Down = new TH1F("Ttbar_1_hfstats2Down","",newrec,new_rec);   Ttbar_1_hfstats2Down->SetBinContent(1,Migration_Matrix_hfstats2Down->GetBinContent(1,1)); Ttbar_1_hfstats2Down->SetBinContent(2,Migration_Matrix_hfstats2Down->GetBinContent(2,1));
    TH1F *Ttbar_2_hfstats2Down = new TH1F("Ttbar_2_hfstats2Down","",newrec,new_rec);   Ttbar_2_hfstats2Down->SetBinContent(1,Migration_Matrix_hfstats2Down->GetBinContent(1,2)); Ttbar_2_hfstats2Down->SetBinContent(2,Migration_Matrix_hfstats2Down->GetBinContent(2,2));
    TH1F *Ttbar_1_lfstats1Down = new TH1F("Ttbar_1_lfstats1Down","",newrec,new_rec);   Ttbar_1_lfstats1Down->SetBinContent(1,Migration_Matrix_lfstats1Down->GetBinContent(1,1)); Ttbar_1_lfstats1Down->SetBinContent(2,Migration_Matrix_lfstats1Down->GetBinContent(2,1));
    TH1F *Ttbar_2_lfstats1Down = new TH1F("Ttbar_2_lfstats1Down","",newrec,new_rec);   Ttbar_2_lfstats1Down->SetBinContent(1,Migration_Matrix_lfstats1Down->GetBinContent(1,2)); Ttbar_2_lfstats1Down->SetBinContent(2,Migration_Matrix_lfstats1Down->GetBinContent(2,2));
    TH1F *Ttbar_1_lfstats2Down = new TH1F("Ttbar_1_lfstats2Down","",newrec,new_rec);   Ttbar_1_lfstats2Down->SetBinContent(1,Migration_Matrix_lfstats2Down->GetBinContent(1,1)); Ttbar_1_lfstats2Down->SetBinContent(2,Migration_Matrix_lfstats2Down->GetBinContent(2,1));
    TH1F *Ttbar_2_lfstats2Down = new TH1F("Ttbar_2_lfstats2Down","",newrec,new_rec);   Ttbar_2_lfstats2Down->SetBinContent(1,Migration_Matrix_lfstats2Down->GetBinContent(1,2)); Ttbar_2_lfstats2Down->SetBinContent(2,Migration_Matrix_lfstats2Down->GetBinContent(2,2));
    TH1F *Ttbar_1_jesDown = new TH1F("Ttbar_1_jesDown","",newrec,new_rec);   Ttbar_1_jesDown->SetBinContent(1,Migration_Matrix_jesDown->GetBinContent(1,1)); Ttbar_1_jesDown->SetBinContent(2,Migration_Matrix_jesDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jesDown = new TH1F("Ttbar_2_jesDown","",newrec,new_rec);   Ttbar_2_jesDown->SetBinContent(1,Migration_Matrix_jesDown->GetBinContent(1,2)); Ttbar_2_jesDown->SetBinContent(2,Migration_Matrix_jesDown->GetBinContent(2,2));


TFile out("Input_undfolding_data_.root","recreate");


Ttbar_1_nominal->Write();
Ttbar_2_nominal->Write();

Ttbar_1_pileupUp->Write();
Ttbar_2_pileupUp->Write();
Ttbar_1_eleIDUp->Write();
Ttbar_2_eleIDUp->Write();
Ttbar_1_eleHLTUp->Write();
Ttbar_2_eleHLTUp->Write();
Ttbar_1_Top_pT_rewUp->Write();
Ttbar_2_Top_pT_rewUp->Write();
Ttbar_1_mistagUp->Write();
Ttbar_2_mistagUp->Write();
Ttbar_1_toptagUp->Write();
Ttbar_2_toptagUp->Write();
Ttbar_1_ele_recUp->Write();
Ttbar_2_ele_recUp->Write();
Ttbar_1_ISRUp->Write();
Ttbar_2_ISRUp->Write();
Ttbar_1_FSRUp->Write();
Ttbar_2_FSRUp->Write();
//Ttbar_1_jecUp->Write();
//Ttbar_2_jecUp->Write();
//Ttbar_1_jerUp->Write();
//Ttbar_2_jerUp->Write();
Ttbar_1_hdampUp->Write();
Ttbar_2_hdampUp->Write();

Ttbar_1_cferr1Up->Write();
Ttbar_2_cferr1Up->Write();
Ttbar_1_cferr2Up->Write();
Ttbar_2_cferr2Up->Write();
Ttbar_1_hfUp->Write();
Ttbar_2_hfUp->Write();
Ttbar_1_lfUp->Write();
Ttbar_2_lfUp->Write();
Ttbar_1_hfstats1Up->Write();
Ttbar_2_hfstats1Up->Write();
Ttbar_1_hfstats2Up->Write();
Ttbar_2_hfstats2Up->Write();
Ttbar_1_lfstats1Up->Write();
Ttbar_2_lfstats1Up->Write();
Ttbar_1_lfstats2Up->Write();
Ttbar_2_lfstats2Up->Write();
Ttbar_1_jesUp->Write();
Ttbar_2_jesUp->Write();

Ttbar_1_pileupDown->Write();
Ttbar_2_pileupDown->Write();
Ttbar_1_eleIDDown->Write();
Ttbar_2_eleIDDown->Write();
Ttbar_1_eleHLTDown->Write();
Ttbar_2_eleHLTDown->Write();
Ttbar_1_Top_pT_rewDown->Write();
Ttbar_2_Top_pT_rewDown->Write();
Ttbar_1_mistagDown->Write();
Ttbar_2_mistagDown->Write();
Ttbar_1_toptagDown->Write();
Ttbar_2_toptagDown->Write();
Ttbar_1_ele_recDown->Write();
Ttbar_2_ele_recDown->Write();
Ttbar_1_ISRDown->Write();
Ttbar_2_ISRDown->Write();
Ttbar_1_FSRDown->Write();
Ttbar_2_FSRDown->Write();
//Ttbar_1_jecDown->Write();
//Ttbar_2_jecDown->Write();
//Ttbar_1_jerDown->Write();
//Ttbar_2_jerDown->Write();
Ttbar_1_hdampDown->Write();
Ttbar_2_hdampDown->Write();

Ttbar_1_cferr1Down->Write();
Ttbar_2_cferr1Down->Write();
Ttbar_1_cferr2Down->Write();
Ttbar_2_cferr2Down->Write();
Ttbar_1_hfDown->Write();
Ttbar_2_hfDown->Write();
Ttbar_1_lfDown->Write();
Ttbar_2_lfDown->Write();
Ttbar_1_hfstats1Down->Write();
Ttbar_2_hfstats1Down->Write();
Ttbar_1_hfstats2Down->Write();
Ttbar_2_hfstats2Down->Write();
Ttbar_1_lfstats1Down->Write();
Ttbar_2_lfstats1Down->Write();
Ttbar_1_lfstats2Down->Write();
Ttbar_2_lfstats2Down->Write();
Ttbar_1_jesDown->Write();
Ttbar_2_jesDown->Write();
 
   auto c1    = new TCanvas("c1","c1",600,400);
   c1->cd();
   Migration_Matrix->GetYaxis()->SetTitle("#Delta #cbar y_{gen} #cbar");   
   Migration_Matrix->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
   Migration_Matrix->Draw("COLZ");

   TLatex latex;
   latex.SetTextSize(0.045);
   latex.SetTextAlign(11);  //align at top
   latex.DrawLatex(-1.9,2.05,"CMS preliminary");

   TLatex latex2;
   latex2.SetTextSize(0.045);
   latex2.SetTextAlign(11);  //align at top
   latex2.DrawLatex(0.9,2.05,"36.77 fb^{-1} (13 TeV)");

   c1->Print("Migration_Matrix.pdf");

    TH2F *Stability_Matrix = new TH2F("Stability_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);

   for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
            Stability_Matrix->SetBinContent(a,b,Migration_Matrix->GetBinContent(a,b)/Migration_Matrix->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinContent(a,b,Migration_Matrix->GetBinContent(a,b)/Migration_Matrix->Integral(a,a,1,binnum_gen));
            Stability_Matrix->SetBinError(a,b,Migration_Matrix->GetBinError(a,b)/Migration_Matrix->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinError(a,b,Migration_Matrix->GetBinError(a,b)/Migration_Matrix->Integral(a,a,1,binnum_gen));
       }
   }

// Purity && Stability

   TH1F *Stability = new TH1F("Stability","",binnum_gen,bins_gen);
   TH1F *Purity = new TH1F("Purity","",binnum_gen,bins_gen);

   for(Int_t m=1;m<=binnum_gen;m++){
       Stability->SetBinContent(m,Stability_Matrix->GetBinContent(m,m));
       Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
       Stability->SetBinError(m,Stability_Matrix->GetBinError(m,m));
       Purity->SetBinError(m,Purity_Matrix->GetBinError(m,m));
   }

   Stability->GetYaxis()->SetRangeUser(0,1);
   Stability->GetYaxis()->SetTitle("P&S");
   Stability->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
   Purity->SetLineColor(kRed);
   Purity->SetLineWidth(2);
   Stability->SetLineColor(kBlue);
   Stability->SetLineWidth(2);

   TCanvas* cc = new TCanvas("cc","",2400,1200);
   cc->Divide(1,1);
   cc->cd(1);
   Stability->Draw("samei e");
   Purity->Draw("same e");

   Float_t a = Stability->GetMaximum();

   TLegend leg(.55, .55, .75, .75, "");
   leg.SetFillColor(0);
   leg.AddEntry(Purity, "Purity");
   leg.AddEntry(Stability, "Stability");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   TLatex latex3;
   latex3.SetTextSize(0.045);
   latex3.SetTextAlign(11);
   latex3.DrawLatex(-1.9,1.02,"CMS preliminary");

   TLatex latex4;
   latex4.SetTextSize(0.045);
   latex4.SetTextAlign(11);
   latex4.DrawLatex(1.1,1.02,"36.77 fb^{-1} (13 TeV)");

   cc->Print("PS.pdf");

   TMatrix H(2,2);
   for (Int_t irow = 0; irow < 2; irow++){
   for (Int_t icol = 0; icol < 2; icol++){
      H[icol][irow] = Migration_Matrix->GetBinContent(irow+1,icol+1);
   }
   }
   cout << H.Determinant() << endl;

   TVectorD rowsum(2);
   TVectorD fSig(2);
   for (Int_t irow = 0; irow < 2; irow++){
   for (Int_t icol = 0; icol < 2; icol++){
   rowsum(irow-1) += H(irow,icol);
   }
   }
   TDecompSVD lu(H);
   TVectorD sig = lu.GetSig();
   for (Int_t irow = 0; irow < 2; irow++){
    cout << sig[irow] << endl;
   }
 
}


