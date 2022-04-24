# script to be run normally i.e. in a subsehll, not sourced
set -x
git config --global alias.alias 'config --get-regexp alias'
git config --global alias.comit   'commit'
git config --global alias.commmit 'commit'
git config --global alias.diffn 'diff --name-status'
git config --global alias.shown 'show --name-status'

git alias