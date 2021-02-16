//
//  vector.hpp
//  Vectors
//
//  Created by Lee Barney on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef stack_hpp //if that macro doesn't exist ( avoid double compilation)
#define stack_hpp // then define the macro ( our flag to not compile twice)
#ifdef UNIT_TESTING // if we are testing
int main(int argc, const char* argv[]); // prototype for unit_test's main
#endif
//creating my own space for naming
namespace custom {
    // creating own datatype that can hold any element
    template< typename T > class stack{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);// give main acess to the private data( friend)
#endif
    private:
        T* buffer; // reserving space  for my pointer to  dynamically allocated array
        int numElements; // size
        int numCapacity; // how many spaces are allocated
        
    public:
        /*
         * Constructors & Destructor
         */
        // setting my private members default data
        stack(){
            //setting my pointer to NULL ( Null means not zero but address that holds nothing)
            buffer = NULL;
            numElements = 0; // we have nothing
            numCapacity = 0; // no space
        }
        //non-default constructor
        //"Error: asking for top of empty stack" is a string literal and in c++ is
        // held as a const char *
        //throw: will allow other functions to know what is wrong ( should not pop off of empty stack)
        stack(int capacity)throw (const char*)// Creating a new stack
        {
            
            
            // set the firt element to  new T element ( dereference return the value)
            //buffer[0] = *new T();
            
            // setting the first address to point to the new element
            //buffer = new T();
            
            //creatring a new space and set the point to the fisrt new address
            // just create uninitialized space unlike stack
            buffer = new T[capacity];
            
           // set to zero size
            this->numElements = 0;
          // we have as many elements that the client need it
            this->numCapacity = capacity;
        }
        
        // copy constrocutor
         stack(stack const &rhs){
            if (rhs.numElements > 0) {
                if (buffer != NULL) {
                    delete [] buffer;
                    buffer = NULL;
                }
                buffer = new T[rhs.numElements];
                for (int i = 0; i < rhs.numElements; i++) {
                    buffer[i] = rhs.buffer[i];
                }
            }
            numElements = rhs.numElements;
            numCapacity = rhs.numElements;
        }
        ~stack()
        {
            if (buffer != NULL)
                delete [] buffer;
        }
        
        int size(){
            return numElements;
        }
        int capacity(){
            return numCapacity;
        }
        bool empty(){
            return !numElements;
        }
        void clear(){
            numElements = 0;
        }
        
        // creating my push function
        void push(T anElement){
            // I can't say cap = 0  because I will be not able to double my capacity ( 0 * 2 = 0)
            if (numElements == numCapacity) {
                // this way will be less efficient(slower) beucause I need to check every time if
                //cap == 0. That happen just once when I create my stack ( cap == 0), so why check
                // everytime when I do "push" ?
                //numCapacity == 0 ? resize(1) : resize(numCapacity * 2);
                numCapacity != 0 ? resize(numCapacity *2) : resize(1); // now as you can see I will
                //rezise(1) will happen just in the first moment when I create the stack, allowing me
                // to be more efficient(faster)
            }
            buffer[numElements++] = anElement;
        }
        T& top()throw (const char*)
        {
            if (!empty())
            {
                return buffer[numElements-1];
            }
            else
                throw "Error: asking for top of empty stack." ;
        }
        
        void pop()
        {
            if (!empty())
            --numElements;
        }
        
     
    private:
        // this function will create a new buffer, copy de old one, delete it and add to the top
        // a new element
        void resize(int numCapacity){
        
            T* resizedBuffer = NULL;
            int numElementsToCopy = 0;
            if (numCapacity >= 0) {
                if (numCapacity > 0) {
                    // this will create my  "temporary buffer"
                    resizedBuffer = new T[numCapacity];
                    if (buffer != NULL) {
                        numElementsToCopy = numElements < numCapacity ? numElements : numCapacity;
                    // loop through all the elements inside of my buffer
                        for (int i = 0; i < numElementsToCopy; i++) {
                            // copy my buffer using a " temporary buffer
                            resizedBuffer[i] = buffer[i];
                        }
                        // free memory - because I am creating a new stack ( buffer) with more
                        // size and capacity, I need to delete the old one
                        // every time that I say "new" I need to delete it!(memory allocation)
                        delete [] buffer;
                    }
                }
                // the buffer still pointing to the old address.
                // that line of code will make my buffer pointer to the new "address"
                buffer = resizedBuffer;
                this->numCapacity = numCapacity;
                numElements = numElementsToCopy;
            }
        }
        /*
         * Operators
         */
    public:
        stack& operator = (const stack& rhs){
            numElements=0;
            if(rhs.numCapacity > numCapacity){
                resize(rhs.numElements);
            }
            numElements = rhs.numElements;
            for (int i = 0; i < numElements; i++) {
                buffer[i] = rhs.buffer[i];
            }
            return *this;
        }
    };
}

#endif /* vector_h */


