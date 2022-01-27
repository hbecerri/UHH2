#!/bin/bash


rm -f *.root
rm -f *.json
rm -f *.txt

cp 2016_muon_750_900/muon_2016_750_900.txt .
cp 2017_muon_750_900/muon_2017_750_900.txt .
cp 2018_muon_750_900/muon_2018_750_900.txt .

cp 2016_electron_750_900/electron_2016_750_900.txt .
cp 2017_electron_750_900/electron_2017_750_900.txt .
cp 2018_electron_750_900/electron_2018_750_900.txt .


combineCards.py muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt  electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt > Ac_2016_750_900.txt

text2workspace.py Ac_2016_750_900.txt -o Ac_2016_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_nMlo[1,0,20]' --PO map='.*/Ttbar_3:r_nMhi[1,0,20]' --PO map='.*/Ttbar_2:r_pMlo[1,0,20]' --PO map='.*/Ttbar_4:r_pMhi=expr;;r_pMhi("-@0*22962/5416 +  22766/5416*@2*(1+@1)/(1-@1) +  5353/5416*@3*(1+@1)/(1-@1)",r_pMlo,Ac[0.0045,-2,2],r_nMlo,r_nMhi)'  --PO verbose


bash impacts_new_750.sh
mv r_nMlo.pdf r_nMlo_750.pdf
mv r_nMhi.pdf r_nMhi_750.pdf
mv r_pMlo.pdf r_pMlo_750.pdf
mv r_pMhi.pdf r_pMhi_750.pdf
mv Ac.pdf Ac_750.pdf

