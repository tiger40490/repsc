cd "$( dirname "${BASH_SOURCE[0]}" )"/..
# now we are in the parent dir of run.sh

set -e
make clean all
ls -l ./feed
./feed
printf '    ~~~~~~~~~~~~~~~~~~~~~~\n'
/bin/rm *.o *.a

printf 'v v   untracked files   v v\n'
git clean -n
