/****************************************
** Aimee Sullivan (sullivai)
** CS362-400 Random Testing Quiz 2
** April 30, 2017
**/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int min = 32;
    int max = 125;
    char c = (rand() % (max + 1 - min)) + min;

    return c;
}

char *inputString()
{
    char s[6];
    char c;

    //char *s = malloc(6*sizeof(char));
    int i;
    for (i=0; i<5; i++){
        s[i] = (rand()%(116 + 1 - 101)) + 101;
    }
    s[i] = '\0';
    return strdup(&s[0]);
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
