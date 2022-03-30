#### a useful yet simple bash function 
# showcase: boolean variable assign and check. This function can be simplified to get rid of the boolean variable.

add_path(){
  dir=`echo $1|perl -pe 's|/$||'`
  [ -r $dir ] || return
  echo $PATH|grep -P "$dir(:|$)" > /dev/null && return 0

  #todo: check world write perm, esp for root
  isPre=false #this is a demo of a reusable feature, not really needed here
  [[ "$2" = "-p" ]] && isPre=true && echo Prepending $dir to PATH
  if $isPre; then
    PATH=$dir:$PATH
  else
    PATH=$PATH:$dir
  fi
  cnt=$(echo $PATH |perl -pe 's/:/\n/g' | wc -l)
  #echo adding $dir to PATH and returning $ret
  return $cnt
}
