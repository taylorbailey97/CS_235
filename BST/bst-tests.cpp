/*
 * main.cpp
 *
 *  Created by Lee Barney on 11/1/18.
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
#include "bst.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;

int main(int argc, const char * argv[]) {
    
    /*
     * Testing default node constructor
     */
    BST<int>::BNode defaultNode;
    assert(defaultNode.pLeft == NULL);
    assert(defaultNode.pRight == NULL);
    assert(defaultNode.pParent == NULL);
    
    /*
     * Testing node constructor with data
     */
    BST<int>::BNode dataNode;
    assert(dataNode.data == 4);
    assert(dataNode.pLeft == NULL);
    assert(dataNode.pRight == NULL);
    assert(dataNode.pParent == NULL);
    
    cout<<"Passed Node Constructor Tests"<<endl;
    
    /*
     * Testing node destructor
     */
    unit_testing_delete_call_counter = 0;
    BST<int>::BNode* nodeToDelete = new BST<int>::BNode();
    delete nodeToDelete;
    assert(unit_testing_delete_call_counter == 1);
    //When done with a pointer set it to NULL so you don't create a zombie pointer.
    nodeToDelete = NULL;
    
    cout<<"Passed Node Destructor Test"<<endl;
    
    /*
     * Testing default list constructor
     */
    BST <int> defaultBST;
    assert(defaultBST.root == NULL);
    assert(defaultBST.numElements == 0);
    cout << "Default BST Constructor Test Passed" << endl;
    
    
    /*
     * Testing size and empty
     */
    BST<int> sizedTree;
    sizedTree.numElements = 0;
    assert(sizedTree.size() == 0);
    assert(sizedTree.empty());
    sizedTree.numElements = 32;
    assert(sizedTree.size() == 32);
    assert(!sizedTree.empty());
    cout<<"BST Size and Empty Tests Passed"<<endl;
    
    /*
     * Testing BST copy constructor
     */
    BST<int> bstToCopy;
    bstToCopy.numElements = 0;
    bstToCopy.root = NULL;
    
    //testing copy of empty list
    BST<int>emptyBstCopy(bstToCopy);
    assert(emptyBstCopy.numElements == 0);
    assert(emptyBstCopy.root == NULL);
    
    //Generating small BST with the values                              |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5             9             11
    
    //reusing bstToCopy
    bstToCopy.numElements = 6;
    bstToCopy.root = new BST<int>::BNode();
    bstToCopy.root->data = 7;
    
    BST<int>::BNode* rootRight = new BST<int>::BNode();
    rootRight->data = 10;
    rootRight->pParent = bstToCopy.root;
    bstToCopy.root->pRight = rootRight;
    
    BST<int>::BNode* rootRightRight = new BST<int>::BNode();
    rootRightRight->data = 11;
    rootRightRight->pParent = rootRight;
    rootRight->pRight = rootRightRight;
    
    BST<int>::BNode* rootRightLeft = new BST<int>::BNode();
    rootRightLeft->data = 9;
    rootRightLeft->pParent = rootRight;
    rootRight->pLeft = rootRightLeft;
    
    BST<int>::BNode* rootLeft = new BST<int>::BNode();
    rootLeft->data = 6;
    rootLeft->pRight = NULL;
    rootLeft->pParent = bstToCopy.root;
    bstToCopy.root->pLeft = rootLeft;
    
    
    BST<int>::BNode* rootLeftLeft = new BST<int>::BNode();
    rootLeftLeft->data = 5;
    rootLeftLeft->pRight = NULL;
    rootLeftLeft->pLeft = NULL;
    rootLeftLeft->pParent = rootLeft;
    rootLeft->pLeft = rootLeftLeft;
    
    //testing copy of non-empty tree. Making sure it is a deep copy.
    //Using BST                                                         |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5             9             11
    BST<int> bstCopy(bstToCopy);
    assert(bstCopy.root != NULL);
    assert(bstCopy.root != bstToCopy.root);
    assert(bstCopy.root->data == 7);
    assert(bstCopy.numElements == 6);
    
    assert(bstCopy.root->pLeft != NULL);
    assert(bstCopy.root->pLeft != bstToCopy.root->pLeft);
    assert(bstCopy.root->pLeft->data == 6);
    assert(bstCopy.root->pLeft->pRight == NULL);
    
    assert(bstCopy.root->pLeft->pLeft != NULL);
    assert(bstCopy.root->pLeft->pLeft != bstToCopy.root->pLeft->pLeft);
    assert(bstCopy.root->pLeft->pLeft->data == 5);
    assert(bstCopy.root->pLeft->pLeft->pRight == NULL);
    assert(bstCopy.root->pLeft->pLeft->pLeft == NULL);
    
    assert(bstCopy.root->pRight != NULL);
    assert(bstCopy.root->pRight != bstToCopy.root->pRight);
    assert(bstCopy.root->pRight->data == 10);
    
    assert(bstCopy.root->pRight->pLeft != NULL);
    assert(bstCopy.root->pRight->pLeft != bstToCopy.root->pRight->pLeft);
    assert(bstCopy.root->pRight->pLeft->data == 9);
    assert(bstCopy.root->pRight->pLeft->pLeft == NULL);
    assert(bstCopy.root->pRight->pLeft->pRight == NULL);
    
    assert(bstCopy.root->pRight->pRight != NULL);
    assert(bstCopy.root->pRight->pRight != bstToCopy.root->pRight->pLeft);
    assert(bstCopy.root->pRight->pRight->data == 11);
    assert(bstCopy.root->pRight->pRight->pLeft == NULL);
    assert(bstCopy.root->pRight->pRight->pRight == NULL);
    
    cout<<"Passed BST Copy Constructor Test"<<endl;
    
    
    /*
     * Testing BST Clear
     */
    
    BST<int> bstToClear;
    //Generating small BST with the values                              |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5             9             11
    
    bstToClear.root = new BST<int>::BNode();
    bstToClear.root->data = 7;
    
    BST<int>::BNode* clearRootRight = new BST<int>::BNode();
    clearRootRight->data = 10;
    clearRootRight->pParent = bstToClear.root;//(7)
    bstToClear.root->pRight = clearRootRight;//(10)
    
    BST<int>::BNode* clearRootRightRight = new BST<int>::BNode();
    clearRootRightRight->data = 11;
    clearRootRightRight->pParent = clearRootRight;//(10)
    clearRootRight->pRight = clearRootRightRight;//(11)
    
    BST<int>::BNode* clearRootRightLeft = new BST<int>::BNode();
    clearRootRightLeft->data = 9;
    clearRootRightLeft->pParent = clearRootRight;//(10)
    clearRootRight->pLeft = clearRootRightLeft;//(9)
    
    BST<int>::BNode* clearRootLeft = new BST<int>::BNode();
    clearRootLeft->data = 6;
    clearRootLeft->pRight = NULL;
    clearRootLeft->pParent = bstToClear.root;//(7)
    bstToClear.root->pLeft = clearRootLeft;//(6)
    
    
    BST<int>::BNode* clearRootLeftLeft = new BST<int>::BNode();
    clearRootLeftLeft->data = 5;
    clearRootLeftLeft->pRight = NULL;
    clearRootLeftLeft->pLeft = NULL;
    clearRootLeftLeft->pParent = clearRootLeft;//(6)
    clearRootLeft->pLeft = clearRootLeftLeft;//(5)
    
    
    unit_testing_delete_call_counter = 0;
    bstToClear.clear();
    assert(unit_testing_delete_call_counter == 6);//delete the list and each of the six nodes
    
    cout<<"Passed BST Clear Tests"<<endl;
    
    /*
     * Testing BST destructor
     */
    
    unit_testing_delete_call_counter = 0;
    BST<int>* bstToDelete = new BST<int>();
    delete bstToDelete;
    assert(unit_testing_delete_call_counter == 1);
    
    
    //killing potential zombie
    bstToDelete = NULL;
    
    //reset deletion counter
    unit_testing_delete_call_counter = 0;
    //Generating small BST with the values                              |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5             9             11
    
    //reusing bstToDelete
    bstToDelete = new BST<int>();
    bstToDelete->root = new BST<int>::BNode();
    bstToDelete->root->data = 7;
    
    BST<int>::BNode* delRootRight = new BST<int>::BNode();
    delRootRight->data = 10;
    delRootRight->pParent = bstToDelete->root;//(7)
    bstToDelete->root->pRight = delRootRight;//(10)
    
    BST<int>::BNode* delRootRightRight = new BST<int>::BNode();
    delRootRightRight->data = 11;
    delRootRightRight->pParent = delRootRight;//(10)
    delRootRight->pRight = delRootRightRight;//(11)
    
    BST<int>::BNode* delRootRightLeft = new BST<int>::BNode();
    delRootRightLeft->data = 9;
    delRootRightLeft->pParent = delRootRight;//(10)
    delRootRight->pLeft = delRootRightLeft;//(9)
    
    BST<int>::BNode* delRootLeft = new BST<int>::BNode();
    delRootLeft->data = 6;    delRootLeft->pRight = NULL;
    delRootLeft->pParent = bstToDelete->root;//(7)
    bstToDelete->root->pLeft = delRootLeft;//(6)
    
    
    BST<int>::BNode* delRootLeftLeft = new BST<int>::BNode();
    delRootLeftLeft->data = 5;
    delRootLeftLeft->pRight = NULL;
    delRootLeftLeft->pLeft = NULL;
    delRootLeftLeft->pParent = delRootLeft;//(6)
    delRootLeft->pLeft = delRootLeftLeft;//(5)
    
    
    unit_testing_delete_call_counter = 0;
    delete bstToDelete;
    assert(unit_testing_delete_call_counter == 7);//delete the list and each of the six nodes
    
    bstToDelete = NULL;//kill potential zombie
    
    cout<<"Passed BST Deletion Tests"<<endl;
    
    /*
     * Testing BST Insert
     */
    
    //Generating small BST with the values                              |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5             9             11
    
    BST<int> insertIntoBST;
    insertIntoBST.numElements = 6;
    insertIntoBST.root = new BST<int>::BNode();
    insertIntoBST.root->data = 7;
    
    BST<int>::BNode* insertRootRight = new BST<int>::BNode();
    insertRootRight->data = 10;
    insertRootRight->pParent = insertIntoBST.root;//(7)
    insertIntoBST.root->pRight = insertRootRight;//(10)
    
    BST<int>::BNode* insertRootRightRight = new BST<int>::BNode();
    insertRootRightRight->data = 11;
    insertRootRightRight->pParent = insertRootRight;//(10)
    insertRootRight->pRight = insertRootRightRight;//(11)
    
    BST<int>::BNode* insertRootRightLeft = new BST<int>::BNode();
    insertRootRightLeft->data = 9;
    insertRootRightLeft->pParent = insertRootRight;//(10)
    insertRootRight->pLeft = insertRootRightLeft;//(9)
    
    BST<int>::BNode* insertRootLeft = new BST<int>::BNode();
    insertRootLeft->data = 6;
    insertRootLeft->pRight = NULL;
    insertRootLeft->pParent = insertIntoBST.root;//(7)
    insertIntoBST.root->pLeft = insertRootLeft;//(6)
    
    
    BST<int>::BNode* insertRootLeftLeft = new BST<int>::BNode();
    insertRootLeftLeft->data = 5;
    insertRootLeftLeft->pRight = NULL;
    insertRootLeftLeft->pLeft = NULL;
    insertRootLeftLeft->pParent = insertRootLeft;//(6)
    insertRootLeft->pLeft = insertRootLeftLeft;//(5)
    
    insertIntoBST.insert(8);
    //Should be BST with the values                                      |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6---     ------10------
    //                                                       |             |             |
    //                                                       5         ----9             11
    //                                                                 |
    //                                                                 8
    assert(insertIntoBST.numElements == 7);
    assert(insertIntoBST.root->data == 7);
    assert(insertIntoBST.root->pLeft->data == 6);
    assert(insertIntoBST.root->pLeft->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->data == 5);
    assert(insertIntoBST.root->pLeft->pLeft->pParent == insertIntoBST.root->pLeft);
    assert(insertIntoBST.root->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft == NULL);
    assert(insertIntoBST.root->pRight->data == 10);
    assert(insertIntoBST.root->pRight->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pRight->pRight->data == 11);
    assert(insertIntoBST.root->pRight->pRight->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pRight->pRight == NULL);
    assert(insertIntoBST.root->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pLeft->data == 9);
    assert(insertIntoBST.root->pRight->pLeft->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->data ==8);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pParent == insertIntoBST.root->pRight->pLeft);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pLeft == NULL);
    
    insertIntoBST.insert(20);
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                       5         ----9             11-------
    //                                                                 |                          |
    //                                                                 8                          20
    assert(insertIntoBST.numElements == 8);
    assert(insertIntoBST.root->data == 7);
    assert(insertIntoBST.root->pLeft->data == 6);
    assert(insertIntoBST.root->pLeft->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->data == 5);
    assert(insertIntoBST.root->pLeft->pLeft->pParent == insertIntoBST.root->pLeft);
    assert(insertIntoBST.root->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft == NULL);
    assert(insertIntoBST.root->pRight->data == 10);
    assert(insertIntoBST.root->pRight->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pRight->pRight->data == 11);
    assert(insertIntoBST.root->pRight->pRight->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight != NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->data == 20);
    assert(insertIntoBST.root->pRight->pRight->pRight->pParent == insertIntoBST.root->pRight->pRight);
    assert(insertIntoBST.root->pRight->pRight->pRight->pRight == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pLeft->data == 9);
    assert(insertIntoBST.root->pRight->pLeft->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->data ==8);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pParent == insertIntoBST.root->pRight->pLeft);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pLeft == NULL);
    
    insertIntoBST.insert(3);
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                   ----5         ----9---          11-------
    //                                                  |             |                           |
    //                                                  3             8                           20
    assert(insertIntoBST.numElements == 9);
    assert(insertIntoBST.root->data == 7);
    assert(insertIntoBST.root->pLeft->data == 6);
    assert(insertIntoBST.root->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->data == 5);
    assert(insertIntoBST.root->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->data == 3);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pParent == insertIntoBST.root->pLeft->pLeft);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft == NULL);
    assert(insertIntoBST.root->pRight->data == 10);
    assert(insertIntoBST.root->pRight->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pRight->pRight->data == 11);
    assert(insertIntoBST.root->pRight->pRight->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight != NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->data == 20);
    assert(insertIntoBST.root->pRight->pRight->pRight->pParent == insertIntoBST.root->pRight->pRight);
    assert(insertIntoBST.root->pRight->pRight->pRight->pRight == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pLeft->data == 9);
    assert(insertIntoBST.root->pRight->pLeft->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->data ==8);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pParent == insertIntoBST.root->pRight->pLeft);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pLeft == NULL);
    
    insertIntoBST.insert(4);
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                   ----5         ----9---          11-------
    //                                                  |             |                           |
    //                                                  3---          8                           20
    //                                                      |
    //                                                      4
    assert(insertIntoBST.numElements == 10);
    assert(insertIntoBST.root->data == 7);
    assert(insertIntoBST.root->pLeft->data == 6);
    assert(insertIntoBST.root->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->data == 5);
    assert(insertIntoBST.root->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->data == 3);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pParent == insertIntoBST.root->pLeft->pLeft);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight->data == 4);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->data == 10);
    assert(insertIntoBST.root->pRight->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pRight->pRight->data == 11);
    assert(insertIntoBST.root->pRight->pRight->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight != NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->data == 20);
    assert(insertIntoBST.root->pRight->pRight->pRight->pParent == insertIntoBST.root->pRight->pRight);
    assert(insertIntoBST.root->pRight->pRight->pRight->pRight == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pLeft->data == 9);
    assert(insertIntoBST.root->pRight->pLeft->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->data ==8);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pParent == insertIntoBST.root->pRight->pLeft);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pLeft == NULL);
    
    insertIntoBST.insert(2);
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                   ----5         ----9---          11-------
    //                                                  |             |                           |
    //                                              ----3---          8                           20
    //                                             |        |
    //                                             2        4
    assert(insertIntoBST.numElements == 11);
    assert(insertIntoBST.root->data == 7);
    assert(insertIntoBST.root->pLeft->data == 6);
    assert(insertIntoBST.root->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->data == 5);
    assert(insertIntoBST.root->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->data == 3);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pParent == insertIntoBST.root->pLeft->pLeft);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight->data == 4);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pRight->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft->data == 2);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pLeft->pLeft->pLeft->pLeft->pLeft == NULL);
    assert(insertIntoBST.root->pRight->data == 10);
    assert(insertIntoBST.root->pRight->pParent == insertIntoBST.root);
    assert(insertIntoBST.root->pRight->pRight->data == 11);
    assert(insertIntoBST.root->pRight->pRight->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight != NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->data == 20);
    assert(insertIntoBST.root->pRight->pRight->pRight->pParent == insertIntoBST.root->pRight->pRight);
    assert(insertIntoBST.root->pRight->pRight->pRight->pRight == NULL);
    assert(insertIntoBST.root->pRight->pRight->pRight->pLeft == NULL);
    assert(insertIntoBST.root->pRight->pLeft->data == 9);
    assert(insertIntoBST.root->pRight->pLeft->pParent == insertIntoBST.root->pRight);
    assert(insertIntoBST.root->pRight->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft != NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->data ==8);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pParent == insertIntoBST.root->pRight->pLeft);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pRight == NULL);
    assert(insertIntoBST.root->pRight->pLeft->pLeft->pLeft == NULL);
    
    BST<int> buildBST;
    buildBST.insert(10);
    //should be                                                     |
    //                                                              10
    assert(buildBST.numElements == 1);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pRight == NULL);
    assert(buildBST.root->pLeft == NULL);
    assert(buildBST.root->pParent == NULL);
    
    buildBST.insert(5);
    //should be                                                     |
    //                                                       -------10
    //                                                      |
    //                                                      5
    assert(buildBST.numElements == 2);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pRight == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight == NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    
    buildBST.insert(11);
    //should be                                                     |
    //                                                       -------10-------
    //                                                      |                |
    //                                                      5                11
    assert(buildBST.numElements == 3);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pRight != NULL);
    assert(buildBST.root->pRight->data == 11);
    assert(buildBST.root->pRight->pParent = buildBST.root);
    assert(buildBST.root->pRight->pRight == NULL);
    assert(buildBST.root->pRight->pLeft == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight == NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    
    buildBST.insert(9);
    //should be                                                     |
    //                                                       -------10-------
    //                                                      |                |
    //                                                      5----            11
    //                                                           |
    //                                                           9
    assert(buildBST.numElements == 4);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pRight != NULL);
    assert(buildBST.root->pRight->data == 11);
    assert(buildBST.root->pRight->pParent = buildBST.root);
    assert(buildBST.root->pRight->pRight == NULL);
    assert(buildBST.root->pRight->pLeft == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight != NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->data == 9);
    assert(buildBST.root->pLeft->pRight->pParent == buildBST.root->pLeft);
    assert(buildBST.root->pLeft->pRight->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft == NULL);
    
    
    buildBST.insert(7);
    //should be                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                      7
    assert(buildBST.numElements == 5);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pRight != NULL);
    assert(buildBST.root->pRight->data == 11);
    assert(buildBST.root->pRight->pParent = buildBST.root);
    assert(buildBST.root->pRight->pRight == NULL);
    assert(buildBST.root->pRight->pLeft == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight != NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->data == 9);
    assert(buildBST.root->pLeft->pRight->pParent == buildBST.root->pLeft);
    assert(buildBST.root->pLeft->pRight->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->data == 7);
    assert(buildBST.root->pLeft->pRight->pLeft->pParent == buildBST.root->pLeft->pRight);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight == NULL);
    
    
    buildBST.insert(6);
    //should be                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                   ---7
    //                                                  |
    //                                                  6
    assert(buildBST.numElements == 6);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pRight != NULL);
    assert(buildBST.root->pRight->data == 11);
    assert(buildBST.root->pRight->pParent = buildBST.root);
    assert(buildBST.root->pRight->pRight == NULL);
    assert(buildBST.root->pRight->pLeft == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight != NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->data == 9);
    assert(buildBST.root->pLeft->pRight->pParent == buildBST.root->pLeft);
    assert(buildBST.root->pLeft->pRight->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->data == 7);
    assert(buildBST.root->pLeft->pRight->pLeft->pParent == buildBST.root->pLeft->pRight);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->data == 6);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pParent == buildBST.root->pLeft->pRight->pLeft);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pLeft == NULL);
    
    
    buildBST.insert(8);
    //should be                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                   ---7---
    //                                                  |       |
    //                                                  6       8
    assert(buildBST.numElements == 7);
    assert(buildBST.root->data == 10);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pRight != NULL);
    assert(buildBST.root->pRight->data == 11);
    assert(buildBST.root->pRight->pParent = buildBST.root);
    assert(buildBST.root->pRight->pRight == NULL);
    assert(buildBST.root->pRight->pLeft == NULL);
    assert(buildBST.root->pLeft != NULL);
    assert(buildBST.root->pLeft->data == 5);
    assert(buildBST.root->pLeft->pParent == buildBST.root);
    assert(buildBST.root->pLeft->pRight != NULL);
    assert(buildBST.root->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->data == 9);
    assert(buildBST.root->pLeft->pRight->pParent == buildBST.root->pLeft);
    assert(buildBST.root->pLeft->pRight->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->data == 7);
    assert(buildBST.root->pLeft->pRight->pLeft->pParent == buildBST.root->pLeft->pRight);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight != NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->data == 6);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pParent == buildBST.root->pLeft->pRight->pLeft);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pLeft->pLeft == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight->data == 8);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight->pParent == buildBST.root->pLeft->pRight->pLeft);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight->pRight == NULL);
    assert(buildBST.root->pLeft->pRight->pLeft->pRight->pLeft == NULL);
    
    
    cout<<"Passed Insert Tests"<<endl;
    
    /*
     * Testing Iterator Constructors
     */
    BST<int>::iterator emptyIterator;
    assert(emptyIterator.ptr == NULL);
    
    BST<int>::BNode* noDataNodePtr = new BST<int>::BNode();
    BST<int>::iterator nonEmptyIterator(noDataNodePtr);
    assert(nonEmptyIterator.ptr != NULL);
    assert(nonEmptyIterator.ptr == noDataNodePtr);
    //clean up memory
    delete noDataNodePtr;
    //get rid of zombies
    noDataNodePtr = NULL;
    nonEmptyIterator.ptr = NULL;
    
    cout<<"Passed Iterator Constructor Tests"<<endl;
    
    /*
     * Testing Iterator Destructor
     */
    
    BST<int>::iterator* iteratorToDelete = new BST<int>::iterator();
    unit_testing_delete_call_counter = 0;
    delete iteratorToDelete;
    assert(unit_testing_delete_call_counter == 1);//don't delete the node. It's part of a list.
    
    //resetting
    noDataNodePtr = new BST<int>::BNode();
    iteratorToDelete = new BST<int>::iterator();
    iteratorToDelete->ptr = noDataNodePtr;
    unit_testing_delete_call_counter = 0;
    delete iteratorToDelete;
    assert(unit_testing_delete_call_counter == 1);
    //clean up memory
    delete noDataNodePtr;
    //get rid of zombie
    iteratorToDelete = NULL;
    
    cout<<"Passed Iterator Destructor Tests"<<endl;
    
    /*
     * Testing iterator equality operator
     */
    
    BST<int>::iterator nullNodeIterator;
    BST<int>::iterator otherNullNodeIterator;
    assert(nullNodeIterator == nullNodeIterator);//compare the memory locations of nodes
    assert(otherNullNodeIterator == otherNullNodeIterator);
    assert((nullNodeIterator == otherNullNodeIterator));
    
    
    //resetting
    noDataNodePtr = new BST<int>::BNode();
    BST<int>::iterator nonNullNodeIterator;
    nonNullNodeIterator.ptr = noDataNodePtr;
    assert(nonNullNodeIterator == nonNullNodeIterator);//compare memory locations of nodes
    assert(!(nonNullNodeIterator == nullNodeIterator));
    
    //setting up a node with the data
    BST<int>::BNode* dataNodePtr = new BST<int>::BNode();
    dataNodePtr->data = 7;
    BST<int>::iterator nodeHasDataIterator;
    nodeHasDataIterator.ptr = dataNodePtr;
    assert(nodeHasDataIterator == nodeHasDataIterator);
    
    //setting up an iterator to the same data node
    BST<int>::iterator otherNodeHasDataIterator;
    otherNodeHasDataIterator.ptr = dataNodePtr;
    assert(otherNodeHasDataIterator == nodeHasDataIterator);//compare memory locations of nodes
  
    
    
    cout<<"Passed Iterator Equality Tests"<<endl;
    
    /*
     * Testing iterator non-equality operator
     */
    //comparing with self
    assert((otherNullNodeIterator != otherNullNodeIterator) == false);
    assert((nodeHasDataIterator != nodeHasDataIterator) == false);
    
    //having different nodes makes the iterators different
    assert(nullNodeIterator != nodeHasDataIterator);
    
    //having nodes with data duplicates doesn't make the iterators the same iterator
    BST<int>::BNode* otherNodeWithSameData= new BST<int>::BNode();
    otherNodeWithSameData->data = 7;
    BST<int>::iterator otherNodeWithSameDataIterator;
    otherNodeWithSameDataIterator.ptr = otherNodeWithSameData;
    assert(nodeHasDataIterator != otherNodeWithSameDataIterator);
    
    
    //clean up memory
    delete otherNodeWithSameData;
    delete noDataNodePtr;
    delete dataNodePtr;
    //get rid of zombies
    otherNodeWithSameData = NULL;
    noDataNodePtr = NULL;
    dataNodePtr = NULL;
    
    cout<<"Passed Iterator Non-equality Tests"<<endl;
    
    
    /*
     * Testing iterator assignment operator
     */
    
    BST<int>::iterator assignTo;
    assignTo.ptr = NULL;
    BST<int>::iterator assignFrom;
    assignFrom.ptr = NULL;
    assignTo = assignFrom;
    assert(assignTo.ptr == assignFrom.ptr);
    
    //reset
    nodeToDelete = new BST<int>::BNode();
    assignTo.ptr = nodeToDelete;
    assignTo.ptr->data = 5;
    
    assignFrom.ptr = new BST<int>::BNode();
    assignFrom.ptr->data = 17;
    
    assignTo = assignFrom;
    assert(assignTo.ptr == assignFrom.ptr);
    assert(assignTo.ptr->data = 17);
    
    //clean up memory
    delete assignFrom.ptr;
    delete nodeToDelete;
    //kill zombies
    assignFrom.ptr = NULL;
    nodeToDelete = NULL;
    
    /*
     * Testing dereference operator
     */
    //testing when pointer is NULL
    BST<int>::iterator dereferenceIterator;
    dereferenceIterator.ptr = NULL;
    try {
        *dereferenceIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message,"Error: dereferencing null node.") == 0);
    }
    dereferenceIterator.ptr = new BST<int>::BNode();
    dereferenceIterator.ptr->data = 32;
    
    assert((*dereferenceIterator) == 32);
    
    cout<<"Passed Iterator Dereference Test"<<endl;
    
    
    /*
     * Testing BST begin and end
     */
    
    BST<int> emptyBeginEndTree;
    emptyBeginEndTree.root = NULL;
    assert(emptyBeginEndTree.begin().ptr == NULL);
    assert(emptyBeginEndTree.end().ptr == NULL);
    
    //Reusing insertIntoBST
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                   ----5         ----9---          11-------
    //                                                  |             |                           |
    //                                              ----3---          8                           20
    //                                             |        |
    //                                             2        4
    assert(insertIntoBST.begin().ptr == insertIntoBST.root->pLeft->pLeft->pLeft->pLeft);
    assert(insertIntoBST.begin().ptr->data == 2);
    assert(insertIntoBST.end().ptr == insertIntoBST.root->pRight->pRight->pRight);
    assert(insertIntoBST.end().ptr->data == 20);
    
    //reusing buildBST
    //currently                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                   ---7---
    //                                                  |       |
    //                                                  6       8
    assert(buildBST.begin().ptr == buildBST.root->pLeft);
    assert(buildBST.end().ptr == buildBST.root->pRight);
    
    cout<<"Pased BST Begin and End Tests"<<endl;
    
    /*
     * Testing BST find
     */
    
    //Reusing emptyBeginEndTree
    assert(emptyBeginEndTree.find(23).ptr == NULL);
    
    //Reusing insertIntoBST
    //Should be BST with the values                                     |
    //                                                            ------7---------
    //                                                            |              |
    //                                                       -----6        ------10------
    //                                                       |             |             |
    //                                                   ----5         ----9---          11-------
    //                                                  |             |                           |
    //                                              ----3---          8                           20
    //                                             |        |
    //                                             2        4
    
    //searching in a balanced tree
    assert(insertIntoBST.find(7).ptr == insertIntoBST.root);
    assert(insertIntoBST.find(2).ptr == insertIntoBST.root->pLeft->pLeft->pLeft->pLeft);
    assert(insertIntoBST.find(20).ptr == insertIntoBST.root->pRight->pRight->pRight);
    assert(insertIntoBST.find(8).ptr == insertIntoBST.root->pRight->pLeft->pLeft);
    assert(insertIntoBST.find(8).ptr->data == 8);
    assert(insertIntoBST.find(456).ptr == NULL);
    //* ToDo: expand each of these tests to check all values of the tree to make sure nothing got messed up.
    
    assert(insertIntoBST.find(4).ptr == insertIntoBST.root->pLeft->pLeft->pLeft->pRight);
    assert(insertIntoBST.find(4).ptr->data == 4);
    
    //reusing buildBST
    //currently                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                   ---7---
    //                                                  |       |
    //                                                  6       8
    
    //searching in unbalanced tree
    assert(buildBST.find(8).ptr == buildBST.root->pLeft->pRight->pLeft->pRight);
    assert(buildBST.find(8).ptr->data == 8);
    
    /*
     * Testing BST copy constructor
     */
    BST<int> emptyCopy(emptyBeginEndTree);
    assert(emptyCopy.root == NULL);
    
    //reusing buildBST
    //currently                                                     |
    //                                                --------------10-------
    //                                               |                       |
    //                                               5-----------            11
    //                                                           |
    //                                                       ----9
    //                                                      |
    //                                                   ---7---
    //                                                  |       |
    //                                                  6       8
    BST<int> buildCopy(buildBST);
    assert(buildCopy.root != buildBST.root);
    assert(buildCopy.root->data == buildBST.root->data);
    assert(buildCopy.root->pRight != buildBST.root->pRight);
    assert(buildCopy.root->pRight->data == buildBST.root->pRight->data);//(11)
    assert(buildCopy.root->pLeft != buildBST.root->pLeft);
    assert(buildCopy.root->pLeft->data == buildBST.root->pLeft->data);//(5)
    assert(buildCopy.root->pLeft->pRight != buildBST.root->pLeft->pRight);
    assert(buildCopy.root->pLeft->pRight->data == buildBST.root->pLeft->pRight->data);//(9)
    assert(buildCopy.root->pLeft->pRight->pLeft != buildBST.root->pLeft->pRight->pLeft);
    assert(buildCopy.root->pLeft->pRight->pLeft->data == buildBST.root->pLeft->pRight->pLeft->data);//(7)
    assert(buildCopy.root->pLeft->pRight->pLeft->pRight != buildBST.root->pLeft->pRight->pLeft->pRight);
    assert(buildCopy.root->pLeft->pRight->pLeft->pRight->data == buildBST.root->pLeft->pRight->pLeft->pRight->data);//(8)
    assert(buildCopy.root->pLeft->pRight->pLeft->pLeft != buildBST.root->pLeft->pRight->pLeft->pLeft);
    assert(buildCopy.root->pLeft->pRight->pLeft->pLeft->data == buildCopy.root->pLeft->pRight->pLeft->pLeft->data);//(6)
    
    cout<<"Passed BST Copy Tests"<<endl;
    
    /*
     * Testing BST erase
     */
    
    //building erase tree
    //                                                                  |
    //                                                          --------13--------
    //                                                          |                 |
    //                                                      ----5----         ----22----
    //                                                     |         |       |          |
    //                                                     4         11      21         23
    
    BST<int>eraseTree;
    eraseTree.numElements = 7;
    eraseTree.root = new BST<int>::BNode();
    eraseTree.root->data = 13;
    eraseTree.root->pLeft = new BST<int>::BNode();
    eraseTree.root->pLeft->data = 5;
    eraseTree.root->pLeft->pParent = eraseTree.root;
    eraseTree.root->pLeft->pLeft = new BST<int>::BNode();
    eraseTree.root->pLeft->pLeft->data = 4;
    eraseTree.root->pLeft->pLeft->pParent = eraseTree.root->pLeft;
    eraseTree.root->pLeft->pLeft->pRight = NULL;
    eraseTree.root->pLeft->pLeft->pLeft = NULL;
    eraseTree.root->pLeft->pRight = new BST<int>::BNode();
    eraseTree.root->pLeft->pRight->data = 11;
    eraseTree.root->pLeft->pRight->pParent = eraseTree.root->pLeft;
    eraseTree.root->pLeft->pRight->pRight = NULL;
    eraseTree.root->pLeft->pRight->pLeft = NULL;
    
    eraseTree.root->pRight = new BST<int>::BNode();
    eraseTree.root->pRight->data = 22;
    eraseTree.root->pRight->pParent = eraseTree.root;
    eraseTree.root->pRight->pLeft = new BST<int>::BNode();
    eraseTree.root->pRight->pLeft->data = 21;
    eraseTree.root->pRight->pLeft->pParent = eraseTree.root->pRight;
    eraseTree.root->pRight->pRight = new BST<int>::BNode();
    eraseTree.root->pRight->pRight->data = 23;
    eraseTree.root->pRight->pRight->pParent = eraseTree.root->pRight;
    
    BST<int>::iterator eraseIterator;
    eraseIterator.ptr = eraseTree.root->pLeft->pLeft;//(4)
    unit_testing_delete_call_counter = 0;
    eraseTree.erase(eraseIterator);
    
    //should now be
    //                                                                  |
    //                                                          --------13--------
    //                                                          |                 |
    //                                                      ----5----         ----22----
    //                                                               |       |          |
    //                                                               11      21         23
    
    assert(unit_testing_delete_call_counter == 1);
    assert(eraseTree.root->pLeft->pLeft == NULL);
    assert(eraseTree.numElements == 6);
    
    //setting up
    BST<int>::BNode* elevenNode = eraseTree.root->pLeft->pRight;
    unit_testing_delete_call_counter = 0;
    //reusing eraseIterator
    eraseIterator.ptr = eraseTree.root->pLeft;
    eraseTree.erase(eraseIterator);
    
    //should now be
    //                                                                  |
    //                                                          --------13--------
    //                                                          |                 |
    //                                                          11            ----22----
    //                                                                       |          |
    //                                                                       21         23
    assert(unit_testing_delete_call_counter == 1);
    assert(eraseTree.root->pLeft == elevenNode);
    assert(eraseTree.numElements == 5);
    
    //rebuild tree for next test
    //                                                                  |
    //                                                          --------13--------
    //                                                          |                 |
    //                                                      ----11---         ----22----
    //                                                     |         |       |          |
    //                                                     10        12      21         23
    
    
    elevenNode->pLeft = new BST<int>::BNode();
    elevenNode->pLeft->data = 10;
    elevenNode->pLeft->pParent = elevenNode;
    elevenNode->pRight = new BST<int>::BNode();
    elevenNode->pRight->data = 12;
    elevenNode->pRight->pParent = elevenNode;
    
    eraseTree.numElements = 7;
    
    //setting up
    BST<int>::BNode* twentyOneNode = eraseTree.root->pRight->pLeft;
    BST<int>::BNode* twentyTwoNode = eraseTree.root->pRight;
    unit_testing_delete_call_counter = 0;
    //reusing eraseIterator
    eraseIterator.ptr = eraseTree.root;
    eraseTree.erase(eraseIterator);
    //should now be
    //                                                                  |
    //                                                          --------21--------
    //                                                          |                 |
    //                                                      ----11---             22----
    //                                                     |         |                  |
    //                                                     10        12                 23
    assert(unit_testing_delete_call_counter == 1);
    assert(eraseTree.root == twentyOneNode);
    assert(eraseTree.root->data = 21);
    assert(eraseTree.root->pRight == twentyTwoNode);
    assert(eraseTree.root->pRight->pLeft == NULL);
    assert(eraseTree.root->pLeft == elevenNode);
    assert(eraseTree.numElements == 6);
    
    cout<<"Passed BST Erase Tests"<<endl;
    
    
    
    /*
     * Testing iterator pre-increment operator
     */
    BST<int>::iterator incrementIterator;
    incrementIterator.ptr = NULL;
    try {
        ++incrementIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: incrementing null node.") == 0);
    }
    //beginning of tree test
    incrementIterator.ptr = eraseTree.root->pLeft->pLeft;//(10)
    assert((++incrementIterator).ptr == eraseTree.root->pLeft);//(11)
    //end of tree test
    incrementIterator.ptr = eraseTree.root->pRight->pRight;
    assert((++incrementIterator).ptr == NULL);
    //middle of tree test
    incrementIterator.ptr = eraseTree.root->pLeft->pRight;//(12)
    assert((++incrementIterator).ptr == eraseTree.root);
    
    cout<<"Passed Iterator Pre-Increment Test"<<endl;
    
    /*
     * Testing iterator post increment operator
     */
    
    
    //should now be
    //                                                                  |
    //                                                          --------21--------
    //                                                          |                 |
    //                                                      ----11---             22----
    //                                                     |         |                  |
    //                                                     10        12                 23
    incrementIterator.ptr = NULL;
    try {
        incrementIterator++;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: incrementing null node.") == 0);
    }
    //reusing eraseTree
    //beginning of tree test
    incrementIterator.ptr = eraseTree.root->pLeft->pLeft;//(10)
    assert((incrementIterator++).ptr == eraseTree.root->pLeft->pLeft);//(10)
    assert(incrementIterator.ptr == eraseTree.root->pLeft);//(11)
    //end of tree test
    incrementIterator.ptr = eraseTree.root->pRight->pRight;//(23)
    assert((incrementIterator++).ptr == eraseTree.root->pRight->pRight);
    assert(incrementIterator.ptr == NULL);
    //middle of tree test
    incrementIterator.ptr = eraseTree.root->pLeft->pRight;//(12)
    assert((incrementIterator++).ptr == eraseTree.root->pLeft->pRight);
    assert(incrementIterator.ptr == eraseTree.root);//(21)
    
    cout<<"Passed Iterator Post Increment Test"<<endl;
    
    /*
     * Testing iterator pre-decrement operator
     */
    //should now be
    //                                                                  |
    //                                                          --------21--------
    //                                                          |                 |
    //                                                      ----11---             22----
    //                                                     |         |                  |
    //                                                     10        12                 23
    BST<int>::iterator decrementIterator;
    decrementIterator.ptr = NULL;
    try {
        --decrementIterator;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: decrementing null node.") == 0);
    }
    //beginning of tree test
    decrementIterator.ptr = eraseTree.root->pLeft->pLeft;//(10)
    assert((--decrementIterator).ptr == NULL);
    //end of tree test
    decrementIterator.ptr = eraseTree.root->pRight->pRight;//(23)
    assert((--decrementIterator).ptr == eraseTree.root->pRight);
    //middle of tree test
    decrementIterator.ptr = eraseTree.root->pLeft->pRight;//(12)
    assert((--decrementIterator).ptr == eraseTree.root->pLeft);
    
    cout<<"Passed Iterator Pre-Decrement Tests"<<endl;
    
    /*
     * Testing iterator post decrement operator
     */
    //should now be
    //                                                                  |
    //                                                          --------21--------
    //                                                          |                 |
    //                                                      ----11---             22----
    //                                                     |         |                  |
    //                                                     10        12                 23
    decrementIterator.ptr = NULL;
    try {
        decrementIterator--;
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: decrementing null node.") == 0);
    }
    //beginning of tree test
    decrementIterator.ptr = eraseTree.root->pLeft->pLeft;//(10)
    assert((decrementIterator--).ptr == eraseTree.root->pLeft->pLeft);
    assert(decrementIterator.ptr == NULL);
    //end of tree test
    decrementIterator.ptr = eraseTree.root->pRight->pRight;//(23)
    assert((decrementIterator--).ptr == eraseTree.root->pRight->pRight);
    //middle of tree test
    decrementIterator.ptr = eraseTree.root->pLeft->pRight;//(12)
    assert((decrementIterator--).ptr == eraseTree.root->pLeft->pRight);
    assert(decrementIterator.ptr == eraseTree.root->pLeft);
    
    cout<<"Passed Iterator Post Decrement Tests"<<endl;
    
    //*ToDo: Write string test.
    
    
    
    
    
    
    
    
    return 0;
}
