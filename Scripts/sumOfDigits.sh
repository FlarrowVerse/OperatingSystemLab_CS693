#!/bin/bash

echo -n 'Enter a number: '
read num

sum=0 # sum of digits

if [ $num -lt 0 ];
then
	num=`expr 0 - $num`
fi

while [ $num -gt 0 ];
do
	lastDigit=`expr $num % 10`
	sum=`expr $sum + $lastDigit`
	num=`expr $num / 10`
done

echo 'Sum of Digits: '$sum
