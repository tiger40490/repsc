#!/usr/bin/perl -p
 $spacePolicy = '|'; # '|' means repalce SOH with pipe, not implemented
 $spacePolicy = '2'; # '2' means replace SOH with two-spaces
 $spacePolicy = '^'; # '^' means replace embedded space with caret, so that we use a single space to replace SOH. In this case, we swap ^ with space in the traditional format.

=head1 Essential design goals
This tool reformats logged FIX messages in human readable (hopefully compact) format, hopefully easy to grep
Reliability is a top 3 priority
Thoroughness is not a priority... this tool is not designed to be thorough. When it doesn't work, it should be obvious not misleading
Simplicity is a top 5 priority
Readability is a top 10 priority
=cut

=head1 Usage
Usage : less some.log |this.pl | less
Usage : this.pl some.log | less
=cut

next LINE unless /8=FIX/ ; # simplicity is priority
s/: Sending /: Sending  /; # output alignment

if     ($spacePolicy == '^'){
  while( s/(\x01\S+) /\1^/g ){}
  s/\x01/ /g ; # single-space to replace SOH
}elsif ($spacePolicy == '2'){
  s/\x01/  /g ; # two-spaces .. look different from a single embedded space
}
