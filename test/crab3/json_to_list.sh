#!/bin/bash

while read run lumis; do
    run=`echo $run | sed "s;\";;g;s;:;;g;s;{;;g;" | awk '{ print $1 }'`
    for lumi in $lumis; do
	if (( `echo $lumi | grep '\[' | wc -l` )); then
	    start=`echo "$lumi" | sed "s;,;;g;s;\[;;g"`
	else
	    end=`echo "$lumi" | sed "s;,;;g;s;\];;g;s;};;g"`
	    for i in `seq $start $end`; do echo "$run $i"; done
	fi
    done
done < $1
