
//  Created by Leo Silva on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp
#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom { // because I am creating my onw BST I need to have my own
    // namesapce
    // otherwise i should code like this:  " std::"
    
    template< typename T > class BST{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
#endif
    private:
        
        class BNode;// prototype from my class node
    
        
        BNode * root;
        int numElements;
        
        // I am buiding a stack of fucntion call for every node
        // because without it I will need to a lot of sintax
        // buiding a stack means
       BNode *copyBTree(const BNode *pNode)
        {
            if(pNode == NULL)
            {
                // for a pLeft and pRight point to at the leaves
                return NULL;
            }
            
            BNode * newOne = new BNode(pNode->data);
            
            newOne->pLeft  = copyBTree(pNode->pLeft);
        newOne->pRight = copyBTree(pNode->pRight);
            
            if (newOne->pLeft != NULL)
            {
                newOne->pLeft->pParent = newOne;
            }
            if (newOne->pRight != NULL)
            {
                newOne->pRight->pParent = newOne;
            }
            
            return newOne;
        }
        
        void deleteBinaryTree(BNode *pNode)
       {
            if (!pNode)
            {
                return;
            }

            if (pNode->pLeft != NULL)
                deleteBinaryTree(pNode->pLeft);
            if (pNode->pRight != NULL)
                deleteBinaryTree(pNode->pRight);

            delete pNode;
            pNode = NULL;
            return;
     }

    public:
        /*
         * Constructors & Destructor
         */
        
        class iterator;//prototype from my class iterator
        
        BST(){// default constructor
            root = NULL;
            numElements = 0;
        }
        
        BST(BST const &rhs){ // copy constructor
            
            if ( rhs.root != NULL)
            {
                 //allocate a new root
                // root = rhs.root ;  that is a shalow copy
               
                // deep copy
                root = copyBTree(rhs.root);
                numElements = rhs.numElements;
                
            }
            else{
                //BST();
                // the same thing
                root = NULL;// this way will be a litle faster
                numElements = 0;
            }
    
        }
        
        
        ~BST()
        {// cant leave empty
            clear();
        }
        
        int size() const{
            
            return numElements;
        }
        
        
        bool empty() const{
           
            if (numElements != 0)
            {
                return false;
            }
            
            return true;
        }
        void clear(){
            if (!root)
            {
                return;
            }
            
            if (root->pLeft != NULL)
                deleteBinaryTree(root->pLeft);
            if (root->pRight != NULL)
                deleteBinaryTree(root->pRight);
            
            numElements = 0;
            delete root;
            root = NULL;
            
        }
        
        iterator find(const T & anElement){

            BNode * pNode = root;
            while(pNode != NULL)
            {
                if(pNode->data == anElement)
                {
                    return iterator(pNode);
                }
                if(pNode->data <= anElement)
                    pNode = pNode->pRight;
                else
                    pNode = pNode->pLeft;
            }
            
    
              return iterator(pNode);
          }
        
        iterator erase(iterator & toErase){
            
            iterator toReturn = toErase;
            ++toReturn;

            if(toErase.ptr->pRight == NULL && toErase.ptr->pLeft ==  NULL)
            {
                
                if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pRight == toErase.ptr)
                {
                    toErase.ptr->pParent->pRight = NULL;
                }
                if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pLeft == toErase.ptr)
                {
                    toErase.ptr->pParent->pLeft = NULL;
                }
                if(toErase.ptr == root)
                {
                    root = NULL;
                }

            }


            if(toErase.ptr->pRight == NULL && toErase.ptr->pLeft != NULL)
            {
                toErase.ptr->pRight->pParent = toErase.ptr->pParent;

                if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pRight == toErase.ptr)
                {
                  toErase.ptr->pParent->pRight = toErase.ptr->pLeft;
                }
                if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pLeft == toErase.ptr)
                {
                  toErase.ptr->pParent->pLeft = toErase.ptr->pLeft;
                }

                if(toErase.ptr == root)
                {
                    root = toErase.ptr->pLeft;
                }

            }

            if(toErase.ptr->pLeft == NULL && toErase.ptr->pRight != NULL)
            {
                toErase.ptr->pRight->pParent = toErase.ptr->pParent;

                 if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pRight == toErase.ptr)
                 {
                   toErase.ptr->pParent->pRight = toErase.ptr->pRight;
                 }
                if(toErase.ptr->pParent != NULL && toErase.ptr->pParent->pLeft == toErase.ptr)
                 {
                   toErase.ptr->pParent->pLeft = toErase.ptr->pRight;
                 }
                if(toErase.ptr == root)
                {
                    root = toErase.ptr->pRight;
                }

            }
            
            if(toErase.ptr->pLeft != NULL && toErase.ptr->pRight != NULL)
            {
                if(toReturn.ptr)
                {
                    if(toReturn.ptr->pParent)
                        toReturn.ptr->pParent->pLeft  = toReturn.ptr->pRight;
             
                    if(toReturn.ptr->pRight)
                        toReturn.ptr->pRight->pParent = toReturn.ptr->pParent;
                
                    if(toErase.ptr)
                    {
                    toReturn.ptr->pLeft = toErase.ptr->pLeft;
                    toReturn.ptr->pRight = toErase.ptr->pRight;
                    }
                
                    if(toReturn.ptr->pLeft)
                    {
                        toReturn.ptr->pLeft->pParent = toReturn.ptr;
                    }
                    if(toReturn.ptr->pRight)
                    {
                        toReturn.ptr->pRight->pParent = toReturn.ptr;
                    }
                }
                if(toErase.ptr == root)
                {
                    root = toReturn.ptr;
                }

            }

              delete toErase.ptr;
              toErase.ptr = NULL; // avoid zombie
            numElements--;
             return toReturn;
            //return iterator();
        }
        iterator begin(){
            
            if (root == NULL)
            {
                return NULL;
            }
            
            BNode * pNode = root;
            
            while (pNode->pLeft)
            {
                pNode = pNode->pLeft;
            }
            
            return iterator(pNode);
        }
        
        iterator end(){
            
            if (root == NULL)
            {
                return NULL;
            }
            
            BNode * pNode = root;
            
            while (pNode->pRight)
            {
                pNode = pNode->pRight;
            }
            
            return iterator(pNode);
        }
        
      void  insert(T data) throw (const char*){
          
              //case1 - No Parent
              if (numElements == 0) {
                    root = new BNode(data);
                  numElements++;
                  return;
              }
          BNode *temp = new BNode(data);
          
              BNode *pNode = root;
          
                      while(pNode)
                      if(pNode->data >= data)
                      {
                          if(pNode->pLeft == NULL)
                          {
                              pNode->pLeft = temp;
                              pNode->pLeft->pParent = pNode;
                              break;
                          }
                          pNode = pNode->pLeft;
                      }
                  else
                      {
                          if(pNode->pRight == NULL)
                          {
                              pNode->pRight = temp;
                              pNode->pRight->pParent = pNode;
                              break;
                          }
                          pNode = pNode->pRight;
                      }
          numElements++;
      }

        class iterator{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
            friend BST;
          
        private:
            BNode* ptr;
        public:
            iterator(){
                ptr = NULL;
            }
            iterator(BNode *ptr){
                this->ptr = ptr;
            }
            iterator(const iterator& aIt){
                ptr = aIt.ptr;
            }
            iterator operator = (BNode *aPtr){
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
            bool operator==( const BNode * & leo)const{
                return ptr == leo;
            }
            // iterator to node comparition!!!!!!!!
            bool operator!=(const BNode * & leo)const{
                return ptr != leo;
            }
            
            //prefix operator
            iterator operator++(){
                if( ptr == NULL)
                {
                    throw "Error: incrementing null node.";
                }
                if(ptr->pRight)
                {
                    ptr = ptr->pRight;
                    
                    while(ptr->pLeft)
                    {
                        ptr = ptr->pLeft;
                    }
                }
                else if (ptr->pParent)
                {
                    if(ptr == ptr->pParent->pLeft)
                    {
                        ptr = ptr->pParent;
                    }
                    else  if(ptr == ptr->pParent->pRight)
                    {
                        if(ptr->pParent->pParent)
                        {
                            if(ptr->data < ptr->pParent->pParent->data)
                                ptr = ptr->pParent->pParent;
                            else
                                ptr = NULL;
                        }
                        else
                            ptr = NULL;
                   
                    }
                }
               
                return *this;
                
            }
            
            //postfix operator
            iterator operator++(int lhs){
                iterator result = iterator(*this);
                if (ptr != NULL) {
                    ++ *this;
                }
                else
                {
                    throw "Error: incrementing null node.";
                }
                return result;
            }
            //prefix operator
            iterator operator--(){
                if( ptr == NULL)
                {
                    throw "Error: decrementing null node.";
                }
                if(ptr->pLeft)
                {
                    ptr = ptr->pLeft;
                    
                    while(ptr->pRight)
                    {
                        ptr = ptr->pRight;
                    }
                }
                else if (ptr->pParent)
                {
                    if(ptr == ptr->pParent->pRight)
                    {
                        ptr = ptr->pParent;
                    }
                    else  if(ptr == ptr->pParent->pLeft)
                    {
                        if(ptr->pParent->pParent)
                        {
                            if(ptr->data > ptr->pParent->pParent->data)
                                ptr = ptr->pParent->pParent;
                            else
                                ptr = NULL;
                        }
                        else
                            ptr = NULL;
                        
                    }
                }
                return *this;
            }
                
            
            //postfix operator
            iterator operator--(int lhs){
                iterator result = iterator(*this);
                if (ptr != NULL) // valid pointer
                {
                    -- *this;
                  
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
        // to the BST
        class BNode{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
            
        public:
            T data;
            BNode *pLeft;
            BNode *pRight;
            BNode *pParent;
            //bool isRed;
            
            /*
             * Create Node
             */
            BNode(){ // default
                //data = T(); // could not be zero because we should call the default constructor for the template
                pLeft = NULL;
                pRight = NULL;
                pParent = NULL;
                
            }
            
            BNode(const T & rhs){ // non-default constructor
                pLeft = NULL;
                pRight = NULL;
                pParent = NULL;
                data = rhs;
            }
        
        };
        
    };
}
    
#endif /* BST_h */
    
    

