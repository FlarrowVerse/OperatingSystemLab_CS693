#!/bin/bash

#completing first task
if [[ $# -le 0 ]];
then
	echo "Insufficient arguments."
else
	echo "Reading student details and sorting......"
	echo "Replacing lower case letters with upper case letters......"
	awk -f readscript.awk $1
	echo "Writing output to the file 'output-tr'"
	awk -f readscript.awk $1 > output-tr
	echo "--------------------------------------------------------------"
	echo "Unique name from the above file"
	cut -d '|' -f 1 < output-tr | sort > NAMES
	uniq -u NAMES > unique.txt
	cat unique.txt
	echo "--------------------------------------------------------------"
	echo -n "2nd Line from the file containing sorted student details: "
	head --lines=2 output-tr | tail --lines=1
	echo -n "3rd line from the file containing sorted student details: "
	head --lines=3 output-tr | tail --lines=1
	echo "-------------------------------------------------------------"
fi
