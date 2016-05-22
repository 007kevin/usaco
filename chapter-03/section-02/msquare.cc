/*
ID: min_j
LANG: C++
TASK: msquare
Date: 18/05/2015
Anaylsis:
  We could recursively attempt to solve this solution while memoizing 
  configurations to prune the recursive tree.
  We use bfs.
  
  ** Develop trie datastructure for memoizing permutations **
  Note: There are 8! = 40320 different permutations

*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

#define SIZE 8
string init = "12345678";
string target = "";
string solution;
/***** TRIE Datastructure *****/
typedef struct node{ 
  char n;
  node *sib, *next;
} node;

node *HEAD;
node* insert(node *ptr, const char *perm, int size){
  if (size == 0)
    return NULL;
  if (ptr == NULL){
    ptr = (node*) calloc(1,sizeof(node));
    ptr->sib=ptr->next=NULL;
    ptr->n = *perm;
  }
  node *cur = ptr;
  while (cur->sib != NULL && cur->n != *perm){
    cur = cur->sib;
  }
  if (cur->n == *perm)
    cur->next = insert(cur->next, perm+1, size-1);
  else
    cur->sib = insert(cur->sib, perm, size);
  return ptr;
}

int find(node *ptr,const char *perm, int size){
  if (size == 0)
    return 1;
  node *cur = ptr;
  while(cur != NULL){
    if (cur->n == *perm){
      return find(cur->next,perm+1,size-1);
    }
    cur = cur->sib;
  }
  return 0;
}

void release_mem(node *ptr){
  if (ptr == NULL)
    return;
  release_mem(ptr->sib);
  release_mem(ptr->next);
  free(ptr);
}
/******************************/

string moveA(string cur){
  string res = "";
  for (int i = 7; i >=0; --i)
    res+=cur[i];
  return res;
}

string moveB(string cur){
  string res = "";
  res+= cur[3];
  res+=cur.substr(0,3);
  res+=cur.substr(5,3);
  res+=cur[4];
  return res;
}

string moveC(string cur){
  string res = cur;
  res[1] = cur[6];
  res[2] = cur[1];
  res[5] = cur[2];
  res[6] = cur[5];
  return res;
}

void solve(){
  queue<pair<string,string> > bfs;
  bfs.push(pair<string,string>(init,""));
  HEAD = insert(HEAD,init.c_str(),SIZE);  
  pair<string,string> cur;
  string next,path;
  while (true){
    cur = bfs.front();
    bfs.pop();
    if (cur.first.compare(target) == 0){
      solution = cur.second;
      return;
    }
    next = moveA(cur.first);
    path = cur.second+"A";
    if (find(HEAD,next.c_str(),SIZE) == 0){
      insert(HEAD,next.c_str(),SIZE);
      bfs.push(pair<string,string>(next,path));
    }
    next = moveB(cur.first);
    path = cur.second+"B";
    if (find(HEAD,next.c_str(),SIZE) == 0){
      insert(HEAD,next.c_str(),SIZE);
      bfs.push(pair<string,string>(next,path));
    }
    next = moveC(cur.first);
    path = cur.second+"C";
    if (find(HEAD,next.c_str(),SIZE) == 0){
      insert(HEAD,next.c_str(),SIZE);
      bfs.push(pair<string,string>(next,path));
    }
  }
}

int main(){
  FILE *fin = fopen("msquare.in","r");
  FILE *fout = fopen("msquare.out","w");
  assert(fin != NULL && fout != NULL);
  char c;
  for (int i = 0; i < SIZE; ++i){
    fscanf(fin,"%c ", &c);
    target+=c;
  }
  fclose(fin);

  solve();
  
  fprintf(fout,"%lu\n%s\n",solution.size(),solution.c_str());
  
  release_mem(HEAD);
  fclose(fout);        
  return 0;
}
