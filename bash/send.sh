<< ______________end_of_comment_1________________
todo: print reusable command to query out.VTA
todo: print reusable script to remote tail the messages.log

To prepare a multiline msg file:
perl -pe 's/:/\n/g' cmf_msg.txt

Note *.m.cmf often has a trailing new line

Usage:
cd /L/infra/qa/vtan2/gateway/dat/
prepare the input files
this.sh instusalgo1 # reads INSTUSALGO1.m.cmf and appends t to in.VTA
this.sh INSTUSALGO1.m.cmf # ditto .. characters after dot are removed

todo:
lg2: cd to /L/infra/qa/vtan2/gateway/dat/, then popd

______________end_of_comment_1________________

adn=` echo $1 | perl -pe ' s/\..*//; $_=uc ' `
[[ -z "$adn" ]] && adn=$aDn
echo adn is $adn

rand=$((4000 + $RANDOM%1000)) # random 4-digit number between 4000 and 4999
[[ -z "$2" ]] || perl -pi -e "s/^qid=.*/qid=$2/m" $adn.m.cmf
[[ -z "$3" ]] || perl -pi -e   "s/^lp=.*/lp=$3/m" $adn.m.cmf
perl -pe "s/^#.*$//; s/^id=\S*/id=VTA40490.$rand/" $adn.m.cmf > $adn.1.cmf
perl -pi -e 's/\s*#.*//' $adn.1.cmf # remove trailing comments
perl -pi -e 's/ +$//m' $adn.1.cmf # remove trailing spaces
perl -pi -e 's/^\s+$//m' $adn.1.cmf # remove empty lines
perl -pi -e 's/\n+/:/' $adn.1.cmf
###perl -pi -e 's/^:+//' $adn.1.cmf # remove leading colon
[[ -s $adn.1.cmf ]] || exit # file empty
echo >> $adn.1.cmf # append a newline

printf 'Now sending new order --> '
cat $adn.1.cmf  |grep --color 40490.$rand
#exit # early exit for testing
wc -l in.VTA
cat $adn.1.cmf >> in.VTA  ## send new order

if [ -d / ] ; then # replace or cxl
  xr='r' # flag value should be x or r
  perl -pi.NOS -e "s/:mt=o:/:mt=$xr:/; s/:id=/:to=/; s/:$/:id=VTA40490.$rand.$xr:/" $adn.1.cmf
  #perl -pi -e     "s/ac=.+?:/ac=diffffffffff:/" $adn.1.cmf # diff replacement value
  perl -pi -e     "s/algp\.darkOnly=.:/algp.darkOnly=1:/" $adn.1.cmf # diff replacement value
# perl -pi -e     "s/algp\.ddarkOnly=.:/algp.darkOnly=1:/" $adn.1.cmf # introduce the darkOnly field, by converting from rubbish
#  perl -pi -e     "s/algp\.darkOnly=.://" $adn.1.cmf # remove a field
  git --no-pager diff --no-index $adn.1.cmf.NOS   $adn.1.cmf
  printf "Will Send a  ... $xr ...  after sleep "
  cat $adn.1.cmf  |grep --color 40490.$rand
  #exit
  #sleep 2
  cat $adn.1.cmf >> in.VTA
fi

wc -l in.VTA
printf "dumping out.VTA lines usually starting with A|E|C|O|..\n"
printf "tail  -99  out.VTA |egrep --color '40490.$rand:' | m \n"
sleep 1
        tail  -99  out.VTA |egrep --color "40490.$rand:"

# not ideal but works. Let's focus on high-leverage GTD
set -x
echo $adn | lookupAdn.pl 2>/dev/null
host=$( echo $adn | lookupAdn.pl 2>/dev/null)
set +x
#host=qxsrfpqa050
printf "$adn is on $host according to /L/infra/apps/qa/mi/scripts/go . Now tailing adapter log..(Break ..) \n"

adapterLog=$( ssh -q $host "ls -t /L/infra/apps/qa/mi/epa/$adn/log/C*.$adn.messages.log " | head -1 )

set -x
  ssh -q $host "tail --lines=11    $adapterLog" >  /tmp/victan_$adn.log
# ssh -q $host "tail --lines=11 -f $adapterLog" >  /tmp/victan_$adn.log
cleanFix.pl /tmp/victan_$adn.log | egrep --color "40490.$rand| 8158="
set +x
echo "   cleanFix.pl /tmp/victan_$adn.log | less  +/40490.$rand | m "
