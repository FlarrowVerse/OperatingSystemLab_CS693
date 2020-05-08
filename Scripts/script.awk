#!/bin/awk -f
BEGIN {
	FS="|";
	maxMarks=0;
	student="";
	count=0;
}
{
	if(count == 0) {
		count++;
	} else {
		total=0;
		for(i = 2; i <= 5; i++) {
			total += $i;
		}
		print $1 " scored " total " marks in total."
		if(total > maxMarks) {
			maxMarks = total;
			student = $1;
		}
	}
}
END {
	print student " recieved the highest total marks of " maxMarks;
}
