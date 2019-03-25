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

#ifndef BNode_H
#define BNode_H

#include <iostream>
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

using namespace std;
namespace custom 
{

template <class T>
class BST
{
   public:

   class BNode;
   class iterator;
   
   BST() : root(NULL), numElements(0) {}
   BST(const BST<T> & rhs) {
      if (rhs.root != NULL) {
         BNode * newNode = new BNode(rhs.root->data);
         this->root = newNode;
         if (rhs.root->pLeft) {
            this->root->pLeft = copyBTree(rhs.root->pLeft);
            this->root->pLeft->pParent = this->root;
         }

         if (rhs.root->pRight) {
            this->root->pRight = copyBTree(rhs.root->pRight);
            this->root->pRight->pParent = this->root;
         }
      }
      else {
         this->root = NULL;
      }
      this->numElements = rhs.numElements;
   }
   ~BST() { clear(); }


   BST <T> operator = (const BST<T> & rhs) {
      BST<T> newTree;
      if (rhs.root) {
         newTree.root = rhs.root;
         newTree.root->pLeft = copyBTree(rhs.root->pLeft);
         if (newTree.root->pLeft) {
            newTree.root->pLeft->pParent = newTree.root;
         }

         newTree.root->pRight = copyBTree(rhs.root->pRight);
         if (newTree.root->pRight) {
            newTree.root->pRight->pParent = newTree.root;
         }
      }
      newTree.numElements = rhs.numElements;
      
      return newTree;
   }

   BNode * copyBTree(const BNode * cNode) throw (const char *) {
      if (cNode == NULL) {
         return NULL;
      }
      BNode * pDest = new BNode(cNode->data);
      pDest->pLeft = copyBTree(cNode->pLeft);

      if (pDest->pLeft) {
         pDest->pLeft->pParent = pDest;
      }

      pDest->pRight = copyBTree(cNode->pRight);
      if (pDest->pRight) {
         pDest->pRight->pParent = pDest;
      }
      return pDest;
      
   }

   ////////////////////////////////////
   // Size
   ////////////////////////////////////
   int size() {
      return this->numElements;
   }

   ////////////////////////////////////
   // Empty
   ////////////////////////////////////
   bool empty() { return !numElements; }
   
   ////////////////////////////////////
   // Clear
   ////////////////////////////////////
   void clear() {
      clearB(root);
   }
   
   void clearB(BNode * node) {
      if (node == NULL) {
         return;
      }
      if (node->pLeft) {
         clearB(node->pLeft);
      }
      if (node->pRight) {
         clearB(node->pRight);
      }
      delete node;
   }

   ////////////////////////////////////
   // Insert
   ////////////////////////////////////
   void insert (const T &t) {
      BNode * cNode = this->root;
      BNode * parent = NULL;

      while (cNode) {
         parent = cNode;
         if (t < cNode->data) {
            cNode = cNode->pLeft;
         } else {
            cNode = cNode->pRight;
         }
      }
      cNode = new BNode(t);
      if (parent == NULL) {
         root = cNode;
      }
      else if (t < parent->data) {
         parent->pLeft = cNode;
         cNode->pParent = parent;
      } else {
         parent->pRight = cNode;
         cNode->pParent = parent;
      }
      numElements++;
   }

   ////////////////////////////////////
   // Erase
   ////////////////////////////////////
   void erase (iterator it) {
      // NO CHILDREN
      if (!it.ptr->pLeft && !it.ptr->pRight) {
         if (it.ptr->pParent->data < it.ptr->data) {
            it.ptr->pParent->pRight = NULL;
         } else {
            it.ptr->pParent->pLeft = NULL;
         }
         delete it.ptr; 
         numElements--;
      }

      // ROOT
      else if (!it.ptr->pParent) {
         BNode * pPred;
         if (it.ptr->pRight->pLeft) {
            pPred = it.ptr->pRight->pLeft;
            pPred->pParent->pLeft = NULL;
            pPred->pRight = it.ptr->pRight;
            pPred->pRight->pParent = pPred;
         } else {
            pPred = it.ptr->pRight;
         }
         pPred->pLeft = it.ptr->pLeft;
         pPred->pLeft->pParent = pPred;
         this->root = pPred;
         delete it.ptr;
         numElements--;
      }

      // LEFT CHILD
      else if (!it.ptr->pRight && it.ptr->pLeft) {
         it.ptr->pLeft->pParent = it.ptr->pParent;
         
         if (it.ptr->pParent && it.ptr->pParent->pRight == it.ptr) {
            it.ptr->pParent->pRight = it.ptr->pLeft;
         }
         
         if (it.ptr->pParent && it.ptr->pParent->pLeft == it.ptr) {
            it.ptr->pParent->pLeft = it.ptr->pLeft;
         }
         
         delete it.ptr;
         numElements--;
      }

      // RIGHT CHILD
      else if (!it.ptr->pLeft && it.ptr->pRight) {
         it.ptr->pRight->pParent = it.ptr->pParent;
         
         if (it.ptr->pParent && it.ptr->pParent->pRight == it.ptr) {
            it.ptr->pParent->pRight = it.ptr->pRight;
         }

         if (it.ptr->pParent && it.ptr->pParent->pLeft == it.ptr) {
            it.ptr->pParent->pLeft = it.ptr->pRight;
         }

         delete it.ptr;
         numElements--;
      }

      // TWO CHILDREN
      else if(it.ptr->pLeft && it.ptr->pRight) {
         //Find x's inorder successor and its parent
         BNode * pNext = it.ptr->pRight;
         it.ptr->pParent = it.ptr;
         while (pNext->pLeft != NULL) {
            it.ptr->pParent = pNext;
            pNext = pNext->pLeft;
         }
         
         //Move contents of next  to Remove and change Remove to apoint to Next, which will be remove
         it.ptr->data = pNext->data;
         it.ptr = pNext;  
         delete it.ptr; 
         numElements--;
      }
      
   }
   
   ////////////////////////////////////
   // Find
   ////////////////////////////////////
   iterator find(const T data) {
      return iterator(findNode(this->root, data));
   }

   BNode * findNode(BNode * cNode, T data) {
      if (!cNode) {
         return NULL;
      }

      if (cNode->data == data) {
         return cNode;
      }

      if (data < cNode->data) {
         findNode(cNode->pLeft, data);
      } else {
         findNode(cNode->pRight, data);
      }
   }
   
   ////////////////////////////////////
   // Begin
   ////////////////////////////////////
   iterator begin()  {
      if (!root) {
         return NULL;
      }
      BNode * pDest = this->root;
      while (pDest->pLeft) {
         pDest = pDest->pLeft;
      }
      return iterator(pDest);
   }
   
   ////////////////////////////////////
   // End
   ////////////////////////////////////
   iterator end() {
      if (!root) {
         return NULL;
      }
      BNode * pDest = this->root;
      while (pDest->pRight) {
         pDest = pDest->pRight;
      }
      return iterator(pDest);
   }


   
   BNode * root;
   int numElements;

};

template <class T>
class BST<T> :: BNode 
{
   public:
   T data;
   BNode * pLeft;
   BNode * pRight;
   BNode * pParent;

   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL),  data(4) {} 
   BNode(T t) : pLeft(NULL), pRight(NULL), pParent(NULL),  data(t) {} 
   
};


template <class T>
class BST <T> :: iterator
{
   public:
   // constructors, destructors, and assignment operator
   iterator()      : ptr(NULL)      {              }
   iterator(BNode * ptr) : ptr(ptr)         {              }
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
   T & operator * () { 
      if (!this->ptr)
         throw "Error: dereferencing null node.";
      return this->ptr->data;
   }
 
   // prefix increment
   iterator operator ++ ()
   {
      if (!this->ptr) {
         throw "Error: incrementing null node.";
      }
      BNode * pPos = new BNode(this->ptr->data);
      if (this->ptr->pRight != NULL) {
         pPos = this->ptr->pRight;
         while (pPos->pLeft)
            pPos = pPos->pLeft;
      } else if (this->ptr->pParent) {
         if (this->ptr->pParent->data > pPos->data)
            pPos = this->ptr->pParent;
         else if (this->ptr->pParent->pParent->data > pPos->data)
            pPos = this->ptr->pParent->pParent;
         else
            pPos = NULL;
      }
      return iterator(pPos);
   }
 
   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      if (!this->ptr) {
         throw "Error: incrementing null node.";
      }
      BNode * pPos = new BNode(this->ptr->data);
      if (this->ptr->pRight != NULL) {
         pPos = this->ptr->pRight;
         while (pPos->pLeft)
            pPos = pPos->pLeft;
      } else if (this->ptr->pParent) {
         if (this->ptr->pParent->data > pPos->data)
            pPos = this->ptr->pParent;
         else if (this->ptr->pParent->pParent->data > pPos->data)
            pPos = this->ptr->pParent->pParent;
         else
            pPos = NULL;
      }
      this->ptr = pPos;
      return tmp;
   }
 
   iterator operator -- ()
   {
      if (!this->ptr) {
         throw "Error: decrementing null node.";
      }
      BNode * pPos = new BNode(this->ptr->data);
      if (this->ptr->pLeft != NULL) {
         pPos = this->ptr->pLeft;
         while (pPos->pRight)
            pPos = pPos->pRight;
      } else if (this->ptr->pParent) {
         if (this->ptr->pParent->data < pPos->data)
            pPos = this->ptr->pParent;
         else if (this->ptr->pParent->pParent->data < pPos->data)
            pPos = this->ptr->pParent->pParent;
         else
            pPos = NULL;
      }
      this->ptr = pPos;
      return *this;
   } 
 
   // postfix increment
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      if (!this->ptr) {
         throw "Error: decrementing null node.";
      }
      BNode * pPos = new BNode(this->ptr->data);
      if (this->ptr->pLeft != NULL) {
         pPos = this->ptr->pLeft;
         while (pPos->pRight)
            pPos = pPos->pRight;
      } else if (this->ptr->pParent) {
         if (this->ptr->pParent->data < pPos->data)
            pPos = this->ptr->pParent;
         else if (this->ptr->pParent->pParent->data < pPos->data)
            pPos = this->ptr->pParent->pParent;
         else
            pPos = NULL;
      }
      this->ptr = pPos;
      return tmp;
   }
   BNode * ptr;
};

}
#endif