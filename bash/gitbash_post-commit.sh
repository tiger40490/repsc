#!/bin/sh
# Tested in win10 gitbash, this script is triggered after commit-msg and before the console message of commit confirmation.
############################
# localBranch=$(git symbolic-ref -q --short HEAD)

# upstream is the hash of remote tip
#https://stackoverflow.com/questions/19474577/what-does-the-argument-u-mean-in-git explains @{u}
upstream=$(git rev-parse -q --verify @{u})

if ! git merge-base --is-ancestor $upstream HEAD; then
  head=$(git rev-parse -q --verify HEAD)
  printf "\nvvv-- post-commit --> Consider revising .. remote upstream isn't a fast-forward ancestor of last commit :(\n  $upstream = upstream\n  $head = HEAD\n^^^\n\n"
fi
