#!/bin/bash

echo -n 'Enter a year: '
read year

if [ $year -lt 0 ];
then
	echo 'ERROR: Year cannot be neagtive.'
elif [[ `expr $year % 400` -eq 0 || `expr $year % 4` -eq 0 && `expr $year % 100` -ne 0 ]];
then
	echo $year' is a leap year'
else
	echo $year' is not a leap year'
fi
