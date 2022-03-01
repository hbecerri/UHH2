#!/bin/bash

#rm -f *.pdf
rm -f *.root
rm -f *.json
rm -f *.txt

cp 2016_muon_900_FWP_btag/muon_2016_900.txt .
cp 2017_muon_900_FWP_btag/muon_2017_900.txt .
cp 2018_muon_900_FWP_btag/muon_2018_900.txt .

cp 2016_electron_900_FWP_btag/ele_2016_900.txt .
cp 2017_electron_900_FWP_btag/ele_2017_900.txt .
cp 2018_electron_900_FWP_btag/ele_2018_900.txt .

cp 2016_muon_750_900_FWP_btag/muon_2016_750_900.txt .
cp 2017_muon_750_900_FWP_btag/muon_2017_750_900.txt .
cp 2018_muon_750_900_FWP_btag/muon_2018_750_900.txt .

cp 2016_electron_750_900_FWP_btag/ele_2016_750_900.txt .
cp 2017_electron_750_900_FWP_btag/ele_2017_750_900.txt .
cp 2018_electron_750_900_FWP_btag/ele_2018_750_900.txt .

combineCards.py muon_2018_900=muon_2018_900.txt  muon_2017_900=muon_2017_900.txt  muon_2016_900=muon_2016_900.txt ele_2018_900=ele_2018_900.txt  ele_2017_900=ele_2017_900.txt ele_2016_900=ele_2016_900.txt  muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt  ele_2018_750_900=ele_2018_750_900.txt ele_2017_750_900=ele_2017_750_900.txt ele_2016_750_900=ele_2016_750_900.txt > Ac_750.txt

combineCards.py muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt  ele_2018_750_900=ele_2018_750_900.txt ele_2017_750_900=ele_2017_750_900.txt ele_2016_750_900=ele_2016_750_900.txt > Ac_750_900.txt
combineCards.py muon_2018_900=muon_2018_900.txt  muon_2017_900=muon_2017_900.txt  muon_2016_900=muon_2016_900.txt ele_2018_900=ele_2018_900.txt  ele_2017_900=ele_2017_900.txt ele_2016_900=ele_2016_900.txt > Ac_900.txt
combineCards.py muon_2018_900=muon_2018_900.txt  muon_2017_900=muon_2017_900.txt  muon_2016_900=muon_2016_900.txt muon_2018_750_900=muon_2018_750_900.txt  muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt > Ac_muon.txt
combineCards.py ele_2018_900=ele_2018_900.txt  ele_2017_900=ele_2017_900.txt ele_2016_900=ele_2016_900.txt ele_2018_750_900=ele_2018_750_900.txt ele_2017_750_900=ele_2017_750_900.txt ele_2016_750_900=ele_2016_750_900.txt > Ac_ele.txt


text2workspace.py Ac_750.txt -o Ac_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("0.9905*67566/68556*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose 
text2workspace.py Ac_900.txt -o Ac_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("1.0165*35668/36268*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose
text2workspace.py Ac_750_900.txt -o Ac_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("0.9608*31898/32288*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

bash impacts_750.sh
mv Ac.pdf Ac_750_full.pdf 
mv r_neg.pdf r_neg_750_full.pdf 
mv impacts.json impacts_750_full.json

bash impacts_750_900.sh
mv Ac.pdf Ac_750_900_full.pdf
mv r_neg.pdf r_neg_750_900_full.pdf
mv impacts.json impacts_750_900_full.json

bash impacts_900.sh
mv Ac.pdf Ac_900_full.pdf
mv r_neg.pdf r_neg_900_full.pdf
mv impacts.json impacts_900_full.json








 







