#!/bin/bash

rm -f *.root
rm -f *.json
rm -f *.txt


cp 2016_electron/electron_2016.txt .
cp 2017_electron/electron_2017.txt .
cp 2018_electron/electron_2018.txt .

cp 2016_electron_750_900/electron_2016_750_900.txt .
cp 2017_electron_750_900/electron_2017_750_900.txt .
cp 2018_electron_750_900/electron_2018_750_900.txt .

combineCards.py electron_2018=electron_2018.txt  electron_2017=electron_2017.txt electron_2016=electron_2016.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt > Ac_900.txt
 
text2workspace.py Ac_900.txt -o Ac_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_nMlo[1,0,20]' --PO map='.*/Ttbar_3:r_nMhi[1,0,20]' --PO map='.*/Ttbar_4:r_pMhi[1,0,20]' --PO map='.*/Ttbar_2:r_pMlo=expr;;r_pMlo("-@0*6430/5675 + 5674/5675*@2*(1+@1)/(1-@1) +  6255/5675*@3*(1+@1)/(1-@1)",r_pMhi,Ac[0.0073,-2,2],r_nMlo,r_nMhi)'  --PO verbose

bash impacts_new_electron.sh
mv r_nMlo.pdf r_nMlo_ele.pdf
mv r_nMhi.pdf r_nMhi_ele.pdf
mv r_pMlo.pdf r_pMlo_ele.pdf
mv r_pMhi.pdf r_pMhi_ele.pdf
mv Ac.pdf Ac_ele.pdf


