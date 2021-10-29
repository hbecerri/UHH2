#!/bin/bash


cp 2017_muon_750_900/muon_2017_750_900.txt .
cp 2018_muon_750_900/muon_2018_750_900.txt .

cp 2016_electron_750_900/electron_2016_750_900.txt .
cp 2017_electron_750_900/electron_2017_750_900.txt .
cp 2018_electron_750_900/electron_2018_750_900.txt .


combineCards.py muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt > Ac_2016_750_900.txt

text2workspace.py Ac_2016_750_900.txt -o Ac_2016_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

bash impacts_new_750.sh


