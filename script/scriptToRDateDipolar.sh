#!/bin/bash
N=8
nOrb=16
name1=dipolar
dI=0
dF=1.5
dStep=0.1
ratio=1
ratioFlag=1 # 1 is ration = 1; 0 is other ratios

# get common divider NDiv
NDiv=$(($N))
while [ $NDiv -ge 1 ]; do
  if [ $(($N%$NDiv)) -eq 0 -a $(($nOrb%$NDiv)) -eq 0 ]
  then
    break
  else
    NDiv=$(($NDiv-1))
  fi
done

mkdir script
mkdir rawData
mkdir rawData/$name1
mkdir rawData/$name1/N$N/
#loop
while [ $(echo "$dI<=$dF" | bc) -eq 1 ]; do
    echo $dI
    s=$(($NDiv/2))
    while [ $s -le $NDiv ]; do
	if [ $ratioFlag -eq 0 ]
	then 
	    t=$(($NDiv/2))
	else
	    t=$s
	fi
	while [ $t -le $NDiv ]; do
            echo $s and $t
        #make data file
	    dataFile=rawData/$name1/N$N/s$s\t$t
            mkdir $dataFile
        #bash
	    file=script/$name1\N$N\s$s\t$t\d$dI
	    mv $file/r* $dataFile
            t=$(($t+1))
	done
	s=$(($s+1))
    done
    dI=$(echo "$dI+$dStep" | bc)
done




