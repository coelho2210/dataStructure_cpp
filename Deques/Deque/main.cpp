/*
 * main.cpp
 *
 *  Created by Lee Barney on 8/22/18.
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
//Do not change the next line without instructor approval.
//To do so is cheating and, when found, will result in consequences.
int asserts_existing = 371;

#include <iostream>
#include "deque.h"
#include "unit_testing.h"

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
    deque <int> defaultDeque;
    assertTrue(defaultDeque.iFront == 0, __LINE__);
    assertTrue(defaultDeque.iBack == -1, __LINE__);
    assertTrue(defaultDeque.numCapacity == 0, __LINE__);
    assertTrue(defaultDeque.buffer == NULL, __LINE__);
    cout << "Default Constructor Test Passed" << endl;
    
    /*
     * Testing sized deque constructor
     */
    try{
        deque<int> badSizeDeque(-3);
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: deque sizes must be greater than or equal to 0.") == 0,__LINE__);
    }
    deque <int> sizedDeque(4);
    assertTrue(sizedDeque.iFront == 0,__LINE__);
    assertTrue(defaultDeque.iBack == -1,__LINE__);
    assertTrue(sizedDeque.numCapacity == 4,__LINE__);
    assertTrue(sizedDeque.buffer != NULL,__LINE__);
    cout << "Sized Constructor Test Passed" << endl;
    
    /*
     * Testing Size
     */
    deque <int> sizeTestDeque;
    
    sizeTestDeque.numCapacity = 8;
    sizeTestDeque.iBack = 38;
    sizeTestDeque.iFront = 31;
    assertTrue(sizeTestDeque.size() == 8,__LINE__);
    
    sizeTestDeque.iBack = 35;
    sizeTestDeque.iFront = 36;
    assertTrue(sizeTestDeque.size() == 0,__LINE__);
    
    sizeTestDeque.iBack = 50;
    sizeTestDeque.iFront = -26;
    assertTrue(sizeTestDeque.size() == 77,__LINE__);
    
    sizeTestDeque.iBack = -10;
    sizeTestDeque.iFront = 5;
    assertTrue(sizeTestDeque.size() == -14,__LINE__);
    
    cout << "Size Tests Passed" << endl;
    /*
     * Testing Capacity
     */
    assertTrue(sizeTestDeque.capacity() == 8,__LINE__);
    sizeTestDeque.numCapacity = 0;
    assertTrue(sizeTestDeque.capacity() == 0,__LINE__);
    cout << "Capacity Tests Passed" << endl;
    /*
     * Resetting for further use
     */
    sizeTestDeque.numCapacity = 8;
    sizeTestDeque.iFront = 5;
    sizeTestDeque.iBack = -7;
    sizeTestDeque.buffer = new int[sizeTestDeque.numCapacity];
    for (int i = 0; i < sizeTestDeque.numCapacity; i++) {
        sizeTestDeque.buffer[i]=i*i+1;
    }
    /*
     * Testing Clear
     */
    sizeTestDeque.clear();
    assertTrue(sizeTestDeque.iBack == -1,__LINE__);
    assertTrue(sizeTestDeque.iFront == 0,__LINE__);
    assertTrue(sizeTestDeque.numCapacity == 8,__LINE__);
    cout << "Clear Test Passed" << endl;
    /*
     * Testing Empty
     */
    sizeTestDeque.numCapacity = 8;
    sizeTestDeque.iFront = -3;
    sizeTestDeque.iBack = 7;
    
    assertTrue(!sizeTestDeque.empty(),__LINE__);
    
    sizeTestDeque.iFront = 0;
    sizeTestDeque.iBack = -1;
    
    assertTrue(sizeTestDeque.empty(),__LINE__);
    cout << "Empty Tests Passed" << endl;
    
    /*
     * Testing iNormalize
     */
    
    deque <int> normalizeDeque;
    normalizeDeque.numCapacity = 0;
    normalizeDeque.iFront = 0;
    normalizeDeque.iBack = -1;
    //testing uninitialized deque
    try{
        normalizeDeque.iNormalize(1);
    } catch (const char * message) {
        assertTrue(strcmp("Error: uninitialized deque.", message) == 0,__LINE__);
    }
    
    normalizeDeque.numCapacity = 4;
    assertTrue(normalizeDeque.iNormalize(0) == 0,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(1) == 1,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(2) == 2,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(3) == 3,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(4) == 0,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(5) == 1,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(6) == 2,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-1) == 3,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-2) == 2,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-3) == 1,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-4) == 0,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-5) == 3,__LINE__);
    
    assertTrue(normalizeDeque.iNormalize(-6) == 2,__LINE__);
    
    cout << "iNormalize test passed." << endl;
    
    /*
     * Testing iFrontNormalize
     */
    try{
        assertTrue(normalizeDeque.iFrontNormalize() == 0,__LINE__);
    } catch (const char * message) {
        assertTrue(strcmp(message, "Error: uninitialized deque."),__LINE__);
    }
    //setting to simulate intialized deque
    normalizeDeque.numCapacity = 4;
    normalizeDeque.iFront = 0;
    assertTrue(normalizeDeque.iFrontNormalize() == 0,__LINE__);
    
    normalizeDeque.iFront = -17;
    assertTrue(normalizeDeque.iFrontNormalize() == 3,__LINE__);
    
    normalizeDeque.iFront = 18;
    assertTrue(normalizeDeque.iFrontNormalize() == 2,__LINE__);
    
    normalizeDeque.iFront = 8931;
    assertTrue(normalizeDeque.iFrontNormalize() == 3,__LINE__);
    
    //reseting deque to default constructed values
    normalizeDeque.iFront = 0;
    normalizeDeque.iBack = -1;
    normalizeDeque.numCapacity = 0;
    cout << "iFrontNormalized Test Passed." << endl;
    
    /*
     * Testing iBackNormalize
     */
    
    //reseting deque to default constructed values
    normalizeDeque.iFront = 0;
    normalizeDeque.iBack = -1;
    normalizeDeque.numCapacity = 0;
    try{
        assertTrue(normalizeDeque.iBackNormalize() == 0,__LINE__);
    } catch (const char * message) {
        assertTrue(strcmp(message, "Error: uninitialized deque.") == 0,__LINE__);
    }
    //setting to simulate intialized deque
    normalizeDeque.numCapacity = 4;
    normalizeDeque.iBack = 0;
    assertTrue(normalizeDeque.iBackNormalize() == 0,__LINE__);
    
    normalizeDeque.iBack = -17;
    assertTrue(normalizeDeque.iBackNormalize() == 3,__LINE__);
    
    normalizeDeque.iBack = 18;
    assertTrue(normalizeDeque.iBackNormalize() == 2,__LINE__);
    
    normalizeDeque.iBack = 8931;
    assertTrue(normalizeDeque.iBackNormalize() == 3,__LINE__);
    cout << "iBackNormalized Test Passed." << endl;
    
    /*
     * Testing resize
     */
    //setting up as if all had been pushed front then one popped front and one popped back
    deque <int> resizeDeque;
    resizeDeque.buffer = NULL;
    resizeDeque.iFront = 0;
    resizeDeque.iBack = -1;
    resizeDeque.resize(3);
    
    assertTrue(resizeDeque.buffer != NULL,__LINE__);
    assertTrue(resizeDeque.iFront == 0,__LINE__);
    assertTrue(resizeDeque.iBack == -1,__LINE__);
    assertTrue(resizeDeque.numCapacity == 3,__LINE__);
    
    //resetting
    resizeDeque.buffer = new int[5];
    resizeDeque.iFront = 0 - 5 + 1;// 5 push_fronts (7,8,9,10,12) then one pop_front removing 12
    resizeDeque.iBack = -1 - 1;//then one pop_back removing 7
    resizeDeque.numCapacity = 5;
    resizeDeque.buffer[0] = 12;
    resizeDeque.buffer[1] = 10;
    resizeDeque.buffer[2] = 9;
    resizeDeque.buffer[3] = 8;
    resizeDeque.buffer[4] = 7;
    int *theBuffer = resizeDeque.buffer;
    resizeDeque.resize(10);
    assertTrue(theBuffer != resizeDeque.buffer,__LINE__);
    assertTrue(resizeDeque.iFront == 0,__LINE__);
    assertTrue(resizeDeque.iBack == 2,__LINE__);
    assertTrue(resizeDeque.numCapacity == 10,__LINE__);
    assertTrue(resizeDeque.buffer[0] == 10,__LINE__);
    assertTrue(resizeDeque.buffer[1] == 9,__LINE__);
    assertTrue(resizeDeque.buffer[2] == 8,__LINE__);
    
    theBuffer = resizeDeque.buffer;
    resizeDeque.resize(2);
    assertTrue(theBuffer != resizeDeque.buffer,__LINE__);
    assertTrue(resizeDeque.iFront == 0,__LINE__);
    assertTrue(resizeDeque.iBack == 1,__LINE__);
    assertTrue(resizeDeque.numCapacity == 2,__LINE__);
    assertTrue(resizeDeque.buffer[0] == 10,__LINE__);
    assertTrue(resizeDeque.buffer[1] == 9,__LINE__);
    
    theBuffer = resizeDeque.buffer;
    resizeDeque.resize(0);
    assertTrue(theBuffer != resizeDeque.buffer,__LINE__);
    assertTrue(resizeDeque.iFront == 0,__LINE__);
    assertTrue(resizeDeque.iBack == -1,__LINE__);
    assertTrue(resizeDeque.numCapacity == 0,__LINE__);
    assertTrue(resizeDeque.buffer == NULL,__LINE__);
    
    cout << "Resize Test Passed" << endl;
    
    /*
     * Testing push_back
     */
    deque <int> pushBackDeque(4);
    pushBackDeque.push_back(1);
    assertTrue(pushBackDeque.numCapacity == 4,__LINE__);
    assertTrue(pushBackDeque.iFront == 0,__LINE__);
    assertTrue(pushBackDeque.iBack == 0,__LINE__);
    assertTrue(pushBackDeque.buffer[0] == 1,__LINE__);
    cout << "Push_back First ElementTest Passed" << endl;
    
    pushBackDeque.push_back(5);
    assertTrue(pushBackDeque.numCapacity == 4,__LINE__);
    assertTrue(pushBackDeque.iFront == 0,__LINE__);
    assertTrue(pushBackDeque.iBack == 1,__LINE__);
    assertTrue(pushBackDeque.buffer[0] == 1,__LINE__);
    assertTrue(pushBackDeque.buffer[1] == 5,__LINE__);
    cout << "Push_back Second Element Test Passed" << endl;
    
    pushBackDeque.push_back(10);
    assertTrue(pushBackDeque.numCapacity == 4,__LINE__);
    assertTrue(pushBackDeque.iFront == 0,__LINE__);
    assertTrue(pushBackDeque.iBack == 2,__LINE__);
    assertTrue(pushBackDeque.buffer[0] == 1,__LINE__);
    assertTrue(pushBackDeque.buffer[1] == 5,__LINE__);
    assertTrue(pushBackDeque.buffer[2] == 10,__LINE__);
    cout << "Push_back Third Element Test Passed" << endl;
    
    /*
     * Testing push_front
     */
    deque <int> pushFrontDeque(4);
    pushFrontDeque.push_front(1);
    assertTrue(pushFrontDeque.numCapacity == 4,__LINE__);
    assertTrue(pushFrontDeque.iFront == -1,__LINE__);
    assertTrue(pushFrontDeque.iBack == -1,__LINE__);
    assertTrue(pushFrontDeque.buffer[3] == 1,__LINE__);
    cout << "Push_back First ElementTest Passed" << endl;
    
    pushFrontDeque.push_front(5);
    assertTrue(pushFrontDeque.numCapacity == 4,__LINE__);
    assertTrue(pushFrontDeque.iFront == -2,__LINE__);
    assertTrue(pushFrontDeque.iBack == -1,__LINE__);
    assertTrue(pushFrontDeque.buffer[3] == 1,__LINE__);
    assertTrue(pushFrontDeque.buffer[2] == 5,__LINE__);
    cout << "Push_back Second Element Test Passed" << endl;
    
    pushFrontDeque.push_front(10);
    assertTrue(pushFrontDeque.numCapacity == 4,__LINE__);
    assertTrue(pushFrontDeque.iFront == -3,__LINE__);
    assertTrue(pushFrontDeque.iBack == -1,__LINE__);
    assertTrue(pushFrontDeque.buffer[3] == 1,__LINE__);
    assertTrue(pushFrontDeque.buffer[2] == 5,__LINE__);
    assertTrue(pushFrontDeque.buffer[1] == 10,__LINE__);
    cout << "Push Third Element Test Passed" << endl;
    
    
    /*
     * Testing push_front with resize
     */
    //iFront starts at 0 iFront decrimented each time push
    //iBack starts at -1 iBack incremented each time push
    deque <int> pushFrontResizeDeque;
    pushFrontResizeDeque.push_front(1);
    assertTrue(pushFrontResizeDeque.numCapacity == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.iFront == -1,__LINE__);
    assertTrue(pushFrontResizeDeque.iBack == -1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[0] == 1,__LINE__);
    cout << "Push_front First ElementTest Passed" << endl;
    
    pushFrontResizeDeque.push_front(5);
    assertTrue(pushFrontResizeDeque.numCapacity == 2,__LINE__);
    assertTrue(pushFrontResizeDeque.iFront == -1,__LINE__);
    assertTrue(pushFrontResizeDeque.iBack == 0,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[0] == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[1] == 5,__LINE__);
    cout << "Push_back Second Element Test Passed" << endl;
    
    pushFrontResizeDeque.push_front(10);
    assertTrue(pushFrontResizeDeque.numCapacity == 4,__LINE__);
    assertTrue(pushFrontResizeDeque.iFront == -1,__LINE__);
    assertTrue(pushFrontResizeDeque.iBack == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[0] == 5,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[1] == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[3] == 10,__LINE__);
    cout << "Push Third Element Test Passed" << endl;
    
    
    pushFrontResizeDeque.push_front(20);
    assertTrue(pushFrontResizeDeque.numCapacity == 4,__LINE__);
    assertTrue(pushFrontResizeDeque.iFront == -2,__LINE__);
    assertTrue(pushFrontResizeDeque.iBack == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[0] == 5,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[1] == 1,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[2] == 20,__LINE__);
    assertTrue(pushFrontResizeDeque.buffer[3] == 10,__LINE__);
    cout << "Push Fourth Element Test Passed" << endl;
    
    /*
     * Testing push_front-pop_back
     */
    deque <int> popDeque;
    popDeque.buffer = new int[6];
    popDeque.buffer[0] = -500;
    popDeque.buffer[1] = 0;
    popDeque.buffer[2] = -100;
    popDeque.buffer[3] = 300;
    popDeque.buffer[4] = 10;
    popDeque.buffer[5] = 0;
    popDeque.iFront = -6;
    popDeque.iBack = -1;
    popDeque.numCapacity = 6;
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -2,__LINE__);
    assertTrue(popDeque.numCapacity = 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4]== 10,__LINE__);
    assertTrue(popDeque.buffer[5]== 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -3,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -4,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -6,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == -6,__LINE__);
    assertTrue(popDeque.iBack == -7,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    //testing popping an empty deque
    try{
        popDeque.pop_back();
        assertTrue(false,__LINE__);
    } catch(const char* message){
        assertTrue(strcmp(message,"Error: Can not pop an empty deque.") == 0,__LINE__);
    }
    cout << "Push Front Pop Back Test Passed" << endl;
    /*
     * Testing push_front-pop_front
     */
    //resetting to simulate push_front
    popDeque.buffer = new int[6];
    popDeque.buffer[0] = -500;
    popDeque.buffer[1] = 0;
    popDeque.buffer[2] = -100;
    popDeque.buffer[3] = 300;
    popDeque.buffer[4] = 10;
    popDeque.buffer[5] = 0;
    popDeque.iFront = -6;
    popDeque.iBack = -1;
    popDeque.numCapacity = 6;
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == -5,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == -4,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == -3,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == -2,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == -1,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    //testing popping an empty deque
    try{
        popDeque.pop_front();
        assertTrue(false,__LINE__);
    } catch(const char* message){
        assertTrue(strcmp(message, "Error: Can not pop an empty deque.") == 0,__LINE__);
    }
    
    cout << "Push Front Pop Front Test Passed" << endl;
    /*
     * Testing push_back-pop_front
     */
    
    //resetting to simulate push_back
    popDeque.buffer = new int[6];
    popDeque.buffer[0] = -500;
    popDeque.buffer[1] = 0;
    popDeque.buffer[2] = -100;
    popDeque.buffer[3] = 300;
    popDeque.buffer[4] = 10;
    popDeque.buffer[5] = 0;
    popDeque.iFront = 0;
    popDeque.iBack = 5;
    popDeque.numCapacity = 6;
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 1,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 2,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 3,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 4,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 5,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    popDeque.pop_front();
    assertTrue(popDeque.iFront == 6,__LINE__);
    assertTrue(popDeque.iBack == 5,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    //testing popping an empty deque
    try{
        popDeque.pop_front();
        assertTrue(false,__LINE__);
    } catch(const char* message){
        assertTrue(strcmp(message, "Error: Can not pop an empty deque.") == 0,__LINE__);
    }
    
    cout << "Push Back Pop Front Test Passed" << endl;
    /*
     * Testing push_back-pop_back
     */
    //resetting to simulate push_back
    popDeque.buffer = new int[6];
    popDeque.buffer[0] = -500;
    popDeque.buffer[1] = 0;
    popDeque.buffer[2] = -100;
    popDeque.buffer[3] = 300;
    popDeque.buffer[4] = 10;
    popDeque.buffer[5] = 0;
    popDeque.iFront = 0;
    popDeque.iBack = 5;
    popDeque.numCapacity = 6;
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == 4,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == 3,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == 2,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == 1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == 0,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    popDeque.pop_back();
    assertTrue(popDeque.iFront == 0,__LINE__);
    assertTrue(popDeque.iBack == -1,__LINE__);
    assertTrue(popDeque.numCapacity == 6,__LINE__);
    assertTrue(popDeque.buffer[0] == -500,__LINE__);
    assertTrue(popDeque.buffer[1] == 0,__LINE__);
    assertTrue(popDeque.buffer[2] == -100,__LINE__);
    assertTrue(popDeque.buffer[3] == 300,__LINE__);
    assertTrue(popDeque.buffer[4] == 10,__LINE__);
    assertTrue(popDeque.buffer[5] == 0,__LINE__);
    
    //testing popping an empty deque
    try{
        popDeque.pop_back();
        assertTrue(false,__LINE__);
    } catch(const char* message){
        assertTrue(strcmp(message, "Error: Can not pop an empty deque.") == 0,__LINE__);
    }
    
    cout << "Push Back Pop Back Test Passed" << endl;
    /*
     * Testing copy constructor
     */
    sizedDeque.buffer[0] = 1;
    sizedDeque.buffer[1] = 5;
    sizedDeque.buffer[2] = 10;
    sizedDeque.buffer[3] = 15;
    sizedDeque.numCapacity = 4;
    sizedDeque.iFront = 1;
    sizedDeque.iBack = -1+4-1;//starts at -1. These iFront and iBack values are as if pushed_back was called 4 times, pop_front was called once and pop_back was called once.
    deque <int> dequeCopy(sizedDeque);
    assertTrue(dequeCopy.iFront == 0,__LINE__);
    assertTrue(dequeCopy.iBack == 1,__LINE__);
    assertTrue(dequeCopy.numCapacity == 2,__LINE__);
    assertTrue(dequeCopy.buffer != sizedDeque.buffer,__LINE__);
    assertTrue(dequeCopy.buffer[0] == 5,__LINE__);
    assertTrue(dequeCopy.buffer[1] == 10,__LINE__);
    cout << "Copy Constructor Test Passed" << endl;
    
    /*
     * Testing Front
     */
    deque <int> frontBackDeque;
    frontBackDeque.buffer = new int[6];
    frontBackDeque.buffer[0] = -500;
    frontBackDeque.buffer[1] = 0;
    frontBackDeque.buffer[2] = 7;
    frontBackDeque.buffer[3] = 13;
    frontBackDeque.buffer[4] = 23;
    frontBackDeque.buffer[5] = -1;
    frontBackDeque.numCapacity = 6;
    //simulating all push_front
    frontBackDeque.iFront = -6;
    frontBackDeque.iBack = -1;
    //test accessor
    assertTrue(frontBackDeque.front() == -500,__LINE__);
    //test mutator
    frontBackDeque.front() = 35;
    assertTrue(frontBackDeque.buffer[0] == 35,__LINE__);
    
    //simulating one push_back of 35 and zero push_fronts.
    frontBackDeque.iFront = 0;
    frontBackDeque.iBack = 0;
    assertTrue(frontBackDeque.front() == 35,__LINE__);
    
    //simulating seven push_fronts and one pop_back
    frontBackDeque.iBack = -2;
    frontBackDeque.iFront = -7;
    assertTrue(frontBackDeque.front() == -1,__LINE__);
    
    //simulate six push_backs and three pop_fronts
    frontBackDeque.iBack = 5;
    frontBackDeque.iFront = 3;
    assertTrue(frontBackDeque.front() == 13,__LINE__);
    
    //simulate 3 push_backs and 3 push_fronts
    frontBackDeque.iBack = 2;
    frontBackDeque.iFront = -3;
    assertTrue(frontBackDeque.front() == 13,__LINE__);
    
    
    deque <int> emptyDeque;
    try{
        emptyDeque.front();
        assertTrue(false,__LINE__);
    } catch (const char* message) {
        assertTrue(strcmp(message, "Error: deque is empty.") == 0,__LINE__);
    }
    
    cout << "Front tests passed"<<endl;
    
    /*
     * Testing Back
     */
    
    //simulating all push_front
    frontBackDeque.iFront = -6;
    frontBackDeque.iBack = -1;
    //test accessor
    assertTrue(frontBackDeque.back() == -1,__LINE__);
    //test mutator
    frontBackDeque.back() = 18;
    assertTrue(frontBackDeque.buffer[5] == 18,__LINE__);
    
    //simulating six push_fronts and one pop_back
    frontBackDeque.iBack = 0;
    assertTrue(frontBackDeque.back() == 35,__LINE__);
    
    //simulating six push_fronts and six pop_backs
    
    frontBackDeque.iBack = -7;
    
    try {
        
        frontBackDeque.back();
        
        assertTrue(false, __LINE__);
        
    } catch (const char* message) {
        
        assertTrue(strcmp(message, "Error: deque is empty.")== 0,__LINE__);
        
    }
    
    //simulating six push_fronts and two pop_backs
    frontBackDeque.iBack = -3;
    assertTrue(frontBackDeque.back() == 13,__LINE__);
    
    //simulating six push_fronts, five pop_fronts, and four push_backs
    frontBackDeque.iFront = -1;
    frontBackDeque.iBack = 3;
    assertTrue(frontBackDeque.back() == 13,__LINE__);
    
    
    try{
        emptyDeque.back();
        assertTrue(false,__LINE__);
    } catch (const char* message) {
        assertTrue(strcmp(message, "Error: deque is empty.") == 0,__LINE__);
    }
    
    cout << "Back tests passed"<<endl;
    
    
    /*
     * Testing = operator and copy constructor
     */
    deque <int> dequeToCopy;
    dequeToCopy.numCapacity = 8;
    dequeToCopy.buffer = new int[dequeToCopy.numCapacity];
    for (int i = 0; i < dequeToCopy.numCapacity; i++) {
        dequeToCopy.buffer[i]=i*i+1;
    }
    dequeToCopy.iBack = 21;//starts at -1
    dequeToCopy.iFront = 17;//starts at 0
    
    deque <int> dequeCopiedTo = dequeToCopy;
    assertTrue(dequeCopiedTo.iFront == 0,__LINE__);
    assertTrue(dequeCopiedTo.iBack == 4,__LINE__);
    assertTrue(dequeCopiedTo.numCapacity == 5,__LINE__);
    assertTrue(dequeCopiedTo.buffer[0] == 2,__LINE__);
    assertTrue(dequeCopiedTo.buffer[1] == 5,__LINE__);
    assertTrue(dequeCopiedTo.buffer[2] == 10,__LINE__);
    assertTrue(dequeCopiedTo.buffer[3] == 17,__LINE__);
    assertTrue(dequeCopiedTo.buffer[4] == 26,__LINE__);
    cout << "= Operator and Copy Constructor Test Passed" << endl;
    
    
    
    /*
     * Testing Push for Non-Integer Deque Behavior (Just to Make Sure deque Works For Other Types)
     */
    deque <string> sString;
    
    sString.push_front("Hello");
    sString.push_front("It's me");
    sString.push_front("I was wondering");
    assertTrue(sString.numCapacity == 4,__LINE__);
    assertTrue(sString.iFront == -1,__LINE__);
    assertTrue(sString.iBack == 1,__LINE__);
    assertTrue(sString.buffer[0] == "It's me",__LINE__);
    assertTrue(sString.buffer[1] == "Hello",__LINE__);
    assertTrue(sString.buffer[3] == "I was wondering",__LINE__);
    
    cout << "This deque can hold strings!!!!" << endl;
    generateTestingReport();
    
    
    return 0;
}



