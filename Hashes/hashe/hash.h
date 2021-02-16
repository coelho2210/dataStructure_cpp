
#ifndef hash_h
#define hash_h


#include "list.h"
#ifdef UNIT_TESTING

int main(int argc, const char* argv[]);
#endif

namespace custom {
    template < typename T > class Hash {

#ifdef UNIT_TESTING
        friend int ::main(int argc,const char* argv[]);
#endif
        
    private:
        list<T>** table;
        int numElements;
        long numBuckets;
        
    public:
        Hash(long numBuckets) throw (const char*){
            if(numBuckets <= 0){
                throw "Error: Hashes must have at least 1 bucket.";
            }
            table = new list<T>*[numBuckets];
            for (int i = 0; i < numBuckets; i++) {
               
                table[i] = new list<T>(); // create a default list for the table at i to point to
            }
            
            this->numBuckets = numBuckets;
            this->numElements = 0;
        }
        Hash (const Hash& rhs){ // copy constructor
            
           if(rhs.numBuckets > 0)
           {
               table = new list<T>*[rhs.numBuckets];
               for(int i = 0; i < rhs.numBuckets; i++)
               {
                   table[i] = new list<T>(*rhs.table[i]);
               }
               this->numBuckets = rhs.numBuckets;
               this->numElements = rhs.numElements;
           }
            else
                throw "Error: Hashes must have at least 1 bucket.";
            
               
        }
        
        ~Hash(){
            clear();
        }
        
        void clear()
        {
            if(table != NULL)
            {
                for ( int i = 0; i < numBuckets; i++)
                {
                    if(table[i] != NULL)
                    {
                        delete table[i];
                    }
                }
                
            
            delete [] table;
               // delete table;
            table = NULL;
            }
            
        }
        
        int size(){
            return numElements;
        }
       
        long capacity(){
            return numBuckets;
        }
        bool empty(){
            
            return numElements == 0;
        }
        bool find (const T& aValue, long (*hashFunc)(const T&, long)){
            
            typename custom::list <T> :: iterator it = table[hashFunc(aValue,numBuckets)]->find(aValue);
            if (table[hashFunc(aValue,numBuckets)]->end() == it)
            {
               return false;
            }
            else
                return true;

        }

     void insert ( const T& aValue, long (*hashFunc) (const T&, long)){
         
         //std::cout << hashFunc(aValue,7) << std::endl;
          table [hashFunc(aValue,numBuckets)]->push_back(aValue);
         numElements++;
     
        }

        Hash& operator = (const Hash& rhs){

            clear();
            
            this->numElements = rhs.numElements;
            this->numBuckets = rhs.numBuckets;
            //this needs to alocate all the new data

            table = new list<T>*[rhs.numBuckets];
            
            for (int i = 0; i < numBuckets; i++)
            {
                table[i] = new list<T>;
                for (typename list<T>::iterator it =rhs.table[i]->begin();
                     it != rhs.table[i]->end(); it++ )
                    table[i]->push_back(*it);
            }

            return *this;
            
        }

    };
}

#endif /*hash_h */

