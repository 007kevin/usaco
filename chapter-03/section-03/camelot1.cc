/*
ID: min_j
LANG: C++
TASK: camelot
Date: 01/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;
#define infinity INT_MAX
#define max(a,b) (a) < (b) ? b : a
#define min(a,b) (a) < (b) ? a : b
#define MROW 30
#define MCOL 26
int R,C;
int mover[] = {-1,-1,+1,+1,+2,-2,+2,-2};
int movec[] = {+2,-2,+2,-2,-1,-1,+1,+1};
int K,Krow[MROW*MCOL],Kcol[MROW*MCOL]; // King is when K=0
int piece[MROW][MCOL];
int board[MROW][MCOL];

template <typename T>
struct node {
  T data;
  node<T>* next;
  node(T d): next(NULL) {data = d;}
};

template <class T>
class cqueue{
  node<T>* head;
  node<T>* tail;
  void delete_node(node<T>* n){
    if (n == NULL) return;
    delete_node(n->next);
    delete n;
  }
public:
  cqueue(): head(NULL), tail(NULL) {}
  ~cqueue(){
    delete_node(head);
  }
  void push(T item){
    node<T>* n = new node<T>(item);
    if (head == NULL){
      head = n;
      tail = head;
    }
    else{
      tail->next = n;
      tail = n;
    }
  }
  void pop(){
    if (empty())
      return;
    node<T>* n = head->next;
    delete head;
    head = n;
  }
  T front(){
    return head->data;
  }
  bool empty(){
    return head == NULL;
  }
};

struct coord {
  int r,c,d;
  coord(){};
  coord(int row,int col,int dist){
    r = row; c = col; d = dist;
  }
};

void reset(int (*board)[MCOL]){
  for (int i = 0; i < R*C; ++i)
    board[i/C][i%C] = infinity;
}

bool valid(int (*board)[MCOL], int r, int c){
  if (r < 0 || r >= R || c < 0 || c >= C)
    return false;
  return true;
}

int king_from(int r, int c){
  return max(abs(Krow[0]-r),abs(Kcol[0]-c));
}

int bfs_from(int (*board)[MCOL], int r, int c){
  reset(board);
  int knights = 0;
  int gather = 0;
  int minking = king_from(r,c);
  cqueue<coord> Q;
  Q.push(coord(r,c,0));
  while(!Q.empty() && knights < K){
    coord cur = Q.front(); Q.pop();
    if (!valid(board,cur.r,cur.c) ||
        board[cur.r][cur.c] != infinity)
      continue;
    board[cur.r][cur.c] = cur.d;

    //Backtrack from found knight to initial
    //position to track the lowest king steps
    if (piece[cur.r][cur.c] == 1){
      knights++;
      if (minking != 0){
        cqueue<coord> B;
        B.push(cur);
        while(!B.empty()){
          coord back = B.front(); B.pop();
          minking = min(minking,king_from(back.r,back.c));
          for (int i = 0; i < 8; ++i)
            if (piece[back.r+mover[i]][back.c+movec[i]] != 1 &&
                valid(board,back.r+mover[i],back.c+movec[i]) &&
                board[back.r+mover[i]][back.c+movec[i]] == back.d-1 &&
                board[back.r+mover[i]][back.c+movec[i]] != 0)
              B.push(coord(back.r+mover[i],back.c+movec[i],back.d-1));
        }
      }
    }
    for (int i = 0; i < 8; ++i)
      Q.push(coord(cur.r+mover[i],cur.c+movec[i],cur.d+1));
  }
  for (int i = 1; i < K; ++i)
    gather+=board[Krow[i]][Kcol[i]];

  if (minking == infinity || gather == infinity)
    return infinity;
  return minking + gather;
}

void debugprint(int (*board)[MCOL]){
  cout << endl;
  cout << "\t";
  for (int i = 0; i < C; ++i)
    cout << (char) ('A'+i) << "\t";
  cout << endl;
  for (int i = 0; i < R; ++i){
    cout << i+1 << '\t';
    for (int j = 0 ; j < C; ++j){
      if (board[i][j] != infinity)
        cout << board[i][j] << "\t";
      else
        cout << '-' << '\t';
    }
    cout << endl;
  }
}

int main(){
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");
  assert(fin.is_open() && fout.is_open());
  fin>>R>>C;
  int row; char col;
  fin>>col>>row;
  row--; col-='A';
  piece[row][col] = 2;
  Krow[K] = row; Kcol[K] = col;
  K++;
  while (fin>>col>>row){
    row--; col-='A';
    piece[row][col] = 1;
    Krow[K] = row; Kcol[K] = col;
    K++;
  }
  fin.close();
  int solution = infinity;
  for(int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j){
      solution = min(solution,bfs_from(board,i,j));
    }

  fout << solution << endl;

  // debugprint(piece);
  // debugprint(board);

  
  // cqueue<int> test;
  // for (int i = 0; i < 10; ++i)
  //   test.push(i);
  // for (int i = 0; i < 10; ++i){
  //   cout << test.front() << endl;
  //   test.pop();
  // }
  
  fout.close();  
  return 0;
}

