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

void all_unfolding_data_900(string var_name = "", string var_gen = "", string region = "", string year = "2016")
{

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    //jec_TimeptEta
    TChain *chreco_ttbar_semi_jecTimePtEtaup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecTimePtEtaup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_muon_CHS_JECup_Timepteta/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecTimePtEtaup = (TTree*) chreco_ttbar_semi_jecTimePtEtaup;

    TChain *chreco_ttbar_semi_jecTimePtEtadown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecTimePtEtadown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_muon_CHS_JECdown_Timepteta/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecTimePtEtadown = (TTree*) chreco_ttbar_semi_jecTimePtEtadown;

    //jer
    TChain *chreco_ttbar_semi_jerup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jerup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_muon_CHS_JERup/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jerup = (TTree*) chreco_ttbar_semi_jerup;

    TChain *chreco_ttbar_semi_jerdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jerdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_muon_CHS_JERdown/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jerdown = (TTree*) chreco_ttbar_semi_jerdown;

    //hdamp

    TChain *chreco_ttbar_semi_hdampup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/hdamp_up/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi_hdampup = (TTree*) chreco_ttbar_semi_hdampup;

    TChain *chreco_ttbar_semi_hdampdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/hdamp_down/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree",year.c_str()));
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
    TH2F *Migration_Matrix_muIDUp = new TH2F("Migration_Matrix_muIDUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTUp = new TH2F("Migration_Matrix_muHLTUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewUp = new TH2F("Migration_Matrix_Top_pT_rewUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagUp = new TH2F("Migration_Matrix_mistagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagUp = new TH2F("Migration_Matrix_toptagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recUp = new TH2F("Migration_Matrix_muon_recUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRUp = new TH2F("Migration_Matrix_ISRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRUp = new TH2F("Migration_Matrix_FSRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecTimePtEtaUp = new TH2F("Migration_Matrix_jecTimePtEtaUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jerUp = new TH2F("Migration_Matrix_jerUp","",newrec,new_rec,binnum_gen,bins_gen);
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
    TH2F *Migration_Matrix_muIDDown = new TH2F("Migration_Matrix_muIDDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTDown = new TH2F("Migration_Matrix_muHLTDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewDown = new TH2F("Migration_Matrix_Top_pT_rewDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagDown = new TH2F("Migration_Matrix_mistagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagDown = new TH2F("Migration_Matrix_toptagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recDown = new TH2F("Migration_Matrix_muon_recDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRDown = new TH2F("Migration_Matrix_ISRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRDown = new TH2F("Migration_Matrix_FSRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecTimePtEtaDown = new TH2F("Migration_Matrix_jecTimePtEtaDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jerDown = new TH2F("Migration_Matrix_jerDown","",newrec,new_rec,binnum_gen,bins_gen);
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

    string Mttbar_gen = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";

    string Mttbar_cut = Form("(%s > 900 && Mttbar < 900)",Mttbar_gen.c_str());

    string  pileupUp = Form("(weight_sfmu_HighPtID)*(weight_pu_up)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  pileupDown = Form("(weight_sfmu_HighPtID)*(weight_pu_down)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muIDUp = Form("(weight_sfmu_HighPtID_up)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muIDDown = Form("(weight_sfmu_HighPtID_down)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muHLTUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muHLTDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  cferr1Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1up)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  cferr1Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  cferr2Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2up)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  cferr2Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfup)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfdown)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfstats1Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfstats1Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfstats2Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hfstats2Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  jesUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesup)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  jesDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesdown)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfup)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfdown)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfstats1Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1up)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfstats1Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfstats2Up = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2up)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  lfstats2Down = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2down)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  Top_pT_rewUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  Top_pT_rewDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_down_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  mistagUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  mistagDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  toptagUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  toptagDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muon_recUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_up)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  muon_recDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_down)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  HTUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT_up)*%s",Mttbar_cut.c_str());
    string  HTDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT_down)*%s",Mttbar_cut.c_str());
    string  ISRUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*ISRup*%s",Mttbar_cut.c_str());
    string  ISRDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*ISRdown*%s",Mttbar_cut.c_str());
    string  FSRUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*FSRup*%s",Mttbar_cut.c_str());
    string  FSRDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*FSRdown*%s",Mttbar_cut.c_str());
    string  jecTimePtEtaUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  jecTimePtEtaDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  jerUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  jerDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hdampUp = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());
    string  hdampDown = Form("(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*%s",Mttbar_cut.c_str());

    Float_t mistag_nominal = 0.86;

    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750)*%f",mistag_nominal);

//Matrices
    treereco_ttbar_semi->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_MuonTrigger*weight_pu*weight_toptagSF_*weight_pt_rew_nolimit*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)*%s",selcuts_boosted_central.c_str(),Mttbar_cut.c_str()));

    treereco_ttbar_semi->Project("Migration_Matrix_pileupUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muIDUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecTimePtEtaup->Project("Migration_Matrix_jecTimePtEtaUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecTimePtEtaUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jerup->Project("Migration_Matrix_jerUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerUp.c_str(),selcuts_boosted_central.c_str()));
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
    treereco_ttbar_semi->Project("Migration_Matrix_muIDDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecTimePtEtadown->Project("Migration_Matrix_jecTimePtEtaDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecTimePtEtaDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jerdown->Project("Migration_Matrix_jerDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerDown.c_str(),selcuts_boosted_central.c_str()));
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


    TH1F *Ttbar_3_nominal = new TH1F("Ttbar_3_nominal","",binnum_gen,bins_gen);   Ttbar_3_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,1)); Ttbar_3_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,1));
    TH1F *Ttbar_4_nominal = new TH1F("Ttbar_4_nominal","",binnum_gen,bins_gen);   Ttbar_4_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,2)); Ttbar_4_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,2));
 
    TH1F *Ttbar_3_pileupUp = new TH1F("Ttbar_3_pileupUp","",newrec,new_rec);  Ttbar_3_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,1)); Ttbar_3_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,1));
    TH1F *Ttbar_4_pileupUp = new TH1F("Ttbar_4_pileupUp","",newrec,new_rec);  Ttbar_4_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,2)); Ttbar_4_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,2));
    TH1F *Ttbar_3_muIDUp = new TH1F("Ttbar_3_muIDUp","",newrec,new_rec);      Ttbar_3_muIDUp->SetBinContent(1,Migration_Matrix_muIDUp->GetBinContent(1,1)); Ttbar_3_muIDUp->SetBinContent(2,Migration_Matrix_muIDUp->GetBinContent(2,1));
    TH1F *Ttbar_4_muIDUp = new TH1F("Ttbar_4_muIDUp","",newrec,new_rec);      Ttbar_4_muIDUp->SetBinContent(1,Migration_Matrix_muIDUp->GetBinContent(1,2)); Ttbar_4_muIDUp->SetBinContent(2,Migration_Matrix_muIDUp->GetBinContent(2,2));
    TH1F *Ttbar_3_muHLTUp = new TH1F("Ttbar_3_muHLTUp","",newrec,new_rec);    Ttbar_3_muHLTUp->SetBinContent(1,Migration_Matrix_muHLTUp->GetBinContent(1,1)); Ttbar_3_muHLTUp->SetBinContent(2,Migration_Matrix_muHLTUp->GetBinContent(2,1));
    TH1F *Ttbar_4_muHLTUp = new TH1F("Ttbar_4_muHLTUp","",newrec,new_rec);    Ttbar_4_muHLTUp->SetBinContent(1,Migration_Matrix_muHLTUp->GetBinContent(1,2)); Ttbar_4_muHLTUp->SetBinContent(2,Migration_Matrix_muHLTUp->GetBinContent(2,2));
    TH1F *Ttbar_3_Top_pT_rewUp = new TH1F("Ttbar_3_Top_pT_rewUp","",newrec,new_rec);   Ttbar_3_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,1)); Ttbar_3_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,1));
    TH1F *Ttbar_4_Top_pT_rewUp = new TH1F("Ttbar_4_Top_pT_rewUp","",newrec,new_rec);   Ttbar_4_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,2)); Ttbar_4_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,2)); 
    TH1F *Ttbar_3_mistagUp = new TH1F("Ttbar_3_mistagUp","",newrec,new_rec);   Ttbar_3_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,1)); Ttbar_3_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,1));
    TH1F *Ttbar_4_mistagUp = new TH1F("Ttbar_4_mistagUp","",newrec,new_rec);   Ttbar_4_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,2)); Ttbar_4_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,2));
    TH1F *Ttbar_3_toptagUp = new TH1F("Ttbar_3_toptagUp","",newrec,new_rec);   Ttbar_3_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,1)); Ttbar_3_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,1));
    TH1F *Ttbar_4_toptagUp = new TH1F("Ttbar_4_toptagUp","",newrec,new_rec);    Ttbar_4_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,2)); Ttbar_4_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,2));
    TH1F *Ttbar_3_muon_recUp = new TH1F("Ttbar_3_muon_recUp","",newrec,new_rec);    Ttbar_3_muon_recUp->SetBinContent(1,Migration_Matrix_muon_recUp->GetBinContent(1,1)); Ttbar_3_muon_recUp->SetBinContent(2,Migration_Matrix_muon_recUp->GetBinContent(2,1));
    TH1F *Ttbar_4_muon_recUp = new TH1F("Ttbar_4_muon_recUp","",newrec,new_rec);    Ttbar_4_muon_recUp->SetBinContent(1,Migration_Matrix_muon_recUp->GetBinContent(1,2)); Ttbar_4_muon_recUp->SetBinContent(2,Migration_Matrix_muon_recUp->GetBinContent(2,2));
    TH1F *Ttbar_3_ISRUp = new TH1F("Ttbar_3_ISRUp","",newrec,new_rec);   Ttbar_3_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,1)); Ttbar_3_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,1));
    TH1F *Ttbar_4_ISRUp = new TH1F("Ttbar_4_ISRUp","",newrec,new_rec);   Ttbar_4_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,2)); Ttbar_4_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,2));
    TH1F *Ttbar_3_FSRUp = new TH1F("Ttbar_3_FSRUp","",newrec,new_rec);    Ttbar_3_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,1)); Ttbar_3_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,1));
    TH1F *Ttbar_4_FSRUp = new TH1F("Ttbar_4_FSRUp","",newrec,new_rec);    Ttbar_4_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,2)); Ttbar_4_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,2));
    TH1F *Ttbar_3_jecTimePtEtaUp = new TH1F("Ttbar_3_jecTimePtEtaUp","",newrec,new_rec);    Ttbar_3_jecTimePtEtaUp->SetBinContent(1,Migration_Matrix_jecTimePtEtaUp->GetBinContent(1,1)); Ttbar_3_jecTimePtEtaUp->SetBinContent(2,Migration_Matrix_jecTimePtEtaUp->GetBinContent(2,1));
    TH1F *Ttbar_4_jecTimePtEtaUp = new TH1F("Ttbar_4_jecTimePtEtaUp","",newrec,new_rec);    Ttbar_4_jecTimePtEtaUp->SetBinContent(1,Migration_Matrix_jecTimePtEtaUp->GetBinContent(1,2)); Ttbar_4_jecTimePtEtaUp->SetBinContent(2,Migration_Matrix_jecTimePtEtaUp->GetBinContent(2,2));
    TH1F *Ttbar_3_jerUp = new TH1F("Ttbar_3_jerUp","",newrec,new_rec);   Ttbar_3_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,1)); Ttbar_3_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,1));
    TH1F *Ttbar_4_jerUp = new TH1F("Ttbar_4_jerUp","",newrec,new_rec);   Ttbar_4_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,2)); Ttbar_4_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,2));
    TH1F *Ttbar_3_hdampUp = new TH1F("Ttbar_3_hdampUp","",newrec,new_rec);   Ttbar_3_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,1)); Ttbar_3_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,1));
    TH1F *Ttbar_4_hdampUp = new TH1F("Ttbar_4_hdampUp","",newrec,new_rec);   Ttbar_4_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,2)); Ttbar_4_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,2));
    TH1F *Ttbar_3_cferr1Up = new TH1F("Ttbar_3_cferr1Up","",newrec,new_rec);   Ttbar_3_cferr1Up->SetBinContent(1,Migration_Matrix_cferr1Up->GetBinContent(1,1)); Ttbar_3_cferr1Up->SetBinContent(2,Migration_Matrix_cferr1Up->GetBinContent(2,1));
    TH1F *Ttbar_4_cferr1Up = new TH1F("Ttbar_4_cferr1Up","",newrec,new_rec);   Ttbar_4_cferr1Up->SetBinContent(1,Migration_Matrix_cferr1Up->GetBinContent(1,2)); Ttbar_4_cferr1Up->SetBinContent(2,Migration_Matrix_cferr1Up->GetBinContent(2,2));
    TH1F *Ttbar_3_cferr2Up = new TH1F("Ttbar_3_cferr2Up","",newrec,new_rec);   Ttbar_3_cferr2Up->SetBinContent(1,Migration_Matrix_cferr2Up->GetBinContent(1,1)); Ttbar_3_cferr2Up->SetBinContent(2,Migration_Matrix_cferr2Up->GetBinContent(2,1));
    TH1F *Ttbar_4_cferr2Up = new TH1F("Ttbar_4_cferr2Up","",newrec,new_rec);   Ttbar_4_cferr2Up->SetBinContent(1,Migration_Matrix_cferr2Up->GetBinContent(1,2)); Ttbar_4_cferr2Up->SetBinContent(2,Migration_Matrix_cferr2Up->GetBinContent(2,2));
    TH1F *Ttbar_3_hfUp = new TH1F("Ttbar_3_hfUp","",newrec,new_rec);   Ttbar_3_hfUp->SetBinContent(1,Migration_Matrix_hfUp->GetBinContent(1,1)); Ttbar_3_hfUp->SetBinContent(2,Migration_Matrix_hfUp->GetBinContent(2,1));
    TH1F *Ttbar_4_hfUp = new TH1F("Ttbar_4_hfUp","",newrec,new_rec);   Ttbar_4_hfUp->SetBinContent(1,Migration_Matrix_hfUp->GetBinContent(1,2)); Ttbar_4_hfUp->SetBinContent(2,Migration_Matrix_hfUp->GetBinContent(2,2));
    TH1F *Ttbar_3_lfUp = new TH1F("Ttbar_3_lfUp","",newrec,new_rec);   Ttbar_3_lfUp->SetBinContent(1,Migration_Matrix_lfUp->GetBinContent(1,1)); Ttbar_3_lfUp->SetBinContent(2,Migration_Matrix_lfUp->GetBinContent(2,1));
    TH1F *Ttbar_4_lfUp = new TH1F("Ttbar_4_lfUp","",newrec,new_rec);   Ttbar_4_lfUp->SetBinContent(1,Migration_Matrix_lfUp->GetBinContent(1,2)); Ttbar_4_lfUp->SetBinContent(2,Migration_Matrix_lfUp->GetBinContent(2,2));
    TH1F *Ttbar_3_hfstats1Up = new TH1F("Ttbar_3_hfstats1Up","",newrec,new_rec);   Ttbar_3_hfstats1Up->SetBinContent(1,Migration_Matrix_hfstats1Up->GetBinContent(1,1)); Ttbar_3_hfstats1Up->SetBinContent(2,Migration_Matrix_hfstats1Up->GetBinContent(2,1));
    TH1F *Ttbar_4_hfstats1Up = new TH1F("Ttbar_4_hfstats1Up","",newrec,new_rec);   Ttbar_4_hfstats1Up->SetBinContent(1,Migration_Matrix_hfstats1Up->GetBinContent(1,2)); Ttbar_4_hfstats1Up->SetBinContent(2,Migration_Matrix_hfstats1Up->GetBinContent(2,2));
    TH1F *Ttbar_3_hfstats2Up = new TH1F("Ttbar_3_hfstats2Up","",newrec,new_rec);   Ttbar_3_hfstats2Up->SetBinContent(1,Migration_Matrix_hfstats2Up->GetBinContent(1,1)); Ttbar_3_hfstats2Up->SetBinContent(2,Migration_Matrix_hfstats2Up->GetBinContent(2,1));
    TH1F *Ttbar_4_hfstats2Up = new TH1F("Ttbar_4_hfstats2Up","",newrec,new_rec);   Ttbar_4_hfstats2Up->SetBinContent(1,Migration_Matrix_hfstats2Up->GetBinContent(1,2)); Ttbar_4_hfstats2Up->SetBinContent(2,Migration_Matrix_hfstats2Up->GetBinContent(2,2));
    TH1F *Ttbar_3_lfstats1Up = new TH1F("Ttbar_3_lfstats1Up","",newrec,new_rec);   Ttbar_3_lfstats1Up->SetBinContent(1,Migration_Matrix_lfstats1Up->GetBinContent(1,1)); Ttbar_3_lfstats1Up->SetBinContent(2,Migration_Matrix_lfstats1Up->GetBinContent(2,1));
    TH1F *Ttbar_4_lfstats1Up = new TH1F("Ttbar_4_lfstats1Up","",newrec,new_rec);   Ttbar_4_lfstats1Up->SetBinContent(1,Migration_Matrix_lfstats1Up->GetBinContent(1,2)); Ttbar_4_lfstats1Up->SetBinContent(2,Migration_Matrix_lfstats1Up->GetBinContent(2,2));
    TH1F *Ttbar_3_lfstats2Up = new TH1F("Ttbar_3_lfstats2Up","",newrec,new_rec);   Ttbar_3_lfstats2Up->SetBinContent(1,Migration_Matrix_lfstats2Up->GetBinContent(1,1)); Ttbar_3_lfstats2Up->SetBinContent(2,Migration_Matrix_lfstats2Up->GetBinContent(2,1));
    TH1F *Ttbar_4_lfstats2Up = new TH1F("Ttbar_4_lfstats2Up","",newrec,new_rec);   Ttbar_4_lfstats2Up->SetBinContent(1,Migration_Matrix_lfstats2Up->GetBinContent(1,2)); Ttbar_4_lfstats2Up->SetBinContent(2,Migration_Matrix_lfstats2Up->GetBinContent(2,2));
    TH1F *Ttbar_3_jesUp = new TH1F("Ttbar_3_jesUp","",newrec,new_rec);   Ttbar_3_jesUp->SetBinContent(1,Migration_Matrix_jesUp->GetBinContent(1,1)); Ttbar_3_jesUp->SetBinContent(2,Migration_Matrix_jesUp->GetBinContent(2,1));
    TH1F *Ttbar_4_jesUp = new TH1F("Ttbar_4_jesUp","",newrec,new_rec);   Ttbar_4_jesUp->SetBinContent(1,Migration_Matrix_jesUp->GetBinContent(1,2)); Ttbar_4_jesUp->SetBinContent(2,Migration_Matrix_jesUp->GetBinContent(2,2));





    TH1F *Ttbar_3_pileupDown = new TH1F("Ttbar_3_pileupDown","",newrec,new_rec);  Ttbar_3_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,1)); Ttbar_3_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,1));
    TH1F *Ttbar_4_pileupDown = new TH1F("Ttbar_4_pileupDown","",newrec,new_rec);  Ttbar_4_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,2)); Ttbar_4_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,2));
    TH1F *Ttbar_3_muIDDown = new TH1F("Ttbar_3_muIDDown","",newrec,new_rec);      Ttbar_3_muIDDown->SetBinContent(1,Migration_Matrix_muIDDown->GetBinContent(1,1)); Ttbar_3_muIDDown->SetBinContent(2,Migration_Matrix_muIDDown->GetBinContent(2,1));
    TH1F *Ttbar_4_muIDDown = new TH1F("Ttbar_4_muIDDown","",newrec,new_rec);      Ttbar_4_muIDDown->SetBinContent(1,Migration_Matrix_muIDDown->GetBinContent(1,2)); Ttbar_4_muIDDown->SetBinContent(2,Migration_Matrix_muIDDown->GetBinContent(2,2));
    TH1F *Ttbar_3_muHLTDown = new TH1F("Ttbar_3_muHLTDown","",newrec,new_rec);    Ttbar_3_muHLTDown->SetBinContent(1,Migration_Matrix_muHLTDown->GetBinContent(1,1)); Ttbar_3_muHLTDown->SetBinContent(2,Migration_Matrix_muHLTDown->GetBinContent(2,1));
    TH1F *Ttbar_4_muHLTDown = new TH1F("Ttbar_4_muHLTDown","",newrec,new_rec);    Ttbar_4_muHLTDown->SetBinContent(1,Migration_Matrix_muHLTDown->GetBinContent(1,2)); Ttbar_4_muHLTDown->SetBinContent(2,Migration_Matrix_muHLTDown->GetBinContent(2,2));
    TH1F *Ttbar_3_Top_pT_rewDown = new TH1F("Ttbar_3_Top_pT_rewDown","",newrec,new_rec);   Ttbar_3_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,1)); Ttbar_3_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,1));
    TH1F *Ttbar_4_Top_pT_rewDown = new TH1F("Ttbar_4_Top_pT_rewDown","",newrec,new_rec);   Ttbar_4_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,2)); Ttbar_4_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,2));
    TH1F *Ttbar_3_mistagDown = new TH1F("Ttbar_3_mistagDown","",newrec,new_rec);   Ttbar_3_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,1)); Ttbar_3_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,1));
    TH1F *Ttbar_4_mistagDown = new TH1F("Ttbar_4_mistagDown","",newrec,new_rec);   Ttbar_4_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,2)); Ttbar_4_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,2));
    TH1F *Ttbar_3_toptagDown = new TH1F("Ttbar_3_toptagDown","",newrec,new_rec);   Ttbar_3_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,1)); Ttbar_3_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,1));
    TH1F *Ttbar_4_toptagDown = new TH1F("Ttbar_4_toptagDown","",newrec,new_rec);    Ttbar_4_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,2)); Ttbar_4_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,2));
    TH1F *Ttbar_3_muon_recDown = new TH1F("Ttbar_3_muon_recDown","",newrec,new_rec);    Ttbar_3_muon_recDown->SetBinContent(1,Migration_Matrix_muon_recDown->GetBinContent(1,1)); Ttbar_3_muon_recDown->SetBinContent(2,Migration_Matrix_muon_recDown->GetBinContent(2,1));
    TH1F *Ttbar_4_muon_recDown = new TH1F("Ttbar_4_muon_recDown","",newrec,new_rec);    Ttbar_4_muon_recDown->SetBinContent(1,Migration_Matrix_muon_recDown->GetBinContent(1,2)); Ttbar_4_muon_recDown->SetBinContent(2,Migration_Matrix_muon_recDown->GetBinContent(2,2));
    TH1F *Ttbar_3_ISRDown = new TH1F("Ttbar_3_ISRDown","",newrec,new_rec);   Ttbar_3_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,1)); Ttbar_3_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,1));
    TH1F *Ttbar_4_ISRDown = new TH1F("Ttbar_4_ISRDown","",newrec,new_rec);   Ttbar_4_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,2)); Ttbar_4_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,2));
    TH1F *Ttbar_3_FSRDown = new TH1F("Ttbar_3_FSRDown","",newrec,new_rec);    Ttbar_3_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,1)); Ttbar_3_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,1));
    TH1F *Ttbar_4_FSRDown = new TH1F("Ttbar_4_FSRDown","",newrec,new_rec);    Ttbar_4_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,2)); Ttbar_4_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,2));
    TH1F *Ttbar_3_jecTimePtEtaDown = new TH1F("Ttbar_3_jecTimePtEtaDown","",newrec,new_rec);    Ttbar_3_jecTimePtEtaDown->SetBinContent(1,Migration_Matrix_jecTimePtEtaDown->GetBinContent(1,1)); Ttbar_3_jecTimePtEtaDown->SetBinContent(2,Migration_Matrix_jecTimePtEtaDown->GetBinContent(2,1));
    TH1F *Ttbar_4_jecTimePtEtaDown = new TH1F("Ttbar_4_jecTimePtEtaDown","",newrec,new_rec);    Ttbar_4_jecTimePtEtaDown->SetBinContent(1,Migration_Matrix_jecTimePtEtaDown->GetBinContent(1,2)); Ttbar_4_jecTimePtEtaDown->SetBinContent(2,Migration_Matrix_jecTimePtEtaDown->GetBinContent(2,2));
    TH1F *Ttbar_3_jerDown = new TH1F("Ttbar_3_jerDown","",newrec,new_rec);   Ttbar_3_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,1)); Ttbar_3_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,1));
    TH1F *Ttbar_4_jerDown = new TH1F("Ttbar_4_jerDown","",newrec,new_rec);   Ttbar_4_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,2)); Ttbar_4_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,2));
    TH1F *Ttbar_3_hdampDown = new TH1F("Ttbar_3_hdampDown","",newrec,new_rec);   Ttbar_3_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,1)); Ttbar_3_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,1));
    TH1F *Ttbar_4_hdampDown = new TH1F("Ttbar_4_hdampDown","",newrec,new_rec);   Ttbar_4_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,2)); Ttbar_4_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,2));
    TH1F *Ttbar_3_cferr1Down = new TH1F("Ttbar_3_cferr1Down","",newrec,new_rec);   Ttbar_3_cferr1Down->SetBinContent(1,Migration_Matrix_cferr1Down->GetBinContent(1,1)); Ttbar_3_cferr1Down->SetBinContent(2,Migration_Matrix_cferr1Down->GetBinContent(2,1));
    TH1F *Ttbar_4_cferr1Down = new TH1F("Ttbar_4_cferr1Down","",newrec,new_rec);   Ttbar_4_cferr1Down->SetBinContent(1,Migration_Matrix_cferr1Down->GetBinContent(1,2)); Ttbar_4_cferr1Down->SetBinContent(2,Migration_Matrix_cferr1Down->GetBinContent(2,2));
    TH1F *Ttbar_3_cferr2Down = new TH1F("Ttbar_3_cferr2Down","",newrec,new_rec);   Ttbar_3_cferr2Down->SetBinContent(1,Migration_Matrix_cferr2Down->GetBinContent(1,1)); Ttbar_3_cferr2Down->SetBinContent(2,Migration_Matrix_cferr2Down->GetBinContent(2,1));
    TH1F *Ttbar_4_cferr2Down = new TH1F("Ttbar_4_cferr2Down","",newrec,new_rec);   Ttbar_4_cferr2Down->SetBinContent(1,Migration_Matrix_cferr2Down->GetBinContent(1,2)); Ttbar_4_cferr2Down->SetBinContent(2,Migration_Matrix_cferr2Down->GetBinContent(2,2));
    TH1F *Ttbar_3_hfDown = new TH1F("Ttbar_3_hfDown","",newrec,new_rec);   Ttbar_3_hfDown->SetBinContent(1,Migration_Matrix_hfDown->GetBinContent(1,1)); Ttbar_3_hfDown->SetBinContent(2,Migration_Matrix_hfDown->GetBinContent(2,1));
    TH1F *Ttbar_4_hfDown = new TH1F("Ttbar_4_hfDown","",newrec,new_rec);   Ttbar_4_hfDown->SetBinContent(1,Migration_Matrix_hfDown->GetBinContent(1,2)); Ttbar_4_hfDown->SetBinContent(2,Migration_Matrix_hfDown->GetBinContent(2,2));
    TH1F *Ttbar_3_lfDown = new TH1F("Ttbar_3_lfDown","",newrec,new_rec);   Ttbar_3_lfDown->SetBinContent(1,Migration_Matrix_lfDown->GetBinContent(1,1)); Ttbar_3_lfDown->SetBinContent(2,Migration_Matrix_lfDown->GetBinContent(2,1));
    TH1F *Ttbar_4_lfDown = new TH1F("Ttbar_4_lfDown","",newrec,new_rec);   Ttbar_4_lfDown->SetBinContent(1,Migration_Matrix_lfDown->GetBinContent(1,2)); Ttbar_4_lfDown->SetBinContent(2,Migration_Matrix_lfDown->GetBinContent(2,2));
    TH1F *Ttbar_3_hfstats1Down = new TH1F("Ttbar_3_hfstats1Down","",newrec,new_rec);   Ttbar_3_hfstats1Down->SetBinContent(1,Migration_Matrix_hfstats1Down->GetBinContent(1,1)); Ttbar_3_hfstats1Down->SetBinContent(2,Migration_Matrix_hfstats1Down->GetBinContent(2,1));
    TH1F *Ttbar_4_hfstats1Down = new TH1F("Ttbar_4_hfstats1Down","",newrec,new_rec);   Ttbar_4_hfstats1Down->SetBinContent(1,Migration_Matrix_hfstats1Down->GetBinContent(1,2)); Ttbar_4_hfstats1Down->SetBinContent(2,Migration_Matrix_hfstats1Down->GetBinContent(2,2));
    TH1F *Ttbar_3_hfstats2Down = new TH1F("Ttbar_3_hfstats2Down","",newrec,new_rec);   Ttbar_3_hfstats2Down->SetBinContent(1,Migration_Matrix_hfstats2Down->GetBinContent(1,1)); Ttbar_3_hfstats2Down->SetBinContent(2,Migration_Matrix_hfstats2Down->GetBinContent(2,1));
    TH1F *Ttbar_4_hfstats2Down = new TH1F("Ttbar_4_hfstats2Down","",newrec,new_rec);   Ttbar_4_hfstats2Down->SetBinContent(1,Migration_Matrix_hfstats2Down->GetBinContent(1,2)); Ttbar_4_hfstats2Down->SetBinContent(2,Migration_Matrix_hfstats2Down->GetBinContent(2,2));
    TH1F *Ttbar_3_lfstats1Down = new TH1F("Ttbar_3_lfstats1Down","",newrec,new_rec);   Ttbar_3_lfstats1Down->SetBinContent(1,Migration_Matrix_lfstats1Down->GetBinContent(1,1)); Ttbar_3_lfstats1Down->SetBinContent(2,Migration_Matrix_lfstats1Down->GetBinContent(2,1));
    TH1F *Ttbar_4_lfstats1Down = new TH1F("Ttbar_4_lfstats1Down","",newrec,new_rec);   Ttbar_4_lfstats1Down->SetBinContent(1,Migration_Matrix_lfstats1Down->GetBinContent(1,2)); Ttbar_4_lfstats1Down->SetBinContent(2,Migration_Matrix_lfstats1Down->GetBinContent(2,2));
    TH1F *Ttbar_3_lfstats2Down = new TH1F("Ttbar_3_lfstats2Down","",newrec,new_rec);   Ttbar_3_lfstats2Down->SetBinContent(1,Migration_Matrix_lfstats2Down->GetBinContent(1,1)); Ttbar_3_lfstats2Down->SetBinContent(2,Migration_Matrix_lfstats2Down->GetBinContent(2,1));
    TH1F *Ttbar_4_lfstats2Down = new TH1F("Ttbar_4_lfstats2Down","",newrec,new_rec);   Ttbar_4_lfstats2Down->SetBinContent(1,Migration_Matrix_lfstats2Down->GetBinContent(1,2)); Ttbar_4_lfstats2Down->SetBinContent(2,Migration_Matrix_lfstats2Down->GetBinContent(2,2));
    TH1F *Ttbar_3_jesDown = new TH1F("Ttbar_3_jesDown","",newrec,new_rec);   Ttbar_3_jesDown->SetBinContent(1,Migration_Matrix_jesDown->GetBinContent(1,1)); Ttbar_3_jesDown->SetBinContent(2,Migration_Matrix_jesDown->GetBinContent(2,1));
    TH1F *Ttbar_4_jesDown = new TH1F("Ttbar_4_jesDown","",newrec,new_rec);   Ttbar_4_jesDown->SetBinContent(1,Migration_Matrix_jesDown->GetBinContent(1,2)); Ttbar_4_jesDown->SetBinContent(2,Migration_Matrix_jesDown->GetBinContent(2,2));


TFile out("Input_undfolding_data_900.root","recreate");


Ttbar_3_nominal->Write();
Ttbar_4_nominal->Write();

Ttbar_3_pileupUp->Write();
Ttbar_4_pileupUp->Write();
Ttbar_3_muIDUp->Write();
Ttbar_4_muIDUp->Write();
Ttbar_3_muHLTUp->Write();
Ttbar_4_muHLTUp->Write();
Ttbar_3_Top_pT_rewUp->Write();
Ttbar_4_Top_pT_rewUp->Write();
Ttbar_3_mistagUp->Write();
Ttbar_4_mistagUp->Write();
Ttbar_3_toptagUp->Write();
Ttbar_4_toptagUp->Write();
Ttbar_3_muon_recUp->Write();
Ttbar_4_muon_recUp->Write();
Ttbar_3_ISRUp->Write();
Ttbar_4_ISRUp->Write();
Ttbar_3_FSRUp->Write();
Ttbar_4_FSRUp->Write();
Ttbar_3_jecTimePtEtaUp->Write();
Ttbar_4_jecTimePtEtaUp->Write();
Ttbar_3_jerUp->Write();
Ttbar_4_jerUp->Write();
Ttbar_3_hdampUp->Write();
Ttbar_4_hdampUp->Write();

Ttbar_3_cferr1Up->Write();
Ttbar_4_cferr1Up->Write();
Ttbar_3_cferr2Up->Write();
Ttbar_4_cferr2Up->Write();
Ttbar_3_hfUp->Write();
Ttbar_4_hfUp->Write();
Ttbar_3_lfUp->Write();
Ttbar_4_lfUp->Write();
Ttbar_3_hfstats1Up->Write();
Ttbar_4_hfstats1Up->Write();
Ttbar_3_hfstats2Up->Write();
Ttbar_4_hfstats2Up->Write();
Ttbar_3_lfstats1Up->Write();
Ttbar_4_lfstats1Up->Write();
Ttbar_3_lfstats2Up->Write();
Ttbar_4_lfstats2Up->Write();
Ttbar_3_jesUp->Write();
Ttbar_4_jesUp->Write();

Ttbar_3_pileupDown->Write();
Ttbar_4_pileupDown->Write();
Ttbar_3_muIDDown->Write();
Ttbar_4_muIDDown->Write();
Ttbar_3_muHLTDown->Write();
Ttbar_4_muHLTDown->Write();
Ttbar_3_Top_pT_rewDown->Write();
Ttbar_4_Top_pT_rewDown->Write();
Ttbar_3_mistagDown->Write();
Ttbar_4_mistagDown->Write();
Ttbar_3_toptagDown->Write();
Ttbar_4_toptagDown->Write();
Ttbar_3_muon_recDown->Write();
Ttbar_4_muon_recDown->Write();
Ttbar_3_ISRDown->Write();
Ttbar_4_ISRDown->Write();
Ttbar_3_FSRDown->Write();
Ttbar_4_FSRDown->Write();
Ttbar_3_jecTimePtEtaDown->Write();
Ttbar_4_jecTimePtEtaDown->Write();
Ttbar_3_jerDown->Write();
Ttbar_4_jerDown->Write();
Ttbar_3_hdampDown->Write();
Ttbar_4_hdampDown->Write();

Ttbar_3_cferr1Down->Write();
Ttbar_4_cferr1Down->Write();
Ttbar_3_cferr2Down->Write();
Ttbar_4_cferr2Down->Write();
Ttbar_3_hfDown->Write();
Ttbar_4_hfDown->Write();
Ttbar_3_lfDown->Write();
Ttbar_4_lfDown->Write();
Ttbar_3_hfstats1Down->Write();
Ttbar_4_hfstats1Down->Write();
Ttbar_3_hfstats2Down->Write();
Ttbar_4_hfstats2Down->Write();
Ttbar_3_lfstats1Down->Write();
Ttbar_4_lfstats1Down->Write();
Ttbar_3_lfstats2Down->Write();
Ttbar_4_lfstats2Down->Write();
Ttbar_3_jesDown->Write();
Ttbar_4_jesDown->Write();


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

   TMatrix H(8,8);
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


