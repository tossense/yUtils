#!/bin/bash

function errexit(){
    echo "error: $@" >&2
    exit 1
}

checkday() {
	[[ ${#1} -eq 8 ]] || errexit "illegal date $1"
	[[ ${#2} -eq 8 ]] || errexit "illegal date $2"
	ts=`date +%s -d $1 2>/dev/null`
	if [ ${#ts} -eq 0 ]; then
		errexit "illegal begin date $1"
	fi
	ts=`date +%s -d $2 2>/dev/null`
	if [ ${#ts} -eq 0 ]; then
		errexit "illegal end date $2"
	fi
}

if [ $# -eq 2 ]; then
        bd=$1; ed=$2;
		checkday $bd $ed
		[[ $bd -gt $ed ]] && errexit "$bd later than $ed"
		
		until [ $bd -gt $ed ]; do
			echo $bd
			bd=`date -d "$bd 1days" +%Y%m%d`
		done
else
        errexit "yseqdate.sh [begdate] [enddate]"
fi
