#### a simple bash function showing many reusable features
# showcase: repeating a command N times or until successful, showing (set -x) the commands in first iteration only
# showcase: count number of matching filenames, saving the number in a shell variable
# showcase: using string test on integers
# showcase: overwrite if-newer and with prompt
# showcase: capitalize a string
# the perl one-liner is currently buggy !

rerun(){ 
  adn=${1^^}
  derivation='from $1'
  base=/xxxxxxxx
  if [[ -z "$adn" ]] ; then
   adn=` pwd | perl -ne "print \"$1\" if m|$base/(\w*)\b| " `
   derivation='from pwd'
  fi
  if [[ -z "$adn" ]] ; then
   adn=$aDn
   derivation='from aDn'
  fi
  echo using adn $derivation .. $adn
  #sleep 3 # let me check
  [[ -z "$adn" ]] && return
  count=` ls $jarout/epa_$bk2-*-SNAPSHOT.victan.jar | wc -l `
  if [ "$count" != "1"  ]; then  
    echo multiple matching jars found
    return
  fi
  set -e
  /bin/cp -iuv $jarout/epa_$bk2-*-SNAPSHOT.victan.jar   $base/$adn/lib/
  set +ex
  sleep 1
  stop $adn
  echo y | run $adn # run() function/script expects a keyboard input

  ## now watch log
  date
  adapterLog=$base/$adn/log/qa$adn-out.log
  for i in {1..44}; do
    [[ $i -eq "1" ]] && set -x # verbose for first try
    grep "Session manager created" $adapterLog && break
    sleep 1
    { set +x; } 2>/dev/null
    printf "\e[0K\r   repeating # $i ..  "
  done
  echo

  # now some milestones:
  set -x
  grep epa.QuickFixEventHandler $adapterLog
  { set +x; } 2>/dev/null
}
