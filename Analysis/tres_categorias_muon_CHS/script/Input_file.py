from array import array
from ROOT import *
import sys
from sys import *
import numpy

Bin = []
#MTtbar
if argv[1] == 'Mttbar':
    Bin = [880.,1050.,1300.,1500.,1800.,2200.,2600.,4000.]
#pT_Ttbar
if argv[1] == 'pT_ttbar':
    Bin = [0.,200.,400.,600.,800.,1200.]
#DeltaY
if argv[1] == 'DeltaY':
    Bin = [-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.]
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
ct = '(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)'
systematic_direction_Ttbar={'nominal':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'pileupUp':'(weight_sfmu_HighPtID)*(weight_pu_up)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'pileupDown':'(weight_sfmu_HighPtID)*(weight_pu_down)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muIDUp':'(weight_sfmu_HighPtID_up)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muIDDown':'(weight_sfmu_HighPtID_down)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muHLTUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muHLTDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'cferr1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_cferr1up)*(muonrecSF_nominal)',
	 		    'cferr1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_cferr1down)*(muonrecSF_nominal)',
                            'hfUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfup)*(muonrecSF_nominal)',
		    	    'hfDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfdown)*(muonrecSF_nominal)',
			    'hfstats1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats1up)*(muonrecSF_nominal)',
			    'hfstats1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats1down)*(muonrecSF_nominal)',
			    'hfstats2Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats2up)*(muonrecSF_nominal)',
			    'hfstats2Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats2down)*(muonrecSF_nominal)',
			    'jesUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_jesup)*(muonrecSF_nominal)',
			    'jesDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_jesdown)*(muonrecSF_nominal)',
			    'lfUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfup)*(muonrecSF_nominal)',
		            'lfDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfdown)*(muonrecSF_nominal)',
		            'lfstats1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats1up)*(muonrecSF_nominal)',
                            'lfstats1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats1down)*(muonrecSF_nominal)',
			    'lfstats2Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats2up)*(muonrecSF_nominal)',
                            'lfstats2Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats2down)*(muonrecSF_nominal)',
			    'pt_rewUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(1)*(weight_btagdisc_central)*(muonrecSF_nominal)',
			    'pt_rewDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_down)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'misttagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02',
 		            'misttagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98',
                            'miswtagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02',
			    'miswtagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98',		
                            'toptagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_up_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
			    'toptagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_down_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',	
}
systematic_direction_otherbkgs={'nominal':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'pileupUp':'(weight_sfmu_HighPtID)*(weight_pu_up)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'pileupDown':'(weight_sfmu_HighPtID)*(weight_pu_down)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muIDUp':'(weight_sfmu_HighPtID_up)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muIDDown':'(weight_sfmu_HighPtID_down)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muHLTUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'muHLTDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'cferr1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_cferr1up)*(muonrecSF_nominal)',
                            'cferr1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_cferr1down)*(muonrecSF_nominal)',
                            'hfUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfup)*(muonrecSF_nominal)',
                            'hfDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfdown)*(muonrecSF_nominal)',
                            'hfstats1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats1up)*(muonrecSF_nominal)',
                            'hfstats1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats1down)*(muonrecSF_nominal)',
                            'hfstats2Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats2up)*(muonrecSF_nominal)',
                            'hfstats2Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_hfstats2down)*(muonrecSF_nominal)',
                            'jesUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_jesup)*(muonrecSF_nominal)',
                            'jesDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_jesdown)*(muonrecSF_nominal)',
                            'lfUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfup)*(muonrecSF_nominal)',
                            'lfDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfdown)*(muonrecSF_nominal)',
                            'lfstats1Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats1up)*(muonrecSF_nominal)',
                            'lfstats1Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats1down)*(muonrecSF_nominal)',
                            'lfstats2Up':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats2up)*(muonrecSF_nominal)',
                            'lfstats2Down':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_lfstats2down)*(muonrecSF_nominal)',
                            'pt_rewUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(1)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'pt_rewDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_down)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'misttagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02',
                            'misttagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98',
                            'miswtagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02',
                            'miswtagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98',
                            'toptagUp':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_up_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
                            'toptagDown':'(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_down_)*(weight_pt_rew)*(weight_btagdisc_central)*(muonrecSF_nominal)',
}

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/"
samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2018.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST_2018.root',
'qcd':'uhh2.AnalysisModuleRunner.MC.QCD_HT_2018.root',
'dy':'uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2018.root',
'vv':'uhh2.AnalysisModuleRunner.MC.WW_WZ_ZZ_2018.root',
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2018.root',
'Ttbar':'uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root',
}

categories=['T1']
fout = TFile('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root', 'recreate')
 
type = ['SR1T','SR0T','CR1']
process  = ['Ttbar','singletop','data_obs','qcd','wjets','vv','dy']

for t in type:
    for p in process:
        fout.mkdir(t+'/'+p)
gROOT.SetBatch(kTRUE)

for cat in categories:
    if cat == 'T1':
            a=0
            for key_sample in samplelist:
                myfile = TFile(inputdir+samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass",argv[1])
                gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/SR1T/'+key_sample)
                if key_sample == 'DATA':
                    gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/SR1T/data_obs')
                    cut = str('(ttagN>=0 & btagN>=1)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    tempdata = TH1F("tempdata","tempdata",nb,array('d',Bin))
                    mytree.Draw("invmass>>tempdata",cut)
                    tempdata.SetName(key_sample)
                    gDirectory.WriteObject(tempdata,'nominal')
                    del tempdata
                elif 'Ttbar' in key_sample:
                    for syst in systematic_direction_Ttbar:
                        cut = str('(ttagN==1 & btagN==0)*1.00*(weight)*'+systematic_direction_Ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'singletop' in key_sample or 'wjets' in key_sample or 'dy' in key_sample or 'vv' in key_sample or 'qcd' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str('(ttagN==1 & btagN==0)*(weight)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys

    elif cat == 'T0':
            a=0
            for key_sample in samplelist:
                myfile = TFile(inputdir+samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass",argv[1])
                gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/SR0T/'+key_sample)
                if key_sample == 'DATA':
                    gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/SR0T/data_obs')
                    cut = str('(ttagN==0 & btagN==1)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    temp2data = TH1F("temp2data","temp2data",nb,array('d',Bin))
                    mytree.Draw("invmass>>temp2data",cut)
                    temp2data.SetName(key_sample)
                    gDirectory.WriteObject(temp2data,'nominal')
                    del temp2data
                elif 'Ttbar' in key_sample:
                    for syst in systematic_direction_Ttbar:
                        cut = str('(ttagN==0 & btagN==1)*(weight)*'+systematic_direction_Ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                                tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                                mytree.Draw("invmass>>tempsys",cut)
                                tempsys.SetName(syst)
                                gDirectory.WriteObject(tempsys,syst)
                                del tempsys
                elif 'singletop' in key_sample or 'wjets' in key_sample or 'qcd' in key_sample or 'dy' in key_sample or 'vv' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str('(ttagN == 0 & btagN==1)*(weight)*'+systematic_direction_otherbkgs[syst])
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName('nominal')
                            gDirectory.WriteObject(temp2,'nominal')
                            del temp2
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                
    elif cat == 'T0B0':
            a=0
            for key_sample in samplelist:
                myfile = TFile(inputdir+samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass",argv[1])
                gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/CR1/'+key_sample)
                if key_sample == 'DATA':
                    gDirectory.cd('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon_3cat.root:/CR1/data_obs')
                    cut = str('(ttagN==0 & btagN==0)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    temp2data = TH1F("temp2data","temp2data",nb,array('d',Bin))
                    mytree.Draw("invmass>>temp2data",cut)
                    temp2data.SetName(key_sample)
                    gDirectory.WriteObject(temp2data,'nominal')
                    del temp2data
                elif 'Ttbar' in key_sample:
                    for syst in systematic_direction_Ttbar:
                        cut = str('(ttagN==0 & btagN==0)*(weight)*'+systematic_direction_Ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                elif 'singletop' in key_sample or 'wjets' in key_sample or 'dy' in key_sample or 'vv' in key_sample or 'qcd' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str('(ttagN==0 & btagN==0)*(weight)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys





