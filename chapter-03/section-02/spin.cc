/*
ID: min_j
LANG: C++
TASK: spin
Date: 13/05/2015
Anaylsis:
  Making use of arrays of size 360 made it a lot easier
  to process each of the wheel's wedges. Furthermore,
  it seems that if wheel A at wedge from 90 to 270,
  and wheel B has a wedge from 270 to 330,
  there exists a gap at 270. ( This misunderstanding caused
  quite the headache)

  Note the following from the problem:
  "The 'extent' also includes the original "degree" of the wedge,
   so '0 180' means degrees 0..180 inclusive -- one more than 
   most would imagine."
*/
#include <cstdio>
#include <cassert>
#include <cstring>
#define NWHEELS 5
#define MAXWEDGE 5
//#define DEBUG
int counter = 0;
typedef struct {
  int start,extent;
} wedge;
typedef struct {
  int speed,n,cur;
  wedge w[MAXWEDGE];
} wheel;
wheel W[NWHEELS];

int aligned(){
  int alignment[360]; // opaque region
  int cur[360]; // current wheel
  memset(alignment,0,sizeof(alignment));
  for (int i = 0; i < NWHEELS; ++i){
    memset(cur,0,sizeof(cur));  
    for (int j = 0; j < W[i].n; ++j){
      int w1 = (W[i].cur+W[i].w[j].start)%360;
      int w2 = (w1+W[i].w[j].extent)%360;
      
      for (int k = w1; k != w2; k = (k+1)%360)
        cur[k] = 1;
      cur[w2] = 1;
    }
    for (int j = 0; j < 360; ++j)
      if (cur[j] == 0)
        alignment[j] = 1;

#ifdef DEBUG    
    printf("\n");
    for (int j = 0; j < 360; ++j)
      printf("%d",alignment[j]);
    printf("\n");
#endif
  }

#ifdef DEBUG
    for (int i = 0; i < NWHEELS; ++i){
      for (int j = 0; j < W[i].n; ++j){
        int w1 = (W[i].cur+W[i].w[j].start)%360;
        int w2 = (w1+W[i].w[j].extent)%360;
        printf("W:%d\tw1:%d\tw2:%d\n",i,w1,w2);
      }
    }
#endif
  for (int i = 0; i < 360; ++i){
    if (alignment[i] == 0)
      return 1;
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
    for (int j = 0; j < W[i].n; ++j){
      fscanf(fin,"%d %d",&W[i].w[j].start, &W[i].w[j].extent);
    }
  }
  fclose(fin);
 
  while (aligned() == 0){
    rotate();
    counter++;
    if (origin()){
      counter = -1;
      break;
    }
  }
#ifdef DEBUG
  // if (counter != -1)
  //   for (int i = 0; i < NWHEELS; ++i){
  //     for (int j = 0; j < W[i].n; ++j){
  //       int w1 = (W[i].cur+W[i].w[j].start)%360;
  //       int w2 = (w1+W[i].w[j].extent)%360;
  //       printf("W:%d\tw1:%d\tw2:%d\n",i,w1,w2);
  //     }
  //   }
#endif

  if (counter != -1)
    fprintf(fout,"%d\n",counter);
  else
    fprintf(fout,"none\n");
      
  
  fclose(fout);
  
  return 0;
}
