/*
ID: min_j
LANG: C
TASK: maze1
Date: 26/04/2015
Anaylsis:
  Problem set too large to implement floyd warshall alg. 
  (3500 vertices to power of 3 is too big of a run time O(n^3)).
  We must use dijkstra's algorithm instead. That means first
  finding the farthest vertex from the exit vertices and performing
  d.a on them O(n^2)
*/
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#define DEBUG
#define MAXW 78
#define MAXH 201
#define infinity INT_MAX
#define m(x) (x)*2+1
int W,H;
char maze[MAXH][MAXW];
int matrix[3800][3800];

typedef struct obj {
  int x,y;
} vertex;

int adjacent(vertex v1, vertex v2){
  int res = 0;
  if ((v1.x == v2.x && v1.y < v2.y && v2.y - v1.y == 1 && maze[m(v1.x)][m(v1.y)+1] == ' ') ||
      (v1.x == v2.x && v1.y > v2.y && v1.y - v2.y == 1 && maze[m(v1.x)][m(v1.y)-1] == ' ') ||
      (v1.y == v2.y && v2.x > v1.x && v2.x - v1.x == 1 && maze[m(v1.x)+1][m(v1.y)] == ' ') ||
      (v1.y == v2.y && v2.x < v1.x && v1.x - v2.x == 1 && maze[m(v1.x)-1][m(v1.y)] == ' '))
    res = 1;
  //  printf("{%d,%d}{%d,%d}  %d\n", v1.x,v1.y,v2.x,v2.y,res);
  return res;
}

void find(int *exit){
  int e = 0;
  vertex v;
  for (int i = 0; i < H*W; ++i){
    v.x = i/W; v.y = i - ((i/W)*W);
    if (v.x == 0   && maze[m(v.x)-1][m(v.y)] == ' ') exit[e++] = i;
    if (v.x == H-1 && maze[m(v.x)+1][m(v.y)] == ' ') exit[e++] = i;
    if (v.y == 0   && maze[m(v.x)][m(v.y)-1] == ' ') exit[e++] = i;
    if (v.y == W-1 && maze[m(v.x)][m(v.y)+1] == ' ') exit[e++] = i;    
  }
}

int add(int a, int b){
  if (a == infinity || b == infinity)
    return infinity;
  else
    return a+b;
}

void floydwarshall(){
  for (int k = 0; k < H*W; ++k)
    for (int i = 0; i < H*W; ++i)
      for (int j =0; j < H*W; ++j)
        if (add(matrix[i][k],matrix[k][j]) < matrix[i][j])
          matrix[i][j] = add(matrix[i][k],matrix[k][j]);
}

int main(){
  FILE *fin = fopen("maze1.in", "r");
  FILE *fout = fopen("maze1.out", "w");
  assert(fin != NULL);
  assert(fout != NULL);
  fscanf(fin,"%d %d",&W,&H);
  
  // Edge case
  if (H == 1 && W == 1){
    fprintf(fout,"%d\n",1);
    fclose(fout);
    return 0;
  }
  
  while(fgetc(fin) != '\n'); // Because scanf scans until it finds a whitespace character,
                             // the whitespace is left in the buffer. Thus we must read
                             // from input until that whitespace character is read
  for (int i = 0; i < 2*H+1; ++i)
    fgets(&maze[i][0], MAXW, fin);

  // Fill up adjacency matrix;
  for (int i = 0; i < H*W; ++i)
    for (int j = 0; j < H*W; ++j){
      if (i != j){
        vertex v1,v2;
        v1.x = i/W; v1.y = i-((i/W)*W);
        v2.x = j/W; v2.y = j-((j/W)*W);
        //        printf("%d:%d\t", i,j);
        if (adjacent(v1,v2))
          matrix[i][j] = 1;
        else
          matrix[i][j] = infinity;
      }
    }

  floydwarshall();

  // Find exits
  int exit[2];
  find(exit);
  
#ifdef DEBUG
  printf("%d %d\n",exit[0],exit[1]);
#endif

  // Get min path to exits
  int sol = 0;
  for (int i = 0; i < H*W; ++i){
    int p = matrix[i][exit[0]] < matrix[i][exit[1]] ? matrix[i][exit[0]] : matrix[i][exit[1]];
    sol = p > sol ? p : sol;
  }

  fprintf(fout, "%d\n", sol + 1);

#ifdef DEBUG
  for (int i = 0; i < 2*H+1; ++i)
    printf("%s", &maze[i][0]);

  for (int i = 0; i < H*W; ++i){
    for (int j = 0; j < H*W; ++j){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("solution: %d\n", sol + 1);
#endif
  
  fclose(fin);
  fclose(fout);
  return 0;
}
