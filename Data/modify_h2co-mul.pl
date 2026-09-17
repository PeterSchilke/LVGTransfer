#! /usr/bin/perl -w
#
# Time-stamp: <2000-07-03 13:31:56 schilke> 
#
# transpose.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

open (IN, "h2co-o.col.ori");
open (OUT, ">h2co-o.col");
$i = 0;
print OUT "21\n";
print OUT "10. 15. 20. 30. 40. 50. 60. 70. 80. 90. 100. 120. 140. 160. 180. 200. 220. 240. 260. 280. 300.\n";

while (<IN>) {
  if ($i == 4){
    $i = 0;
  }
  chomp;
  if ($i == 0) {
    $a = $_;
    print OUT "$a ";
  } elsif ($i == 1) {
    @b = split;
    for ($j=0; $j<= $#b; $j++) {
      $b[$j] *= 1e-10;
      print OUT "$b[$j] ";
    }
  } elsif ($i == 2) {
    @c = split;
    for ($j=0; $j<= $#c; $j++) {
      $c[$j] *= 1e-10;
      print OUT "$c[$j] ";
    }
  } elsif ($i == 3) {
    @d = split;
    for ($j=0; $j<= $#d; $j++) {
      $d[$j] *= 1e-10;
      print OUT "$d[$j] ";
    }
  print OUT "\n";
  } 
  $i++;
}
