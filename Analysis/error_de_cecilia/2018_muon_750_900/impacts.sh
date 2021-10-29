#!/usr/bin/env bash
date

#declare -a POIS=(
#  "r_neg"
#  "Ac"
#)

declare -a POIS=(
  "r_1"
  "r_2"
  "r_3"
  "r_4"
)

export WORKSPACE=muon_2018_750_900.root
export VERBOSITY=0

#export SetParameters="rgx{r.+}=1,Ac=0.7"
#export SetParametersExplicit="r_neg=1,Ac=0.7"
#export SetParameterRanges="rgx{r.+}=0.5,2:Ac=-10,5"
#export redefineSignalPOIs="Ac,r_neg"

export SetParametersExplicit="r_1=1,r_2=1,r_3=1,r_4=1"
export SetParameterRanges="r_1=0.5,2:r_2=0.5,2:r_3=0.5,2:r_4=0.5,2"
export redefineSignalPOIs="r_1,r_2,r_3,r_4"

export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
#export ASIMOV=""



###IMPACTS
echo
echo
echo "DO INITIAL FIT"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE -v $VERBOSITY --doInitialFit --robustFit 1 -m 125 --redefineSignalPOIs $redefineSignalPOIs --setParameters $SetParametersExplicit --cminDefaultMinimizerStrategy 1 --saveWorkspace $ASIMOV --setCrossingTolerance 0.00000000000001



echo
echo
echo "DO FITS"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE --robustFit 1 --doFits -m 125 --redefineSignalPOIs $redefineSignalPOIs  --setParameters $SetParametersExplicit --cminDefaultMinimizerStrategy 0 $ASIMOV --parallel 20



echo
echo
echo "STAT ONLY UNCERTAINTY (ALL NUISANCES FROZEN)"
echo
echo
combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n _paramFit_Test_allConstrainedNuisancesFrozen --freezeParameters allConstrainedNuisances $ASIMOV



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

