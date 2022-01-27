#!/bin/bash

declare -a StringArray=("DeltaY")
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'

for var in ${StringArray[@]}; do

        echo ${var}
	python script/Input_file.py ${var}
        python script/Get_UF_OF.py ${var}
        rm -f DeltaY.root 

        cp script2/*.root .    
        hadd DeltaY.root DeltaY_muon.root pdf_btag.root pdf_ttag.root pdf_wtag.root q2_btag.root q2_ttag.root q2_wtag.root

	python script/TxtDC.py ${var} 
        mkdir Variables/${var}

#Fit para cuando haga unfolding with combine 

        combineCards.py SR1T_muon=CR1_muon${var}.txt > Combined_muon.txt
        text2workspace.py Combined_muon.txt

        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
        plotImpacts.py -i impacts.json -o impacts
        mv impacts.pdf impacts_semiresolved.pdf
        mv  impacts.json  impacts_semireolved.json
        rm -f Combined_muon.*

        combineCards.py SR1T_muon=SR0T_muon${var}.txt > Combined_muon.txt
        text2workspace.py Combined_muon.txt

        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
        bash sed.sh
        plotImpacts.py -i impacts.json -o impacts
        mv impacts.pdf impacts_resolved.pdf
        mv  impacts.json  impacts_reolved.json
        rm -f Combined_muon.*

        combineCards.py SR1T_muon=SR1T_muon${var}.txt > Combined_muon.txt
        text2workspace.py Combined_muon.txt

        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
        bash sed.sh
        plotImpacts.py -i impacts.json -o impacts
        mv impacts.pdf impacts_boosted.pdf
        mv  impacts.json  impacts_boosted.json
        rm -f Combined_muon.*

        combineCards.py SR1T_muon=SR1T_muon${var}.txt SR0T_muon=SR0T_muon${var}.txt CR1_muon=CR1_muon${var}.txt > Combined_muon.txt
        text2workspace.py Combined_muon.txt

        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
        bash sed.sh
        plotImpacts.py -i impacts.json -o impacts
        mv impacts.pdf impacts_all.pdf
        


done


