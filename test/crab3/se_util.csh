#!/bin/tcsh -f
if ( `which par_source | grep "aliased to" | wc -l` == 0 ) then
    if ( -e source_parallel.csh ) then
	alias par_source 'source source_parallel.csh \!*'
    else if ( -e /data/jkarancs/scripts/source_parallel.csh ) then
	alias par_source 'source /data/jkarancs/scripts/source_parallel.csh \!*'
    else
	"Please set par_source command first"
	" eg.: alias par_source 'source <some_directory>/source_parallel.csh \!*'"
	exit
    endif
endif

set RAND=`uuid | sed "s;-;_;g"`
set DATE=`date | cut -f2- -d" " | sed "s; ;_;g;s;:;h;1;s;:;m;1"`

set cmd=$1
set script_opts=""
set cmd_opts=""
set rest_args=""
set skip=0
foreach n ( `seq 2 $#argv` )
    if ( $skip == 0 ) then
	if ( "$argv[$n]" =~ "--"* ) then
	    set script_opts="$script_opts "$argv[$n]
	    if ( $argv[$n] == "--par" ) then
		set nextn=`expr $n + 1`
	        set Npar=$argv[$nextn]
	        set skip=`expr $skip + 1`
	    endif
	else if ( "$argv[$n]" =~ "-"* ) then
	    set cmd_opts="$cmd_opts "$argv[$n]
	else
	    set rest_args="$rest_args "$argv[$n]
	endif
    else
	set skip=`expr $skip - 1`
    endif
end

#-------------- SE Commands/Paths --------------------

set USERNAME=`whoami`
# Add your site srm paths here
set SITE_INFO=( \
    "T1_US_FNAL"      "srm://cmssrm.fnal.gov:8443/srm/managerv2"          "SFN=/" \
    "T1_US_FNAL_Disk" "srm://cmsdcadisk01.fnal.gov:8443/srm/managerv2"    "SFN=/dcache/uscmsdisk/" \
    "T3_US_FNALLPC"   "srm://cmseos.fnal.gov:8443/srm/v2/server"          "SFN=/" \
    "T2_IT_Rome"      "srm://cmsrm-se01.roma1.infn.it:8443/srm/managerv2" "SFN=/pnfs/roma1.infn.it/data/cms/" \
    "T2_DE_DESY"      "srm://dcache-se-cms.desy.de:8443/srm/managerv2"    "SFN=/pnfs/desy.de/cms/tier2/" \
    "T2_CH_CERN"      "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/" \
    "T2_HU_Budapest"  "srm://grid143.kfki.hu:8446/srm/managerv2"          "SFN=/dpm/kfki.hu/home/cms/phedex/" \
    "T3_HU_Debrecen"  "srm://grid143.kfki.hu:8446"                        "/dpm/kfki.hu/home/cms/phedex/" \
    "desy"            "srm://dcache-se-cms.desy.de:8443/srm/managerv2"    "SFN=/pnfs/desy.de/cms/tier2/" \
    "cern"            "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/" \
    "pixel"           "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/store/group/dpg_tracker_pixel/comm_pixel/" \
    "caf"             "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/store/caf/user/$USERNAME/" \
    "kfki"            "srm://grid143.kfki.hu:8446/srm/managerv2"          "SFN=/dpm/kfki.hu/home/cms/phedex/store/user/$USERNAME/" \
    "deb"             "srm://grid143.kfki.hu:8446"                        "/dpm/kfki.hu/home/cms/phedex/" \
)

# Modify PATHs for commands that don't use the srm:// protocol
# Also replace the sitename of file arguments with these PATHs
#set has_eos=`which eos | grep "aliased to" | wc -l` # SLC5 has eos command too, but has some error, only use at CERN (eg: lxplus) for now
set has_eos=`echo $HOSTNAME | grep "lxplus" | wc -l`
set has_rfio=`echo $HOSTNAME | grep ".kfki.hu" | wc -l`
set use_eos="0"  # use eos ls etc. commands
set use_rfio="0" # use rfdir  etc. commands
set narg="0"
foreach arg ( $rest_args )
    # Replace part of argument specifying site (eg: se ls T2_HU_Budapest: with SRM path)
    set Nsite=`expr $#SITE_INFO / 3`
    foreach i ( `seq 1 $Nsite` )
        set j=`expr $i \* 3 - 2`
        set k=`expr $i \* 3 - 1`
        set l=`expr $i \* 3`
	set SITE=$SITE_INFO[$j]
	set PATH="$SITE_INFO[$k]\\?$SITE_INFO[$l]"
	# Check whether you can use eos/rfio commands and set suitable path for commands
        if ( `echo "$arg" | grep $SITE":" | wc -l` ) then
	    if ( `echo $SITE | grep "cern" | wc -l` && $has_eos == 1 ) then
	        set use_eos="1"
	        set PATH=`echo $SITE_INFO[$l] | sed "s;SFN=;;"`
	    else if ( `echo $SITE | grep "caf" | wc -l` && $has_eos == 1 ) then
	        set use_eos="1"
	        set PATH=`echo $SITE_INFO[$l] | sed "s;SFN=;;"`
	    else if ( (`echo $SITE | grep "kfki" | wc -l` || `echo $SITE | grep "T2_HU_Budapest" | wc -l`) && $has_rfio == 1 ) then
	        set use_rfio="1"
	        setenv DPNS_HOST grid143.kfki.hu
	        setenv DPM_HOST grid143.kfki.hu
	        if ( ! ( $cmd =~ "cp"* || $cmd == "dl" || $cmd == "dl_mis" ) ) set PATH=`echo $SITE_INFO[$l] | sed "s;SFN=;;"`
	    endif
	    set arg=`echo "$arg" | sed "s;$SITE\:;$PATH;"`
	    break
        endif
    end
    set narg=`expr $narg + 1`
    if ( $narg == "1" ) then
        set arg1="$arg"
    else if ( $narg == "2" ) then
        set arg2="$arg"
    else if ( $narg == "3" ) then
        set arg3="$arg"
    endif
end

if ( $use_rfio == 1 ) then
    #alias se-ls        '/usr/bin/rfdir \!* | awk '\''{ print $NF }'\'
    #alias se-ls-l      '/usr/bin/rfdir \!* | awk '\''{ printf "%s %4d %4d %3d %12d %s %s %5s %s\n",$1,$2,$3,$4,$5,$6,$7,$8,$9 }'\'
    if ( $cmd =~ "cp"* || $cmd == "dl" || $cmd == "dl_mis" ) then
	#set se_ls='lcg-ls -b -D srmv2 --vo cms'
	set se_ls='env --unset=LD_LIBRARY_PATH gfal-ls'
    else
	set se_ls='/usr/bin/rfdir'
    endif
    set se_ls_l='/usr/bin/rfdir'
   #set se_cp='/usr/bin/rfcp' # rfcp can not copy from SE to an other SE
    set se_mv='/usr/bin/rfrename'
    set se_rm_r='/usr/bin/rfrm -rf'
    set se_mkdir='/usr/bin/rfmkdir'
    set se_get_perm='/usr/bin/rfstat'
    set se_chmod_664='/usr/bin/rfchmod 664'
    set se_chmod_775='/usr/bin/rfchmod 775'
else
    if ( $use_eos == 1 ) then
	#alias se-ls    'eos ls \!*'
	#alias se-ls-l  'eos ls -l \!*'
       #set se_cp='eos cp' # Works and is fast to copy locally, has to specify a local/eos directory
	set se_ls='eos ls'
	set se_ls_l='eos ls -l'
	set se_rm_r='eos rm -r'
	#set se_mv='eos mv' # there is no known command to move files on EOS on lxplus
	set se_mkdir='eos mkdir'
	set se_get_perm='eos stat' # Instead using this flawed command, we do a workaround with ls -l
	set se_chmod_664='eos chmod 664'
	set se_chmod_775='eos chmod 775'
    else
	#alias se-ls    'lcg-ls -b -D srmv2 --vo cms \!* | sed "s;/; ;g" | awk '\''{ print $NF }'\'
	#alias se-ls-l  'lcg-ls -b -D srmv2 --vo cms -l \!* | sed "s;/; ;g" | awk '\''{ printf "%s %4d %4d %3d %12d %12s %s\n",$1,$2,$3,$4,$5,$6,$NF }'\'
	#set se_ls='lcg-ls -b -D srmv2 --vo cms'
	#set se_ls_l='lcg-ls -b -D srmv2 --vo cms -l'
	set se_ls='env --unset=LD_LIBRARY_PATH gfal-ls'
	set se_ls_l='env --unset=LD_LIBRARY_PATH gfal-ls -l'
	set se_rm='lcg-del -b -D srmv2 --vo cms -l' # much faster than srmrm
	set se_rmdir='srmrmdir'
	set se_mv='srmmv'
	set se_mkdir='srmmkdir'
	set se_get_perm='srm-get-permissions'
	set se_chmod_664='srm-set-permissions -type=CHANGE -group=RW'
	set se_chmod_775='srm-set-permissions -type=CHANGE -group=RWX'
    endif
endif
#set se_cp='lcg-cp -b -D srmv2 --vo cms'
#set se_cp='env -i gfal-copy -p -n 4 -t 86400 -T 86400'
set se_cp='env --unset=LD_LIBRARY_PATH gfal-copy -r'
set se_cp_v='$se_cp -v'
#set se2_ls='lcg-ls -b -D srmv2 --vo cms'
#set se2_ls_l='lcg-ls -b -D srmv2 --vo cms -l'
set se2_ls='env --unset=LD_LIBRARY_PATH gfal-ls'
set se2_ls_l='env --unset=LD_LIBRARY_PATH gfal-ls -l'

#-------------------- Options ------------------------

alias hasopt 'echo "$script_opts" | grep \!* | wc -l'
if ( `hasopt "\-\-dry"` ) then
    alias echo_or_eval   'echo \!*'
    alias peek_or_source 'echo "> Add --run option or Run this script:\nsource "\!*"\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
    if ( `hasopt "\-\-par"` ) alias peek_or_source 'echo "> Add --run option or Run this script:\npar_source "\!*" $Npar\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
else if ( `hasopt "\-\-run"` ) then
    #eval workaround: do not want to interpret newline char for echo
    alias echo_or_eval   'echo \!* >! temp_$RAND.csh; source temp_$RAND.csh; rm temp_$RAND.csh'
    alias peek_or_source 'source \!*; rm \!*'
    if ( `hasopt "\-\-par"` ) alias peek_or_source 'par_source \!* $Npar; rm \!*'
else
    # These are the default actions
    alias echo_or_eval   'echo \!* >! temp_$RAND.csh; source temp_$RAND.csh; rm temp_$RAND.csh'
    alias peek_or_source 'echo "> Add --run option or Run this script:\nsource "\!*"\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
    if ( `hasopt "\-\-par"` ) alias peek_or_source 'echo "> Add --run option or Run this script:\npar_source "\!*" $Npar\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
endif
unalias hasopt

# Additional commands (srmrm is slower than lcg-del)
#alias se-rm    'srmrm \!*'

#alias rfcat    '/usr/bin/rfcat \!*'
#alias rfcomm   '/usr/bin/rfcomm \!*'
#alias rfdf     '/usr/bin/rfdf \!*'
#alias rftp     '/usr/bin/rftp \!*'

# Space and jobs
#lcg-infosites -f BUDAPEST all # Space and jobs

#------------------- Glite/Proxy ---------------------

# Check for LCG env
if ( ! $?GLITE_LOCATION && $HOSTNAME == "grid248" ) source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.csh

# Checking voms proxy
voms-proxy-info > & ! vomsout.txt
if ( `grep "Couldn't find a valid proxy." vomsout.txt` != "" ) then
    echo "---------------- Requesting Voms Proxy ----------------"
    voms-proxy-init --voms cms -valid 168:00
else if ( `grep "Proxy not found" vomsout.txt` != "" ) then
    echo "---------------- Requesting Voms Proxy ----------------"
    voms-proxy-init --voms cms -valid 168:00
else if ( `grep "timeleft" vomsout.txt | awk '{ print $3 }'` == "0:00:00" ) then
    echo "------------ Proxy Expired, Requesting New ------------"
    voms-proxy-init --voms cms -valid 168:00
endif
rm vomsout.txt


#----------------- Excecute Command ------------------
if ( $cmd == "ls" ) then
    echo_or_eval "$se_ls $arg1 | sed "\""s;/; ;g"\"" | awk '{ print "'$NF'" }'"

else if ( $cmd == "ls-l" ) then
    if ( $use_rfio == 1 ) then
	echo_or_eval "$se_ls $arg1 | awk '{ printf "\""%s %4d %4d %3d %12d %s %s %5s %s\\n"\"',$1,$2,$3,$4,$5,$6,$7,$8,$9'" }'"
    else if ( $use_eos == 1 ) then
	echo_or_eval "$se_ls_l $arg1"
    else
	echo_or_eval "$se_ls_l $arg1 | sed "\""s;/; ;g"\"" | awk '{ printf "\""%s %4d %4d %3d %12d %12s %s\\n"\"',$1,$2,$3,$4,$5,$6,$NF'" }'"
    endif

else if ( $cmd == "cp" ) then # specify filename
    echo "$se_cp $arg1 $arg2" >! cp_$DATE.csh
    peek_or_source "cp_$DATE.csh"

else if ( $cmd == "cp-v" ) then
    echo "$se_cp_v $arg1 $arg2" >! cp_$DATE.csh
    peek_or_source "cp_$DATE.csh"

else if ( $cmd == "cplfn" ) then
    set localfile="/data"`echo "$arg1" | sed "s;$PATH;;"`
    #  Create subdirectories and download file
    echo "-------------------------------------------------------"
    echo "Copying file: $arg1"
    echo "To: $localfile"
    echo_or_eval "mkdir -p "`dirname $localfile`
    # Copy from the cern server
    echo_or_eval "$se_cp $arg1 "$localfile
    echo "-------------------------------------------------------"
    echo "Setting file and directry read/write permissions"
    echo_or_eval "find "`dirname $localfile`" -type d -exec chmod 775 {} +"
    echo_or_eval "find "`dirname $localfile`" -type f -exec chmod 664 {} +"
    echo "-------------------------------------------------------"
    unset localfile

else if ( $cmd == "rm" ) then
    if ( $use_rfio == 1 || $use_eos == 1 ) then
    	echo "$se_rm_r $arg1" >! rm_$DATE.csh
        peek_or_source "rm_$DATE.csh"
    else
        ( eval "$se_ls_l $arg1" >! lsout_$RAND.txt ) >& /dev/null
        set nout=`cat lsout_$RAND.txt | wc -l`
        if ( $nout == 0 ) then
            echo "File/Directory does not exist"
        else
	    ( sed "s;/; ;g" lsout_$RAND.txt | awk '{ print "'"$se_rm"' "$NF }' | sed "s;$se_rm ;$se_rm $arg1/;;s;\?;\\\?;" >! rm_$DATE.csh ) >& /dev/null
            if ( $nout == 1 ) then
                if ( `cat lsout_$RAND.txt | grep "^d" | wc -l` ) then
                    echo "$se_rmdir $arg1" >! rm_$DATE.csh
                else 
                    set list_lastfile=`sed "s;/; ;g" lsout_$RAND.txt | awk '{ print $NF }'`
                    set arg1_lastfile=`echo "$arg1" | sed "s;/; ;g" | awk '{ print $NF }'`
                    if ( $list_lastfile == "$arg1"_lastfile ) then
			echo "$se_rm $arg1" >! rm_$DATE.csh
                    else 
			echo "$se_rmdir $arg1" >> rm_$DATE.csh
                    endif
		    unset list_lastfile
		    unset arg1_lastfile
                endif
            else
                echo "$se_rmdir $arg1" >> rm_$DATE.csh
            endif
            peek_or_source "rm_$DATE.csh"
        endif
        rm lsout_$RAND.txt
        unset nout
    endif

else if ( $cmd == "mv" ) then
    if ( $HOSTNAME =~ "lxplus"* ) then
	echo "Sorry, there are no commands to move SE files on lxplus"
	echo "Use srmmv on another computer!"
    else
	echo "$se_mv $arg1 $arg2" >! mv_$DATE.csh
	peek_or_source "mv_$DATE.csh"
    endif

else if ( $cmd == "mkdir" ) then
    echo_or_eval "$se_mkdir $arg1"

else if ( $cmd == "get-perm" ) then
    if ( $HOSTNAME =~ "lxplus"* ) then
	# There is no srm-get-permissions command on lxplus
	# You could use eos stat, but it's no good
	# Workaround: We ls -l on the parent directory, and grep for the file/dir
	set arg1_lastfile=`echo "$arg1" | sed "s;/; ;g" | awk '{ print $NF }'`
	set parent=`echo "$arg1" | sed 's;'"$arg1_lastfile"';;g;s;/$;;;s;/$;;'`
	echo_or_eval "$se_ls_l $parent | grep $arg1_lastfile"
    else
	echo_or_eval "$se_get_perm $arg1"
    endif

else if ( $cmd == "set-perm" ) then
    ( eval "$se_ls_l $arg1" >! lsout_$RAND.txt ) >& /dev/null
    set nout=`cat lsout_$RAND.txt | wc -l`
    if ( $nout == 0 ) then
	echo "File/Directory does not exist"
    else 
	( sed "s;/; ;g" lsout_$RAND.txt | awk '{ print "'"$se_chmod_664"' "$NF }' | sed "s;$se_chmod_664 ;$se_chmod_664 $arg1/;;s;\?;\\\?;" >! set_perm_$DATE.csh ) >& /dev/null
	if ( $nout == 1 ) then
	    if ( `cat lsout_$RAND.txt | grep "^d" | wc -l` ) then
		echo "$se_chmod_775 $arg1" >! set_perm_$DATE.csh
	    else
                set list_lastfile=`sed "s;/; ;g" lsout_$RAND.txt | awk '{ print $NF }'`
                set arg1_lastfile=`echo "$arg1" | sed "s;/; ;g" | awk '{ print $NF }'`
                if ( $list_lastfile == "$arg1"_lastfile ) then
	            echo "$se_chmod_664 $arg1" >! rm_$DATE.csh
                else 
	            echo "$se_chmod_775 $arg1" >> rm_$DATE.csh
                endif
	        unset list_lastfile
	        unset arg1_lastfile
	    endif
	else
	    echo "$se_chmod_775 $arg1" >> set_perm_$DATE.csh
	endif
	peek_or_source "set_perm_$DATE.csh"
    endif
    rm lsout_$RAND.txt
    unset nout

else if ( $cmd == "mis" ) then
    eval "$se_ls $arg1" | sed 's;_; ;g;s;\.root;;' | awk '{ print $NF }' | sort | uniq > jobnums_$RAND.txt
    if ( $narg < 2 ) then
	echo "Need more arguments, Use:"
	echo "se mis <se_dir> Njobs"
	echo "se mis <se_dir> iJobBeg iJobEnd"
    else
	if ( $#argv == 2 ) then
	    set BEG=1
	    set END=$arg2
	else
	    set BEG=$arg2
	    set END=$arg3
	endif
        while ( $BEG <= $END )
            set n=`cat jobnums_$RAND.txt | grep '^'$BEG'$'`
            if ( .$n == . ) then
                echo -n $BEG","
            endif
            set BEG = `expr $BEG + 1`
        end
	echo
	rm jobnums_$RAND.txt
	unset BEG
	unset END
    endif

else if ( $cmd == "dl" ) then # specify output directory
    if ( $narg == "1" ) set arg2="."
    eval "$se_ls $arg1" | grep "\.root" | sed "s;/; ;g" | awk '{ print "'"$se_cp"' ARG1/"$NF" ARG2/"$NF }' | sed "s;ARG1;$arg1;;s;ARG2;$arg2;;s;?;\\?;g" > ! dl_$DATE.csh
    peek_or_source "dl_$DATE.csh"

else if ( $cmd == "dl_mis" ) then
    if ( $narg < 2 ) then
	echo "Need more arguments, Use:"
	echo "se dl_mis <se_dir> <local_dir>"
    else
	eval "$se_ls $arg1" >! lsout_$RAND.txt;
	sed "s;/; ;g" lsout_$RAND.txt | awk '{ print "'"$se_cp_v"' ARG1/"$NF" ARG2/"$NF }' | sed "s;ARG1;$arg1;;s;ARG2;$arg2;;s;?;\\?;g" >! dl_temp_$RAND.csh
	sed "s;_[0-9]*_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]\.root;\.root;;s;\.root;;;s;_; ;g" lsout_$RAND.txt | awk '{ printf "%d\n",$NF }' >! jobnums_se_$RAND.txt
	rm lsout_$RAND.txt
	if ( `echo "$arg2" | grep "srm:" | wc -l` ) then
	    eval "$se2_ls_l -l $arg2" | grep "\.root" | sed "s;/; ;g" | awk '{ print $5,$NF }' | grep -v "^0" | sed "s;_[0-9]*_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]\.root;\.root;;s;\.root;;;s;_; ;g" | awk '{ printf "%d\n",$NF }' > ! jobnums_dled_$RAND.txt
	else
	    ls -l $arg2 | grep "\.root" | awk '{ print $5,$NF }' | grep -v "^0" | sed "s;_[0-9]*_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]\.root;\.root;;s;\.root;;;s;_; ;g" | awk '{ printf "%d\n",$NF }' > ! jobnums_dled_$RAND.txt
	endif
	foreach jobnum ( `cat jobnums_se_$RAND.txt` )
	    if ( ! `grep '^'$jobnum'$' jobnums_dled_$RAND.txt | wc -l` ) then
		# old crab format
		#grep "_"$jobnum"_[0-9]_[0-9a-zA-Z][0-9a-zA-Z][0-9a-zA-Z]\.root" dl_temp_$RAND.csh >>! dl_mis_$DATE.csh
		# This is for TSBatch output format
		#grep "_"`printf "%04d" $jobnum`"\.root" dl_temp_$RAND.csh >>! dl_mis_$DATE.csh
		# crab3 format
		grep "_"`printf "%d" $jobnum`"\.root" dl_temp_$RAND.csh >>! dl_mis_$DATE.csh
	    endif
	end
	rm jobnums_se_$RAND.txt jobnums_dled_$RAND.txt dl_temp_$RAND.csh
	if ( ! -e dl_mis_$DATE.csh ) then
	    echo "All files are downloaded already"
	else
	    peek_or_source "dl_mis_$DATE.csh"
	endif
    endif

else if ( $cmd == "dirsize" || $cmd == "ds" ) then
    if ( $narg < 1 ) then
	echo "Need more arguments, Use:"
	echo "se dirsize <se_dir>"
    else
	echo "$arg1" >! subdirs_$RAND.txt
	set Ndone=0
	set Ntotal=0
	set SUBTOTAL=0
	set TOTAL=0
	while ( `cat subdirs_$RAND.txt | wc -l` )
	    set curr_dir=`head -1 subdirs_$RAND.txt`
	    sed -i -e "1d" subdirs_$RAND.txt
	    eval "$se_ls_l $curr_dir" >! lsout_$RAND.txt
	    # Remove the same directory (stupid behaviour of lcg-ls for empty directories)
	    grep '^d' lsout_$RAND.txt >! dirs_$RAND.txt
	    if ( -f dirs_clean_$RAND.txt ) rm dirs_clean_$RAND.txt
	    touch dirs_clean_$RAND.txt
	    while ( `cat dirs_$RAND.txt | grep '^d' | wc -l` )
		set curr=`head -1 dirs_$RAND.txt | awk '{ print $NF }'`
		if ( ! `echo "$curr_dir" | grep $curr | wc -l` ) then
		    head -1 dirs_$RAND.txt >> dirs_clean_$RAND.txt
		endif
		sed -i -e "1d" dirs_$RAND.txt
	    end
	    # Append new subdirs in front
	    cat dirs_clean_$RAND.txt | sed "s;/; ;g" | awk '{ print $NF }' | sed 's;^;'"$curr_dir/"';;s;\?;\\\?;' >! newsubdirs_$RAND.txt
	    if ( $Ntotal == 0 ) then
		set Ntotal=`cat newsubdirs_$RAND.txt | wc -l`
		cp newsubdirs_$RAND.txt main_subdirs_$RAND.txt
	    endif
	    cat subdirs_$RAND.txt >> newsubdirs_$RAND.txt
	    mv newsubdirs_$RAND.txt subdirs_$RAND.txt
	    rm dirs_$RAND.txt dirs_clean_$RAND.txt
	    # Count total file sizes
	    grep -v '^d' lsout_$RAND.txt >! files_$RAND.txt
	    set SUM=0
	    if ( `wc -l files_$RAND.txt | awk '{ print $1 }'` ) set SUM=`awk '{total = total + $5}END{print total}' files_$RAND.txt`
	    rm files_$RAND.txt
	    set SUBTOTAL=`expr $SUBTOTAL + $SUM`
	    # Print total subdir sizes (recursive)
	    set N=`wc -l subdirs_$RAND.txt | awk '{ print $1 }'`
	    if ( $N == `expr $Ntotal - $Ndone - 1` ) then
		# Print total subdir size
		set Ndone=`expr $Ndone + 1`
		set subdir=`sed -n "$Ndone"p main_subdirs_$RAND.txt | sed "s;/; ;g" | awk '{ print $NF }'`
		echo $SUBTOTAL $subdir | awk '{ printf "%5.1f GB    %s\n", $1/1073741824, $2 }'
		set TOTAL=`expr $TOTAL + $SUBTOTAL`
		set SUBTOTAL=0
	    endif
	end
	echo "---------------------"
	echo $TOTAL "--TOTAL--" | awk '{ printf "%5.1f GB    %s\n", $1/1073741824, $2 }'
	rm main_subdirs_$RAND.txt lsout_$RAND.txt subdirs_$RAND.txt
    endif

else
    echo "Unknown command"

endif


