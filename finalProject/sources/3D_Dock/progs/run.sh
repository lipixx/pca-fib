#!/bin/bash

make clean
make
/usr/bin/time -p ./ftdock -static 2pka.parsed -mobile 5pti.parsed > /dev/null
/usr/bin/time -p ./ftdock -static 1hba.parsed -mobile 5pti.parsed > /dev/null
/usr/bin/time -p ./ftdock -static 4hhb.parsed -mobile 5pti.parsed > /dev/null

# make clean
# make g
# /usr/bin/time ./ftdock -static 2pka.parsed -mobile 5pti.parsed > /dev/null
# /usr/bin/time ./ftdock -static 1hba.parsed -mobile 5pti.parsed > /dev/null
# /usr/bin/time ./ftdock -static 4hhb.parsed -mobile 5pti.parsed > /dev/null

# make clean
# make pg
# ./ftdock -static 2pka.parsed -mobile 5pti.parsed > /dev/null
# gprof ./ftdock > gprof.2pka
# ./ftdock -static 1hba.parsed -mobile 5pti.parsed > /dev/null
# gprof ./ftdock > gprof.1hba
# ./ftdock -static 4hhb.parsed -mobile 5pti.parsed > /dev/null
# gprof ./ftdock > gprof.4hhb

make clean