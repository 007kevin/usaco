#include <iostream>
#include <vector>
#include <climits>
#define infinity INT_MAX
using namespace std;

int indexOf(vector<int> V,int i){
  if (i >= V.size())
    return infinity;
  return V[i];
}

vector<int> mergesort(vector<int>& list, int left, int right){
  if (left == right)
    return vector<int>(1,list[left]);
  int mid = (left+right)/2;
  vector<int> A = mergesort(list,left,mid);
  vector<int> B = mergesort(list,mid+1,right);
  vector<int> C(A.size()+B.size());
  int ai = 0;
  int bi = 0;
  for (int i = 0; i < C.size(); ++i){
    if (indexOf(A,ai) < indexOf(B,bi))
      C[i] = A[ai++];
    else
      C[i] = B[bi++];
  }
  return C;
}

int main(){
  vector<int> list;
  int n;
  while(cin>>n)
    list.push_back(n);
  vector<int> sorted = mergesort(list,0,list.size()-1);
  for (int i = 0; i < sorted.size(); ++i)
    cout<<sorted[i]<<" ";
  cout<<endl;
}
