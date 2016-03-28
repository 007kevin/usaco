/*
ID: min_j
LANG: C++
TASK: castle
Date: 27/03/2015
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXM 1000
#define MAXN 50
#define west(x) ((x) & 0x1)
#define north(x) ((x) & 0x2)
#define east(x) ((x) & 0x4)
#define south(x) ((x) & 0x8)
int M, N, num_components;

struct room {
  int size, component;
};
room largest_room;

struct module{
  int w;
  int c;
};
module lcwall, floorplan[MAXN][MAXM];

void flood_fill(int i, int j, int c, int *nmod){
  module *m = &floorplan[i][j];
  if (m->c != 0)
    return;
  m->c = c;
  *nmod = *nmod + 1;
  if (west(m->w) == 0)
    flood_fill(i,j-1,c, nmod);
  if (north(m->w) == 0)
    flood_fill(i-1,j,c, nmod);
  if (east(m->w) == 0)
    flood_fill(i,j+1,c, nmod);
  if (south(m->w) == 0)
    flood_fill(i+1,j,c, nmod);
}

void find_components(){
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      if (floorplan[i][j].c == 0){
        int nmod = 0;
        flood_fill(i,j,++num_components, &nmod);
        if (largest_room.size < nmod){
          largest_room.size = nmod;
          largest_room.component = num_components;
        }
      }
  cout << "number of components: " << num_components << endl;
  cout << "largest room: " << largest_room.size << endl;
}

int main(){
  ifstream fin("castle.in");
  ofstream fout("castle.out");
  fin>>M>>N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      fin>>floorplan[i][j].w;
  fin.close();
  find_components();
  
  
  fout.close();    
  return 0;
}

