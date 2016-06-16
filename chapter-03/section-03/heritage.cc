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
  node<T>(T value): left(NULL), right(NULL) {
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
public:
  graph<T>(): head(NULL) {}
  ~graph<T>(){destruct(head);}

  void insert(T value){
    node<T>* cur = head;
    if (cur == NULL)
      cur = new node<T>(value);
    else{
      while (cur->left != NULL)
        cur = cur->left;
      cur->left = new node<T>(value);
    }
  }
  void print(){
    order(head);
  }
  void order(node<T>* n){
    if (n == NULL) return;
    order(n->left);
    cout << n->v << endl;
    order(n->right);
  }
};

int main(){
  ifstream fin("heritage.in");
  ofstream fout("heritage.out");
  assert(fin.is_open());
  assert(fout.is_open());  
  fin>>inorder;
  fin>>preorder;
  fin.close();
  graph<char> btree;
  for (int i = 0; i < inorder.size(); ++i)
    btree.insert(inorder[i]);
  btree.print();

  
  fout.close();
  return 0;
}

