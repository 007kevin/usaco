/*
ID: min_j
LANG: C++
TASK: barn1
Date: 05/03/2015
*/
#include <stdio.h>
#define MAXS 201

typedef struct {
  int o, c;
} stall;

stall stalls[MAXS];

int main(){
  FILE *fin = fopen("barn1.in", "r");
  FILE *fout = fopen("barn1.out", "w");
  int M; // Max # boards
  int S; // Total # stalls
  int C; // # of cows
  int fc = MAXS, lc = 0;
  fscanf(fin, "%d %d %d", &M, &S, &C);
  for (int i = 0; i < S; ++i){
    int tmp;
    fscanf(fin, "%d", &tmp);
    fc = tmp < fc ? tmp : fc;
    lc = tmp > lc ? tmp : lc;
    stalls[tmp].o = 1;
  }
  
  // Start with 1 board covering all required stalls
  for (int i = fc; i <= lc; ++i)
    stalls[i].c = 1;

  int boards = 1;
  while (boards != M){
    // Find biggest gap not covered
    int gap, s1, s2, st;
    gap = s1 = s2 = 0;
    st = fc;
    for (int i = fc+1; i <= lc; ++i){
      if (stalls[i].o){
        int thisgap = i - st - 1;
        if (thisgap > gap && stalls[st+1].c && stalls[i-1].c){
          s1 = st;
          s2 = i;
          gap = thisgap;
        }
        st = i;
      }
    }
    for (int i = s1+1; i < s2; ++i)
      stalls[i].c = 0;
  
    boards++;
  }

  // Find total boards required
  int totalb = 0;
  for (int i = 1; i <= S; ++i)
    totalb+=stalls[i].c;
      
  fprintf(fout, "%d\n", totalb);

  fclose(fin);
  fclose(fout);
  return 0;
}
