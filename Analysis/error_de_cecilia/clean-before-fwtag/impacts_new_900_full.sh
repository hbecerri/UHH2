#!/usr/bin/env bash
date

#declare -a POIS=(
#  "r_neg"
#  "Ac"
#)

declare -a POIS=(
  "r_nMlo"
  "Ac"
  "r_nMhi"
  "r_pMhi"
)

export WORKSPACE=Ac_900.root
export VERBOSITY=0

export SetParametersExplicit="r_nMlo=1,Ac=0.0084,r_nMhi=1,r_pMhi=1"
export SetParameterRanges="r_nMlo=-2.5,3.5:Ac=-2,2:r_nMhi=0.5,2:r_pMhi=0.5,2"
export redefineSignalPOIs="r_nMlo,Ac,r_nMhi,r_pMhi"


export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
#export ASIMOV=""


combine -M MultiDimFit --algo singles -d $WORKSPACE -n .part3E.snapshot -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace $ASIMOV
 
mv higgsCombine.part3E.snapshot.MultiDimFit.mH125.root higgsCombine_initialFit_Test.MultiDimFit.mH125.root

echo
echo
echo "DO FITS"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE --robustFit 1 --doFits -m 125 --redefineSignalPOIs $redefineSignalPOIs  --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --cminDefaultMinimizerStrategy 0 $ASIMOV --parallel 20



echo
echo
echo "STAT ONLY UNCERTAINTY (ALL NUISANCES FROZEN)"
echo
echo
combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n _paramFit_Test_allConstrainedNuisancesFrozen --freezeParameters allConstrainedNuisances $ASIMOV



echo
echo
echo "CREATE IMPACTS JSON"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE -o impacts.json -m 125 --redefineSignalPOIs $redefineSignalPOIs



echo
echo
echo "CREATE PLOTS"
echo
echo
for POI in ${POIS[@]}; do
  plotImpacts.py -i impacts.json -o $POI --POI $POI
done
echo
echo

