#!/bin/tcsh
# Author: Janos Karancsi
# Usage: 
#   source_parallel.csh < scriptname.csh >
# or
#   source_parallel.csh < scriptname.csh > < N_parallel <= 10 >

if ( $#argv == 1 ) then
    source $1
    exit
endif
set script=$1
set npar=$2
if ( $npar > 10 ) then
    echo "Too many jobs!, setting N_parallel = 10"
    set npar=10
endif

set username=`whoami`
set time=`date | sed "s;:;;g" | awk '{ printf "%d_%s_%d_%d\n",$6,$2,$3,$4 }'`
set tempdir="parsource_tempdir_$time"
#sed -i '/^$/d' $script # remove empty lines
set nlines=`wc -l $script | awk '{ print $1 }'`
if ( $nlines ) then
    mkdir $tempdir
    touch $tempdir/pids.txt
    set nrun="0"
    foreach n ( `seq 1 $nlines` )
	sed -n $n'p' $script >! $tempdir/$n.csh
	set last_20_id=`tail -$npar $tempdir/pids.txt | tr "\n" " "`
	if ( `cat $tempdir/pids.txt | wc -l` ) set nrun=`ps $last_20_id | sed '1d' | wc -l`
        while ( $nrun == $npar )
            sleep 5
	    set nrun=`ps $last_20_id | sed '1d' | wc -l`
	    printf "\rRunning "$script", bkg jobs: %d, Progress: %"`expr "$nlines" : ".*"`"d/%d" $nrun `expr $n - $nrun - 1` $nlines
        end
        ( source $tempdir/$n.csh >&! "$tempdir"/`printf "%06d" $n`.log &; echo $! >> $tempdir/pids.txt ) >& /dev/null
        printf "\rRunning "$script", bkg jobs: %d, Progress: %"`expr "$nlines" : ".*"`"d/%d" `expr $nrun + 1` `expr $n - $nrun - 1` $nlines
        sleep 0.2
    end
    # Wait until all files are downloaded
    set nrun=`ps $last_20_id | sed '1d' | wc -l`
    while ( $nrun )
	sleep 5
	set nrun=`ps $last_20_id | sed '1d' | wc -l`
        printf "\rRunning "$script", bkg jobs: %d, Progress: %"`expr "$nlines" : ".*"`"d/%d" $nrun `expr $nlines - $nrun` $nlines
    end
    printf "\rRunning "$script", bkg jobs: %d, Progress: %d/%d\n" $nrun $nlines $nlines
    cat $tempdir/*.log >>! parsource_$time.log
    echo "Done. logfile: parsource_$time.log"
    rm -r $tempdir
    unset nrun
    unset last_20_id
endif
unset script
unset npar
unset username
unset tempdir
unset nlines



