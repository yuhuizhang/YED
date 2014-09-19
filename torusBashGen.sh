#!/bin/bash
N=6
nOrb=12
name1=TCTPv11
execute=TCTPHPC
memory=20000
machineFlag=1
dv=v0
dI=-0.10
dF=0.10
dStep=0.01
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
	    file=script/$name1\N$N\s$s\t$t$dv$dI
            mkdir $file
            cp $execute $file
            echo \ $N > $file/parameter
            echo \ $nOrb >> $file/parameter
            echo \ $s >> $file/parameter
            echo \ $t >> $file/parameter
	    echo \ $dI >> $file/parameter
	    echo \ $ratio >> $file/parameter

            echo \ Universe = vanilla > $file/ClassAds
            echo \ Executable = $execute >> $file/ClassAds
	    echo \ request_memory \= $memory >> $file/ClassAds

	    if [ $machineFlag = 1 ]; then
		echo \ +RequiresWholeMachine = True >> $file/ClassAds
		echo \ Requirements = \(Target.CAN_RUN_WHOLE_MACHINE =?= True\) >> $file/ClassAds
		echo \ Rank = Memory >> $file/ClassAds
	    fi

	    echo \ Output = \$\(Process\).out >> $file/ClassAds
            echo \ Error = \$\(Process\).err >> $file/ClassAds
            echo \ Log = \$\(Process\).log >> $file/ClassAds
            echo \ Notification = NEVER >> $file/ClassAds
            echo \ should_transfer_files = YES >> $file/ClassAds
            echo \ transfer_input_files = parameter >> $file/ClassAds
            echo \ when_to_transfer_output = ON_EXIT_OR_EVICT >> $file/ClassAds
            echo \ queue 1 >> $file/ClassAds
            t=$(($t+1))
	done
	s=$(($s+1))
    done
    dI=$(echo "$dI+$dStep" | bc)
done




