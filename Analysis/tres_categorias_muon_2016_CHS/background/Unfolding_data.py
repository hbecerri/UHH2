import math
import sys
import ROOT
from sys import argv
from ROOT import TH1, TH1F, TH2F, TFile, TCanvas, TPad, TLegend, TLatex, TColor, TMath, TVectorD, TGraph, TUnfold, Double, TSpline, TSpline3, TUnfoldDensity, TUnfoldSys, TAttLine, TStyle
from ROOT import *
from array import array
import string

class Background :
    def __init__(self, name, hist):
        self.name = name
        self.hist = hist
        if(name == 'wjets'): 
	        self.norm = 1.
       	        self.err  = 0.3
        if(name == 'dy'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'qcd'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'st'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'ttbar_others'):
                self.norm = 1.
                self.err  = 0.3
class Systematic :
    def __init__(self, name, response):
        self.name = name
        self.response = response


gStyle.SetOptStat(0)
gROOT.SetBatch(True)

unfolding_input_data = TFile("Input_undfolding_data.root")

measurement = unfolding_input_data.Get("Data")
expectation = unfolding_input_data.Get("Var_gen")
ttbar = unfolding_input_data.Get("ttbar_semi_nominal")

ttbar_others = unfolding_input_data.Get("ttbar_others_nominal")
wjets = unfolding_input_data.Get("wjets_nominal")
dy = unfolding_input_data.Get("dy_nominal")
qcd = unfolding_input_data.Get("qcd_nominal")
st = unfolding_input_data.Get("singletop_nominal")

response = unfolding_input_data.Get("Migration_Matrix")

#syst
backgrounds = {}
backgrounds["wjets"] = Background("wjets",wjets)
backgrounds["dy"] = Background("dy",dy)
backgrounds["qcd"] = Background("qcd",qcd)
backgrounds["st"] = Background("st",st)
backgrounds["ttbar_others"] = Background("ttbar_others",ttbar_others)
 
unfold = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)
unfold.SetInput(measurement)

for name, background in backgrounds.iteritems():
    unfold.SubtractBackground(background.hist,background.name,background.norm,background.err)

unfold.DoUnfold(0)
result = unfold.GetOutput("result")
result.Sumw2()

for i in range (1,9):
    print(result.GetBinContent(i))


