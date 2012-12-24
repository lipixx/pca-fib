#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 100000000

int vector[MAX_SIZE];

int meu_abs(int x) {
	if (x < 0) {
		x = -x;
	}
	return x;
}

void aplicaAbs(int *vector, int n)
{
  for (;n>0;n--) {
    vector[n]=meu_abs(vector[n]);
  }
}

int main(int argc, char *argv[])
{
    int n=MAX_SIZE;
    int i, acum,j;

    if (argc > 1) {
	if ((n=atoi(argv[1]))>MAX_SIZE) n=MAX_SIZE; 
    }

    for (i=0,j=n-1; i<n/2; i++,j--)
      {
	vector[i]= (rand()&255)+128;
	vector[j]= (rand()&255)-255;
      }


    
    aplicaAbs(vector, n);

    return 0;
}
