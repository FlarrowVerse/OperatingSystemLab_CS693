#!/bin/bash

echo -n 'Enter username: '
read user

result=`grep -c $user /etc/passwd`

if [[ $result -eq 0 ]];
then
	echo $user' is an invalid user'
else
	echo $user' is a valid user'
fi
