/*
 * main.cpp
 *
 *  Created by Lee Barney on 09/18/18.
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
#include "queue.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;



int main(int argc, const char* argv[]) {
    
    /*
     * Testing default constructor
     */
    queue <int> defaultQueue;
    assert(defaultQueue.numCapacity == 0);
    assert(defaultQueue.numPush == 0);
    assert(defaultQueue.numPop == 0);
    assert(defaultQueue.buffer == NULL);
    cout << "Default Constructor Test Passed" << endl;
    
    
    
    /*
     * Testing Size
     */
    queue <int> sizeTestQueue;
    
    sizeTestQueue.numCapacity = 8;
    sizeTestQueue.numPush = 4;
    sizeTestQueue.numPop = 0;
    assert(sizeTestQueue.size() == 4);
    
    sizeTestQueue.numPop = 4;
    assert(sizeTestQueue.size() == 0);
    
    sizeTestQueue.numPop = 2;
    assert(sizeTestQueue.size() == 2);
    
    
    sizeTestQueue.numPush = 32;
    sizeTestQueue.numPop = 29;
    assert(sizeTestQueue.size() == 3);
    
    cout << "Size Tests Passed" << endl;
    
    /*
     * Testing Capacity
     */
    assert(sizeTestQueue.capacity() == 8);
    sizeTestQueue.numCapacity = 0;
    assert(sizeTestQueue.capacity() == 0);
    cout << "Capacity Tests Passed" << endl;
    
    /*
     * Resetting for further use
     */
    sizeTestQueue.numCapacity = 8;
    sizeTestQueue.numPush = 8;
    sizeTestQueue.numPop = 0;
    sizeTestQueue.buffer = new int[sizeTestQueue.numCapacity];
    for (int i = 0; i < sizeTestQueue.numCapacity; i++) {
        sizeTestQueue.buffer[i]=i*i+1;
    }
    /*
     * Testing Clear
     */
    sizeTestQueue.clear();
    assert(sizeTestQueue.numCapacity == 8);
    assert(sizeTestQueue.numPush == 0);
    assert(sizeTestQueue.numPop == 0);
    assert(sizeTestQueue.buffer != NULL);
    cout << "Clear Test Passed" << endl;
    
    /*
     * Testing Empty
     */
    sizeTestQueue.numPush = 3;
    sizeTestQueue.numPop = 2;
    assert(!sizeTestQueue.empty());
    
    sizeTestQueue.numPop = 3;
    
    assert(sizeTestQueue.empty());
    cout << "Empty Tests Passed" << endl;
    
    /*
     * Testing resize
     */
    queue<int> emptyResizeQueue;
    emptyResizeQueue.resize(-1);
    assert(emptyResizeQueue.numCapacity == 0);
    assert(emptyResizeQueue.numPush == 0);
    assert(emptyResizeQueue.numPop == 0);
    assert(emptyResizeQueue.buffer == NULL);
    cout<<"Passed negative resize test."<<endl;
    
    emptyResizeQueue.resize(7);
    assert(emptyResizeQueue.numCapacity == 7);
    assert(emptyResizeQueue.numPush == 0);
    assert(emptyResizeQueue.numPop == 0);
    assert(emptyResizeQueue.buffer != NULL);
    cout<<"Passed default queue resized test."<<endl;
    
    queue <int> resizeQueue;
    resizeQueue.buffer = new int[5];
    resizeQueue.numCapacity = 5;
    resizeQueue.numPush = 5;
    resizeQueue.numPop = 0;
    resizeQueue.buffer[0] = 7;
    resizeQueue.buffer[1] = 12;
    resizeQueue.buffer[2] = 10;
    resizeQueue.buffer[3] = 9;
    resizeQueue.buffer[4] = 8;
    
    int *theBuffer = resizeQueue.buffer;
    resizeQueue.resize(10);
    assert(theBuffer != resizeQueue.buffer);
    assert(resizeQueue.numCapacity = 10);
    assert(resizeQueue.numPush = 5);
    assert(resizeQueue.numPop == 0);
    assert(resizeQueue.buffer[0] == 7);
    assert(resizeQueue.buffer[1] == 12);
    assert(resizeQueue.buffer[2] == 10);
    assert(resizeQueue.buffer[3] == 9);
    assert(resizeQueue.buffer[4] == 8);
    
    theBuffer = resizeQueue.buffer;
    //reset
    delete [] resizeQueue.buffer;
    resizeQueue.buffer = new int[5];
    theBuffer = resizeQueue.buffer;
    resizeQueue.numCapacity = 5;
    resizeQueue.numPush = 18;
    resizeQueue.numPop = 13;
    resizeQueue.buffer[0] = 7;
    resizeQueue.buffer[1] = 12;
    resizeQueue.buffer[2] = 10;
    resizeQueue.buffer[3] = 9;
    resizeQueue.buffer[4] = 8;
    
    resizeQueue.resize(10);
    assert(theBuffer != resizeQueue.buffer);
    assert(resizeQueue.numCapacity = 10);
    assert(resizeQueue.numPush == 5);
    assert(resizeQueue.numPop == 0);
    assert(resizeQueue.buffer[0] == 9);
    assert(resizeQueue.buffer[1] == 8);
    assert(resizeQueue.buffer[2] == 7);
    assert(resizeQueue.buffer[3] == 12);
    assert(resizeQueue.buffer[4] == 10);
    
    
    
    theBuffer = resizeQueue.buffer;
    resizeQueue.resize(2);
    assert(theBuffer != resizeQueue.buffer);
    assert(resizeQueue.numCapacity == 2);
    assert(resizeQueue.numPush == 2);
    assert(resizeQueue.numPop == 0);
    assert(resizeQueue.buffer[0] == 9);
    assert(resizeQueue.buffer[1] == 8);
    
    theBuffer = resizeQueue.buffer;
    resizeQueue.resize(0);
    assert(resizeQueue.numCapacity == 0);
    assert(resizeQueue.numPush == 0);
    assert(resizeQueue.numPop == 0);
    assert(resizeQueue.buffer == NULL);
    cout << "Resize Test Passed" << endl;
    
    /*
     * Testing iHead and iTail
     */
    queue <int> headTailQueue;
    headTailQueue.buffer = new int[8];
    headTailQueue.numCapacity = 8;
    headTailQueue.numPush = 0;
    headTailQueue.numPop = 0;
    assert(headTailQueue.iHead() == 0);
    assert(headTailQueue.iTail() == -1);
    
    
    headTailQueue.numPush = 1;
    headTailQueue.numPop = 0;
    assert(headTailQueue.iHead() == 0);
    assert(headTailQueue.iTail() == 0);
    
    
    headTailQueue.numPush = 2;
    headTailQueue.numPop = 0;
    assert(headTailQueue.iHead() == 0);
    assert(headTailQueue.iTail() == 1);
    
    
    headTailQueue.numPush = 2;
    headTailQueue.numPop = 1;
    assert(headTailQueue.iHead() == 1);
    assert(headTailQueue.iTail() == 1);
    
    
    headTailQueue.numPush = 2;
    headTailQueue.numPop = 2;
    assert(headTailQueue.iHead() == 2);
    assert(headTailQueue.iTail() == 1);
    
    
    headTailQueue.numPush = 21;
    headTailQueue.numPop = 17;
    assert(headTailQueue.iHead() == 1);
    assert(headTailQueue.iTail() == 4);
    
    
    /*
     * Testing push with resizing
     */
    queue <int> pushResizeQueue;
    pushResizeQueue.push(1);
    assert(pushResizeQueue.numCapacity == 1);
    assert(pushResizeQueue.numPush == 1);
    assert(pushResizeQueue.numPop == 0);
    assert(pushResizeQueue.buffer[0] == 1);
    cout << "Push with resize First ElementTest Passed" << endl;
    
    pushResizeQueue.push(5);
    assert(pushResizeQueue.numCapacity == 2);
    assert(pushResizeQueue.numPush == 2);
    assert(pushResizeQueue.numPop == 0);
    assert(pushResizeQueue.buffer[0] == 1);
    assert(pushResizeQueue.buffer[1] == 5);
    cout << "Push with resize Second Element Test Passed" << endl;
    
    pushResizeQueue.push(10);
    assert(pushResizeQueue.numCapacity == 4);
    assert(pushResizeQueue.numPush == 3);
    assert(pushResizeQueue.numPop == 0);
    assert(pushResizeQueue.buffer[0] == 1);
    assert(pushResizeQueue.buffer[1] == 5);
    assert(pushResizeQueue.buffer[2] == 10);
    cout << "Push with resize Third Element Test Passed" << endl;
    
    pushResizeQueue.push(11);
    assert(pushResizeQueue.numCapacity == 4);
    assert(pushResizeQueue.numPush == 4);
    assert(pushResizeQueue.numPop == 0);
    assert(pushResizeQueue.buffer[0] == 1);
    assert(pushResizeQueue.buffer[1] == 5);
    assert(pushResizeQueue.buffer[2] == 10);
    assert(pushResizeQueue.buffer[3] == 11);
    cout << "Push with resize Fourth Element Test Passed" << endl;
    
    pushResizeQueue.push(13);
    assert(pushResizeQueue.numCapacity == 8);
    assert(pushResizeQueue.numPush == 5);
    assert(pushResizeQueue.numPop == 0);
    assert(pushResizeQueue.buffer[0] == 1);
    assert(pushResizeQueue.buffer[1] == 5);
    assert(pushResizeQueue.buffer[2] == 10);
    assert(pushResizeQueue.buffer[3] == 11);
    assert(pushResizeQueue.buffer[4] == 13);
    cout << "Push with resize Fifth Element Test Passed" << endl;
    
    /*
     * Testing Pop
     */
    
    
    
    /*
     * Testing = operator and copy constructor
     */
    queue <int> queueToCopy;
    queueToCopy.numCapacity = 8;
    queueToCopy.numPush = 8;
    queueToCopy.numPop = 0;
    queueToCopy.buffer = new int[queueToCopy.numCapacity];
    for (int i = 0; i < queueToCopy.numCapacity; i++) {
        queueToCopy.buffer[i]=i*i+1;
    }
    queue <int> queueAssignedCopy;
    queueAssignedCopy = queueToCopy;
    assert(queueAssignedCopy.numCapacity == 8);
    assert(queueAssignedCopy.numPush == 8);
    assert(queueAssignedCopy.numPop == 0);
    assert(queueAssignedCopy.buffer != queueToCopy.buffer);
    assert(queueAssignedCopy.buffer[0] == 1);
    assert(queueAssignedCopy.buffer[1] == 2);
    assert(queueAssignedCopy.buffer[2] == 5);
    assert(queueAssignedCopy.buffer[3] == 10);
    assert(queueAssignedCopy.buffer[4] == 17);
    assert(queueAssignedCopy.buffer[5] == 26);
    assert(queueAssignedCopy.buffer[6] == 37);
    assert(queueAssignedCopy.buffer[7] == 50);
    cout << "(full) = Operator Test Passed" << endl;
    
    queue <int> queueCopy(queueToCopy);
    assert(queueCopy.numCapacity == 8);
    assert(queueCopy.numPush == 8);
    assert(queueCopy.numPop == 0);
    assert(queueCopy.buffer != queueToCopy.buffer);
    assert(queueCopy.numCapacity == 8);
    assert(queueCopy.buffer[0] == 1);
    assert(queueCopy.buffer[1] == 2);
    assert(queueCopy.buffer[2] == 5);
    assert(queueCopy.buffer[3] == 10);
    assert(queueCopy.buffer[4] == 17);
    assert(queueCopy.buffer[5] == 26);
    assert(queueCopy.buffer[6] == 37);
    assert(queueCopy.buffer[7] == 50);
    cout << "(Full) Copy Constructor Test Passed" << endl;
    
    /*
     * Resetting to not full queue
     */
    
    queueToCopy.numPop = 5;
    
    // queue <int> notFullQueueAssignedCopy;
    // notFullQueueAssignedCopy = queueToCopy;
    // assert(notFullQueueAssignedCopy.numCapacity == 3);
    // assert(notFullQueueAssignedCopy.numPush == 3);
    // assert(notFullQueueAssignedCopy.numPop == 0);
    // assert(notFullQueueAssignedCopy.buffer != queueToCopy.buffer);
    // assert(notFullQueueAssignedCopy.buffer[0] == 26);
    // assert(notFullQueueAssignedCopy.buffer[1] == 37);
    // assert(notFullQueueAssignedCopy.buffer[2] == 50);
    // cout << "(Not full) = Operator Test Passed" << endl;
    
    // queue <int> notFullQueueCopy(queueToCopy);
    // assert(notFullQueueCopy.numCapacity == 3);
    // assert(notFullQueueCopy.numPush == 3);
    // assert(notFullQueueCopy.numPop == 0);
    // assert(notFullQueueCopy.buffer != queueToCopy.buffer);
    // assert(notFullQueueCopy.buffer[0] == 26);
    // assert(notFullQueueCopy.buffer[1] == 37);
    // assert(notFullQueueCopy.buffer[2] == 50);
    // cout << "(Not Full) Copy Constructor Test Passed" << endl;
    
    
    /*
     * Testing back
     */
    
    queue<int> frontBackQueue;
    frontBackQueue.numPush = 0;
    frontBackQueue.numPop = 0;
    frontBackQueue.numCapacity = 16;
    try{
        int& theBackRef = frontBackQueue.back();
        assert(false);
    }
    catch(const char* message){
        assert(strcmp(message, "Error: asking for back of empty queue.") == 0);
    }
    //simulating use
    frontBackQueue.buffer = new int[16];
    for (int i = 0; i < 16; i++) {
        frontBackQueue.buffer[i] = 2*i;
    }
    frontBackQueue.numPush = 8;
    frontBackQueue.numPop = 4;
    assert(frontBackQueue.back() == 14);
    frontBackQueue.back() = 15;
    assert(frontBackQueue.buffer[7] == 15);
    
    
    //reset queue
    frontBackQueue.buffer = new int[16];
    for (int i = 0; i < 16; i++) {
        frontBackQueue.buffer[i] = 2*i;
    }
    frontBackQueue.numPush = 0;
    frontBackQueue.numPop = 0;
    frontBackQueue.numCapacity = 16;
    /*
     * Testing front
     */
    try{
        int& theFrontRef = frontBackQueue.front();
        assert(false);
    }
    catch(const char* message){
        assert(strcmp(message, "Error: asking for front of empty queue.") == 0);
    }
    
    frontBackQueue.numPush = 8;
    frontBackQueue.numPop = 4;
    
    assert(frontBackQueue.front() == 8);
    frontBackQueue.front() = 9;
    assert(frontBackQueue.buffer[4] == 9);
    
    /*
     * Testing push for Non-Integer Queue Behavior (Just to Make Sure queue Works For Other Types)
     */
    queue <string> stringQueue;
    
    stringQueue.push("Hello");
    stringQueue.push("It's me");
    stringQueue.push("I was wondering");
    assert(stringQueue.numCapacity == 4);
    assert(stringQueue.buffer[0] == "Hello");
    assert(stringQueue.buffer[1] == "It's me");
    assert(stringQueue.buffer[2] == "I was wondering");
    
    cout << "This queue can hold strings!!!!" << endl;
    
    
    
    return 0;
}
