import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np

#syst=['jer','jec','hfstats1','toptag','eleID','mistag','lfstats2','hf','pileup','eleHLT','lf','Top_pT_rew','hfstats2','lfstats1','cferr1','cferr2','jes','HT','ele_rec', 'ISR', 'FSR', 'hdamp','PDF_1','PDF_2','PDF_3','PDF_4','PDF_5','PDF_6','PDF_7','PDF_8','PDF_9','PDF_10','PDF_11','PDF_12','PDF_13','PDF_14','PDF_15','PDF_16','PDF_17','PDF_18','PDF_19','PDF_20','PDF_21','PDF_22','PDF_23','PDF_24','PDF_25','PDF_26','PDF_27','PDF_28','PDF_29','PDF_30','PDF_31','PDF_32','PDF_33','PDF_34','PDF_35','PDF_36','PDF_37','PDF_38','PDF_39','PDF_40','PDF_41','PDF_42','PDF_43','PDF_44','PDF_45','PDF_46','PDF_47','PDF_48','PDF_49','PDF_50','PDF_51','PDF_52','PDF_53','PDF_54','PDF_55','PDF_56','PDF_57','PDF_58','PDF_59','PDF_60','PDF_61','PDF_62','PDF_63','PDF_64','PDF_65','PDF_66','PDF_67','PDF_68','PDF_69','PDF_70','PDF_71','PDF_72','PDF_73','PDF_74','PDF_75','PDF_76','PDF_77','PDF_78','PDF_79','PDF_80','PDF_81','PDF_82','PDF_83','PDF_84','PDF_85','PDF_86','PDF_87','PDF_88','PDF_89','PDF_90','PDF_91','PDF_92','PDF_93','PDF_94','PDF_95','PDF_96','PDF_97','PDF_98','PDF_99','q2MuRdnMuFdn', 'q2MuRctMuFdn', 'q2MuRupMuFct', 'q2MuRupMuFup', 'q2MuRctMuFup', 'q2MuRdnMuFct']
 
syst=['toptag','eleID','mistag','pileup','lf','Top_pT_rew','ele_rec', 'ISR', 'FSR', 'hdamp','PDF_1','PDF_2','PDF_3','PDF_4','PDF_5','PDF_6','PDF_7','PDF_8','PDF_9','PDF_10','PDF_11','PDF_12','PDF_13','PDF_14','PDF_15','PDF_16','PDF_17','PDF_18','PDF_19','PDF_20','PDF_21','PDF_22','PDF_23','PDF_24','PDF_25','PDF_26','PDF_27','PDF_28','PDF_29','PDF_30','PDF_31','PDF_32','PDF_33','PDF_34','PDF_35','PDF_36','PDF_37','PDF_38','PDF_39','PDF_40','PDF_41','PDF_42','PDF_43','PDF_44','PDF_45','PDF_46','PDF_47','PDF_48','PDF_49','PDF_50','PDF_51','PDF_52','PDF_53','PDF_54','PDF_55','PDF_56','PDF_57','PDF_58','PDF_59','PDF_60','PDF_61','PDF_62','PDF_63','PDF_64','PDF_65','PDF_66','PDF_67','PDF_68','PDF_69','PDF_70','PDF_71','PDF_72','PDF_73','PDF_74','PDF_75','PDF_76','PDF_77','PDF_78','PDF_79','PDF_80','PDF_81','PDF_82','PDF_83','PDF_84','PDF_85','PDF_86','PDF_87','PDF_88','PDF_89','PDF_90','PDF_91','PDF_92','PDF_93','PDF_94','PDF_95','PDF_96','PDF_97','PDF_98','PDF_99','q2MuRdnMuFdn', 'q2MuRctMuFdn', 'q2MuRupMuFct', 'q2MuRupMuFup', 'q2MuRctMuFup', 'q2MuRdnMuFct']

#syst=[]

proc=["Ttbar_1","Ttbar_2", "Ttbar_3","Ttbar_4","dy", "qcd",  "singletop", "ttbar_others", "wjets"]

proc.sort()
proc = list(dict.fromkeys(proc))
proc.sort()

fin = R.TFile('DeltaY.root')
N_reco_bins = 0
datacard=open("electron_2016_750_900.txt","w")
datacard.write("1 imax\n")
datacard.write("* jmax\n")
datacard.write("* kmax\n")

datacard.write("----------------\n")

datacard.write("shapes data_obs  *  /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_electron_750_900/DeltaY.root $PROCESS\n")
datacard.write("shapes *         *  /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_electron_750_900/DeltaY.root $PROCESS_nominal $PROCESS_$SYSTEMATIC\n")

datacard.write("----------------\n")

datacard.write("bin bin1_electron_2016")
datacard.write("\n")
datacard.write("observation -1")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write("bin ")
for ireco in range(1,10):
    datacard.write("bin1_electron_2016 ")
datacard.write("\n")
datacard.write("process ")
datacard.write("Ttbar_1 ")
datacard.write("Ttbar_2 ")
datacard.write("Ttbar_3 ")
datacard.write("Ttbar_4 ")
datacard.write("dy ")
datacard.write("qcd ")
datacard.write("singletop ")
datacard.write("ttbar_others ")
datacard.write("wjets ")
datacard.write("\n")
datacard.write("process ")
for ireco in range(-3,6):
    datacard.write("%d "%ireco) 
datacard.write("\n")
datacard.write("rate ")
for ireco in range(-3,6):
    datacard.write("-1 ")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write('luminosity_2016 lnN ')
for xx in range(len(proc)):
    datacard.write('1.009 ')
datacard.write("\n")
datacard.write('luminosity_161718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.006 ')

datacard.write("\n")
for name in proc:
    if(name == 'Ttbar_4'):
        continue
    if(name == 'Ttbar_3'):
        continue
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

