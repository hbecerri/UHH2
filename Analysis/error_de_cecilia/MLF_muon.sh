#!/bin/bash

rm -f *.root
#rm -f *.pdf 
rm -f *.json
rm -f *.txt

cp 2016_muon/muon_2016.txt .
cp 2017_muon/muon_2017.txt .
cp 2018_muon/muon_2018.txt .

cp 2016_muon_750_900/muon_2016_750_900.txt .
cp 2017_muon_750_900/muon_2017_750_900.txt .
cp 2018_muon_750_900/muon_2018_750_900.txt .

combineCards.py muon_2018=muon_2018.txt  muon_2017=muon_2017.txt  muon_2016=muon_2016.txt muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt > Ac_900.txt
 

text2workspace.py Ac_900.txt -o Ac_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_nMlo[1,0,20]' --PO map='.*/Ttbar_3:r_nMhi[1,0,20]' --PO map='.*/Ttbar_4:r_pMhi[1,0,20]' --PO map='.*/Ttbar_2:r_pMlo=expr;;r_pMlo("-@0*21056/26674 +  26470/26674*@2*(1+@1)/(1-@1) +  20750/26674*@3*(1+@1)/(1-@1)",r_pMhi,Ac[0.0053,-2,2],r_nMlo,r_nMhi)'  --PO verbose

bash impacts_new_muon.sh
mv r_nMlo.pdf r_nMlo_muon.pdf
mv r_nMhi.pdf r_nMhi_muon.pdf
mv r_pMlo.pdf r_pMlo_muon.pdf
mv r_pMhi.pdf r_pMhi_muon.pdf
mv Ac.pdf Ac_muon.pdf



