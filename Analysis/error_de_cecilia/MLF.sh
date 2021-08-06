#!/bin/bash

cp *muon/muon*.txt .

combineCards.py muon_2018=muon_2018.txt muon_2017=muon_2017.txt muon_2016=muon_2016.txt > muon.txt

text2workspace.py muon.txt -o muon.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("24995/25276*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose

bash impacts.sh
