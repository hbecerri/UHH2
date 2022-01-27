import ROOT as R
import sys
from sys import argv
import numpy as np
import math

nbins = 140
#file = R.TFile("rebin_q2_SR1T.root")
file = R.TFile("mu_Test_4cat_q2_SR1T.root")
values_per_bin_ttbar = {}
sigmas = []
for i in range(20):
    values_per_bin_ttbar[str(i)]  = []
#get values per bin
proc = ['ttbar_semi', 'ttbar_others', 'wjets']
h_bkg = {}
h_tmp_q2 = {}
h_q2 = {}
file.cd('')
fout = R.TFile("templates_q2_SR1T.root", 'recreate')
for p in proc:
    file.cd('')
    R.gDirectory.cd('')
    R.gDirectory.cd('SR1T/'+p)
    dir = R.gDirectory.GetListOfKeys()
    print p

    for key in dir:
        a = key.GetName()
        h_bkg[a] = file.Get('SR1T/'+p+'/'+a).Clone()

    for i in range(1,h_bkg['nominal'].GetNbinsX()+1):
        h_tmp_q2[str(i)]=R.TH1F("q2"+str(i),"q2"+str(i), 8000, 0., 40000.)

    for key1 in dir:
        b = key1.GetName()
        print(b)
        if b == 'nominal':
	    continue
        for i in range(1,h_bkg[b].GetNbinsX()+1):
            value = h_bkg[b].GetBinContent(i)
            h_tmp_q2[str(i)].Fill(value)

    bin = h_bkg['nominal'].GetNbinsX()+1
    h_q2["q2Up"] = h_bkg['q2ttbarMuRdnMuFdn__plus'].Clone()
    h_q2["q2Up"].SetName("q2Up")
    h_q2["q2Up"].SetTitle("q2Up")
    h_q2["q2Down"] = h_bkg['q2ttbarMuRdnMuFdn__plus'].Clone()
    h_q2["q2Down"].SetName("q2Down")
    h_q2["q2Down"].SetTitle("q2Down")

    for i in range(1,bin):
        h_q2["q2Up"].SetBinContent(i,h_tmp_q2[str(i)].GetMean()+h_tmp_q2[str(i)].GetRMS())
        h_q2["q2Down"].SetBinContent(i,h_tmp_q2[str(i)].GetMean()-h_tmp_q2[str(i)].GetRMS())

#    fout = R.TFile("templates_q2_SR1T.root", 'recreate')
    if(p == 'ttbar_semi'):
        p = 'Ttbar'
    fout.mkdir(argv[1]+'/'+p)
    fout.cd(argv[1]+"/"+p)
   # fout.cd("")
    R.gDirectory.WriteObject(h_q2["q2Up"],"q2Up" )
    R.gDirectory.WriteObject(h_q2["q2Down"],"q2Down" )

