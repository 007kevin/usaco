/*
ID: min_j
LANG: C++
TASK: heritage
Date: 15/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#define MAXL 27;
using namespace std;
string preorder;
string inorder;

template<typename T>
struct node {
  T v;
  node<T>* left;
  node<T>* right;
  node(T value): left(NULL), right(NULL) {
    v = value;
  }
};
template<class T>
class graph {
  node<T>* head;
  void destruct(node<T>* n){
    if (n == NULL) return;
    destruct(n->left);
    destruct(n->right);
    delete n;
  }
  void order(node<T>* n){
    if (n == NULL) return;
    cout << n->v;
    order(n->left);
    order(n->right);
  }
public:
  graph(): head(NULL) {}
  ~graph(){destruct(head);}

  bool setRoot(T value){
    if (head != NULL)
      return false;
    head = new node<T>(value);
    return true;
  }

  node<T>* find(node<T> *n, T value){
    if (n == NULL) return NULL;
    if (n->v == value) return n;
    node<T>* el;
    el = find(n->left, value);
    if (el = find(n->left,  value)) return el;
    if (el = find(n->right, value)) return el;
    return el;
  }
  void insertLeftOf(T target, T value){
    node<T>* el;
    if (el = find(head, target))
      el->left = new node<T>(value);
  }
  void insertRightOf(T target, T value){
    node<T>* el;
    if (el = find(head, target))
      el->right = new node<T>(value);
  }
  
  void print(){
    order(head);
    cout << endl;
  }
};

void buildTree(graph<char>& btree, string L){
  if (L.size() == 0) return;
  int i,j;
  for (i = 0; i < preorder.size(); ++i)
    for (j = 0; j < L.size(); ++j)
      if (preorder[i] == L[j])
        break;
  if (i == 0){
    btree.setRoot(L[j]);
    buildTree(btree,L.substr(0,j);
  }
  
  
}

int main(){
  ifstream fin("heritage.in");
  ofstream fout("heritage.out");
  assert(fin.is_open());
  assert(fout.is_open());  
  fin>>inorder;
  fin>>preorder;
  fin.close();
  graph<char> btree;

  
    
  btree.print();

  
  fout.close();
  return 0;
}

