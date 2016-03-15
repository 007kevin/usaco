/*
ID: min_j
LANG: C++
TASK: skidesign
Date: 14/03/2015
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define ST 29
#define END 71

#define MAXN 1000
int N, cost, carryover, hill[MAXN], diff[MAXN], orig[MAXN];

int raised, reduced, cr;

void solve(int lvl){
  int j, remove = 0;
  int level = lvl;
  while(level){
    for (j = N-1; j > 0; j--){
      hill[j]--;
      remove++;
      diff[j]++;
      /*       */
      reduced++;
      /*       */    
      if (hill[j]+1 != hill[j-1]) break;
    }
    
    if (hill[N-1] - hill[0] <= 17){
      for (int a = 0; a < N; ++a){
        cost += diff[a] * diff[a];
        cr += diff[a];
      }
      return;
    }

    level--;
  }
  

  while (remove > 0){
    int i;
    for (i = 0; i < N-1; ++i)
      if (hill[i] != hill[i+1]) break;
    for (i; i >= 0 && remove > 0; i--){
      remove--;
      hill[i]++;
      diff[i]++;
      /*       */      
      raised++;
      /*       */            
    }
    if (hill[N-1] - hill[0] <= 17){
      for (int a = 0; a < N; ++a){
        cost+=diff[a]*diff[a];
        cr += diff[a];
      }
      return;
    }
  }


  // for (int i = 0; i < N; ++i){
  //   if (i == ST){ i = END; cout << "... ";}
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // }
  // cout << endl;

  solve(lvl);
}

void solve1(int lvl){
  while (carryover){
    int c, C;
    for (c = 0; c < N - 1; ++c)
      if (hill[c] != hill[c+1]) break;
    
    for (C = c; C >= 1 && hill[C] == hill[C-1] && carryover > 0; C--){
      carryover--;
      diff[C]++;
      hill[C]++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }

    if (carryover > 0){
      carryover--;
      diff[C]++;
      hill[C]++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }
  }

  if (hill[N-1] - hill[0] <= 17){
    for (int i = 0; i < N; ++i)
      cost += diff[i] * diff[i];
    return;
  }
  
  int i, raise = 0, level = lvl;
  while (level){
  for (i = 0; i < N - 1; ++i)
    if (hill[i] != hill[i+1]) break;
  
  for (int a = 0; a <= i; ++a){
    diff[a]++;
    hill[a]++;
    raise++;
  }
  level--;
  }
  
  int j;
  while (raise > 0){
    int reduce = 0;
    for (j = N-1; j >= 1; --j)
      if (hill[j] != hill[j-1]) break;
    for (int k = j; k < N; ++k){
      diff[k]++;
      hill[k]--;
      reduce++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }
    raise-=reduce;
  }
  carryover += raise*-1;
    
  // for (int i = 0; i < N; ++i)
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // cout << carryover << endl << endl;

  solve1(lvl);
}


int main(void){
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>>orig[i];
  fin.close();
  sort(orig, orig + N);
  for (int i = 0; i < N; ++i)
    hill[i] = orig[i];
  
  // for (int i = 0; i < N; ++i){
  //   if (i == ST){ i = END; cout << "... ";}
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // }
  // cout << endl;
  int min = 1000000;
  for (int i = 1; i < 100; ++i){
    solve(i);
    //cout << cost << " " << i << endl;
    min = cost < min ? cost : min;
    cost = reduced = raised = cr = carryover = 0;
    for (int reset = 0; reset < N; ++reset){
      diff[reset] = 0;
      hill[reset] = orig[reset];
    }
    solve1(i);
    //cout << cost << " " << i << endl;
    min = cost < min ? cost : min;
    cost = reduced = raised = cr = carryover = 0;
    for (int reset = 0; reset < N; ++reset){
      diff[reset] = 0;
      hill[reset] = orig[reset];
    }
  }
  
  // for (int i = 0; i < N; ++i){
  //   if (i == ST){ i = END; cout << "... ";}
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // }
  // cout << endl;

  // cout << "Total removed: " << reduced << endl << "Total raised: " << raised << endl;
  // cout << "Unsquared: " << cr << endl;


  fout<<min<<endl;
  fout.close();
  return 0;
}
