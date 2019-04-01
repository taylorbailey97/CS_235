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


template <class T>
class list
{
   public:
   class iterator;
   class node;

   
   list() : pHead(NULL), pTail(NULL), numElements(0) {}

   list(const list & rhs) throw (const char *) {
      if (rhs.numElements < 1) {
         this->pHead = NULL;
         this->pTail = NULL;
         this->numElements = 0;
         return;
      }
      else {
         // this->pHead->data = rhs.pHead->data;
         this->numElements = 0;
         for(node * p = rhs.pTail; p; p = p->pPrev) {
            iterator it = iterator(this->pHead);
            this->insert(it, p->data);
         }

      }
   }

   ~list()
   {
      while (pHead) {
         node * pDelete = pHead;
         pHead = pHead->pNext;
         delete pDelete;
      }
   }

   list & operator =(const list & rhs) {
      //list newList;
      if (rhs.numElements < 1) {
         this->pHead = NULL;
         this->pTail = NULL;
         this->numElements = 0;
         return *this;
      }
      this->clear();
      for(node * p = rhs.pTail; p; p = p->pPrev) {
         iterator it = iterator(this->pHead);
         this->insert(it, p->data);
      }
      return *this;
   }

   int size() { return numElements; }
   bool empty() { return !numElements; }

   void clear() {
      while(pHead) {
         node * pDelete = pHead;
         pHead = pHead->pNext;
         delete pDelete;
         numElements--;
      }
      pTail = pHead;
   }

   void push_back(const T & t) { 
      node * newNode = new node(t);

      if (this->pHead == NULL) {
         this->pHead = newNode;
         this->pTail = newNode;
         numElements++;
         return;
      }
      newNode->pPrev = pTail;
      pTail->pNext = newNode;
      pTail = newNode;
      numElements++;
   }
   void push_front(const T & t) {
      node * newNode = new node(t);
      if (this->pHead == NULL) {
         this->pHead = newNode;
          this->pTail = newNode;
         numElements++;
         return;
      }
      newNode->pNext = pHead;
      pHead->pPrev = newNode;
      pHead = newNode; 
      numElements++;
   }
   void pop_back() { 
      if (pTail) {
         node * pDelete = pTail;
         pTail = pTail->pPrev;
         pTail->pNext = NULL;
         delete pDelete;
         numElements--;
         return;
      }
   }
   void pop_front() { 
      if (pHead) {
         node * pDelete = pHead;
         pHead = pHead->pNext;
         pHead->pPrev = NULL;
         delete pDelete;
         numElements--;
         return;
      }
   }

   T & front() {
      if (!empty()) {
         return pHead->data;
      }
      throw "Error: calling front on empty list.";
   }

   T & back() {
      if (!empty()) {
         return pTail->data;
      }
      throw "Error: calling back on empty list.";
   }

   iterator erase(iterator & it) {
      if (it.ptr == NULL) {
         return it;
         //throw "Error: cannot erase null node";
      }

      if (it.ptr->pPrev) {
         it.ptr->pPrev->pNext = it.ptr->pNext;
      } else {
       pHead = it.ptr->pNext;  
      }

      if (it.ptr->pNext) {
         it.ptr->pNext->pPrev = it.ptr->pPrev;
      } else {
         pTail = it.ptr->pPrev;
      }
      delete it.ptr;

      return it.ptr = pHead;
   }

   void insert(iterator & it, T t) {
   
      node * newNode = new node(t);
      //create a new node and assign the next node value to the passed pointer
      //assign the value of t to data
      //if node is empty
      if (it.ptr == NULL)
      {
         //throw "Error: inserting into NULL list.";
         pHead = newNode;
         pTail = pHead;
         numElements++;
         return;
      }   
      //insert new node before current node
      if (it != NULL)
      {
         newNode->pNext = it.ptr;
         if (it.ptr->pPrev != NULL)
         {
            newNode->pPrev = it.ptr->pPrev;
            newNode->pPrev->pNext = newNode;
         }
         it.ptr->pPrev = newNode;   
         if (it.ptr == pHead) {
            pHead = newNode;
         }
         this->numElements++;
      }   
   }

   iterator find(const T & t) {
      for( node * p = this->pHead; p; p = p->pNext)
      {
          if (p->data == t)
          {
              return iterator(p);
          }
      }
      return NULL;
   }

   iterator begin() {
      return iterator(this->pHead);
   }

   iterator end() {
      return iterator(this->pTail);
   }
   
   //private:
   int numElements;
   node * pHead;
   node * pTail;
};


template <class T>
class list <T> :: node 
{
   public:
   T data;
   node * pNext;
   node * pPrev;
   node() : data(NULL), pNext(NULL), pPrev(NULL) {}
   node(T t) : data(t), pNext(NULL), pPrev(NULL) {}
 
};
 
/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class list <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : ptr(NULL)      {              }
   iterator(node * ptr) : ptr(ptr)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->ptr = rhs.ptr;
      return *this;
   }
 
   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.ptr != this->ptr; }
   bool operator == (const iterator & rhs) const { return rhs.ptr == this->ptr; }
 
   // dereference operator
         node * & operator * ()       { 
            if (ptr) {
               if (!ptr->data)
                  throw "Error: dereferencing null data"; 
               return ptr;
            }
            if (!ptr)
               throw "Error: dereferencing null node.";
         }
   //const node * & operator * () const { return ptr; }
 
   // prefix increment
   iterator & operator ++ ()
   {
      if (!(this->ptr == NULL)) {
         if (this->ptr->pNext)
            this->ptr = this->ptr->pNext;
         return *this;
      }
      throw "Error: incrementing null node.";
   }
 
   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      if (!(ptr == NULL))
      {
         if (this->ptr->pNext)
            this->ptr = this->ptr->pNext;
         return tmp;
      }
      throw "Error: incrementing null node.";
   }
 
   iterator & operator -- ()
   {
      if (!(ptr == NULL)) {
         if (this->ptr->pPrev)
            this->ptr = this->ptr->pPrev;
         return *this;
      }
      throw "Error: decrementing null node.";
   }
 
   // postfix increment
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      if (!(ptr == NULL)) {
         if (this->ptr->pPrev)
            this->ptr = this->ptr->pPrev;
         return tmp;
      }
      throw "Error: decrementing null node.";
   }
   node * ptr;
};


}

#endif