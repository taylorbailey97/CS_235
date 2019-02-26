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

#ifndef NODE_H
#define NODE_H

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
class node 
{
   public:
   T data;
   node * pNext;
   node * pPrev;
   node() : data(NULL), pNext(NULL), pPrev(NULL) {}
   node(T t) { data = t; pNext = NULL; pPrev = NULL; }
 
};


// /*******************************************************
//  *  NODE: INSERT
//  *****************************************************/
// template <class T>
// node <T> * insert(node <T> * nodePtr, const T & t, bool after = false) throw (const char *)
// {
//    //create a new node and assign the next node value to the passed pointer
//    //assign the value of t to data
//    node <T>* newNode = new node<T>(t);
   
//    //if node is empty
//    if (nodePtr == NULL)
//    {
//        throw "Error: inserting into NULL list.";
//    }   
//    //insert new node before current node
//    if (nodePtr->data != NULL && after == false)
//    {
//        newNode->pNext = nodePtr;
//        newNode->pPrev = nodePtr->pPrev;
//        nodePtr->pPrev = newNode;   
//        if (newNode->pPrev )
//        {
//            newNode->pPrev->pNext = newNode;
//        }
//    }   
//    //insert new node after current node
//    if (nodePtr->data != NULL && after == true)
//    {
//       newNode->pPrev = nodePtr;   
//       // if there is node after nsert, set pNext to point
//       if (nodePtr->pNext)
//       newNode->pNext = nodePtr->pNext;
//       else 
//       newNode->pNext = NULL;   
//       // set pNExt of current node to new node
//       nodePtr->pNext = newNode;   
//       // if there is next element change its pPrev to newNode
//       if(newNode->pNext )
//       {
//           newNode->pNext->pPrev = newNode;
//       }
//    }




//    return newNode;
// }

// /*******************************************************
//  *  NODE: COPY
//  *****************************************************/
// template <class T>
// node <T> *  copy(const node <T>  * nodePtr) throw (const char *) 
// {
//    if (NULL == nodePtr)
//     return NULL;

//    try
//    {
//       //Takes in a pointer to the node that needs to be copied
//       node <T> * pDestination = new node<T>(nodePtr->data);
//       node <T> * pCurrent = pDestination;
      
//       for ( node <T> * p = nodePtr->pNext; p; p = p->pNext)
//       {
//         pCurrent = insert(pCurrent, p->data, true);
//       }
      
//       return pDestination;
//    }
//    catch(bad_alloc)
//    {
//        throw "ERROR: Bad Allocation";
//    }
// }

// /*******************************************************
//  *  NODE: FIND
//  *****************************************************/
// template <class T>
// node <T> * find(node <T> * pHead, const T & t) throw (const char *)
// {
//    //Start at the head and find the node with the value passed with T t
//    for( node <T> * p = pHead; p; p = p->pNext)
//    {
//        if (p->data == t )
//        {
//            return p;
//        }
//    }

//    return NULL;

// }

// /*******************************************************
//  *  NODE: CLEAR
//  *****************************************************/
// template <class T>
// void clear(node <T>* & pHead) throw (const char *)
// {
//     if(pHead == NULL)
//        throw "Error: freeing NULL list.";

//     //Clear data in a given list
//     while (pHead != NULL)
//     {
//         node <T> * pDelete = pHead;
//         pHead = pHead->pNext;
//         delete pDelete;
//     }

//     pHead = NULL;


// }

// /*******************************************************
//  *  NODE: REMOVE
//  *****************************************************/
// template <class T>
// node <T> * remove( node <T> * & nodePtr) throw (const char *)
// {
//    //Deletes the node of the pointer that is passed in and returns a pointer to the prev node
//    if (nodePtr == NULL)
//    {
//       return nodePtr;
//    }

//    if (nodePtr->pPrev)
//    {
//        nodePtr->pPrev->pNext = nodePtr->pNext;
//    }

//    if(nodePtr->pNext )
//    {
//        nodePtr->pNext->pPrev = nodePtr->pPrev;
//    }
   
//    node <T> * pReturn;
//    if (nodePtr->pPrev)
//    {
//        pReturn = nodePtr->pPrev; 
//    }
//    else
//    {
//        pReturn = nodePtr->pNext;
//    }

//    delete nodePtr;
//    nodePtr = NULL;
//    return pReturn;

// }

// /*******************************************************
//  *  NODE: Insertion Operator
//  *****************************************************/
// template <class T>
// ostream & operator << (ostream & out, const node <T> & rhs) throw (const char *)
// {
//    out << rhs.data << endl;
//    return out;
// }


}


#endif