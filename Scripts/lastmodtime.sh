#!/bin/bash

echo -n 'Enter file name: '
read file

modTime=`ls -lt | tr -s ' ' | grep -w $file | cut -d ' ' -f6-8` # full line for the file in long format
#modTime=`date -r $file`

if [[ $modTime ==  '' ]];
then
	echo 'ERROR: File not found.'
else
	echo 'Last Modification time for'$fullpath': '$modTime
fi
