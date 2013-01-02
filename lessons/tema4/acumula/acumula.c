#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 100000000
#define N_ITER 1000

long vector[MAX_SIZE];

long acumula(long *v, int len) {
	int i,j;
	long acum = 0;

 for(j=0; j< N_ITER; j++)
 {
	for (i = 0; i < len; i++)
		acum += v[i];
 }

	return acum;
}




int main(int argc, char *argv[])
{
    long n=MAX_SIZE;
    long i, acum;

    if (argc > 1) {
	if ((n=atoi(argv[1]))>MAX_SIZE) n=MAX_SIZE; 
    }

    for (i=0; i<n; i++)
      vector[i]=i;

    acum = acumula(vector, n);
    
    printf("%d\n", acum);
 
    return 0;
}
