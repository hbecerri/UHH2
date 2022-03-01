#!/bin/bash

python makePlots_fromAnalysisTree_electron.py DeltaY 1 0
mv electron_2016.root electron_2016_boosted.root
mv electron_2017.root electron_2017_boosted.root
mv electron_2018.root electron_2018_boosted.root

python makePlots_fromAnalysisTree_electron.py DeltaY 0 0
mv electron_2016.root electron_2016_resolved.root
mv electron_2017.root electron_2017_resolved.root
mv electron_2018.root electron_2018_resolved.root

python makePlots_fromAnalysisTree_electron.py DeltaY 0 1
mv electron_2016.root electron_2016_semiresolved.root
mv electron_2017.root electron_2017_semiresolved.root
mv electron_2018.root electron_2018_semiresolved.root


python makePlots_fromAnalysisTree_muon.py DeltaY 1 0
mv muon_2016.root muon_2016_boosted.root
mv muon_2017.root muon_2017_boosted.root
mv muon_2018.root muon_2018_boosted.root

python makePlots_fromAnalysisTree_muon.py DeltaY 0 0
mv muon_2016.root muon_2016_resolved.root
mv muon_2017.root muon_2017_resolved.root
mv muon_2018.root muon_2018_resolved.root

python makePlots_fromAnalysisTree_muon.py DeltaY 0 1
mv muon_2016.root muon_2016_semiresolved.root
mv muon_2017.root muon_2017_semiresolved.root
mv muon_2018.root muon_2018_semiresolved.root



hadd -f todo_resolved.root *resolved.root 
hadd -f todo_boosted.root *boosted.root
hadd -f todo_semiresolved.root *semiresolved.root
 

