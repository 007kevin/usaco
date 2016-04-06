/*
ID: min_j
LANG: C++
TASK: holstein
Date: 04/04/2015
Analysis:
Solution correct, but dfs is too slow thus
fails at running time. Should try implementing
bfs.

Edit: DFS was too slow because I wasn't
adding the next scoop that is greater than the 
previous scoop. Rather, I was only checking if the 
current scoop wasn't already included (via feed_available).
Since the order of scoops doesn't matter, this resulted in
duplicate scoop combinations therefore greatly increasing
the number of current[MAXG] to be tested. 

Was on the right track, just had to change one line ...
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAXV 26
#define MAXVI 1001 //Max vitamin integers
#define MAXG 16

int V, G;
int vitamins[MAXV];
int feeds[MAXG][MAXVI];
int scoops, current[MAXG];
int minscoops, solution[MAXG];

int feed_available(int a){
  for (int i = 1; i <= scoops; ++i)
    if (current[i] == a)
      return 0;
  return 1;
}

// Check if current meets the vitamin requirements
int requirements_met(){
  int vita[V];
  // zero out test array
  for (int i = 1; i <= V; ++i)
    vita[i] = 0;
  // sum current into test array
  for (int i = 1; i <= scoops; ++i)
    for (int j = 1; j <= V; ++j)
      vita[j] += feeds[current[i]][j];
  // compare against vitamins array
  for (int i = 1; i <= V; ++i)
    if (vita[i] < vitamins[i])
      return 0;
  return 1;
}

void solve(){
  if (scoops > minscoops)
    return;
  
  if (requirements_met()){
    // for (int i = 0; i < scoops; ++i)
    //   cout << current[i] + 1 << " ";
    // cout << endl;
    if (scoops < minscoops){
      minscoops = scoops;
      for (int i = 1; i <= scoops; ++i)
        solution[i] = current[i];
    }
    // choose the one with smallest feedtype numbers
    if (scoops == minscoops){
      int s = 0;
      int c = 0;
      for (int i = 1; i <= scoops; ++i){
        s+=current[i];
        c+=solution[i];
      }
      if (c < s){
        for (int i = 1; i <= scoops; ++i)
          solution[i] = current[i];
      }
    }
    return;
  }
  for (int i = 1; i <= G; ++i){
    if (i > current[scoops]){ // if (feed_available(i))
      current[++scoops] = i;
      solve();
      scoops--;
    }
  }
}

int main(){
  ifstream fin("holstein.in");
  ofstream fout("holstein.out");
  fin>>V;
  for (int i = 1; i <= V; ++i)
    fin>>vitamins[i];
  fin>>G;
  for (int i = 1; i <= G; ++i)
    for (int j = 1; j <= V; ++j)
      fin>>feeds[i][j];
  fin.close();
  minscoops = 100000;
  solve();

  fout << minscoops << " ";
  int i; 
  for (i = 1; i < minscoops; ++i)
    fout << solution[i]  << " ";
  fout << solution[i] << endl;


  fout.close();
  return 0;
}
