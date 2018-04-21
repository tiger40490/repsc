if [ $(whoami) != "rpmadmin" ] ; then
  set -x
  exec su rpmadmin $0 # run the same script under target su user
fi

# now the user id is "correct"
