#include <uC++.h>
#include <iostream>
using namespace std;

_Task BoundedBuffer {
    int front, back, count;
    int Elements[20];
  public:
    BoundedBuffer() : front(0), back(0), count(0) {}
    _Nomutex int query() { return count; }
    void insert( int elem ) {
      Elements[back] = elem;
      back = ( back + 1 ) % 20;
      count += 1;
    }
    int remove() {
      int elem = Elements[front];
      front = ( front + 1 ) % 20;
      count -= 1;
      return elem;
    }
  protected:
    void main() {
      for ( ;; ) { // INFINITE LOOP!!!
        _When ( count != 20 ) _Accept( insert ) { // after call
        } or _When ( count != 0 ) _Accept( remove ) { // after call
        } // _Accept
      }
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