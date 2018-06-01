#!/usr/bin/env bash
arg1=${1:-glg} # default arg
case $arg1 in
  pspt )
    fixFile=/v/global/user/b/bi/bint/capture/fromPassport ;
    host=nyswapsqa1 ;
    port=mvea ;
    cport=$port ;;
  glg )
    fixFile=/v/global/user/b/bi/bint/capture/glg ;
    host=nyswapsqa3 ;
    port=mvea5 ;
    cport=mvea_app5 ;;
  * )
    echo Unknown instanceSelector ;
    # return ; won't compile
    exit 28910 ;;
esac

rand=$(($RANDOM%90+10)) # 2-digit
perl -pi.orig -e "s/P555\\d+/P555$rand/g" $fixFile.tmpl diff $fixFile.tmpl $fixFile.tmpl.orig # 1>&2

perl -pe 's/;\s*/;/g' $fixFile.tmpl > $fixFile orderId=` perl -pe 's/.*;11=(.*?);.*/$1/' $fixFile ` echo ls -l $fixFile set -x
FixShell1 -d ';' -f $fixFile -a $host:$cport -s BINT -m Connect -A # 1>&2 zappit $host grep --color=always $orderId /var/hostlinks/$host/znyswp/$port/Daily/$port.log
{ set +x; } 2>/dev/null
printf "______________________________\n\n"
set -x

zappit $host less +/$orderId /var/hostlinks/$host/znyswp/$port/Daily/$port.log
