echo -en "\n\n\n Run FixShell1 and grep log? [any_other_key / n ] ";
read $REPLY;
[ "$REPLY" = "n" ] && exit # use "return" if this is a sourced script
