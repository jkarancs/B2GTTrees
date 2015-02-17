if ( $#argv < 4 ) then
    echo "Usage:\n  source make_EdmNtuples.csh <edm-version> <name> <input_directory> <number of parallel jobs>"
    exit
endif

set version=$1
set name=$2
set edmdir="/data/gridout/jkarancs/SusyAnalysis/B2G/EdmNtuple/$version/$name"
set input_dir=$3
set Nparallel=$4

ls $input_dir | grep ".root" | awk '{ print "'$input_dir'/"$1 }' >! files.txt
set n=`cat files.txt | wc -l`
if ( -f make_edmtrees_"$version"_$name.csh ) then
    mv make_edmtrees_"$version"_$name.csh make_edmtrees_"$version"_"$name"_prev.csh
endif
foreach i ( `seq 1 $n` )
    set infile=`sed -n "$i"p files.txt`
    set edmfile="$edmdir/B2GEDMNtuple_$i.root"
    echo 'cmsRun ../../../../Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py maxEvts=-1 sample="file:'$infile'" outputLabel="file:'$edmfile'" LHE=False' >>! make_edmtrees_"$version"_$name.csh
end
rm files.txt

mkdir -p $edmdir
source crab3/source_parallel.csh make_edmtrees_"$version"_$name.csh $Nparallel
