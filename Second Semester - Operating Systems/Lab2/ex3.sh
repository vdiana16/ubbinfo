#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "Numar insuf de arg!"
	echo "Utilizare:$0 numedir"
	exit 1
elif [ ! -d $1 ]
then
	echo "$1 nu este un director "
	exit 2
fi
NTF=0
NTL=0
FILES=$(find $1 -type f)
for FILE in $FILES
do
	if file $FILE | grep -q 'ASCII text$'
	then
		echo "Fisier:" $FILE
		NTF=$(($NTF+1))
		NL=$(wc -l <$FILE)
		NTL=$(($NTL+$NL))
	fi
done
echo "Numar mediu linii:" $((NTL/NTF))
exit 0
