//
//  deque.hpp
//  Deque.hpp
//
//  Created by Lee Leo Silva on 05/09/19.
//  Copyright © 2019 Leo Coelho. All rights reserved.
//

#ifndef deque_hpp //if that macro doesn't exist ( avoid double compilation)
#define deque_hpp // then define the macro ( our flag to not compile twice)
#ifdef UNIT_TESTING // if we are testing
int main(int argc, const char* argv[]); // prototype for unit_test's main
#endif
//creating my own space for naming
namespace custom {
    // creating own datatype that can hold any element
    template< typename T > class deque{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);// give main acess to the private data( friend)
#endif
   private:
        T * buffer;     // dynamically allocated array of T
        int numCapacity;      // how many items can I put on the dequeue before full
        int iBack;   // number in the back of the deque
        int iFront;  // number in the front of the deque
        
        
    public:
        /*
         * Constructors & Destructor
         */
        
        // setting my private members default data
        deque()
        {
            //setting my pointer to NULL ( Null means not zero but address that holds nothing)
            buffer =  NULL;
            iBack = -1; // we have nothing
            iFront = 0;
            numCapacity = 0; // no space
            //numItems = 0;
        }
        
        //copy constuctor
        
        deque(const deque &rhs)throw (const char*)
        {
            
            // this set to default at first!!!!!
            iFront =  0;
            iBack =  -1;
            
        
            //if  the right hand side is more  items than the left hand side
            // we need to allocate more space
            if(rhs.size() > this->numCapacity){
                // if we have allocated memory
                if (buffer != NULL)
                    // delete the memory
                    delete [] buffer;
                // allocate the spaces to hold the right hand side stuff!
                buffer = new T[rhs.size()];
                // every time we allocte our capacity should be the same that my [] had inside!!
                this->numCapacity = rhs.size();
            }
            // else we have enough spaces for the rhs
            // we don't need to re-allocate
            // keep the old capacity, that is how many spaces the lhs has
            
            
            for (int i = rhs.iFrontNormalize(); i < rhs.iFrontNormalize() + rhs.size(); i++)
            {
                // I am copying "assigning"  starting to the IFront Normalize and
                // incrementing my temp "iRHS"
                // that means I am looping throw the = RHS ( iNormalize)
                //this->buffer[i - 1] = rhs.buffer[i % rhs.capacity()];
                push_back(rhs.buffer[i % rhs.capacity()]);
            }
            
           
        }
        // noun-default constructor
        
        deque(int numCapacity)throw (const char*)
        {
            if(numCapacity < 0)
            {
                throw "Error: deque sizes must be greater than or equal to 0.";
            }
            // set the firt element to  new T element ( dereference return the value)
            //buffer[0] = *new T;
            
            //setting the first address to point to the new element
            //buffer = new T;
            
            //creatring a new space and set the point to the fisrt new address
            // just create uninitialized space unlike stack
            buffer = new T[numCapacity];
            
            // set to zero size
            this->iBack = -1;
            this->iFront = 0;
            // we have as many elements that the client need it
            this->numCapacity = numCapacity;
        }
        
        
        
        
        ~deque()
        {
            if (buffer != NULL)
                delete [] buffer;
        }
        
        
        bool empty() const throw (const char*)
        {
            if(size() < 0)
            {
                throw "Error: deque is empty.";
            }
            return size() == 0;
        }
        
        void clear()
        {
            iFront = 0;
            iBack = -1;
        }
        // example: if we have one element ifront and iback wll be the same!!!
        // thus the difference will be 0, but we have 1... so we have to add
        // 1!!!!
        int size() const
        {
            return (iBack - iFront) + 1;
        }
        
        void push_front(const T & item) throw(const char *)
        {
           if(size() == capacity())
           //if (size() == numCapacity)
          
            {
                
                numCapacity != 0 ? resize(numCapacity *2) : resize(1);
                // now as you can see I will
                // rezise(1) will happen just in the first moment when I create the stack, allowing me
                // to be more efficient(faster)
                }
                
                iFront--;
                // that line means: put the element in ther end and add one to the numElements after
                //  size is the last index plus one
                buffer[iFrontNormalize()] = item;
        }
        
        void push_back(const T & item) throw(const char *)
        {
               if(size() == capacity())
            //if (size() == numCapacity)
            {
                
                numCapacity != 0 ? resize(numCapacity *2) : resize(1);
                // now as you can see I will
                // rezise(1) will happen just in the first moment when I create the stack, allowing me
                // to be more efficient(faster)
                }
                
                iBack++;
                // that line means: put the element in ther end and add one to the numElements after
                //  size is the last index plus one
                buffer[iBackNormalize()] = item;
        }
                
        void pop_front() throw(const char*)
        {
            if(empty())
            {
                throw "Error: Can not pop an empty deque.";
            }
            else
            {
                iFront++;
            }
            
            
        }
        
        void pop_back() throw(const char *)
        {
            if(empty())
            {
                throw "Error: Can not pop an empty deque.";
            }
            else
            {
                iBack--;
            }
        }
        
        T & front() throw(const char*)
        {
            if (size() != 0)
                return buffer[iNormalize(iFront)];
            else
                throw "Error: deque is empty.";
            
        }
        
        T & back() throw(const  char*)
        {
            if (empty())
            {
                throw"Error: deque is empty.";
            }
            else
                return buffer[iNormalize(iBack)];
        }
        
    private:
        void resize(int aCapacity) throw(const char*)
        {
             // 1 create my temp Buffer
            // tempory buffer that starts pointing to Null (if we dont to allocate we will point to nothing)
            T* resizedBuffer = NULL;
            // just a variable that keep tracking how many things  we need to copy from old buffer
            int numElementsToCopy = 0;
               // if my aCapacity is == 0 than we will create a " default deque" ( see bellow)
                if (aCapacity >= 0) {
                     // this make sure that is not == 0
                    // than we need to copy the old stuff
                    //because I dont want to fail the allocation( can't allocate to -number or 0)
                    if (aCapacity > 0) {
                         // this is still step 1
                        // create new buffer ( allocate memory)
                        // this will create my  "temporary buffer"
                        resizedBuffer = new T[aCapacity];
                        // we dont need to copy if we dont have anything there
                        // dont derefence the buffer if ist pointing to NUll
                        if (buffer != NULL)
                        {
                            // step 2 copy
                            // IF size < than numCapcity THEN assign  numElementsToCopy to size ELSE assing to numCapacity
                            numElementsToCopy = size() < aCapacity ? size() : aCapacity;
                         
                            int indexOld = iFrontNormalize();
                            // step 2 - still copying
                            // loop through all the elements inside of my buffer
                            for (int i = 0; i < numElementsToCopy; i++)
                            {
                                 // sill 2 step
                                // copying all the old stuff
                                // that means I am looping through the old index
                                resizedBuffer[i] = buffer[iNormalize(indexOld++)];
                               
                            }
                            // step 3
                            // free memory - because I am creating a new stack ( buffer) with more
                            // size and capacity, I need to delete the old one
                            // every time that I say "new" I need to delete it!(memory allocation)
                            delete [] buffer;
                        }
                    }
                    // copy the pointer
                    // how many spaces we allocate for!!!
                    
                    
                    // the buffer still pointing to the old address.
                    // that line of code will make my buffer pointer to the new "address"
                    buffer = resizedBuffer;
                    this->numCapacity = aCapacity; // resize
                    
                    // iFront will be my size!!!!( here)
                    // how manytimes I copy
                    // simulating push_back()
                    iFront =  0 ;
                    iBack  = numElementsToCopy -1 ;

                    //numPush = numElementsToCopy;
                }
            }
        int iNormalize(int index) const throw(const char*)
        {
            int normalized = 0;
            if(numCapacity == 0)
            {
                throw "Error: uninitialized deque.";
            }
            normalized = index % numCapacity;
            if (index < 0 && normalized != 0)
            {
                normalized += numCapacity;
            }
            return normalized;
        }
          /*
            if (numCapacity == 0)
            {
                throw"Error: uninitialized deque.";
            }
            if (index % numCapacity < 0)
                return (index % numCapacity) + numCapacity;
            else{
                return index % numCapacity;
            }
        }*/
        
        int iFrontNormalize() const
        {
            return iNormalize(iFront);
        }
        
        int iBackNormalize() const
        {
            return iNormalize(iBack);
        }
        
        int capacity() const
        {
            return numCapacity;
        }
        
        /*
         * Operators
         */
    public:
        deque& operator = (const deque& rhs)
        {
            clear();
            //if  the right hand side is more  items than the left hand side
            // we need to allocate more space
            if(rhs.size() > this->numCapacity){
                // if we have allocated memory
                if (buffer != NULL)
                    // delete the memory
                    delete [] buffer;
                // allocate the spaces to hold the right hand side stuff!
                buffer = new T[rhs.size()];
                // every time we allocte our capacity should be the same that my [] had inside!!
                this->numCapacity = rhs.size();
            }
            // else we have enough spaces for the rhs
            // we don't need to re-allocate
            // keep the old capacity, that is how many spaces the lhs has
            
            int iRhs = rhs.iFrontNormalize();
            for (int i = 0; i < rhs.size(); i++)
            {
                // I am copying "assigning"  starting to the IFront Normalize and
                // incrementing my temp "iRHS"
                // that means I am looping throw the = RHS ( iNormalize)
                this->buffer[i] = rhs.buffer[rhs.iNormalize(iRhs++)];
                
            }
            
           // return *this;
        }
        
    };
}
#endif /* deque_h */


