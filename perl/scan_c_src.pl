#!/usr/bin/perl -n
# todo: make it progressively more portable. Every improvement counts. Don't belittle your effort
# todo: when no match found,  report 0 rathan than "grand total =     needles found"

# ---- usage examples ----
# find .|grep1.pl -i -v -A3 'strinG & value'
# find .|grep1.pl -i -v --class trade
# find .|grep1.pl '\-O2' # escape leading dash in needle. grep requirement
# find .|grep1.pl -P \\bReload\\b # whole word "Reload"

use Data::Dumper qw(Dumper);
INIT{ begin(); } # BEGIN block also usable IIF the sub is defined in advance

sub add_to_core_grep_ops{
      my $option = shift;
      $grep_core_options .= " $option " if ($grep_core_options !~ /$option/);
}
sub begin(){
  $screen_width=`/usr/bin/tput cols`;
  $long_arrow = '-'x($screen_width - 80) . '>';
  my $log_filename = "${0}.log";
  open($LOG, '>', $log_filename) or die "Could not open file '$log_filename' $!";
  print $LOG Dumper \@ARGV;
  my @header_ext=('H', 'h');
  my @src_ext=('C', 'c', 'cpp');
  $extension=join('|', @header_ext, @src_ext, 'xml');
  while(1){
    $needle=shift @ARGV;
    if ($needle !~ /^-/){ # not a command line option, so must be the actual search pattern
      die "--method and --class are mutually exclusive" if $needle_is_class_def and $needle_is_method_def;
      $needle = '(class|struct)\s+'.$needle.'\b(?!;)'   if $needle_is_class_def;
      $needle = '::'.$needle.'\s*\('                    if $needle_is_method_def;
      # Above are best-effort patterns, not exhaustive -- You can hit unexpected line breaks etc

      print $LOG "\n~~> the needle to grep (in haystack) is --> $needle <-- \n";

      die "You can select up to 1 of --no-header or --header-only or --any-ext" if $extension_filers>1;
      print $LOG "\n==> file extensions: $extension \n";
      return;
    }
    my $option = $needle;
    if ($option eq '-P') {
      print $LOG "\n--> perl regex \n";
      add_to_core_grep_ops('-P');
    }elsif ($option eq '-i') {
      print $LOG "\n--> case sensitive grep \n";
      add_to_core_grep_ops('-i');
    }elsif ($option eq '--method'){
      $needle_is_method_def=1;
      add_to_core_grep_ops('-P');
    }elsif ($option eq '--class'){
      $needle_is_class_def=1;
      add_to_core_grep_ops('-P');
    }elsif ($option eq '-v'){
      $verbose=1;
    }elsif ($option =~ /-(A|B)\d+/){
      print $LOG "\n--> found grep context-specifier : $option \n";
      $grep_context .= " $option ";
    }elsif ($option eq '--any-ext'){
      print $LOG "\n==> no file extension check \n";
      $extension_filers++;
      $is_any_ext=1;
      $extension='.*';
    }elsif ($option eq '--no-header'){
      print $LOG "\n==> no-header requested \n";
      $extension_filers++;
      $extension=join('|', @src_ext);
    }elsif ($option eq '--header-only'){
      print $LOG "\n==> header-only requested \n";
      $extension_filers++;
      $extension=join('|', @header_ext);
    }elsif ($option eq '--no-viewer'){
      print $LOG "\n==> no-viewer requested \n";
      $is_viewer_disabled=1;
    }else{
      die "invalid command line option $option";
    }
  } # while
} # sub

## LINE: while(<>){ # use this while loop if you omit "-n" on shebang line

  chomp ($tmp2 = $_);
  next LINE if -d $tmp2;
  next LINE unless /\.($extension)$/;

  # --color may require q(less) to use -R
  # single-quotes preseve embedded space in $needle
  my $cmd   = "grep $grep_core_options $grep_context -n --color=always '$needle' $_";
  #my $cmdNoColor = "grep $grep_core_options $grep_context -n '$needle' $_"; # works
  if ($verbose){
    $cmd =~ s/\s{2,}/ /g;
    print $LOG "$cmd"; #trailing newline
  }
  my $grep_output = qx($cmd);
  next LINE unless $grep_output;
  if ($verbose){
    print $LOG "$grep_output";
  }

  $pat2 = '(?:\x1b\[[0-9;]*[mGK])*'; # matches color code from less output
  $grep_output =~ s/^$pat2(\d+)$pat2:$pat2\s*/$1: /gm; # compact original leading spaces
  $offset = $1;
  # todo: hide the line if needle appears ONLY in a trailing comment

  ($filename = $_) =~ s/^\.\/(.*?)\s+$/\1/;
  $cmd = "grep $grep_core_options -o '$needle' $filename|wc -l";
  if ($verbose){
    $cmd =~ s/\s{2,}/ /g;
    print $LOG "$cmd # find count\n";
  }
  my $count = qx($cmd);
  chomp $count;
  $grand_total += $count;
  print "-- $count hit(s) in $long_arrow $filename :\n$grep_output";

END{
  if ($grand_total != 1){
    print "---- grand total ==   $grand_total   needles found\n";
  }elsif( ! $is_viewer_disabled){
    # command would not work properly if you pipe this to "| less" !
    my $cmd = "less +${offset}g -MN $filename";
    print "---- exactly one match. Let's use command below to open the file. \n$cmd\n...\n\n";
    if (system($cmd)){
      print "someting unexpected happened (but never mind) :$!";
    }
    print STDERR "\n  v  v  v  v  v  v  v  v\n If you don't see line numbers then you may have a pipe to  \"| less\"  somewhere . Run this command directly in your shell :\n$cmd\n  ^  ^  ^  ^  ^  ^  ^  ^\n";
  }
  print $LOG "closing log file :)";
  close $LOG;
}
