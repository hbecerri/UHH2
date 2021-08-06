import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np

#syst=['toptag','muID','mistag','pileup','muHLT','Top_pT_rew','muon_rec', 'ISR', 'FSR', 'hdamp', 'jec', 'jer']
syst=['hfstats1','toptag','muID','mistag','lfstats2','hf','pileup','muHLT','lf','Top_pT_rew','hfstats2','lfstats1','cferr1','cferr2','jes','HT','muon_rec','jer','jec', 'ISR', 'FSR', 'hdamp','pdf','q2']
 
proc=["Ttbar_1","Ttbar_2", "dy", "qcd",  "singletop", "ttbar_others", "wjets"]

proc.sort()
proc = list(dict.fromkeys(proc))
proc.sort()

fin = R.TFile('DeltaY.root')
N_reco_bins = 0
datacard=open("muon_2017.txt","w")
datacard.write("1 imax\n")
datacard.write("* jmax\n")
datacard.write("* kmax\n")

datacard.write("----------------\n")

datacard.write("shapes data_obs  *  /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_muon/DeltaY.root $PROCESS\n")
datacard.write("shapes *         *  /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_muon/DeltaY.root $PROCESS_nominal $PROCESS_$SYSTEMATIC\n")

datacard.write("----------------\n")

datacard.write("bin muon_2017")
datacard.write("\n")
datacard.write("observation -1")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write("bin ")
for ireco in range(1,8):
    datacard.write("muon_2017 ")
datacard.write("\n")
datacard.write("process ")
datacard.write("Ttbar_1 ")
datacard.write("Ttbar_2 ")
datacard.write("dy ")
datacard.write("qcd ")
datacard.write("singletop ")
datacard.write("ttbar_others ")
datacard.write("wjets ")
datacard.write("\n")
datacard.write("process ")
for ireco in range(-1,6):
    datacard.write("%d "%ireco) 
datacard.write("\n")
datacard.write("rate ")
for ireco in range(-1,6):
    datacard.write("-1 ")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write('luminosity_2017 lnN ')
for xx in range(len(proc)):
    datacard.write('1.02 ')
datacard.write("\n")
datacard.write('luminosity_161718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.009 ')
datacard.write("\n")
datacard.write('luminosity_1718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.006 ')


datacard.write("\n")
for name in proc:
    if(name == 'Ttbar_2'):
        continue
    if(name == 'Ttbar_1'):
        name = 'Ttbar'
    datacard.write('xsec_%s lnN '%name)
    for name2 in proc:
        if(name2.find(name) != -1):
            if(name2.find('Ttbar') != -1):
                datacard.write('1.05 ')
            else:
                datacard.write('1.30 ')
        else:
            datacard.write('- ')
    datacard.write("\n")
datacard.write("---------------------------------------------------\n")

for name in syst:
    datacard.write('%s shape '%name)
    for name2 in proc:
        fin.cd('')
        dir2 = R.gDirectory.GetListOfKeys()
        existe = '- '
        for element in dir2:
            el = element.GetName() 
            if(el.find(name2+'_'+name+'Up') != -1):
                existe = '1 '
        datacard.write(existe)      
    datacard.write("\n")
datacard.write('* autoMCStats 1000000 1')

