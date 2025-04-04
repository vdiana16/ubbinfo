#!bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizaare: $0 nume_director"	
	exit 1
fi

FILES=$(find $1 -type f)
for FILE in $FILES
do
	if file $FILE | grep -q 'ASCII text$'
	then
		echo "Fisier:" $FILE
		NL=$(cat $FILE | wc -l)
		if [ $NL -lt 6 ]
		then
			cat $FILE
		else
			echo 'Head'
			head -3 $FILE
			echo 'Tail'
			tail -3 $FILE
		fi
	fi
done
exit 0

