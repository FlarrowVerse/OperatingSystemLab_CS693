#!/bin/bash

menu()
{
	echo 'MENU::'
	echo '	1. Check file permissions'
	echo '	2. Check No. of files and directories'
	echo '	3. Check No. of connected users'
	echo '	0. Exit'
	echo -n 'Enter your choice: '
	read choice

	case "$choice" in
		"1") echo -n 'Enter file name: '
		read file
		if [[ -a $file ]];
		then
			echo 'File permissions of '$file': '`ls -lt | grep $file | cut -d ' ' -f 1`
		else
			echo 'ERROR: File does not exist'
		fi ;;
		"2") echo 'Total No. of files and directories in this directory: '`ls -l | wc -l` ;;
		"3") echo 'Total No. of connected users: '`who | wc -l` ;;
		"0") echo 'Stopping script......'
		exit;;
		*) echo 'ERROR: Invalid choice.';;
	esac

}


while [ 1 ];
do
	menu
done
