#!/bin/bash
##
## Script to automatize pi.elf execution from NMIN to NMAX steps.
## Intended for Lesson 2 PCA LAB Delivery
## Felip Moll - 09/2012
##

#This function will run pi with $NMIN decimals $NEXEC times, and will get the mean exec. time.
function run
{  
    echo "" > /tmp/error
    x=1
    while [ $x -le $NEXEC ]
    do	
	/usr/bin/time -f %e ./$ELF $NMIN 1>/dev/null 2>>/tmp/error
	x=$(( $x + 1 ))	
    done

    TEMPS=0
    #Mitja de temps
    for line in $(cat /tmp/error)
    do	
	TEMPS=`echo "scale=2; $TEMPS + $line" | bc`
    done

    TEMPS=`echo "scale=4; $TEMPS / $NEXEC" | bc`
    
    echo "$NMIN $TEMPS" >> exec_$ELF.out
}

#This function performs the computations for the problem B of the lab session
function calc_graph_b
{
    export IFS=$'\n'
    echo "" > /tmp/graph_$ELF.out

    for line in $(cat exec_$ELF.out)
    do
	DECIMALS=$(echo $line | cut -d" " -f 1)
	TEMPS=$(echo $line | cut -d" " -f 2)

        X=`echo "scale=8; $TEMPS / $DECIMALS" | bc`
	echo "$DECIMALS $X" >> /tmp/graph_$ELF.out
    done
}

##
## MAIN FUNCTION
##
if [ $# != 5 ]
then
    echo ""
    echo "Usage: ./exec_elf.sh <NMIN> <NMAX> <NEXEC> <STEPS> <execname>"
    echo ""
    echo "Example: ./exec_elf.sh 500 2000 5 500 pi will run ./pi with number-of-something parameters (500, 2000), obtaining 500, 1000, 1500 and 2000 decimals"
    echo "Then, for each number-of-something parameter will repeat the experiment 5 times"
    echo ""
    echo "Results are stored in the file exec_pi.out in the current workdir."
    echo ""
else

echo "" > /tmp/error
NMIN=$1
NMAX=$2
NEXEC=$3
STEPS=$4
ELF=$5

echo "Running exec from $NMIN decimals to $NMAX decimals in steps of $STEPS, repeating experiment $NEXEC times"

#From NMIN to NMAX, in steps of $STEPS, run pi.
if [ -f exec_$ELF.out ]; then mv exec_$ELF.out exec_$ELF.out.`date +%H%M%S`; fi;
while [ $NMIN -le $NMAX ]
do
  run
  #We sleep half a second to let the system do their things and get less impact between our executions
  sleep 0.5
  NMIN=$(( $NMIN + $STEPS ))
done

#Normalize output format from .X to 0.X (optional)
sed -i 's/\ \./ 0./' exec_$ELF.out

#Obtain elapsed time/nºdecimals versus nºdecimals
calc_graph_b

#Print graphs
gnuplot -p -e "plot 'exec_$ELF.out' using 1:2 with linespoints"
gnuplot -p -e "plot '/tmp/graph_$ELF.out' using 1:2 with linespoints"

#Cleanup
rm /tmp/error
#rm /tmp/graph_$ELF.out
fi
