/*
ID: min_j
LANG: C++
TASK: spin
Date: 13/05/2015
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#define NWHEELS 5
#define MAXWEDGE 5
typedef struct {
  int start,extent;
} wedge;
typedef struct {
  int speed,n,cur;
  wedge w[MAXWEDGE];
} wheel;
wheel W[NWHEELS];
int aligned(int s,int e,int n){
  if (n == NWHEELS){
    return 1;
  }
  if (n == 0){
    for (int i = 0; i < W[n].n; ++i)
      if (aligned((W[n].cur+W[n].w[i].start)%360,W[n].w[i].extent,n+1))
        return 1;
  }
  else{
    int a1 = s;
    int a2 = s+e;
    for (int i = 0; i < W[n].n; ++i){
      int w1 = W[n].cur+W[n].w[i].start;
      int w2 = w1+W[n].w[i].extent;
      if (w1 > 360 && w2 > 360){
        w1%=360;
        w2%=360;
      }
      printf("n:%d\ta1:%d\ta2:%d\tw1:%d\tw2:%d\n",n,a1,a2,w1,w2);
      if (a1 <= w1 && w1 < a2){
          int newextent = w2 <= a2 ? w2 - w1 : a2 - w1;
          if (aligned(w1%360,newextent,n+1))
            return 1;
        }
      else
        if (w1 <= a1 && a1 < w2){
          int newextent = a2 <= w2 ? a2 - a1 : w2 - a1;
          if (aligned(a1%360,newextent,n+1))
            return 1;
        }
    }
  }
  return 0;
}

void rotate() {
  for (int i = 0; i < NWHEELS; ++i)
    W[i].cur = (W[i].cur+W[i].speed)%360;
}

int origin() {
  for (int i = 0; i < NWHEELS; ++i)
    if (W[i].cur != 0)
      return 0;
  return 1;
}

int main(){
  FILE *fin = fopen("spin.in","r");
  FILE *fout = fopen("spin.out","w");
  assert(fin != NULL && fout != NULL);
  for (int i = 0; i < NWHEELS; ++i){
    fscanf(fin,"%d %d",&W[i].speed,&W[i].n);
    for (int j = 0; j < W[i].n; ++j)
      fscanf(fin,"%d %d",&W[i].w[j].start, &W[i].w[j].extent);
  }
  fclose(fin);
  int counter = 0;
  
  while (aligned(0,0,0) == 0){
    if (counter == 9)
      break;
    rotate();
    if (origin()){
      fprintf(fout,"none\n");
      break;
    }
    counter++;
  }
  
  for (int i = 0; i < NWHEELS; ++i){
    int w1 = W[i].cur+W[i].w[0].start;
    int w2 = w1+W[i].w[0].extent;
      if (w1 > 360 && w2 > 360){
        w1%=360;
        w2%=360;
      }
    printf("n:%d\ta1:%d\ta2:%d\n",i,w1,w2);
  }

  fprintf(fout,"%d\n", counter);
  fclose(fout);
  
  return 0;
}
