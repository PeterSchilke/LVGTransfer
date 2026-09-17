#! /usr/bin/perl -w
#
# Time-stamp: <2000-06-30 18:08:39 schilke> 
#
# transpose.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

open (IN, "h2co-p.col.ori");
open (OUT, ">h2co-p.col");
$i = 0;
$k = -1;
while (<IN>) {
  if ($i == 4){
    $i = 0;
  }
  chomp;
  $a[$i] = $_;
  $i == 3 && print OUT "$a[0] $a[1] $a[2] $a[3]\n";
  $i++;
}
