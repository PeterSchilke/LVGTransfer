# Makefile for LVG
# Copyright (C) 1997 Peter Schilke <schilke@mpifr-bonn.mpg.de>
# $Header: /home/schilke/cvsroot/transfer/lvg/generic/Makefile,v 1.2 2004/02/12 17:12:40 schilke Exp $
# $Log: Makefile,v $
# Revision 1.2  2004/02/12 17:12:40  schilke
# *** empty log message ***
#
# Revision 1.1.1.1  2003/10/15 16:10:22  schilke
# Generic LVG
#
# Revision 1.1.1.1  2001/04/04 08:28:14  schilke
# version using bn
#

CC = c++
CFLAGS = -ftemplate-depth-30 -g #-I/usr/include/c++/4.0.2/ # opt/intel/cc/9.0/include/c++
LFLAGS = -w  -lstdc++ -lm -g#-L/usr/lib/gcc/i586-suse-linux/4.0.2/ 
#-I /aux160/schilke/lib/gcc/g++-include
# -I /opt/CC/include/CC 

OBJS = main.o Mols.o LinearVib.o LinearVibl.o atomicOxygen.o NH3.o AsymmetricRotor.o AsymmetricRotorT.o\
       Defmol.o Utils.o Cloud.o print.o atomicCarbon.o \
       CalcColl.o SolveLVG.o setP.o \
       PrintOutLinearVib.o PrintOutLinearVibl.o PrintOutatomicOxygen.o PrintOutNH3.o PrintOutAsymm.o \
	PrintOutAsymmT.o PrintOutatomicCarbon.o \
       calcJ.o DoCalc.o \
       newt.o ludcmp.o lubksb.o lnsrch.o fdjac.o fmin.o nrutil.o calEq.o  \
       MinMaxInput.o printPars.o

XOBJS = main_Xmol.o Mols.o LinearVib.o LinearVibl.o atomicOxygen.o NH3.o AsymmetricRotor.o AsymmetricRotorT.o\
       Defmol.o Utils.o Cloud.o print.o  atomicCarbon.o \
       CalcColl.o SolveLVG.o setP.o PrintOutatomicCarbon.o \
       PrintOutLinearVib.o PrintOutLinearVibl.o PrintOutatomicOxygen.o PrintOutNH3.o PrintOutAsymm.o PrintOutAsymmT.o\
       calcJ.o DoCalc_Xmol.o \
       newt.o ludcmp.o lubksb.o lnsrch.o fdjac.o fmin.o nrutil.o calEq.o  \
       MinMaxInput_Xmol.o printPars.o

SRCS = $(OBJS:.o=.cc)
.cc.o:
	$(CC) -c $(CFLAGS) $<              
lvg:	$(OBJS)
	$(CC) $(LFLAGS) -o lvg $(OBJS) 
xmol:	$(XOBJS)
	$(CC) $(LFLAGS) -o lvg_xmol $(XOBJS) 
tar:
	touch lvg.tar.gz
	rm lvg.tar.gz
	tar cvzf lvg.tar.gz *.cc *.h *.gif Makefile README lvg_gui ../Data/*.col ../Data/*.dat ../Data/*.sif
$(OBJS): Mols.h Params.h
