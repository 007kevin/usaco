/*
  ID: min_j
  LANG: C++
  TASK: maze1
  Date: 26/04/2015
  Anaylsis:

*/
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

#define MAXW 78
#define MAXH 201
#define infinity INT_MAX
#define m(x) (x)*2+1
int W,H;
char maze[MAXH][MAXW];
int matrix[100*38][100*38];

typedef struct {
  int x,y;
} vertex;

int adjacent(vertex v1, vertex v2){
  

}

int main(){
  FILE *fin = fopen("maze1.in", "r");
  FILE *fout = fopen("maze1.out", "w");
  assert(fin != NULL);
  assert(fout != NULL);
  fscanf(fin,"%d%d",&W,&H);
  while(fgetc(fin) != '\n'); // Because scanf scans until it finds a whitespace character,
                             // the whitespace is left in the buffer. Thus we must read
                             // from input until that whitespace character is read
  // for (int i = 0; i < 2*H+1; ++i)
  //   fgets(&maze[i][0], MAXW, fin);
  // printf("%d\n%d\n%d\n", m(0),m(1),m(2));

  // Fill up adjacency matrix
  for (int i = 0; i < H*W; ++i)
    for (int j = 0; j < H*W; ++j){
      if (i != j){
        vertex v1,v2;
        v1.x = i-(i%H); v1.y = i-(i%W);
        v2.x = j-(j%H); v2.y = j-(j%W);
        if (adjacent(v1,v2))
          matrix[i][j] = 1;
        else
          matrix[i][j] = infinity;
      }
    }


  return 0;
}
