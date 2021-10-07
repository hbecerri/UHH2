from ROOT import *
import sys
from sys import argv
import numpy
from array import array
import string

array_rec = [-2,0,2]
len_rec = len(array_rec) - 1

ct_top = 'weight*(weight_sfelec_TightID)*(weight_pu)*(weight_sfelec_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(weight_sfelec_Rec)*(weight_HT_HT)*0.86'

systematic_direction_ttbar={
                            'q2MuRdnMuFdnDown':ct_top+'*(weight_murmuf_downdown)',
                            'q2MuRdnMuFdnUp':ct_top,
                            'q2MuRupMuFupUp':ct_top+'*(weight_murmuf_upup)',
                            'q2MuRupMuFupDown':ct_top,
                            'q2MuRdnMuFctDown':ct_top+'*(weight_murmuf_downnone)',
                            'q2MuRdnMuFctUp':ct_top,
                            'q2MuRupMuFctUp':ct_top+'*(weight_murmuf_upnone)',
                            'q2MuRupMuFctDown':ct_top,
                            'q2MuRctMuFdnDown':ct_top+'*(weight_murmuf_nonedown)',
                            'q2MuRctMuFdnUp':ct_top,
                            'q2MuRctMuFupUp':ct_top+'*(weight_murmuf_noneup)',
                            'q2MuRctMuFupDown':ct_top+'*1',
                           }

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/"
samplelist = {
'ttbar_semi':'uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root',
}

categories=['T1']
fout = TFile('mu_Test_4cat_q2_SR1T.root', 'recreate')

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
            if key_sample == 'DATA':
                print("--------------------------------------")
            else:
                for syst in systematic_direction_ttbar:
                    cut = str(cut_string+' & ttagN<=%s & btagN>=1 & wtagN<=%s & %s < 0)*1.00*'%(sys.argv[1],sys.argv[2],argv[3])+systematic_direction_ttbar[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",len_rec,array('d',array_rec))
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        temp2sys.SetBinContent(1,temp2sys.GetBinContent(0)+temp2sys.GetBinContent(1))
                        temp2sys.SetBinContent(2,temp2sys.GetBinContent(2)+temp2sys.GetBinContent(3))
                        gDirectory.cd('mu_Test_4cat_q2_SR1T.root:/')
                        gDirectory.WriteObject(temp2sys,'Ttbar_1_'+syst)
                        del temp2sys
