/*
ID: min_j
LANG: C++
TASK: butter
Date: 22/05/2015
Anaylsis:
  For each pasture having at least 1 cow, perform disjtra's algorithm
  to find the minimum total distance walked by the cows.



  Note: A pasture can have more than 1 cow, so if a pasture with two cows
        are added to the tree, the distance is doubled.

  Solved. Writing dijkstra's algorithm with binary heap was interesting.
*/
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#define MAXP 801
#define infinity INT_MAX
using namespace std;

ifstream fin("butter.in");
ofstream fout("butter.out");
int N,P,C;
int pasture[MAXP];
struct node{
  int pasture,dist;
  bool operator<(const node& rhs) const{
    return dist > rhs.dist;
  }
};
map<int,map<int,int> > AL;
map<int,int>::iterator it;

int main(){
  ios::sync_with_stdio(false);   
  fin>>N>>P>>C;
  int n;
  for (int i = 0; i < N; ++i){
    fin>>n;
    pasture[n]++; // Store number of cows per pasture
  }
  int p1,p2,w;
  for (int i = 0; i < C; ++i){
    fin>>p1>>p2>>w;
    // Fill up adjacency list for faster lookup
    AL[p1][p2] = w;
    AL[p2][p1] = w;;
  }
  fin.close();
  
  int sol = infinity;
  int dist[MAXP];
  int visited[MAXP];
  for (int i = 1; i <= P; ++i){
    dist[i] = infinity;
    visited[i] = 0;
  }
  for (int c = 1; c <= P; ++c){
    int walk = 0;
    vector<int> tree;
    priority_queue<node> min;
    dist[c] = 0;
    node source = {c,dist[c]};
    min.push(source);
    while (tree.size() < P){
      node minnode = min.top(); min.pop();
      if(visited[minnode.pasture] == 1)
        continue;
      
      walk+=dist[minnode.pasture]*pasture[minnode.pasture];
      if (walk > sol) break;

      tree.push_back(minnode.pasture);
      visited[minnode.pasture] = 1;
      for (it = AL[minnode.pasture].begin();
           it != AL[minnode.pasture].end();
           ++it){
        if (visited[it->first] == 0)
          if (minnode.dist + it->second < dist[it->first]){
            dist[it->first] = minnode.dist + it->second;
            node n = {it->first, minnode.dist + it->second};
            min.push(n);
          }
      }
    }
    //cout << "----" << endl;
    for (int i = 1; i <= P; ++i){
      //cout << i << ":" << dist[i] << endl;
      dist[i] = infinity;
      visited[i] = 0;
    }
    sol = walk < sol ? walk : sol;
  }
  
  fout << sol << endl;

  fout.close();
  return 0;
}


