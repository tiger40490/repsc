#usage: this.script inFile > outFile

$i=0;
while(<>) {
	$i++;
	if ($i == 999){ # a target line to edit
	  chomp
		$_ = "$_\r\n";  # insert carriage-return before the original line-feed
	}
	print $_;
}