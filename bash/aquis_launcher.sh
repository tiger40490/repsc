# Purpose: This handy test driver script saves time when you need to launch parser
# (+ supporting jobs) 20 times in an hour.  It will launch a playback
# test. Prior to that it cleans up everything. After the test, to stop all processes, just
# hit Ctrl-C.
#
# Tip: Better source this script. One known benefit -- "jobs"  command would now work
# Tip: Ctrl-C to kill first 6 background jobs
#
# unset  NO_COMPLIE   # run normal make as part of this script
# export NO_COMPLIE=0 # ditto
# export NO_COMPLIE=1 # run make as part of this script but skip dependencies
# export NO_COMPLIE=2 # skip make
# showcase signal trap
# showcase prompting user to confirm

sigtrap(){
  echo Interrupted
  kill %1 %2 %3 %4 %5 %6 %7 %8  2>/dev/null
  $baseR/bin/aquis_rebus.sh -T stop # -T to use test.cfg
  trap - INT
  trap # show active signal traps
  sleep 1
  jobs -l
  ps4
}

[[ $(hostname) == "rtdevfrh"* ]] && isUK=1
[[ -z $isUK ]] && printf "not in UK; "
[[ -n $isUK ]] && printf "in UK; "
#base=~/release/tp/plugins/xtap/aquis
    base=~/repo/tp/plugins/xtap/aquis
llvl=5 #default
[[ -f $base/etc/local_driver.cfg ]] && source $base/etc/local_driver.cfg
printf "NO_COMPILE= $NO_COMPILE ; parser loglvl set to $llvl \n"

if alias ps4 2>/dev/null >/dev/null ; then
  ps4
else
  ps auxwww|grep --color -P '(s2o|c2o|f2s|f2c|pbflow|rebus|xtap|nysemkt_integrated_parser[1-8]) '
fi

echo "jobs:"
jobs -l
printf "\nContinue? [ y /any_other_key to quit] "
unset REPLY; read $REPLY
[ "$REPLY" = "y" ] || return
unset REPLY

/bin/rm ~/aq/working/AQUIS1Parser_StaticDataMap.dat
/bin/cp ~/aq/working/security-20170906.csvv ~/aq/working/security-20170906.csv

logbase=/tmp/vtan
dirs -c
pushd $base
if [ $NO_COMPILE -lt 2 ] && [[ -z $isUK ]] ; then
  make NO_NETWORK=1 || return # much faster by returning
fi
echo '--------------------'
popd

trap "sigtrap" INT

# tcp echo server tends to mess up the parser
#$base/src/tcpEchoServer.py 40493 > $logbase/fakeReplayServer_$LOGNAME.txt.log 2>&1 &

c2o localhost 40494| decript2 ctf > $logbase/rtsd_aq_$LOGNAME.txt.log 2>$logbase/stderrS.log &

#capture parser server-output .... without affecting rebus, used to be on port 10337
c2o localhost 40497 |tee $logbase/2rebus_captured_$LOGNAME.bin.log | decript2 ctf > $logbase/2rebus_captured_aq_$LOGNAME.txt.log 2>$logbase/stderrR.log &

baseR=~/repo/tp/rebus/aquis
s2o 40483 > $logbase/rebus_output_$LOGNAME.log 2>&1 &

########### start rebus one way or another
        ### fake safemux client
        #c2o localhost 27660 |tee $logbase/fakeRebus_$LOGNAME.bin.log |decript2 ctf > $logbase/fakeRebus_aq_$LOGNAME.txt.log 2>&1 &
        ### fake rebus server
        #s2o 27660 |tee $logbase/fakeRebus_$LOGNAME.bin.log |decript2 ctf > $logbase/fakeRebus_aq_$LOGNAME.txt.log 2>&1 &
        ### run local rebus || from /var/opt
$baseR/bin/aquis_rebus -D 1 $baseR/etc/test.cfg > $logbase/rebus_$LOGNAME.log 2>&1 &
        ### use rebus start script
        #$baseR/bin/aquis_rebus.sh -T start # -T to use test.cfg

########### now start parser one way or another:
        ### run a local debug build: # may need to set NO_COMPILE TO 2
        #$base/shared/tp_xtap/bin/xtap_d -D $llvl -c $base/etc/test_debug.cfg > $logbase/xtap_$LOGNAME.log 2>&1 &
        ### run from /var/opt
        #$varaq/bin/aquis1_parser -D $llvl -c $varaq/etc/test_replay.cfg > $logbase/xtap_$LOGNAME.log 2>&1 &

        ### run a local build:
if [ -z $isUK ]; then
        #massifOut=/home/vtan/aq/massif.out; valgrind --tool=massif --pages-as-heap=yes --time-unit=B --massif-out-file=$massifOut
        $base/shared/tp_xtap/bin/xtap -D $llvl -c $base/etc/test_replay.cfg > $logbase/xtap_$LOGNAME.log 2>&1 &
        #ms_print $massifOut |m
else
  [[ -f $base/etc/.1 ]] && $base/shared/tp_xtap/bin/xtap -D $llvl -c $base/etc/test_replay.cfg.real1 > $logbase/aq1_xtap_$LOGNAME.log 2>&1 &
  [[ -f $base/etc/.2 ]] && $base/shared/tp_xtap/bin/xtap -D $llvl -c $base/etc/test_replay.cfg.real2 > $logbase/aq2_xtap_$LOGNAME.log 2>&1 &
  [[ -f $base/etc/.3 ]] && $base/shared/tp_xtap/bin/xtap -D $llvl -c $base/etc/test_replay.cfg.real3 > $logbase/aq3_xtap_$LOGNAME.log 2>&1 &
  [[ -f $base/etc/.4 ]] && $base/shared/tp_xtap/bin/xtap -D $llvl -c $base/etc/test_replay.cfg.real4 > $logbase/aq4_xtap_$LOGNAME.log 2>&1 &
fi

sleep 2 # wait for parser to initialize
ls -lt $logbase
#echo -en "\n\n\nDebugger ready? Start pbflow? [any_other_key/ n ] "; read $REPLY; [ "$REPLY" != "n" ] || return

pb -R 98765 /home/vtan/captured/aq/AQUIS_A-F-mcast.shraw | sendmc -i localhost 224.0.0.7:49260:104 2>/dev/null
pb -R 98765 /home/vtan/captured/aq/AQUIS_A-F-mcast.shraw | sendmc -i localhost 224.0.0.7:49260:105 2>/dev/null
pb -R 98765 /home/vtan/captured/aq/AQUIS_A-F-mcast.shraw | sendmc -i localhost 224.0.0.7:49260:106 2>/dev/null
pb -R 98765 /home/vtan/captured/aq/AQUIS_A-F-mcast.shraw | sendmc -i localhost 224.0.0.7:49260:107 2>/dev/null
#pb -R 98765 /home/vtan/captured/aq/AQUIS_A-F-mcast.shraw | sendmc -i localhost 224.0.0.8:49260:104 2>/dev/null &
if [ -z $isUK ]; then
  ### ------ either play some QA msg files ....
  #datafileMC=~/captured/aq/jhe/* # can wipe out 2rebus_capture ?! Need to use fakeRebus to see any CTF output

  ### ------ or play the multicast data ....
  #datafileMC=~/captured/aq/10G_A-Feed_MC_224.0.121.96.capture
  # 99M has no worse data loss than 99k
  #ls $datafileMC && f2m -n1 -r99M 224.0.0.7 49260 $datafileMC &

  ### ------ or play the tcp replay files, by f2s:
  #datafile=~/captured/aq/20170821.mdstreamXET1Gb
  #datafile=~/captured/aq/20170821.mdstreamLSE1Gb
  datafile=~/captured/aq/20170821.mdstreamENXT1Gb
  #datafile=~/captured/aq/20170821.mdstreamOthers1Gb
  #datafile=~/captured/aq/AquisAddOrder.msg #-r200 works
  # -r2999K could sometimes lead to data loss since rebus may not be fast enough
  #ls -l $datafile && f2c -n1 -r99K localhost 40495 $datafile &
fi

jobs -l; sleep 3 ; less -N $logbase/xtap_$LOGNAME.log # let the user read 'jobs' before tailing

#echo $base/scripts/test1afterBatch.sh
#sleep 1 # give parser time to process more messages
#$base/scripts/test1afterBatch.sh || echo "Sanity check didn't pass :("
