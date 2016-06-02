/*
ID: min_j
LANG: C++
TASK: fence
Date: 24/05/2016
Anaylsis:
  A graph has an Eulerian tour/path if and only if it is connected
  and every node except two has even degree. The nodes of odd degrees
  must be the start and end node. Therefore, for us to find the Eulerian
  fence path, always start on the lesser numbered node so that we get
  the smallest magnitude base 500 number

  Note: Two intersections can have many fences betwee them
*/
#include <cstdio>
#include <cstring>
#define MAXF 1024
#define MAXI 500
#define min(a,b) (a) < (b) ? a : b
#define max(a,b) (a) > (b) ? a : b
int F;
int minI=MAXI,maxI;
int degree[MAXI];
int matrix[MAXI+1][MAXI+1];
int I,path[MAXF+2];

void find_eulerian_path(int node){
  for (int i = 1; i <= maxI; ++i){
    if (matrix[node][i]){
      matrix[node][i]--;
      matrix[i][node]--;
      find_eulerian_path(i);
    }
  }
  path[I++] = node;
}

int main(){
  FILE *fin = fopen("fence.in","r");
  FILE *fout = fopen("fence.out","w");
  fscanf(fin,"%d",&F);
  int a,b;
  for (int i = 0; i < F; ++i){
    fscanf(fin,"%d %d",&a,&b);
    degree[a]++;
    degree[b]++;
    minI=min(a,minI);
    minI=min(b,minI);
    maxI=max(a,maxI);
    maxI=max(b,maxI);    
    matrix[a][b]++;
    matrix[b][a]++;    
  }
  // start algorithm on lowest numbered node of odd degree.
  // If all nodes are found to be of even degree, we know
  // that we have an Eulerian circuity
  int s;
  for (s = 1; s <= maxI; ++s)
    if (degree[s]%2 == 1) break;
  if (s > maxI) // found Eulerian circuit
    s = minI;

  find_eulerian_path(s);
  for (int i = I-1; i >= 0; --i)
    fprintf(fout,"%d\n",path[i]);

  
  return 0;
}
