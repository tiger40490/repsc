# showcase set -o pipefail
# showcase $SECONDS, 2-digit $RANDOM number
# showcase positive and negative prompt for user confirmation
#!/bin/env bash

dirname "${BASH_SOURCE[0]}"
echo .. above dirname is often a relative path

fullpath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo fullpath is $fullpath # fairly reliable one-liner,

source $fullpath/RajBuild.env # definitions of config-variables

if [[ $extraFlags = *"V=1"* ]]; then
  echo will use gmake V=1 to capture g++ commands.. to be run from trunk/build/
else
  extraFlags="$extraFlags --silent"
fi
echo will use gmake $extraFlags

shadow=/v/campus/vi/cs/ets/bint/ets.SysNameFlow.$whichShadow
build=$shadow/ets/SysNameFlow/trunk/build$whichShadow

if [ -d $build ]; then
  printf "will use existing build dir $build\n"
else
  printf "creating build dir ... " # don't print trailing newline!
  set -ex
  mkdir $build
  { set +x; } 2>/dev/null
fi

SECONDS=0 # timing
set -e # if command fails, then we are probably in the wrong host
pushd /d/d1/shared/bint/ets.SysNameFlow.$whichShadow/ets/SysNameFlow/trunk/src/
set +e

set -x
if [ -f / ] ; then ## -d always true; -f always false
     # deleting artefacts from last build
     /bin/rm -rf -v $build/*   # a thorough clean-up
     # below command may not be needed after the rm
     premake --solution=common/etsSysNameFlow.lua --ccid=gcc34_64 --id_target=rhel4 --location=$build clean
fi
time premake --solution=common/etsSysNameFlow.lua --ccid=gcc34_64 --id_target=rhel4 --location=$build gmake
{ set +x; } 2>/dev/null
echo `date` ========= $SECONDS seconds taken by last two commands i.e. premake =========

SECONDS=0 # reset elapse timer for next command
set -ex
set -o pipefail # needed
gmake $extraFlags -j 32 -C $build config=debug | tee ./build.log
{ set +x; } 2>/dev/null
set +e
echo `date` ========= $SECONDS seconds taken by last command i.e. build =========

RAND=$(($RANDOM%90+10)) # 2-digit
mkdir /var/tmp/bint/install_$RAND
mv -v $shadow/ets/SysNameFlow/trunk/install/.exec/x86_64.linux.2.6.glibc.2.3/bin/SysName* /var/tmp/bint/install_$RAND/

set -x
gmake $extraFlags -j 32 -C $build MS_PREFIX=$shadow MS_RELEASE=trunk install | tee ./install.log
{ set +x; } 2>/dev/null
echo `date` ========= install completed... now checking unit tests ... =========
popd

utest=$shadow/ets/SysNameFlow/trunk/install/.exec/x86_64.linux.2.6.glibc.2.3/bin/SysName_unittest-g
ls -l $utest
[[ -n "$isUtestNeeded" ]] && $utest


[[ -n "$isSendingOrder" ]] || exit
echo -en "\n\n\nSysName restarted? Run FixShell1 and grep log? [ n / any_other_key_for_yes ] ";
read $REPLY;
[ "$REPLY" = "n" ] && exit

fsh.sh
