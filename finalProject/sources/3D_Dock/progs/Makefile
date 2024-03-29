# Copyright (C) 1997-2000 Gidon Moont

# Biomolecular Modelling Laboratory
# Imperial Cancer Research Fund
# 44 Lincoln's Inn Fields
# London WC2A 3PX

# +44 (0)20 7269 3565
# http://www.bmm.icnet.uk/

#############

# This line you will definitely have to edit

FFTW_DIR        = ../../fftw-2.1.3/bin

#############

# You may need/want to edit some of these
#
# Hint: For the CC_FLAGS have a look at what the fftw build used

SHELL           = /bin/sh

CC              = gcc

CC_FLAGS        = $(FLAGS) -O3 -march=native -static -pthread
STRIP           = strip

CC_LINKERS      = -lm

SECURITY	= chmod 555

####################################################

# You should not be editing anything below here

CC_FLAGS_FULL	= -I$(FFTW_DIR)/include $(CC_FLAGS)
FFTW_LINKERS    = -L$(FFTW_DIR)/lib -lrfftw -lfftw

#############

.SUFFIXES:	.c .o

.c.o:
		$(CC) $(CC_FLAGS_FULL) -c $<

#############

LIBRARY_OBJECTS = manipulate_structures.o angles.o coordinates.o electrostatics.o grid.o qsort_scores.o

PROGRAMS = ftdock build randomspin

all:		$(PROGRAMS)

g:		
		make FLAGS='-g'

pg:		
		make FLAGS='-g -pg'

dbg:
		make CC_FLAGS='$(FLAGS)-march=native -static -pthread -g'

#############

ftdock:		ftdock.o $(LIBRARY_OBJECTS) structures.h
		$(CC) $(CC_FLAGS_FULL) -o $@ ftdock.o $(LIBRARY_OBJECTS) $(FFTW_LINKERS) $(CC_LINKERS)
#		$(STRIP) $@
		$(SECURITY) $@

#############

build:		build.o $(LIBRARY_OBJECTS) structures.h
		$(CC) $(CC_FLAGS) -o $@ build.o $(LIBRARY_OBJECTS) $(CC_LINKERS)
#		$(STRIP) $@
		$(SECURITY) $@

#############

randomspin:	randomspin.o $(LIBRARY_OBJECTS) structures.h
		$(CC) $(CC_FLAGS) -o $@ randomspin.o $(LIBRARY_OBJECTS) $(CC_LINKERS)
#		$(STRIP) $@
		$(SECURITY) $@

#############

clean:
		rm -f *.o core $(PROGRAMS)

#############

# dependencies

ftdock.o:			structures.h
build.o:			structures.h
randomspin.o:			structures.h

angles.o:			structures.h
coordinates.o:			structures.h
electrostatics.o:		structures.h
grid.o:				structures.h
manipulate_structures.o:	structures.h
qsort_scores.o:			structures.h
