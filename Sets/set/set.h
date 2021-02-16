
//
//  vector.hpp
//  Vectors
//
//  Created by Lee Barney on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef set_hpp
#define set_hpp
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif
namespace custom {
    template< typename T > class set{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
#endif
    private:
        T* buffer;
        int numElements;
        int numCapacity;
    public:
        /*
         * Constructors & Destructor
         */
        set(){ // default
            buffer = NULL;
            numElements = 0;
            numCapacity = 0;
        }
        set(int numCapacity)throw (const char*){ // noun-default
            if(numCapacity < 0){
                throw "Error: set sizes must be greater than or equal to 0.";
            }
            
            this->buffer = new T[numCapacity];
            for(int i = 0; i < numCapacity; i++){
                buffer[i] = *new T();
            }
            this->numElements = 0;
            this->numCapacity = numCapacity;
        }
        set( const set &rhs){ // copy constructor
           
           // *this = rhs;
            numElements = rhs.numElements;
            numCapacity = rhs.numElements;
            if( rhs.numElements > 0)
            {
                buffer = new T[rhs.numElements];
            
                for (int i = 0; i < rhs.numElements; i++) {
                    buffer[i] = rhs.buffer[i];
                }
            }
            else {
                buffer = NULL;
            }
        
        }
        
        set & operator = (const set &rhs)
        {
            numCapacity = rhs.numElements;
           
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
            
            return *this;
        }
        ~set(){}// destructor
        
        // This create a prototype for " my iterator"
        // So I can have access before class definition
        class iterator;
        
    
        int size(){
            return numElements;
        }
        
        bool empty(){
            return !numElements;
        }
        
        void clear(){
            numElements = 0;
        }
        
        void insert(T anElement)
        {
            
            if(numElements == 0)
            {
                if(numCapacity == 0)
                    resize(1);
                buffer[0] = anElement;
                numElements++;
                return;
            }
            
    
            int iInsert = findIndex(anElement);

            if(buffer[iInsert] == anElement)
            {
                return;
            }
            
            if(numElements == numCapacity)
                //if (size() == numCapacity)
            {
                
                resize(numCapacity *2);
                // now as you can see I will
                // rezise(1) will happen just in the first moment when I create the stack, allowing me
                // to be more efficient(faster)
            }

            //{
            for (int i = numElements - 1; i >= iInsert; i--)
                {
                    buffer[i + 1] = buffer[i];
                    //if (buffer[i - 1] < anElement)
                }
                
                buffer[iInsert] = anElement;
                numElements++;
         //  }
        }
            
         iterator  find (T anElement)
        {
            int iBegin  = 0;
            int iEnd    = numElements -1;
            int iMiddle = 0; // default to 0
            
            while(iBegin <= iEnd)
            {
                iMiddle = ( iBegin + iEnd) / 2;
                if(anElement == buffer[iMiddle])
                {
                    // iterator(&buffer[iMiddle])
                    return iterator(buffer + iMiddle); // that uses my copy constructor
                }
                else if(anElement < buffer[iMiddle])
                {
                    iEnd = iMiddle -1;
                }
                else
                {
                    iBegin = iMiddle + 1;
                }
            }
            
            return iterator(); // return a null interator because I didn't find the element
        }
        
        // I want to be able to use that symbol as an union operator
        // This function will look throught the Lhs and rhs and add each elements and don't add duplicates
       // That function will create a new " operation"
        set operator ||(const set &rhs)
        {
            // this call the non-default constructor
            // Assigning the firts parameter to the "addition"(numEle +rhs.num)
            // and allocate buffer that can hold at list as much as both set hold
            set setReturn = numElements + rhs.numElements;
           int  iRhs = 0;//variable that represents the right hand side and track where we are in the buffer
           int  iLhs = 0;//variable that represents the left hand side and track where we are in the buffer
            
            // loop until we have elements in eather of sides
            while( iLhs < this->numElements || iRhs < rhs.numElements)
            {
                //this->numElements ( left hand side)
                // when the ILHS( index) is equal to the NumElements
                // we  are done comparing
                // if we are done adding all the elements in the left hand side
                // so Add the remainder elements of the right hand side
                if( iLhs == this->numElements)
                {
                    //go to the setReturn( buffer) and Add the right hand side element to the end!
                    setReturn.buffer[setReturn.numElements++] = rhs.buffer[iRhs++];
                }
                //this->numElements ( right hand side)
                // when the iRHS( index) is equal to the NumElements
                // we  are done comparing
                // if we are done adding all the elements in the right hand side
                // so Add the remainder elements of the left hand sid
                else if(iRhs == rhs.numElements)
                {
                    //go to the setReturn( buffer) and Add the right hand side element to the end!
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                    
                }
                // if the elements inside the sets are the same add one not both
                else if(this->buffer[iLhs] == rhs.buffer[iRhs])
                {
                    //choose one side to add!!!!
                    // I CHOOSE LEFT TO ADD, HOWEVER I NEED TO INCREMENT BOTH SIDE BECAUSE
                    // IF I DONT DO THIS I WILL REPEAT THE NUMBER AGAIN
                    //WHEN I HAVE THE SAME ELEMENT IN BOTH SIDE AND I ADD ONE OF THEM, IF I DONT
                    //INCREAMENT THE NEXT ONE WILL BE > THEN AND I WILL ADD THE SAME NUMBER AGAIN
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                    iRhs++;
                }
                else if(this->buffer[iLhs] < rhs.buffer[iRhs])
                {
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                    
                }
                else
                {
                    setReturn.buffer[setReturn.numElements++] = rhs.buffer[iRhs++];
                    
                }
            }
            setReturn.resize(setReturn.numElements);
            return setReturn;
                    
        }
        // I want to be able to use that symbol as an intersection operator
        // That function will create a new " operation"
        set operator &&(const set &rhs)
        {
            set setReturn;
            
            if(this->numElements != 0 && rhs.numElements != 0)
            {
               if(this->numElements < rhs.numElements)
               {
                 setReturn.buffer = new  T[this->numElements];
               }
              else
             {
                setReturn.buffer = new  T[this->numElements];
             }
           }
            
            int  iRhs = 0;
            int  iLhs = 0;
            
            while(iLhs < this->numElements || iRhs < rhs.numElements)
            {
                if( iLhs == this->numElements)
                {
                    setReturn.resize(setReturn.numElements);
                    return setReturn;
                }
                else if(iRhs == rhs.numElements)
                {
                    setReturn.resize(setReturn.numElements);
                    return setReturn;
                }
                else if(this->buffer[iLhs] == rhs.buffer[iRhs])
                {
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                    iRhs++;
                }
                else if(this->buffer[iLhs] < rhs.buffer[iRhs])
                {
                    iLhs++;
                }
                else
                {
                    iRhs++;
                }
             
                    
            }
            setReturn.resize(setReturn.numElements);
            /*if (setReturn.numElements == 0 && setReturn.buffer != NULL)
            {
                delete [] setReturn.buffer;
                setReturn.buffer = NULL;
            }*/
                
            return setReturn;
        }
        // I want to be able to use that symbol as an difference operator
        // That function will create a new " operation"
        set operator -(const set &rhs)
        {
            set setReturn;
            int  iRhs = 0;
            int  iLhs = 0;
            
            if(rhs.numElements == 0)
            {
                if (this->numElements != 0)
                {
                setReturn.buffer = new T[this->numElements];
                    setReturn.numCapacity = this->numElements;
                    
                while(iLhs < this->numElements)
                {
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                }
                }
                return setReturn;
            }
            else
                setReturn.buffer = new T[this->numElements];
            
           
         
            while(iLhs < this->numElements)
            {
                if( iLhs == this->numElements)
                {
                    setReturn.resize(setReturn.numElements);
                    return setReturn;
                }
                else if(iRhs == rhs.numElements)
                {
                    while(iLhs < this->numElements)
                    {
                       setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                    }
                    setReturn.resize(setReturn.numElements);
                    return setReturn;
                }
                else if(this->buffer[iLhs] == rhs.buffer[iRhs])
                {
                    iLhs++;
                    iRhs++;
                }
                else if(this->buffer[iLhs] < rhs.buffer[iRhs])
                {
                    setReturn.buffer[setReturn.numElements++] = this->buffer[iLhs++];
                }
                else
                    iRhs++;
            }
            setReturn.resize(setReturn.numElements);
            return setReturn;
        }
        
        iterator begin(){
            return iterator(buffer);
        }
        
        iterator end(){
            return iterator(buffer + numElements);
        }
        
        iterator erase(iterator & anIt)
        {
            if(anIt == iterator())
            {
                return iterator();
            }
            int iErase = findIndex(*anIt);
            
            if(buffer[iErase] == *anIt)
            {
                for(int i = iErase; i< numElements; i++)
                {
                    buffer[i] = buffer[i+1];
                }
                numElements--;
            }
            return iterator(buffer);
        }
       
       
        class iterator{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
        private:
            T* ptr; // allow us to point to one element
        
        
        public:
            iterator(){ // default
                ptr = NULL;
            }
            iterator(T* aTPtr){ // noun default
                ptr = aTPtr;
            }
            iterator(const iterator& aIt){ // copy constructor
                ptr = aIt.ptr;
            }
            iterator operator = (T* aPtr){ // assigment operator
                ptr = aPtr;
                return this;
            }
            bool operator==(iterator anIt){ //comparison
                return ptr == anIt.ptr;
            }
            
            bool operator!=(iterator anIt){ //conparison (not)
                return ptr != anIt.ptr;
            }
            //prefix operator
            iterator operator++(){ //prefix increment
                if (ptr != NULL) {
                    ++ptr;
                }
                return *this;
            }
            //postfix operator
            iterator operator++(T lhs){ // postfix - increment
                iterator result = iterator(*this);
                if (ptr != NULL) {
                    ++ptr;
                }
                return result;
            }
            //prefix operator
            iterator operator--(){ //decrement
                if (ptr != NULL) {
                    ptr --;
                }
                return *this;
            }
            //postfix operator
            iterator operator--(T lhs){ // decrement
                iterator result = iterator(*this);
                if (ptr != NULL) {
                    ptr--;
                }
                return result;
            }
            //dereference operator
            T& operator *(){ // return the value of the  element( the iteretor point to the address, and with this, I can get access to the value)
                return *ptr;
            }
            
        }; // end of iterator
        
    private:
        void resize(int numCapacity){
            T* resizedBuffer = NULL;
            int numElementsToCopy = 0;
            if (numCapacity >= 0) {
                if (numCapacity > 0) {
                    resizedBuffer = new T[numCapacity];
                    if (buffer != NULL) {
                        numElementsToCopy = numElements < numCapacity ? numElements : numCapacity;
                        for (int i = 0; i < numElementsToCopy; i++) {
                            resizedBuffer[i] = buffer[i];
                        }
                        delete [] buffer;
                    }
                }
                buffer = resizedBuffer;
                this->numCapacity = numCapacity;
                numElements = numElementsToCopy;
            }
        }
        
        int findIndex(T anElement)
        {
            int iBegin  = 0;
            int iEnd    = numElements -1;
            int iMiddle = 0; // default to 0
            
            while(iBegin <= iEnd)
            {
                iMiddle = ( iBegin + iEnd) / 2;
                if(anElement == buffer[iMiddle])
                {
                    return iMiddle; // that uses my copy constructor
                }
                else if(anElement < buffer[iMiddle])
                {
                    iEnd = iMiddle -1;
                }
                else
                {
                    iBegin = iMiddle + 1;
                }
            }
            
            return iBegin; // return a null interator because I didn't find the element
        }
        
       
    };
}

#endif /* set_h */

