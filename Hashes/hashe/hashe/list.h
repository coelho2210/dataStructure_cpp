
//  Created by Leo Silva on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef list_hpp
#define list_hpp
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom { // because I am creating my onw list I need to have my own
    // namesapce
    // otherwise i should code like this:  " std::"
    
    template< typename T > class list{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
#endif
    private:
        
        class node;// prototype from my class node
    
        
        node *pHead;
        node *pTail;
        int numElements;
        
    public:
        /*
         * Constructors & Destructor
         */
        
        class iterator;//prototype from my class iterator
        
        list(){
            numElements = 0;
            pHead = NULL;
            pTail = NULL;
        }
        
        list(list const &rhs){
            
                pHead = NULL;
                pTail = NULL;
                numElements = 0;
            
                node *current = NULL;
                node *nodeToBeCopied = rhs.pHead;
                while(nodeToBeCopied != NULL)
                {
                     node* copiedNode = new node(nodeToBeCopied->data);
                    if(pHead == NULL)
                    {
                        pHead = copiedNode;
                        current = pHead;
                    }
                    else
                    {
                        current->pNext = copiedNode;
                        current->pNext->pPrev = current;
                        current = current->pNext;
                        
                    }
                    numElements++;
                    pTail = copiedNode;
                    nodeToBeCopied = nodeToBeCopied->pNext;
                }

        }
        ~list()
        {// cant leave empty
            if (pHead != NULL)
            {
                node * pDelete = pHead;
                while(pHead->pNext != NULL)
                {
                    pHead = pHead->pNext;
                    delete pDelete;
                    pDelete = pHead;
                }
                delete pDelete;
                pHead = NULL;
                pTail = NULL;
                pDelete = NULL;
            }
            
        }
        
        int size() const{
            return numElements;
        }
        
        bool empty(){
            return !numElements;
        }
        void clear(){
            if (pHead != NULL)
            {
                node * pDelete = pHead;
                while(pHead->pNext != NULL)
                {
                    pHead = pHead->pNext;
                    delete pDelete;
                    pDelete = pHead;
                }
                delete pDelete;
                pHead = NULL;
                pTail = NULL;
                pDelete = NULL;
            }
            numElements = 0;
        }
        
        void push_front(const T & item) throw(const char *)
        {
            {
                if (pHead == NULL)
                {
                    pHead = pTail = new node (item);
                }
                    else
                    {
                        node  * newNode = new node(item);
                        newNode->pNext = pHead;
                        pHead->pPrev = newNode;
                        pHead = newNode;
                        newNode->pPrev = NULL;
                    }
                numElements++;
            }

        }
        
        void push_back(const T & item) throw(const char *)
        
        {
            
                if (pTail == NULL)
                    pHead = pTail = new node(item);
                else
                {
                    node * newNode = new node(item);
                    newNode->pPrev = pTail;
                    pTail->pNext = newNode;
                    pTail = newNode;
                    newNode->pNext = NULL;
                }
                numElements++;
            }
            
        
        void pop_front() throw(const char*)
        {
            if(pHead == NULL)
            {
                 numElements = 0;
                return;
            }
            
            if(pHead == pTail)
            {
                 numElements = 0;
                return;
            }
            
            if(pHead != NULL)
            {
                numElements--;
                pHead = pHead->pNext;
                delete pHead->pPrev;
                pHead->pPrev = NULL;
                
            }
                
        }
        void pop_back() throw(const char *)
        {
            if(pTail == NULL)
            {
                numElements = 0;
                return;
            }
            
            if(pTail == pHead)
            {
                numElements = 0;
                //delete ptail and phead
                //set them both to null
                return;
            }
            
            if(pTail != NULL)
            {
                numElements--;
                pTail = pTail->pPrev;
               // std::cerr << "??" <<std::endl;
                delete pTail->pNext;
                pTail->pNext = NULL;
            }
        }
        
        
        list& operator = (const list& rhs)//assignment operator
        {
            clear();
            {
                pHead = pTail = NULL;
                numElements = 0;
                
                node * temp = rhs.pHead;
                while(temp != NULL)
                {
                    this->push_back(temp->data);
                    temp = temp->pNext;
                }
            }
        
        return *this;
            
        }
        
       
        T & front() throw(const char*)
        {
            if (size() != 0)
                return pHead->data;
            else
                throw "Error: calling front on empty list.";
            
        }
        
        T & back() throw(const  char*)
        {
            if (empty())
            {
                throw"Error: calling back on empty list.";
            }
            else
                return pTail->data;
        }
        iterator find(const T & anElement){
             node * toFind = pHead;
            while(toFind != NULL)
            {
                if(toFind->data == anElement)
                    return iterator(toFind);// we just have node ( itetator just loops through nodes)
                
                toFind = toFind->pNext;
            }
            
            return iterator(); // return a null iterator;
    
        }
        iterator erase(iterator & toErase){
           //  NULL check
            if(toErase.ptr != NULL)
            {
            iterator toReturn; // create a null itetarstor
            
            
            if(toErase.ptr->pPrev != NULL)
            {
                toErase.ptr->pPrev->pNext = toErase.ptr->pNext; // setting the pPrev iteretor to the next
                
                toReturn = toErase.ptr->pPrev; // this is the ideal case ( when pprev exist), return this one
            }
            
            
            if(toErase.ptr->pNext != NULL)//go to the itetator and give me it pointer and see if the next exist
            {
                toErase.ptr->pNext->pPrev = toErase.ptr->pPrev;
                // the second case when ppre is null
                if(toReturn == NULL) // if still unitiaLIZE
                 {
                     toReturn = toErase.ptr->pNext; // prev dosen't exist return next
                 }
            }
        // check to see if the itetator is ponting to head or tail in LIST!!!!
                if (pHead == toErase.ptr)
                {
                    pHead = pHead->pNext; // assign to null or not we dont care!!!!
                }
                if(pTail == toErase.ptr)
                {
                    pTail = pTail->pPrev;
                }
                
            delete toErase.ptr;
            toErase.ptr = NULL; // avoid zombie
                return toReturn;
            
        }
            
            return iterator();// the third case when bothside is null
            
        }
        
        iterator begin(){
            return iterator(pHead);
        }
        
        iterator end(){
            return iterator(NULL);
        }
        
        iterator insert(const iterator & insertBeforeIt, T data) throw (const char*){
           
                // make a new pointer
                node * newNode = new node(data);

                if (insertBeforeIt == pHead)
                {
                    push_front(data);
                    return  begin();
                }
                   // inseting before tail
                    newNode->pNext = insertBeforeIt.ptr;
                    newNode->pPrev = insertBeforeIt.ptr->pPrev;
                    insertBeforeIt.ptr->pPrev->pNext = newNode;
                    insertBeforeIt.ptr->pPrev = newNode;
                    return iterator(newNode);
        }

        class iterator{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
            friend list;
        private:
            node* ptr;
        public:
            iterator(){
                ptr = NULL;
            }
            iterator(node *ptr){
                this->ptr = ptr;
            }
            iterator(const iterator& aIt){
                ptr = aIt.ptr;
            }
            iterator operator = (node *aPtr){
                ptr = aPtr;
                return *this;
            }
            bool operator==(iterator anIt)const{
                return ptr == anIt.ptr;
            }
            
            bool operator!=(iterator anIt)const{
                return ptr != anIt.ptr;
            }
            // iterator to node comparition!!!!!!!!
            bool operator==( const node * & leo)const{
                return ptr == leo;
            }
            // iterator to node comparition!!!!!!!!
            bool operator!=(const node * & leo)const{
                return ptr != leo;
            }
            //prefix operator
            iterator operator++(){
                if (ptr != NULL) {
                    if (ptr->pNext != NULL) // we are not at the end
                    {
                        ptr = ptr->pNext;  // we don't have a buffer, this is how we walk through the list
                    }
                }
                else
                {
                    throw "Error: incrementing null node.";
                }
                return *this;
            }
            //postfix operator
            iterator operator++(T lhs){
                iterator result = iterator(*this);
                if (ptr != NULL) {
                    ptr = ptr->pNext;  // we don't have a buffer, this is how we walk through the list
                    
                }
                else
                {
                    throw "Error: incrementing null node.";
                }
                return result;
            }
            //prefix operator
            iterator operator--(){
                if (ptr != NULL) {
                    if (ptr->pPrev != NULL) // we are not at the beginning
                    {
                        ptr = ptr->pPrev;  // we don't have a buffer, this is how we walk through the list
                    }
                }
                else
                {
                    throw "Error: decrementing null node.";
                }
                return *this;
            }
            //postfix operator
            iterator operator--(T lhs){
                iterator result = iterator(*this);
                if (ptr != NULL) // valid pointer
                {
                  if (ptr->pPrev != NULL) // we are not at the beginning
                  {
                      ptr = ptr->pPrev;  // we don't have a buffer, this is how we walk through the list
                  }
                }
                else
                {
                    throw "Error: decrementing null node.";
                }
                return result;
            }
            //dereference operator
            T& operator *(){
      
            if(ptr != NULL)
            {
               return ptr->data;
            }
            
            else
            {
                throw "Error: dereferencing null node.";
            }
        }
        };
        
    private: // because We dont people to have access to the node outside
        // to the list
        class node{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
            
        public:
            T data;
            node *pNext;
            node *pPrev;
            
            /*
             * Create Node
             */
            node(){ // default
                data = T(); // could not be zero because we should call the default constructor for the template
                pNext = NULL;
                pPrev = NULL;
            }
            
            node(const T & rhs){ // non-default constructor
                pPrev = NULL;
                pNext = NULL;
                data = rhs;
                
                //node <T> *pNext;
            }
            
            ~node(){ //destructor
                
                pNext = NULL;//avoid zombie
                pPrev = NULL;// avoid zombie
            }
        };
        
    };
    
}
    
#endif /* list_h */
    
    

