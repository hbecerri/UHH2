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

ttbar_others = unfolding_input_data.Get("ttbar_others_"+argv[1])
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

nominal = []

nominal.append(416.897119553)
nominal.append(1161.58098396)
nominal.append(1659.05641)
nominal.append(2115.59272144)
nominal.append(2127.57235071)
nominal.append(1628.84864597)
nominal.append(1126.09113128)
nominal.append(398.55242767)

sys_1 = result.GetBinContent(1)
sys_2 = result.GetBinContent(2)
sys_3 = result.GetBinContent(3)
sys_4 = result.GetBinContent(4)
sys_5 = result.GetBinContent(5)
sys_6 = result.GetBinContent(6)
sys_7 = result.GetBinContent(7)
sys_8 = result.GetBinContent(8)

diff = []

diff.append(abs(nominal[0] - sys_1))
diff.append(abs(nominal[1] - sys_2))
diff.append(abs(nominal[2] - sys_3))
diff.append(abs(nominal[3] - sys_4))
diff.append(abs(nominal[4] - sys_5))
diff.append(abs(nominal[5] - sys_6))
diff.append(abs(nominal[6] - sys_7))
diff.append(abs(nominal[7] - sys_8))

mCovTot  = TH2F('mCovTot','',8,-2,2,8,-2,2)

for i in range(0,8):
    for j in range(0,8):
        mCovTot.SetBinContent(i+1,j+1,diff[i]*diff[j])

c1 = TCanvas('c1', 'Dynamic Slice Example', 10, 10, 700, 500 )
c1.cd()
mCovTot.Draw('colz')
c1.Print('ttbar_others_'+argv[1]+'_Covariance.pdf')


fout = TFile('ttbar_others_'+argv[1]+'.root', 'recreate')
fout.cd()

gDirectory.WriteObject(mCovTot,"mCovTot")




