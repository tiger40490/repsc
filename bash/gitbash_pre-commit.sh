#!/bin/sh
# The hook should Use q[exit] with non-zero status after issuing an appropriate message if it wants to stop the commit.
# The --no-verify option to git commit bypasses the pre-commit hook when committing

# Based on https://stackoverflow.com/questions/19387073/how-to-detect-commit-amend-by-pre-commit-hook
# If head is strictly ahead (eg: child) of $upstream, this hook is quiet.
# if head is strictly behind (eg: parent of) $upstream, this hook would complain, correctly.
# if head is same as $upstream, then --amend vs regular append are _indistinguishable_ so this hook has to "err on the side of caution" and prompt user to confirm.
# Risk in "Amend" scenario is too high, much higher than the inconvenience of "Append" scenario.
# The inconvenience is a necessary evil -- all my git hooks are.

############################
# Are we on a branch?  If not, don't object
localBranch=$(git symbolic-ref -q --short HEAD) || exit 0

# If initial commit, don't object
head=$(git rev-parse -q --verify HEAD) || exit 0

# upstream is the hash of remote tip
#https://stackoverflow.com/questions/19474577/what-does-the-argument-u-mean-in-git explains @{u}
upstream=$(git rev-parse -q --verify @{u}) || exit 0
printf "FYI\n  $upstream = upstream\n  $head = head\n"

if git merge-base --is-ancestor HEAD $upstream; then
  printf "Amending || appending on $localBranch branch-tip while original commit is on remote upstream?\n( Tip 1: Once inside commit-msg editor, you will have one more chance to cancel this commit via :cq )\n( Tip 2: Successful commit always print details to console. If you don't see them then nothing committed. )\n Continue? [ y / any_other_key to quit] "
  exec < /dev/tty # without this, pre-commit hook ignores stdin :(
  read $REPLY
  [ "$REPLY" = "y" ] || exit 40490
fi
exit 0