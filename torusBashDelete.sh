#!/bin/bash
N=8
nOrb=16
name1=TCTP
execute=TCTPHPC

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
#loop
s=$(($NDiv/2))
while [ $s -le $NDiv ]; do
    t=$s
    while [ $t -le $NDiv ]; do
        echo $s and $t
	file=script/$name1\N$N\s$s\t$t
	rm -r $file
        t=$(($t+1))
    done
    s=$(($s+1))
done




