//
//  queue.hpp
//  Queues
//
//  Created by  Leo Silva on 05/09/19.
//  Copyright © 2019 Leo Coelho. All rights reserved.
//

#ifndef queue_hpp //if that macro doesn't exist ( avoid double compilation)
#define queue_hpp // then define the macro ( our flag to not compile twice)
#ifdef UNIT_TESTING // if we are testing
int main(int argc, const char* argv[]); // prototype for unit_test's main
#endif
//creating my own space for naming
namespace custom {
    // creating own datatype that can hold any element
    template< typename T > class queue{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);// give main acess to the private data( friend)
#endif
    private:
        T* buffer; // reserving space for my pointer to  dynamically allocated array
        int numPush; // size
        int numPop; //
        int numCapacity; // how many spaces are allocated
        
      
        
    public:
        /*
         * Constructors & Destructor
         */
        
        // setting my private members default data
        queue(){
            
            //setting my pointer to NULL ( Null means not zero but address that holds nothing)
            buffer = NULL;
            numPush = 0; // we have nothing
            numPop = 0;
            numCapacity = 0; // no space
        }
        
        
        //non-default constructor
        //"Error: asking for top of empty stack" is a string literal and in c++ is
        // held as a const char *
        //throw: will allow other functions to know what is wrong ( should not pop off of empty stack)
        queue(int capacity)throw (const char*)// Creating a new queue
        {

             // set the firt element to  new T element ( dereference return the value)
            //buffer[0] = *new T;
            
             //setting the first address to point to the new element
            //buffer = new T;
            
            //creatring a new space and set the point to the fisrt new address
           
            // just create uninitialized space unlike stack
            buffer = new T[capacity];
            
            // set to zero size
            this->numPush = 0;
            this->numPop = 0;
            // we have as many elements that the client need it
            this->numCapacity = capacity;
        }
        
        // copy constructor
        queue(const queue &rhs)
        {
       
            buffer = new T[rhs.numCapacity];
       
            this->numPop = 0;
            this->numPush = this->numCapacity;
            this->numCapacity = rhs.size();
        
        int iRhs = rhs.iHead();
        for (int i = 0; i < rhs.size(); i++)
        {
            this->buffer[i] = rhs.buffer[iRhs++ % rhs.numCapacity];
        }
            numPush = rhs.size();
            
    }
        // d
        ~queue()
        {
            if (buffer != NULL)
                delete [] buffer;
        }
        
        int size() const
        {
            return (numPush - numPop);
        }
       
        bool empty(){
            return (numPush == numPop);
        }
        void clear()
        {
            numPush = 0;
            numPop =  0;
            
        }
        
        int capacity() const
        {
            return numCapacity;
        }
        
        // creating my push function
        void push(const T value) throw ( const char *)
        {
           if (size() == numCapacity)
            {
                
                numCapacity != 0 ? resize(numCapacity *2) : resize(1);
                // now as you can see I will
               // rezise(1) will happen just in the first moment when I create the stack, allowing me
              // to be more efficient(faster)
            }
           
                numPush++;
             // that line means: put the element in ther end and add one to the numElements after
            //  size is the last index plus one
            buffer[iTail()] = value;
        }
        void pop()
        {
            if (!empty())
               numPop++;
            else
                throw "Error: poping  off empty queue";
        }
        
    
       T& front() throw (const char *)
        {
            assert(size() <= numCapacity);
            if ( empty())
                throw "Error: asking for front of empty queue.";
            return buffer[iHead()];
        }
        
        
        T& back() throw (const char *)
        {
            assert ( size() <= numCapacity);
            if (empty())
                throw "Error: asking for back of empty queue.";
            return buffer[iTail()];
        }
        
        
    private:
        // this function will create a new buffer, copy the old one, delete it and add to the top
        // more space
        void resize(int aCapacity)
        {
            // tempory buffer that starts pointing to Null (if we dont to allocate we will point to nothing)
            T* resizedBuffer = NULL;
            int numElementsToCopy = 0;
            if (aCapacity >= 0) {
                //because I dont want to fail the allocation( can't allocate to -number or 0)
                if (aCapacity > 0) {
                    // this will create my  "temporary buffer"
                    resizedBuffer = new T[aCapacity];
                    // we dont need to copy if we dont have anything there
                    // dont derefence the buffer if ist pointing to NUll
                    if (buffer != NULL)
                    {
                        // IF size < than numCapcity THEN assign  numElementsToCopy to size ELSE assing to numCapacity
                        numElementsToCopy = size() < aCapacity ? size() : aCapacity;
                        // loop through all the elements inside of my buffer
                        
                        for (int i = iHead(); i < iHead() + size(); i++) {
                            // copy my buffer using a " temporary buffer
                            resizedBuffer[i - iHead()] = buffer[i % numCapacity];// [] does dereferebnce (could be *(buffer + i))
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
                this->numCapacity = aCapacity; // resize
              
                numPop = 0;
                
                numPush = numElementsToCopy;
             }
           }
        int iHead() const
        {
            return numPop  % numCapacity;
        }
        
        int iTail() const
        {
            return (numPush -1)  % numCapacity;
        }
        
        
        /*
         * Operators
         */
    public:
        queue& operator = (const queue& rhs){
            numPop = 0;
            
            if(rhs.size() > numCapacity){
                if (buffer != NULL)
                    delete [] buffer;
                buffer = new T[rhs.size()];
                this->numCapacity = rhs.size();
            }
            
            int iRhs = rhs.iHead();
            for (int i = 0; i < rhs.size(); i++)
            {
                this->buffer[i] = rhs.buffer[iRhs++ % rhs.numCapacity];
                numPush++;
            }
          
            return *this;
        }
    };
    
    
}

#endif /* vector_h */


