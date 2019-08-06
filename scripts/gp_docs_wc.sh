#!/bin/bash

# A script to count the number of words in GenPipes documentation

display_usage() {
   echo "****************************************"
   echo ""
   echo "Usage:"
   echo "./gp_docs_wc.sh [options]"
   echo ""
   echo "-h display runtime command and options"
   echo "--help display detailed help message"
   echo ""
   echo "****************************************"
}

if [[ $1 = "--help" ]];
then
   echo ""
   echo "Script gp_docs_wc"
   echo ""
   echo "Displays the total number of words in rst text source files."
   echo "This lets you know current GenPipes documentation content size."
   echo ""
   display_usage 
   exit
elif [[ $1 = "-h" ]];
then
   display_usage
   exit
elif [[ $1 = "" ]];
then
  j=0;k=0;for i in `find . -type f -name *.rst`; do k=`cat $i | wc -w`;j=`expr $j + $k`;done;echo "Total number of words in GenPipes documenation is $j"
  exit
else
  display_usage
fi;
