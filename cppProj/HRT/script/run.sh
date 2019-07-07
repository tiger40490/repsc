cd "$( dirname "${BASH_SOURCE[0]}" )"/..
# now we are in the parent dir of run.sh

set -e
make 
./feed
make clean 

printf '~~ untracked files ~~\n'
git clean -n
#ls -l
