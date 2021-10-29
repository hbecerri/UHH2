#!/bin/bash


rm -f -r *.root 
rm -f -r *.txt
rm -f -r *.pdf
rm -f -r *.json

year='2017'
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'

declare -a StringArray=("DeltaY")
declare -a StringArray2=("rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900")

for var in ${StringArray[@]}; do
        echo ${var}
	python script/Input_file.py ${var}
        python script/Get_UF_OF.py ${var}
done

for var in ${StringArray[@]}; do
        root -l -b -q "script/all_unfolding_data_750.C(\"${var}\",\"${var_gen}\")"
        root -l -b -q "script/all_unfolding_data_900.C(\"${var}\",\"${var_gen}\")"
done


cp script3/pdf_ttbar1.root .
cp script3/q2_ttbar1.root .

cp script3/pdf_ttbar2.root .
cp script3/q2_ttbar2.root .

cp script3/pdf_ttbar3.root .
cp script3/q2_ttbar3.root .

cp script3/pdf_ttbar4.root .
cp script3/q2_ttbar4.root .


hadd -f DeltaY.root DeltaY_muon.root Input_undfolding_data_750.root Input_undfolding_data_900.root pdf_ttbar1.root q2_ttbar1.root pdf_ttbar2.root q2_ttbar2.root pdf_ttbar3.root q2_ttbar3.root pdf_ttbar4.root q2_ttbar4.root

python datacard.py
 
#text2workspace.py muon_2017_750_900.txt -o muon_2017_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("7542/7722*@0*(100+@1)/(100-@1)",r_neg,Ac[-2,-5,0])' --PO verbose
 
#text2workspace.py muon_2017_750_900.txt -o muon_2017_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_1[1,0,20]' --PO map='.*/Ttbar_2:r_2[1,0,20]' --PO map='.*/Ttbar_3:r_3[1,0,20]' --PO map='.*/Ttbar_4:r_4[1,0,20]'   --PO verbose

