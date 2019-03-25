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

#ifndef LIST_H
#define LIST_H

#include <cassert>  // because I am paranoid
#include "bst.h"

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

// Allowing the set-tests file to access private variables
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom 
{


template <class T1, class T2>
class map
{
   public:
   class iterator;
   map() : bst(NULL) {}

   map & operator =(const map rhs) {}
   
   int size() {}
   
   bool empty() {}

   void clear() {}

   T2 access(T1 t1) {}

   iterator find(T1 t1) {}

   void insert(T1 t1, T2 t2) {}

   iterator begin() {}

   iterator end() {}

   BST bst;
};
 
/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T1, class T2>
class map <T1, T2> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : ptr(NULL)      {              }
   iterator(const BST :: iterator rhs) : ptr(rhs)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      return *this;
   }
 
   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.ptr != this->ptr; }
   bool operator == (const iterator & rhs) const { return rhs.ptr == this->ptr; }
 
   // dereference operator
    node * & operator * ()       {}
   //const node * & operator * () const { return ptr; }
 
   // prefix increment
   iterator & operator ++ ()     {}
 
   // postfix increment
   iterator operator ++ (int postfix)  {}
 
   iterator & operator -- ()    {}
 
   // postfix increment
   iterator operator -- (int postfix)   {}

   
   iterator :: BST it;
};

}

#endif