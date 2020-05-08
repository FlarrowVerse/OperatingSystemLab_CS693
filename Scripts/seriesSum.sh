#!/bin/bash

n=$1

if [ $n -le 0 ];
then
	echo 'ERROR: n should be greater than 0'
else
	sum=0
	for (( i=1;i<=$n;i++ ))
	do
		sum=`expr $sum + $i`
	done
	echo 'Sum = '$sum
fi
