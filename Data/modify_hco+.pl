#! /usr/bin/perl -w
#
# Time-stamp: <1999-07-05 14:37:26 schilke> 
#
# transpose.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

open (IN, "hco+.rates");
open (OUT, ">hco+_new.col");
$i = -1;
$k = -1;
while (<IN>) {
  s/D/e/g;
  (@line) = split;
  if ($#line == 0) {
    $i++;
    $temp[$i] = $line[0];
  } elsif (/\(/) {
    $k = -1;
  } elsif ($i >= 0) {
    $k++;
#    print "$_ \n";
    for ($j=0; $j<=$#line; $j++) {
      $rate[$k][$j][$i] = $line[$j];
    }
  }
}
$max_temp = $i+1;
print OUT "$max_temp\n";
for ($i=0; $i<$max_temp; $i++) {
  print OUT "$temp[$i] ";
}
print OUT "\n";
for ($k=0; $k<21; $k++) {
  for ($j=0; $j<21; $j++) {
    print OUT "$k $j ";
    for ($i=0; $i<$max_temp; $i++) {
      print OUT "$rate[$k][$j][$i] ";
    }
    print OUT "\n";
  }
}
