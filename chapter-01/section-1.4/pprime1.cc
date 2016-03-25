/*
ID: min_j
LANG: C++
TASK: pprime
Date: 21/03/2015
Comment: 
Very fast, but very brittle.
Recursively generate odd palindromes, but use
the fact all even digit palindromes greater than 11 are
divisble by 11.
Also special edge case to print 11 after 7.
Rushed so I can sleep.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
unsigned long a, b;
char pal[100];

FILE *fin, *fout;

bool isprime(unsigned long n){
  if (n == 2)
    return true;
  if (n == 3)
    return true;
  if (n % 2 == 0)
    return false;
  if (n % 3 == 0)
    return false;
  int i = 5;p
  int w = 2;
  while (i * i <= n){
    if (n % i == 0)
      return false;
    i+=w;
    w = 6 - w;
  }
  return true;
}

// Note: gpal will not generate palindromes of even digits
// but that is okay since even digit palindromes greater than 11 are
// divisible by 11 (hence not a prime)
void gpal(int idx, int d){
  if (idx == d/2+1){
    int i = idx-1;
    while (idx != d)
      pal[idx++] = pal[--i];
    pal[idx] = '\0';
    unsigned long test = atoi(pal);
    if (a <= test && test <= b && isprime(test)){
      fprintf(fout, "%s\n", pal);
      if (test == 7) // special use case for 11
        fprintf(fout, "%d\n", 11);
    }
    return;
  }
  if (idx == 0)
    for (int i = 1; i <= 9; i+=2){
      pal[idx] = i+'0';
      gpal(idx+1, d);
    }
  else {
    for (int i = 0; i <= 9; i++){
      pal[idx] = i+'0';
      gpal(idx+1, d);
    }
  }
}

int numdigits(unsigned long n){
  char num[100];
  sprintf(num, "%lu", n);
  return strlen(num);
}

int main(){
  fin = fopen("pprime.in", "r");
  fout = fopen("pprime.out", "w");
  fscanf(fin, "%lu%lu", &a, &b);
  fclose(fin);

  int ad = numdigits(a);
  int bd = numdigits(b);
  ad = ad%2 == 0 ? ad+1 : ad;
  bd = bd%2 == 0 ? bd-1 : bd;
  for (int i = ad; i <= bd; i+=2)
    gpal(0, i);

  fclose(fout);
    
  return 0;
}
