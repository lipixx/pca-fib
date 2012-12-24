#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
int N, N4;
//Es necessari tenir unsigned o ens basten char?
unsigned char d239[239][10][2];
unsigned char d25[25][10][2];
unsigned char d5[5][10][2];
unsigned char mul[4][10][2];
char a[10240], b[10240], c[10240];
char string[100];
char SUBS_YZ[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char * _SUBS_YZ = SUBS_YZ+9;

void calculate (void);
void progress (void);
void epilog (void);
void set_datasets(void);

#define DIV_UNROLL 6  /*Best unroll value: 6*/
#define LDIV_UNROLL 4 /*Best unroll value: 4*/
#define CHAR_BIT 8
#define _R 0
#define _Q 1
#define DIV_UN(addr,map,r,_x,_Q)			\
  addr = map[r][*_x];					\
  *_x = *(addr + _Q);					\
  r = *addr;						\
  _x++;							\

#define LDIV_UN(r,u,q,n,x)			\
  u = r * 10 + *x;				\
  q = u / n;					\
  r = u - q * n;				\
  *x = q;					\
  x++;						\

#define DIVIDE(matrix_addr,map,steps,rest)				\
  {  int k; unsigned char q, r, u, * addr; char *_x;		\
  _x = matrix_addr;							\
  r = 0;								\
  for (k = 0; k <steps; k++)						\
    {									\
      DIV_UN(addr,map,r,_x,_Q);						\
      DIV_UN(addr,map,r,_x,_Q);						\
      DIV_UN(addr,map,r,_x,_Q);						\
      DIV_UN(addr,map,r,_x,_Q);						\
      DIV_UN(addr,map,r,_x,_Q);						\
      DIV_UN(addr,map,r,_x,_Q);						\
    }									\
  for (k = 0; k <rest; k++)						\
    {									\
      DIV_UN(addr,map,r,_x,_Q);						\
    }}

#define LONGDIV(xaddr,n)				\
  { int k, steps, rest; unsigned q, r, u; char *x;	\
    x = xaddr;						\
    steps = (N4+1) / LDIV_UNROLL;			\
    rest = (N4+1) - steps * LDIV_UNROLL;		\
    r = 0;						\
    for (k = 0; k < steps; k++)				\
      {							\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x); }				\
    for (k = 0; k < rest; k++, x++) LDIV_UN(r,u,q,n,x);	\
  }							

void
MULTIPLY (char *x)
{
  int j, k, n;
  unsigned char q, r, u;
  r = 0;
  x += N4;
  /*
     r : [0,3]
     x : [0,9]
   */
  for (k = N4; k >= 0; k--, x--)
    {
      q = mul[r][*x][_Q];
      r = mul[r][*x][_R];
      *x = q;
    }
}

void
SET (char *x, int n)
{
  memset (x, 0, N4 + 1);
  *x = n;
}

inline void
SUBTRACT (char *x, char *y, char *z)
{
  int j, k;
  char v;
  x += N4;
  y += N4;
  z += N4;

  /*Original Version*/
  /* for (k = N4; k >= 0; k--, x--, y--, z--) */
  /*   { */
  /*     v = *y - *z; */
  /*     if (v < 0)		//HEAVY */
  /* 	{ */
  /* 	  *x = v + 10; */
  /* 	  *(z - 1) = *(z - 1) + 1; */
  /* 	} */
  /*     else */
  /* 	*x = v; */
  /*   } */

  for (k = N4; k >= 0; k--, x--, y--, z--)
    {
      v = *y - *z;     
      *x = *(_SUBS_YZ+v);
      *(z - 1) = *(z - 1) + (v < 0);

      /* /\*Alternatives*\/ */
      /* *x = v + (v>>(sizeof(char)*CHAR_BIT -1) & 0xA); */
      /* *x = v + ((v<0) * 10); //Slowest */
      
      /* /\*Hints*\/ */
      /* printf("Max entre %i i %i = %i\n",*y,*z,*x^((*x ^ *y) & -(*x < *y))); */
      /* printf("Abs de %i = %i\n",v, (v+(v >> sizeof(char) * 8 - 1))^(v >> sizeof(char) * 8 - 1)); */      
    }
}


inline void
SUBTRACT_MUL (char *x, char *z)
{
  int j, k;
  char v;
  unsigned char q,r,u,r0;
  r = 0,r0=0;
  x += N4;
  z += N4;

  for (k = N4; k >= 0; k--, x--, z--)
    {
      q = mul[r0][*x][_Q];
      r0 = mul[r0][*x][_R];
      *x = q;

      v = *x - *z;     
      *x = *(_SUBS_YZ+v);
      *(z - 1) = *(z - 1) + (v < 0);
      
      q = mul[r][*x][_Q];
      r = mul[r][*x][_R];
      *x = q;
    }
}

int
main (int argc, char *argv[])
{
  N = 10000;
  setbuf (stdout, NULL);
  set_datasets ();
  calculate ();
  epilog ();
  return 0;
}

void
calculate (void)
{
  int j;

  N4 = N + 4;

  int steps = (N+5) / DIV_UNROLL;
  int rest = (N+5) - steps * DIV_UNROLL;  

  SET (a, 0);
  SET (b, 0);
  for (j = 2 * N4 + 1; j >= 3; j -= 2)
    {
      SET (c, 1);
      LONGDIV (c, j);

      SUBTRACT (a, c, a);
      DIVIDE(a,d25,steps,rest);

      SUBTRACT (b, c, b);
      DIVIDE(b,d239,steps,rest);
      DIVIDE(b,d239,steps,rest);
    }

  for (j=0; j<250; j++)
    {
      printf("........................................");
    }
  printf(".....");
  SET (c, 1);
  SUBTRACT (a, c, a);
  DIVIDE(a,d5,steps,rest);
  SUBTRACT (b, c, b);
  DIVIDE(b,d239,steps,rest);

  /*Loop Fusion, provar-ho al servidor*/
  /*SUBTRACT_MUL(a,b);*/
  MULTIPLY (a);
  SUBTRACT (a, a, b);
  MULTIPLY (a);
}

void
progress (void)
{
  printf (".");
}

void
epilog (void)
{
  int j;
  {
    fprintf (stdout, " \n3.");
    for (j = 1; j <= N; j++)
      {
	fprintf (stdout, "%d", a[j]);
	if (j % 5 == 0)
	  if (j % 50 == 0)
	    if (j % 250 == 0)
	      fprintf (stdout, "    <%d>\n\n   ", j);
	    else
	      fprintf (stdout, "\n   ");
	  else
	    fprintf (stdout, " ");
      }
  }
}

void
set_datasets ()
{
  unsigned r_10, r, x, u, q;
  /*multiply*/
  for (r=0; r<4;r++)
    {
      for ( x=0; x<10; x++)
	{
	  unsigned _q = 4 * x + r;
	  unsigned _r = _q / 10;
	  mul[r][x][_R] = _r;
	  mul[r][x][_Q] = _q - _r * 10;
	  
	}
    }
	 

  /* d239[r][x][_R o _Q] */
  for (r = 0; r < 239; r++)
    {
      r_10 = r * 10;
      for (x = 0; x < 10; x++)
	{
	  u = r_10 + x;
	  q = u / 239;
	  d239[r][x][_R] = u - q * 239;
	  d239[r][x][_Q] = q;
	}
    }

  /* d25[r][x][_r o _q] */
  for (r = 0; r < 25; r++)
    {
      r_10 = r * 10;

      for (x = 0; x < 10; x++)
	{
	  u = r_10 + x;
	  q = u / 25;
	  d25[r][x][_R] = u - q * 25;
	  d25[r][x][_Q] = q;
	}
    }

  /* d5[r][x][_r o _q] */
  for (r = 0; r < 5; r++)
    {
      r_10 = r * 10;

      for (x = 0; x < 10; x++)
	{
	  u = r_10 + x;
	  q = u / 5;
	  d5[r][x][_R] = u - q * 5;
	  d5[r][x][_Q] = q;
	}
    }

}
