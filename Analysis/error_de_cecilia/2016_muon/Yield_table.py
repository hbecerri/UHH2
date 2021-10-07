#! /usr/bin/env python

import ROOT
from ROOT import *
import math
import array
from numpy import *
text = 'Table.txt'
T = open(text,"w+")
Rootfile = TFile("DeltaY.root")
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
        error = math.sqrt(error*error + error_sys) 
        nom = int(nominal)
        e = int(error)
        if element == 'data_obs':
            e = 0
        T.write(element)
        T.write("\t")
        T.write(str(nom))
        T.write("\pm")
        T.write(str(e))                
        T.write("\n")    
myhisto2 = gDirectory.Get('data_obs').Clone()
c = myhisto2.Integral()
T.write('DATA')
T.write("\t")
T.write(str(c))
