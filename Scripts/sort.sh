#!/bin/bash

sort()
{
	arr=("${!1}")
	len=${#arr[*]}

	outer=`expr $len - 1`

	#echo $len' of array '${arr[*]}
	
	for (( i=0; i <= $outer; i++ ))
	do
		inner=`expr $len - $i`
		for (( j=0; j < $inner; j++ ))
		do
			curr=${arr[$j]}
			next=${arr[`expr $j + 1`]}

			#echo $curr' > '$next

			if [[ $curr -gt $next ]];
			then
				arr[$j]=$next
				arr[`expr $j + 1`]=$curr
			fi
		done
	done

	echo ${arr[*]}
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

sort arr[@]
