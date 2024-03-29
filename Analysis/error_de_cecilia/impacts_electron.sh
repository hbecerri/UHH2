#!/usr/bin/env bash
date

declare -a POIS=(
  "r_neg"
  "Ac"
)

export WORKSPACE=Ac_electron.root
export VERBOSITY=0

export SetParameters="rgx{r.+}=1,Ac=0.72"
export SetParametersExplicit="r_neg=1,Ac=0.72"
export SetParameterRanges="rgx{r.+}=0.5,2:Ac=-10,5"
export redefineSignalPOIs="Ac,r_neg"

#export SetParameters="rgx{r.+}=1,r_pos=1"
#export SetParametersExplicit="r_neg=1,r_pos=1"
#export SetParameterRanges="rgx{r.+}=0.5,2:r_pos=0.5,2"
#export redefineSignalPOIs="r_pos,r_neg"


export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
#export ASIMOV=""



###IMPACTS
echo
echo
echo "DO INITIAL FIT"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE -v $VERBOSITY --doInitialFit --robustFit 1 -m 125 --redefineSignalPOIs $redefineSignalPOIs --setParameters $SetParameters --setParameterRanges $SetParameterRanges --cminDefaultMinimizerStrategy 0 --saveWorkspace $ASIMOV



echo
echo
echo "DO FITS"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE --robustFit 1 --doFits -m 125 --redefineSignalPOIs $redefineSignalPOIs  --setParameters $SetParametersExplicit --setParameterRanges $SetParameterRanges --cminDefaultMinimizerStrategy 0 $ASIMOV --parallel 20



echo
echo
echo "STAT ONLY UNCERTAINTY (ALL NUISANCES FROZEN)"
echo
echo
combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParameters --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n _paramFit_Test_allConstrainedNuisancesFrozen --freezeParameters allConstrainedNuisances $ASIMOV



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

