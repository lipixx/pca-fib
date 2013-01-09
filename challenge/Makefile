CC=gcc

CFLAGS = -O3 -pipe -march=core2 -mfpmath=sse -pthread -Wl,-s,-O1 -lm 
DBGFLAGS = -pipe -march=core2 -mfpmath=sse -pthread -Wl,-s,-O1 -lm 

all:	maxsum

pg:	
	$(CC) $(CFLAGS) -pg maxsum.c -o maxsum

g:	
	$(CC) -g maxsum.c -o maxsum

clean:
	rm maxsum