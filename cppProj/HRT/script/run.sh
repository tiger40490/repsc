cd "$( dirname "${BASH_SOURCE[0]}" )"/..
# now we are in the parent dir of run.sh
set -e
make 
./feed
rm *.o *.a 
ls -l
