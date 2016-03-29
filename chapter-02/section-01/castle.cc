/*
ID: min_j
LANG: C++
TASK: castle
Date: 27/03/2015
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;
#define MAXM 1000
#define MAXN 50
#define west(x) ((x) & 0x1)
#define north(x) ((x) & 0x2)
#define east(x) ((x) & 0x4)
#define south(x) ((x) & 0x8)
int M, N, num_components;
vector<int*> allocated;
struct room {
  int size, component, n, m;
} largest_room;

struct ifroom {
  int size, n, m;
  char w;
} largest_capable_room;

struct module{
  int w;
  int c;
  int v; // visited flag for 'find_largest_creatable' 
  int *size;
};
module lcwall, floorplan[MAXN][MAXM];

void flood_fill(int i, int j, int c, int *size){
  module *m = &floorplan[i][j];
  if (m->c != 0)
    return;
  m->c = c;
  m->size = size;
  (*m->size)++;
  if (west(m->w) == 0)
    flood_fill(i,j-1,c,size);
  if (north(m->w) == 0)
    flood_fill(i-1,j,c,size);
  if (east(m->w) == 0)
    flood_fill(i,j+1,c,size);
  if (south(m->w) == 0)
    flood_fill(i+1,j,c,size);
}

void find_largest_creatable(int i, int j, int c){
  module *m = &floorplan[i][j];
  if (m->v != 0)
    return;
  m->v = 1;
  if (west(m->w) && j != 0 && floorplan[i][j-1].c != c){
    module *nextm = &floorplan[i][j-1];
    int newsize = largest_room.size + *nextm->size;
    if (largest_capable_room.size < newsize){
      largest_capable_room.size = newsize;
      largest_capable_room.n = i;
      largest_capable_room.m = j;
      largest_capable_room.w = 'W';
    }
    else{
      if (largest_capable_room.size == newsize){
        ifroom temp = largest_capable_room;
        if (largest_capable_room.m > j){
          temp.n = i;
          temp.m = j;
          temp.w = 'W';
        }
        if (largest_capable_room.m == j && largest_capable_room.n < i){
          temp.n = i;
          temp.m = j;
          temp.w = 'W';
        }
        largest_capable_room = temp;
      }
    }
  }
  if (north(m->w) && i != 0 && floorplan[i-1][j].c != c){
    module *nextm = &floorplan[i-1][j];
    int newsize = largest_room.size + *nextm->size;
    if (largest_capable_room.size < newsize){
      largest_capable_room.size = newsize;
      largest_capable_room.n = i;
      largest_capable_room.m = j;
      largest_capable_room.w = 'N';
    }
    else{
      if (largest_capable_room.size == newsize){
        ifroom temp = largest_capable_room;
        if (largest_capable_room.m > j){
          temp.n = i;
          temp.m = j;
          temp.w = 'N';
        }
        if (largest_capable_room.m == j && largest_capable_room.n < i){
          temp.n = i;
          temp.m = j;
          temp.w = 'N';
        }
        largest_capable_room = temp;
      }
    }
  }
  if (east(m->w) && j != M-1 && floorplan[i][j+1].c != c){
    module *nextm = &floorplan[i][j+1];
    int newsize = largest_room.size + *nextm->size;
    if (largest_capable_room.size < newsize){
      largest_capable_room.size = newsize;
      largest_capable_room.n = i;
      largest_capable_room.m = j;
      largest_capable_room.w = 'E';
    }
    else{
      if (largest_capable_room.size == newsize){
        ifroom temp = largest_capable_room;
        if (largest_capable_room.m > j){
          temp.n = i;
          temp.m = j;
          temp.w = 'E';
        }
        if (largest_capable_room.m == j && largest_capable_room.n < i){
          temp.n = i;
          temp.m = j;
          temp.w = 'E';
        }
        if (largest_capable_room.m == j && largest_capable_room.n == i &&
            largest_capable_room.w != 'N'){
          temp.n = i;
          temp.m = j;
          temp.w = 'E';
        }
        largest_capable_room = temp;
      }
    }
  }
  if (south(m->w) && i != N-1 && floorplan[i+1][j].c != c){
    module *nextm = &floorplan[i+1][j];
    int newsize = largest_room.size + *nextm->size;
    if (largest_capable_room.size < newsize){
      largest_capable_room.size = newsize;
      largest_capable_room.n = i;
      largest_capable_room.m = j;
      largest_capable_room.w = 'S';
    }
    else{
      if (largest_capable_room.size == newsize){
        ifroom temp = largest_capable_room;
        if (largest_capable_room.m > j){
          temp.n = i;
          temp.m = j;
          temp.w = 'S';
        }
        if (largest_capable_room.m == j && largest_capable_room.n < i){
          temp.n = i;
          temp.m = j;
          temp.w = 'S';
        }
        largest_capable_room = temp;
      }
    }
  }
  if (west(m->w) == 0)
    find_largest_creatable(i, j-1, c);
  if (north(m->w) == 0)
    find_largest_creatable(i-1, j, c);
  if (east(m->w) == 0)
    find_largest_creatable(i, j+1, c);
  if (south(m->w) == 0)
    find_largest_creatable(i+1, j, c);
}

void find_components(){
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      if (floorplan[i][j].c == 0){
        // calloc size variable so that all modules of a component carries its component size
        int *allocated_size = (int*) calloc(1, sizeof(int));
        allocated.push_back(allocated_size);
        flood_fill(i,j,++num_components, allocated_size);
        if (largest_room.size < *floorplan[i][j].size){
          largest_room.n = i;
          largest_room.m = j;
          largest_room.size = *floorplan[i][j].size;
          largest_room.component = num_components;
        }
      }
  find_largest_creatable(largest_room.n,
                         largest_room.m,
                         largest_room.component);
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

  // cout << "number of room: " << num_components << endl;
  // cout << "largest component: " << largest_room.size << endl;
  // cout << "largest capable room: " << largest_capable_room.size << endl;
  // cout << largest_capable_room.n + 1 << " ";
  // cout << largest_capable_room.m + 1 << " ";
  // cout << largest_capable_room.w << endl;

  fout << num_components << endl;
  fout << largest_room.size << endl;
  fout << largest_capable_room.size << endl;
  fout << largest_capable_room.n + 1 << " ";
  fout << largest_capable_room.m + 1 << " ";
  fout << largest_capable_room.w << endl;

  // for (int i = 0; i < N; ++i){
  //   if (i == 0){
  //     for (int i1 = 0; i1 < N; ++i1)
  //       cout << "- ";
  //     cout << endl;
  //   }
  //   for (int j = 0; j < M; ++j){
  //     if (j == 0)
  //       cout << "|";
  //     if (east(floorplan[i][j].w))
  //       cout << "|"; 
  //     if (j == M-1)
  //       cout << "|";
  //     cout << endl;
  //   }
  //   if (i == N-1){
  //     for (int i1 = 0; i1 < N; ++i1)
  //       cout << "- " ;
  //     cout << endl;
  //   }
  // }

  // free allocated memory
  for (vector<int*>::iterator i = allocated.begin(); i != allocated.end(); ++i)
    free(*i);

  // for (int i = 0; i < sizeof(allocated); ++i)
  //   if (allocated[i] != 0)
  //     free(allocated[i]);

  fout.close();    
  return 0;
}

