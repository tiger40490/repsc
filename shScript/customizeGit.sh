# script to be run normally i.e. in a subsehll, not sourced

git config --global alias.alias 'config --get-regexp alias'
git config --global alias.amend 'commit --am --reset-author' #would update timestamp even if no new content. To preserve timestamp, use :cq to exit vi.
git config --global alias.comit  'commit'
git config --global alias.commmit 'commit'
git config --global alias.diffn 'diff --name-status'
git config --global alias.force 'push --force-with-lease'
git config --global alias.shown 'show --name-status'
git config --global alias.swapLast2 "!GIT_SEQUENCE_EDITOR=\"sed -i -n 'h;1n;2p;g;p' \" git rebase -i HEAD~2"
git config --global alias.reword '!git commit --fixup reword:$1 && GIT_EDITOR=true && git rebase --autosquash --interactive --rebase-merges $1~1 && echo "Successful reword on"'

# less useful in repo1 as it often downloads a disconnected branch 
git config --global alias.pullb '!git fetch origin ${1}:${1}' 
git alias