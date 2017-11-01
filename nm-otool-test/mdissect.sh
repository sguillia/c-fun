#!/bin/bash

# Same as "dissect.sh" but without stdin

### Test ft_nm on truncated files
### Run this in a temporary directory, like /tmp

#set -e # Stop on error

if [ -z "$1" ] || [ -z "$2" ]
then
	echo "Usage: $0 ./ft_nm file"
   	exit 1
fi

filename=$2

# Retrieve size and trim spaces
size=$(wc -c < "$filename" | xargs)

echo $filename $size

for (( i=$size; i>0; i--))
do
	outname="$filename.part$i.__tmp"
	head -c $i "$filename" > "$outname"
	$( $1 $outname 1>/dev/null 2>/dev/null )
	#$( head -c $i "$filename" | $1 - 1>/dev/null 2>&1 )
	retval=$?
	echo -n "Part $i: "
	if [ $retval -ne 0 ]
	then
		if [ $retval -ne 1 ]
		then
			echo "Fatal error: exit status $retval"
			exit
		else
			echo "Exit 1"
		fi
	else
		echo "Ok"
	fi
	rm $outname
done
