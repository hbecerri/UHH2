import sys
from ROOT import *
from ROOT import TH1
import ConfigParser
from math import sqrt,log10,floor,ceil,fabs
import os
from array import array
TH1.AddDirectory(False)

file_list = ['Ttbar_mass.root']
h_list = ["MatchableBeforeChi2Cut_General/M_tophad_dr_ttag_rebin", "MatchableBeforeChi2Cut_General/M_toplep_dr_ttag_rebin"]
h_title = ["M_{t}^{had, wtag} (correctly matched) [GeV]","M_{t}^{lep, ttag} (correctly matched) [GeV]"]

fname = 'w'
print fname
def hists(file_HLTsel, plot):
    
    input_HLTsel = TFile.Open(file_HLTsel)
    h = input_HLTsel.Get(plot)
    return h

gStyle.SetOptStat(1111111)
gStyle.SetOptFit()
gStyle.SetTitleSize(0.06,"x")  
gStyle.SetTitleSize(0.06,"y")
gStyle.SetOptTitle(0)

for i in file_list:
    if i == file_list[0]:
        print i
        h_base = hists(i, "TTbar_b")
h_base.SetMarkerStyle(4)
h_base.Fit("gaus", 'R', 'same',150, 200)
h_base.SetMarkerStyle(4)
#    print h_base.GetMean()
#    print h_base.GetRMS()
    #h_base.Fit("gaus")

h = 600
w = 800
            
c1 = TCanvas("Top Mass", "Top Mass", w, h)
h_base.SetMarkerStyle(4)
h_base.GetYaxis().SetTitle("Events")            
h_base.GetXaxis().SetTitle(h_title[0])
h_base.GetXaxis().SetTitleSize(0.04)
h_base.GetYaxis().SetTitleSize(0.04)
h_base.SetMarkerStyle(4)            
h_base.Draw()
h_base.SetMarkerStyle(4)
gStyle.SetOptStat(1111111)
c1.SaveAs(fname+".pdf")






