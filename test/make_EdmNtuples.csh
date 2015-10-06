if ( $#argv < 5 ) then
    echo "Usage:\n  source make_EdmNtuples.csh <edm-version> <name> <input_directory> <output_directory> <number of parallel jobs>"
    exit
endif

set version=$1
set name=$2
set input_dir=$3
set output_dir=$4
set Nparallel=$5

ls $input_dir | grep ".root" | awk '{ print "'$input_dir'/"$1 }' >! files.txt
if ( -f make_edmtrees_"$version"_$name.csh ) mv make_edmtrees_"$version"_$name.csh make_edmtrees_"$version"_"$name"_prev.csh
set n=`cat files.txt | wc -l`
foreach i ( `seq 1 $n` )
    set infile=`sed -n "$i"p files.txt`
    set edmfile="$output_dir/$version/$name/B2GEDMNtuple_$i.root"
    echo 'nice cmsRun $CMSSW_BASE/src/Analysis/B2GAnaFW/test/b2gedmntuples_cfg.py sample="file:'$infile'" outputLabel="file:'$edmfile'" DataProcessing=MC25ns globalTag=MCRUN2_74_V9 maxEvents=-1' >>! make_edmtrees_"$version"_$name.csh
end
rm files.txt

mkdir -p $output_dir/$version/$name
source $CMSSW_BASE/src/Analysis/B2GTTrees/test/crab3/source_parallel.csh make_edmtrees_"$version"_$name.csh $Nparallel
