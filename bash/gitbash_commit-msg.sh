#!/usr/bin/bash
# This is the master version, whereas .git/hooks/commit-msg is the live version.
# This file is supposed to be usable as is on all my hosts.
# Priorities are reliability, simplicity, minimum dependency (no python/perl please)
# showcase printf
# showcase string match
# showcase compound if-block
# showcase bash string regex.. No quote please.

hn=`hostname`
[[ $hn == 'LAPTOP-3U2UKQPB' ]] && prefix='hp '
[[ $hn == 'acer299' ]] && prefix='299' #Acer$299 
[[ $hn == 'DSIOTE10077' ]]     && prefix='mlp'
# prefix should be space-saving, fairly unique
orig=`cat $1`

#below uses non-regex
[[ $orig == "$prefix"* ]] && {
 printf "vvv-- commit-msg --> q[$prefix] is already a prefix in the user-supplied commit msg\n" >&2
 exit 0
} 
[[ $orig =~ ^new$|^minor$|^major$|^inter$ ]] && {
  suffix="_$RANDOM"
  # printf "suffix = $suffix\n" >&2
}
printf "$prefix $orig$suffix" > $1
