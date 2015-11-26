#!/bin/bash

getmaple(){
	lines=`awk 'END{ print NR; }' ./result.txt`
	awk -F" " '{ if( NR == '$lines'-6 ){ printf("%s%s%s ",$3,$4,$5); } else if( NR >= '$lines'-4 ){ printf("%s ",$3); } }' ./result.txt >> ${all}/DATE.txt
	echo "" >> ${all}/DATE.txt
}

recurrence(){
	cd $1
	for file in `ls`
	do
		if [ -d $file ]
			then
			recurrence $file
		elif [ $file == "test.sh" ]
			then
			make
			for((i=0;i<100;i++))
			do 
				./$file
				pwd | awk -F"/" '{ printf("%s ",$NF); }' >> ${all}/DATE.txt
				getmaple
				rm coverage iroot.db memo.db pct.histo sinfo.db sinst.db stat.out test.histo result.txt
			done
		fi
	done

	cd ..
}

all=$PWD
rm ${all}/DATE.txt
recurrence "."