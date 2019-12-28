# bash this.script.sh

cd /c/0/landGrab
pwd

i=1
for f in *.dat; do
  mv -v "$f" "2000MB_diskHogMade]cpp$i.dat"
  let "i=i+1"
done
