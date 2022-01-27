#!/bin/bash

python plot_acceptance.py electron_ttbar1.txt
mv plots.pdf electron_ttbar1.pdf 
python plot_acceptance.py electron_ttbar2.txt
mv plots.pdf electron_ttbar2.pdf
python plot_acceptance.py muon_ttbar1.txt
mv plots.pdf muon_ttbar1.pdf
python plot_acceptance.py muon_ttbar2.txt
mv plots.pdf muon_ttbar2.pdf

python plot_acceptance.py electron_ttbar1_750.txt
mv plots.pdf electron_ttbar1_750.pdf
python plot_acceptance.py electron_ttbar2_750.txt
mv plots.pdf electron_ttbar2_750.pdf
python plot_acceptance.py muon_ttbar1_750.txt
mv plots.pdf muon_ttbar1_750.pdf
python plot_acceptance.py muon_ttbar2_750.txt
mv plots.pdf muon_ttbar2_750.pdf

