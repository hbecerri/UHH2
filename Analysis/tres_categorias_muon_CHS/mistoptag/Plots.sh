#!/bin/bash

rm -f *.txt

#declare -a StringArray=("Ak4_ji_pt")
#declare -a StringArray=("pT_had" "pT_lep" "pT_ttbar" "TL_M" "TH_M")
#declare -a StringArray=("N_Ak4" "N_Ak8" "Mttbar" "lep1_pt" "MET_pt" "Ak8_j1_pt" "pT_had" "pT_lep" "pT_ttbar" "TL_M" "TH_M")


declare -a StringArray=("DeltaY" "Ak4_j1_pt")
for var in ${StringArray[@]}; do
     python makePlots_fromAnalysisTree.py ${var} -b 
done

