#!/bin/awk -f
BEGIN {
	FS="|";
	count=0;
}
{
	student[$2]=$0;
	roll[count]=$2;
	count++;
}
END {
	for(i = 0; i < count; i++) {
		for(j = 0; j < count-i-1; j++) {
			if(roll[j] < roll[j+1]) {
				temp=roll[j];
				roll[j]=roll[j+1];
				roll[j+1]=temp;
			}
		}
	}
	for(i = 0; i < count; i++) {
		cmd = "tr [a-z] [A-Z]";

		print student[roll[i]] | cmd;
#		close(cmd, "to");
#		cmd |& getline out;
#		print student[roll[i]] | cmd;
#		print out > "output";
	}
}

