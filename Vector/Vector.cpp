/***********************************************************************
* Program:
*    Checkpoint ###, ????          (e.g. Checkpoint 01a, review)  
*    Brother {Burton, Falin, Ercanbrack, Comeau}, CS165
* Author:
*    your name
* Summary: 
*    Summaries are not necessary for checkpoint assignments.
* ***********************************************************************/

#include <iostream>
#include <Vector.h>
using namespace std;

template<typename T>
Vector<T>::Vector()
{
	this->numCapacity = 0;
}

template<typename T>
Vector<T>::Vector(int numElements)
{
	this->numCapacity = numElements;
	this->numElements = numElements;
}

template<typename T>
Vector<T>::Vector(int numElements, T t)
{
}

template<typename T>
Vector<T>::Vector(Vector rhs)
{
}

template<typename T>
Vector<T>::~Vector()
{
}

template<typename T>
Vector Vector<T>::assign(Vector rhs)
{
	return Vector();
}

template<typename T>
int Vector<T>::size()
{
	return 0;
}

template<typename T>
int Vector<T>::capacity()
{
	return 0;
}

template<typename T>
bool Vector<T>::empty()
{
	return false;
}

template<typename T>
void Vector<T>::clear()
{
}

template<typename T>
void Vector<T>::push_back(T t)
{
}

template<typename T>
T Vector<T>::access(int index)
{
	return T();
}

template<typename T>
Iterator Vector<T>::begin()
{
	return Iterator();
}

template<typename T>
Iterator Vector<T>::end()
{
	return Iterator();
}

template<typename T>
void Vector<T>::resize(int numCapacity)
{
}