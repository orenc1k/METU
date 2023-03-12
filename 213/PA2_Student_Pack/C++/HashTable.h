#ifndef __KEYED_HASH_TABLE_H__
#define __KEYED_HASH_TABLE_H__

#include <vector>
#include <string>

// Expand threshold is the multiplicative inverse of the 1/3 (%33)
// in order to prevent floating point math
#define EXPAND_THRESHOLD 3
// Only first 100 primes are defined, test cases would not exceed the maximum
// prime in this table
#define PRIME_TABLE_COUNT 100

struct HashData
{
    std::vector<int>    intArray;
    std::string         key;
    // Constructor
                        HashData() { key = ""; }
};

// A Simple Hash Table class
// Holds key value pairs
// Key is a string, Value is an integer array
// using quadratic probing for collision
class KeyedHashTable
{
    private:
        // Stores the first 100 primes
        static const int            PRIME_LIST[PRIME_TABLE_COUNT];
        static int                  FindNearestLargerPrime(int requestedCapacity);

        // Hash Table Storage
        HashData*                   table;
        int                         tableSize;
        int                         occupiedElementCount;

        // Private Functions
        // Generates hash from the string (initial index on the table)
        // Please check the Assignment Text for more information
        int                         Hash(const std::string& key) const;
        // Doubles the capacity to the nearest prime
        // Rehash the entire table to the new expanded table
        void                        ReHash();

        // Friend class that will access your private members etc.
        // This will be used for testing. Do not remove/edit these
        // statements.
        friend class                PA3_HT_TEST_CASE;
        friend class                PA3_MAPS_TEST_CASE;

    public:
        // Constructors & Destructor
                                    KeyedHashTable();
                                    KeyedHashTable(int requestedCapacity);
                                    KeyedHashTable(const KeyedHashTable&);
        KeyedHashTable&             operator=(const KeyedHashTable&);
                                    ~KeyedHashTable();
        // Methods
        // Insert
        // Inserts the key value pair
        // If key already exists on the table:
        // function returns false
        // returns true if insertion is successful
        bool                    Insert(const std::string& key,
                                       const std::vector<int>& intArray);
        // Tries to remove the key/value pair defined by the key
        // If key/value pair is not found function returns false
        // returns true if remove operation is successful
        bool                    Remove(const std::string& key);
        // Clears Entire Table removes everything
        // Does NOT deallocate memory tho
        void                    ClearTable();
        // Finds the value pair
        // returns true if found (and also populates the value out with the data)
        // returns false if key is not found in the table
        bool                    Find(std::vector<int>& valueOut,
                                     const std::string& key) const;
        // Prints the table
        void                    Print() const;

    private:


    int helper_insert( int index,const std::vector<int> intArray,const std::string key,int prob)
    {
    
    int index_eq=-1;
    
    if(index>=tableSize)
        {
            index_eq=index;
            index-=tableSize;
        }
    if(table[index].key==key)
        return -1;
        
    else{ 
        if (index_eq!=-1){
            index=index_eq;
        }
        index+=prob*prob;
    
        if(table[index].key=="")
            {
            table[index].intArray=intArray;
            table[index].key=key;
            return -31;
            }
            
        index-=prob*prob;    
        prob++;
        helper_insert(index,intArray,key,prob);
    }  
      
    }            

        int helper_rehash( int index,const std::string key,int prob,HashData* table)
    {
        int index_eq=-1;
        
        index+=prob*prob;
        if (index>=tableSize)
            {
            index_eq=index;
            index-=tableSize;
            }
        if(table[index].key=="")
            {
            return index;
            }

        else{
            if(index_eq!=-1){
                index=index_eq;
            }
        index-=prob*prob;    
        prob++;
        return helper_rehash(index,key,prob,table);
        }   
    }

};
#endif //__KEYED_HASH_TABLE_H__