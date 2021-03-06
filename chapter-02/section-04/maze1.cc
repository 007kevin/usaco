/*
ID: min_j
LANG: C++
TASK: maze1
Date: 26/04/2015
Anaylsis:
  Although this solution is also correct, we could
  have solved this problem with the flood fill algorithm

*/
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <algorithm>

//#define DEBUG
#define MAXW 38
#define MAXH 100
#define infinity INT_MAX
#define m(x) ((x)*2+1)
int W,H;
char maze[m(MAXH)+5][m(MAXW)+5];

typedef struct obj {
  int x,y,id;
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

vertex convert(int i){
  vertex v;
  v.x = i/W;
  v.y = i - ((i/W)*W);
  return v;
}

void find(int *exit){
  int e = 0;
  vertex v;
  for (int i = 0; i < H*W; ++i){
    vertex v = convert(i);
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

void dijkstra_SPA(vertex *table){
  // Keep loops until all verticies have been visited
  while (true){
    vertex *v = NULL;
    for (int i = 0; i < H*W; ++i) // find unvisited vertex with min. dist to source
      if (table[i].visited == 0 && (v == NULL || table[i].dist < v->dist)){
        v = table+i;
      }
    if (v == NULL) break;
    v->visited = 1;
    // Find adjacent vertices of the visiting vertex.
    // We know a given square can be at most adjacent to
    // four other squares
    if (v->id+1<H*W && adjacent(*v,table[v->id+1])){
      if (add(v->dist,1) < table[v->id+1].dist){
        table[v->id+1].dist = add(v->dist,1);
        table[v->id+1].parent = v->id;
      }
    }
    if (v->id-1>=0 && adjacent(*v,table[v->id-1]))
      if (add(v->dist,1) < table[v->id-1].dist){
        table[v->id-1].dist = add(v->dist,1);
        table[v->id-1].parent = v->id;
      }
    if (v->id-W>=0 && adjacent(*v,table[v->id-W]))
      if (add(v->dist,1) < table[v->id-W].dist){
        table[v->id-W].dist = add(v->dist,1);
        table[v->id-W].parent = v->id;
      }
    if (v->id+W<H*W && adjacent(*v, table[v->id+W]))
      if (add(v->dist,1) < table[v->id+W].dist){
        table[v->id+W].dist = add(v->dist,1);
        table[v->id+W].parent = v->id;
      }
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
  for (int i = 0; i < m(H); ++i)
    fgets(&maze[i][0], m(W)+5, fin);

  // Find exits
  int exit[2];
  exit[0] = exit[1] = -1;
  find(exit);
  if (exit[1] == -1)
    exit[1] = exit[0];

  // Setup initial state of tables
  for (int i = 0; i < H*W; ++i){
    vertex v = convert(i);
    v.id = i;
    v.visited = 0;    
    v.dist = infinity;
    v.parent = -1;
    if (exit[0] == i){
      table2[i] = v;
      v.dist = 0;
      table1[i] = v;
    }
    if (exit[1] == i){
      table1[i] = v;
      v.dist = 0;
      table2[i] = v;
    }
    else{
      table1[i] = v;
      table2[i] = v;
    }
  }

  dijkstra_SPA(table1);
  dijkstra_SPA(table2);
  
  int sol[H*W];
  for (int i = 0; i < H*W; ++i)
      sol[i] = table1[i].dist < table2[i].dist ? table1[i].dist : table2[i].dist;

  std::sort(sol,sol+H*W);

#ifdef DEBUG
  for (int i = 0; i < m(H); ++i)
    printf("%s", &maze[i][0]);
  printf("exits %d %d\n",exit[0],exit[1]);
  printf("---- table 1 ----\n");
  printf("node\tvisited\tdist2source\tparent\n");
  for (int i = 0; i < H*W; ++i)
    printf("%d\t%d\t%d\t%d\n",table1[i].id,table1[i].visited,table1[i].dist,table1[i].parent);
  printf("\n---- table 2 ----\n");
  printf("node\tvisited\tdist2source\tparent\n");
  for (int i = 0; i < H*W; ++i)  
    printf("%d\t%d\t%d\t%d\n",table1[i].id,table1[i].visited,table1[i].dist,table1[i].parent);
#endif

  // we add one to solution for the last step of moving out of the maze  
  fprintf(fout,"%d\n",sol[H*W-1]+1);
  
  fclose(fin);
  fclose(fout);
  return 0;
}
