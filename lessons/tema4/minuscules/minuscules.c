#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



#define MAX_CHAR (1<<20)

int strlen (char *s)
{
	int len = 0;

	while (*s != 0) {
		s++;
		len++;
	}
	return len;
}

/* convertir una cadena de caràcters a minuscules */
void lowercase (char *s)
{
	int i;
       	char mi = 'A' - 'a';
	int sl = strlen(s);
	for (i = 0; i < sl; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] -= (mi);
		}
	}
}

void generateSentence(char *s, int n_car)
{
   int i;
   char mi = '\0' + 1;

   for (i=0; i<n_car; i++)
   {
      s[i]=(rand()&127)+mi;
   }
   s[i]='\0';
}



 
int main(int argc, char *argv[])
{
    int n_car=MAX_CHAR;
    char SENTENCE[MAX_CHAR+1];

    if (argc > 1) {
	n_car = atoi(argv[1]); 
    }

    generateSentence(SENTENCE, n_car);

    lowercase(SENTENCE);

    //write(0,SENTENCE,MAX_CHAR+1);
    return 0;
}
