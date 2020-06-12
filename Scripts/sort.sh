#!/bin/bash

sort()
{
	arr=("${!1}")
	len=${#arr[*]}

	# outer=`expr $len - 1`
	
	for (( i=0; i <= ($len - 1); i++ ))
	do
		for (( j=0; j < ($len - $i - 1); j++ ))
		do
			if [[ ${arr[$j]} -gt ${arr[$j + 1]} ]];
			then
				temp=${arr[$j]}
				arr[$j]=${arr[$j + 1]}
				arr[($j + 1)]=$temp
			fi
		done
	done
	echo "Sorted Array: ${arr[*]}"
}

echo -n 'Enter number of elements: '
read n

declare -a arr
for(( i=0; i<$n; i++  ))
do
	echo -n 'arr['$i'] = '
	read input	
	arr[$i]=$input
done

echo "Original Array: ${arr[*]}"

sort arr[@]
