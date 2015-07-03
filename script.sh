#!/bin/bash

#######
# Script config
###
e="\e[1;31m" # Error color
r="\e[m"     # Reset color


#######
# Define Input / Output
###
# Default output file's name
output="result.xml"

# Check the number of arguments
if [ $# == 1 ]; then
	input=$1
elif [ $# == 2 ]; then
	input=$1
	output=$2
else
	echo -e "${e}Invalide arguments !\n"
	echo -e "Usage : \n$0 <input file> [output file]$r"
	exit 1
fi

# Check if the file exist
if [ ! -f $input ]; then
	echo -e "${e}File \"${input}\" not found.$r"
	exit 1
fi


#######
# Parse file
###
# Init variables
total=`grep -Po "^ Total asserts : (\s*)(\d*)" $input | sed 's/[^0-9][^0-9]*//'`
failures=`grep -Po "^ Failed        : (\s*)(\d*)" $input | sed 's/[^0-9][^0-9]*//'`

# Loop trough errors message
grep -Po "\[_not_set_\]:(.*)" $input | sed 's/^[^%]* User message: \[//' | while read -r line ; do
	echo -e "  <testcase name=\"${line::-1}\" classname=\"FRUIT\">\n    <failure message=\"\" type=\"\"/>\n  </testcase>" >> tmp.txt
done

content=`cat tmp.txt`
rm tmp.txt

#######
# Write to output file
###
echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" > $output
echo "<testsuite name=\"FRUIT tests\" tests=\"$total\" failures=\"$failures\">" >> $output
echo -e "$content" >> $output
echo "</testsuite>" >> $output