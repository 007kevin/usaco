/*
ID: min_jn
LANG: C++
TASK: contact
Date: 09/05/2015
Anaylsis:

*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAXC 200000
#define MAXB 4096
#define MAXP 12
using namespace std;
int A,B,N,I;
char seq[MAXC];
int sol[12+1][MAXB+1];
struct freq {
  char *s;
  int n;
};
vector<freq> solvec;


int pow(int b,int e){
  int res = 1;
  while (e--)
    res*=b;
  return res;
}

int tonum(char *s,int n){
  int res = 0;
  for (int i = 0; i < n; ++i)
    if (*(s+i) == '1')
      res+=pow(2,n-1-i);
  return res;
}

bool cmp(const freq &a, const freq &b){
  if (a.n == b.n)
    return tonum(a.s,strlen(a.s))  < tonum(a.s,strlen(a.s));
  return a.n > b.n;
}

int conv(char *buf, int n, int bitlen){
  if (n == 0){
    for (int b = 0; b < bitlen; ++b)
      buf[b] = '0';
    buf[bitlen] = '\0';
    return bitlen;
  }
  int len = conv(buf, n/2, bitlen-1);
  buf[len] = "01"[n%2];
  buf[len+1] = '\0';
  return len+1;
}

void solve(){
  for (int i = 0; i < I; ++i){
    for (int j = A; j <= B; ++j)
      if (i+j < I)
        sol[j][tonum(seq+i,j)]++;
  }
}

int main(){
  FILE *fin = fopen("contact.in", "r");
  FILE *fout = fopen("contact.out", "w");
  fscanf(fin,"%d%d%d",&A,&B,&N);
  int c;
  while ((c = fgetc(fin)) != '\n');
  while ((c = fgetc(fin)) != EOF)
    seq[I++] = c;

  solve();
  char buf[100];
  for (int i = 0; i < MAXP+1; ++i)
    for (int j = 0; j < MAXB+1; ++j)
    if (sol[i][j]){
      conv(buf,j,i);
      freq rec;
      rec.s = strdup(buf);
      rec.n = sol[i][j];
      solvec.push_back(rec);
    }
  sort(solvec.begin(),solvec.end(),cmp);
  vector<freq>::iterator vi;
  for (vi = solvec.begin(); vi != solvec.end(); ++vi)
    printf("%s %d\n",vi->s, vi->n);

}
