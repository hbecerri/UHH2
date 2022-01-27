#!/bin/bash

rm -f *.root
rm -f *.pdf 
rm -f *.json
rm -f *.txt

bash MLF_muon.sh
bash MLF_electron.sh
bash MLF_900.sh
bash MLF_750.sh
bash MLF_all.sh

