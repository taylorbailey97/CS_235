#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>

template <typename T>
class Vector 
{
private:
    Array<T> array;
    int numElements;
    int numCapacity;
public:
    Vector();
    Vector(int numElements);
    Vector(int numElements, T t);
    Vector(Vector rhs);
    ~Vector();
    Vector assign(Vector rhs);
    int size();
    int capacity();
    bool empty();
    void clear();
    void push_back(T t);
    T access(int index);
    Iterator begin();
    Iterator end();
    void resize(int numCapacity);


};

#endif


