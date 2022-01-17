#!/bin/bash

# INPUT VALIDATION
#terminate if there are not 2 arguments passed to the script
if [[ "$#" != 2 ]]
then
	echo "Usage ./csv2html.sh <csv input> <html output>"
	exit 1

fi

#terminate if the first argument is not a name of an existing file
if [[ ! -f $1 ]]
then
	echo "Error $1 is not a valid file"
	exit 1
fi

# CONVERT TO HTML
{
echo "<table>"

while read line
do
	echo "<TR><TD>$line</TD></TR>" | sed -e 's/,/<\/TD><TD>/g'
done < $1

echo "</table>"
} > $2