#! /usr/bin/env python
#
# Time-stamp: <2007-11-14 11:33:51 schilke> 
#
# levels_hnco.py	-- Peter Schilke (<schilke@mpifr-bonn.mpg.de>)
#

inFile = open('dco+_xclass.dat', 'r')
outFile = open('dco+.dat', 'w')

i = 0
 
for inLine in inFile.readlines():
    # take it apart
    tag    = inLine[0:4]
    if tag == 'DCO+':
        ji     = int(inLine[37:39])
        en     = float(inLine[81:87])/1.438856139
#        print '%s  %2d %2d %2d %f' % (tag, ji[i], kai[i], kbi[i], en[i])
        outLine =  '0 %2d %f\n' % (ji, en)
        outFile.write(outLine)
