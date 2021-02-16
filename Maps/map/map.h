
//  Created by Leo Silva on 9/15/18.
//  Copyright © 2018 Lee Barney. All rights reserved.
//

#ifndef MAP_hpp
#define MAP_hpp
#ifdef UNIT_TESTING
#include "bst.h"

int main(int argc, const char* argv[]);
#endif

namespace custom { // because I am creating my onw map I need to have my own
    // namesapce
    // otherwise i should code like this:  " std::"
    template< typename K, typename V > class map{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
#endif
    public:
        class pair;
    private:
        BST <pair> bst;
    public:
        class iterator;
        map()//constructor
        {
            bst = BST<pair>();
        }
        
        map operator = (map const &rhs)  throw (const char*)
        {
            if(!rhs.bst.empty())
            {
                this->bst = rhs.bst;
                
            }
            
            return map();
        }
        
        ~map(){
            clear();
        }
        
        int size()
        {
            return bst.size();
        }
        
        void clear(){
        
          bst.clear();
        }
        
        bool empty()
        {
            return bst.empty();
        }
        
        V & operator [](const K & key) throw(const char*) // setter version
        {
            pair match(key, V());
            typename BST<pair>:: iterator it = bst.find(match);

            if(it != NULL)
            {
                return (*it).second;
            }
            else
                bst.insert(match);

                return(*bst.find(match)).second;
            
            return (*bst.find(pair(key,V()))).second;
        }
        
        V operator[](const K & key) const throw(const char *) // getting version
        {
            pair match(key, V());
            typename BST<pair>:: iterator it = bst.find(match);

            if(it != NULL)
            {
                return (*it).data.second;
            }
            else
                bst.insert(match);

                return(*bst.find(match)).data.second;
//
            return (*bst.find(pair(key,V()))).second;
        }
        iterator find(const K & aKey){
        
            //create a temp variable to hold a pair
            pair temp = pair(aKey, V());
            
            // return a map iterator - where pair was found in the tree
            
            iterator mapIt = bst.find(temp);
            return mapIt;
            
        }
        
        void  insert(const K &key, const V &value) throw (const char*){
       
            pair match(key,value);
            typename BST<pair>:: iterator it = bst.find(match);
            
            if(it != typename BST<pair>::iterator())
            {
                *it = match;
            }
            else
                bst.insert(match);
    }
        
        iterator begin(){
            
            
            return iterator(bst.begin());
        }
        
        iterator end(){
            
            return iterator(bst.end());
        }
    
        
        
        class pair{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
        
    public:
            K first;
            V second;
            
            
            pair(){ // constructor
                
                first =  K();
                second = V();
            }
            
            pair(const K &first,const V &second)
            {
                this->first  = first;
                this->second = second;
            }
            
            pair & operator = (pair const &rhs)
            {
                
                first = rhs.first;
                second = rhs.second;
                return *this;
            }
            
            bool operator ==(pair const &rhs)
            {
                return first == rhs.first;
            }
            
            bool operator >(pair const &rhs)
            {
                return first > rhs.first;
            }
           
            bool operator <(pair const &rhs)
            {
              return first < rhs.first;
                
            }
           
            bool operator <=(pair const &rhs)
            {
              return first <= rhs.first;
                
            }
            
            bool operator >=(pair const &rhs)
            {
               return first >= rhs.first;
                
            }
            
        };
        
        class iterator{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
        private:
            typename BST<pair>::iterator it;
        public:
            iterator(){
            }
            iterator( const typename  BST<pair>::iterator &it){
                this->it = it;
            }
            iterator(const iterator& aIt){
                it = aIt.it;
            }
            iterator operator = ( typename BST<pair>::iterator *it){
                it = it;
                return *this;
            }
            bool operator==(iterator anIt)const{
                return it == anIt.it;
            }
            
            bool operator!=(iterator anIt)const{
                return it != anIt.it;
            }
            // iterator to node comparition!!!!!!!!
            bool operator==( const  typename BST<pair>::iterator * & leo)const{
                return it == leo;
            }
            // iterator to node comparition!!!!!!!!
            bool operator!=(const typename BST<pair>::iterator * & leo)const{
                return it != leo;
            }
            
            //prefix operator
            iterator operator++(){
                if( it == NULL)
                {
                    throw "Error: incrementing null node.";
                }
                ++it;
                return *this;
            }
            
            //postfix operator
            iterator operator++(int lhs){
                iterator result = iterator(*this);
                if (it != NULL) {
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
                --it;
                return *this;
            }
                
            
            //postfix operator
            iterator operator--(int lhs){
                iterator result = iterator(*this);
                if (it != NULL) // valid pointer
                {
                    --it;
                  
                }
                else
                {
                    throw "Error: decrementing null node.";
                }
                return result;
            }
            
            //dereference operator
            pair& operator *() {
      
            if(it != NULL)
            {
               return *it;
            }
            
            else
            {
                throw "Error: dereferencing null node.";
            }
        }
    };// end of my iterator class

}; // end of map
    
    
} // end of my nameSpace
    
    
    
#endif /* bst_h */
    
    

