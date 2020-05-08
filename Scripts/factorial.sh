#!/bin/bash

# read a number from user
echo -n 'Enter a number: '
read num

if [ $num -lt 0 ];
then
	echo 'Negative Number'
else
	factorial=1
	while [ $num -gt 0 ];
	do
		factorial=`expr $factorial \* $num`
		num=`expr $num - 1`
	done
	echo 'Factorial = ' $factorial
fi

