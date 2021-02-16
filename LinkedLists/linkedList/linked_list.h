
//
//  linked_list.hpp
//  linked_list
//
//  Created by Lee Barney on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <iostream>
using namespace std;

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif
namespace custom {
    template< typename T > class node{
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
            data = 0;
            pNext = NULL;
            pPrev = NULL;
        }
        
        node(const T & rhs){ // non-default constructor
            pPrev = NULL;
            pNext = NULL;
            this->data = rhs;
            
            //node <T> *pNext;
        }
        
        ~node(){ //destructor
            
        }
    };
    
}
       template<class T>
void  clear(custom::node<T> * & pNode) throw (const char*){
    
    
    
    // see if we are in the "final" spot
    if(pNode == NULL)
    {
        throw "Error: freeing NULL list.";
    }
    
    
    if(pNode->pNext != NULL)
    {
        //recursively call clear on the nest node (build our stack first)
        clear(pNode->pNext);
        //then delete the node that the pointer is pointing to
        delete pNode;
        pNode = NULL;
    }
    // now we have hit the end. No more need to recursively call clear()
    else {
        delete pNode;
        pNode = NULL;
        return;
    }
}
        
    template <class T>
custom::node <T> * insert( custom::node<T> * &pNode, T data, bool after = false) throw (const char*){

    if (pNode == NULL)
    {
        throw "Error: inserting into NULL list.";
    }

    custom::node<T> *newOne = new custom::node<T>(data);

    if (!after)
    {
        newOne->pNext = pNode;
        if(pNode->pPrev != NULL)
        {
            pNode->pPrev->pNext = newOne;
            newOne->pPrev = pNode->pPrev;
        }
        pNode->pPrev = newOne;
    }
    else // after
    {
        newOne->pPrev = pNode;
        if (pNode->pNext != NULL)
        {
            pNode->pNext->pPrev = newOne;
            newOne->pNext = pNode->pNext;
        }
        pNode->pNext = newOne;
    }
     return newOne;
}

template <class T>
custom::node<T> * copy(custom::node<T> * pSource) throw(const char *)
{
    // Check to see if  I got  a NULL
    if (pSource == NULL)
        return NULL; // return a NULL pointer
    
    // Create my temporary pointer to return as our list to the client
    custom::node <T> * myCopy = new custom::node <T>;
    
    // Copy data into the temporary pointer
    myCopy->data = pSource->data; // assign  data value
    
    // if the next exist than recursively call copy on the next
    if (pSource->pNext != NULL)
        // assign next to newly created Node
        // I'm calling copy() because I want to deal with the "new" once
        // that means I will have a node representing each item in the list and assign the next to that allocated node
        myCopy->pNext = copy(pSource->pNext);
        // check if the next is not Null because null dosent have a previous
    if(myCopy->pNext != NULL)
        // assing the next "person " in lne to have his previous point to me"
        myCopy->pNext->pPrev = myCopy;
        
    return myCopy;//  return a pointer to the allocated memory
}
  template <class T>
custom::node <T> * find(custom::node<T> * pNode, T anElement)

{
    if (pNode !=NULL)
    {
        while(pNode->pNext)
        {
            if(anElement == pNode->data)
            {
                return pNode;
            }
            pNode = pNode->pNext;
        }
        if (anElement == pNode->data)
        {
            return pNode;
        }
    }
    
    return NULL;
}

template <class T>
custom::node <T> * remove (custom::node<T> * &pRemove)
{
    //when it pointing to allocate memory
   if (pRemove != NULL)
   {   // create a new node  ( because I need to keep track of which node I am going to return)
       // I am going to delete the node in the list. If I delete the node, I lose access to the rest of the list.
       // Thus I need to maintain a pointer (toReturn) to the node to be returned.
       custom::node <T> * toReturn;
       // on Prenove go to the next one
       if(pRemove->pNext != NULL)
       {
           //see if the left exist
           if(pRemove->pPrev != NULL)
           {
               //setting pPrev to the next
               // I am deleting PRemove, so I need to set pprev(PRemove) to  PNext(pRemove)
               pRemove->pPrev->pNext = pRemove->pNext;
              // ???????
               toReturn = pRemove->pPrev;
               //return pRemove->pNext;
           }
           else{
               // ????? why
               toReturn = pRemove->pNext;
           }
           //
           pRemove->pNext->pPrev = pRemove->pPrev;
           delete pRemove;
           pRemove = NULL;
           return toReturn;
       }
       else // pNext is NULL
       {
          if(pRemove->pPrev != NULL)
          {
              pRemove->pPrev->pNext = NULL;
              toReturn = pRemove->pPrev;
              delete pRemove;
              pRemove = NULL;
              return toReturn;
          }
          else { // pPrev is NULL, single NULL
              toReturn = NULL;
              delete pRemove;
              pRemove = NULL;
              return toReturn;
          }
       }
       
   }
    return pRemove;
}

#endif /* linked_list_h */

