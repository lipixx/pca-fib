#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUB(i,j,k) (matrix[i+k][j] - matrix[i][j])
#define MAXN 810
#define DEBUG 0

int N;
short matrix[MAXN][MAXN];

void read_matrix();
void print_matrix();
int maxsum();

int main(int argc, char *argv[])
{
  scanf("%i",&N);
  read_matrix();

#if DEBUG
  clock_t start, end;
  start = clock();
  printf("%i\n",maxsum());
  end = clock();
  printf("Elapsed time: %d\n",(end-start));
#else
  printf("%i\n",maxsum());
#endif

  //print_matrix(matrix);
  
  return 0;
}

void print_matrix()
{
  int i,j;
  printf("\n\n ##MATRIX PRINT##\n");
  for (i=0; i<N;i++)
    {
      for (j=0;j<N;j++)
	{
	  printf("%i ",matrix[i][j]);
	}
      printf("\n");
    }
  printf("##END OF MATRIX PRINT##\n");
}

void read_matrix()
{
  int i, j, r;

  for(i = 0; i<N; i++)
    {
      for(j = 0; j<N; j++)
	{
	  scanf("%i",&r);
          matrix[i][j] = (char) r;
	}
    }
}

int maxsum()
{
  int i, j, k, x, result;
  for(i = 1; i<=N; i++)
    {
      for(j = 0; j<N; j++)
  	matrix[i][j] =  matrix[i][j] + matrix[i-1][j];
    }

  result = matrix[1][0];
  for(k = 0; k<N; k++)
    {
      for(i = 0; i<=N-k; i++)
	{
	  x = 0;
	  for(j = 0; j<N; j++)
	    {
	      if(x >= 0)
	      	x += SUB(i,j,k);
	      else
	      	x =  SUB(i,j,k);

	      if(x > result)
		result = x;
	    }
	}
    }               
  return result;
}
