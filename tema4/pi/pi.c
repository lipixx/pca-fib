#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
int N, N4;
char a[10240], b[10240], c[10240];
unsigned char q_d239[239][10];
unsigned char r_d239[239][10];
unsigned char q_d25[25][10];
unsigned char r_d25[25][10];
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
DIVIDEF (char *x, char *y, unsigned char map0[][10], unsigned char map1[][10])
{
  /*x=a, y=b*/
  int k;
  unsigned char q, r0,r1,r2, u;
  unsigned char *addr;
  char xt,yt,xp;

  r0 = 0;
  r1 = 0;
  r2 = 0;
  for (k = 0; k <= N4; k++, x++, y++)
    {
      xt = *x;
      xp = q_d239[r0][xt];
      r0 = r_d239[r0][xt];

      *x = q_d239[r1][xp];
      r1 = r_d239[r1][xp];

      yt = *y;
      *y = q_d25[r2][yt];
      r2 = r_d25[r2][yt];
    }
}

void
DIVIDEF2 (char *x, char *y, unsigned char map0[][10][2], unsigned char map1[][10])
{
  /*x=a, y=b*/
  int k;
  unsigned char q, r0,r1;
  unsigned char *addr;
  char yt;
  r0 = 0;
  r1 = 0;
  for (k = 0; k <= N4; k++, x++, y++)
    {
      addr = map0[r0][*x];
      *x = *(addr + _Q);
      r0 = *addr;
      
      yt = *y;
      *y = q_d239[r1][yt];
      r1 = r_d239[r1][yt];
    }
}

void
LONGDIV (char *x, int n)
{
  int k;
  unsigned q, r, u;
  
  r = 0;

  for (k = N4; k; k--)
    {
      *x++ = (q = ((u=r*10+*x)/n));
      r = u - q * n;
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
  a += N4;
  c += N4;
  b += N4;
  for (k = N4; k >= 0; k--, a--, b--, c--)
    {
      v = *c - *a;
      *a = SUBS[v+10];
      *(a-1) = *(a-1) + (v < 0);

      v = *c - *b;
      *b = SUBS[v+10];
      *(b - 1) = *(b - 1) + (v < 0);
    }
}

void
LONGDIVF (char *x, int n)
{
  int k;
  unsigned q, r, u;

  *x++=0;
  r = 1;                       

  for (k = N4;  k;  --k)
    {
      *x++ = (q = ((u = r * 10) / n)); 
      r = u - (q * n); 
    }
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
    
  for (j = 2 * N4 + 1; j >= 3; j -= 2)
    {
      LONGDIVF (c, j);
      SUBTRACTF(a,c,b);
      DIVIDEF(b,a,q_d239,q_d25);
    }

  SET (c, 1);
  SUBTRACTF(a,c,b);
  DIVIDEF2(a,b,d5,q_d239);
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
	 
  /*d239[x][r][_Q]*/
   for (r = 0; r < 239; r++)
    {
      r_10 = r * 10;
      for (x = 0; x < 10; x++)
	{       
	  u = r_10 + x;
	  q = u / 239;
	  r_d239[r][x] = u - q * 239;
	  q_d239[r][x] = q;
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
	  r_d25[r][x] = u - q * 25;
	  q_d25[r][x] = q;
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
