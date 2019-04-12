#include <uC++.h>
#include <iostream>
using namespace std;

_Task BoundedBuffer {
  uCondition full, empty;
  int front, back, count;
  int Elements[20];
  public:
    BoundedBuffer() : front(0), back(0), count(0) {}
    _Nomutex int query() { return count; }
    void insert( int elem ) {
      if ( count == 20 ) empty.wait(); // only wait if necessary
      Elements[back] = elem;
    }
    int remove() {
      if ( count == 0 ) full.wait(); // only wait if necessary
      return Elements[front];
    }
  protected:
    void postInsert() {
      back = ( back + 1 ) % size;
      count += 1;
    }
    void postRemove() {
      front = ( front + 1 ) % size;
      count -= 1;
    }
    void main() {
      for ( ;; ) {
        _Accept( insert ) {
          if ( count != 20 ) { // producer did not wait ?
            postInsert();
            if ( ! full.empty() ) { // waiting consumers ?
              full.signal(); // wake and adjust
              postRemove();
            }
          }
        } or _Accept( remove ) {
          if ( count != 0 ) { // consumer did not wait ?
            postRemove();
            if ( ! empty.empty() ) { // waiting producers ?
              empty.signal(); // wake and adjust
              postInsert();
            }
          }
        } //_Accept
      } // for
    }
};

int main() {
  BoundedBuffer bf;
  for (int i = 0; i < 20; i++) {
    bf.insert(i);
  }
  for (int i = 0; i < 5; i++) {
    bf.remove();
  }
  cout << bf.query() << endl;
}