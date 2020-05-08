#!/bin/bash

if [[ $# -le 0 ]];
then
	echo "Insufficient arguments."
else
	awk -f script.awk $1
fi
