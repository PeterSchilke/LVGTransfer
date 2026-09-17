#! /usr/bin/perl -w
#
# Time-stamp: <1999-07-05 12:48:10 schilke> 
#
# transpose.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

open (IN, "HCO+.rates");
$i = 0;
while (<IN>) {
  (@line) = split;
  if ($#line == 0) {
  } elsif ($i++ < 22) {
    $en = $line[$#line]/1.438856139;
    print "$en \n";
  }
}
