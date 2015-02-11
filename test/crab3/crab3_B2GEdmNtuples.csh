#!/bin/tcsh
# Author: Janos Karancsi
# E-mail: janos.karancsi@cern.ch
# Tool: multicrab-like tool to create, submit, get status of crab3 tasks for B2GEdmNtuples
#       When jobs finish, we can also get report and download all output files locally

echo "crab3_B2GEdmNtuples.csh usage:                                                              " >! Usage.txt
echo "                                                                                            " >> Usage.txt
echo "source crab3_B2GEdmNtuples.csh create <TASKNAME>                                            " >> Usage.txt
echo "                                                                                            " >> Usage.txt
echo "  Set the DATASETS variable to the datasets that you want to run on, set also the           " >> Usage.txt
echo "  SE_SITE, and SE_USERDIR variables below to where you want to send output, then a directory" >> Usage.txt
echo "  named B2G_edm_<TASKNAME> is automatically created containing py config files for each task" >> Usage.txt
echo "                                                                                            " >> Usage.txt
echo "source crab3_B2GEdmNtuples.csh submit <TASKNAME>                                            " >> Usage.txt
echo "                                                                                            " >> Usage.txt
echo "  Check that the config files are accurate, and then add --run after                        " >> Usage.txt
echo "  the command to submit jobs to grid or paste the output that is written                    " >> Usage.txt
echo "                                                                                            " >> Usage.txt
echo "source crab3_B2GEdmNtuples.csh status <TASKNAME>                                            " >> Usage.txt
echo "                                                                                            " >> Usage.txt
echo "  Show commands to check status of tasks, add --run to excecute them		          " >> Usage.txt
echo " 											          " >> Usage.txt
echo "source crab3_B2GEdmNtuples.csh report <TASKNAME>					          " >> Usage.txt
echo " 											          " >> Usage.txt
echo "  Show commands to get report of tasks, add --run to excecute them			  " >> Usage.txt
echo " 											          " >> Usage.txt
echo "source crab3_B2GEdmNtuples.csh download <TASKNAME>					  " >> Usage.txt
echo " 											          " >> Usage.txt
echo "  Download all root output files from the Storage element to a local directory (DLDIR)      " >> Usage.txt
echo "  Check that the SRM site name and url is defined for SE_SITE in the se_util.csh	          " >> Usage.txt
echo "  script (SITE_INFO is the vector that contains this info)                                  " >> Usage.txt
if ( $1 == "-h" || $1 == "--help" ) then
    cat Usage.txt; rm Usage.txt; exit
endif
rm Usage.txt

# options
set cmd=$1
set TASKNAME=$2
# Working directory name (created in the current directory)
set DIR="B2G_edm_"$TASKNAME

# ----------------------------- Set These variables -----------------------------

# Output storage element site and user directory (output is copied there)
set SE_SITE="T2_HU_Budapest"
set SE_USERDIR="/store/user/jkarancs/SusyAnalysis/B2GEdmNtuple"

# Local directory (output is copied here from the above storage element)
set DLDIR="/data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/"$TASKNAME # download directory (copies output here from SE)

# List here the datasets you want to run on
# Short name (subdir)    # MINIAODSIM Dataset name
set DATASETS=( \
"TT"                     "/TT_Tune4C_13TeV-pythia8-tauola/Phys14DR-PU20bx25_tsg_PHYS14_25_V1-v1/MINIAODSIM" \
"T_tW-channel"           "/T_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"Tbar_tW-channel"        "/Tbar_tW-channel-DR_Tune4C_13TeV-CSA14-powheg-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"WJetsToLNu"             "/WJetsToLNu_13TeV-madgraph-pythia8-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"WJetsToLNu_HT-100to200" "/WJetsToLNu_HT-100to200_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"WJetsToLNu_HT-200to400" "/WJetsToLNu_HT-200to400_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"WJetsToLNu_HT-400to600" "/WJetsToLNu_HT-400to600_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"WJetsToLNu_HT-600toInf" "/WJetsToLNu_HT-600toInf_Tune4C_13TeV-madgraph-tauola/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"DYJetsToLL"             "/DYJetsToLL_M-50_13TeV-madgraph-pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"QCD_Pt_20to30_bcToE"    "/QCD_Pt_20to30_bcToE_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v2/MINIAODSIM" \
"QCD_Pt_30to80_bcToE"    "/QCD_Pt_30to80_bcToE_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"QCD_Pt_80to170_bcToE"   "/QCD_Pt_80to170_bcToE_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v2/MINIAODSIM" \
"QCD_Pt_170toInf_bcToE"  "/QCD_Pt_170toInf_bcToE_Tune4C_13TeV_pythia8/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"QCD_HT-100To250"        "/QCD_HT-100To250_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"QCD_HT_250To500"        "/QCD_HT_250To500_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v2/MINIAODSIM" \
"QCD_HT-500To1000"       "/QCD_HT-500To1000_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/MINIAODSIM" \
"QCD_HT_1000ToInf"       "/QCD_HT_1000ToInf_13TeV-madgraph/Phys14DR-PU20bx25_PHYS14_25_V1_ext1-v1/MINIAODSIM" \
"GGJets_M-200To500"      "/GGJets_M-200To500_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"GGJets_M-500To1000"     "/GGJets_M-500To1000_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"GGJets_M-1000To2000"    "/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"GGJets_M-2000To4000"    "/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"GGJets_M-4000To8000"    "/GGJets_M-4000To8000_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
"GGJets_M-8000To13000"   "/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/Phys14DR-PU20bx25_PHYS14_25_V1-v1/MINIAODSIM" \
)

# -------------------------------------------------------------------------------

# Aliases
if ( ! (-e $PWD/source_parallel.csh) || ! (-e $PWD/se_util.csh) ) then
    echo "Please run this script from the same directory where\nsource_parallel.csh and se_util.csh is or copy them here" 
    exit
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
    alias eval_or_echo   'echo \!*;echo \!* >! temp.csh; source temp.csh; rm temp.csh'
    set dry="0"
else
    alias eval_or_echo   'echo \!*'
    set dry="1"
endif

if ( `echo $cmd | grep "create" | wc -l` ) then
    mkdir $DIR
    sed "s;PUBNAME;$DIR;;s;SE_SITE;$SE_SITE;;s;SE_USERDIR;$SE_USERDIR;" crab_template_edmntuple_py.txt > $DIR/crab_template_edmntuple_py.txt
    set Nsite=`expr $#DATASETS / 2`
    foreach i ( `seq 1 $Nsite` )
        set j=`expr $i \* 2 - 1`
        set k=`expr $i \* 2`
	sed "s;TASK;$DATASETS[$j];;s;DATASET;$DATASETS[$k];" $DIR/crab_template_edmntuple_py.txt > $DIR/crab_$DATASETS[$j].py
    end
    rm $DIR/crab_template_edmntuple_py.txt
    echo "Config files ready in directory: "$DIR
    ls -ltr $DIR

else if ( `echo $cmd | grep "submit" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    eval_or_echo "cd B2G-edm-Feb04"
    foreach cfg_file ( `ls -ltr $DIR/*.py | awk '{ print $NF }'`)
        eval_or_echo "crab submit -c $cfg_file"
    end
    eval_or_echo "cd .."

else if ( `echo $cmd | grep "status" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `ls -ltrd $DIR/* | grep "^d" | awk '{ print $NF }'`)
        eval_or_echo "crab status -d $dir"
    end
    
else if ( `echo $cmd | grep "download" | wc -l` ) then
    if ( $dry == "1" ) echo "source dl_$TASKNAME.csh \nOR add --run after command to excecute following lines:\n"
    echo 'set DLDIR="/data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/'"$TASKNAME"'"' >! dl_$TASKNAME.csh
    echo 'alias se "source se_util.csh \\!*"\n' >> dl_$TASKNAME.csh
    echo 'mkdir -p $DLDIR' >> dl_$TASKNAME.csh
    eval_or_echo "mkdir -p $DLDIR"
    foreach taskdir ( `ls -ltrd $DIR/*/ | sed "s;/; ;g" | awk '{ print $NF }'`)
        set primary_dataset=`crab status -d $DIR/$taskdir | grep "Output dataset:" | awk '{ print $3 }' | sed "s;/; ;g" | awk '{ print $1 }'`
        set SAMPLEDIR=`echo $taskdir | sed "s;crab_;;"`
        eval_or_echo "mkdir -p $DLDIR/$SAMPLEDIR"
        eval_or_echo "cd $DLDIR/$SAMPLEDIR"
        set time=`se ls "$SE_SITE":"$SE_USERDIR/$primary_dataset/$DIR"`
        eval_or_echo "se dl $SE_SITE":"$SE_USERDIR/$primary_dataset/$DIR/$time/0000 --par 4 --run"
        eval_or_echo "cd -"
        echo "mkdir -p "'$DLDIR'"/$SAMPLEDIR" >> dl_$TASKNAME.csh
        echo "cd "'$DLDIR'"/$SAMPLEDIR" >> dl_$TASKNAME.csh
        echo "se dl $SE_SITE":"$SE_USERDIR/$primary_dataset/$DIR/$time/0000 --par 4 --run" >> dl_$TASKNAME.csh
        echo "cd -" >> dl_$TASKNAME.csh
    end


else if ( `echo $cmd | grep "report" | wc -l` ) then
    if ( $dry == "1" ) echo "Add --run after command to excecute following lines:\n"
    foreach dir ( `ls -ltrd $DIR/* | grep "^d" | awk '{ print $NF }'`)
        eval_or_echo "crab report -d $dir"
    end

endif
