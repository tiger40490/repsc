g1(){ # single-hit
  find .|scan_c_src.pl "$@"
}
g(){ # multi-hit
  # the trailing q(less) is for the normal "multi-hit" case. In the single-hit case, it would mess up the exec(less ....)
  g1 "$@" |less -ER
}
