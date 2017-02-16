#!/bin/bash
DIR=$1
CERT=$2
MINRUN=$3
MAXRUN=$4

# Convert JSON file to the list of all lumisections (all_lumis.txt)
curl $CERT > Cert.txt 2>/dev/null
source json_to_list.sh Cert.txt | awk '{ if ( $1 >= '$MINRUN' && $1 <= '$MAXRUN' ) print $1" "$2 }' | sort -V > all_lumis.txt

# Make a list of processed lumisections (lumis.txt) from the output root files in DIR
root -l 'print_lumis.C("'"$DIR/*.root"'")' | grep "RUN/LS" | awk '{ print $2" "$3 }' | sort -V > processed_lumis.txt

# Diff them to create a list of missing lumisections
diff processed_lumis.txt all_lumis.txt | grep "^>" | awk '{ print $2" "$3 }' > missing_lumis.txt

# Convert list to the JSON format
source list_to_json.sh missing_lumis.txt

# Remove temp files
rm processed_lumis.txt Cert.txt all_lumis.txt missing_lumis.txt
