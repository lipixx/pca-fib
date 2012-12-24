
.SUFFIXES: .pg .g .pg3 .3 .3p4 .pgp .2 .3ni

#CC=icc

PROGS_PG3 = ${PROGS:=.pg3}
PROGS_PG = ${PROGS:=.pg}
PROGS_PGP = ${PROGS:=.pgp}
PROGS_G = ${PROGS:=.g}
PROGS_3 = ${PROGS:=.3}
PROGS_2 = ${PROGS:=.2}
PROGS_3p4 = ${PROGS:=.3p4}
PROGS_3ni = ${PROGS:=.3ni}

PROGS_CLEAN = ${PROGS} ${PROGS_PG} ${PROGS_3} ${PROGS_G} ${PROGS_PG3} ${PROGS_PGP} ${PROGS_3p4} ${PROGS_2} ${PROGS_3ni}
PROGS_ALL = ${PROGS} ${PROGS_3}

all: ${PROGS_ALL}

zip: 
	make cleanall; dir=`basename $(PWD)`; cd .. ; rm -f $$dir.zip; zip -r $$dir $$dir

.c.3:
	$(CC) $(CFLAGS) $< -O3 $(LDLIBS) -o $@

.c.2:
	$(CC) $(CFLAGS) $< -O2 $(LDLIBS) -o $@

.c.3p4:
	$(CC) $(CFLAGS) $< -O3 -march=prescott $(LDLIBS) -o $@

.c.3ni:
	$(CC) $(CFLAGS) $< -O3 -fno-inline $(LDLIBS) -o $@

.c.pg:
	$(CC) $(CFLAGS) $< -pg -g -static $(LDLIBS) -o $@

.c.pgp:
	$(CC) $(CFLAGS) $< -pg -g -lc_p -lm_p -static -o $@

.c.pg3:
	$(CC) $(CFLAGS) $< -pg -g -O3 -static $(LDLIBS) -o $@

.c.g:
	$(CC) $(CFLAGS) $< -g $(LDLIBS) -o $@

clean:
	$(RM) -f $(PROGS_CLEAN) core.* gmon.out 

cleanall:
	@ for i in */. ; do  cd $$i; ${MAKE} clean; cd .. ; done
