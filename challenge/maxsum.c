#include <stdio.h>
#include <stdlib.h>

#define Dif(i,j,k) (matrix[i+k][j] - matrix[i][j])
#define MAXN 810

int N, MAX;
int matrix[MAXN][MAXN];

void read_matrix();
void print_matrix();
int maxsum();

int main(int argc, char *argv[])
{
  scanf("%i",&N);
  read_matrix();
  printf("%i\n",maxsum());
  /*print_matrix(matrix);*/  
  
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
  int i, j;

  for(i = 1; i<=N; i++)
    {
      for(j  = 0; j<N; j++)
	{
	  scanf("%d",&matrix[i][j]);         
	}
    }
}

int maxsum()
{
  int i, j, k, t;
  for(i = 1; i<=N; i++)
    {
      for(j = 0; j<N; j++)
	matrix[i][j] =  matrix[i][j] + matrix[i-1][j];
    }

  MAX = matrix[1][0];
  for(k = 1; k<=N; k++)
    {
      for(i = 0; i<=N-k; i++)
	{
	  for(t = 0, j = 0; j<N; j++)
	    {
	      if(t>=0)
		t+= Dif(i,j,k);
	      else
		t = Dif(i,j,k);
	      if(t>MAX)
		MAX = t;
	    }
	}
    }               
  return MAX;
}
