import math
import sys
import ROOT
from sys import argv
from ROOT import TH1, TH1F, TH2F, TFile, TCanvas, TPad, TLegend, TLatex, TColor, TMath, TVectorD, TGraph, TUnfold, Double, TSpline, TSpline3, TUnfoldDensity, TUnfoldSys, TAttLine, TStyle
from ROOT import *
from array import array
import string

gStyle.SetOptStat(0)
gROOT.SetBatch(True)
unfolding_input_data = TFile("mCovTot.root")
mCovTot  = unfolding_input_data.Get("mCovTot")

nominal = []
nominal.append(641.626454521)
nominal.append(1417.33246038)
nominal.append(2180.97431959)
nominal.append(2809.25373223)
nominal.append(2836.62085926)
nominal.append(2227.21614705)
nominal.append(1452.70597497)
nominal.append(643.451692616)

c2 = TCanvas('c1', 'Dynamic Slice Example', 10, 10, 700, 500 )
c2.cd()
mCovTot.Draw('colz')
c2.Print('Covariance.pdf')




