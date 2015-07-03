#!/bin/bash

#######
# Script config
###
e="\e[1;31m"  # Error color
r="\e[m"      # Reset color
d="data.temp" # Tempory file for data extraction

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
# Init parsing variables
start="Start of FRUIT summary:"
end="end of FRUIT summary"
flag=false

# Extract data
cat $input | while read -r line ; do
	# Start of text
	if [[ $line == *$start* ]]; then
		flag=true
	fi

	if [ $flag == true ]; then
		echo -e "$line" >> $d
	fi

	# End of text
	if [[ $line == *$end* ]]; then
		flag=false
	fi
done

# Init result variables
total=`grep -Po "^Total asserts : (\s*)(\d*)" $d | sed 's/[^0-9][^0-9]*//'`
failures=`grep -Po "^Failed        : (\s*)(\d*)" $d | sed 's/[^0-9][^0-9]*//'`

# Loop through errors message
grep -Po "\[_not_set_\]:(.*)" $d | sed 's/^[^%]* User message: \[//' | while read -r line ; do
	echo -e "  <testcase name=\"${line::-1}\" classname=\"FRUIT\">\n    <failure message=\"\" type=\"\"/>\n  </testcase>" >> tmp.txt
done

# Load errors content
if [ -f "tmp.txt" ]; then
	content=`cat tmp.txt`
	rm tmp.txt
fi

# Remove tempory file
rm $d

# Add unidentified tests
for nb in `seq 1 $(($total-$failures))`; do
	content="$content\n  <testcase name=\"Test $nb\" classname=\"FRUIT\"></testcase>"
done

#######
# Write to output file
###
echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" > $output
echo "<testsuite name=\"FRUIT tests\" tests=\"$total\" failures=\"$failures\">" >> $output
echo -e "$content" >> $output
echo "</testsuite>" >> $output