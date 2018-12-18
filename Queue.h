#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <list>
#include <vector>
#include <utility>

namespace cop4530
{
template <typename T>
class Queue 
{
public:
    /*// iterator support
    typedef T* iterator;
    typedef const T* const_iterator;***find out to use iterator class or no***/
    
    // constructor, destructor, and copy constructor
    Queue(); // zero parameter constructor. Create an empty qeueu
    ~Queue(); // destructor. De-allocate memory if necessary
    Queue(const Queue &rhs); // copy constructor. Create the new queue with the elements of an exisiting queue rhs.
    Queue(Queue &&rhs); // move constructor. Create the new queue with the elements of an exisiting queue rhs.

    // operators

    // copy assignment operator
    const Queue& operator=(const Queue &rhs);

    // move assignment operator
    Queue& operator=(Queue &&rhs);

    T &front(); // return a reference to the first element in the queue
    const T& front() const;

    T &back(); //return a reference to the last element in the queue
    const T &back() const;

    bool empty() const; // return true if there is no element in the queue; return false otherwise 

    // accessor member functions
    int size(); // return the number of elements in the current queue

    // mutator member functions
    void pop(); // remove the first element in the queue and discard it.   
    void push(const T& val); // add a new element val into the end of the current queue
    void push(T&& val); //add a new element val into the end of the current queue. Val should be moved instead of copied

private:
    std::list<T> theList; //try auto instead of T
    //int theSize;
};

#include "Queue.hpp"
}
#endif