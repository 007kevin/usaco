#include <iostream>
using namespace std;

template <typename T>
struct node {
  T data;
  node<T>* next,prev;
  node(T d): next(NULL) {
    data = d;
  }
};
template <typename T>
class linked_list {
  node<T>* head,tail;
public:
  linked_list(): head(NULL), tail(NULL) {}
  ~linked_list(){
    destroy(head);
  }
  
  void destroy(node<T> *n){
    if (n == NULL) return;
    destroy(n->next);
    delete n;
  }

  void insert(T d){
    if (head == NULL){
      head = new node<T>(d);
      tail = head;
      return;
    }
    node<T> *cur = head;
    while(cur->next != NULL && cur->next->data < d)
      cur = cur->next;
    node<T> *new_node = new node<T>(d);
    new_node->next = cur->next;
    cur->next = new_node;
    if (new_node->next == NULL)
      tail = new_node;
  }
  void print(){
    node<T> *cur = head;
    while(cur != NULL)
      cout << cur->data << " ";
    cout << endl;
  }
};

int main(){

  return 0;
}
