#!/bin/bash

sort -V $1 > sorted_lumis.txt

lastrun=-1
lastlumi=-1
firstrun=1
firstlumi=1
while read run lumi; do
    # New run
    if [ "$run" -ne "$lastrun" ]; then
	if (( $firstrun )); then
	    echo -n "{"
	else
	    end=$lastlumi
	    if (( ! $firstlumi )); then echo -n ", "; fi
	    echo -n "[$start, $end]"
	    printf "],\n "
	fi
	firstrun=0
	echo -n "\"$run\": ["
	firstlumi=1
	start=$lumi
	end=-1
    # Same run
    else
	# non-consecutive lumisections
	if [ $((lastlumi + 1)) -ne $lumi ]; then 
	    end=$lastlumi
	    if (( ! $firstlumi )); then echo -n ", "; fi
	    echo -n "[$start, $end]"
	    firstlumi=0
	    start=$lumi
	    end=-1
	fi
    fi
    lastrun=$run
    lastlumi=$lumi
done < sorted_lumis.txt

end=$lastlumi
if (( ! $firstlumi )); then echo -n ", "; fi
echo "[$start, $end]]}"

rm sorted_lumis.txt
