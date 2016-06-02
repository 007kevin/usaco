/*
ID: min_j
LANG: C++
TASK: shopping
Date: 25/05/2016
Anaylsis:
  We use dynamic programming know that the shopping cart has at most
  6^5 different states. By using the set of offers, we build up an 
  optimal combination of offers in the cart matrix.
*/
#include <cstdio>
#include <cassert>
#define MAXS 99
#define MAXC 999
typedef struct {
  int item[5],p;
} special;
special offer[MAXS+1];
int S;

//hold the product code to index mapping for cart
//and vice versa
int index[MAXC+1];
int code[5];
int C;

int purchase[5];
int cart[6][6][6][6][6];

int main(){
  FILE *fin = fopen("shopping.in","r");
  FILE *fout = fopen("shopping.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d",&S);
  int n,c,k,p;
  for (int i = 0; i <= MAXC; ++i) index[i] = -1;
  for (int i = 0; i < S; ++i){
    fscanf(fin,"%d",&n);
    for (int j = 0; j < n; ++j){
      fscanf(fin,"%d%d",&c,&k);
      if (index[c] == -1){
        index[c] = C;
        code[C] = c;
        C++;
      }
      offer[i].item[index[c]] = k;
    }
    fscanf(fin,"%d",&p);
    offer[i].p = p;
  }
  int b=0;
  fscanf(fin,"%d",&b);
  for (int i = 0; i < b; ++i){
    fscanf(fin,"%d%d%d",&c,&k,&p);
    if (index[c] == -1){
      index[c] = C;
      code[C] = c;
      C++;
    }
    purchase[index[c]] = k;
    offer[S].item[index[c]] = 1;
    offer[S].p = p;
    S++;
  }
  // for (int i = 0; i < C; ++i)
  //   printf("%d:%d %d %d\n",i,code[i],index[code[i]],purchase[i]);

  //build dp table
  for (int i = 0; i < S; ++i){
    int a,b,c,d,e;
    a = offer[i].item[0];
    b = offer[i].item[1];
    c = offer[i].item[2];
    d = offer[i].item[3];
    e = offer[i].item[4];
    cart[a][b][c][d][e] = offer[i].p;
  }

  for (int i = 0; i <= purchase[0]; ++i)
    for (int j = 0; j <= purchase[1]; ++j)
      for (int k = 0; k <= purchase[2]; ++k)
        for (int l = 0; l <= purchase[3]; ++l)
          for (int m = 0; m <= purchase[4]; ++m){
            if (cart[i][j][k][l][m] != 0){
              int a,b,c,d,e;
              for (int n = 0; n < S; ++n){
                a = i+offer[n].item[0];
                b = j+offer[n].item[1];
                c = k+offer[n].item[2];
                d = l+offer[n].item[3];
                e = m+offer[n].item[4];
                if (a <= purchase[0] &&
                    b <= purchase[1] &&
                    c <= purchase[2] &&
                    d <= purchase[3] &&
                    e <= purchase[4])
                  if(cart[a][b][c][d][e] == 0 ||
                     cart[i][j][k][l][m]+offer[n].p < cart[a][b][c][d][e])
                    cart[a][b][c][d][e] = cart[i][j][k][l][m]+offer[n].p;
              }
            }
          }
  fprintf(fout,"%d\n",cart[purchase[0]][purchase[1]][purchase[2]][purchase[3]][purchase[4]]);
  
  fclose(fin);
  fclose(fout);
  return 0;
}

