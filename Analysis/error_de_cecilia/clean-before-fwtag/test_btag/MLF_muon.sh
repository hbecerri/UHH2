#!/bin/bash

rm -f *.root
#rm -f *.pdf 
rm -f *.json
rm -f *.txt

cp ../2018_muon_FWP_btag/muon_2018.txt .
cp ../2018_muon_750_900_FWP_btag/muon_2018_750_900.txt .

combineCards.py muon_2018=muon_2018.txt muon_2018_750_900=muon_2018_750_900.txt > Ac_muon.txt
 

text2workspace.py Ac_muon.txt -o Ac_muon.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

bash impacts.sh
mv r_nMlo.pdf r_nMlo_muon.pdf
mv r_nMhi.pdf r_nMhi_muon.pdf
mv r_pMlo.pdf r_pMlo_muon.pdf
mv r_pMhi.pdf r_pMhi_muon.pdf
mv Ac.pdf Ac_muon.pdf



