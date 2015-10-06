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
echo "1) create <TASKNAME> <DATASETS.txt> <XSECS.txt> \\"        >> Usage.txt
echo "          <SE_SITE> <SE_USERDIR>"                          >> Usage.txt
echo "  The 1st txt file should contain a short name and the"    >> Usage.txt
echo "  B2GEdmNTuple dataset on each line"                       >> Usage.txt
echo "  The 2nd txt file should contain the primary_dataset_name">> Usage.txt
echo "  and the corresponding cross-section (pb) on each line"   >> Usage.txt
echo "  SE_SITE and SE_USERDIR should be the location you want"  >> Usage.txt
echo "  to send the output to, eg:"                              >> Usage.txt
echo "  T2_HU_Budapest"                                          >> Usage.txt
echo "  /store/user/jkarancs/SusyAnalysis/B2GTTreeNtuple"        >> Usage.txt
echo ""                                                          >> Usage.txt
echo "2) submit <TASKNAME>"                                      >> Usage.txt
echo "  Submit tasks to the grid (check cfg files first)"        >> Usage.txt
echo ""                                                          >> Usage.txt
echo "3) status <TASKNAME>"                                      >> Usage.txt
echo "  Check status of tasks and resubmit jobs if needed"	 >> Usage.txt
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
echo "6) make_ttrees <TASKNAME> <XSEC.txt> <INDIR> <OUTDIR>"     >> Usage.txt
echo "               <NPARALLEL>"                                >> Usage.txt
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
    if ( $#argv < 6 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set INPUT_FILE=$3
    set XSEC_FILE=$4
    set SE_SITE=$5
    set SE_USERDIR=$6
    if (-d $TASKDIR ) then
	echo "Error: task directory: "$TASKDIR" already exists. exiting..."
	exit
    else
	mkdir $TASKDIR
    endif
    echo "SE_SITE "$SE_SITE >! $TASKDIR/config.txt
    echo "SE_USERDIR "$SE_USERDIR >> $TASKDIR/config.txt
    if ( !(-f $INPUT_FILE) ) then
	echo "$INPUT_FILE doesn't exist"; exit
    endif
    cp $INPUT_FILE $TASKDIR/input_datasets.txt
    cp $XSEC_FILE $TASKDIR/xsec_datasets.txt
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_ttreentuple_py.txt > $TASKDIR/crab_template_ttreentuple_py.txt
    set N=`grep "/" $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
	set SHORT=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set DATASET=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
	set primary=`echo $DATASET | sed "s;/; ;g" | awk '{ print $1 }'`
	set isData=`echo $DATASET | grep 'Run2015' | wc -l`
	set xsec=`grep $primary $TASKDIR/xsec_datasets.txt | awk '{ print $2 }'`
	if ( ! $isData && $xsec == "" ) then
	    echo "Error: Cross-section is missing for $primary, exiting..."
	    rm -r $TASKDIR
	    exit
	endif
	if ( $isData ) then
	    set WEIGHT=1
	else 
	    set nevent=`das_client.py --query="dataset=$DATASET instance=prod/phys03 | grep dataset.nevents" | tail -1`
	    set WEIGHT=`echo | awk '{ printf "%lf", 1000*'$xsec'/'$nevent' }'`
	endif
	set MIDNAME=`echo $DATASET | sed "s;/; ;g" | awk '{ print $2 }'`
	# 50ns
	if ( `echo $MIDNAME | grep "Run2015B" | wc -l` ) then
	    set JECNAME="Summer15_50nsV5_DATA"
	    set ISDATA="True"
	else if ( `echo $MIDNAME | grep "Asympt50ns" | wc -l` ) then
	    set JECNAME="Summer15_50nsV5_MC"
	    set ISDATA="False"
	# 25ns
	else if ( `echo $MIDNAME | grep "Run2015C" | wc -l` || `echo $MIDNAME | grep "Run2015D" | wc -l` ) then
	    set JECNAME="Summer15_25nsV2_DATA"
	    set ISDATA="True"
	else if ( `echo $MIDNAME | grep "Asympt25ns" | wc -l` ) then	    
	    set JECNAME="Summer15_25nsV2_MC"
	    set ISDATA="False"
	endif
	sed "s;TASKNAME;$SHORT;;s;DATASET;$DATASET;;s;weight=1.0;weight=$WEIGHT;;s;JECNAME;$JECNAME;;s;ISDATA;$ISDATA;" $TASKDIR/crab_template_ttreentuple_py.txt > $TASKDIR/crab_$SHORT.py
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
    foreach dir ( `ls -ltrd $TASKDIR/* | grep "^d" | awk '{ print $NF }'`)
	crab status -d $dir >! Status.txt
	set Status=`grep "Task status:" Status.txt | awk '{ print $3 }'`
	printf "%-70s %s\n" $dir $Status
	if ( `echo $Status | grep COMPLETED | wc -l` == 0 ) then
	    grep "%.*\(.*\)" Status.txt
	    if ( `grep "failed.*\%.*\(" Status.txt | wc -l` == 1 ) then
		crab resubmit -d $dir
		echo "Failed jobs resubmitted"
	    endif
	endif
	rm Status.txt
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
    if ( $dry == "1" ) then 
	echo "source dl_$TASKNAME.csh $DLDIR\nOR add --run after command to excecute following lines\n"
        echo "kinit jkarancs@FNAL.GOV"
        echo "ssh -YX jkarancs@cmslpc-sl6.fnal.gov"
        echo "cd /uscms_data/d3/jkarancs/CMSSW/CMSSW_7_4_4_patch1/src"
        echo "cmsenv"
        echo "cd /uscms_data/d3/jkarancs/B2GTTreeNtuple"
        echo "scp jkarancs@grid18.kfki.hu:$PWD/dl_$TASKNAME.csh ."
        echo "source dl_$TASKNAME.csh "`echo $TASKNAME | sed "s;_; ;g" | awk '{ print $1 }'`"\n"
    endif
    echo 'if ( $#argv < 1 ) echo "Please specify directory where you want to download files"' >! dl_$TASKNAME.csh
    echo 'alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \\!*"' >> dl_$TASKNAME.csh
    echo 'alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \\!*"\n' >> dl_$TASKNAME.csh
    foreach taskdir ( `ls -ltrd $TASKDIR/*/ | sed "s;/; ;g" | awk '{ print $NF }'` )
        set primary_dataset=`grep inputDataset $TASKDIR/$taskdir.py | sed "s;/; ;g" | awk '{ print $4 }'`
        set TIME=`se ls "$SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir" | tail -1`
        set SAMPLEDIR=`echo $taskdir | sed "s;crab_;;"`
        eval_or_echo "mkdir -p $DLDIR/$SAMPLEDIR"
        eval_or_echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir/$TIME/0000 $DLDIR/$SAMPLEDIR/ --par 4 --run"
        echo "mkdir -p "'$1'"/$SAMPLEDIR" >> dl_$TASKNAME.csh
        echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir/$TIME/0000 "'$1'"/$SAMPLEDIR/ --par 4 --run" >> dl_$TASKNAME.csh
    end

else if ( `echo $cmd | grep "find_missing" | wc -l` ) then
    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
    foreach taskdir ( `ls -ltrd $TASKDIR/*/ | sed "s;/; ;g" | awk '{ print $NF }'`)
        set primary_dataset=`grep inputDataset $TASKDIR/$taskdir.py | sed "s;/; ;g" | awk '{ print $4 }'`
        set TIME=`se ls "$SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir" | tail -1`
        set SAMPLEDIR=`echo $taskdir | sed "s;crab_;;"`
	set njobs=`crab status -d $TASKDIR/$taskdir | grep ".*\%.*\(.*\)" | tail -1 | sed "s;/; ;g;s;); ;g"| awk '{ print $NF }'`
        set missing=`se mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$taskdir/$TIME/0000 $njobs | sed 's;.$;;'`
	if ( $missing != "" ) then
	    echo "crab resubmit -d $TASKDIR/$taskdir --wait --force --jobids=$missing"
	endif
    end

else if ( `echo $cmd | grep "make_ttrees" | wc -l` ) then
    if ( $#argv < 6 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    set XSEC_FILE=$3
    set EDM_NTUPLE=$4
    set TTREEDIR=$5
    set Nparallel=$6
    foreach dir ( `ls -ltrd $EDM_NTUPLE/* | grep "^d" | sed "s;/; ;g" | awk '{ print $NF }'` )
        eval_or_echo "mkdir -p $TTREEDIR/$dir"
        if ( -f $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh ) rm $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
	# calculate event weight (xsec/nevent) for tot int lumi = 1 fb^-1
	set totevt=0
        foreach file ( `ls $EDM_NTUPLE/$dir | grep ".root"` )
	    set nevt=`edmFileUtil $EDM_NTUPLE/$dir/$file | grep events | awk '{ print $6 }'`
	    set totevt=`expr $totevt + $nevt`
        end
	set XSEC=`grep $dir $XSEC_FILE | awk '{ print $2 }'`
	set WEIGHT=`echo | awk '{ printf "%lf", 1000*'$XSEC'/'$totevt' }'`
	# Specify latest JEC
	# 50ns
	if ( `echo $dir | grep "Run2015B-17Jul2015" | wc -l` ) then
	    set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_50nsV5_DATA"
	    set isData="True"
	else if ( `echo $dir | grep "Run2015B-PromptReco" | wc -l` ) then
	    set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_50nsV5_DATA"
	    set isData="True"
	# 25 ns
	else if ( `echo $dir | grep "Run2015C" | wc -l`) then
	    set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_25nsV2_DATA"
	    set isData="True"
	else if ( `echo $dir | grep "Run2015D" | wc -l`) then
	    set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_25nsV2_DATA"
	    set isData="True"
	else
	    # This version only handles 25ns MC
	    set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_25nsV2_MC"
	    set isData="False"
	endif
        foreach file ( `ls $EDM_NTUPLE/$dir | grep ".root"` )
            set outfile=`echo "$file" | sed "s;B2GEDMNtuple;B2GTTreeNtupleExtra;"`
            echo "nice cmsRun $CMSSW_BASE/src/Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py isData=$isData sample=file:$EDM_NTUPLE/$dir/$file outputLabel=$TTREEDIR/$dir/$outfile JECloc=$JEC_TXT_FILE weight=$WEIGHT" >>! $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
        end
        eval_or_echo "source source_parallel.csh $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh $Nparallel"
    end

endif
rm Usage.txt
