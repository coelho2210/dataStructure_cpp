//
//  node_delete.h
//  junk
//
//  Created by Leo Coelho.
//
//

#ifndef unit_testing_delete_h
#define unit_testing_delete_h

#include <math.h>

//DON'T EDIT THIS CODE!! IF YOU DO, YOU WILL HATE LIFE.

#ifdef UNIT_TESTING
//This global int variable is used to track calls to delete for unit testing purposes only.
int unit_testing_delete_call_counter = 0;

int asserts_passed = 0;

extern int asserts_existing;

void generateTestingReport(){
    std::cerr<<"Tests Passed:  "<<floor(100*(float)asserts_passed/asserts_existing)<<"%"<<std::endl;
}

#undef assert
void assertTrue(bool condition, int line)
{
    if (!condition)
    {
        std::cout << "Error line " << line << std::endl;
        //capturing cerr result is the percentage correct.
        generateTestingReport();
        exit(asserts_passed+1);
    }
    asserts_passed++;
}

//overloading the delete operator globally.
bool deletingArray = false;
#ifdef __APPLE__
void operator delete(void * p) _NOEXCEPT
#else
void operator delete(void * p)
#endif
{
    free(p);
    if (!deletingArray) {
        unit_testing_delete_call_counter++;
    }
}

#ifdef __APPLE__
void operator delete[]( void* ptr)  _NOEXCEPT
#else
void operator delete[]( void* ptr)
#endif
{
    deletingArray = true;
    free(ptr);
    deletingArray = false;
    unit_testing_delete_call_counter++;
}

void * operator new(size_t size) throw(std::bad_alloc)
{
    void * p = malloc(size);
    return p;
}
#endif /* UNIT_TESTING */
#endif /* unit_testing_delete_h */


