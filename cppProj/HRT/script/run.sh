cd "$( dirname "${BASH_SOURCE[0]}" )"/..
# now we are in the parent dir of run.sh

set -e
make clean all 2>&1 |less -E
ls -l ./feed
./feed # 2>&1 |less -E
printf '    ~~~~~~~~~~~~~~~~~~~~~~\n'
/bin/rm *.o *.a

printf 'v v   untracked files   v v\n'
git clean -n
