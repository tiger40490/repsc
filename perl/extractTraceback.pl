open(IN, '<', 'extractTraceback.dat') or die $!;
$state=0; #0 means outside. 1 means between Traceback and raise. 2 means after printing the raise line, before printing the trailer-line
while(<IN>){
  / Traceback / and $state=1;
  
  if ($state != 0){
    s/\[.*\]//;
    print ; 
  }
  if (/ raise /){
    $state=2;
  } elsif ($state == 2){
    $state = 0;    
    print "\n\n";  
  }
}
=pod
Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=39484&action=edit
=cut