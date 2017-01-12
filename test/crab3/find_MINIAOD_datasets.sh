mc_datasets=(
    "dataset=/*/RunIISummer16*/MINIAODSIM"
)


mc_find_exclude_list=(
    #'strings to grep on, use regular expressions:strings separated by , to exclude'
#    '/SMS-T[1,2,5]tt.*Fast:2Lfilter'
#    '/SMS-T[1,2,5]tt:Fast'
#    '/TT_|/TTJets_:_HT-,Lept,Mtt,RECODEBUG,mtop,mpiOFF,noCR,up,down,alphaS,widthx,RAWAODSIM_80X' # OLD
#    '/TTJets_HT-:'
#    '/TT_|/TTJets_:HT-,Lept,lept,down,up,mtop,evtgen'
#    '/TTWJetsToLNu_|/TTWJetsToQQ_:_ext2'
#    '/TTZToLLNuNu_|/TTZToQQ_:'
#    '/TTGJets_:_ext'
#    '/TTTT_TuneCUETP8M2T4:'
#    '/ST.*inclusiveDecays.*TuneCUETP8M2T4|/ST_s-channel:up,down,mtop,_DS'
#    #'/QCD:Enriched,ALCATkAlMinBias,HcalNZSRAW,RECODEBUG'
#    '/QCD_HT:BGenFilter,GenJets5,_ext' 
#    #'/QCD_HT.*_ext:BGenFilter,GenJets5'
#    '/DYJetsToLL_M.*_HT:_ext,DYJetsToLL_M-50_HT-600toInf'
#    #'/DYJetsToLL_M.*_HT.*_ext:'
#    '/DYJetsToQQ_:'
#    '/ZJetsToNuNu_HT:_ext'
#    #'/ZJetsToNuNu_HT.*_ext:'
#    '/ZJetsToQQ_:'
#    '/WJetsToLNu_HT:_ext'
#    '/WJetsToLNu_HT.*_ext:'
#    '/WJetsToQQ_:HT-600ToInf'
#    '/WWTo.*powheg:Up,Down,Mll,herwigpp,_ext'
#    '/WZTo.*amcatnloFXFX:PtZ'
#    '/ZZTo:ZZTo4L_13TeV-amcatnloFXFX,sherpa'
#    '/WWW|/WWZ|/WZZ|/ZZZ:'
)


# First make a list of available datasets from DAS
#echo -n "" > mc_datasets.txt
#for mc in "${mc_datasets[@]}"; do
#    das_client --limit=100000 --query=$mc >> mc_datasets.txt
#done

# Loop over DB servers
for item in ${mc_find_exclude_list[@]}; do
    unset exclList
    # split sub-list if available
    if [[ $item == *":"* ]]; then
        # split server name from sub-list
        tmpArray=(${item//:/ })
        find=${tmpArray[0]}
        exclList=${tmpArray[1]}
        # make array from simple string
        exclList=(${exclList//,/ })
    fi

    # find datasets and exclude those you don't need
    grep -E "$find" mc_datasets.txt | sort > result.txt
    for excl in ${exclList[@]}; do
        grep -v "$excl" result.txt > temp.txt
	mv temp.txt result.txt
    done
    echo '------------------------------ Result for "'$item'" -------------------------'
    sort result.txt
    echo
    rm result.txt
done
echo '-----------------------------------------------------------------------------'

#rm mc_datasets.txt
