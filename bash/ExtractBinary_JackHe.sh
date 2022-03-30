#!/bin/bash
<< ______________end_of_comment_1________________
Usage: this_script 44 x2cx00
Usage: this_script 44 \\x2c\\x00 # original usage
Usage: this_script 44 \x2c\x00   # also works
Usage: this_script 44 '\x2c\x00' # single or double quote

______________end_of_comment_1________________
#######         command args processing   ##########

###     1) sizeMsg
sizeMsg=$1
###     2) needle
needle=$( echo $2|perl -pe '      s|\\||g; s|x|\\x|g    '  )
###     3)
filePattern="20170821.mdstreamL*"
filePattern="american-integrated1-primary.*"
filePattern="$3"

#######         command args done         ##########

sizeHdr=16 # for nysemkt integrated feed
#sizeHdr=1  # for Aquis
outputfile=MsgType_outputfile
whichNeedle=3 # 1st, 2nd, 3rd ... if there are enough matches on 1st matched line

for datafile in   $(find . -name "$filePattern"); do
  printf "\nUsing 'find' to check $datafile ...\n"
  #extraGrepOps="-U" # -U seems to be a Windows feature
  #max-count stops after finding one matching line, though that line may match many times. head -N further filters out all but N matches
  set -x
  offset=` grep $extraGrepOps --perl-regexp --text --byte-offset --only-matching --max-count $whichNeedle  "$needle" $datafile |head -$whichNeedle|tail -1|cut -d':' -f1 `
  set +x
  [[ -n "$offset" ]] && break
done

if [ -n "$offset" ]; then
  echo '... found :)'
  if [ $sizeMsg -gt 0 ]; then
    finaloffset=$(($offset-$sizeHdr))
    finallength=$(($sizeHdr+$sizeMsg))
    set -x
    `dd   if=$datafile  of=$outputfile  bs=1  skip=$finaloffset  count=$finallength`
  fi
else
  printf "\nToo bad needle  %s  not located in any file like  $filePattern  \n" $needle
fi
