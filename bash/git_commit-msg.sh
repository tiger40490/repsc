#!/bin/sh
# This is the master version, whereas .git/hooks/commit-msg is the live version.
# This file is supposed to be usable as is on all my hosts.
# Priorities are reliability, simplicity, minimum dependency (no python/perl please)

hn=`hostname`
[[ $hn == 'LAPTOP-3U2UKQPB' ]] && prefix='hp '
[[ $hn == 'MAXIMUSIII' ]]      && prefix='116'
# prefix should be space-saving, fairly unique
orig=`cat $1`
[[ $orig == "$hn"* ]] && {
 echo $hn is already a prefix >&2
 exit 0 
} 
printf "$prefix $orig" > $1
