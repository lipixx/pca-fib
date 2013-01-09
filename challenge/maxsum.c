#include <stdio.h>
#include <stdlib.h>

#define max(X, Y) ((X) > (Y) ? (X) : (Y))

int N;

void print_matrix(char matrix[][N]);
void read_matrix(char matrix[][N]);
int maxsum(char matrix[][N]);

int main(int argc, char *argv[])
{
  int i,j;

  scanf("%i",&N);
  char (*matrix)[N] = malloc(sizeof *matrix * N);

  read_matrix(matrix);
  printf("%i",maxsum(matrix));
  /*print_matrix(matrix);*/

  return 0;
}

void read_matrix(char matrix[][N])
{
  int i,j,r;

  for (i=0; i<N;i++)
    {
      for (j=0;j<N;j++)
	{
	  scanf("%i",&r);
	  matrix[i][j] = (char) r;
	}
    }
}

void print_matrix(char matrix[][N])
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

int maxsum(char matrix[][N])
{
  int x,y,i,j,acum,tmp,result;
  
  result = 0xFFFFFFFF;

  for (x=0; x<N; x++)
    for (y=0; y<N; y++)
      {
	acum = 0xFFFFFFFF;
	for (i=0;i<N;i++)
	  {
	    tmp = 0;
	    for (j=x;j<=y;j++)
	      {
		tmp += matrix[i][j];
	      }
	    acum = max(acum + tmp, tmp);
	    result = max(result, acum);
	  }
      }
  
  return result;
}
