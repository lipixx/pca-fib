#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define X 200
#define Y 30000000

int min (int x, int y) { return x < y ? x : y; }
int max (int x, int y) { return x < y ? y : x; }
void incr (int *x, int v) { *x += v; }
int square (int x) { return x * x; }



int codiA (int x, int y)
{
  int i;
  int t=0;

  for (i = min (x, y); i < max(x, y); incr(&i, 1))
	t += square (i);

  return t;
}
 
int codiB (int x, int y)
{
  int i;
  int t=0;

  for (i = max (x, y) - 1; i >= min(x, y); incr(&i, -1))
	t += square (i);

  return t;
}

int codiC (int x, int y)
{
  int i;
  int t=0;

  int low = min(x, y);
  int high = max(x, y);

  for (i = low; i < high; incr(&i, 1))
	t += square(i);
  return t;
}
 
 
int main(int argc, char *argv[])
{
    int x=X, y=Y;
    int t, t1, t2;

    if (argc > 2) {
	x = atoi(argv[1]); 
	y = atoi(argv[2]); 
    }

    t = codiA(x,y);
    t1 = codiB(x,y);
    t2 = codiC(x,y);

    printf("%d %d %d\n", t, t1, t2);
    
    return 0;
}
