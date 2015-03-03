#!/bin/tcsh
# Author: Janos Karancsi
# E-mail: janos.karancsi@cern.ch
# Tool: multicrab-like tool to create, submit, get status of crab3 tasks for B2G TTreeNtuples
#       When jobs finish, we can also get report and download all output files locally

echo "Usage:"                                                    >! Usage.txt
echo "  source crab3_B2GTTreeNtuples.csh <cmd> <TASKNAME> ..."   >> Usage.txt
echo "  there is a default safety mechanism for each command"    >> Usage.txt
echo "  add --run at the end to excecute them"                   >> Usage.txt
echo ""                                                          >> Usage.txt
echo "Commands:"                                                 >> Usage.txt
echo "1) create <TASKNAME> <DATASETS.txt> <SE_SITE> <SE_USERDIR>">> Usage.txt
echo "  The txt file should contain a short name and the"        >> Usage.txt
echo "  B2GEdmNTuple dataset on each line"                       >> Usage.txt
echo "  SE_SITE and SE_USERDIR should be the location you want"  >> Usage.txt
echo "  to send the output to, eg:"                              >> Usage.txt
echo "  T2_HU_Budapest"                                          >> Usage.txt
echo "  /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple"        >> Usage.txt
echo ""                                                          >> Usage.txt
echo "2) submit <TASKNAME>"                                      >> Usage.txt
echo "  Submit tasks to the grid (check cfg files first)"        >> Usage.txt
echo ""                                                          >> Usage.txt
echo "3) status <TASKNAME>"                                      >> Usage.txt
echo "  Check status of tasks"		                         >> Usage.txt
echo "" 						         >> Usage.txt
echo "4) report <TASKNAME>"                                      >> Usage.txt
echo "  Show commands to get report of tasks"		         >> Usage.txt
echo "" 						         >> Usage.txt
echo "5) download <TASKNAME> <DLDIR>"                            >> Usage.txt
echo "  Download all root output files from the Storage"         >> Usage.txt
echo "  element to a local directory DLDIR"                      >> Usage.txt
echo "  Check that the SRM site name and url is defined for"     >> Usage.txt
echo "  SE_SITE in the se_util.csh script (look for SITE_INFO)"  >> Usage.txt
echo "" 						         >> Usage.txt
echo "6) make_ttrees <TASKNAME> <INDIR> <OUTDIR> <NPARALLEL>"    >> Usage.txt
echo "  Produce locally TTreeNtuples from EdmNtuples"            >> Usage.txt
echo "  Multiple background cmsRuns can be run in parallel"      >> Usage.txt
echo "  Useful if you have small samples (Few GB)"               >> Usage.txt

if ( $1 == "-h" || $1 == "--help" || $#argv < 2 ) then
    cat Usage.txt; rm Usage.txt; exit
endif

# options
set cmd=$1
set TASKNAME=$2
# Working directory name (created in the current directory)
set TASKDIR="B2G_ttree_"$TASKNAME

# Aliases
if ( ! (-e $PWD/source_parallel.csh) || ! (-e $PWD/se_util.csh) ) then
    echo "Please run this script from the same directory where\nsource_parallel.csh and se_util.csh is or copy them here" 
    exit
endif
# script that takes another script as argument and runs n lines in parallel
# used by se_util.csh
alias par_source 'source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \!*'
# Storage element utility (ls, cp, dl, mkdir etc commands)
alias se         'source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \!*'

set rest_args=""
foreach n ( `seq 3 $#argv` )
    set rest_args="$rest_args "$argv[$n]
end
if ( `echo "$rest_args" | grep "\-\-run" | wc -l` ) then
    alias eval_or_echo   'echo \!* >! temp.csh; source temp.csh; rm temp.csh'
    alias source_or_peek 'echo "> Add --run option or Run this script:\nsource "\!*"\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
    set dry="0"
else
    alias eval_or_echo   'echo \!*'
    set dry="1"
endif


if ( `echo $cmd | grep "create" | wc -l` ) then
    if ( $#argv < 5 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set TXT_FILE=$3
    set SE_SITE=$4
    set SE_USERDIR=$5
    mkdir $TASKDIR
    echo "SE_SITE "$SE_SITE >! $TASKDIR/config.txt
    echo "SE_USERDIR "$SE_USERDIR >> $TASKDIR/config.txt
    if ( !(-f $TXT_FILE) ) then
	echo "$TXT_FILE doesn't exist"; exit
    endif
    cp $TXT_FILE $TASKDIR/input_datasets.txt
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_ttreentuple_py.txt > $TASKDIR/crab_template_ttreentuple_py.txt
    set N=`grep "/" $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
	set SHORT=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set DATASET=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
	sed "s;TASKNAME;$SHORT;;s;DATASET;$DATASET;" $TASKDIR/crab_template_ttreentuple_py.txt > $TASKDIR/crab_$SHORT.py
    end
    rm $TASKDIR/crab_template_ttreentuple_py.txt
    echo "Config files ready in directory: "$TASKDIR
    ls -ltr $TASKDIR

else if ( `echo $cmd | grep "submit" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach cfg_file ( `ls -ltr $TASKDIR/*.py | awk '{ print $NF }'`)
        eval_or_echo "crab submit -c $cfg_file --wait"
    end

else if ( `echo $cmd | grep "status" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `ls -ltrd $TASKDIR/* | grep "^d" | awk '{ print $NF }'`)
        eval_or_echo "crab status -d $dir"
    end

else if ( `echo $cmd | grep "finished" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `ls -ltrd $TASKDIR/* | grep "^d" | awk '{ print $NF }'`)
        eval_or_echo "crab status -d $dir | grep finished"
    end

else if ( `echo $cmd | grep "report" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `ls -ltrd $TASKDIR/* | grep "^d" | awk '{ print $NF }'`)
        eval_or_echo "crab report -d $dir"
    end

else if ( `echo $cmd | grep "getoutput" | wc -l` ) then
    if ( $#argv < 3 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    set DLDIR=`echo $3"/"$TASKNAME | sed "s;//;/;"`
    foreach dir ( `ls -ltrd $TASKDIR/* | grep "^d" | awk '{ print $NF }'`)
	eval_or_echo "mkdir -p $DLDIR/"`echo $dir | sed "s;$TASKDIR/crab_;;"`
        eval_or_echo "crab getoutput -d $dir --outputpath=$DLDIR/"`echo $dir | sed "s;$TASKDIR/crab_;;"`"/"
    end

else if ( `echo $cmd | grep "download" | wc -l` ) then
    if ( $#argv < 3 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set DLDIR=`echo $3"/"$TASKNAME | sed "s;//;/;"`
    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
    if ( $dry == "1" ) echo "source dl_$TASKNAME.csh $DLDIR\nOR add --run after command to excecute following lines\n"
    echo 'if ( $#argv < 1 ) echo "Please specify directory where you want to download files"' >! dl_$TASKNAME.csh
    echo 'alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \\!*"' >> dl_$TASKNAME.csh
    echo 'alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \\!*"\n' >> dl_$TASKNAME.csh
    foreach taskdir ( `ls -ltrd $TASKDIR/*/ | sed "s;/; ;g" | awk '{ print $NF }'`)
        set primary_dataset=`grep inputDataset $TASKDIR/$taskdir.py | sed "s;/; ;g" | awk '{ print $4 }'`
        set time=`se ls "$SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir" | tail -1`
        set SAMPLEDIR=`echo $taskdir | sed "s;crab_;;"`
        eval_or_echo "mkdir -p $DLDIR/$SAMPLEDIR"
        eval_or_echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir/$time/0000 $DLDIR/$SAMPLEDIR/ --par 4 --run"
        echo "mkdir -p "'$1'"/$SAMPLEDIR" >> dl_$TASKNAME.csh
        echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir/$time/0000 "'$1'"/$SAMPLEDIR/ --par 4 --run" >> dl_$TASKNAME.csh
    end

else if ( `echo $cmd | grep "make_ttrees" | wc -l` ) then
    if ( $#argv < 5 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    set EDM_NTUPLE=$3
    set TTREEDIR=$4
    set Nparallel=$5
    foreach dir ( `ls -ltrd $EDM_NTUPLE/* | grep "^d" | sed "s;/; ;g" | awk '{ print $NF }'` )
        eval_or_echo "mkdir -p $TTREEDIR/$dir"
        if ( -f $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh ) rm $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
        foreach file ( `ls $EDM_NTUPLE/$dir | grep ".root"` )
            set outfile=`echo "$file" | sed "s;B2GEDMNtuple;B2GTTreeNtupleExtra;"`
            echo "nice cmsRun $CMSSW_BASE/src/Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py sample=file:$EDM_NTUPLE/$dir/$file outputLabel=$TTREEDIR/$dir/$outfile" >>! $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
        end
        eval_or_echo "source source_parallel.csh $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh $Nparallel"
    end

endif
rm Usage.txt
