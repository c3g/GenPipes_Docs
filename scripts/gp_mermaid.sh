#!/bin/bash

# Converts mmd input files in source/mmd folder into png

display_usage() {
   echo "****************************************"
   echo ""
   echo "Usage:"
   echo "./gp_mermaid.sh"
   echo ""
   echo "****************************************"
}

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
MMDCLI="/usr/local/bin/mmdc"
if [[ $# -gt 0 ]];
then
   echo ""
   echo "Does not accept any input arguments."
   echo ""
   display_usage 
   exit
else
    echo "here1"
    for i in `find $SCRIPTDIR/../docs/source/mmd/pipelines/ -type f -name *.mmd`; do echo ${i}; $MMDCLI -i $i -o $i.png -b transparent; done
    echo "here2"
    mv $SCRIPTDIR/../docs/source/mmd/pipelines/*.mmd.png $SCRIPTDIR/../docs/source/img/pipelines/mmd/.
fi;
