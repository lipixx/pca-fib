#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
int N, N4;
char a[10240], b[10240], c[10240];
unsigned char d239[239][10][2];
unsigned char d25[25][10][2];
unsigned char d5[5][10][2];
unsigned char mul[4][10][2];
char SUBS[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char * _SUBS = SUBS+10;

#define _R 0
#define _Q 1
void set_datasets ();
void calculate (void);
void epilog (void);

void
DIVIDEF_LONGDIV (char *x, char *y, unsigned char map0[][10][2], unsigned char map1[][10][2], char *z, int jj)
{
  /*x=a, y=b*/
  int k;
  unsigned q3, r3, u3;
  unsigned char q, r0,r1,r2, u;
  unsigned char *addr;
  r0 = 0;
  r1 = 0;
  r2 = 0;

  addr = map0[r0][*x];
  *x = *(addr + _Q);
  r0 = *addr;

  addr = map0[r1][*x];
  *x = *(addr + _Q);
  r1 = *addr;

  addr = map1[r2][*y];
  *y = *(addr + _Q);
  r2 = *addr;

  *z++=0;
  r3 = 1;                       

  for (k = 1; k <= N4; k++, x++, y++, z++)
    {
      addr = map0[r0][*x];
      *x = *(addr + _Q);
      r0 = *addr;

      addr = map0[r1][*x];
      *x = *(addr + _Q);
      r1 = *addr;

      addr = map1[r2][*y];
      *y = *(addr + _Q);
      r2 = *addr;

      u3 = r3 * 10; 
      q3 = u3 / jj; 
      r3 = u3 % jj; 
      *z = q3; 
    }
}

void
DIVIDEF (char *x, char *y, unsigned char map0[][10][2], unsigned char map1[][10][2])
{
  /*x=a, y=b*/
  int k;
  unsigned char q, r0,r1,r2, u;
  unsigned char *addr;
  r0 = 0;
  r1 = 0;
  r2 = 0;
  for (k = 0; k <= N4; k++, x++, y++)
    {
      addr = map0[r0][*x];
      *x = *(addr + _Q);
      r0 = *addr;

      addr = map0[r1][*x];
      *x = *(addr + _Q);
      r1 = *addr;

      addr = map1[r2][*y];
      *y = *(addr + _Q);
      r2 = *addr;
    }
}

void
DIVIDEF2 (char *x, char *y, unsigned char map0[][10][2], unsigned char map1[][10][2])
{
  /*x=a, y=b*/
  int k;
  unsigned char q, r0,r1;
  unsigned char *addr;
  r0 = 0;
  r1 = 0;
  for (k = 0; k <= N4; k++, x++, y++)
    {
      addr = map0[r0][*x];
      *x = *(addr + _Q);
      r0 = *addr;

      addr = map1[r1][*y];
      *y = *(addr + _Q);
      r1 = *addr;
    }
}

void
SET (char *x, int n)
{
  memset (x, 0, N4 + 1);
  *x = n;
}

void
SUBTRACTF (char*a,char*c,char*b)
{
  /*x=a, y=b, z=c*/
  /* SUBTRACT (a, c, a); */
  /* SUBTRACT (b, c, b); */

  int j, k;
  unsigned q, r, u;
  char v;
  char carry1=0, carry2=0;

  a += N4;
  c += N4;
  b += N4;
  for (k = N4; k >= 0; k--, a--, b--, c--)
    {
      v = *c - *a - carry1;
      *a = SUBS[v+10];
      carry1 = (v < 0);

      v = *c - *b - carry2;
      *b = SUBS[v+10];
      carry2 = (v < 0);
    }
}

void
LONGDIVF (char *x, int n)
{
  int k;
  unsigned q, r, u;

  /* x[0] = 0; */
  *x++=0;
  r = 1;                       
  /* x++; */

#if 0
  for (k = N4;  k;  --k)
    {
      *x++ = (q = ((u = r * 10) / n)); 
      r = u - (q * n); 
    }
#else
  for (k = 1; k <= N4; k++, x++) 
    { 
      u = r * 10; 
      q = u / n; 
      r = u % n; 
      *x = q; 
    } 
#endif
}

void
SUBTRACT_MUL (char *x, char *z)
{
  int j, k;
  char v;
  unsigned char q,r,u,r0;
  r = 0;
  r0 = 0;
  x += N4;
  z += N4;

  for (k = N4; k >= 0; k--, x--, z--)
    {
      q = mul[r0][*x][_Q];
      r0 = mul[r0][*x][_R];
      *x = q;

      v = *x - *z;     
      *x = SUBS[v+10];
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
  SET (a, 0);
  SET (b, 0);
   
  LONGDIVF (c, 2*N4 + 1);

  for (j = 2 * N4+1; j >= 5; j -= 2)
    {
      SUBTRACTF(a,c,b);
      DIVIDEF_LONGDIV(b,a,d239,d25,c,j-2);
    }

  SUBTRACTF(a,c,b);
  DIVIDEF(b,a,d239,d25);
  SET (c, 1);
  SUBTRACTF(a,c,b);
  DIVIDEF2(a,b,d5,d239);
  SUBTRACT_MUL(a,b);
}

void
epilog (void)
{
  int j,k,n;
  for (j=0; j<125; j++)
    {
      printf("................................................................................");
    }
  printf("..... \n3.");
  
  for (n = 0, j = 1, k = 1; j <= N; j+=5, k++)
    {
      fprintf (stdout, "%d%d%d%d%d", a[j],a[j+1],a[j+2],a[j+3],a[j+4]);
      if (k == 10)
	{
	  k = 0;
	  n += 50;
	  if (n % 250 == 0)
	    fprintf (stdout, "    <%d>\n\n   ", n);
	  else
	    fprintf (stdout, "\n   ");
	}
      else
	fprintf (stdout, " ");
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
	  unsigned _r = _q * 0.1;
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
	  q = u * 0.04;
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
	  q = u * 0.2;
	  d5[r][x][_R] = u - q * 5;
	  d5[r][x][_Q] = q;
	}
    }
}
