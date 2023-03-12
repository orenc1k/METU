#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};


int KeyedHashTable::Hash(const std::string& key) const
{    
    int size;
    int i=0,hash=0;

    for (; i< key.length();i++)
    {
     hash+= ((int)key[i])* PRIME_LIST[i];        
    }

    size=tableSize;
    hash= hash % size;
   
    return hash;
    // TODO
}


void KeyedHashTable::ReHash()
{   
    int index;
    HashData *new_table;
    int size,old_size;
    size=tableSize*2;
    size= FindNearestLargerPrime(size);
    new_table=new HashData[size]; 
    old_size=tableSize;
    tableSize=size;

    for(int i=0; i< old_size; i++){
        index=Hash(table[i].key);
        if(new_table[index].key=="")
            {
            new_table[index].key=table[i].key;
            new_table[index].intArray=table[i].intArray;
            }
        else{
            index=helper_rehash(index,table[i].key,0,new_table);
            new_table[index].key=table[i].key;
            new_table[index].intArray=table[i].intArray;
        }    
    }
    delete []table;
    table=new_table;
    // TODO
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{   
    int i=0;
    for ( ; requestedCapacity>= PRIME_LIST[i];i++)
    { 
        
    }       
                 
    return PRIME_LIST[i];
    // TODO
}

KeyedHashTable::KeyedHashTable()
{   
    
    table=new HashData[2];   // DEFAULT CONSTRUCTOR
    tableSize=2;
    occupiedElementCount=0;
    // TODO
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    int capacity= FindNearestLargerPrime(requestedCapacity);  
    tableSize=capacity;
                             /// CONSTRUCTOR FOR NEAREST PRIME
    table=new HashData[capacity];
    occupiedElementCount=0;
    // TODO
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{   
    table=new HashData[other.tableSize];
    for(int i=0; i< other.tableSize; i++){
        table[i].intArray=other.table[i].intArray;
        table[i].key=other.table[i].key;
    }
    tableSize=other.tableSize;
    occupiedElementCount=other.occupiedElementCount;
    
    // TODO
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{   
    if(tableSize!=0)
        delete []table;

    table=new HashData[other.tableSize];
    
    for(int i=0; i< other.tableSize; i++){
        table[i].intArray=other.table[i].intArray;
        table[i].key=other.table[i].key;
    }
    
    tableSize=other.tableSize;
    occupiedElementCount=other.occupiedElementCount;
    
    // TODO
}

KeyedHashTable::~KeyedHashTable()
{   
    delete []table;
    
    // TODO
}


bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    int index;
    
    index=Hash(key);
    index=helper_insert(index,intArray,key,0);

    if(index==-1){
        return false;
        
    }
    
    else{occupiedElementCount++;

        if (occupiedElementCount*EXPAND_THRESHOLD>= tableSize)
            ReHash();
        
        
        return true;    
        } 
        
    // TODO
}

bool KeyedHashTable::Remove(const std::string& key)
{   
    
    for (int i=0; i< tableSize;i++){
        if(table[i].key==key){
            table[i].key="";
            table[i].intArray.clear();
            occupiedElementCount--;
            return true;
        }

    }

    return false;

    // TODO
}

void KeyedHashTable::ClearTable()
{
    for (int i=0; i<tableSize;i++){

        table[i].key="";
        table[i].intArray.clear();
    }
    
    occupiedElementCount=0;
    
   // TODO
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    for (int i=0; i< tableSize; i++){

        if (table[i].key==key){
            valueOut=table[i].intArray;
            return true;
        }
    }

    return false;
    
    // TODO
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}