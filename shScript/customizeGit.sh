# todo: remove the shell alias/functions that are no longer required

# script to be run normally i.e. in a subsehll, not sourced
git config --global alias.alias 'config --get-regexp alias'
git config --global alias.amend   'commit --am --reset-author' #would update timestamp even if no new content. To preserve timestamp, use :cq to exit vi.
git config --global alias.comit   'commit'
git config --global alias.commmit 'commit'
git config --global alias.diffn 'diff --name-status'
git config --global alias.shown 'show --name-status'
git config --global alias.force 'push --force-with-lease'

# less useful in repo1 as it often downloads a disconnected branch 
git config --global alias.pullb '!git fetch origin ${1}:${1}' 
git alias