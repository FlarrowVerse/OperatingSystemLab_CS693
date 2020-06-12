#!/bin/bash

#completing first task
if [[ $# -le 0 ]];
then
	echo "Insufficient arguments."
else
	echo "Reading student details and sorting......"
	echo "Replacing lower case letters with upper case letters......"
	awk -f readscript.awk $1
	echo "Writing output to the file 'output'"
	awk -f readscript.awk $1 > output.txt
	echo "--------------------------------------------------------------"
	echo "Unique name from the above file"
	cut -d '|' -f 1 < output.txt | sort > NAMES
	uniq -u NAMES >> output.txt
	cat output.txt
	echo "--------------------------------------------------------------"
	echo -n "2nd Line from the file containing sorted student details: "
	head --lines=2 output.txt | tail --lines=1
	echo -n "3rd line from the file containing sorted student details: "
	head --lines=3 output.txt | tail --lines=1
	echo "-------------------------------------------------------------"
fi
