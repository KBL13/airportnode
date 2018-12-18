#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <list>
#include <vector>
#include <utility>
#include "Queue.h"

using namespace std;

template <typename T>
Queue<T>::Queue()
{
	
}

template <typename T>
Queue<T>::~Queue()
{
    theList.clear();
}

template <typename T>
Queue<T>::Queue(const Queue & rhs) //Copy constructor
{
	
	theList = rhs.theList;
}

template <typename T>
const Queue<T>& Queue<T>:: operator= ( const Queue & rhs ) //Copy assignment operator
{
    Queue copy = rhs;
    std::swap(*this, copy); 
    return *this;
}

template <typename T>
Queue<T>::Queue(Queue && rhs) //Move constructor 
{

	theList = rhs.theList;
	rhs.theList.clear();

}

template <typename T>
Queue<T>& Queue<T>:: operator= (Queue && rhs) // Move assignment operator
{
    std::move(theList, rhs.theList);
        
    return *this;
}

template <typename T>
T& Queue<T>::front()
{
    if(theList.empty())
    {
        throw out_of_range("Error"); //throw out_of_range("Error")
    }
    else
    {
        return theList.front();
    }
}
    
template <typename T>
const T& Queue<T>::front() const
{
    if(theList.empty())
    {
        throw out_of_range("Error"); //throw out_of_range("Error")
    }
    else
    {
        return theList.front();
    }
}

template <typename T>
T& Queue<T>::back()
{
    if(theList.empty())
    {
        throw out_of_range("Error"); //throw out_of_range("Error")
    }
    else
    {
        return theList.back();
    }
}
    
template <typename T>
const T& Queue<T>::back() const
{
    if(theList.empty())
    {
		throw out_of_range("Error"); //throw out_of_range("Error")
    }
    else
    {
        return theList.back();
    }
}

template <typename T>
bool Queue<T>::empty() const
{
    return theList.empty();
}

template <typename T>
int Queue<T>::size()
{
    return theList.size();
}

template <typename T>
void Queue<T>::pop()
{
	theList.pop_front();
}

template <typename T>
void Queue<T>::push(const T& val)
{
	theList.push_back(val);
}

template <typename T>
void Queue<T>::push(T&& val)
{
 	theList.push_back(std::move(val));
}
#endif
