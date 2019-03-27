#ifndef MAP_H
#define MAP_H

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

#include "bst.h"

namespace custom
{

   template <class K, class V>
   class map
   {
      public:

         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif

         class pair;
         class iterator;

         map();
         map(const map<K, V>& map);
         ~map();

         map<K, V>& operator = (const map<K, V>& rhs);
         V& operator [] (const K& key);
 
         int size();
         bool empty();
         void clear();

         void insert(const K& key, const V& value);
         
         iterator find(const K& key);
         iterator begin();
         iterator end();

      private:
         BST<pair> bst; 

   };

   template<class K, class V> 
   class map<K, V>::pair
   {
      public:

         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif

         pair();
         pair(const K& key, const V& value);
             
         bool operator == (const pair& rhs) const;
         bool operator != (const pair& rhs) const;
         bool operator > (const pair& rhs) const;
         bool operator < (const pair& rhs) const;
         bool operator >= (const pair& rhs) const;
         bool operator <= (const pair& rhs) const;

         K first;
         V second;

   };

   template<class K, class V> 
   class map<K, V>::iterator   
   {
      public:
         
         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif

         iterator();
         iterator(const typename BST<pair>::iterator& rhs);
         iterator(const iterator& rhs);

         iterator& operator = (const iterator& rhs);
         bool operator == (const iterator& rhs) const;
         bool operator != (const iterator& rhs) const;
         pair& operator * ();
         iterator& operator ++ ();
         iterator operator ++ (int postfix);
         iterator& operator -- ();
         iterator operator -- (int postfix);

      private:
         typename BST<pair>::iterator it;

   };

}

#include "map.cpp"

#endif