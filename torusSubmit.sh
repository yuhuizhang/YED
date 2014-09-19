#!/bin/bash
N=6
nOrb=12
name1=TCTPv11
execute=TCTPHPC
dv=v0
dI=-0.10
dF=0.10
dStep=0.01
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
        #submit the file
	    file=script/$name1\N$N\s$s\t$t$dv$dI
	    cd $file
	    #condor_submit ClassAds
	    ./$execute
	    cd ../../
	    t=$(($t+1))
	done
	s=$(($s+1))
    done
    dI=$(echo "$dI+$dStep" | bc)
done

