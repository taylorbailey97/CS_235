/*
 * main.cpp
 *
 *  Created by Lee Barney on 09/20/18.
 *  Copyright (c) 2018 Lee Barney
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

/* !!!!GRADING INSTRUCTIONS!!!!
 *
 * When you report your score for this test set, report
 * the percentage of asserts found in this test code that
 * your data structure code passed.
 */
#define UNIT_TESTING

#include <iostream>
#include <cstring>
#include <cassert>
#include "unit_testing_delete.h"
#include "list.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;


int main(int argc, const char* argv[])
{
    
    /*
     * Testing default node constructor
     */
    list<int>::node defaultNode;
    assert(defaultNode.data == 0);
    assert(defaultNode.pNext == NULL);
    assert(defaultNode.pPrev == NULL);
    
    /*
     * Testing Node constructor with data
     */
    list<int>::node dataNode(4);
    assert(dataNode.data == 4);
    assert(dataNode.pNext == NULL);
    assert(dataNode.pPrev == NULL);
    
    cout<<"Passed Node Constructor Tests"<<endl;
    
    /*
     * Testing Node Destructor
     */
    unit_testing_delete_call_counter = 0;
    list<int>::node* nodeToDelete = new list<int>::node();
    delete nodeToDelete;
    assert(unit_testing_delete_call_counter == 1);
    //When done with a pointer set it to NULL so you don't create a zombie pointer.
    nodeToDelete = NULL;
    
    //resetting deletion counter
    unit_testing_delete_call_counter = 0;
    nodeToDelete = new list<int>::node(5);
    delete nodeToDelete;
    assert(unit_testing_delete_call_counter == 1);
    //killing potential zombie
    nodeToDelete = NULL;
    cout<<"Passed Node Destructor Test"<<endl;
    
    /*
     * Testing default list constructor
     */
    list <int> defaultList;
    assert(defaultList.pHead == NULL);
    assert(defaultList.pTail == NULL);
    assert(defaultList.numElements == 0);
    cout << "Default List Constructor Test Passed" << endl;
    
    
    /*
     * Testing copy constructor
     */
    list<int> listToCopy;
    listToCopy.numElements = 0;
    listToCopy.pHead = NULL;
    listToCopy.pTail = NULL;
    
    //testing copy of empty list
    list<int>emptyListCopy(listToCopy);
    assert(emptyListCopy.numElements == 0);
    assert(emptyListCopy.pHead == NULL);
    assert(emptyListCopy.pTail == NULL);
    
    //Generating small doubly linked list with the ordered list of values 5<->6<->7<->9<->9<->10. The character set <-> indicates doubly linked lists.
    listToCopy.numElements = 6;
    listToCopy.pHead = new list<int>::node(5);
    list<int>::node* currentNodePtr = listToCopy.pHead;
    currentNodePtr->pNext = new list<int>::node(6);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(7);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(9);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(9);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(10);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    listToCopy.pTail = currentNodePtr;
    //reset currentNodePtr to be NULL so it can't be a zombie pointer
    currentNodePtr = NULL;
    
    //testing copy of non-empty list
    list<int> listCopy(listToCopy);
    assert(listCopy.numElements == 6);
    //These two pointers are here to get rid of the chain of pointers that yout saw in the LinkedList tests.
    list<int>::node* toCopyCurrentNode = listToCopy.pHead;
    list<int>::node* copyCurrentNode = listCopy.pHead;

    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext != copyCurrentNode->pNext);
    assert(toCopyCurrentNode->pPrev == NULL);
    
    toCopyCurrentNode = toCopyCurrentNode->pNext;
    copyCurrentNode = copyCurrentNode->pNext;
    
    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext != copyCurrentNode->pNext);
    assert(toCopyCurrentNode->pPrev != copyCurrentNode->pPrev);
    
    toCopyCurrentNode = toCopyCurrentNode->pNext;
    copyCurrentNode = copyCurrentNode->pNext;
    
    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext != copyCurrentNode->pNext);
    assert(toCopyCurrentNode->pPrev != copyCurrentNode->pPrev);
    
    toCopyCurrentNode = toCopyCurrentNode->pNext;
    copyCurrentNode = copyCurrentNode->pNext;
    
    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext != copyCurrentNode->pNext);
    assert(toCopyCurrentNode->pPrev != copyCurrentNode->pPrev);
    
    toCopyCurrentNode = toCopyCurrentNode->pNext;
    copyCurrentNode = copyCurrentNode->pNext;
    
    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext != copyCurrentNode->pNext);
    assert(toCopyCurrentNode->pPrev != copyCurrentNode->pPrev);
    
    toCopyCurrentNode = toCopyCurrentNode->pNext;
    copyCurrentNode = copyCurrentNode->pNext;
    
    assert(toCopyCurrentNode != copyCurrentNode);
    assert(toCopyCurrentNode->data == copyCurrentNode->data);
    assert(toCopyCurrentNode->pNext == NULL);
    assert(toCopyCurrentNode->pPrev != copyCurrentNode->pPrev);
   
    cout<<"Passed List Copy Constructor Test"<<endl;
    
    
    /*
     * Testing list destructor
     */
    
    unit_testing_delete_call_counter = 0;
    list<int>* listToDelete = new list<int>();
    delete listToDelete;
    assert(unit_testing_delete_call_counter == 1);
    
    //killing potential zombie
    listToDelete = NULL;
    
    //reset deletion counter
    unit_testing_delete_call_counter = 0;
    //resetting listToDelete to: 5<=>6<=>7<=>9
    listToDelete = new list<int>();
    listToDelete->pHead = new list<int>::node(5);
    //reusing currentNodePtr variable
    currentNodePtr = listToDelete->pHead;
    currentNodePtr->pNext = new list<int>::node(6);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(7);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    currentNodePtr->pNext = new list<int>::node(9);
    currentNodePtr->pNext->pPrev = currentNodePtr;
    listToDelete->numElements = 4;
    
    //kill potential zombie
    currentNodePtr = NULL;
    
    delete listToDelete;
    assert(unit_testing_delete_call_counter == 5);
    //kill potential zombie
    listToDelete = NULL;
    
    cout<<"Passed Destructor Tests"<<endl;
    
    /*
     * Testing size
     */
    list<int>emptyList;
    //building emptyList
    emptyList.numElements = 0;
    emptyList.pHead = NULL;
    emptyList.pTail = NULL;
    
    list<int>listWithStuffInIt;
    //building listWithStuffInIt: 5<=>6<=>7<=>9
    listWithStuffInIt.numElements = 4;
    list<int>::node* firstNode = new list<int>::node(5);
    listWithStuffInIt.pHead = firstNode;
    //reusing currentNodePtr variable
    currentNodePtr = listWithStuffInIt.pHead;
    list<int>::node* secondNode = new list<int>::node(6);
    currentNodePtr->pNext = secondNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    list<int>::node* thirdNode = new list<int>::node(7);
    currentNodePtr->pNext = thirdNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    list<int>::node* fourthNode = new list<int>::node(9);
    currentNodePtr->pNext = fourthNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    
    listWithStuffInIt.pTail = fourthNode;
    listWithStuffInIt.pHead = firstNode;
    
    //testing empty list
    assert(emptyList.size() == 0);
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    //testing non-empty list
    assert(listWithStuffInIt.size() == 4);
    //make sure nothing changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    cout<<"Passed Size Tests"<<endl;
    
    /*
     * Testing empty
     */
    //testing empty list
    assert(emptyList.empty() == true);
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing non-empty list
    assert(listWithStuffInIt.empty() == false);
    //make sure nothing changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    cout<<"Passed Empty Tests"<<endl;
    
    /*
     * Testing front
     */
    //testing empty list front getter
    try {
        emptyList.front();
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: calling front on empty list.") == 0);
    }
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing empty list front setter
    try {
        emptyList.front() = 7;
        assert(false);
        
    } catch (const char* message) {
        assert(strcmp(message, "Error: calling front on empty list.") == 0);
    }
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing non-empty list front getter:5<=>6<=>7<=>9
    assert(listWithStuffInIt.front() == 5);
    //make sure nothing changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    //testing non-empty lists front setter:5<=>6<=>7<=>9 becomes 7<=>6<=>7<=>9
    listWithStuffInIt.front() = 7;
    //make sure the first node's data changed
    assert(listWithStuffInIt.pHead->data == 7);
    //make sure no nodes were changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    cout<<"Passed Front Tests"<<endl;
    
    /*
     * Testing back
     */
    //testing empty list back getter
    try {
        emptyList.back();
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: calling back on empty list.") == 0);
    }
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing empty list back setter
    try {
        emptyList.back() = 7;
        assert(false);
        
    } catch (const char* message) {
        assert(strcmp(message, "Error: calling back on empty list.") == 0);
    }
    //testing non-empty list back getter:7<=>6<=>7<=>9
    assert(listWithStuffInIt.back() == 9);
    //make sure nothing changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    //testing non-empty list back setter: 7<=>6<=>7<=>9 becomes 7<=>6<=>7<=>1
    listWithStuffInIt.back() = 1;
    //make sure the first node's data changed
    assert(listWithStuffInIt.pTail->data == 1);
    //make sure no nodes were changed in the list
    assert(listWithStuffInIt.numElements == 4);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == fourthNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    assert(listWithStuffInIt.pHead->pNext->pNext->pNext == fourthNode);
    assert(fourthNode->pPrev == thirdNode);
    
    cout<<"Passed Back Tests"<<endl;
    
    /*
     * Testing pop_back
     */
    //testing pop_back for empty list
    try {
        emptyList.pop_back();
    } catch (const char* message) {
        assert(false);
    }
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing pop_back for non-empty list:7<=>6<=>7<=>1 becomes 7<=>6<=>7
    listWithStuffInIt.pop_back();
    assert(listWithStuffInIt.numElements == 3);
    assert(listWithStuffInIt.pHead == firstNode);
    assert(listWithStuffInIt.pTail == thirdNode);
    assert(listWithStuffInIt.pHead->pNext == secondNode);
    assert(secondNode->pPrev == firstNode);
    assert(listWithStuffInIt.pHead->pNext->pNext == thirdNode);
    assert(thirdNode->pPrev == secondNode);
    
    cout<<"Passed pop_back Tests"<<endl;
    
    /*
     * Testing pop_front
     */
    //testing pop_front for empty list
    try {
        emptyList.pop_front();
    } catch (const char* message) {
        assert(false);
    }
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    
    //testing pop_front for non-empty list:7<=>6<=>7 becomes 6<=>7
    listWithStuffInIt.pop_front();
    assert(listWithStuffInIt.numElements == 2);
    assert(listWithStuffInIt.pHead == secondNode);
    assert(listWithStuffInIt.pTail == thirdNode);
    assert(listWithStuffInIt.pHead->pNext == thirdNode);
    assert(listWithStuffInIt.pHead->pPrev == NULL);
    
    cout<<"Passed Pop Front Tests"<<endl;
    
    /*
     * Testing clear
     */
    //resetting delete counter
    unit_testing_delete_call_counter = 0;
    //testing empty list
    emptyList.clear();
    assert(unit_testing_delete_call_counter == 0);
    assert(emptyList.numElements == 0);
    assert(emptyList.pHead == NULL);
    assert(emptyList.pTail == NULL);
    //testing non-empty list: 6<=>7
    unit_testing_delete_call_counter = 0;
    listWithStuffInIt.clear();
    assert(unit_testing_delete_call_counter == 2);
    assert(listWithStuffInIt.numElements == 0);
    assert(listWithStuffInIt.pHead == NULL);
    assert(listWithStuffInIt.pTail == NULL);
    
    cout<<"Passed Clear tests"<<endl;
    
    /*
     * Testing push_front
     */
    list<int> pushTestingList;
    pushTestingList.numElements = 0;
    pushTestingList.pHead = NULL;
    pushTestingList.pTail = NULL;
    
    //testing push_front on an empty list
    try {
        pushTestingList.push_front(3);
    } catch (const char* message) {
        assert(false);
    }
    assert(pushTestingList.numElements == 1);
    assert(pushTestingList.pHead != NULL);
    assert(pushTestingList.pTail == pushTestingList.pHead);
    assert(pushTestingList.pHead->pNext == NULL);
    assert(pushTestingList.pTail->pPrev == NULL);
    assert(pushTestingList.pHead->data == 3);
    
    //testing push_front on a list with one node: 3 becomes 5<=>3
    pushTestingList.push_front(5);
    assert(pushTestingList.numElements == 2);
    assert(pushTestingList.pHead != NULL);
    assert(pushTestingList.pTail != NULL);
    assert(pushTestingList.pHead != pushTestingList.pTail);
    assert(pushTestingList.pHead->pNext == pushTestingList.pTail);
    assert(pushTestingList.pTail->pPrev == pushTestingList.pHead);
    assert(pushTestingList.pHead->data == 5);
    assert(pushTestingList.pHead->pNext->data == 3);
    
    //testing push_front on a list with multiple nodes: 5<=>3 becomes -2<=>5<=>3
    list<int>::node* previousHead = pushTestingList.pHead;
    pushTestingList.push_front(-2);
    assert(pushTestingList.numElements == 3);
    //making sure the pointers all got set correctly
    assert(pushTestingList.pHead != NULL);
    assert(pushTestingList.pTail != NULL);
    assert(pushTestingList.pHead != pushTestingList.pTail);
    assert(pushTestingList.pHead->pNext == previousHead);
    assert(pushTestingList.pHead->pPrev == NULL);
    assert(pushTestingList.pTail->pPrev == previousHead);
    assert(pushTestingList.pTail->pNext == NULL);
    assert(previousHead->pPrev == pushTestingList.pHead);
    assert(previousHead->pNext == pushTestingList.pTail);
    //making sure the data didn't get messed up
    assert(pushTestingList.pHead->data == -2);
    assert(pushTestingList.pTail->data == 3);
    assert(previousHead->data == 5);
    
    cout<<"Passed Push Front Tests"<<endl;
    
    /*
     * Testing push_back
     */
    list<int>pushBackTestingList;
    pushBackTestingList.numElements = 0;
    pushBackTestingList.pHead = NULL;
    pushBackTestingList.pTail = NULL;
    
    //testing push_back on an empty list
    pushBackTestingList.push_back(20);
    assert(pushBackTestingList.numElements = 1);
    assert(pushBackTestingList.pHead != NULL);
    assert(pushBackTestingList.pTail == pushBackTestingList.pHead);
    assert(pushBackTestingList.pHead->pNext == NULL);
    assert(pushBackTestingList.pTail->pPrev == NULL);
    assert(pushBackTestingList.pTail->data == 20);
    
    //testing push_back on a list with one node: 20 becomes 20<=>0
    pushBackTestingList.push_back(0);
    assert(pushBackTestingList.numElements = 2);
    assert(pushBackTestingList.pHead != NULL);
    assert(pushBackTestingList.pTail != NULL);
    assert(pushBackTestingList.pHead != pushBackTestingList.pTail);
    assert(pushBackTestingList.pHead->pNext == pushBackTestingList.pTail);
    assert(pushBackTestingList.pTail->pPrev == pushBackTestingList.pHead);
    assert(pushBackTestingList.pTail->data == 0);
    assert(pushBackTestingList.pHead->data == 20);
    
    //testing push_back on a list with multiple nodes: 20<=>0 becomes 20<=>0<=>32
    list<int>::node* previousTail = pushBackTestingList.pTail;
    pushBackTestingList.push_back(32);
    assert(pushBackTestingList.numElements = 3);
    //making sure the pointers all got set correctly
    assert(pushBackTestingList.pHead != NULL);
    assert(pushBackTestingList.pTail != NULL);
    assert(pushBackTestingList.pHead != pushBackTestingList.pTail);
    assert(pushBackTestingList.pHead->pNext == previousTail);
    assert(pushBackTestingList.pHead->pPrev == NULL);
    assert(pushBackTestingList.pTail->pPrev == previousTail);
    assert(pushBackTestingList.pTail->pNext == NULL);
    assert(previousTail->pPrev == pushBackTestingList.pHead);
    assert(previousTail->pNext == pushBackTestingList.pTail);
    //making sure the data didn't get messed up
    assert(pushBackTestingList.pHead->data == 20);
    assert(previousTail->data == 0);
    assert(pushBackTestingList.pTail->data == 32);
    
    cout<<"Passed Push Back Tests"<<endl;

    /*
     * Testing assignment operator
     */
    //testing assigning to an empty list
    list<int>assignedToList;
    assignedToList.numElements = 0;
    assignedToList.pHead = NULL;
    assignedToList.pTail = NULL;
    
    unit_testing_delete_call_counter = 0;
    assignedToList = pushBackTestingList;
    assert(assignedToList.numElements == 3);
    //making sure the pointers all got set correctly
    assert(assignedToList.pHead != NULL);
    assert(assignedToList.pTail != NULL);
    assert(assignedToList.pHead != assignedToList.pTail);
    assert(assignedToList.pHead != pushBackTestingList.pHead);
    assert(assignedToList.pHead->pNext != pushBackTestingList.pHead->pNext);
    assert(assignedToList.pTail != pushBackTestingList.pTail);
    //making sure the data didn't get messed up
    assert(assignedToList.pHead->data == 20);
    assert(assignedToList.pHead->pNext->data == 0);
    assert(assignedToList.pTail->data == 32);
    assert(unit_testing_delete_call_counter == 0);
    
    //testing assigning to a non-empty list
    
    list<int>listToAssign;
    int simpleValue = 123;
    list<int>::node* simpleNode = new list<int>::node(simpleValue);
    listToAssign.numElements = 1;
    listToAssign.pHead = simpleNode;
    listToAssign.pTail = simpleNode;
    
    unit_testing_delete_call_counter = 0;
    //assignedToList is currently: 20<=>0<=>32
    assignedToList = listToAssign;
    //now assignedToList should be: 123
    assert(assignedToList.numElements == 1);
    //making sure the pointers all got set correctly
    assert(assignedToList.pHead != NULL);
    assert(assignedToList.pTail != NULL);
    assert(assignedToList.pHead == assignedToList.pTail);
    //making sure the data didn't get messed up
    assert(assignedToList.pHead->data == 123);
    assert(unit_testing_delete_call_counter == 3);

    cout<<"Passed Assignment Operator Tests"<<endl;
    
    
    /*
     * Testing iterator Constructors
     */
    
    //testing default constructor
    list<int>::iterator emptyIterator;
    assert(emptyIterator.ptr == NULL);
    
    //testing non-default constructor with node that has a null data pointer
    int leftDataValue = 5;
    list<int>::node* leftNode = new list<int>::node();
    leftNode->data = leftDataValue;
    
    int rightDataValue = -76;
    list<int>::node* rightNode = new list<int>::node();
    rightNode->data = rightDataValue;
    
    list<int>::node* defaultDataNode = new list<int>::node();
    defaultDataNode->data = NULL;
    //set up the pointers correctly
    defaultDataNode->pNext = rightNode;
    rightNode->pPrev = defaultDataNode;
    defaultDataNode->pPrev = leftNode;
    leftNode->pNext = defaultDataNode;
    
    list<int>::iterator defaultDataNodeIterator(defaultDataNode);
    assert(defaultDataNodeIterator.ptr == defaultDataNode);
    
    
    //make sure the pointers didn't get messed up
    assert(defaultDataNode->pNext == rightNode);
    assert(rightNode->pPrev == defaultDataNode);
    assert(defaultDataNode->pPrev == leftNode);
    assert(leftNode->pNext == defaultDataNode);
    
    //make sure the values didn't get messed up
    assert(defaultDataNode->data == 0);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    
    cout<<"Passed Iterator Constructor Tests"<<endl;
    
    /*
     * Testing iterator copy constructors
     */
    
    
    //copies of iterators are shallow copies
    
    //testing copy of iterator with null node
    list<int>::iterator nullNodeIterator;
    nullNodeIterator.ptr = NULL;
    
    list<int>::iterator nullNodeIteratorCopy(nullNodeIterator);
    assert(nullNodeIteratorCopy.ptr == NULL);
    
    //testing non-default constructor with node that has a non-null data pointer
    int middleNodeDataValue = 512;
    list<int>::node* nonNullDataNode = new list<int>::node();
    nonNullDataNode->data = middleNodeDataValue;
    //set up the pointers correctly
    nonNullDataNode->pNext = rightNode;
    rightNode->pPrev = nonNullDataNode;
    nonNullDataNode->pPrev = leftNode;
    leftNode->pNext = nonNullDataNode;
    
    list<int>::iterator nonDefaultDataNodeIterator(nonNullDataNode);
    assert(nonDefaultDataNodeIterator.ptr == nonNullDataNode);
    
    //make sure the pointers didn't get messed up
    assert(nonNullDataNode->pNext == rightNode);
    assert(rightNode->pPrev == nonNullDataNode);
    assert(nonNullDataNode->pPrev == leftNode);
    assert(leftNode->pNext == nonNullDataNode);
    
    //make sure the values didn't get messed up
    assert(nonNullDataNode->data == 512);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    
    //Testing copy constructor with default data node
    list<int>::iterator defaultDataCopiedIterator(defaultDataNodeIterator);
    assert(defaultDataCopiedIterator.ptr == defaultDataNodeIterator.ptr);
    assert(defaultDataCopiedIterator.ptr->pNext == rightNode);
    assert(defaultDataCopiedIterator.ptr->pPrev == leftNode);
    //make sure the values didn't get messed up
    assert(defaultDataCopiedIterator.ptr->data == 0);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    //Testing copy constructor with non-default data node
    list<int>::iterator nonNullDataCopiedIterator(nonDefaultDataNodeIterator);
    assert(nonNullDataCopiedIterator.ptr == nonDefaultDataNodeIterator.ptr);
    assert(nonNullDataCopiedIterator.ptr->pNext == rightNode);
    assert(nonNullDataCopiedIterator.ptr->pPrev == leftNode);
    //make sure the values didn't get messed up
    assert(nonNullDataNode->data == 512);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    cout<<"Passed Iterator Copy Constructor Tests"<<endl;
    
    /*
     * Testing iterator assignment operator
     */
    
    //testing copy of iterator when node pointer is null
    
    //reuse nullNodeIterator
    list<int>::iterator nullNodeAssignedIterator = nullNodeIterator;
    assert(nullNodeAssignedIterator.ptr == NULL);
    
    
    //testing iterator when data in the node is null
    list<int>::iterator defaultDataAssignedTo = defaultDataNodeIterator;
    assert(defaultDataAssignedTo.ptr == defaultDataNodeIterator.ptr);
    assert(defaultDataAssignedTo.ptr->pNext == rightNode);
    assert(defaultDataAssignedTo.ptr->pPrev == leftNode);
    //make sure the values didn't get messed up
    assert(defaultDataAssignedTo.ptr->data == 0);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    //testing when data in the node is non-null
    list<int>::iterator nonNullDataAssignedTo = nonDefaultDataNodeIterator;
    assert(nonNullDataAssignedTo.ptr == nonDefaultDataNodeIterator.ptr);
    assert(nonNullDataAssignedTo.ptr->pNext == rightNode);
    assert(nonNullDataAssignedTo.ptr->pPrev == leftNode);
    //make sure the values didn't get messed up
    assert(nonNullDataNode->data == 512);
    assert(leftNode->data == 5);
    assert(rightNode->data == -76);
    
    cout<<"Passed Iterator Assignment Operator Tests"<<endl;
    
    /*
     * Testing iterator equality operator
     */
    
    //testing equality of self
    assert(nullNodeIterator == nullNodeIterator);
    //testing equality of not-self (null node)
    assert(nullNodeIteratorCopy == nullNodeIterator);
    //testing equality of not-self, non-null node, null data in node
    assert(defaultDataNodeIterator == defaultDataCopiedIterator);
    //testing equality of not-self, non-null node, non-null data in node
    assert(nonDefaultDataNodeIterator == nonNullDataCopiedIterator);
    //testing equality of non-null node, null data in node
    list<int>::node secondNullNode;
    secondNullNode.data = NULL;
    list<int>::iterator secondNullNodeIterator;
    secondNullNodeIterator.ptr = &secondNullNode;
    assert(!(nullNodeIterator == secondNullNodeIterator));
    //testing equality of non-null node, default data in node
    int anInt = 7;
    list<int>::node secondNonNullDataNode;
    secondNonNullDataNode.data = anInt;
    list<int>::iterator secondNonNullDataNodeIterator;
    secondNonNullDataNodeIterator.ptr = &secondNonNullDataNode;
    assert(!(nonDefaultDataNodeIterator == secondNullNodeIterator));
    //testing equality of iterator with different node but same value in node
    list<int>::node thirdNonNullDataNode;
    thirdNonNullDataNode.data = anInt;
    list<int>::iterator thirdNonNullDataNodeIterator;
    thirdNonNullDataNodeIterator.ptr = &thirdNonNullDataNode;
    assert(!(secondNonNullDataNodeIterator == thirdNonNullDataNodeIterator));
    
    cout<<"Passed Iterator Equality Tests"<<endl;
    
    /*
     * Testing inequality operator
     */
    //testing inequality of non-null node, null data in node
    assert(secondNullNodeIterator != nullNodeIterator);
    //testing inequality of non-null node, non-null data in node
    assert(nonDefaultDataNodeIterator != secondNonNullDataNodeIterator);
    //testing inequality of self
    assert(!(nullNodeIterator != nullNodeIterator));
    //testing inequality of not-self (null node)
    assert(!(nullNodeIteratorCopy != nullNodeIterator));
    //testing inequality of not-self, non-null node, null data in node
    assert(!(defaultDataNodeIterator != defaultDataCopiedIterator));
    //testing inequality of not-self, non-null node, non-null data in node
    assert(!(nonDefaultDataNodeIterator != nonNullDataCopiedIterator));
    //testing equality of iterator with different node but same value in node
    assert(secondNonNullDataNodeIterator != thirdNonNullDataNodeIterator);
    
    cout<<"Passed Iterator Inequality Tests"<<endl;
    
    
    //building list for incrementor tests
    list<int>incrementorList;
    //building listWithStuffInIt: 5<=>6<=>7<=>9
    incrementorList.numElements = 4;
    firstNode = new list<int>::node(5);
    incrementorList.pHead = firstNode;
    //reusing currentNodePtr variable
    currentNodePtr = incrementorList.pHead;
    secondNode = new list<int>::node(6);
    currentNodePtr->pNext = secondNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    thirdNode = new list<int>::node(7);
    currentNodePtr->pNext = thirdNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    fourthNode = new list<int>::node(9);
    currentNodePtr->pNext = fourthNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    incrementorList.pTail = fourthNode;
    /*
     * Testing post-incrementor operator
     */
    
    //testing incrementor when node is NULL
    try {
        nullNodeIterator++;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: incrementing null node.") == 0);
    }
    list<int>::iterator nonNullNodeIterator;
    //testing incrementing with tail
    nonNullNodeIterator.ptr = fourthNode;
    assert((nonNullNodeIterator++).ptr == fourthNode);
    assert(nonNullNodeIterator.ptr == fourthNode);
    //testing for any node other than tail
    nonNullNodeIterator.ptr = secondNode;
    assert((nonNullNodeIterator++).ptr == secondNode);
    assert(nonNullNodeIterator.ptr == thirdNode);
    cout<<"Passed Iterator Post-Incrementor Test"<<endl;
    
    /*
     * Testing pre-incrementor operator
     */
    
    //testing incrementor when node is NULL
    try {
        ++nullNodeIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: incrementing null node.") == 0);
    }
    //testing incrementing with tail
    nonNullNodeIterator.ptr = fourthNode;
    assert((++nonNullNodeIterator).ptr == fourthNode);
    //testing for any node other than tail
    nonNullNodeIterator.ptr = secondNode;
    assert((++nonNullNodeIterator).ptr == thirdNode);
    cout<<"Passed Iterator Pre-Incrementor Test"<<endl;
    
    /*
     * Testing post-decrement operator
     */
    //testing decrementor when node is NULL
    try {
        nullNodeIterator--;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: decrementing null node.") == 0);
    }
    //list<int>::iterator nonNullNodeIterator;
    //testing decrementing with head
    nonNullNodeIterator.ptr = firstNode;
    assert((nonNullNodeIterator--).ptr == firstNode);
    assert(nonNullNodeIterator.ptr == firstNode);
    //testing for any node other than tail
    nonNullNodeIterator.ptr = secondNode;
    assert((nonNullNodeIterator--).ptr == secondNode);
    assert(nonNullNodeIterator.ptr == firstNode);
    cout<<"Passed Iterator Post-Decrementor Test"<<endl;
    /*
     * Testing pre-decrement operator
     */
    //testing decrementor when node is NULL
    try {
        --nullNodeIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: decrementing null node.") == 0);
    }
    //resetting node relationships
    firstNode->pNext = secondNode;
    secondNode->pPrev = firstNode;
    //testing decrementing with head
    nonNullNodeIterator.ptr = firstNode;
    assert((--nonNullNodeIterator).ptr == firstNode);
    //testing for any node other than tail
    nonNullNodeIterator.ptr = thirdNode;
    assert((--nonNullNodeIterator).ptr == secondNode);
    cout<<"Passed Iterator Pre-Decrementor Test"<<endl;
    
    /*
     * Testing dereference operator
     */
    //testing dereference of null node
    try {
        *nullNodeIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message,"Error: dereferencing null node.") == 0);
    }
    try {
        *defaultDataNodeIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: dereferencing null data") == 0);
    }
    //assert(*nonDefaultDataNodeIterator == 512);
    
    cout<<"Passed Iterator Dereference Operator Tests"<<endl;
    
    
    
    
    //building empty begin/end list
    list<int>emptyBeginEndList;
    emptyBeginEndList.numElements = 0;
    emptyBeginEndList.pHead = NULL;
    emptyBeginEndList.pTail = NULL;
    
    
    //building a list do begin and end
    list<int>beginEndList;
    //building listWithStuffInIt: 5<=>6<=>7<=>9
    beginEndList.numElements = 4;
    firstNode = new list<int>::node(5);
    beginEndList.pHead = firstNode;
    //reusing currentNodePtr variable
    currentNodePtr = beginEndList.pHead;
    secondNode = new list<int>::node(6);
    currentNodePtr->pNext = secondNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    thirdNode = new list<int>::node(7);
    currentNodePtr->pNext = thirdNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    fourthNode = new list<int>::node(9);
    currentNodePtr->pNext = secondNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    //make sure we don't have a zombie
    currentNodePtr = NULL;
    /*
     * Testing Begin
     */
    assert(emptyBeginEndList.begin().ptr == NULL);
    assert(beginEndList.begin().ptr == beginEndList.pHead);
    cout<<"Passed Begin Tests"<<endl;
    
    /*
     * Testing End
     */
    assert(emptyBeginEndList.end().ptr == NULL);
    assert(beginEndList.end().ptr == NULL);
    
    
    /*
     * Testing Find
     */
    list<int>emptyFindList;
    emptyFindList.numElements = 0;
    emptyFindList.pHead = NULL;
    emptyFindList.pTail = NULL;
    
    //testing for something not found in the list
    assert(emptyFindList.find(10).ptr == NULL);
    
    //building a list do search
    list<int>filledFindList;
    //building listWithStuffInIt: 5<=>6<=>7<=>9
    filledFindList.numElements = 4;
    firstNode = new list<int>::node(5);
    filledFindList.pHead = firstNode;
    //reusing currentNodePtr variable
    currentNodePtr = filledFindList.pHead;
    secondNode = new list<int>::node(6);
    currentNodePtr->pNext = secondNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    thirdNode = new list<int>::node(7);
    currentNodePtr->pNext = thirdNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    currentNodePtr = currentNodePtr->pNext;
    
    fourthNode = new list<int>::node(9);
    currentNodePtr->pNext = fourthNode;
    currentNodePtr->pNext->pPrev = currentNodePtr;
    filledFindList.pTail = fourthNode;
    //make sure we don't have a zombie
    currentNodePtr = NULL;
    
    
    //testing for something not found in the list
    assert(filledFindList.find(10).ptr == NULL);
    //testing finding the first element
    assert(filledFindList.find(5).ptr == filledFindList.pHead);
    //testing finding the last element
    assert(filledFindList.find(9).ptr == filledFindList.pTail);
    //testing finding an element somewhere in the middle
    assert(filledFindList.find(6).ptr == filledFindList.pHead->pNext);
    
    cout<<"Passed Find Tests"<<endl;
    
    /*
     * Testing erase
     */
    
    //testing for erasing end iterator
    //reusing iterator with a null node to simulate end iterator
    unit_testing_delete_call_counter = 0;
    assert(emptyFindList.erase(nullNodeIterator).ptr == NULL);
    assert(unit_testing_delete_call_counter == 0);
    assert(filledFindList.erase(nullNodeIterator).ptr == NULL);
    assert(unit_testing_delete_call_counter == 0);
    
    //testing erasing head from list:  5<=>6<=>7<=>9
    list<int>::iterator headIterator;
    headIterator.ptr = filledFindList.pHead;
    list<int>::node* nextHead = filledFindList.pHead->pNext;
    unit_testing_delete_call_counter = 0;
    assert(filledFindList.erase(headIterator).ptr == nextHead);
    assert(filledFindList.pHead == nextHead);
    assert(unit_testing_delete_call_counter == 1);
    
    //testing erasing something in the middle: 6<=>7<=>9
    unit_testing_delete_call_counter = 0;
    list<int>::iterator midIterator;
    midIterator.ptr = filledFindList.pHead->pNext;
    assert(filledFindList.erase(midIterator).ptr == filledFindList.pHead);
    assert(unit_testing_delete_call_counter == 1);
    
    //testing erasing tail of list: 6<=>9
    unit_testing_delete_call_counter = 0;
    list<int>::iterator endIterator;
    endIterator.ptr = filledFindList.pTail;
    assert(filledFindList.erase(endIterator).ptr == filledFindList.pHead);
    assert(unit_testing_delete_call_counter == 1);
    
    cout<<"Passed Erase Tests"<<endl;
    
    /*
     * Testing Insert
     */
    list<int>insertList;
    insertList.numElements = 0;
    insertList.pHead = NULL;
    insertList.pTail = NULL;
    
    //testing inserting into a list with an invalid iterator (might be one from a different list, etc.)
    list<int>::iterator insertIterator;
    insertIterator.ptr = new list<int>::node(2);
    
    insertList.insert(insertIterator, -7);
    assert(insertList.numElements);
    //resetting insertIterator
    delete insertIterator.ptr;
    insertIterator.ptr = NULL;
    unit_testing_delete_call_counter = 0;
    
    // //testing inserting into an empty list with valid iterator (simulating end iterator)
    insertList.insert(insertIterator, 4);
    assert(insertList.pHead != NULL);
    assert(insertList.pHead->data == 4);
    assert(insertList.pHead == insertList.pTail);
    
    
    //testing inserting before head, list will be: 8<=>4
    //reusing previous head variable
    previousHead = insertList.pHead;
    insertIterator.ptr = insertList.pHead;
    insertList.insert(insertIterator, 8);
    assert(insertList.pHead != NULL);
    assert(insertList.pHead != previousHead);
    assert(insertList.pHead->pNext == previousHead);
    assert(insertList.pHead->data == 8);
    assert(insertList.pTail->data == 4);
    
    //testing inserting in middle, list will be: 8<=>13<=>4
    insertIterator.ptr = insertList.pTail;
    insertList.insert(insertIterator, 13);
    assert(insertList.pTail != NULL);
    assert(insertList.pTail->pPrev != insertList.pHead);
    assert(insertList.pTail->pPrev->data == 13);
    assert(insertList.pTail->data == 4);
    assert(insertList.pHead->data == 8);
    
    cout<<"Passed Insert Tests"<<endl;
    
    
    /*
     * Testing push_back for Non-Integer list Behavior (just to see if it works for other types)
     */
    
    list<string>stringList;
    assert(stringList.pHead == NULL);
    assert(stringList.pTail == NULL);
    assert(stringList.numElements == 0);
    stringList.push_back("Hello");
    
    assert(stringList.pHead == stringList.pTail);
    assert(stringList.pHead->data.compare("Hello") == 0);
    
    cout << "This list can hold strings!!!!" << endl;
     
    return 0;
}
