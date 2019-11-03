#!/bin/sh
# Based on https://stackoverflow.com/questions/19387073/how-to-detect-commit-amend-by-pre-commit-hook
# An example hook script to verify what is about to be committed.
# The hook should

# Use q[exit] with non-zero status after issuing an appropriate message if it wants to stop the commit.

# the --no-verify option to git commit bypasses the pre-commit hook when committing

# If initial commit, don't object
git rev-parse -q --verify HEAD >/dev/null || exit 0

# Are we on a branch?  If not, don't object
localBranch=$(git symbolic-ref -q --short HEAD) || exit 0

# Does the branch have an upstream?  If not, don't object
# https://stackoverflow.com/questions/19474577/what-does-the-argument-u-mean-in-git explains @{u}
upstream=$(git rev-parse -q --verify @{u}) || exit 0

# If HEAD is contained within upstream, object.
if git merge-base --is-ancestor HEAD $upstream; then
  printf "Apparently amending $localBranch branch while original commit is on remote upstream..\n Continue? [ Y / any_other_key to quit] "
  exec < /dev/tty # without this pre-commit hook ignores stdin
  read $REPLY
  [ "$REPLY" = "Y" ] || exit 40490
fi
exit 0