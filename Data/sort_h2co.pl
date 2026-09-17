#! /usr/bin/perl -w
#
# Time-stamp: <2001-03-27 15:49:03 schilke> 
#
# sort_h2co.pl	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#
@data = split(/\n/, `cat h2co-o.dat.ori`);
local(@datakeys);
foreach (@data) {
  push(@datakeys, (split())[4]);
}
sub bydatakeys{ $datakeys[$a] <=> $datakeys[$b]; }

@sortdata = @data[sort bydatakeys $[..$#data];
print join("\n", @sortdata);
print "\n";
