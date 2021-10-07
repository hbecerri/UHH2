#!/bin/bash

cp 2016_muon/muon_2016.txt .
cp 2016_electron/electron_2016.txt .
cp 2016_muon_750_900/muon_2016_750_900.txt .
cp 2016_electron_750_900/electron_2016_750_900.txt .

cp 2017_muon/muon_2017.txt .
cp 2017_electron/electron_2017.txt .
cp 2017_muon_750_900/muon_2017_750_900.txt .
cp 2017_electron_750_900/electron_2017_750_900.txt .

cp 2018_muon/muon_2018.txt .
cp 2018_electron/electron_2018.txt .
cp 2018_muon_750_900/muon_2018_750_900.txt .
cp 2018_electron_750_900/electron_2018_750_900.txt .



combineCards.py muon_2018_750_900=muon_2018_750_900.txt muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt  muon_2018=muon_2018.txt muon_2017=muon_2017.txt muon_2016=muon_2016.txt electron_2018=electron_2018.txt electron_2017=electron_2017.txt electron_2016=electron_2016.txt > Ac.txt

combineCards.py muon_2018_750_900=muon_2018_750_900.txt muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt > Ac_750.txt

combineCards.py muon_2018=muon_2018.txt muon_2017=muon_2017.txt muon_2016=muon_2016.txt electron_2018=electron_2018.txt electron_2017=electron_2017.txt electron_2016=electron_2016.txt > Ac_900.txt

combineCards.py muon_2018_750_900=muon_2018_750_900.txt muon_2017_750_900=muon_2017_750_900.txt muon_2016_750_900=muon_2016_750_900.txt muon_2018=muon_2018.txt muon_2017=muon_2017.txt muon_2016=muon_2016.txt > Ac_muon.txt

combineCards.py electron_2018_750_900=electron_2018_750_900.txt electron_2017_750_900=electron_2017_750_900.txt electron_2016_750_900=electron_2016_750_900.txt electron_2018=electron_2018.txt electron_2017=electron_2017.txt electron_2016=electron_2016.txt > Ac_electron.txt

text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("59155/59842*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

text2workspace.py Ac_750.txt -o Ac_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("28123/28382*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

text2workspace.py Ac_900.txt -o Ac_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("31032/31460*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

text2workspace.py Ac_muon.txt -o Ac_muon.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("47222/47734*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

text2workspace.py Ac_electron.txt -o Ac_electron.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("11933/12108*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose

bash impacts_all.sh
mv r_neg.pdf r_neg_all.pdf
mv Ac.pdf Ac_all.pdf
mv impacts.json impacts_all.json
bash impacts_750.sh
mv r_neg.pdf r_neg_750.pdf
mv Ac.pdf Ac_750.pdf
mv impacts.json impacts_750.json
bash impacts_900.sh
mv r_neg.pdf r_neg_900.pdf
mv Ac.pdf Ac_900.pdf
mv impacts.json impacts_900.json
bash impacts_muon.sh
mv r_neg.pdf r_neg_muon.pdf
mv Ac.pdf Ac_muon.pdf
mv impacts.json impacts_muon.json
bash impacts_electron.sh
mv r_neg.pdf r_neg_electron.pdf
mv Ac.pdf Ac_electron.pdf
mv impacts.json impacts_electron.json

#text2workspace.py Ac.txt -o Ac.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]'  --PO map='.*/Ttbar_2:r_pos[1,0,20]' --PO verbose


