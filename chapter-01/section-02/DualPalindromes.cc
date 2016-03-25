/*
ID: min_j
LANG: C++
TASK: dualpal
Date: 24/02/2015
Comment:
  Be sure to read problem carefully. Instructions said to only output
  numbers STRICTLY greater than S. In other words, don't print S whether
  or not it is a dual palindrome
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void numbconv(char *s, int n, int b){
  if (n == 0){
    s[0] = '\0';
    return;
  }
  numbconv(s, n/b, b);
  int len = strlen(s);
  s[len++] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[n%b];
  s[len] = '\0';
}

int ispal(char *s){
  for (char *t = s+strlen(s)-1; s < t; s++, t--)
    if (*t != *s) return 0;
  return 1;
}

int main(){
  FILE *fin = fopen("dualpal.in", "r");
  FILE *fout = fopen("dualpal.out", "w");
  int S, N;
  fscanf(fin, "%d %d", &N, &S);
  char s[MAX];
  while (N){
    ++S;
    int count = 0;
    for (int base = 2; base <= 10; ++base){
      numbconv(s, S, base);
      if (ispal(s)) count++;
      if (count == 2){
        fprintf(fout, "%d\n", S);
        N--;
        count = 0;
        break;
      }
    }
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
