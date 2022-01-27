#!/bin/bash

rm -f *.pdf

#declare -a StringArray=("2018" "2017" "2016")
declare -a StringArray=("Run_II")
for var in ${StringArray[@]}; do
    root -l -b -q "all_unfolding_data.C(\"${var}\")"
done

for var in ${StringArray[@]}; do
    root -l -b -q "all_unfolding_data_t.C(\"${var}\")"
done

for var in ${StringArray[@]}; do
    root -l -b -q "all_unfolding_data_b.C(\"${var}\")"
done

for var in ${StringArray[@]}; do
    root -l -b -q "all_unfolding_data_l.C(\"${var}\")"
done

