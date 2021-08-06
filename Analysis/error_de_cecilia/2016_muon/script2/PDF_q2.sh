#!/bin/bash

rm -f -r pdf.root
rm -f -r q2.root

var_gen='(TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3])))))'

python createq2templates_SR1T.py 1 1
python New_q2_SR1T.py
mv templates_q2_SR1T.root q2.root

python createpdftemplates_SR1T.py 1 1
python New_PDF_SR1T.py 
mv templates_pdf_SR1T.root pdf.root

#python createq2templates_ttbar1.py 1 1 "${var_gen}"
#python New_q2_ttbar.py 1
#mv templates_q2_SR1T.root q2_ttbar1.root

#python createq2templates_ttbar2.py 1 1 "${var_gen}"
#python New_q2_ttbar.py 2
#mv templates_q2_SR1T.root q2_ttbar2.root

#python createpdftemplates_ttbar1.py 1 1 "${var_gen}"
#python New_PDF_ttbar.py 1
#mv templates_pdf_SR1T.root pdf_ttbar1.root

#python createpdftemplates_ttbar2.py 1 1 "${var_gen}"
#python New_PDF_ttbar.py 2
#mv templates_pdf_SR1T.root pdf_ttbar2.root



