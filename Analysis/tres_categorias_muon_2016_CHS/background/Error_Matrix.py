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
#mCovTot = unfolding_input_data.Get("mCovTot")
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

''' 
diagonals = []
for ibin in xrange(1,mCovTot.GetNbinsX()+1):
    tmp = math.sqrt(mCovTot.GetBinContent(ibin,ibin)) if (math.sqrt(mCovTot.GetBinContent(ibin,ibin)) is not 0) else 1.0
    diagonals.append(tmp)
for ibinx in xrange(1,mCovTot.GetNbinsX()+1):
    for ibiny in xrange(1,mCovTot.GetNbinsY()+1):
        tmp = mCovTot.GetBinContent(ibinx,ibiny) / diagonals[ibinx-1] / diagonals[ibiny-1]
        mCovTot.SetBinContent(ibinx,ibiny,tmp)



c1 = TCanvas('c1', 'Dynamic Slice Example', 10, 10, 700, 500 )
c1.cd()
mCovTot.Draw('colz')
c1.Print('Correlation.pdf')

'''


for i in range(0,8):
    for j in range(0,8):
        mCovTot.SetBinContent(i+1,j+1,math.sqrt(mCovTot.GetBinContent(i+1,j+1)/(nominal[i]*nominal[j])))

c2 = TCanvas('c1', 'Dynamic Slice Example', 10, 10, 700, 500 )
c2.cd()
mCovTot.Draw('colz')
c2.Print('Error.pdf')


'''
c2 = TCanvas('c1', 'Dynamic Slice Example', 10, 10, 700, 500 )
c2.cd()
mCovTot.Draw('colz')
c2.Print('Covariance.pdf')
'''





