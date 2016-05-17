/*
ID: min_j
LANG: C++
TASK: kimbits
Date: 15/05/2015
Anaylsis:
We know that if 2^L > I, then the I'th number is I-1 (since 0 counts as
the 1st element of set S). If 2^L <= I, then we know the I'th number is greater
than 2^L
*/
#include <cstdio>
#include <cassert>
#include <cmath>
unsigned N,L,I;
int nbits(int n){
  int b = 0;
  while (n){
    n = n&(n-1);
    b++;
  }
  return b;
}

int conv(char *buf, unsigned n, int pad){
  if (n == 0){
    int i = 0;
    for (i = 0; i < pad; ++i)
      buf[i] = '0';
    buf[i] = '\0';
    return i;
  }
  int len = conv(buf,n/2,pad-1);
  buf[len] = "01"[n%2];
  buf[len+1] = '\0';
  return len+1;
}

int main(){
  FILE *fin = fopen("kimbits.in","r");
  FILE *fout = fopen("kimbits.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%u%u%u",&N,&L,&I);
  fclose(fin);
  unsigned n,ith;
  if (I == 1){
    n = 0;
    ith = 1;
  }
  else if (I < (int) pow(2,L)){
    n = I-1;
    ith = I;; //+1 because 0 counts as an element
  }
  else
    if (I >= (int) pow(2,L)){
      n = (int) pow(2,L)-1;
      ith = n+1;
    }
  while (ith < I){  
    if (nbits(++n) <= L)
      ith++;
  }
  char buf[100];
  conv(buf,n,N);
  fprintf(fout,"%s\n",buf);
  fclose(fout);
  return 0;
}
