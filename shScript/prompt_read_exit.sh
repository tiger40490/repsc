printf "\n Continue? [ y / any_other_key to quit] " #printf is better than q[echo -en]
read $REPLY
[ "$REPLY" = "y" ] || return # use q[ exit ] if this is a standalone script


########  Here's the "opposite" way
echo -en "\n Continue? [any_other_key to confirm / n ] "
read $REPLY
[ "$REPLY" = "n" ] && exit # use q[ return ] if this is a sourced script
