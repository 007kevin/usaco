/*
ID: min_j
LANG: C++
TASK: wormhole
Date: 10/03/2015
*/
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

typedef struct {
  unsigned long x,y;
} coord;

typedef struct wpair{
  coord c1,c2;
  bool operator <(const wpair &rhs) const {
    return (c1.x < rhs.x && c1.y <= rhs.y) ||
                   ()
                   ;
                   
  }
} wpair;


set<wpair> pp;

int main(){
  ifstream fin("wormhole.in");
  ofstream fout("wormhole.out");
  int N;
  fin >> N;
  coord w[N];
  for (int i = 0; i < N; ++i)
    fin>>w[i].x>>w[i].y;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j){
      if (i != j){
        wpair p = {{w[i].x, w[i].y},{w[j].x,w[j].y}};
        // pp.insert(p);
      }
    }

  
  
      
}
