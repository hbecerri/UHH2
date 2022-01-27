#! /usr/bin/env python

import math
import ROOT
from ROOT import *
import math
import array
from numpy import *

def back_yields(Rootfile):

    Ttbar_1_nominal = 0.
    Ttbar_2_nominal = 0.
    wjets_nominal = 0.
    DY_nominal = 0.
    ST_nominal = 0.
    ttbar_others = 0.
    qcd_nominal = 0.

    Ttbar_1_error = 0.
    Ttbar_2_error = 0.
    wjets_error = 0.
    DY_error = 0.
    ST_error = 0.
    ttbar_error = 0.
    qcd_error = 0.

    syst = Rootfile.GetListOfKeys()
    s=[]
    for sys in syst:
        c = sys.GetName()
        s.append(c)
    s.sort()
    s = list(dict.fromkeys(s))
    nominal = 0
    error = 0
    error_sys = Double(0.0)
    err = Double(0.0)
    for element in s:
        nominal = 0
        error = 0
        error_sys = Double(0.0)
        err = Double(0.0)
        if 'nominal' in element:
            proceso = element[:-8]
            a = 0
            error_nominal = Double(0.0)
            Rootfile.cd("")
            myhisto = gDirectory.Get(element).Clone()
            a = myhisto.IntegralAndError(1,2,error_nominal,"")
            nominal = int(a)
            error = int(error_nominal)
            for elemento in s:
#                if 'PDF' in elemento:
#                    continue
#                if 'hdamp' in elemento:
#                    continue
                if 'jer' in elemento:
                    continue
                if 'jec' in elemento:
                    continue
                if 'nominal' in elemento:
                    continue
                if (not (proceso in elemento)):
                    continue
                if 'down' in elemento:
                    continue
                myhisto = gDirectory.Get(elemento).Clone()
                b = myhisto.Integral()
                err = abs(nominal - b)
                error_sys += err*err
                err = 0
#                print(elemento)
#                print(math.sqrt(error_sys))
            error = math.sqrt(error*error + error_sys)
            if 'Ttbar_1' in proceso:
                Ttbar_1_nominal = int(nominal)
                Ttbar_1_error = int(error)
            elif 'Ttbar_2' in proceso:
                Ttbar_2_nominal = int(nominal)
                Ttbar_2_error = int(error)
            elif 'wjets' in proceso:
                wjets_nominal = int(nominal)
                wjets_error = int(error)
            elif 'dy' in proceso:
                dy_nominal = int(nominal)
                dy_error = int(error)
            elif 'others' in proceso:
                ttbar_others_nominal = int(nominal)
                ttbar_others_error = int(error)
            elif 'qcd' in proceso:
                qcd_nominal = int(nominal)
                qcd_error = int(error)
            elif 'singletop' in proceso:
                ST_nominal = int(nominal)
                ST_error = int(error)
            myhisto2 = gDirectory.Get('data_obs').Clone()
            data = myhisto2.Integral()
            print(Rootfile)
            print(Ttbar_1_nominal)
            print(Ttbar_2_nominal)

    return Ttbar_1_nominal, Ttbar_1_error, Ttbar_2_nominal, Ttbar_2_error, wjets_nominal, wjets_error, dy_nominal, dy_error, ttbar_others_nominal, ttbar_others_error, qcd_nominal, qcd_error, ST_nominal, ST_error, data

text = 'Table.txt'
T = open(text,"w+")
T.write('\\begin{table}[htbp]')
T.write("\n") 
T.write('\\fontsize{10}{10}\\selectfont')
T.write("\n") 
T.write('\\begin{center}')
T.write("\n") 
T.write('\\begin{tabular}{|l|c|c|c|c|c|c|} \\hline')
T.write("\n") 
T.write(' Process &  $\mu_{2018}$ & $\mu_{2017}$ & $\mu_{2016}$ & $e_{2018}$ & $e_{2017}$ & $e_{2016}$ \\\[0.1cm]')
T.write("\n") 

channel_1 = TFile("2016_muon/DeltaY.root")
channel_2 = TFile("2016_electron/DeltaY.root")
channel_3 = TFile("2017_muon/DeltaY.root")
channel_4 = TFile("2017_electron/DeltaY.root")
channel_5 = TFile("2018_muon/DeltaY.root")
channel_6 = TFile("2018_electron/DeltaY.root")

a11, a12, b11, b12, c11, c12, d11, d12, e11, e12, f11, f12, g11, g12, data1 = back_yields(channel_1) 
a21, a22, b21, b22, c21, c22, d21, d22, e21, e22, f21, f22, g21, g22, data2 = back_yields(channel_2)
a31, a32, b31, b32, c31, c32, d31, d32, e31, e32, f31, f32, g31, g32, data3 = back_yields(channel_3)
a41, a42, b41, b42, c41, c42, d41, d42, e41, e42, f41, f42, g41, g42, data4 = back_yields(channel_4)
a51, a52, b51, b52, c51, c52, d51, d52, e51, e52, f51, f52, g51, g52, data5 = back_yields(channel_5)
a61, a62, b61, b62, c61, c62, d61, d62, e61, e62, f61, f62, g61, g62, data6 = back_yields(channel_6)

total_nominal_muon_2016 = int(a11 + b11 + c11 + d11 + e11 + f11 + g11)
total_error_muon_2016 = int(math.sqrt(a12*a12 + b12*b12 + c12*c12 + d12*d12 + e12*e12 + f12*f12 + g12*g12))
total_nominal_muon_2017 = int(a31 + b31 + c31 + d31 + e31 + f31 + g31)
total_error_muon_2017 = int(math.sqrt(a32*a32 + b32*b32 + c32*c32 + d32*d32 + e32*e32 + f32*f32 + g32*g32))
total_nominal_muon_2018 = int(a51 + b51 + c51 + d51 + e51 + f51 + g51)
total_error_muon_2018 = int(math.sqrt(a52*a52 + b52*b52 + c52*c52 + d52*d52 + e52*e52 + f52*f52 + g52*g52))

total_nominal_electron_2016 = int(a21 + b21 + c21 + d21 + e21 + f21 + g21)
total_error_electron_2016 = int(math.sqrt(a22*a22 + b22*b22 + c22*c22 + d22*d22 + e22*e22 + f22*f22 + g22*g22))
total_nominal_electron_2017 = int(a41 + b41 + c41 + d41 + e41 + f41 + g41)
total_error_electron_2017 = int(math.sqrt(a42*a42 + b42*b42 + c42*c42 + d42*d42 + e42*e42 + f42*f42 + g42*g42))
total_nominal_electron_2018 = int(a61 + b61 + c61 + d61 + e61 + f61 + g61)
total_error_electron_2018 = int(math.sqrt(a62*a62 + b62*b62 + c62*c62 + d62*d62 + e62*e62 + f62*f62 + g62*g62))


total_nominal_2016_muon = int(a11 + b11)
total_error_2016_muon = int(math.sqrt(a12*a12 + b12*b12))
total_nominal_2017_muon = int(a31 + b31)
total_error_2017_muon = int(math.sqrt(a32*a32 + b32*b32))
total_nominal_2018_muon = int(a51 + b51)
total_error_2018_muon = int(math.sqrt(a52*a52 + b52*b52))

total_nominal_2016_electron = int(a21 + b21)
total_error_2016_electron = int(math.sqrt(a22*a22 + b22*b22))
total_nominal_2017_electron = int(a41 + b41)
total_error_2017_electron = int(math.sqrt(a42*a42 + b42*b42))
total_nominal_2018_electron = int(a61 + b61)
total_error_2018_electron = int(math.sqrt(a62*a62 + b62*b62))


T.write('  \\hline  \\rule{-2pt}{11pt}')
T.write('\n')
T.write('$t\\bar{t}_{semi}$ & ')
T.write('\t')
T.write(str(total_nominal_2018_muon)+'\\pm'+str(total_error_2018_muon)+'\t &\t'+str(total_nominal_2017_muon)+'\\pm'+str(total_error_2017_muon)+'\t &\t'+str(total_nominal_2016_muon)+'\\pm'+str(total_error_2016_muon)+'\t &\t'+str(total_nominal_2018_electron)+'\\pm'+str(total_error_2018_electron)+'\t &\t'+str(total_nominal_2017_electron)+'\\pm'+str(total_error_2017_electron)+'\t &\t'+str(total_nominal_2016_electron)+'\\pm'+str(total_error_2016_electron))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('$t\\bar{t}_{others}$ & ')
T.write('\t')
T.write(str(e51)+'\\pm'+str(e52)+'\t &\t'+str(e31)+'\\pm'+str(e32)+'\t &\t'+str(e11)+'\\pm'+str(e12)+'\t &\t'+str(e61)+'\\pm'+str(e62)+'\t &\t'+str(e41)+'\\pm'+str(e42)+'\t &\t'+str(e21)+'\\pm'+str(e22))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('$\\Wjets$ & ')
T.write('\t')
T.write(str(c51)+'\\pm'+str(c52)+'\t &\t'+str(c31)+'\\pm'+str(c32)+'\t &\t'+str(c11)+'\\pm'+str(c12)+'\t &\t'+str(c61)+'\\pm'+str(c62)+'\t &\t'+str(c41)+'\\pm'+str(c42)+'\t &\t'+str(c21)+'\\pm'+str(c22))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('Single Top & ')
T.write('\t')
T.write(str(g51)+'\\pm'+str(g52)+'\t &\t'+str(g31)+'\\pm'+str(g32)+'\t &\t'+str(g11)+'\\pm'+str(g12)+'\t &\t'+str(g61)+'\\pm'+str(g62)+'\t &\t'+str(g41)+'\\pm'+str(g42)+'\t &\t'+str(g21)+'\\pm'+str(g22))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('Drell-Yan & ')
T.write('\t')
T.write(str(d51)+'\\pm'+str(d52)+'\t &\t'+str(d31)+'\\pm'+str(d32)+'\t &\t'+str(d11)+'\\pm'+str(d12)+'\t &\t'+str(d61)+'\\pm'+str(d62)+'\t &\t'+str(d41)+'\\pm'+str(d42)+'\t &\t'+str(d41)+'\\pm'+str(d22))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('Multi-Jet & ')
T.write('\t')
T.write(str(f51)+'\\pm'+str(f52)+'\t &\t'+str(f31)+'\\pm'+str(f32)+'\t &\t'+str(f11)+'\\pm'+str(f12)+'\t &\t'+str(f61)+'\\pm'+str(f62)+'\t &\t'+str(f41)+'\\pm'+str(f42)+'\t &\t'+str(f41)+'\\pm'+str(f22))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('Total & ')
T.write('\t')
T.write(str(total_nominal_muon_2018)+'\\pm'+str(total_error_muon_2018)+'\t &\t'+str(total_nominal_muon_2017)+'\\pm'+str(total_error_muon_2017)+'\t &\t'+str(total_nominal_muon_2016)+'\\pm'+str(total_error_muon_2016)+'\t &\t'+str(total_nominal_electron_2018)+'\\pm'+str(total_error_electron_2018)+'\t &\t'+str(total_nominal_electron_2017)+'\\pm'+str(total_error_electron_2017)+'\t &\t'+str(total_nominal_electron_2016)+'\\pm'+str(total_error_electron_2016))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('DATA & ')
T.write('\t')
T.write(str(data5)+'\t &\t'+str(data3)+'\t &\t'+str(data1)+'\t &\t'+str(data6)+'\t &\t'+str(data4)+'\t &\t'+str(data2))
T.write('\t')
T.write('\\\\')
T.write('\n')
T.write(' \\hline  \\rule{-2pt}{11pt}')
T.write('\n')

T.write('\\end{tabular}')
T.write('\n')
T.write('\\vspace{.5cm}')
T.write('\n')
T.write('\\caption{Event yields for each of the six channels used in the analysis ($\\mujets$, $\\ejets$ and 3 years: 2018, 2017 and 2016) for events that pass the signal sample selection. The errors shown include both MC statistical and total systematic uncertainty. \\label{tab:yields}}')
T.write('\n')
T.write('\\end{center}')
T.write('\n')
T.write('\\end{table}')

