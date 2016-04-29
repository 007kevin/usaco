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

#define DEBUG
#define MAXW 38
#define MAXH 100
#define infinity INT_MAX
#define m(x) (x)*2+1
int W,H;
char maze[m(MAXH)][m(MAXW)+1];

typedef struct obj {
  int x,y;
  int visited,dist,parent;
} vertex;

vertex table1[MAXH*MAXW]; // dijkstra's shortest path for exit 1
vertex table2[MAXH*MAXW]; // dijkstra's shortest path for exit 2

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

void dijkstra_SPA(int source, vertex *table){
  int visited = 0;
  while (visited < H*W){
    int dist = infinity;
    for (int i = 0; i < H*W; ++i) // find unvisited vertex with min. dist to source
      if (table[i].visited == 0 && table[i].dist < dist){
        dist = table[i];
    
  }
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

  // Find exits
  int exit[2];
  find(exit);

  // Setup initial state of tables
  for (int i = 0; i < H*W; ++i){
    vertex v;
    v.x = i/W; v.y = i-((i/W)*W);
    v.visited = 0;    
    v.dist = infinity;
    v.parent = -1;
    if (exit[0] == i){
      table2[i] = v;
      v.dist = 0;
      table1[i] = v;
    }
    else if (exit[1] == i){
      table1[i] = v;
      v.dist = 0;
      table2[i] = v;
    }
    else{
      table1[i] = v;
      table2[i] = v;
    }
  }

  dijkstra_SPA(exit[0],table1);
  
#ifdef DEBUG
  for (int i = 0; i < 2*H+1; ++i)
    printf("%s", &maze[i][0]);
  printf("exits %d %d\n",exit[0],exit[1]);
  printf("---- table 1 ----\n");
  printf("node\tvisited\tdist2source\tparent\n");
  for (int i = 0; i < H*W; ++i)
    printf("%d\t%d\t%d\t%d\n",i,table1[i].visited,table1[i].dist,table1[i].parent);
  printf("\n---- table 2 ----\n");
  printf("node\tvisited\tdist2source\tparent\n");
  for (int i = 0; i < H*W; ++i)
    printf("%d\t%d\t%d\t%d\n",i,table2[i].visited,table2[i].dist,table2[i].parent);
#endif
  
  fclose(fin);
  fclose(fout);
  return 0;
}
