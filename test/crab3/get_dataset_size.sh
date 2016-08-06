#!/bin/bash

LIST=$1
ntup_total_size_byte=0

while read short dataset; do
    if (( `echo $short $dataset | grep -v '^#' | grep "/MINIAOD" | wc -l` )); then
	size_byte=`das_client --query "dataset=$dataset | grep dataset.size" | tail -1`
	if (( `echo $dataset | grep -E '/JetHT/|/TT|SMS|QCD' | wc -l` )); then conv_factor=0.04; else conv_factor=0.007; fi
	ntup_size_byte=`echo $size_byte $conv_factor | awk '{ printf "%d", $1*$2 }'`
	ntup_total_size_byte=$(($total_size_byte + $ntup_size_byte))
	echo "$ntup_total_size_byte $ntup_size_byte $short" | awk '{ printf "%3.2f TB - %5.0f GB - %15d - %s\n", $1/1073741824.0/1024.0, $2/1073741824.0, $2, $3 }'
    fi
done < $LIST
