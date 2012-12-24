#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N_ITER 20000000
#define operacio(_A,_B,_C,__i,__j,__k)				\
  _C[__i][__j] = _C[__i][__j] + _A[__i][__k] * _B[__k][__j];	\
  
#define multiplica(_A,_B,_C,n_iter)			\
  for (_iter=0; _iter<n_iter; _iter++)			\
    {							\
	      operacio(_A,_B,_C,0,0,0);				\
	      operacio(_A,_B,_C,0,0,1);				\
	      operacio(_A,_B,_C,0,0,2);				\
	      operacio(_A,_B,_C,0,0,3);				\
	      operacio(_A,_B,_C,0,1,0);				\
	      operacio(_A,_B,_C,0,1,1);				\
	      operacio(_A,_B,_C,0,1,2);				\
	      operacio(_A,_B,_C,0,1,3);				\
	      operacio(_A,_B,_C,0,2,0);				\
	      operacio(_A,_B,_C,0,2,1);				\
	      operacio(_A,_B,_C,0,2,2);				\
	      operacio(_A,_B,_C,0,2,3);				\
	      operacio(_A,_B,_C,0,3,0);				\
	      operacio(_A,_B,_C,0,3,1);				\
	      operacio(_A,_B,_C,0,3,2);				\
	      operacio(_A,_B,_C,0,3,3);				\
	      operacio(_A,_B,_C,1,0,0);				\
	      operacio(_A,_B,_C,1,0,1);				\
	      operacio(_A,_B,_C,1,0,2);				\
	      operacio(_A,_B,_C,1,0,3);				\
	      operacio(_A,_B,_C,1,1,0);				\
	      operacio(_A,_B,_C,1,1,1);				\
	      operacio(_A,_B,_C,1,1,2);				\
	      operacio(_A,_B,_C,1,1,3);				\
	      operacio(_A,_B,_C,1,2,0);				\
	      operacio(_A,_B,_C,1,2,1);				\
	      operacio(_A,_B,_C,1,2,2);				\
	      operacio(_A,_B,_C,1,2,3);				\
	      operacio(_A,_B,_C,1,3,0);				\
	      operacio(_A,_B,_C,1,3,1);				\
	      operacio(_A,_B,_C,1,3,2);				\
	      operacio(_A,_B,_C,1,3,3);				\
	      operacio(_A,_B,_C,2,0,0);				\
	      operacio(_A,_B,_C,2,0,1);				\
	      operacio(_A,_B,_C,2,0,2);				\
	      operacio(_A,_B,_C,2,0,3);				\
	      operacio(_A,_B,_C,2,1,0);				\
	      operacio(_A,_B,_C,2,1,1);				\
	      operacio(_A,_B,_C,2,1,2);				\
	      operacio(_A,_B,_C,2,1,3);				\
	      operacio(_A,_B,_C,2,2,0);				\
	      operacio(_A,_B,_C,2,2,1);				\
	      operacio(_A,_B,_C,2,2,2);				\
	      operacio(_A,_B,_C,2,2,3);				\
	      operacio(_A,_B,_C,2,3,0);				\
	      operacio(_A,_B,_C,2,3,1);				\
	      operacio(_A,_B,_C,2,3,2);				\
	      operacio(_A,_B,_C,2,3,3);				\
	      operacio(_A,_B,_C,3,0,0);				\
	      operacio(_A,_B,_C,3,0,1);				\
	      operacio(_A,_B,_C,3,0,2);				\
	      operacio(_A,_B,_C,3,0,3);				\
	      operacio(_A,_B,_C,3,1,0);				\
	      operacio(_A,_B,_C,3,1,1);				\
	      operacio(_A,_B,_C,3,1,2);				\
	      operacio(_A,_B,_C,3,1,3);				\
	      operacio(_A,_B,_C,3,2,0);				\
	      operacio(_A,_B,_C,3,2,1);				\
	      operacio(_A,_B,_C,3,2,2);				\
	      operacio(_A,_B,_C,3,2,3);				\
	      operacio(_A,_B,_C,3,3,0);				\
	      operacio(_A,_B,_C,3,3,1);				\
	      operacio(_A,_B,_C,3,3,2);				\
	      operacio(_A,_B,_C,3,3,3);				\
    }									\
  
/* void multiplica(int A[4][4], int B[4][4], int C[4][4], unsigned int n_iter)
/* { */
/*    int iter; */
/*    int i,j,k; */

/*    for (iter=0; iter<n_iter; iter++) */
/*    { */
/*       for (i = 0; i < 4; i++)  */
/*       { */
/*         for (j = 0; j < 4; j++)  */
/* 	{ */
/*            for (k = 0; k < 4; k++)  */
/* 	   { */
/*               C[i][j] = C[i][j] + A[i][k] * B[k][j]; */
/* 	   } */
/* 	} */
/*       } */
/*    } */
/* } */

#define randu(_M,_N,_f,_c)			\
  _M[_f][_c] = rand();				\
  _N[_f][_c] = rand();				\

int main(int argc, char *argv[])
{
    int A[4][4], B[4][4], C[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    unsigned int n_iter=N_ITER, i,j;
    int _iter;
    int _i,_j,_k;

    /* for (i=0; i<4; i++) { */
    /*     for (j=0; j<4; j++) { */
    /*         A[i][j] = rand(); */
    /*         B[i][j] = rand(); */
    /*     } */
    /* } */

    randu(A,B,0,0);
    randu(A,B,0,1);
    randu(A,B,0,2);
    randu(A,B,0,3);

    randu(A,B,1,0);
    randu(A,B,1,1);
    randu(A,B,1,2);
    randu(A,B,1,3);

    randu(A,B,2,0);
    randu(A,B,2,1);
    randu(A,B,2,2);
    randu(A,B,2,3);

    randu(A,B,3,0);
    randu(A,B,3,1);
    randu(A,B,3,2);
    randu(A,B,3,3);

    if (argc > 1) {
	n_iter = atoi(argv[1]); 
    }

    multiplica(A, B, C, n_iter);
      
    printf("%d ", C[0][0]);
    printf("%d ", C[0][1]);
    printf("%d ", C[0][2]);
    printf("%d ", C[0][3]);   
    printf("\n");
    printf("%d ", C[1][0]);
    printf("%d ", C[1][1]);
    printf("%d ", C[1][2]);
    printf("%d ", C[1][3]);   
    printf("\n");
    printf("%d ", C[2][0]);
    printf("%d ", C[2][1]);
    printf("%d ", C[2][2]);
    printf("%d ", C[2][3]);   
    printf("\n");
    printf("%d ", C[3][0]);
    printf("%d ", C[3][1]);
    printf("%d ", C[3][2]);
    printf("%d ", C[3][3]);   
    printf("\n");
    return 0;
}
