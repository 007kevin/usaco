#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int>& data, int a, int b){
  int tmp = data[a];
  data[a] = data[b];
  data[b] = tmp;
}
// inline quicksort
void quicksort(vector<int>& data, int left, int right){
  if (left >= right)
    return;
  int mid = (left+right)/2;
  swap(data,left,mid);
  int last = left;
  for (int i = left+1; i <= right; ++i)
    if (data[i] < data[left])
      swap(data,i,++last);
  swap(data,left,last);
  quicksort(data,left,last-1);
  quicksort(data,right,last+1);
}

int main(){
  vector<int> data;
  int n;
  while (cin>>n)
    data.push_back(n);
  quicksort(data,0,data.size()-1);
  for (int i = 0; i < data.size(); ++i)
    cout<<data[i] << " ";
  cout<<endl;
  return 0;
}
