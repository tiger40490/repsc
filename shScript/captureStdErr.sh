# This script has two modes:
## normal mode outputs everything in console
## if we call orderId=$(thisScript.sh  2>/dev/null) then only the orderId is captured :)

RAND=$(($RANDOM%90+10)) # 2-digit random number probably 10-99

## note the double backslash
perl -pi.orig -e "s/P555\\d+/P555$RAND/g" $fixFile.tmpl

diff $fixFile.tmpl $fixFile.tmpl.orig 1>&2

perl -pe 's/;\s*/;/g' $fixFile.tmpl > $fixFile

perl -pe 's/.*11=(.*?);.*/$1/' $fixFile #1>&2

## ... use the $fixFile
