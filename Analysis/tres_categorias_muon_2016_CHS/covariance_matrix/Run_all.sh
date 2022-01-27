#!/bin/bash

rm -f *.txt
rm -f *.pdf
rm -f mCovTot.root

declare -a StringArray=("pileup" "muID" "muHLT" "misttag" "cferr1" "cferr2" "hf" "lf" "hfstats1" "hfstats2" "lfstats1" "lfstats2" "jes" "pt_rew" "toptag" "muon_rec" "pdf" "q2" "jer" "jec" "hdamp")
for region in "${StringArray[@]}"; do
    echo ${region}
    python -b Unfolding_data.py ${region} > out.txt
done


hadd mCovTot.root *.root

python Corre*.py 
