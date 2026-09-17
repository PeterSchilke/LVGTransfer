#! /usr/bin/perl -w
#
# Time-stamp: <2006-11-20 15:56:16 schilke> 
#
# transpose.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

open (IN, "ci_p.col");
open (OUT, ">ci.col");
$i = 0;
while (<IN>) {
  ($a[$i], $b[$i], $c[$i]) = split;
  $i++;
}
for ($j=0;$j<$i;$j++) {
  $a[$j] *=1e-10;
  print OUT "$a[$j] ";
}
print OUT "\n";
for ($j=0;$j<$i;$j++) {
  $b[$j] *=1e-10;
  print OUT "$b[$j] ";
}
print OUT "\n";

for ($j=0;$j<$i;$j++) {
  $c[$j] *=1e-10;
  print OUT "$c[$j] ";
}
print OUT "\n";
