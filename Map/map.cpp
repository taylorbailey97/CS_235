#include "map.h"

using namespace custom;

template <class K, class V>
map<K, V> :: map() {
    this->bst = BST<pair>();
}

template <class K, class V>
map<K, V> :: map(const map<K, V>& map) {
    this->bst = map.bst;
}

template <class K, class V>
map<K, V> :: ~map() {

}

template <class K, class V>
map<K, V> map<K, V> :: operator = (const map<K, V>& rhs) {
    this->bst = BST<pair>(rhs.bst);
    return *this;
}

template <class K, class V>
V& map<K, V> :: operator [] (const K& key) {
    pair p = pair(key, V());
    typename BST<pair>::iterator it = this->bst.find(p);
    if (it != NULL) {
       return it.ptr->data.second;
    } else {
       this->bst.insert(p);
       return this->bst.find(p).ptr->data.second;
    }
}

template <class K, class V>
int map<K, V> :: size() {
    return this->bst.size();
}

template <class K, class V>
bool map<K, V> :: empty() {
    return this->bst.empty();
}

template <class K, class V>
void map<K, V> :: clear() {
    this->bst.clear();
}

template <class K, class V>
void map<K, V> :: insert(const K& key, const V& value) {
    map<K, V> :: pair newPair(key, value);
    iterator it = iterator(this->bst.find(newPair));
    if (it) {
       *it = newPair;
    } else {
       this->bst.insert(newPair);
    }
}
        
template <class K, class V>
typename map<K, V> :: iterator map<K, V> :: find(const K& key) {
    map<K, V> :: iterator findIt = map<K, V> :: iterator(this->bst.find(pair(key, V())));
    if (findIt.it != NULL) {
       return findIt;
    } else {
       return iterator();
    }
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V> :: begin() {
    map<K, V> :: iterator it = map<K, V> :: iterator(this->bst.begin());
    return it;
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V> :: end() {
    map<K, V> :: iterator it = map<K, V> :: iterator(this->bst.end());
    return it;
}




template <class K, class V>
typename map<K, V> :: iterator& map<K, V>::iterator :: operator = (const iterator& rhs) {
    this->it = rhs.it;
    return *this;
}

template <class K, class V>
bool map<K, V>::iterator :: operator == (const iterator& rhs) const {
    return this->it == rhs.it;
}

template <class K, class V>
bool map<K, V>::iterator :: operator != (const iterator& rhs) const {
    return this->it != rhs.it;
}

template <class K, class V>
typename map<K, V> :: pair& map<K, V>::iterator :: operator * () {
    return *it;
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V>::iterator :: operator ++ () {
    return iterator(++it);
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V>::iterator :: operator ++ (int postfix) {
    return iterator(it++);
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V>::iterator :: operator -- () {
    return iterator(--it);
}

template <class K, class V>
typename map<K, V> :: iterator map<K, V>::iterator :: operator -- (int postfix) {
    return iterator(it--);
}