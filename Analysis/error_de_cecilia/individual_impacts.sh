#!/bin/bash

cd 2016_muon
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_muon/
text2workspace.py muon_2016.txt -o muon_2016.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("7053.01/7156.152*@0*1.02*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

cd 2017_muon
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_muon/
text2workspace.py muon_2017.txt -o muon_2017.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("7705/7810*@0*1.02*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

cd 2018_muon
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2018_muon/
text2workspace.py muon_2018.txt -o muon_2018.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("10251/10296*@0*1.02*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

cd 2016_muon_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_muon/
text2workspace.py muon_2016_750_900.txt -o muon_2016_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("6863/6801*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

cd 2017_muon_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_muon_750_900/
text2workspace.py muon_2017_750_900.txt -o muon_2017_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("7542/7722*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

cd 2018_muon_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2018_muon_750_900/
text2workspace.py muon_2018_750_900.txt -o muon_2018_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("10006/10141*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2016_electron
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_electron/
text2workspace.py electron_2016.txt -o electron_2016.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("2636.01/2697.152*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2017_electron
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron/
text2workspace.py electron_2017.txt -o electron_2017.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("2245/2345*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2018_electron
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2018_electron/
text2workspace.py electron_2018.txt -o electron_2018.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("3324/3314*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2018_electron_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2018_electron_750_900/
text2workspace.py electron_2018_750_900.txt -o electron_2018_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("2132/2179*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2017_electron_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2017_electron_750_900/
text2workspace.py electron_2017_750_900.txt -o electron_2017_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("1548/1521*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv


cd 2016_electron_750_900
bash MLF.sh
cd ~/public/theta/CMSSW_10_2_13/src/
cmsenv
cd /nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/error_de_cecilia/2016_electron_750_900/
text2workspace.py electron_2016.txt -o electron_2016.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_1:r_neg[1,0,20]' --PO map='.*/Ttbar_2:r_pos=expr;;r_pos("1673/1647*@0*(100+@1)/(100-@1)",r_neg,r_Asym[-2,-5,0])' --PO verbose
bash impacts.sh
cd ..
cmsenv

