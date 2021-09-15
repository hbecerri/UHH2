from array import array
from ROOT import *
import sys
from sys import *
import numpy

Bin = []
#DeltaY
if argv[1] == 'DeltaY':
    Bin = [-2.,0.,2.]

nb = len(Bin)-1
ct = '(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(muonrecSF_down)*(weight_HT_HT)'
systematic_direction_Ttbar={
'nominal':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'pileupUp':'(weight_sfelec_TightID)*(weight_pu_up)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'pileupDown':'(weight_sfelec_TightID)*(weight_pu_down)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleIDUp':'(weight_sfelec_TightID_up)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleIDDown':'(weight_sfelec_TightID_down)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleHLTUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleHLTDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'jesUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'jesDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'Top_pT_rewUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(1)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'Top_pT_rewDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_down_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'mistagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*1.01*(weight_HT_HT)',
                            'mistagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*0.99*(weight_HT_HT)',
                            'toptagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'toptagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'ele_recUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_up)*(weight_HT_HT)',
                            'ele_recDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_down)*(weight_HT_HT)',
                            'HTUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_up)',
                            'HTDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_down)',
#                            'ISRUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*ISRup',
#                            'ISRDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*ISRdown',
#                            'FSRUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*FSRup',
#                            'FSRDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*FSRdown',
#                            'jecUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
#                            'jecDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
#                            'jerUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
#                            'jerDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
#                            'hdampUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84',
#                            'hdampDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84',
}
systematic_direction_otherbkgs={
'nominal':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'pileupUp':'(weight_sfelec_TightID)*(weight_pu_up)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'pileupDown':'(weight_sfelec_TightID)*(weight_pu_down)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleIDUp':'(weight_sfelec_TightID_up)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleIDDown':'(weight_sfelec_TightID_down)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleHLTUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'eleHLTDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'cferr2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'hfstats2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'jesUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'jesDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfup)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfdown)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats1Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats1Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats2Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2up)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'lfstats2Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2down)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'mistagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*1.01*(weight_HT_HT)',
                            'mistagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*0.99*(weight_HT_HT)',
                            'toptagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'toptagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)',
                            'ele_recUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_up)*(weight_HT_HT)',
                            'ele_recDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec_down)*(weight_HT_HT)',
                            'HTUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_up)',
                            'HTDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT_down)',
}


jecdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_JECdown/"
jecupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_JECup/"
jerupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_JERup/"
jerdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/workdir_Zprime_Analysis_2017_muon_CHS_JERdown/"
hdampupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/hdamp_up/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampup_2017.root"
hdampdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/hdamp_down/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampdown_2017.root"
 

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/"
samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_EGamma_Run2017v2.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST_2017v2.root',
'qcd':'uhh2.AnalysisModuleRunner.MC.QCD_HT_2017v2.root',
'dy':'uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2017v2.root',
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2017v2.root',
'ttbar_others':'uhh2.AnalysisModuleRunner.MC.TTToOthers.root',
}

categories=['T1']
fout = TFile('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/'+argv[1]+'_muon_3cat.root', 'recreate')
 
type = ['SR1T']

process  = ['Ttbar','singletop','data_obs','qcd','wjets','dy','ttbar_others']

gROOT.SetBatch(kTRUE)

for cat in categories:
    if cat == 'T1':
            a=0
            for key_sample in samplelist:
                myfile = TFile(inputdir+samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass",argv[1])
                gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/'+argv[1]+'_muon_3cat.root:/')
                if key_sample == 'DATA':
                    gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/'+argv[1]+'_muon_3cat.root:/')
                    cut = str('(ttagN<=1 & btagN>=1 & wtagN<=1 & Mttbar>750 & Mttbar<900 & rec_chi2 < 30)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    tempdata = TH1F("tempdata","tempdata",nb,array('d',Bin))
                    mytree.Draw("invmass>>tempdata",cut)
                    tempdata.SetName(key_sample)
                    gDirectory.WriteObject(tempdata,'data_obs')
                    del tempdata
                elif 'singletop' in key_sample or 'wjets' in key_sample or 'dy' in key_sample or 'vv' in key_sample or 'qcd' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str('(ttagN<=1 & btagN>=1 & wtagN<=1 & Mttbar>750 & Mttbar<900 & rec_chi2 < 30)*(weight)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,key_sample+'_'+syst)
                            del temp
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/'+argv[1]+'_muon_3cat.root:/')
                            je_tree.SetAlias("invmass","DeltaY")
                            tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,key_sample+'_'+syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,key_sample+'_'+syst)
                            del temp2sys
                elif 'ttbar_others' in key_sample:
                    for syst in systematic_direction_Ttbar:
                        cut = str('(ttagN<=1 & btagN>=1 & wtagN<=1 & Mttbar>750 & Mttbar<900 & rec_chi2 < 30)*(weight)*'+systematic_direction_Ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,key_sample+'_'+syst)
                            del temp
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/'+argv[1]+'_muon_3cat.root:/')
                            je_tree.SetAlias("invmass","DeltaY")
                            tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,key_sample+'_'+syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,key_sample+'_'+syst)
                            del temp2sys
