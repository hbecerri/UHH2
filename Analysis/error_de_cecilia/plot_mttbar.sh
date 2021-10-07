#!/bin/bash


python 2016_electron/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2016_electron/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2016_electron.pdf
mv Mttbar_750.pdf Mttbar_750_2016_electron.pdf

python 2017_electron/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2017_electron/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2017_electron.pdf
mv Mttbar_750.pdf Mttbar_750_2017_electron.pdf

python 2018_electron/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2018_electron/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2018_electron.pdf
mv Mttbar_750.pdf Mttbar_750_2018_electron.pdf

python 2016_muon/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2016_muon/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2016_muon.pdf
mv Mttbar_750.pdf Mttbar_750_2016_muon.pdf

python 2017_muon/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2017_muon/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2017_muon.pdf
mv Mttbar_750.pdf Mttbar_750_2017_muon.pdf

python 2018_muon/mttbar_plots/makePlots_fromAnalysisTree.py Mttbar
python 2018_muon/mttbar_plots/makePlots_fromAnalysisTree_750.py Mttbar

mv Mttbar_900.pdf Mttbar_900_2018_muon.pdf
mv Mttbar_750.pdf Mttbar_750_2018_muon.pdf
