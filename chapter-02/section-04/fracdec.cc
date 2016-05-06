/*
ID: min_j
LANG: C++
TASK: fracdec
Date: 04/05/2015
Anaylsis:
  Use the divison algorithm to record the 
  dividing value and once we find that value 
  has already been produced, we know that 
  it will repeat.
*/
#include <stdio.h>
#include <string.h>
using namespace std;
int N,D;

void convert(char *buf, int n){
  if (n == 0){
    buf[0] = '\0';
    return;
  }
  convert(buf, n/10);
  int len = strlen(buf);
  buf[len] = n%10 + '0';
  buf[++len] = '\0';
}

void dec(char *buf, int n, int d){
  convert(buf,n/d);
  int len = strlen(buf);
  if (len == 0)
    buf[len++] = '0';
  buf[len++] = '.';
  if (n%d == 0){
    buf[len++] = '0';
    buf[len] = '\0';
    return;
  }
  int repeatbuf[1000000];
  int reverse[1000000];
  int ri = 0;
  memset(repeatbuf, 0, sizeof(repeatbuf));
  while (n%d != 0){
    n=(n%d)*10;
    if (repeatbuf[n]){
      int i = len++;
      buf[len++] = ')';
      ri--;
      do {
        buf[i] = buf[i-1];
        i--;
      } while (reverse[ri--] != n);
      buf[i] = '(';
      break;
    }
    repeatbuf[n] = 1;
    reverse[ri++] = n;
    buf[len++] = n/d + '0';
  }
  buf[len] = '\0';
}

int main(){
  FILE *fin = fopen("fracdec.in", "r");
  FILE *fout = fopen("fracdec.out", "w");
  fscanf(fin,"%d %d", &N,&D);
  fclose(fin);
  char buf[100000];
  dec(buf,N,D);
  int counter = 0;
  for (int i = 0; i < strlen(buf); i+=76){
    fprintf(fout,"%.76s\n",buf + i);
    
  }
  fclose(fout);
  return 0;
}
