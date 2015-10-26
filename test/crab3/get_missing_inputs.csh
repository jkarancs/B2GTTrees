set taskdir=$1
set njobs=$2
if ( ! -e $taskdir/results/lumiSummary.json ) then
    crab report -d $taskdir
endif
grep "Result:" $taskdir/crab.log | tail -1 | tr ' ' '\n' | grep ".root" | sed "s;_; ;g;s;.root; ;g" | awk '{ print $(NF-1) }' | sort -n | uniq >! jobnums.txt

set base=`grep "Result:" $taskdir/crab.log | tail -1 | tr ' ' '\n' | grep ".root" | grep "B2GEDMNtuple" | sed "s;';;g;s;[0-9]*.root; ;g" | awk '{ print $1 }' | uniq`

# find missing files
set N=1
set missing=""
foreach N ( `seq 1 $njobs` )
    if ( `grep '^'$N'$' jobnums.txt | wc -l` == 0 ) echo "'"$base$N".root',"
end
unset N
rm jobnums.txt

