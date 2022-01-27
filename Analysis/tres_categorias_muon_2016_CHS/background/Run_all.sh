#!/bin/bash

rm -f *.txt
rm -f *.pdf
rm -f *.root

cp ../up*/In*.root .

declare -a StringArray=("pileupUp" "muIDUp" "muHLTUp" "misttagUp" "cferr1Up" "cferr2Up" "hfUp" "lfUp" "hfstats1Up" "hfstats2Up" "lfstats1Up" "lfstats2Up" "jesUp" "toptagUp" "muon_recUp" "pdfUp" "q2Up")
for region in "${StringArray[@]}"; do
    echo ${region}
    python -b Unfolding_data_wjets.py ${region} > out.txt
done

hadd mCovTot.root Wjets*.root
mv mCovTot.root mCovTot_wjtes.root
rm -f -r Wjets*.root

####ttbar_others

declare -a StringArray2=("pileupUp" "muIDUp" "muHLTUp" "misttagUp" "cferr1Up" "cferr2Up" "hfUp" "lfUp" "hfstats1Up" "hfstats2Up" "lfstats1Up" "lfstats2Up" "jesUp" "toptagUp" "muon_recUp" "pdfUp" "q2Up")
for region in "${StringArray2[@]}"; do
    echo ${region}
    python -b Unfolding_data_ttbar_others.py ${region} > out.txt
done

hadd mCovTot.root ttbar*.root
mv mCovTot.root mCovTot_ttbar_others.root
rm -f -r ttbar_others*.root

###singletop


declare -a StringArray3=("pileupUp" "muIDUp" "muHLTUp" "misttagUp" "cferr1Up" "cferr2Up" "hfUp" "lfUp" "hfstats1Up" "hfstats2Up" "lfstats1Up" "lfstats2Up" "jesUp" "toptagUp" "muon_recUp")
for region in "${StringArray3[@]}"; do
    echo ${region}
    python -b Unfolding_data_singletop.py ${region} > out.txt
done

hadd mCovTot.root single*.root
mv mCovTot.root mCovTot_singletop.root
rm -f -r singletop*.root

#####dy

declare -a StringArray4=("pileupUp" "muIDUp" "muHLTUp" "misttagUp" "cferr1Up" "cferr2Up" "hfUp" "lfUp" "hfstats1Up" "hfstats2Up" "lfstats1Up" "lfstats2Up" "jesUp" "toptagUp" "muon_recUp")
for region in "${StringArray4[@]}"; do
    echo ${region}
    python -b Unfolding_data_dy.py ${region} > out.txt
done

hadd mCovTot.root dy*.root
mv mCovTot.root mCovTot_dy.root
rm -f -r dy*.root

#####qcd

declare -a StringArray5=("pileupUp" "muIDUp" "muHLTUp" "misttagUp" "cferr1Up" "cferr2Up" "hfUp" "lfUp" "hfstats1Up" "hfstats2Up" "lfstats1Up" "lfstats2Up" "jesUp" "toptagUp" "muon_recUp")
for region in "${StringArray5[@]}"; do
    echo ${region}
    python -b Unfolding_data_qcd.py ${region} > out.txt
done

hadd mCovTot.root qcd*.root
mv mCovTot.root mCovTot_qcd.root
rm -f -r qcd*.root



hadd mCovTot.root mCovTot_*.root

python Err*.py
python Corre*.py
python Cov*.py
 
