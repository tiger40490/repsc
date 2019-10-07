# to be sourced in .bashrc
# proven since 2010 mostly on linux but now need to test more on git-bash, then upload to github
# usage: exa -t ss ~/.ssh
# usage? exa /usr/bin # same as exa bin /usr/bin
# usage: exa aa # same as exa aa `pwd`
# showcase eval
# showcase == on integer, using string equality test
# showcase string length

exa(){
  local ops
  while is_opt=`echo $1 |perl -ne 'print if /^-/'  ` && [ "$is_opt" ]; do
    ops="$ops $1"; shift
  done
  [ $# == "0" ] && return

  if [ $# == "1" ]; then
    if [ ${#1} -ge 5 ]; then
      fullpath=$1
      shortname=`echo $1|perl -pe 's|/$||;s|^.*/||'   `
    elif [ ${#1} -le 2 ]; then
      fullpath=`pwd`
      shortname=$1
      printf "creating shortname $1 for pwd\n"
    fi
  else
    fullpath=$2
    shortname=$1
  fi

  [ -x $fullpath ] || return # error msg? no need .. KISS
  eval $shortname="$fullpath" # create a shell variable with a dynamic name!
  printf "$shortname \t now set to $fullpath \n"
  prj="$fullpath"
  alias  "$shortname"="cd $fullpath;ls1page $ops"
  alias  prj=$shortname # USE MORE
}
