/*
 * main.cpp
 *
 *  Created by Lee Barney on 09/15/18.
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
#include "set.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;

/*
 * While set can be implemented either sorted
 * or not sorted, for this class, you are
 * required to implement the sorted design.
 */

int main(int argc, const char* argv[])
{
    
    /*
     * Testing default constructor
     */
    set <int> defaultset;
    assert(defaultset.numCapacity == 0);
    assert(defaultset.numElements == 0);
    assert(defaultset.buffer == NULL);
    cout << "Default Constructor Test Passed" << endl;
    
    /*
     * Testing sized set constructor
     */
    try
    {
        set<int> badSizeset(-3);
        assert(false);
    }
    catch(const char* exceptionMessage)
    {
        assert(strcmp(exceptionMessage,"Error: set sizes must be greater than or equal to 0.") == 0);
    }
    
    set <int> sizedset(4);
    assert(sizedset.numCapacity == 4);
    assert(sizedset.numElements == 0);
    assert(sizedset.buffer != NULL);
    cout << "Sized Constructor Test Passed" << endl;
    
    /*
     * Testing Size
     */
    set <int> sizeTestset;
    
    sizeTestset.numCapacity = 8;
    sizeTestset.numElements = 4;
    assert(sizeTestset.size() == 4);
    cout << "Size Tests Passed" << endl;
    
    /*
     * Resetting for further use
     */
    sizeTestset.numCapacity = 8;
    sizeTestset.numElements = 8;
    sizeTestset.buffer = new int[sizeTestset.numCapacity];
    for (int i = 0; i < sizeTestset.numCapacity; i++)
    {
        sizeTestset.buffer[i]=i*i+1;
    }
    //buffer: [1,2,5,10,17,26,50,65]
    /*
     * Testing Clear
     */
    sizeTestset.clear();
    assert(sizeTestset.numCapacity == 8);
    assert(sizeTestset.numElements == 0);
    assert(sizeTestset.buffer != NULL);
    cout << "Clear Test Passed" << endl;
    
    /*
     * Testing Empty
     */
    sizeTestset.numElements = 3;
    assert(!sizeTestset.empty());
    
    sizeTestset.numElements = 0;
    
    assert(sizeTestset.empty());
    cout << "Empty Tests Passed" << endl;
    
    /*
     * Testing insert with no resizing
     */
    set <int> insertset;
    insertset.buffer = new int[5];
    insertset.numCapacity = 5;
    insertset.numElements = 0;
    
    int * tempBuffer = insertset.buffer;
    insertset.insert(3);
    assert(tempBuffer == insertset.buffer);
    assert(insertset.numCapacity == 5);
    assert(insertset.numElements == 1);
    assert(insertset.buffer[0] == 3);
    cout << "Insert First Element Test Passed" << endl;
    
    //make sure inserting a duplicate makes no changes to the end result.
    insertset.insert(3);
    assert(insertset.numCapacity == 5);
    assert(insertset.numElements == 1);
    assert(insertset.buffer[0] == 3);
    cout << "Insert Second Element Test Passed" << endl;
    
    
    insertset.insert(7);
    assert(insertset.numCapacity == 5);
    assert(insertset.numElements == 2);
    assert(insertset.buffer[0] == 3);
    assert(insertset.buffer[1] == 7);
    cout << "Insert Third Element Test Passed" << endl;
    
    
    insertset.insert(-5);
    assert(insertset.numCapacity == 5);
    assert(insertset.numElements == 3);
    assert(insertset.buffer[0] == -5);
    assert(insertset.buffer[1] == 3);
    assert(insertset.buffer[2] == 7);
    
    cout<<"Passed insert no-resize Tests"<<endl;
    
    
    
    /*
     * Testing FindIndex
     */
    set<int> findIndexSet;
    //testing find with empty set
    findIndexSet.numElements = 0;
    findIndexSet.numCapacity = 0;
    findIndexSet.buffer = NULL;
    assert(findIndexSet.findIndex(35) == 0);
    
    //resetting
    findIndexSet.numElements = 3;
    findIndexSet.numCapacity = 4;
    findIndexSet.buffer = new int[4];
    findIndexSet.buffer[0] = 2;
    findIndexSet.buffer[1] = 4;
    findIndexSet.buffer[2] = 8;
    //buffer - [2,4,8]
    //Testing happy paths
    assert(findIndexSet.findIndex(8) == 2);
    assert(findIndexSet.findIndex(2) == 0);
    assert(findIndexSet.findIndex(4) == 1);
    //Testing not found. Indicates where the element should be inserted when not found.
    assert(findIndexSet.findIndex(5) == 2);
    assert(findIndexSet.findIndex(27) == 3);
    assert(findIndexSet.findIndex(0) == 0);
    assert(findIndexSet.findIndex(-100) == 0);
    cout<<"findIndex Test Passed."<<endl;
    
    
    
    
    
    /*
     * Testing Raw Iterators
     */
    set<int>::iterator nullIt = set<int>::iterator();
    assert(nullIt.ptr == NULL);
    int someInt = 3;
    int *someIntPtr = &someInt;
    set<int>::iterator intPtr = set<int>::iterator(&someInt);
    assert(intPtr.ptr == someIntPtr);
    
    cout<<"Passed Raw Iterator Test."<<endl;
    
    /*
     * Testing Iterator Assignment Operator
     */
    set<int>::iterator iteratorToAssign;
    iteratorToAssign.ptr = someIntPtr;
    set<int>::iterator assignedToIterator;
    assignedToIterator = iteratorToAssign;
    assert(assignedToIterator.ptr == someIntPtr);
    cout<<"Passed iterator assignment test."<<endl;
    
    /*
     * Testing Iterator Comparison Operators
     */
    
    //reset
    int someOtherInt = 4;
    int* someOtherIntPtr = &someOtherInt;
    assignedToIterator.ptr = someOtherIntPtr;
    
    set<int>::iterator duplicateValueIterator;
    duplicateValueIterator.ptr = someIntPtr;
    
    
    assert(iteratorToAssign == duplicateValueIterator);
    assert(!(assignedToIterator == iteratorToAssign));
    
    cout<<"Passed operator == test."<<endl;
    
    assert(iteratorToAssign != assignedToIterator);
    assert(!(iteratorToAssign != duplicateValueIterator));
    cout<<"Passed operator != test."<<endl;
    /*
     * Testing Dereference Operator
     */
    assert(*assignedToIterator == 4);
    cout<<"Passed dereference operator test."<<endl;
    /*
     * Testing iterator incrementor
     */
    nullIt.ptr = NULL;
    assert((nullIt++).ptr == NULL);
    assert((++nullIt).ptr == NULL);
    
    set<int> incrementTesterSet;
    incrementTesterSet.buffer = new int[3];
    //setting to the beginning of buffer
    set<int>::iterator fakeBeginIt = set<int>::iterator();
    fakeBeginIt.ptr = incrementTesterSet.buffer;
    
    assert((fakeBeginIt++).ptr == incrementTesterSet.buffer);
    //reset
    fakeBeginIt.ptr = incrementTesterSet.buffer;
    assert((++fakeBeginIt).ptr == incrementTesterSet.buffer+1);
    
    cout<<"Passed pre and post-increment ++ test."<<endl;
    
    incrementTesterSet.buffer = new int[8];
    incrementTesterSet.numCapacity = 8;
    incrementTesterSet.numElements = 5;
    incrementTesterSet.buffer[0] = 6;
    incrementTesterSet.buffer[1] = 4;
    incrementTesterSet.buffer[2] = -3;
    incrementTesterSet.buffer[3] = 2;
    incrementTesterSet.buffer[4] = 0;
    //buffer: [6,4,-3,2,0]
    //setting to the end of buffer
    set<int>::iterator fakeEndIt = set<int>::iterator();
    fakeEndIt.ptr = incrementTesterSet.buffer+incrementTesterSet.numElements;
    assert((fakeEndIt--).ptr == incrementTesterSet.buffer+incrementTesterSet.numElements);
    //reset
    fakeEndIt.ptr = incrementTesterSet.buffer+incrementTesterSet.numElements;
    assert((--fakeEndIt).ptr == incrementTesterSet.buffer+incrementTesterSet.numElements - 1);
    cout<<"Passed pre and post-increment -- test."<<endl;
    
    /**
     - ToDo: Move union, intersection, and difference to be tested after
     resize() since they use resize.
     */
    
    /*
     * Testing union operator
     */
    set<int>shortSet;
    shortSet.numCapacity = 0;
    shortSet.numElements = 0;
    shortSet.buffer = NULL;
    
    set<int>longSet;
    longSet.numCapacity = 0;
    longSet.numElements = 0;
    longSet.buffer = NULL;
    
    //testing union empty sets is empty set
    assert((shortSet || longSet).numCapacity == 0);
    assert((shortSet || longSet).numElements == 0);
    assert((shortSet || longSet).buffer == NULL);
    cout<<"Passed empty set union test."<<endl;
    
    //testing union empty set with filled buffer set
    longSet.buffer = new int[10];
    longSet.numCapacity = 10;
    longSet.numElements = 10;
    longSet.buffer[0] = 3;
    longSet.buffer[1] = 4;
    longSet.buffer[2] = 5;
    longSet.buffer[3] = 6;
    longSet.buffer[4] = 7;
    longSet.buffer[5] = 8;
    longSet.buffer[6] = 9;
    longSet.buffer[7] = 10;
    longSet.buffer[8] = 11;
    longSet.buffer[9] = 12;
    
    assert((shortSet || longSet).numCapacity == 10);
    assert((shortSet || longSet).numElements == 10);
    assert((shortSet || longSet).buffer != NULL);
    assert((shortSet || longSet).buffer != longSet.buffer);
    assert((shortSet || longSet).buffer != shortSet.buffer);
    assert((shortSet || longSet).buffer[0] == 3);
    assert((shortSet || longSet).buffer[1] == 4);
    assert((shortSet || longSet).buffer[2] == 5);
    assert((shortSet || longSet).buffer[3] == 6);
    assert((shortSet || longSet).buffer[4] == 7);
    assert((shortSet || longSet).buffer[5] == 8);
    assert((shortSet || longSet).buffer[6] == 9);
    assert((shortSet || longSet).buffer[7] == 10);
    assert((shortSet || longSet).buffer[8] == 11);
    assert((shortSet || longSet).buffer[9] == 12);
    
    //testing union empty set with partially filled buffer set
    //reset longSet
    longSet.numElements = 3;
    assert((shortSet || longSet).numCapacity == 3);
    assert((shortSet || longSet).numElements == 3);
    assert((shortSet || longSet).buffer != NULL);
    assert((shortSet || longSet).buffer != longSet.buffer);
    assert((shortSet || longSet).buffer != shortSet.buffer);
    assert((shortSet || longSet).buffer[0] == 3);
    assert((shortSet || longSet).buffer[1] == 4);
    assert((shortSet || longSet).buffer[2] == 5);
    
    //testing union partially filled buffer set with full buffer
    //reset longSet
    longSet.numElements = 3;
    //reset shortSet
    shortSet.buffer = new int[5];
    shortSet.numCapacity = 5;
    shortSet.numElements = 5;
    shortSet.buffer[0] = 5;
    shortSet.buffer[1] = 6;
    shortSet.buffer[2] = 7;
    shortSet.buffer[3] = 8;
    shortSet.buffer[4] = 9;
    
    assert((shortSet || longSet).numCapacity == 7);
    assert((shortSet || longSet).numElements == 7);
    assert((shortSet || longSet).buffer != NULL);
    assert((shortSet || longSet).buffer != longSet.buffer);
    assert((shortSet || longSet).buffer != shortSet.buffer);
    assert((shortSet || longSet).buffer[0] == 3);
    assert((shortSet || longSet).buffer[1] == 4);
    assert((shortSet || longSet).buffer[2] == 5);
    assert((shortSet || longSet).buffer[3] == 6);
    assert((shortSet || longSet).buffer[4] == 7);
    assert((shortSet || longSet).buffer[5] == 8);
    assert((shortSet || longSet).buffer[6] == 9);
    
    //testing union two full sets -- no elements in common
    //resetting longSet
    longSet.numElements = 10;
    shortSet.buffer = new int[6];
    shortSet.numCapacity = 6;
    shortSet.numElements = 6;
    shortSet.buffer[0] = -6;
    shortSet.buffer[1] = -5;
    shortSet.buffer[2] = -4;
    shortSet.buffer[3] = -3;
    shortSet.buffer[4] = -2;
    shortSet.buffer[5] = -1;
    assert((shortSet || longSet).numCapacity == 16);
    assert((shortSet || longSet).numElements == 16);
    assert((shortSet || longSet).buffer != NULL);
    assert((shortSet || longSet).buffer != shortSet.buffer);
    assert((shortSet || longSet).buffer != longSet.buffer);
    assert((shortSet || longSet).buffer[0] == -6);
    assert((shortSet || longSet).buffer[1] == -5);
    assert((shortSet || longSet).buffer[2] == -4);
    assert((shortSet || longSet).buffer[3] == -3);
    assert((shortSet || longSet).buffer[4] == -2);
    assert((shortSet || longSet).buffer[5] == -1);
    assert((shortSet || longSet).buffer[6] == 3);
    assert((shortSet || longSet).buffer[7] == 4);
    assert((shortSet || longSet).buffer[8] == 5);
    assert((shortSet || longSet).buffer[9] == 6);
    assert((shortSet || longSet).buffer[10] == 7);
    assert((shortSet || longSet).buffer[11] == 8);
    assert((shortSet || longSet).buffer[12] == 9);
    assert((shortSet || longSet).buffer[13] == 10);
    assert((shortSet || longSet).buffer[14] == 11);
    assert((shortSet || longSet).buffer[15] == 12);
    
    //testing union two full sets all of short found in long
    //resetting short set
    shortSet.buffer[0] = 5;
    shortSet.buffer[1] = 7;
    shortSet.buffer[2] = 8;
    shortSet.buffer[3] = 9;
    shortSet.buffer[4] = 10;
    shortSet.buffer[5] = 11;
    
    assert((shortSet || longSet).numCapacity == 10);
    assert((shortSet || longSet).numElements == 10);
    assert((shortSet || longSet).buffer != NULL);
    assert((shortSet || longSet).buffer != longSet.buffer);
    assert((shortSet || longSet).buffer != shortSet.buffer);
    assert((shortSet || longSet).buffer[0] == 3);
    assert((shortSet || longSet).buffer[1] == 4);
    assert((shortSet || longSet).buffer[2] == 5);
    assert((shortSet || longSet).buffer[3] == 6);
    assert((shortSet || longSet).buffer[4] == 7);
    assert((shortSet || longSet).buffer[5] == 8);
    assert((shortSet || longSet).buffer[6] == 9);
    assert((shortSet || longSet).buffer[7] == 10);
    assert((shortSet || longSet).buffer[8] == 11);
    assert((shortSet || longSet).buffer[9] == 12);
    
    //testing union with itself
    assert((longSet || longSet).numCapacity == 10);
    assert((longSet || longSet).numElements == 10);
    assert((longSet || longSet).buffer != NULL);
    assert((longSet || longSet).buffer != longSet.buffer);
    assert((longSet || longSet).buffer[0] == 3);
    assert((longSet || longSet).buffer[1] == 4);
    assert((longSet || longSet).buffer[2] == 5);
    assert((longSet || longSet).buffer[3] == 6);
    assert((longSet || longSet).buffer[4] == 7);
    assert((longSet || longSet).buffer[5] == 8);
    assert((longSet || longSet).buffer[6] == 9);
    assert((longSet || longSet).buffer[7] == 10);
    assert((longSet || longSet).buffer[8] == 11);
    assert((longSet || longSet).buffer[9] == 12);
    
    /**
     - ToDo: test partial and partial together.
     */
    
    /**
     - ToDo: test returning empty.
     */
    cout<<"Passed Union Tests."<<endl;
    
    /*
     * Testing Intersection
     */
    //resetting shortSet
    shortSet.buffer = NULL;
    shortSet.numCapacity = 0;
    shortSet.numElements = 0;
    
    //resetting longSet
    longSet.buffer = NULL;
    longSet.numCapacity = 0;
    longSet.numElements = 0;
    //testing intersection of empty sets
    
    assert((shortSet && longSet).numCapacity == 0);
    assert((shortSet && longSet).numElements == 0);
    assert((shortSet && longSet).buffer == NULL);
    
    //resetting longSet
    longSet.buffer = new int[10];
    longSet.numCapacity = 10;
    longSet.numElements = 10;
    longSet.buffer[0] = 3;
    longSet.buffer[1] = 4;
    longSet.buffer[2] = 5;
    longSet.buffer[3] = 6;
    longSet.buffer[4] = 7;
    longSet.buffer[5] = 8;
    longSet.buffer[6] = 9;
    longSet.buffer[7] = 10;
    longSet.buffer[8] = 11;
    longSet.buffer[9] = 12;
    
    //testing intersection of empty set and non-empty set
    assert((shortSet && longSet).numCapacity == 0);
    assert((shortSet && longSet).numElements == 0);
    assert((shortSet && longSet).buffer == NULL);
    
    //resetting shortSet
    shortSet.buffer = new int[6];
    shortSet.numCapacity = 6;
    shortSet.numElements = 6;
    shortSet.buffer[0] = -6;
    shortSet.buffer[1] = -5;
    shortSet.buffer[2] = -4;
    shortSet.buffer[3] = -3;
    shortSet.buffer[4] = -2;
    shortSet.buffer[5] = -1;
    
    //testing intersection nothing in common
        assert((shortSet && longSet).numCapacity == 0);
    assert((shortSet && longSet).numElements == 0);
    assert((shortSet && longSet).buffer == NULL);
    
    
    //resetting shortSet
    shortSet.buffer[0] = 5;
    shortSet.buffer[1] = 7;
    shortSet.buffer[2] = 8;
    shortSet.buffer[3] = 9;
    shortSet.buffer[4] = 10;
    shortSet.buffer[5] = 11;
    
    //testing intersection all short set in common
    assert((shortSet && longSet).numCapacity == 6);
    assert((shortSet && longSet).numElements == 6);
    assert((shortSet && longSet).buffer != NULL);
    assert((shortSet && longSet).buffer != shortSet.buffer);
    assert((shortSet && longSet).buffer != longSet.buffer);
    assert((shortSet && longSet).buffer[0] == 5);
    assert((shortSet && longSet).buffer[1] == 7);
    // cout << "inside buffer 2: " << (shortSet && longSet).buffer[2] << endl;
    // cout << "inside buffer 2: " << (shortSet && longSet).buffer[2] << endl;
    assert((shortSet && longSet).buffer[2] == 8);
    assert((shortSet && longSet).buffer[3] == 9);
    assert((shortSet && longSet).buffer[4] == 10);
    assert((shortSet && longSet).buffer[5] == 11);
    
    //resetting shortSet
    shortSet.buffer[3] = 70;
    shortSet.buffer[4] = 121;
    shortSet.buffer[5] = 1273;
    
    
    //testing intersection some elements in common
    assert((shortSet && longSet).numCapacity == 3);
    assert((shortSet && longSet).numElements == 3);
    assert((shortSet && longSet).buffer != NULL);
    assert((shortSet && longSet).buffer != shortSet.buffer);
    assert((shortSet && longSet).buffer != longSet.buffer);
    assert((shortSet && longSet).buffer[0] == 5);
    assert((shortSet && longSet).buffer[1] == 7);
    
    /*
     * Testing Difference
     */
    
    //resetting shortSet
    shortSet.numCapacity = 0;
    shortSet.numElements = 0;
    shortSet.buffer = NULL;
    //resetting longSet
    longSet.numCapacity = 0;
    longSet.numElements = 0;
    longSet.buffer = NULL;
    
    //testing difference empty sets both directions
    
    assert((shortSet - longSet).numCapacity == 0);
    assert((shortSet - longSet).numElements == 0);
    assert((shortSet - longSet).buffer == NULL);
    
    assert((longSet - shortSet).numCapacity == 0);
    assert((longSet - shortSet).numElements == 0);
    assert((longSet - shortSet).buffer == NULL);
    
    //resetting longSet
    longSet.buffer = new int[10];
    longSet.numCapacity = 10;
    longSet.numElements = 10;
    longSet.buffer[0] = 3;
    longSet.buffer[1] = 4;
    longSet.buffer[2] = 5;
    longSet.buffer[3] = 6;
    longSet.buffer[4] = 7;
    longSet.buffer[5] = 8;
    longSet.buffer[6] = 9;
    longSet.buffer[7] = 10;
    longSet.buffer[8] = 11;
    longSet.buffer[9] = 12;
    
    //testing one set empty difference both ways
    
    assert((shortSet - longSet).numCapacity == 0);
    assert((shortSet - longSet).numElements == 0);
    assert((shortSet - longSet).buffer == NULL);
    
    assert((longSet - shortSet).numCapacity == 10);
    assert((longSet - shortSet).numElements == 10);
    assert((longSet - shortSet).buffer != NULL);
    assert((longSet - shortSet).buffer != longSet.buffer);
    assert((longSet - shortSet).buffer[0] == 3);
    assert((longSet - shortSet).buffer[1] == 4);
    assert((longSet - shortSet).buffer[2] == 5);
    assert((longSet - shortSet).buffer[3] == 6);
    assert((longSet - shortSet).buffer[4] == 7);
    assert((longSet - shortSet).buffer[5] == 8);
    assert((longSet - shortSet).buffer[6] == 9);
    assert((longSet - shortSet).buffer[7] == 10);
    assert((longSet - shortSet).buffer[8] == 11);
    assert((longSet - shortSet).buffer[9] == 12);
    
    //testing difference for sets with same elements
    
    assert((shortSet - shortSet).numCapacity == 0);
    assert((shortSet - shortSet).numElements == 0);
    assert((shortSet - shortSet).buffer == NULL);
    
    //resetting shortSet
    shortSet.numCapacity = 6;
    shortSet.numElements = 6;
    shortSet.buffer = new int[6];
    shortSet.buffer[0] = -6;
    shortSet.buffer[1] = -5;
    shortSet.buffer[2] = -4;
    shortSet.buffer[3] = -3;
    shortSet.buffer[4] = -2;
    shortSet.buffer[5] = -1;
    
    //testing difference nothing in common both ways
    //longSet [3,4,5,6,7,8,9,10,11,12]
    assert((shortSet - longSet).numCapacity == 6);
    assert((shortSet - longSet).numElements == 6);
    assert((shortSet - longSet).buffer != NULL);
    assert((shortSet - longSet).buffer != shortSet.buffer);
    assert((shortSet - longSet).buffer != longSet.buffer);
    assert((shortSet - longSet).buffer[0] == -6);
    assert((shortSet - longSet).buffer[1] == -5);
    assert((shortSet - longSet).buffer[2] == -4);
    assert((shortSet - longSet).buffer[3] == -3);
    assert((shortSet - longSet).buffer[4] == -2);
    assert((shortSet - longSet).buffer[5] == -1);
    
    assert((longSet - shortSet).numCapacity == 10);
    assert((longSet - shortSet).numElements == 10);
    assert((longSet - shortSet).buffer != NULL);
    assert((longSet - shortSet).buffer != longSet.buffer);
    assert((longSet - shortSet).buffer != shortSet.buffer);
    assert((longSet - shortSet).buffer[0] == 3);
    assert((longSet - shortSet).buffer[1] == 4);
    assert((longSet - shortSet).buffer[2] == 5);
    assert((longSet - shortSet).buffer[3] == 6);
    assert((longSet - shortSet).buffer[4] == 7);
    assert((longSet - shortSet).buffer[5] == 8);
    assert((longSet - shortSet).buffer[6] == 9);
    assert((longSet - shortSet).buffer[7] == 10);
    assert((longSet - shortSet).buffer[8] == 11);
    assert((longSet - shortSet).buffer[9] == 12);
    
    //resetting shortSet
    shortSet.buffer[0] = -21;
    shortSet.buffer[1] = -13;
    shortSet.buffer[2] = 0;
    shortSet.buffer[3] = 1;
    shortSet.buffer[4] = 5;
    shortSet.buffer[5] = 11;
    
    //testing some elements in common both ways
    //longSet [3,4,5,6,7,8,9,10,11,12]
    assert((shortSet - longSet).numCapacity == 4);
    assert((shortSet - longSet).numElements == 4);
    assert((shortSet - longSet).buffer != NULL);
    assert((shortSet - longSet).buffer != shortSet.buffer);
    assert((shortSet - longSet).buffer != longSet.buffer);
    assert((shortSet - longSet).buffer[0] == -21);
    assert((shortSet - longSet).buffer[1] == -13);
    assert((shortSet - longSet).buffer[3] == 0);
    assert((shortSet - longSet).buffer[2] == 1);
    
    assert((longSet - shortSet).numCapacity == 8);
    assert((longSet - shortSet).numElements == 8);
    assert((longSet - shortSet).buffer != NULL);
    assert((longSet - shortSet).buffer != longSet.buffer);
    assert((longSet - shortSet).buffer != shortSet.buffer);
    assert((longSet - shortSet).buffer[0] == 3);
    assert((longSet - shortSet).buffer[1] == 4);
    assert((longSet - shortSet).buffer[2] == 6);
    assert((longSet - shortSet).buffer[3] == 7);
    assert((longSet - shortSet).buffer[4] == 8);
    assert((longSet - shortSet).buffer[5] == 9);
    assert((longSet - shortSet).buffer[6] == 10);
    assert((longSet - shortSet).buffer[7] == 12);
    
    cout<<"Passed Difference Tests."<<endl;
    
    /*
     * Testing Find
     */
    set<int>findSet;
    findSet.numCapacity = 0;
    findSet.numElements = 0;
    findSet.buffer = NULL;
    
    set<int>::iterator foundIt;
    foundIt = findSet.find(3);
    assert(foundIt.ptr == NULL);
    
    //resetting
    findSet.numCapacity = 5;
    findSet.numElements = 4;
    findSet.buffer = new int[5];
    findSet.buffer[0] = -231;
    findSet.buffer[1] = 0;
    findSet.buffer[2] = 13;
    findSet.buffer[3] = 857;
    
    //testing happy path
    foundIt = findSet.find(-231);
    assert(foundIt.ptr == findSet.buffer);
    
    foundIt = findSet.find(857);
    assert(foundIt.ptr == findSet.buffer+3);
    
    //testing non-existant
    
    foundIt = findSet.find(23);
    //assert(foundIt.ptr == NULL);
    
    cout<<"Passed find tests"<<endl;
    
    /*
     * Testing Erase
     */
    set <int> eraseSet;
    eraseSet.buffer = new int[6];
    eraseSet.numCapacity = 6;
    eraseSet.numElements = 5;
    eraseSet.buffer[0] = -500;
    eraseSet.buffer[1] = 0;
    eraseSet.buffer[2] = 7;
    eraseSet.buffer[3] = 13;
    eraseSet.buffer[4] = 23;
    
    eraseSet.erase(nullIt);
    assert(eraseSet.numCapacity == 6);
    assert(eraseSet.numElements == 5);
    assert(eraseSet.buffer[0] == -500);
    assert(eraseSet.buffer[1] == 0);
    assert(eraseSet.buffer[2] == 7);
    assert(eraseSet.buffer[3] == 13);
    assert(eraseSet.buffer[4] == 23);
    
    cout<<"Passed erase tests"<<endl;
    
    /*
     * Testing resize
     */
    set<int> emptyResizeset;
    emptyResizeset.resize(-1);
    assert(emptyResizeset.numCapacity == 0);
    assert(emptyResizeset.numElements == 0);
    assert(emptyResizeset.buffer == NULL);
    cout<<"Passed negative resize test."<<endl;
    
    emptyResizeset.resize(7);
    assert(emptyResizeset.numCapacity == 7);
    assert(emptyResizeset.numElements == 0);
    assert(emptyResizeset.buffer != NULL);
    cout<<"Passed default set resized test."<<endl;
    
    set <int> resizeSet;
    resizeSet.buffer = new int[5];
    resizeSet.numCapacity = 5;
    resizeSet.numElements = 5;
    resizeSet.buffer[0] = 7;
    resizeSet.buffer[1] = 12;
    resizeSet.buffer[2] = 10;
    resizeSet.buffer[3] = 9;
    resizeSet.buffer[4] = 8;
    //buffer: [7,12,10,9,8]
    
    int *theBuffer = resizeSet.buffer;
    resizeSet.resize(10);
    //buffer: [7,12,10,9,8,_,_,_,_,_]
    assert(theBuffer != resizeSet.buffer);
    assert(resizeSet.numCapacity = 10);
    assert(resizeSet.numElements = 5);
    assert(resizeSet.buffer[0] == 7);
    assert(resizeSet.buffer[1] == 12);
    assert(resizeSet.buffer[2] == 10);
    assert(resizeSet.buffer[3] == 9);
    assert(resizeSet.buffer[4] == 8);
    
    theBuffer = resizeSet.buffer;
    resizeSet.resize(2);
    //buffer: [7,12,10,9,8,_,_,_,_,_]
    assert(theBuffer != resizeSet.buffer);
    assert(resizeSet.numCapacity == 2);
    //assert(resizeSet.numElements == 2);
    assert(resizeSet.buffer[0] == 7);
    assert(resizeSet.buffer[1] == 12);
    
    theBuffer = resizeSet.buffer;
    resizeSet.resize(0);
    assert(resizeSet.numCapacity == 0);
    assert(resizeSet.numElements == 0);
    assert(resizeSet.buffer == NULL);
    cout << "Resize Test Passed" << endl;
    
    
    /*
     * Testing insert with resize
     */
    set<int> insertResizeSet;
    insertResizeSet.buffer = NULL;
    insertResizeSet.numCapacity = 0;
    insertResizeSet.numElements = 0;
    
    insertResizeSet.insert(21);
    assert(insertResizeSet.buffer != NULL);
    assert(insertResizeSet.numCapacity == 1);
    assert(insertResizeSet.numElements == 1);
    assert(insertResizeSet.buffer[0] = 21);
    
    int* oldBuffer = insertResizeSet.buffer;
    insertResizeSet.insert(7);
    assert(insertResizeSet.buffer != NULL);
    assert(insertResizeSet.buffer != oldBuffer);
    assert(insertResizeSet.numCapacity == 2);
    assert(insertResizeSet.numElements == 2);
    assert(insertResizeSet.buffer[0] = 7);
    assert(insertResizeSet.buffer[1] = 21);
    
    // //testing insert something that already exits
    // oldBuffer = insertResizeSet.buffer;
    // insertResizeSet.insert(7);
    // assert(insertResizeSet.buffer != NULL);
    // assert(insertResizeSet.buffer == oldBuffer);
    // assert(insertResizeSet.numCapacity == 2);
    // assert(insertResizeSet.numElements == 2);
    // assert(insertResizeSet.buffer[0] = 7);
    // assert(insertResizeSet.buffer[1] = 21);
    
    // //testing resize on insert yet again
    // oldBuffer = insertResizeSet.buffer;
    // insertResizeSet.insert(100);
    // assert(insertResizeSet.buffer != NULL);
    // assert(insertResizeSet.buffer != oldBuffer);
    // assert(insertResizeSet.numCapacity == 4);
    // assert(insertResizeSet.numElements == 3);
    // assert(insertResizeSet.buffer[0] = 7);
    // assert(insertResizeSet.buffer[1] = 21);
    // assert(insertResizeSet.buffer[2] = 100);
    
    
    // //testing no-resize on insert
    // oldBuffer = insertResizeSet.buffer;
    // insertResizeSet.insert(50);
    // assert(insertResizeSet.buffer != NULL);
    // assert(insertResizeSet.buffer != oldBuffer);
    // assert(insertResizeSet.numCapacity == 4);
    // assert(insertResizeSet.numElements == 4);
    // assert(insertResizeSet.buffer[0] = 7);
    // assert(insertResizeSet.buffer[1] = 21);
    // assert(insertResizeSet.buffer[2] = 50);
    // assert(insertResizeSet.buffer[3] = 100);
    
    
    
    
    
    
    /*
     * Testing = operator and copy constructor
     */
    set <int> setToCopy;
    setToCopy.numCapacity = 8;
    setToCopy.numElements = 8;
    setToCopy.buffer = new int[setToCopy.numCapacity];
    for (int i = 0; i < setToCopy.numCapacity; i++)
    {
        setToCopy.buffer[i]=i*i+1;
    }
    set <int> setAssignedCopy;
    setAssignedCopy = setToCopy;
    assert(setAssignedCopy.numCapacity == 8);
    assert(setAssignedCopy.numElements == 8);
    assert(setAssignedCopy.buffer != setToCopy.buffer);
    assert(setAssignedCopy.buffer[0] == 1);
    assert(setAssignedCopy.buffer[1] == 2);
    assert(setAssignedCopy.buffer[2] == 5);
    assert(setAssignedCopy.buffer[3] == 10);
    assert(setAssignedCopy.buffer[4] == 17);
    assert(setAssignedCopy.buffer[5] == 26);
    assert(setAssignedCopy.buffer[6] == 37);
    assert(setAssignedCopy.buffer[7] == 50);
    cout << "(full) = Operator Test Passed" << endl;
    
    set <int> setCopy(setToCopy);
    assert(setCopy.numCapacity == 8);
    assert(setCopy.numElements == 8);
    assert(setCopy.buffer != setToCopy.buffer);
    assert(setCopy.numCapacity == 8);
    assert(setCopy.buffer[0] == 1);
    assert(setCopy.buffer[1] == 2);
    assert(setCopy.buffer[2] == 5);
    assert(setCopy.buffer[3] == 10);
    assert(setCopy.buffer[4] == 17);
    assert(setCopy.buffer[5] == 26);
    assert(setCopy.buffer[6] == 37);
    assert(setCopy.buffer[7] == 50);
    cout << "(Full) Copy Constructor Test Passed" << endl;
    
    /*
     * Resetting to not full set
     */
    
    setToCopy.numElements = 3;
    
    set <int> notFullsetAssignedCopy;
    notFullsetAssignedCopy = setToCopy;
    assert(notFullsetAssignedCopy.numCapacity == 3);
    assert(notFullsetAssignedCopy.numElements == 3);
    assert(notFullsetAssignedCopy.buffer != setToCopy.buffer);
    assert(notFullsetAssignedCopy.buffer[0] == 1);
    assert(notFullsetAssignedCopy.buffer[1] == 2);
    assert(notFullsetAssignedCopy.buffer[2] == 5);
    cout << "(Not full) = Operator Test Passed" << endl;
    
    set <int> notFullSetCopy(setToCopy);
    assert(notFullSetCopy.numCapacity == 3);
    assert(notFullSetCopy.numElements == 3);
    assert(notFullSetCopy.buffer != setToCopy.buffer);
    assert(notFullSetCopy.buffer[0] == 1);
    assert(notFullSetCopy.buffer[1] == 2);
    assert(notFullSetCopy.buffer[2] == 5);
    cout << "(Not Full) Copy Constructor Test Passed" << endl;
    
    
    
    /*
     * Testing insert for Non-Integer set Behavior (Just to Make Sure set Works For Other Types)
     */
    set <string> stringset;
    
    stringset.insert("Hello");
    stringset.insert("It's me");
    stringset.insert("Are you wondering");
    assert(stringset.numCapacity == 4);
    assert(stringset.buffer[0] == "Are you wondering");
    assert(stringset.buffer[1] == "Hello");
    assert(stringset.buffer[2] == "It's me");
    
    cout << "This set can hold strings!!!!" << endl;
    
    
    
    return 0;
}
