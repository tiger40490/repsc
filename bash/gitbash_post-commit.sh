#!/bin/sh
# this script runs after commit-msg and before the commit confirmation is printed to console.
############################
# localBranch=$(git symbolic-ref -q --short HEAD)

head=$(git rev-parse -q --verify HEAD)

# upstream is the hash of remote tip
#https://stackoverflow.com/questions/19474577/what-does-the-argument-u-mean-in-git explains @{u}
upstream=$(git rev-parse -q --verify @{u})

if ! git merge-base --is-ancestor $upstream HEAD; then
  printf "\nvvv-- post-commit --> Consider revising .. remote upstream isn't a fast-forward ancestor of last commit :(\n  $upstream = upstream\n  $head = head\n^^^\n\n"
fi
