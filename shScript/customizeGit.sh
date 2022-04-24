# todo: remove the shell alias/functions that are no longer required

# script to be run normally i.e. in a subsehll, not sourced
git config --global alias.alias 'config --get-regexp alias'
git config --global alias.comit   'commit'
git config --global alias.commmit 'commit'
git config --global alias.diffn 'diff --name-status'

# less useful in repo1 as it often downloads a disconnected branch 
git config --global alias.pullb '!git fetch origin ${1}:${1}' 
git config --global alias.shown 'show --name-status'
git alias