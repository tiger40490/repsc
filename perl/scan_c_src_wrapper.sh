g (){
    g1 "$@" | less -ER
}
g1 (){
    find . | scan_c_src.pl "$@"
}
