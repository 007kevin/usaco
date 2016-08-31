/*
ID: min_j
LANG: C++
TASK: buylow
Date: 17/08/2016
Anaylsis:
  dp2[i] is the number of unique sequences of length dp1[i] if and only if 
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
//#define DEBUG
#define MAXN 5001
#define max(a,b) ((a) < (b) ? b : a)

class BigNum {
  std::vector<int> N;
public:
  friend std::ostream& operator<<(std::ostream &out, const BigNum &num);  
  BigNum(){ N.push_back(0); }
  BigNum(int n){
    if (n == 0)
      N.push_back(0);
    else
      while(n){ N.push_back(n%10); n/=10; }
  }
  BigNum(std::vector<int> v):N(v){}

  BigNum operator+(BigNum &M){
    std::vector<int> &op1 = this->N.size() >= M.N.size() ? this->N : M.N;
    std::vector<int> &op2 = this->N.size() >= M.N.size() ? M.N : this->N;
    std::vector<int> R(op1.size());
    bool cf = false;
    int b;
    for (int i = 0; i < op1.size(); ++i){
      b = i < op2.size() ? op2[i] : 0;
      R[i] = (op1[i]+b+cf)%10;
      cf = (op1[i]+b+cf > 9) ? true : false;
    }
    if (cf)
      R.push_back(1);
    return BigNum(R);
  }

  void operator+=(BigNum &M){
    *this = *this+M;
  }

  bool operator==(const BigNum &M){
    const std::vector<int> &op1 = this->N;
    const std::vector<int> &op2 = M.N;
    if (op1.size() != op2.size())
      return false;
    for (int i = 0; i < op1.size(); ++i)
      if (op1[i] != op2[i])
        return false;
    return true;
  }

};

std::ostream& operator<<(std::ostream &out, const BigNum &num){
    std::string number = "";
    for (int i = num.N.size()-1; i >= 0 ; --i)
      number+=num.N[i]+'0';
    return out<<number;  
}

using namespace std;

int N;
int seq[MAXN];
int dp1[MAXN]; // let dp1[i] be length of longest sequence ending in seq[i]
BigNum dp2[MAXN]; // let dp2[i] be number of sequences of length dp1[i] ending in seq[i]
int longest;
BigNum num_seq;

int main(){
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  
  for (int i = 0; i < N; ++i)
    fin>>seq[i];

  for (int i = 0; i < N; ++i){
    dp1[i] = 1;
    for (int j = i-1; j >= 0; --j){
      if (seq[j] > seq[i]){
        dp1[i] = max(dp1[i], dp1[j]+1);
      }
    }
    int l = -1;
    for (int j = i-1; j >= 0; --j){
      if (seq[j] > seq[i] &&
          dp1[j]+1 == dp1[i] &&
          seq[j] != l){
        dp2[i]+=dp2[j];
        l = seq[j];
      }
    }
    if (dp2[i] == BigNum(0))
      dp2[i] = BigNum(1);
    
    longest = max(longest, dp1[i]);
  }

  int l = -1;
  for (int i = N-1; i >= 0; --i){
    if (dp1[i] == longest &&
        seq[i] != l){
      num_seq+=dp2[i];
      l = seq[i];
    }
  }
  
// #ifdef DEBUG
//   for (int i = 0; i < N; ++i)
//     cout << seq[i] << "\t";
//   cout << endl;
  
//   for (int i = 0; i < N; ++i)
//     cout << dp1[i] << "\t";
//   cout << endl;

//   for (int i = 0; i < N; ++i)
//     cout << dp2[i] << "\t";
//   cout << endl;
// #endif

  fout << longest << " " << num_seq << endl;
  
  return 0;
}
