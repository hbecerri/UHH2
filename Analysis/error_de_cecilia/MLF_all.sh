#!/bin/bash

cp 2016_muon/muon_2016.txt .
cp 2017_muon/muon_2017.txt .
cp 2018_muon/muon_2018.txt .

cp 2016_electron/electron_2016.txt .
cp 2017_electron/electron_2017.txt .
cp 2018_electron/electron_2018.txt .

cp 2016_muon_750_900/muon_2016_750_900.txt .
cp 2017_muon_750_900/muon_2017_750_900.txt .
cp 2018_muon_750_900/muon_2018_750_900.txt .

cp 2016_electron_750_900/electron_2016_750_900.txt .
cp 2017_electron_750_900/electron_2017_750_900.txt .
cp 2018_electron_750_900/electron_2018_750_900.txt .


combineCards.py muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt  muon_2016_750_900=muon_2016_750_900.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt  muon_2018=muon_2018.txt  muon_2017=muon_2017.txt  muon_2016=muon_2016.txt electron_2018=electron_2018.txt electron_2017=electron_2017.txt electron_2016=electron_2016.txt > Ac_2016.txt

text2workspace.py Ac_2016.txt -o Ac_2016.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

bash impacts_new.sh

#bash impacts_2016.sh

#mv r_neg.pdf r_neg_2016.pdf
#v r_Asym.pdf r_Asym_2016.pdf
#mv impacts.json impacts_2016.json


#text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]'  --PO map='.*/Ttbar_2:r_pos[1,0,20]' --PO verbose


