/*
ID: min_j
LANG: C++
TASK: comehome
Date: 03/05/2015
Anaylsis:
  Use dijkstra's algorithm to solve.
  progess_highlights: 
  - Solved in first attempt againt judge!
  - Wrote dijkstra's alg from memory
*/
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
//#define DEBUG
#define MAXP 10000
#define inf INT_MAX
int P; // number of edges
int N; // number of nodes
struct edge{
  char p1,p2;
  int d;
};
edge list[MAXP];
struct node{
  char p; //parent
  int v,d; // visited, dist2source
};
node nodes[256];
int numnodes[256];

int main(){
  ifstream fin("comehome.in");
  ofstream fout("comehome.out");
  fin >> P;
  for (int i = 0; i < P; ++i){
    fin>>list[i].p1;
    fin>>list[i].p2;
    fin>>list[i].d;
    numnodes[list[i].p1] = 1;
    numnodes[list[i].p2] = 1;
  }
  fin.close();
  for (int i = 0; i < 256; ++i)
    if (numnodes[i]) N++;
  for (int i = 0; i < 256; ++i){
    nodes[i].d = inf;
    nodes[i].p = -1;
  }
  nodes['Z'].d = 0;
  // dijkstra's algorithm
  int visited = 0;
  while (visited < N){
    // find nodes of minimum distance to source
    int min = inf;
    int n = 0;
    for (int i = 0; i < 256; ++i)
      if (numnodes[i] && nodes[i].v == 0 && nodes[i].d < min){
        min = nodes[i].d;
        n = i;
      }
    nodes[n].v = 1;
    visited++;
    for (int i = 0; i < P; ++i){

      if (list[i].p1 == n){
        if (nodes[n].d + list[i].d < nodes[list[i].p2].d){
          nodes[list[i].p2].d = nodes[n].d + list[i].d;
          nodes[list[i].p2].p = n;
        }
      }
      if (list[i].p2 == n){
        if (nodes[n].d + list[i].d < nodes[list[i].p1].d){
          nodes[list[i].p1].d = nodes[n].d + list[i].d;
          nodes[list[i].p2].p = n;
        }
      }
    }
  }
  
#ifdef DEBUG
  printf("node\tvisited\tdist\tparent\n");
  for (int i = 0; i < 256; ++i)
    if (numnodes[i] == 1)
      printf("%c\t%d\t%d\t%d\n",(char) i, nodes[i].v,nodes[i].d,nodes[i].p);
  printf("\n");
#endif
  
  int min = inf;
  int n;
  for (int i = 0; i < 256; ++i)
    if (numnodes[i] &&
        i != 'Z' &&
        'A' <= (char) i && (char) i <= 'Z' &&
        nodes[i].d < min){
      min = nodes[i].d;
      n = i;
    }
  fout << (char) n << " " <<  min << endl;
  fout.close();
}
