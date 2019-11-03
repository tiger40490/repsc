#!/usr/bin/bash
# This is the master version, whereas .git/hooks/commit-msg is the live version.
# This file is supposed to be usable as is on all my hosts.
# Priorities are reliability, simplicity, minimum dependency (no python/perl please)
# showcase printf
# showcase string match
# showcase compound if-block

hn=`hostname`
[[ $hn == 'LAPTOP-3U2UKQPB' ]] && prefix='hp '
[[ $hn == 'MAXIMUSIII' ]]      && prefix='116'
# prefix should be space-saving, fairly unique
orig=`cat $1`
[[ $orig == "$prefix"* ]] && {
 echo Warning from $0: q[$prefix] is already a prefix in the user-supplied commit msg >&2
 exit 0
} 
printf "$prefix $orig" > $1
