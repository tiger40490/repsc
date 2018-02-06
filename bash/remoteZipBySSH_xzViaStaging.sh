date=0804
if [ $# -ge 1 ]; then
  date=$1
fi

ch=1
if [ $# -eq 2 ]; then
  ch=$2
fi

tgz=nx$date.tgz

set -x
ssh -q uidev1 ssh -q bxbrdr2 "tar cfvz $tgz /data/mnt/captures/tp1/lfeeds/nyseamerican/american-integrated$ch-primary.2017${date}_*"
ssh -q uidev1 ssh -q bxbrdr2 "hostname; ls -l ~"
ssh -q uidev1 scp -pq bxbrdr2:$tgz .
set +x
echo '------------------'
ssh -q uidev1 "hostname; ls -l ~/$tgz"
# now download to localhost
echo '------------------'
pushd ~/captured/nx/
scp -pq uidev1:$tgz .
chmod a-w $tgz
hostname
ls -l $(pwd)/$tgz
mkdir $date
tar xf $tgz -C $date --strip-components 6
popd
