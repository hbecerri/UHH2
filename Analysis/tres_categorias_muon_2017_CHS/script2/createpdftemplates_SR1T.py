from ROOT import *
import sys
import numpy
from array import array
import string

array_rec = [-2,-1.5,-1.25,-1.0,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1.,1.25,1.5,2]
len_rec = len(array_rec) - 1

ct_top = '(weight)*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_sfelec_HT)'
systematic_direction_ttbar={'nominal':ct_top}

for i in range(0,100):
    pdfstring  = '*(wgtMC__PDF['+str(i)+'])'
    systematic_direction_ttbar['wgtMC__PDF_'+str(i)] = ct_top+pdfstring

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/"
samplelist = {
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2017.root',
'ttbar_semi':'uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2017.root',
'ttbar_others':'uhh2.AnalysisModuleRunner.MC.TTToOthers.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST_2017.root',
'dy':'uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2017.root',
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2017.root',
}

categories=['T1']
fout = TFile('mu_Test_4cat_PDF_SR1T.root', 'recreate')

fout.mkdir("SR1T")
fout.mkdir("SR1T/ttbar_semi")
fout.mkdir("SR1T/dy")
fout.mkdir("SR1T/ttbar_others")
fout.mkdir("SR1T/wjets")
fout.mkdir("SR1T/singletop")
gROOT.SetBatch(kTRUE)
                               
for cat in categories:
    cut_string_GL='(Mttbar>900 &'
    if cat == 'T1':
        cut_string = cut_string_GL+' rec_chi2<30  '
        a=0
        for key_sample in samplelist:
            if key_sample == 'QCD':
                continue
            myfile = TFile(inputdir+samplelist[key_sample])
            mytree = myfile.Get("AnalysisTree")
            mytree.SetAlias("invmass","DeltaY")
            gDirectory.cd('mu_Test_4cat_PDF_SR1T.root:/SR1T/'+key_sample)
            if key_sample == 'DATA':
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat_PDF_SR1T.root:/SR1T/data_obs')
                cut = str(cut_string+' & ttagN==%d & btagN>=1 & wtagN==%d)'%(argv[1],argv[2]))
                print("--------------------------------------")
                print "Processing: ",key_sample
                print "Applying cut:",cut
                tempdata = TH1F("tempdata","tempdata",len_rec,array('d',array_rec))
                mytree.Draw("invmass>>tempdata",cut)
                tempdata.SetBinContent(1,tempdata.GetBinContent(0)+tempdata.GetBinContent(1))
                tempdata.SetBinContent(14,tempdata.GetBinContent(15)+tempdata.GetBinContent(14))
                tempdata.SetName(key_sample)
                gDirectory.WriteObject(tempdata,'nominal')
                del tempdata
#            elif 'ttbar' in key_sample:
            else:
                for syst in systematic_direction_ttbar:
                    cut = str(cut_string+' & ttagN==%s & btagN>=1 & wtagN==%s)*1.00*'%(sys.argv[1],sys.argv[2])+systematic_direction_ttbar[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        temp = TH1F("temp","temp",len_rec,array('d',array_rec))
                        mytree.Draw("invmass>>temp",cut)
                        temp.SetBinContent(1,temp.GetBinContent(0)+temp.GetBinContent(1))
                        temp.SetBinContent(14,temp.GetBinContent(15)+temp.GetBinContent(14))
                        temp.SetName(syst)
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                        gDirectory.WriteObject(temp,syst)
                        del temp
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",len_rec,array('d',array_rec))
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        temp2sys.SetBinContent(1,temp2sys.GetBinContent(0)+temp2sys.GetBinContent(1))
                        temp2sys.SetBinContent(14,temp2sys.GetBinContent(15)+temp2sys.GetBinContent(14))
                        gDirectory.WriteObject(temp2sys,syst)
                        del temp2sys


