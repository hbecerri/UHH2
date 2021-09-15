#!/bin/bash

cp 2016_muon/muon*.txt .
cp 2016_electron/electron*.txt .
combineCards.py muon_2016=muon_2016.txt electron_2016=electron_2016.txt > Ac.txt

#combineCards.py muon_2018=muon_2018.txt muon_2017=muon_2017.txt muon_2016=muon_2016.txt electron_2018=electron_2018.txt electron_2017=electron_2017.txt electron_2016=electron_2016.txt > Ac.txt

#cp 2016_muon/muon*.txt .
#cp 2016_muon_750_900/muon*.txt .
#combineCards.py muon_2016=muon_2016.txt > Ac.txt  #muon_2016_750_900=muon_2016_750_900.txt > Ac.txt

text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("9689/9853*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose

bash impacts.sh

#text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]'  --PO map='.*/Ttbar_2:r_pos[1,0,20]' --PO verbose


