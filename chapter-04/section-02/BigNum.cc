#include <iostream>
#include <vector>

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
      if (op1[i]+b+cf > 9)
        cf = true;
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

int main(){
  BigNum N(99999);
  BigNum M(1);
  N+=M;
  std::cout << N << std::endl;
  
  return 0;
}
