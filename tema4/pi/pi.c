#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
int N, N4;
char a[10240], b[10240], c[10240];
unsigned char d239[239][10][2];
unsigned char d25[25][10][2];
unsigned char d5[5][10][2];
unsigned char mul[4][10][2];
char SUBS_YZ[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char * _SUBS_YZ = SUBS_YZ+10;

#define _R 0
#define _Q 1
void set_datasets ();
void calculate (void);
void progress (void);
void epilog (void);

void
DIVIDE (char *x, unsigned char map[][10][2])
{
  int k;
  unsigned char q, r, u;
  unsigned char *addr;
  r = 0;
  for (k = 0; k <= N4; k++, x++)
    {
      addr = map[r][*x];
      *x = *(addr + _Q);
      r = *addr;
    }
}

void
DIVIDEF (char *x, char *y)
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
      addr = d239[r0][*x];
      *x = *(addr + _Q);
      r0 = *addr;

      addr = d239[r1][*x];
      *x = *(addr + _Q);
      r1 = *addr;

      addr = d25[r2][*y];
      *y = *(addr + _Q);
      r2 = *addr;
    }
}


void
LONGDIV (char *x, int n)
{
  int k;
  unsigned q, r, u;
  
  r = 0;
  for (k = 0; k <= N4; k++, x++)
    {
      u = r * 10 + *x;
      q = u / n;
      r = u - q * n;
      *x = q;
    }
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
      *x = *(_SUBS_YZ+v);
      *(z - 1) = *(z - 1) + (v < 0);
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

  /* SET (c, 1); */
  /* LONGDIV (c, j); */
  /* SUBTRACT (a, c, a); */
  /* DIVIDE(a,d25,steps,rest); */
  /* SUBTRACT (b, c, b);     */
  /* DIVIDE(b,d239,steps,rest); */
  /* DIVIDE(b,d239,steps,rest); */
    
  for (j = 2 * N4 + 1; j >= 3; j -= 2)
    {
      SET (c, 1);
      LONGDIV (c, j);
      SUBTRACT (a, c, a);
      SUBTRACT (b, c, b);
      DIVIDEF(b,a);
    }
  SET (c, 1);
  SUBTRACT (a, c, a);
  DIVIDE (a,d5);
  SUBTRACT (b, c, b);
  DIVIDE (b,d239);
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
