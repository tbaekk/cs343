#ifndef __Q3BUFFER_H__
#define __Q3BUFFER_H__

#include <uC++.h>
#include <queue>
using namespace std;

template<typename T> class BoundedBuffer {
    const unsigned int maxSize;
    queue<T> buffer;
    uOwnerLock lock;
    uCondLock pLock;
    uCondLock cLock;
    bool stopBarging;
  public:
    BoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
};

template<typename T>
BoundedBuffer<T>::BoundedBuffer( const unsigned int size ) : 
    maxSize(size), stopBarging(false) {}

template <typename T>
void BoundedBuffer<T>::insert( T elem ) {
    try {
        lock.acquire();
#if defined( BUSY )
        while ( buffer.size() == maxSize ) {
            pLock.wait(lock);
        }
#elif defined( NOBUSY )
        if ( buffer.size() == maxSize || stopBarging ) {
            pLock.wait(lock);
        } // if
        stopBarging = false;
#else
    #error unknown preprocessor variable ( BUSY | NOBUSY )
#endif // if

        buffer.push(elem);

#if defined( BUSY )
        if ( buffer.size() < maxSize ) {
            cLock.signal();
        } // if
#elif defined( NOBUSY )
        stopBarging = true;
        if ( !cLock.empty() ) {
            cLock.signal();
        } else if ( !pLock.empty() && buffer.size() < maxSize ) {
            pLock.signal();
        } else {
            stopBarging = false;
        } // if
#endif // if
    } catch( ... ) {
    } _Finally {
        lock.release();
    }
}

template <typename T>
T BoundedBuffer<T>::remove() {
    try {
        lock.acquire();
#if defined( BUSY )
        while ( buffer.empty() ) {
            cLock.wait(lock);
        }
#elif defined( NOBUSY )
        if ( buffer.empty() || stopBarging ) {
            cLock.wait(lock);
        } // if
        stopBarging = false;
#else
    #error unknown preprocessor variable ( BUSY | NOBUSY )
#endif // if

        T val = buffer.front();
        buffer.pop();

#if defined( BUSY )
        pLock.signal();
#elif defined( NOBUSY )
        stopBarging = true;
        if ( !pLock.empty() ) {
            pLock.signal();
        } else if ( !pLock.empty() && !cLock.empty() ) {
            cLock.signal();
        } else {
            stopBarging = false;
        } // if
#endif // if
        return val;
    } catch( ... ) {
    } _Finally {
        lock.release();
    }
}

#endif