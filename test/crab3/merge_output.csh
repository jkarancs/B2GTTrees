#!/bin/tcsh
# Author: Janos Karancsi
# E-mail: janos.karancsi@cern.ch
# Desc:   Simple Tool that merges root files inside sub-directories in <IN_DIR>
#         into single root files in <OUT_DIR>

echo "Usage: -h, --help - shows this help "                >! Usage.txt
echo "" >> Usage.txt
echo "  source merge_output.csh <IN_DIR> <OUT_DIR>"        >> Usage.txt
echo "" >> Usage.txt
echo "  root files inside sub-directories in <IN_DIR> are" >> Usage.txt
echo "  merged into single root files in <OUT_DIR> "       >> Usage.txt
echo "  file names will be that of the sub-directories'"   >> Usage.txt
echo "  HT bins/ST channels etc. are also merged"          >> Usage.txt
echo "" >> Usage.txt
echo "  Normally scrips produces the commands to run"      >> Usage.txt
echo "  Add --run additionally to excecute the script"     >> Usage.txt

if ( $1 == "-h" || $1 == "--help" || $#argv < 2 ) then
    cat Usage.txt; rm Usage.txt; exit
endif

set INDIR=$1
set OUTDIR=$2

# Alias
if ( `echo "$3" | grep "\-\-run" | wc -l` ) then
    alias eval_or_echo   'echo \!* >! temp.csh; source temp.csh; rm temp.csh'
else
    alias eval_or_echo   'echo \!*'
endif

foreach dir ( `ls -d $INDIR/*` )
    set SUB_DIR=`echo $dir | sed "s;/; ;g" | awk '{ print $NF }'`
    eval_or_echo "hadd $OUTDIR/$SUB_DIR.root $INDIR/$SUB_DIR/*.root"
    #eval_or_echo "rm $DIR/SUB_DIR/*.root"
end

set Merge=( \
    "$OUTDIR/JetHT.root"                   "$OUTDIR/JetHT*.root" \
    "$OUTDIR/SingleElectron.root"          "$OUTDIR/SingleElectron*.root" \
    "$OUTDIR/SingleMuon.root"              "$OUTDIR/SingleMuon*.root" \
    "$OUTDIR/GJets_HT-40ToInf.root"        "$OUTDIR/GJets_HT-*.root" \
    "$OUTDIR/QCD_HT100toInf.root"          "$OUTDIR/QCD_HT*.root" \
    "$OUTDIR/SingleTop.root"               "$OUTDIR/ST_*.root" \
    "$OUTDIR/TTJets_HT-600ToInf.root"      "$OUTDIR/TTJets_HT-*.root" \
    "$OUTDIR/TTV.root"                     "$OUTDIR/TTWJetsToLNu.root $OUTDIR/TTZ*.root" \
    "$OUTDIR/WJetsToLNu_HT-100ToInf.root"  "$OUTDIR/WJetsToLNu_HT-*.root" \
    "$OUTDIR/Diboson_Small.root"           "$OUTDIR/WW.root $OUTDIR/WZ.root $OUTDIR/ZZ.root" \
    "$OUTDIR/Diboson_Large.root"           "$OUTDIR/WWTo*.root $OUTDIR/WZTo*.root $OUTDIR/ZZTo*.root" \
    "$OUTDIR/ZJetsToNuNu_HT-100ToInf.root" "$OUTDIR/ZJetsToNuNu_HT-*.root" \
)
set Nmerge=`expr $#Merge / 2`
foreach i ( `seq 1 $Nmerge` )
    set j=`expr $i \* 2 - 1`
    set k=`expr $i \* 2`
    set in=`ls $Merge[$k] | tr "\n" " "`
    eval_or_echo "hadd $Merge[$j] $in"
    eval_or_echo "rm $in"
end
