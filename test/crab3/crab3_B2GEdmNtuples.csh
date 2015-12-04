#!/bin/tcsh
# Author: Janos Karancsi
# E-mail: janos.karancsi@cern.ch
# Tool: multicrab-like tool to create, submit, get status of crab3 tasks for B2GEdmNtuples
#       When jobs finish, we can also get report and download all output files locally

echo "Usage:"                                                    >! Usage.txt
echo "  source crab3_B2GEdmNtuples.csh <cmd> <TASKNAME> ..."     >> Usage.txt
echo "  there is a default safety mechanism for each command"    >> Usage.txt
echo "  add --run at the end to excecute them"                   >> Usage.txt
echo ""                                                          >> Usage.txt
echo "Commands:"                                                 >> Usage.txt
echo "1) create <TASKNAME> <PUBLISH_NAME> <DATASETS.txt>"        >> Usage.txt
echo "  <SE_SITE> <SE_USERDIR>"                                  >> Usage.txt
echo "  The txt file should contain a short name and the"        >> Usage.txt
echo "  MINIAOD(SIM) dataset on each line"                       >> Usage.txt
echo "  PUBLISH_NAME should specify the B2GAnaFW version tag"    >> Usage.txt
echo "  SE_SITE and SE_USERDIR should be the location you want"  >> Usage.txt
echo "  to send the output to, eg:"                              >> Usage.txt
echo "  T2_HU_Budapest"                                          >> Usage.txt
echo "  /store/user/jkarancs/SusyAnalysis/B2GEdmNtuple"          >> Usage.txt
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
echo "5) get_datasets <TASKNAME>"                                >> Usage.txt
echo "  Get a list of produced datasets"		         >> Usage.txt
echo "" 						         >> Usage.txt
echo "6) checkup <TASKNAME>"                                     >> Usage.txt
echo "  Check for duplicate files due to double submission"      >> Usage.txt
echo "  Gives a script to invalidate them"		         >> Usage.txt
echo "" 						         >> Usage.txt
echo "7) make_twiki <TASKNAME>"                                  >> Usage.txt
echo "  Generate a table in general cern twiki format that"      >> Usage.txt
echo "  contains useful infos for the produced datasets."        >> Usage.txt
echo "  Just copy-paste this to the B2G Ntuple twiki"            >> Usage.txt
echo -n "  https://twiki.cern.ch/twiki/bin/view/CMS/"            >> Usage.txt
echo      "B2GAnaFilesRunIISpring15DR74Asympt25ns"               >> Usage.txt
echo "" 						         >> Usage.txt
echo "8) download <TASKNAME> <DLDIR>"                            >> Usage.txt
echo "  Download all root output files from the Storage"         >> Usage.txt
echo "  element to a local directory DLDIR"                      >> Usage.txt
echo "  Check that the SRM site name and url is defined for"     >> Usage.txt
echo "  SE_SITE in the se_util.csh script (look for SITE_INFO)"  >> Usage.txt
echo "" 						         >> Usage.txt
echo "9) make_ttrees <TASKNAME> <DIR> <NPARALLEL>"               >> Usage.txt
echo "  Produce locally TTreeNtuples from EdmNtuples"            >> Usage.txt
echo "  Files need to be downloaded with the download command"   >> Usage.txt
echo "  Multiple background cmsRuns can be run in parallel"      >> Usage.txt
echo "  Useful if you have small samples (Few GB)"               >> Usage.txt

if ( $1 == "-h" || $1 == "--help" || $#argv < 2 ) then
    cat Usage.txt; rm Usage.txt; exit
endif

# options
set cmd=$1
set TASKNAME=$2
# Working directory name (created in the current directory)
set TASKDIR="B2G_edm_"$TASKNAME

# Aliases
if ( ! (-e $PWD/source_parallel.csh) || ! (-e $PWD/se_util.csh) ) then
    echo "Please run this script from the same directory where\nsource_parallel.csh and se_util.csh is or copy them here" 
    rm Usage.txt; exit
endif
# script that takes another script as argument and runs n lines in parallel
# used by se_util.csh
alias par_source 'source source_parallel.csh \!*'
# Storage element utility (ls, cp, dl, mkdir etc commands)
alias se         'source se_util.csh \!*'

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

set DATE=`date | sed "s; ;_;g;s;:;h;1;s;:;m;1"`

if ( `echo $cmd | grep "create" | wc -l` ) then
    if ( $#argv < 6 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set PUBNAME=$3
    set TXT_FILE=$4
    set SE_SITE=$5
    set SE_USERDIR=$6
    mkdir $TASKDIR
    echo "SE_SITE "$SE_SITE >! $TASKDIR/config.txt
    echo "SE_USERDIR "$SE_USERDIR >> $TASKDIR/config.txt
    if ( !(-f $TXT_FILE) ) then
	echo "$TXT_FILE doesn't exist"; rm Usage.txt; exit
    endif
    grep "/MINIAOD" $TXT_FILE >! $TASKDIR/input_datasets.txt
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_edmntuple_Data_py.txt > $TASKDIR/crab_template_edmntuple_Data_py.txt
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_edmntuple_MC_py.txt > $TASKDIR/crab_template_edmntuple_MC_py.txt
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
	set line=`sed -n "$i"p $TASKDIR/input_datasets.txt`
	set SHORT=`echo $line | awk '{ print $1 }'`
	set DATASET=`echo $line | awk '{ print $2 }'`
	set PUBNAME2=`echo $DATASET | sed "s;/; ;g" | awk '{ print $2 }'`
	set isData=`echo $DATASET | grep 'MINIAOD$' | wc -l`
	set CERT_DIR="https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV"
	set LATEST_50NS_GOLDEN_JSON=`ls -rt /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/ | grep Collisions15_50ns_JSON | grep -v MuonPhys | grep -v Silver | tail -1`
	set LATEST_25NS_GOLDEN_JSON=`ls -rt /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/ | grep Collisions15_25ns_JSON | grep -v MuonPhys | grep -v Silver | tail -1`
	set LATEST_25NS_SILVER_JSON=`ls -rt /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/ | grep Collisions15_25ns_JSON | grep -v MuonPhys | grep Silver | tail -1`
	# 50ns - Data (ReMiniAOD)
	if ( `echo $PUBNAME2 | grep "Run2015B-05Oct2015" | wc -l` ) then
	    set DATAPROC="Data50ns_MiniAODv2"
	    set JEC_DB_FILE="Summer15_50nsV5_DATA.db"
	    set JSON="$CERT_DIR/$LATEST_50NS_GOLDEN_JSON"
	    set RUNS="1-999999"
	else if ( `echo $PUBNAME2 | grep "Run2015C_50ns-05Oct2015" | wc -l`) then
	    set DATAPROC="Data50ns_MiniAODv2"
	    set JEC_DB_FILE="Summer15_50nsV5_DATA.db"
	    set JSON="$CERT_DIR/$LATEST_50NS_GOLDEN_JSON"
	    set RUNS="1-999999"
	# 50ns - MC (ReMiniAOD)
	else if ( `echo $PUBNAME2 | grep "RunIISpring15MiniAODv2-Asympt50ns" | wc -l ` ) then
	    set DATAPROC="MC50ns_MiniAODv2"
	    set JEC_DB_FILE="Summer15_50nsV5_MC.db"
	# 25 ns - Data (ReReco)
	else if ( `echo $PUBNAME2 | grep "Run2015C_25ns-05Oct2015" | wc -l`) then
	    set DATAPROC="Data25ns_ReReco"
	    set JEC_DB_FILE="Summer15_25nsV6_DATA.db"
	    set JSON="$CERT_DIR/$LATEST_25NS_GOLDEN_JSON"
	    set RUNS="1-999999"
	# 25 ns - Data (ReMiniAOD)
	else if ( `echo $PUBNAME2 | grep "Run2015D-05Oct2015" | wc -l`) then
	    set DATAPROC="Data25ns_MiniAODv2"
	    set JEC_DB_FILE="Summer15_25nsV6_DATA.db"
	    set JSON="$CERT_DIR/$LATEST_25NS_GOLDEN_JSON"
	    set RUNS="1-999999"
	# 25 ns - Data (PromptReco)
	else if ( `echo $PUBNAME2 | grep "Run2015D-PromptReco-v4" | wc -l`) then
	    set DATAPROC="Data25ns_PromptRecov4"
	    set JEC_DB_FILE="Summer15_25nsV6_DATA.db"
	    set JSON="$CERT_DIR/$LATEST_25NS_GOLDEN_JSON"
	    set RUNS="1-999999"
	# 25 ns - MC FastSim
	else if ( `echo $PUBNAME2 | grep "RunIISpring15MiniAODv2-FastAsympt25ns" | wc -l` ) then
	    set DATAPROC="MC25ns_MiniAODv2_FastSim"
	    set JEC_DB_FILE="Summer15_25nsV6_MC.db"
	# 25 ns - MC FullSim (ReMiniAOD)
	else if ( `echo $PUBNAME2 | grep "RunIISpring15MiniAODv2" | wc -l` ) then
	    set DATAPROC="MC25ns_MiniAODv2"
	    set JEC_DB_FILE="Summer15_25nsV6_MC.db"
	else
	    echo "ERROR - Dataset not defined (probably because not using latest): "$DATASET
	    rm -r $TASKDIR Usage.txt
	    exit
	endif
	if ( $isData ) then
	    sed "s;REQNAME;$SHORT;;s;PUBNAME;$PUBNAME"_"$PUBNAME2;;s;DATASET;$DATASET;;s;DATAPROC;$DATAPROC;;s;JEC_DB_FILE;$JEC_DB_FILE;;s;JSON;$JSON;;s;RUNS;$RUNS;" $TASKDIR/crab_template_edmntuple_Data_py.txt > $TASKDIR/crab_$SHORT.py
	else
	    sed "s;REQNAME;$SHORT;;s;PUBNAME;$PUBNAME"_"$PUBNAME2;;s;DATASET;$DATASET;;s;DATAPROC;$DATAPROC;;s;JEC_DB_FILE;$JEC_DB_FILE;" $TASKDIR/crab_template_edmntuple_MC_py.txt > $TASKDIR/crab_$SHORT.py
	endif
    end
    rm $TASKDIR/crab_template_edmntuple_Data_py.txt $TASKDIR/crab_template_edmntuple_MC_py.txt
    echo "Config files ready in directory: "$TASKDIR
    ls -ltr $TASKDIR

else if ( `echo $cmd | grep "submit" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach cfg_file ( `awk '{ print "'$TASKDIR'/crab_"$1".py" }' $TASKDIR/input_datasets.txt` )
        eval_or_echo "crab submit -c $cfg_file; sleep 1m"
    end

else if ( `echo $cmd | grep "status" | wc -l` ) then
    foreach short ( `awk '{ print $1 }' $TASKDIR/input_datasets.txt` )
	set dir=`echo $TASKDIR"/crab_"$short`
	if ( ! -d $dir ) then
	    set Status="MISSING"
	else
	    if ( ! -d $TASKDIR/status/$short ) mkdir -p $TASKDIR/status/$short
	    # Check if task was completed already
	    if ( `ls $TASKDIR/status/$short | grep ".txt" | wc -l` ) then
		set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
		set Status=`grep "Task status:" $status_txt | awk '{ print $3 }'`
		if ( $Status != "COMPLETED" ) then
		    crab status -d $dir >! $TASKDIR/status/$short/$DATE.txt
		endif
            else
		crab status -d $dir >! $TASKDIR/status/$short/$DATE.txt
	    endif
	    set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	    set Status=`grep "Task status:" $status_txt | awk '{ print $3 }'`
	    if ( $Status == "" ) then
                set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | head -n -1 | tail -1`
                set Status=`if ( $status_txt != "" ) grep "Task status:" $status_txt | awk '{ print $3 }'`
	    endif
	endif
        printf "%-70s %s\n" $dir $Status
	if ( $Status == "MISSING" ) then
	    echo "  -> Task is not found (not yet submitted?). Submitting ...\n"
	    crab submit -c $dir.py
	    echo
	else if ( `grep "Cannot find \.requestcache" $status_txt | wc -l` ) then
	    echo "  -> Task submission failed - No requestcache. Delete and submit again ...\n"
	    echo "rm -rf $dir"
	    echo "crab submit -c $dir.py"
	    echo
	else if ( `echo $Status | grep SUBMITFAILED | wc -l` && `find $dir -maxdepth 0 -type d -mmin +120 | wc -l` && `grep "\%.*\(" $status_txt | wc -l` == 0 ) then
	    echo "  -> Task submission failed after more than 2 hours and no jobs are running. Delete and submit again ...\n"
	    echo "rm -rf $dir"
	    echo "crab submit -c $dir.py"
	    echo
	else if ( `grep "The server answered with an error" $status_txt | wc -l` ) then
	    echo "  -> Server error. Do nothing ...\n"
	
	#else if ( `echo $Status | grep NEW | wc -l` && `find $dir -maxdepth 0 -type d -mmin +120 | wc -l` ) then
	#    echo "  -> Task stuck in NEW state for more than 2 hours. Kill, delete and submit again ...\n"
	#    crab kill -d $dir
	#    rm -rf $dir
	#    crab submit -c $dir.py
	#    echo
	#else if ( `echo $Status | grep SUBMITTED | wc -l` && `grep "not yet bootstrapped" $status_txt | wc -l` && `find $dir -maxdepth 0 -type d -mmin +120 | wc -l` ) then
	#    echo "  -> Task stuck in bootstrapping for more than 2 hours. Kill, delete and submit again ...\n"
	#    crab kill -d $dir
	#    rm -rf $dir
	#    crab submit -c $dir.py
	#    echo
        else if ( `echo $Status | grep COMPLETED | wc -l` == 0 ) then
	    grep "%.*\(.*\)" $status_txt
            if ( `grep "failed.*\%.*\(" $status_txt | wc -l` == 1 ) then
        	echo "  -> Resubmitting failed jobs ...\n"
        	crab resubmit -d $dir
		echo
            endif
        endif
    end

else if ( `echo $cmd | grep "report" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `awk '{ print "'$TASKDIR'/crab_"$1 }' $TASKDIR/input_datasets.txt` )
        eval_or_echo "crab report -d $dir"
    end

else if ( `echo $cmd | grep "get_datasets" | wc -l` ) then
    # Get list of output datasets
    if ( -f $TASKDIR/output_datasets.txt ) rm $TASKDIR/output_datasets.txt
    # use already saved status txt files
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
        set primary_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | sed "s;/; ;g" | awk '{ print "/"$2"/" }'`
        set out_dataset=`grep 'Output dataset:' $TASKDIR/status/$short/*.txt | grep $primary_dataset | awk '{ print $NF }' | tail -1`
        echo $out_dataset >>! $TASKDIR/output_datasets.txt
    end
    # ask status again
    #foreach dir ( `awk '{ print "'$TASKDIR'/crab_"$1 }' $TASKDIR/input_datasets.txt` )
    #    crab status -d $dir | grep 'Output dataset:' | awk '{ print "'$NF'" }' >>! $TASKDIR/output_datasets.txt
    #end
    # get maximum number of characters to print
    set Nchar_max="0"
    foreach short ( `cat $TASKDIR/input_datasets.txt | awk '{ print $1 }'` )
        set Nchar=`echo $short | wc -m`
        if ( $Nchar > $Nchar_max ) set Nchar_max=$Nchar
    end
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    if ( -f EdmNtuple_"$TASKNAME"_input.txt ) rm EdmNtuple_"$TASKNAME"_input.txt
    foreach i ( `seq 1 $N` )
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
        set out_dataset=`sed -n "$i"p $TASKDIR/output_datasets.txt`
        printf "%-"$Nchar_max"s %s\n" $short $out_dataset >>! EdmNtuple_"$TASKNAME"_input.txt
    end
    cat EdmNtuple_"$TASKNAME"_input.txt

else if ( `echo $cmd | grep "checkup" | wc -l` ) then
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set out_dataset=`sed -n "$i"p $TASKDIR/output_datasets.txt`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
	das_client.py --limit=10000 --query="file dataset=$out_dataset instance=prod/phys03" | grep "\.root" | grep -v $timestamp >! duplicates.txt
	if ( `cat duplicates.txt | wc -l` ) then
	    printf "%-70s Duplicates found: %d\n" $short `cat duplicates.txt | wc -l`
	    if ( ! -e $TASKDIR/Duplicates_$DATE.txt ) touch $TASKDIR/Duplicates_$DATE.txt
	    cat duplicates.txt >> $TASKDIR/Duplicates_$DATE.txt
	else
	    if ( `grep "Task status" $status_txt | awk '{ print $NF }'` == "COMPLETED" ) then
		printf "%-70s OK\n" $short
	    else
		printf "%-70s %s\n" $short `grep "Task status" $status_txt | awk '{ print $NF }'`
	    endif
	endif
	rm duplicates.txt
    end
    if ( -e $TASKDIR/Duplicates_$DATE.txt ) then
	echo "Please issue command below to invalidate duplicate files on the Storage element:"
	echo "python $DBS3_CLIENT_ROOT/examples/DBS3SetFileStatus.py --url=https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter --status=invalid --recursive=False --files=$TASKDIR/Duplicates_$DATE.txt"
    endif

else if ( `echo $cmd | grep "getoutput" | wc -l` ) then
    if ( $#argv < 3 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    set DLDIR=`echo $3"/"$TASKNAME | sed "s;//;/;"`
    foreach short ( `awk '{ print $1 }' $TASKDIR/input_datasets.txt` )
	eval_or_echo "mkdir -p $DLDIR/$short"
        eval_or_echo "crab getoutput -d $dir --outputpath=$DLDIR/$short/"
    end

else if ( `echo $cmd | grep "download" | wc -l` ) then
    if ( $#argv < 3 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set DLDIR=`echo $3"/"$TASKNAME | sed "s;//;/;"`
    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
    if ( $dry == "1" ) echo "source dl_$TASKNAME.csh $DLDIR\nOR add --run after command to excecute following lines:\n"
    echo 'if ( $#argv < 1 ) echo "Please specify directory where you want to download files"' >! dl_$TASKNAME.csh
    echo 'alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \\!*"' >> dl_$TASKNAME.csh
    echo 'alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \\!*"\n' >> dl_$TASKNAME.csh
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
        set pubname=`grep outputDatasetTag $TASKDIR/crab_$short.py | sed "s;'; ;g" | awk '{ print $3 }'`
	set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
        eval_or_echo "mkdir -p $DLDIR/$short"
        echo "mkdir -p "'$1'"/$short" >> dl_$TASKNAME.csh
	foreach thousand ( `se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp` )
	    eval_or_echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand $DLDIR/$short --par 4 --run"
	    echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand "'$1'"/$short --par 4 --run" >> dl_$TASKNAME.csh
	end
    end
    if ( ( `grep "EDM_NTUPLE" $TASKDIR/config.txt | wc -l` == 1 ) && ( $dry == "0" ) ) echo "EDM_NTUPLE $DLDIR" >> $TASKDIR/config.txt

else if ( `echo $cmd | grep "find_missing" | wc -l` ) then
    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
        set pubname=`grep outputDatasetTag $TASKDIR/crab_$short.py | sed "s;'; ;g" | awk '{ print $3 }'`
	set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
	set isData=`echo $in_dataset | grep '/MINIAOD$' | wc -l`
	if ( $isData ) then
	    # status txt file not very reliable, but that's available for data
	    set njobs=`grep ".*\%.*\(.*\)" $status_txt | tail -1 | sed "s;/; ;g;s;); ;g"| awk '{ print $NF }'`
	else
	    # better way to get job number as long as the split mode is by file and 1 file = 1 job
	    set njobs=`das_client --query "dataset=$in_dataset | grep dataset.nfiles" | tail -1`
	endif
	# Get missing jobs
	echo -n "" >! jobnums.txt
	foreach thousand ( `se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp` )
	    se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand | grep "\.root" | sed 's;_; ;g;s;\.root;;' | awk '{ print $NF }' | sort -n | uniq >> jobnums.txt
	end
	set missing=""
	foreach N ( `seq 1 $njobs` )
	    if ( `grep '^'$N'$' jobnums.txt | wc -l` == 0 ) set missing="$missing,$N"
	end
        rm jobnums.txt
	set missing=`echo $missing | sed "s;,;;1"`
	if ( $missing != "" ) echo "crab resubmit -d $TASKDIR/crab_$short --wait --force --jobids=$missing"
    end

else if ( `echo $cmd | grep "make_ttrees" | wc -l` ) then
    if ( $#argv < 4 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    if ( `grep "EDM_NTUPLE" $TASKDIR/config.txt | wc -l` == 0 ) then
	echo "EdmNtuple not yet downloaded, issue command:\ndownload <TASKNAME> <DLDIR>"
    else
	if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
        set EDM_NTUPLE=`grep EDM_NTUPLE $TASKDIR/config.txt | awk '{ print $2 }'`
	set TTREEDIR=$3
        set Nparallel=$4
        foreach dir ( `ls -ltrd $EDM_NTUPLE/* | grep "^d" | sed "s;/; ;g" | awk '{ print $NF }'` )
            eval_or_echo "mkdir -p $TTREEDIR/$dir"
	    set is50ns="0"
	    if ( `echo $dir | grep "Run2015B" | wc -l` || `echo $dir | grep "50ns" | wc -l`  ) set is50ns="1"
	    set isData="False"
	    set DATA="MC"
	    if ( `echo $dir | grep "Run2015" | wc -l`  ) then
		set isData="True"
		set DATA="DATA"
	    endif
            if ( $is50ns ) then
		set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_50nsV5_$DATA"
	    else
		set JEC_TXT_FILE="$CMSSW_BASE/src/Analysis/B2GTTrees/JECs/Summer15_25nsV6_$DATA"
	    endif
            if ( -f $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh ) rm $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
            foreach file ( `ls $EDM_NTUPLE/$dir | grep ".root"` )
                set outfile=`echo "$file" | sed "s;B2GEDMNtuple;B2GTTreeNtupleExtra;"`
                echo "nice cmsRun $CMSSW_BASE/src/Analysis/B2GTTrees/test/B2GEdmToTTreeNtupleExtra_cfg.py isData=$isData sample=file:$EDM_NTUPLE/$dir/$file outputLabel=$TTREEDIR/$dir/$outfile JECloc=$JEC_TXT_FILE" >>! $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh
            end
            eval_or_echo "source source_parallel.csh $TASKDIR/make_ttrees_"$TASKNAME"_$dir.csh $Nparallel"
        end
    endif

else if ( `echo $cmd | grep "make_init_twiki" | wc -l` ) then
    echo "Please enter your name:"
    set NAME=$<
    echo "Please enter B2GAnaFW Version tag:"
    set TAG=$<
    set first_data="0"
    set first_mc="0"
    echo "Paste this to the B2G ntuple twiki: https://twiki.cern.ch/twiki/bin/view/CMS/B2GAnaFilesRunIISpring15DR74Asympt25ns"
    foreach in_dataset (`awk '{ print $2 }' $TASKDIR/input_datasets.txt`)
	set isData=`echo $in_dataset | grep '/MINIAOD$' | wc -l`
	if ( $first_data == 0 && $isData ) then
	    set first_data=1
	    echo
	    echo "| *Parent Sample* | *Submitted* | *Status* | *Lumi mask* | *Int. lumi [pb-1]* | *Published dataset* | *B2GFWAna tag* |"
	else if ( $first_mc == 0 && $isData == 0 ) then
	    set first_mc=1
	    echo
	    echo "| *Parent Sample* | *Submitted* | *Status* | *N_events (orig. dataset)* | *N_events processed* | *Published dataset* | *B2GFWAna tag* |"
	endif
	
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$in_dataset&instance=prod%2Fglobal][$in_dataset]] "
	echo -n "| $NAME "
	if ( $isData ) then
	    set crab_script=`grep $in_dataset $TASKDIR/input_datasets.txt | awk '{ print "'$TASKDIR'/crab_"$1".py" }'`
	    set CERT=`grep lumiMask $crab_script | sed "s;'; ;g;s;/; ;g" | awk '{ print $NF }'`
	    echo -n "| Submitted "
	    echo -n "| [[https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/$CERT][$CERT]] "
	    echo -n "|  "
	else
	    set nevents=`das_client.py --query="dataset=$in_dataset | grep dataset.nevents" | tail -1`
	    echo -n "| Submitted "
	    echo -n "|  $nevents "
	    echo -n "|  "
	endif
	echo -n "|  "
	echo "| $TAG |"
    end

else if ( `echo $cmd | grep "make_twiki" | wc -l` ) then
    if ( ! -e $TASKDIR/output_datasets.txt ) then
	"List of output datasets is not yet collected, please issue get_datasets command first"
	cat Usage.txt; rm Usage.txt; exit
    endif
    echo "Please enter your name:"
    set NAME=$<
    echo "Please enter B2GAnaFW Version tag:"
    set TAG=$<
    #echo "Please enter Total Int. lumi [pb-1]:"
    #set INTLUMI=$<
    
    echo "Paste this to the B2G ntuple twiki: https://twiki.cern.ch/twiki/bin/view/CMS/B2GAnaFilesRunIISpring15DR74Asympt25ns"
    set first_data="0"
    set first_mc="0"
    foreach out_dataset ( `cat $TASKDIR/output_datasets.txt` )
	set in_dataset=`das_client.py --query="parent dataset=$out_dataset instance=prod/phys03" | tail -1`
	### set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
	set isData=`echo $in_dataset | grep '/MINIAOD$' | wc -l`
	if ( $first_data == 0 && $isData ) then
	    set first_data=1
	    echo
	    echo "| *Parent Sample* | *Submitted* | *Status* | *Lumi mask* | *Int. lumi [pb-1]* | *Published dataset* | *B2GFWAna tag* |"
	else if ( $first_mc == 0 && $isData == 0 ) then
	    set first_mc=1
	    echo
	    echo "| *Parent Sample* | *Submitted* | *Status* | *N_events (orig. dataset)* | *N_events processed* | *Published dataset* | *B2GFWAna tag* |"
	endif
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$in_dataset&instance=prod%2Fglobal][$in_dataset]] "
	echo -n "| $NAME "
	if ( $isData ) then
	    set crab_script=`grep $in_dataset $TASKDIR/input_datasets.txt | awk '{ print "'$TASKDIR'/crab_"$1".py" }'`
	    set CERT=`grep lumiMask $crab_script | sed "s;'; ;g;s;/; ;g" | awk '{ print $NF }'`
	    echo -n "| Completed "
	    echo -n "| [[https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/$CERT][$CERT]] "
	    echo -n "|  "#$INTLUMI  "
	else
	    set nevents=`das_client.py --query="dataset=$in_dataset | grep dataset.nevents" | tail -1`
	    set nevents_proc=`das_client.py --query="dataset=$out_dataset instance=prod/phys03 | grep dataset.nevents" | tail -1`
	    if ( $nevents == $nevents_proc ) then
		echo -n "| Completed "
	    else
		echo -n "| Submitted "
	    endif
	    echo -n "|  $nevents "
	    echo -n "|  $nevents_proc "
	endif
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$out_dataset&instance=prod%2Fphys03][$out_dataset]] "
	echo "| $TAG |"
    end
    
endif
rm Usage.txt


