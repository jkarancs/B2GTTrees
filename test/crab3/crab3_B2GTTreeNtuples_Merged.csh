#!/bin/tcsh -f
# Author: Janos Karancsi
# E-mail: janos.karancsi@cern.ch
# Tool: multicrab-like tool to create, submit, get status of crab3 tasks for B2GEdmNtuples
#       When jobs finish, we can also get report and download all output files locally

echo "Usage:"                                                    >! Usage.txt
echo "  source crab3_B2GEdmNtuples_Merged.csh <cmd> <TASKNAME> " >> Usage.txt
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
set TASKDIR="B2G_merged_"$TASKNAME

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
alias grep egrep

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

set DATE=`date | cut -f2- -d" " | sed "s; ;_;g;s;:;h;1;s;:;m;1"`

if ( `echo $cmd | grep "create" | wc -l` ) then
    if ( $#argv < 6 ) then
	cat Usage.txt; rm Usage.txt; exit
    endif
    set TAG=$3
    set TXT_FILE=$4
    set XSEC_FILE=$5
    set SE_SITE=$6
    set SE_USERDIR=$7
    set CERT_DIR="https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV"
    set LATEST_GOLDEN_JSON=`ls -lrt /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV | awk '{ print $NF }' | grep -vE "MuonPhys|LowPU" | grep "\.txt" | tail -1`
    #set JSON="$LATEST_GOLDEN_JSON"
    set ICHEP_GOLDEN_JSON="Cert_271036-276811_13TeV_PromptReco_Collisions16_JSON_NoL1T.txt"
    set JSON="$LATEST_GOLDEN_JSON"
    mkdir $TASKDIR
    echo "SE_SITE "$SE_SITE >! $TASKDIR/config.txt
    echo "SE_USERDIR "$SE_USERDIR >> $TASKDIR/config.txt
    if ( !(-f $TXT_FILE) ) then
	echo "$TXT_FILE doesn't exist"; rm Usage.txt; exit
    endif
    grep -v '^#' $TXT_FILE | grep "/MINIAOD" >! $TASKDIR/input_datasets.txt
    cp $XSEC_FILE $TASKDIR/xsec_datasets.txt
    mkdir -p $TASKDIR/cross_sections
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_ttreentuple_merged_Data.py > $TASKDIR/crab_template_ttreentuple_merged_Data.py
    sed "s;TASKDIR;$TASKDIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_ttreentuple_merged_MC.py   > $TASKDIR/crab_template_ttreentuple_merged_MC.py
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
	set line=`sed -n "$i"p $TASKDIR/input_datasets.txt`
	set SHORT=`echo $line | awk '{ print $1 }'`
	set DATASET=`echo $line | awk '{ print $2 }'`
	set primary=`echo $DATASET | sed "s;/; ;g" | awk '{ print $1 }'`
	set PROCESSED_DS_NAME=`echo $DATASET | sed "s;/; ;g" | awk '{ print $2 }'`
	set isData=`echo $DATASET | grep 'MINIAOD$' | wc -l`
	# 2016 Data
	#echo $primary
	if ( `echo $PROCESSED_DS_NAME | grep "Run2016" | wc -l`) then
	    set DATAPROC="Data_80X"
	    set JEC_ERA="EMPTY"
	    set RUNS="1-999999"
	# Spring16 MC
	else if ( `echo $PROCESSED_DS_NAME | grep "RunIISpring16MiniAODv2" | wc -l` ) then
	    # FastSim
	    if ( `echo $PROCESSED_DS_NAME | grep "PUSpring16Fast" | wc -l` ) then
		set DATAPROC="MC_MiniAODv2_80X_FastSim"
		set JEC_ERA="Spring16_25nsFastSimMC_V1"
	    else if ( `echo $PROCESSED_DS_NAME | grep "reHLT" | wc -l` ) then
		set DATAPROC="MC_MiniAODv2_80X_reHLT"
		set JEC_ERA="EMPTY"
	    else
		set DATAPROC="MC_MiniAODv2_80X"
		set JEC_ERA="EMPTY"
	    endif
	else
	    echo "ERROR - Dataset not defined (probably because not using latest): "$DATASET
	    rm -r $TASKDIR Usage.txt
	    exit
	endif
	# Create xsec txt file for each dataset
	if ( `echo $primary | grep SMS | wc -l` || $isData ) then
	    # Signal: Xsec depends on mGlu (fill in ntuple)
	    # Data: Xsec variable not needed
	    set xsec="0"
	else
	    set xsec=`grep "^$primary" $TASKDIR/xsec_datasets.txt | tail -1 | awk '{ print $2 }'`
	    if ( "$xsec" == "" ) then
	        echo "Error: Cross-section is missing for $primary, exiting..."
	        rm -r $TASKDIR
	        exit
	    endif
	    # Multiply cross-section with k-factor
	    set k_factor=`grep "^$primary" $TASKDIR/xsec_datasets.txt | tail -1 | awk '{ print $3 }'`
	    set xsec=`echo | awk '{ printf "%lf", '$xsec'*'$k_factor' }'`
	endif
	# cross_section.txt containing the actual cross-section for each primary dataset
	mkdir -p $TASKDIR/cross_sections/$SHORT
	echo "$xsec" >! $TASKDIR/cross_sections/$SHORT/cross_section.txt
	set XSEC_FILE="$TASKDIR/cross_sections/$SHORT/cross_section.txt"
	if ( $isData ) then
	    sed "s;REQNAME;$SHORT;;s;PUBNAME;$TAG"_"$PROCESSED_DS_NAME;;s;DATASET;$DATASET;;s;DATAPROC;$DATAPROC;;s;JEC_ERA;$JEC_ERA;;s;XSEC_FILE;$XSEC_FILE;;s;JSON;$CERT_DIR/$JSON;;s;RUNS;$RUNS;" $TASKDIR/crab_template_ttreentuple_merged_Data.py > $TASKDIR/crab_$SHORT.py
	else
	    sed "s;REQNAME;$SHORT;;s;PUBNAME;$TAG"_"$PROCESSED_DS_NAME;;s;DATASET;$DATASET;;s;DATAPROC;$DATAPROC;;s;JEC_ERA;$JEC_ERA;;s;XSEC_FILE;$XSEC_FILE;;" $TASKDIR/crab_template_ttreentuple_merged_MC.py > $TASKDIR/crab_$SHORT.py
	endif
    end
    rm $TASKDIR/crab_template_ttreentuple_merged_Data.py $TASKDIR/crab_template_ttreentuple_merged_MC.py
    echo "Config files ready in directory: "$TASKDIR
    ls -ltr $TASKDIR

else if ( `echo $cmd | grep "submit" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach cfg_file ( `awk '{ print "'$TASKDIR'/crab_"$1".py" }' $TASKDIR/input_datasets.txt` )
        eval_or_echo "crab submit -c $cfg_file; sleep 1m"
    end

else if ( `echo $cmd | grep "status" | wc -l` ) then
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
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
	    if ( $Status == "" && `ls -tr $TASKDIR/status/$short/*.txt | head -n -1 | wc -l` != 0 ) then
                set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | head -n -1 | tail -1`
                set Status=`if ( $status_txt != "" ) grep "Task status:" $status_txt | awk '{ print $3 }'`
	    endif
	endif
        printf "%-70s %s\n" $dir $Status
	set nfail=`grep "failed.*\%.*\(" $status_txt | wc -l`
	if ( $Status == "MISSING" ) then
	    echo "  -> Task is not found (not yet submitted?). Submitting ...\n"
	    eval_or_echo "crab submit -c $dir.py"
	    echo
	else if ( `grep "Cannot find \.requestcache" $status_txt | wc -l` ) then
	    echo "  -> Task submission failed - No requestcache. Delete and submit again ...\n"
	    eval_or_echo "rm -rf $dir"
	    eval_or_echo "crab submit -c $dir.py"
	    echo
	else if ( `echo $Status | grep SUBMITFAILED | wc -l` && `grep "does not generate any job" $status_txt | wc -l` != 0 ) then
	    echo "  -> Task submission failed, because dataset is outside of the JSON file ...\n"
	    echo "rm -rf $dir"
	    echo
	else if ( `echo $Status | grep SUBMITFAILED | wc -l` && `find $dir -maxdepth 0 -type d -mmin +120 | wc -l` && `grep "\%.*\(" $status_txt | wc -l` == 0 ) then
	    echo "  -> Task submission failed after more than 2 hours and no jobs are running. Delete and submit again ...\n"
	    eval_or_echo "rm -rf $dir"
	    eval_or_echo "crab submit -c $dir.py"
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
            if ( $nfail != 0 ) then
		if ( `grep "jobs failed with exit code 50660" $status_txt | wc -l` == 0 ) then
		    echo "  -> Resubmitting failed jobs ...\n"
		    eval_or_echo "crab resubmit -d $dir"
		else
		    # Exceed Memory
		    if ( `find $dir -maxdepth 0 -type d -mtime 2 | wc -l` == 0 ) then
			# Resubmit with 2500 MB initially
			echo "  -> Jobs found that exceeded 2000MB memory, resubmitting with 2500MB ...\n"
			eval_or_echo "crab resubmit -d $dir --maxmemory=2500"
                    else
			# Then after two days, 3000 MB
			echo "  -> Jobs found that exceeded allocated memory after 2 days, resubmitting with 3000MB ...\n"
			eval_or_echo "crab resubmit -d $dir --maxmemory=3000"
		    endif
		endif
		echo
	    else
		# Get more info about tasks not failing but near completion
	        set percent=`grep "finished" $status_txt | head -1 | sed "s;\.; ;g" | awk '{ print $2 }'`
	        if ( $percent == "status:" ) set percent=`grep "finished" $status_txt | head -1 | sed "s;\.; ;g" | awk '{ print $4 }'`
	        if ( $percent == "" ) set percent=0
	        if ( $percent > 90 ) then
		    echo "More info about task:"
                    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
                    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
	            set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
	            set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
                    set pubname=`grep outputDatasetTag $TASKDIR/crab_$short.py | sed "s;'; ;g" | awk '{ print $3 }'`
                    set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
	            set njobs=`grep ".*\%.*\(.*\)" $status_txt | tail -1 | sed "s;/; ;g;s;); ;g"| awk '{ print $NF }'`
	            touch missing.txt
                    foreach thousand ( `se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp` )
	                set BEG=`expr $thousand \* 1000`
	                set END=`expr $BEG + 999`
	                if ( "$BEG" == 0 ) set BEG=1
	                if ( $njobs < $END ) set END=$njobs
                        set missing=`se mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand $BEG $END`
	                if ( `echo $missing | grep '^$' | wc -l` != 1 ) echo $missing >> missing.txt
                    end
	            if ( `cat missing.txt | wc -l` ) then
	                echo -n "-  Found missing jobs: "; cat missing.txt
	            else
	                echo "-  No jobs are missing on the SE"
	            endif
	            rm missing.txt
	        endif
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

else if ( `echo $cmd | grep "get_lumi" | wc -l` ) then
    set NORMTAG="/afs/cern.ch/user/l/lumipro/public/normtag_file/moriond16_normtag.json"
    mkdir -p $TASKDIR/data_lumi_summaries_$TASKNAME
    if ( -e $TASKDIR/get_luminosity_$TASKNAME.csh ) rm $TASKDIR/get_luminosity_$TASKNAME.csh
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set isData=`echo $in_dataset | grep 'Run201' | wc -l`
	if ( $isData ) then
	    if ( ! -e $TASKDIR/crab_$short/results/processedLumis.json ) then
	        crab report -d $TASKDIR/crab_$short
	    endif
	    cp $TASKDIR/crab_$short/results/processedLumis.json $TASKDIR/data_lumi_summaries_$TASKNAME/$short.json
	    cp $TASKDIR/crab_$short/results/lumisToProcess.json $TASKDIR/data_lumi_summaries_$TASKNAME/"$short"_input.json
	    echo "echo '$short processed '"\`"brilcalc lumi --normtag $NORMTAG -i data_lumi_summaries_$TASKNAME/$short.json | grep -A 2 totrecorded | tail -1 | awk '{ printf "\""%1.3f pb^-1\\n"\"", "\$"(NF-1)/1000000.0 }'"\`>>! $TASKDIR/get_luminosity_$TASKNAME.csh
	    echo "echo '$short input     '"\`"brilcalc lumi --normtag $NORMTAG -i data_lumi_summaries_$TASKNAME/"$short"_input.json | grep -A 2 totrecorded | tail -1 | awk '{ printf "\""%1.3f pb^-1\\n"\"", "\$"(NF-1)/1000000.0 }'"\`>>! $TASKDIR/get_luminosity_$TASKNAME.csh
	endif
    end
    echo "\n------\n"
    echo "Run these commands to get luminosity: \n"
    echo "scp -r $TASKDIR/data_lumi_summaries_$TASKNAME $TASKDIR/get_luminosity_$TASKNAME.csh "`whoami`"@lxplus.cern.ch:~/"
    echo "ssh lxplus.cern.ch"
    echo "setenv PATH "\$"HOME/.local/bin:/afs/cern.ch/cms/lumi/brilconda-1.0.3/bin:"\$"PATH"
    echo "pip install --install-option="--prefix=$HOME/.local" brilws"
    echo "source get_luminosity_$TASKNAME.csh"

else if ( `echo $cmd | grep "checkup" | wc -l` ) then
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set out_dataset=`sed -n "$i"p $TASKDIR/output_datasets.txt`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
	das_client --limit=10000 --query="file dataset=$out_dataset instance=prod/phys03" | grep "\.root" | grep -v $timestamp >! duplicates.txt
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
    set NPar="1"
    echo 'if ( $#argv < 1 ) echo "Please specify directory where you want to download files"' >! dl_$TASKNAME.csh
    echo 'alias par_source "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh \\!*"' >> dl_$TASKNAME.csh
    echo 'alias se         "source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/se_util.csh \\!*"\n' >> dl_$TASKNAME.csh
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
	if ( `echo $in_dataset | grep Tprime | wc -l` == 0 ) then
	    set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
            set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	    set pubname=`grep outputDatasetTag $TASKDIR/crab_$short.py | sed "s;'; ;g" | awk '{ print $3 }'`
	    set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	    set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
            eval_or_echo "mkdir -p $DLDIR/$short"
            echo "mkdir -p "'$1'"/$short" >> dl_$TASKNAME.csh
	    foreach thousand ( `se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp` )
	        eval_or_echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand $DLDIR/$short --par $NPar --run"
	        echo "se dl_mis $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand "'$1'"/$short --par $NPar --run" >> dl_$TASKNAME.csh
	    end
        endif
    end

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

else if ( `echo $cmd | grep "delete" | wc -l` ) then
    set SE_SITE=`grep SE_SITE $TASKDIR/config.txt | awk '{ print $2 }'`
    set SE_USERDIR=`grep SE_USERDIR $TASKDIR/config.txt | awk '{ print $2 }'`
    set N=`cat $TASKDIR/input_datasets.txt | wc -l`
    foreach i ( `seq 1 $N` )
        set in_dataset=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $2 }'`
        set short=`sed -n "$i"p $TASKDIR/input_datasets.txt | awk '{ print $1 }'`
	set status_txt=`ls -tr $TASKDIR/status/$short/*.txt | tail -1`
	set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
        set out_dataset=`grep 'Output dataset:' $TASKDIR/status/$short/*.txt | grep $primary_dataset | awk '{ print $NF }' | tail -1`
        set pubname=`grep outputDatasetTag $TASKDIR/crab_$short.py | sed "s;'; ;g" | awk '{ print $3 }'`
	set timestamp=`grep "Task name" $status_txt | sed "s;\:; ;g" | awk '{ print $3 }'`
	# Invalidate dataset
	eval_or_echo "python $DBS3_CLIENT_ROOT/examples/DBS3SetDatasetStatus.py --url=https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter --status=INVALID --recursive=False --dataset=$out_dataset"
	# delete all files on SE
	foreach thousand ( `se ls $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp` )
	    eval_or_echo "se rm $SE_SITE":"$SE_USERDIR/$primary_dataset/$pubname/$timestamp/$thousand --run"
	end
    end
    eval_or_echo "rm -r $TASKDIR"

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
    echo "Please enter your e-mail address:"
    set EMAIL=$<
    echo "Please enter B2GAnaFW Version tag:"
    set TAG=$<
    set first_data="0"
    set first_mc="0"
    echo "Paste this to the B2G ntuple twiki: https://twiki.cern.ch/twiki/bin/view/CMS/B2GAnaEDMNTuples76X"
    foreach in_dataset (`awk '{ print $2 }' $TASKDIR/input_datasets.txt`)
	set isData=`echo $in_dataset | grep '/MINIAOD$' | wc -l`
	if ( $first_data == 0 && $isData ) then
	    set first_data=1
	    echo
	    echo "| *Dataset* | *Submitter* | *Status* | *Lumi mask* | *Int. lumi [pb-1]* | *Published dataset* | *B2GAnaFW tag* |"
	else if ( $first_mc == 0 && $isData == 0 ) then
	    set first_mc=1
	    echo
	    echo "| *Dataset* | *Submitter* | *Status* | *Nevents* | *Nevents (processed)* | *Published dataset* | *B2GAnaFW tag* |"
	endif
	
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$in_dataset&instance=prod%2Fglobal][$in_dataset]] "
	echo -n "| [[mailto:$EMAIL][$NAME]] "
	if ( $isData ) then
	    set crab_script=`grep $in_dataset $TASKDIR/input_datasets.txt | awk '{ print "'$TASKDIR'/crab_"$1".py" }'`
	    set CERT=`grep lumiMask $crab_script | sed "s;'; ;g;s;/; ;g" | awk '{ print $NF }'`
	    echo -n "| SUBMITTED "
	    echo -n "| [[https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Reprocessing/$CERT][$CERT]] "
	    echo -n "|  "
	else
	    set nevents=`das_client --query="dataset=$in_dataset | grep dataset.nevents" | tail -1`
	    echo -n "| SUBMITTED "
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
    echo "Please enter your e-mail address:"
    set EMAIL=$<
    echo "Please enter B2GAnaFW Version tag:"
    set TAG=$<
    #echo "Please enter Total Int. lumi [pb-1]:"
    #set INTLUMI=$<
    
    echo "Paste this to the B2G ntuple twiki: https://twiki.cern.ch/twiki/bin/view/CMS/B2GAnaEDMNTuples76X"
    set first_data="0"
    set first_mc="0"
    foreach out_dataset ( `cat $TASKDIR/output_datasets.txt` )
	set in_dataset=`das_client --query="parent dataset=$out_dataset instance=prod/phys03" | tail -1`
	### set primary_dataset=`echo $in_dataset | sed "s;/; ;g" | awk '{ print $1 }'`
	set isData=`echo $in_dataset | grep '/MINIAOD$' | wc -l`
	if ( $first_data == 0 && $isData ) then
	    set first_data=1
	    echo
	    echo "| *Dataset* | *Submitter* | *Status* | *Lumi mask* | *Int. lumi [pb-1]* | *Published dataset* | *B2GAnaFW tag* |"
	else if ( $first_mc == 0 && $isData == 0 ) then
	    set first_mc=1
	    echo
	    echo "| *Dataset* | *Submitter* | *Status* | *N_events (orig. dataset)* | *N_events processed* | *Published dataset* | *B2GAnaFW tag* |"
	endif
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$in_dataset&instance=prod%2Fglobal][$in_dataset]] "
	echo -n "| [[mailto:$EMAIL][$NAME]]"
	if ( $isData ) then
	    set crab_script=`grep $in_dataset $TASKDIR/input_datasets.txt | awk '{ print "'$TASKDIR'/crab_"$1".py" }'`
	    set CERT=`grep lumiMask $crab_script | sed "s;'; ;g;s;/; ;g" | awk '{ print $NF }'`
	    echo -n "| COMPLETED "
	    echo -n "| [[https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Reprocessing/$CERT][$CERT]] "
	    echo -n "|  "#$INTLUMI  "
	else
	    set nevents=`das_client --query="dataset=$in_dataset | grep dataset.nevents" | tail -1`
	    set nevents_proc=`das_client --query="dataset=$out_dataset instance=prod/phys03 | grep dataset.nevents" | tail -1`
	    if ( $nevents == $nevents_proc ) then
		echo -n "| COMPLETED "
	    else
		echo -n "| SUBMITTED "
	    endif
	    echo -n "|  $nevents "
	    echo -n "|  $nevents_proc "
	endif
	echo -n "| [[https://cmsweb.cern.ch/das/request?input=$out_dataset&instance=prod%2Fphys03][$out_dataset]] "
	echo "| $TAG |"
    end
    
endif
rm Usage.txt


