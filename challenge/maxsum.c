#include <stdio.h>
#include <stdlib.h>

int N;

void print_matrix(char matrix[][N]);
void read_matrix(char matrix[][N],int n);

int main(int argc, char *argv[])
{
  int i,j;

  scanf("%i",&N);
  char (*matrix)[N] = malloc(sizeof *matrix * N);

  read_matrix(matrix,N);
  print_matrix(matrix);

  return 0;
}

void read_matrix(char matrix[][N],int n)
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
