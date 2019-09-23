#!/bin/sh
hn=`hostname`
[[ $hn == 'LAPTOP-3U2UKQPB' ]] && prefix='hp '
[[ $hn == 'MAXIMUSIII' ]]      && prefix='116'
# prefix should be space-saving, fairly unique
orig=`cat $1`
printf "$prefix $orig" > $1

