#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
int N, N4;
unsigned char d239[239][10][2];
unsigned char d25[25][10][2];
unsigned char d5[5][10][2];
unsigned char mul[4][10][2];
char a[10240], b[10240], c[10240];
char SUBS_YZ[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void calculate (void);
void progress (void);
void epilog (void);
void set_datasets(void);

#define DIV_UNROLL 8 /*Best unroll value: 6*/
#define LDIV_UNROLL 8 /*Best unroll value: 4*/
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
  {  int k; unsigned char q, r, u, * addr; char *_x;			\
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
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x);				\
	LDIV_UN(r,u,q,n,x); }				\
    for (k = 0; k < rest; k++, x++) LDIV_UN(r,u,q,n,x);	\
  }							

#define DIVIDE239F(matrix_addr)			\
{ int k;					\
  unsigned q, r, r0, u;				\
  unsigned char *addr;				\
  char *x;					\
  x = matrix_addr;				\
  r = 0, r0=0;					\
  for (k = 0; k <= N4; k++, x++)		\
    {						\
      addr = d239[r][*x];			\
      *x = *(addr + _Q);			\
      r = *addr;				\
      addr = d239[r0][*x];			\
      *x = *(addr + _Q);			\
      r0 = *addr;				\
    }}

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

void
SUBTRACTF (char *x, char *y, char *z)
{
  int j, k;
  unsigned q, r, u;
  char v;
  x += N4;
  y += N4;
  z += N4;

  for (k = N4; k >= 0; k--, x--, y--, z--)
    {
      /*SUBTRACT (a,c,a)*/
      v = *y - *z;     
      *z = SUBS_YZ[v+9];
      *(z - 1) = *(z - 1) + (v < 0);

      /*SUBTRACT (b,c,b)*/
      v = *y - *x;
      *x = SUBS_YZ[v+9];
      *(x - 1) = *(x - 1) + (v < 0);

    }
}

void
SUBTRACT (char *x, char *y, char *z)
{
  int j, k;
  unsigned q, r, u;
  char v;
  x += N4;
  y += N4;
  z += N4;

  for (k = N4; k >= 0; k--, x--, y--, z--)
    {
      v = *y - *z;     
      *x = SUBS_YZ[v+9];
      *(z - 1) = *(z - 1) + (v < 0);
    }
}

void
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
      *x = SUBS_YZ[v+9];
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
  int j, steps, rest;

  N4 = N + 4;

  steps = (N+5) / DIV_UNROLL;
  rest = (N+5) - steps * DIV_UNROLL;

  SET (a, 0);
  SET (b, 0);
  for (j = 2 * N4 + 1; j >= 3; j -= 2)
    {
      SET (c, 1);
      LONGDIV (c, j);
      SUBTRACTF(b,c,a);    
      DIVIDE(a,d25,steps,rest);
      DIVIDE239F(b);
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
