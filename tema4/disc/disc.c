#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define DISK_SIZE  (1<<20)
#define N_ITER 100000000

typedef unsigned long long bignum;

typedef struct
	{
	unsigned int *p;		/* pointer to array */
	int bitsPerByte;		/* 8 on normal systems */
	int bytesPerInt;		/* sizeof(unsigned int) */
	int bitsPerInt;			/* for bit arithmetic */
	int bpiShift;			/* 8 bit words = 3, 16=4, etc */
	int bpiMask;			/* bitsPerInch - 1, for modulus */
	bignum bitsInArray;		/* how many bits in array */
	bignum intsInArray;		/* how many uints to give necessary bits */
	} BITARRAY;

void freeBitArray(BITARRAY *ba)
	{
	free(ba);
	}

BITARRAY * createBitArray(bignum bits)
	{
	BITARRAY *ba = malloc(sizeof(BITARRAY));
	assert(ba != NULL);
	ba->bitsPerByte = 8;
	ba->bytesPerInt = sizeof(unsigned int);
	ba->bitsPerInt = ba->bitsPerByte * ba->bytesPerInt;
	switch (ba->bitsPerInt)
		{
		case 8: ba->bpiShift = 3; break;
		case 16: ba->bpiShift = 4; break;
		case 32: ba->bpiShift = 5; break;
		case 64: ba->bpiShift = 6; break;
		case 128: ba->bpiShift = 7; break;
		case 256: ba->bpiShift = 8; break;
		case 512: ba->bpiShift = 9; break;
		default: {
			perror("ABORTING: Non-standard bits per int\n");
			exit(1);
			break;
			}
		};
	ba->bpiMask = ba->bitsPerInt - 1;
	ba->bitsInArray = bits;
	ba->intsInArray = bits/ba->bitsPerInt + 1;
	ba->p = malloc(ba->intsInArray * ba->bytesPerInt);
	assert(ba->p != NULL);
	return ba;
	}

void setBit(BITARRAY *ba, bignum bitSS)
	{
	unsigned int *pInt = ba->p + (bitSS >> ba->bpiShift);
	unsigned int remainder = (bitSS & ba->bpiMask);
	*pInt |= (1 << remainder);
	}

void clearBit(BITARRAY *ba, bignum bitSS)
	{
	unsigned int *pInt = ba->p +  (bitSS >> ba->bpiShift);
	unsigned int remainder =  (bitSS & ba->bpiMask);
	unsigned int mask = 1 << remainder;
	mask = ~mask;
	*pInt &= mask;
	}

int getBit(BITARRAY *ba, bignum bitSS)
	{
	unsigned int *pInt = ba->p + (bitSS >> ba->bpiShift);
	unsigned int remainder = (bitSS & ba->bpiMask);
	unsigned int ret = *pInt;
	ret &= (1 << remainder);
	return(ret != 0);
	}


void clearAll(BITARRAY *ba)
	{
	bignum intSS;
	for(intSS=0; intSS <= ba->intsInArray; intSS++)
		{
		*(ba->p + intSS) = 0;
		}
	}

void setAll(BITARRAY *ba)
	{
	bignum intSS;
	for(intSS=0; intSS <= ba->intsInArray; intSS++)
		{
		*(ba->p + intSS) = ~0;
		}
	}


void diskSimulation(BITARRAY *ba, bignum fileSize, int n_iters)
{
    bignum n_block;
    int i;

    for (i=0; i<n_iters; i++)
    {
       /* "The correct way to generate it is:
        *
        *      n_block=(int) ((float)(fileSize*rand())/(RAND_MAX+1.0));
	*
        *  but it is too expensive for our purpose." 
        */
       n_block=(bignum) rand() & (fileSize-1); /* fileSize = 2^x !!*/
       if (getBit(ba, n_block)) clearBit(ba,n_block);
       else setBit(ba, n_block); 
    }
}

int main(int argc, char *argv[])
{
    bignum fileSize = DISK_SIZE;
    int n_iters = N_ITER;
    BITARRAY *ba;

    if (argc > 1)
	fileSize  = 1 << atoi(argv[1]); 
    if (argc > 2)
	n_iters = atoll(argv[2]); 

    ba = createBitArray(fileSize);
    assert(ba != NULL);		
    setAll(ba);             /* For example */ 

    diskSimulation(ba, fileSize, n_iters);

    write(1, ba->p, ba->intsInArray);

    /*freeBitArray(ba);*/

    return 0;
}
