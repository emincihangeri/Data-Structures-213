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
    // TODO
    int res = 0, len = key.length();
    for(int i = 0; i < len; i++){
        res += key[i] * PRIME_LIST[i];
    }
    return res % tableSize;
}

void KeyedHashTable::ReHash()
{
    // TODO
    int new_size = FindNearestLargerPrime(2 * tableSize);
    std::vector<HashData> holder;
    for(int i = 0; i < tableSize; i++){
        if(table[i].key != ""){
            holder.push_back(table[i]);
        }
    }
    delete [] table;
    table = NULL;
    table = new HashData[new_size];
    occupiedElementCount = 0;
    tableSize = new_size;
    for(int i = 0; i < holder.size(); i++){
        Insert(holder[i].key, holder[i].intArray);
    }
    tableSize = new_size;
    holder.clear();
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
    int i = 0;
    while(PRIME_LIST[i] <= requestedCapacity){
        i++;
    }
    return PRIME_LIST[i];
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
    table = new HashData[2];
    tableSize = 2;
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
    tableSize = FindNearestLargerPrime(requestedCapacity);
    table = new HashData[tableSize];
    occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
    table = new HashData[other.tableSize];
    for(int i = 0; i < other.tableSize; i++){
        table[i].key = other.table[i].key;
        table[i].intArray = other.table[i].intArray;
    }
    tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
    delete [] table;
    tableSize = 0;
    occupiedElementCount = 0;
    table = new HashData[other.tableSize];
    for(int i = 0; i < other.tableSize; i++){
        table[i].key = other.table[i].key;
        table[i].intArray = other.table[i].intArray;
    }
    tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO
    delete [] table;
    tableSize = 0;
    occupiedElementCount = 0;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO
    int i = Hash(key), t = 1;
    while(table[i].key != ""){
        if(table[i].key == key){
            return false;
        }
        i += t;
        t += 2;
        if(i >= tableSize){
            i %= tableSize;
        }
    }
    table[i].key = key;
    table[i].intArray = intArray;
    occupiedElementCount++;
    if(occupiedElementCount * EXPAND_THRESHOLD >= tableSize){
        ReHash();
    }
    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
    int i = Hash(key), t = 1;
    while(table[i].key != ""){
        if(table[i].key == key){
            table[i].key = "__DELETED__";
            table[i].intArray.clear();
            occupiedElementCount--;
            return true;
        }
        i += t;
        t += 2;
        if(i >= tableSize){
            i %= tableSize;
        }
    }
    return false;
}

void KeyedHashTable::ClearTable()
{
   // TODO
   for(int i = 0; i < tableSize; i++){
       if(table[i].key != ""){
            table[i].key = "";
            table[i].intArray.clear();
            occupiedElementCount--;
       }
   }
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO
    int i = Hash(key), t = 1;
    while(table[i].key != ""){
        if(table[i].key == key){
            valueOut = table[i].intArray;
            return true;
        }
        i += t;
        t += 2;
        if(i >= tableSize){
            i %= tableSize;
        }
    }
    return false;
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