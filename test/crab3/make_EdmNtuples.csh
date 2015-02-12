if ( $#argv < 3 ) then
    echo "Usage:\n  source make_EdmNtuples.csh <name> <input_directory> <number of parallel jobs>"
    exit
endif

set name=$1
set edmdir="/data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/Signal_Feb04/"$name
set input_dir=$2
set Nparallel=$3

ls $input_dir | grep ".root" | awk '{ print "'$input_dir'/"$1 }' >! files.txt
set n=`cat files.txt | wc -l`
if ( -f make_ttrees_$name.csh ) then
    mv make_ttrees_$name.csh make_ttrees_"$name"_prev.csh
endif
if ( -f make_edmtrees_$name.csh ) then
    mv make_edmtrees_$name.csh make_edmtrees_"$name"_prev.csh
endif
foreach i ( `seq 1 $n` )
    set infile=`sed -n "$i"p files.txt`
    set i=`echo $i | awk '{ printf "%03d\n",$1 }'`
    set edmfile="$edmdir/B2GEDMNtuple_$i.root"
    echo 'cmsRun ../../../../Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py maxEvts=-1 sample="file:'$infile'" outputLabel="file:'$edmfile'" LHE=False' >>! make_edmtrees_$name.csh
end
rm files.txt

mkdir -p $edmdir
source source_parallel.csh make_edmtrees_$name.csh $Nparallel
