/*
ID: min_j
LANG: C++
TASK: butter
Date: 22/05/2015
Anaylsis:
  We will implement the MST to find the min. path
  the cows must walk to the sugar cube.
  How do we deal with pastures where there are no cows?
  -- Changing any element is a MST generally requires complete recalculation.
  -- Approach building of MST with all pastures, but when a non-cow pasture is added
     to the tree, don't include into the total tree sum. BUT from a non-cow pasture node,
     a cow-pasture is added, add what was previously skipped.
*/
#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
#include <vector>
#define MAXP 801
#define infinity INT_MAX
using namespace std;

ifstream fin("butter.in");
ofstream fout("butter.out");
int N,P,C,Walk;
vector<int> tree;
int matrix[MAXP][MAXP];
struct pasture{
  bool c,v;
};
pasture pasture[MAXP];
int pdist(int p1, int p2){
  if (p1 == p2)
    return 0;
  int dist = matrix[p1][p2];
  for (int i = 1; i <= P; ++i)
    if (matrix[p1][i] != infinity &&
        pasture[i].c == false){
      
      };
    }
  if (dist != infinity)
    return matrix[p1][p2] + dist;
  else
    return infinity;
}

int main(){
  fin>>N>>P>>C;
  int n;
  for (int i = 0; i < N; ++i){
    fin>>n;
    pasture[n].c = true;
  }
  // for (int i = 1; i <= P; ++i)
  //   for (int j = 1; j <= P; ++j)
  //     matrix[i][j] = infinity;

  int p1,p2,w;
  for (int i = 0; i < C; ++i){
    fin>>p1>>p2>>w;
    matrix[p1][p2] = w;
  }
  for (int i = 1; i <= P; ++i){
    for (int j =1; j <= P; ++j)
      printf("%d", matrix[i][j]);
    printf("\n");
  }
  printf("%d\n",pdist(2,3));
  // optimize the matrix by replacing weights between cow-containing
  // pastures with possible lower alternative paths that goes
  // through intermediary non-cow pastures. Then the MST algorithm
  // is simplified because we can focus on only the cow-containing
  // pastures for building the tree.
  // int dist;
  // for (int i = 1; i <= P; ++i)
  //   for (int j = 1; j <= P; ++j){
  //     if (pasture[i].c && pasture[j].c){
  //       dist = pdist(i,j);
  //       if (dist < matrix[i][j])
  //         matrix[i][j] = dist;
  //     }
  //   }

  // int f = 0;
  // for (f = 0; f < P; ++f)
  //   if (pasture[f].c) break;
  // pasture[f].v = true;
  // tree.push_back(f);
  // while (tree.size() < C){
  //   int p,min = infinity;
  //   vector<int>::iterator it;
  //   for (it = tree.begin(); it != tree.end(); ++it)
  //     ;
  // }
  
    
    
  fin.close();
  fout.close();
  return 0;
}


