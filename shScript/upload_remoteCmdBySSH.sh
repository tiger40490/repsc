# demo for interactive command run remotely
# demo for switch-case

checksum=1; [[ $# > 1 ]] && checksum=$2
case $1 in
  nactf )
        destination=namd ;
        pushd ~/repo/tp/rebus/nactf/ ;
        fileList=$(echo nactf_rebus-*.rpm) ;
        checksum=1 ;; # explicitly ignore command line input
  *parser* )
        destination=naeq/stock/ ;
        pushd ~/release/tp/plugins/xtap/nysemkt_integrated_parser/ ;
        fileList=$(echo nysemkt_integrated_parser-*.rpm) ;;
esac

[[ $(echo $fileList|wc -w) -ne $checksum ]] && echo "Wrong rpm count... Expecting $checksum" && exit

set -x
scp -p $fileList   uibxb1:/home/admindb/release/new/$destination
ssh -q uibxb1 -t "ls -l /home/admindb/release/new/$destination"
