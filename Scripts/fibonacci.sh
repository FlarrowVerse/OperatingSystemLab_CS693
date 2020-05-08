#!/bin/bash

echo -n 'Enter a number: '
read n

if [ $n -gt 0 ];
then
	t1=1
	t2=0
	sum=0

	for (( i=1; i <= $n; i++ ))
	do
		echo $sum
		sum=`expr $t1 + $t2`
		t1=$t2
		t2=$sum
	done
	echo ''
else
	echo 'ERROR: Number should be greater than 0'
fi
