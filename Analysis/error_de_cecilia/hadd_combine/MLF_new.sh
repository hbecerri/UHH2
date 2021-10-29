#!/bin/bash

rm -f *.txt
rm -f *.pdf 
rm -f *.root
rm -f *.json

cp muon_900/muon_900.txt .
cp electron_900/electron_900.txt .

cp muon_750/muon_750.txt .
cp electron_750/electron_750.txt .

#combineCards.py muon_2018_750_900=muon_2018_750_900.txt muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt > Ac_750.txt
 
#combineCards.py muon_900=muon_900.txt electron_900=electron_900.txt > Ac_900.txt
#combineCards.py muon_750=muon_750.txt electron_750=electron_750.txt  > Ac_750.txt #electron_750=electron_750.txt > Ac_750.txt
combineCards.py muon_900=muon_900.txt electron_900=electron_900.txt muon_750=muon_750.txt electron_750=electron_750.txt > Ac.txt

#text2workspace.py Ac_900.txt -o Ac_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose
#text2workspace.py Ac_750.txt -o Ac_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

bash impacts_new.sh
mv r_1.pdf r_1_900.pdf
mv r_2.pdf r_2_900.pdf
mv r_3.pdf r_3_900.pdf
mv r_4.pdf r_4_900.pdf




