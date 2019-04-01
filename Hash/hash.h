/***
 * Header:
 *    Linked List
 * Summary:
 *
 *    This will contain the class definition of:
 *       Linked List       : similar to std::Linked list
 * Author
 *    Caleb and Taylor
 **/

#ifndef HASH_H
#define HASH_H

//#include "hash.cpp"
#include "list.h"

namespace custom 
{

template <class T>
class Hash
{
    public:

    //class list;


    Hash(int numBuckets) {
        if (numBuckets >= 1)
        {
            this-> numBuckets = numBuckets;
            numElements = 0;
            table = new list<T>*[numBuckets];
            for (int i = 0; i < numBuckets; i++)
                table[i] = new list<T>();
        }
        else 
        throw "Error: Hashes must have at least 1 bucket.";

    }
    Hash(Hash<T>& rhs) {
        *this = rhs;
    }
    
    ~Hash() {
        for (int i = 0; i < numBuckets; i++) 
        {
            delete table[i];
        }
        delete table;
    }

    Hash<T>& operator = (const Hash<T>& rhs){
        for (int i = 0; i < this->numBuckets; i++)
        {
            delete this->table[i];
        }
        delete this->table;
        numBuckets = rhs.numBuckets;
        numElements = rhs.numElements;
        table = new list<T>*[numBuckets];
        for (int i = 0 ; i < rhs.numBuckets; i++)
        {
            list<T> * temp = rhs.table[i];
            table[i] = temp;
            //delete temp;
        }
        return *this;
    }

    int size() {
        return numElements;
    }
    int capacity() {
        return numBuckets;
    }
    bool empty() {
        return !numElements;
    }

    bool find(T aValue, long (*h)(const T& aValue, long theBucketCount)) {
        
        long bucket = (*h)(aValue, this->numBuckets);
        list<T> * newList = table[bucket];
        if (newList->find(aValue).ptr)
            return newList->find(aValue).ptr->data == aValue;
        else 
            return false;
    }
    void insert(T aValue, long (*h)(const T& valueToHash, long bucketCount)) {
        long bucket = (*h)(aValue, this->numBuckets);
        list<T> * newList = table[bucket];
        newList->insert(newList->end(), aValue);
        this->numElements++;
    }

    list<T>** table;
    int numElements;
    int numBuckets;


};

}

#endif