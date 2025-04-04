    #!/bin/bash


# ./ex1.sh numar natural
# verici numarul de argumente 

if [ $# -eq 0 ] 
then
	echo "Numar insuficient de argumente  !"
	echo "Utilizare: $0 N"
	exit 1
fi
#N=$1
VALORI=$(seq 1 $1)
for X in $VALORI
do
	touch "file_X.txt"
	sed -n ''$X', +5p' /etc/passwd >"file_$X.txt"
done

    
