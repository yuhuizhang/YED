#!/bin/bash
N=6
nOrb=12
name1=TCTPv11
dv=v0
v0I=-0.10
v0F=0.10
vStep=0.01
ratio=1
ratioFlag=1 # 1 is ratio = 1; 0 is other ratios

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
while [ $(echo "$v0I<=$v0F" | bc) -eq 1 ]; do
    echo $v0I
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
	    file=script/$name1\N$N\s$s\t$t$dv$v0I
	    mv $file/r* $dataFile
            t=$(($t+1))
	done
	s=$(($s+1))
    done
    v0I=$(echo "$v0I+$vStep" | bc)
done




