<< ______________end_of_comment_1________________
perl -pe 's/:/\n/g' cmf_msg.txt

Note *.m.cmf often has a trailing new line

Usage:
this.sh instusalgo1 # reads INSTUSALGO1.txt, and appends t to in.VTA
______________end_of_comment_1________________

adn=`echo $1 | perl -pe '$_=uc' `
echo adn is $adn

rand=$((4000 + $RANDOM%1000)) # random 4-digit number between 4000 and 4999
perl -pe "s/^#.*$//; s/^id=\S*/id=VTA40490.$rand/" $adn.m.cmf | perl -pe 's/\n/:/' |perl -pe 's/::+/:/g' > $adn.1.cmf
perl -pi -e 's/^:+//' $adn.1.cmf # remove leading colon
echo >> $adn.1.cmf

wc -l out.VTA
printf 'Now sending CMF '
cat $adn.1.cmf  |grep --color 40490.$rand
# exit
wc -l in.VTA
cat $adn.1.cmf >> in.VTA  ## send order
wc -l in.VTA
tail -f out.VTA |grep --color 40490.$rand &
wc -l out.VTA

# not ideal but works. Let's focus on high-leverage GTD
adapterLog=$( ssh -q qxsrfpqa002 "ls -t /export/home/L/infra/apps/qa/mi/epa/$adn/log/C*.$adn.messages.log " | head -1 )
ssh -q qxsrfpqa002 "tail --lines=11 -f $adapterLog" | tee /tmp/victan_$adn.log

set -x
exec clean.pl /tmp/victan_$adn.log | egrep --color "40490.$rand|"
