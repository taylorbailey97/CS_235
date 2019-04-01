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

#ifndef MAP_H
#define MAP_H

//#include "pair.h"
#include "bst.h"


// Allowing the set-tests file to access private variables
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom 
{

template <class K, class V>
class map
{
   public:
      class pair;
      class iterator;

      map();
      map(const map<K, V>& map);
      ~map();

      map<K, V> operator = (const map<K, V>& rhs);
      V& operator [] (const K& key);
 
      int size();
      bool empty();
      void clear();

      void insert(const K& key, const V& value);
         
      iterator find(const K& key);
      iterator begin();
      iterator end();

      BST<pair> bst;
};


/**********************************************
 * PAIR
 * This class couples together a pair of values, which may be of
 * different types (K and V). The individual values can be
 * accessed through its public members first and second.
 *
 * Additionally, when compairing two pairs, only T1 is compared. This
 * is a key in a name-value pair.
 ***********************************************/
template <class K, class V>
class map<K, V> :: pair
{
public:
   // constructors
   pair()                                    : first(     ), second(      ) {}
   pair(const K & first, const V & second) : first(first), second(second) {}
   pair(const pair & rhs)   : first(rhs.first), second(rhs.second) {}

   // copy the values
   pair & operator = (const pair & rhs)
   {
      first  = rhs.first;
      second = rhs.second;
      return *this;
   }
   
   // compare Pairs. Only first will be compared.
   bool operator >  (const pair & rhs) const { return first >  rhs.first; }
   bool operator >= (const pair & rhs) const { return first >= rhs.first; }
   bool operator <  (const pair & rhs) const { return first <  rhs.first; }
   bool operator <= (const pair & rhs) const { return first <= rhs.first; }
   bool operator == (const pair & rhs) const { return first == rhs.first; }
   bool operator != (const pair & rhs) const { return first != rhs.first; }
   
   // these are public. We cannot validate because we know nothing about T
   K first;
   V second;
};

// /*****************************************************
//  * PAIR INSERTION
//  * Display a pair for debug purposes
//  ****************************************************/
// template <class K, class V>
// inline std::ostream & operator << (std::ostream & out,
//                                    const pair & rhs)
// {
//    out << '(' << rhs.first << ", " << rhs.second << ')';
//    return out;
// }

// /*****************************************************
//  * PAIR EXTRACTION
//  * input a pair
//  ****************************************************/
// template <class K, class V>
// inline std::istream & operator >> (std::istream & in,
//                                    pair & rhs)
// {
//    in >> rhs.first >> rhs.second;
//    return in;
// }






/************************************************************************
* MAPITERATOR: Class used as an iterator for the Map
************************************************************************/
template <class K, class V>
class map<K, V> :: iterator
{
   public:
   iterator() { this->it = NULL; }
   iterator(const typename BST<pair>::iterator& rhs) {
      this->it = rhs;
   }
   iterator(const iterator& rhs) {
      this->it = rhs.it;
   }

   iterator& operator = (const iterator& rhs);
   bool operator == (const iterator& rhs) const;
   bool operator != (const iterator& rhs) const;
   pair& operator * ();
   iterator operator ++ ();
   iterator operator ++ (int postfix);
   iterator operator -- ();
   iterator operator -- (int postfix);

   typename BST<pair>::iterator it;
};


}

#include "map.cpp"

#endif