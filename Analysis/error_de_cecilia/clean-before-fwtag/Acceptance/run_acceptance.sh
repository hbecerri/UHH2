#!/bin/bash

#rm -f electron_ttbar1.txt
#rm -f electron_ttbar2.txt
#rm -f muon_ttbar1.txt
#rm -f muon_ttbar2.txt

StringVal='
wgtMC__PDF[1]
wgtMC__PDF[2]
wgtMC__PDF[3]
wgtMC__PDF[4]
wgtMC__PDF[5]
wgtMC__PDF[6]
wgtMC__PDF[7]
wgtMC__PDF[8]
wgtMC__PDF[9]
wgtMC__PDF[10]
wgtMC__PDF[11]
wgtMC__PDF[12]
wgtMC__PDF[13]
wgtMC__PDF[14]
wgtMC__PDF[15]
wgtMC__PDF[16]
wgtMC__PDF[17]
wgtMC__PDF[18]
wgtMC__PDF[19]
wgtMC__PDF[20]
wgtMC__PDF[21]
wgtMC__PDF[22]
wgtMC__PDF[23]
wgtMC__PDF[24]
wgtMC__PDF[25]
wgtMC__PDF[26]
wgtMC__PDF[27]
wgtMC__PDF[28]
wgtMC__PDF[29]
wgtMC__PDF[30]
wgtMC__PDF[31]
wgtMC__PDF[32]
wgtMC__PDF[33]
wgtMC__PDF[34]
wgtMC__PDF[35]
wgtMC__PDF[36]
wgtMC__PDF[37]
wgtMC__PDF[38]
wgtMC__PDF[39]
wgtMC__PDF[40]
wgtMC__PDF[41]
wgtMC__PDF[42]
wgtMC__PDF[43]
wgtMC__PDF[44]
wgtMC__PDF[45]
wgtMC__PDF[46]
wgtMC__PDF[47]
wgtMC__PDF[48]
wgtMC__PDF[49]
wgtMC__PDF[50]
wgtMC__PDF[51]
wgtMC__PDF[52]
wgtMC__PDF[53]
wgtMC__PDF[54]
wgtMC__PDF[55]
wgtMC__PDF[56]
wgtMC__PDF[57]
wgtMC__PDF[58]
wgtMC__PDF[59]
wgtMC__PDF[60]
wgtMC__PDF[61]
wgtMC__PDF[62]
wgtMC__PDF[63]
wgtMC__PDF[64]
wgtMC__PDF[65]
wgtMC__PDF[66]
wgtMC__PDF[67]
wgtMC__PDF[68]
wgtMC__PDF[69]
wgtMC__PDF[70]
wgtMC__PDF[71]
wgtMC__PDF[72]
wgtMC__PDF[73]
wgtMC__PDF[74]
wgtMC__PDF[75]
wgtMC__PDF[76]
wgtMC__PDF[77]
wgtMC__PDF[78]
wgtMC__PDF[79]
wgtMC__PDF[80]
wgtMC__PDF[81]
wgtMC__PDF[82]
wgtMC__PDF[83]
wgtMC__PDF[84]
wgtMC__PDF[85]
wgtMC__PDF[86]
wgtMC__PDF[87]
wgtMC__PDF[88]
wgtMC__PDF[89]
wgtMC__PDF[90]
wgtMC__PDF[91]
wgtMC__PDF[92]
wgtMC__PDF[93]
wgtMC__PDF[94]
wgtMC__PDF[95]
wgtMC__PDF[96]
wgtMC__PDF[97]
wgtMC__PDF[98]
wgtMC__PDF[99]
weight_murmuf_downdown
weight_murmuf_upup
weight_murmuf_downnone
weight_murmuf_upnone
weight_murmuf_nonedown
weight_murmuf_noneup
FSRup
FSRdown
ISRup
ISRdown
'

num=0
for var in $StringVal; do
        num=$[num+1]
        echo ${num}
        root -l -b -q "Acceptance.C(\"${var}\",${num})"
done

num='110'
var='1'
root -l -b -q "Acceptance_hdamp.C(\"${var}\",${num})"

var='1'
num='111'
root -l -b -q "Acceptance_hdampdown.C(\"${var}\",${num})"





