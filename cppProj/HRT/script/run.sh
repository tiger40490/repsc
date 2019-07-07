cd "$( dirname "${BASH_SOURCE[0]}" )"/..
# now we are in the parent dir of run.sh

set -e
make 
ls -l ./feed
./feed
make clean 

printf 'v v   untracked files   v v\n'
git clean -n
