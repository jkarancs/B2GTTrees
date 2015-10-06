#!/bin/tcsh
if ( `which par_source | grep "aliased to" | wc -l` == 0 ) then
    if ( -e source_parallel.csh ) then
	alias par_source 'source source_parallel.csh \!*'
    else
	"Please set par_source command first"
	" eg.: alias par_source 'source <some_directory>/source_parallel.csh \!*'"
	exit
    endif
endif

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
    "T1_US_FNAL"     "srm://cmssrm.fnal.gov:8443/srm/managerv2"          "SFN=/" \
    "T3_US_FNALLPC"  "srm://cmseos.fnal.gov:8443/srm/v2/server"          "SFN=/" \
    "T2_IT_Rome"     "srm://cmsrm-se01.roma1.infn.it:8443/srm/managerv2" "SFN=/pnfs/roma1.infn.it/data/cms" \
    "T2_DE_DESY"     "srm://dcache-se-cms.desy.de:8443/srm/managerv2"    "SFN=/pnfs/desy.de/cms/tier2/" \
    "T2_CH_CERN"     "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/" \
    "T2_HU_Budapest" "srm://grid143.kfki.hu:8446/srm/managerv2"          "SFN=/dpm/kfki.hu/home/cms/phedex/" \
    "T3_HU_Debrecen" "srm://grid143.kfki.hu:8446"                        "/dpm/kfki.hu/home/cms/phedex/" \
    "desy"           "srm://dcache-se-cms.desy.de:8443/srm/managerv2"    "SFN=/pnfs/desy.de/cms/tier2/" \
    "cern"           "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/" \
    "pixel"          "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/store/group/dpg_tracker_pixel/comm_pixel/" \
    "caf"            "srm://srm-eoscms.cern.ch:8443/srm/v2/server"       "SFN=/eos/cms/store/caf/user/$USERNAME/" \
    "kfki"           "srm://grid143.kfki.hu:8446/srm/managerv2"          "SFN=/dpm/kfki.hu/home/cms/phedex/store/user/$USERNAME/" \
    "deb"            "srm://grid143.kfki.hu:8446"                        "/dpm/kfki.hu/home/cms/phedex/" \
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
    endif
end

if ( $use_rfio == 1 ) then
    #alias se-ls        '/usr/bin/rfdir \!* | awk '\''{ print $NF }'\'
    #alias se-ls-l      '/usr/bin/rfdir \!* | awk '\''{ printf "%s %4d %4d %3d %12d %s %s %5s %s\n",$1,$2,$3,$4,$5,$6,$7,$8,$9 }'\'
    if ( $cmd =~ "cp"* || $cmd == "dl" || $cmd == "dl_mis" ) then
	set se_ls='lcg-ls -b -D srmv2 --vo cms'
    else
	set se_ls='/usr/bin/rfdir'
    endif
    set se_ls_l='/usr/bin/rfdir'
   #set se_cp='/usr/bin/rfcp' # rfcp can not copy from SE to an other SE
    set se_mv='/usr/bin/rfrename'
    set se_rm_r='/usr/bin/rfrm -r'
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
	set se_ls='lcg-ls -b -D srmv2 --vo cms'
	set se_ls_l='lcg-ls -b -D srmv2 --vo cms -l'
	set se_rm='lcg-del -b -D srmv2 --vo cms -l' # much faster than srmrm
	set se_rmdir='srmrmdir'
	set se_mv='srmmv'
	set se_mkdir='srmmkdir'
	set se_get_perm='srm-get-permissions'
	set se_chmod_664='srm-set-permissions -type=CHANGE -group=RW'
	set se_chmod_775='srm-set-permissions -type=CHANGE -group=RWX'
    endif
endif
set se_cp='lcg-cp -b -D srmv2 --vo cms'
set se_cp_v='lcg-cp -b -D srmv2 --vo cms -v'

#-------------------- Options ------------------------

alias hasopt 'echo "$script_opts" | grep \!* | wc -l'
if ( `hasopt "\-\-dry"` ) then
    alias echo_or_eval   'echo \!*'
    alias peek_or_source 'echo "> Add --run option or Run this script:\nsource "\!*"\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
    if ( `hasopt "\-\-par"` ) alias peek_or_source 'echo "> Add --run option or Run this script:\npar_source "\!*" $Npar\n\n> head -5 "\!*":"; head -5 \!*; if ( `cat \!* | wc -l` > 10 ) echo "...\n> tail -5 "\!*":"; if ( `cat \!* | wc -l` > 10 ) tail -5 \!*'
else if ( `hasopt "\-\-run"` ) then
    #eval workaround: do not want to interpret newline char for echo
    alias echo_or_eval   'echo \!* >! temp.csh; source temp.csh; rm temp.csh'
    alias peek_or_source 'source \!*; rm \!*'
    if ( `hasopt "\-\-par"` ) alias peek_or_source 'par_source \!* $Npar; rm \!*'
else
    # These are the default actions
    alias echo_or_eval   'echo \!* >! temp.csh; source temp.csh; rm temp.csh'
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
    echo "$se_cp $arg1 $arg2" >! cp.csh
    peek_or_source "cp.csh"

else if ( $cmd == "cp-v" ) then
    echo "$se_cp_v $arg1 $arg2" >! cp.csh
    peek_or_source "cp.csh"

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
    	echo "$se_rm_r $arg1" >! rm.csh
        peek_or_source "rm.csh"
    else
        ( eval "$se_ls_l $arg1" >! lsout.txt ) >& /dev/null
        set nout=`cat lsout.txt | wc -l`
        if ( $nout == 0 ) then
            echo "File/Directory does not exist"
        else
	    ( sed "s;/; ;g" lsout.txt | awk '{ print "'"$se_rm"' "$NF }' | sed "s;$se_rm ;$se_rm $arg1/;;s;\?;\\\?;" >! rm.csh ) >& /dev/null
            if ( $nout == 1 ) then
                if ( `cat lsout.txt | grep "^d" | wc -l` ) then
                    echo "$se_rmdir $arg1" >! rm.csh
                else 
                    set list_lastfile=`sed "s;/; ;g" lsout.txt | awk '{ print $NF }'`
                    set arg1_lastfile=`echo "$arg1" | sed "s;/; ;g" | awk '{ print $NF }'`
                    if ( $list_lastfile == "$arg1"_lastfile ) then
			echo "$se_rm $arg1" >! rm.csh
                    else 
			echo "$se_rmdir $arg1" >> rm.csh
                    endif
		    unset list_lastfile
		    unset arg1_lastfile
                endif
            else
                echo "$se_rmdir $arg1" >> rm.csh
            endif
            peek_or_source "rm.csh"
        endif
        rm lsout.txt
        unset nout
    endif

else if ( $cmd == "mv" ) then
    if ( $HOSTNAME =~ "lxplus"* ) then
	echo "Sorry, there are no commands to move SE files on lxplus"
	echo "Use srmmv on another computer!"
    else
	echo "$se_mv $arg1 $arg2" >! mv.csh
	peek_or_source "mv.csh"
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
    ( eval "$se_ls_l $arg1" >! lsout.txt ) >& /dev/null
    set nout=`cat lsout.txt | wc -l`
    if ( $nout == 0 ) then
	echo "File/Directory does not exist"
    else 
	( sed "s;/; ;g" lsout.txt | awk '{ print "'"$se_chmod_664"' "$NF }' | sed "s;$se_chmod_664 ;$se_chmod_664 $arg1/;;s;\?;\\\?;" >! set_perm.csh ) >& /dev/null
	if ( $nout == 1 ) then
	    if ( `cat lsout.txt | grep "^d" | wc -l` ) then
		echo "$se_chmod_775 $arg1" >! set_perm.csh
	    else
                set list_lastfile=`sed "s;/; ;g" lsout.txt | awk '{ print $NF }'`
                set arg1_lastfile=`echo "$arg1" | sed "s;/; ;g" | awk '{ print $NF }'`
                if ( $list_lastfile == "$arg1"_lastfile ) then
	            echo "$se_chmod_664 $arg1" >! rm.csh
                else 
	            echo "$se_chmod_775 $arg1" >> rm.csh
                endif
	        unset list_lastfile
	        unset arg1_lastfile
	    endif
	else
	    echo "$se_chmod_775 $arg1" >> set_perm.csh
	endif
	peek_or_source "set_perm.csh"
    endif
    rm lsout.txt
    unset nout

else if ( $cmd == "mis" ) then
    eval "$se_ls $arg1" | sed 's;_; ;g;s;\.root;;' | awk '{ print $NF }' | sort | uniq > jobnums.txt
    set N=1
    if ( $narg < 2 ) then
	echo "Need more arguments, Use:"
	echo "se mis <se_dir> Njobs"
    else
        while ( $N <= $arg2 )
            set n=`cat jobnums.txt | grep '^'$N'$'`
            if ( .$n == . ) then
                echo -n $N","
            endif
            set N = `expr $N + 1`
        end
        echo
        rm jobnums.txt
        unset N
    endif

else if ( $cmd == "dl" ) then # specify output directory
    if ( $narg == "1" ) set arg2="."
    eval "$se_ls $arg1" | sed "s;/; ;g" | awk '{ print "'"$se_cp"' ARG1/"$NF" '$arg2'/"$NF }' | sed "s;ARG1;$arg1;;s;?;\\?;" > ! dl.csh
    peek_or_source "dl.csh"

else if ( $cmd == "dl_mis" ) then
    if ( $narg < 2 ) then
	echo "Need more arguments, Use:"
	echo "se dl_mis <se_dir> <local_dir>"
    else
	eval "$se_ls $arg1" >! lsout.txt;
	sed "s;/; ;g" lsout.txt | awk '{ print "'"$se_cp_v"' ARG1/"$NF" '$arg2'/"$NF }' | sed "s;ARG1;$arg1;;s;?;\\?;" >! dl_temp.csh
	sed "s;_[0-9]*_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]\.root;\.root;;s;\.root;;;s;_; ;g" lsout.txt | awk '{ printf "%d\n",$NF }' >! jobnums_se.txt
	rm lsout.txt
	ls -l $arg2 | grep "\.root" | awk '{ print $5,$NF }' | grep -v "^0" | sed "s;_[0-9]*_[a-zA-Z0-9][a-zA-Z0-9][a-zA-Z0-9]\.root;\.root;;s;\.root;;;s;_; ;g" | awk '{ printf "%d\n",$NF }' > ! jobnums_dled.txt
	if ( -f dl_mis.csh ) mv dl_mis.csh dl_mis_old.csh
	foreach jobnum ( `cat jobnums_se.txt` )
	    if ( ! `grep '^'$jobnum'$' jobnums_dled.txt | wc -l` ) then
		# old crab format
		#grep "_"$jobnum"_[0-9]_[0-9a-zA-Z][0-9a-zA-Z][0-9a-zA-Z]\.root" dl_temp.csh >>! dl_mis.csh
		# This is for TSBatch output format
		#grep "_"`printf "%04d" $jobnum`"\.root" dl_temp.csh >>! dl_mis.csh
		# crab3 format
		grep "_"`printf "%d" $jobnum`"\.root" dl_temp.csh >>! dl_mis.csh
	    endif
	end
	rm jobnums_se.txt jobnums_dled.txt dl_temp.csh
	if ( ! -e dl_mis.csh ) then
	    echo "All files are downloaded already"
	else
	    peek_or_source "dl_mis.csh"
	endif
    endif

else
    echo "Unknown command"

endif


