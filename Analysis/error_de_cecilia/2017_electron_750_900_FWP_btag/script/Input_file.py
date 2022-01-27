from array import array
from ROOT import *
import sys
from sys import *
import numpy

Bin = []
#MTtbar
#if argv[1] == 'Mttbar':
#    Bin = [880.,1050.,1300.,1500.,1800.,2200.,2600.,4000.]
#pT_Ttbar
if argv[1] == 'pT_ttbar':
    Bin = [0.,200.,400.,600.,800.,1200.]
#DeltaY
if argv[1] == 'DeltaY':
    Bin = [-2.,0.,2.]
#Delta_phi
if argv[1] == 'DeltaPhi_thad_lepton':
    Bin = [0,0.5,1.0,1.5,2.0,2.5,3.0,3.5]
#Cos_theta
if argv[1] == 'Cos_theta_thad_tlep':
    Bin = [-1.,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1.]
#Rapidity_ttbar
if argv[1] == 'Rapidity_ttbar':
    Bin = [-2.4,-2.,-1.6,-1.2,-0.8,-0.4,0.0,0.4,0.8,1.2,1.6,2,2.4]
#Rapidity_thad
if argv[1] == 'Rapidity_had':
    Bin = [-2.4,-2.,-1.6,-1.2,-0.8,-0.4,0.0,0.4,0.8,1.2,1.6,2,2.4]
#Rapidity_ttbar
if argv[1] == 'Rapidity_lep':
    Bin = [-2.4,-2.,-1.6,-1.2,-0.8,-0.4,0.0,0.4,0.8,1.2,1.6,2,2.4]

nb = len(Bin)-1
systematic_direction_Ttbar={
'nominal':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)*(weight_HT_HT)',
#                            'hdampUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84',
#                            'hdampDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)*(weight_HT_HT)*0.84',
}
systematic_direction_otherbkgs={
'nominal':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'pileupUp':'(weight_sfelec_TightID)*(weight_pu_up)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'pileupDown':'(weight_sfelec_TightID)*(weight_pu_down)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'eleIDUp':'(weight_sfelec_TightID_up)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'eleIDDown':'(weight_sfelec_TightID_down)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'eleHLTUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'eleHLTDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'btag_HF_corrUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_up)*(weight_sfelec_Rec)',
                            'btag_LF_corrUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_up)*(weight_sfelec_Rec)',
                            'btag_HF_unc17Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_up_un)*(weight_sfelec_Rec)',
                            'btag_LF_unc17Up':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_up_un)*(weight_sfelec_Rec)',
                            'btag_HF_corrDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_down)*(weight_sfelec_Rec)',
                            'btag_LF_corrDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_down)*(weight_sfelec_Rec)',
                            'btag_HF_unc17Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_down_un)*(weight_sfelec_Rec)',
                            'btag_LF_unc17Down':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_down_un)*(weight_sfelec_Rec)',
                            'mistagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)*1.001',
                            'mistagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)*0.999',
                            'toptagUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'toptagDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
                            'ele_recUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec_up)',
                            'ele_recDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec_down)',
#                            'jecUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
#                            'jecDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
#                            'jerUp':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
#                            'jerDown':'(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(weight_sfelec_Rec)',
}

jecdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_muon_CHS_JECdown/"
jecupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_muon_CHS_JECup/"
jerupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_muon_CHS_JERup/"
jerdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/workdir_Zprime_Analysis_2017_muon_CHS_JERdown/"
hdampupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/hdamp_up/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampup_2017v3.root"
hdampdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/eleectron/hdamp_down/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampdown_2017v3.root"
 

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/electron/"
samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_EGamma_Run2017v2.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST_2017.root',
'qcd':'uhh2.AnalysisModuleRunner.MC.QCD_HT_2017.root',
'dy':'uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2017.root',
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2017.root',
}

categories=['T1']
fout = TFile('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900_FWP_btag/'+argv[1]+'_muon_3cat.root', 'recreate')
 
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
                gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900_FWP_btag/'+argv[1]+'_muon_3cat.root:/')
                if key_sample == 'DATA':
                    gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900_FWP_btag/'+argv[1]+'_muon_3cat.root:/')
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
                        cut = str('(ttagN<=1 & btagN>=1 & wtagN<=1 & Mttbar>750 & Mttbar<900  & rec_chi2 < 30)*0.95*(weight)*'+systematic_direction_otherbkgs[syst])
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
                            gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900_FWP_btag/'+argv[1]+'_muon_3cat.root:/')
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
                            gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900_FWP_btag/'+argv[1]+'_muon_3cat.root:/')
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
