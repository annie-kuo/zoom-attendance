#!/bin/bash

# INPUT VALIDATION
#terminate if there are not 2 arguments passed to the script
if [[ "$#" != 2 ]]
then
	echo "Usage fixformat.sh <dirname> <opfile>"
	exit 1

fi

#terminate if the first argument is not a name of an existing directory
if [[ ! -d $1 ]]
then
	echo "Error $1 is not a valid directory"
	exit 1
fi

# REFORMAT DATA
directory=$1
outputFile=$2

#find files of interest
set $(find $directory  -name '[Ll][Aa][Bb]-?.[Cc][Ss][Vv]')

#write the output file
echo "User Email,Name (Original Name),Lab,Total Duration (Minutes)" > $outputFile 

#loop through each appropriate file and generate the reformatted data
while [[ ! -z "$1" ]]
do
	file=$1
	
	#determine which kind of format is the file written in
	if [[ $(head -1 $file) = 'Name (Original Name),User Email,Total Duration (Minutes),Guest' ]]
	then
		format='format1'
	else
		format='format2'
	fi

	#determine the lab letter the file pertains to
	filename="$(basename -- $file)"
	lab=${filename:4:1}
	labCap=${lab^}
	
	#reformat the data according to its original format
	if [[ $format = 'format1' ]]
	then	
		{
			read
			#read and parse each line
			while IFS=, read -r name email duration guest || [ -n "$name" ]
			do
				#write the pertinent information to the ouput file
				echo $email,$name,$labCap,$duration >> $outputFile
		
			done
		} < $file
	else
		{
			read
			#read and pase each line
			while IFS=, read -r name email join leave duration guest || [ -n "$name" ]
			do
				#write the pertinent information to the output file
				echo $email,$name,$labCap,$duration >> $outputFile
				
			done
		} < $file

	fi
	
	#go to next file
	shift
done


#end of algorithm
exit 0
