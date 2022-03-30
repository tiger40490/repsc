#!/bin/bash
# passing shell var into perl is fairly common, but I don't want to over-spend on this experiment

shVar=/apps/qa
export |grep shVar #nothing

# I think the single-quote around $shVar is essential
echo '/abc/apps/qa/xyz' | perl -ne "print '$shVar __ ' . \$1  if m|$shVar/(\w*)\b| "

printf "\n^^^^ above is double-quoted perl command; below is single-quoted vvvv \n"

perl -e 'print $shVar'

printf "\n----\n"

echo '/abc/apps/qa/xyz' | perl -ne 'print $shVar. " __ " . $1 if m|$shVar/(\w*)\b| '
# I think $shVar is Not passed to the perl process due to single-quote around perl command
