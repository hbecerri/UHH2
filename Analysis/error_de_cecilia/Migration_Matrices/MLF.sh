#!/bin/bash

rm -f *.pdf

year='2016'
channel='muon'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

year='2017'
channel='muon'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

year='2018'
channel='muon'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

year='2016'
channel='electron'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

year='2017'
channel='electron'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

year='2018'
channel='electron'
root -l -b -q "Migration_matrix.C(\"${year}\",\"${channel}\")"

