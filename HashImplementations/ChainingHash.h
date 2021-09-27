/* 
    Hugo Aponte
    ChainingHash class
*/

/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <cmath>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    vector<list<pair<K, V>>> table; // our representation of chaining hash
    int numElements;
    int sizeT;
    
public:
    // constructor
    ChainingHash(int n = 11){
        table.resize(n);
        numElements = 0;
        sizeT = n;
    }
    
    // copy constructor
    ChainingHash(vector<list<pair<K, V>>> other){
        table = other;
        numElements = 0;
        sizeT = other.size();
    }

    // destructor
    ~ChainingHash() {
        this->clear();
    }

    // check if table is empty
    bool empty() {
        if(table.empty())
            return true;

        return false;
    }

    // return size of vector (hash table)
    int size() {
        return sizeT;
    }

    // return the value at given key
    // if no value found, allocate new space for given key
    V& at(const K& key) {

        list<pair<K, V>> list = table.at(this->hash(key));
        
        for(int i = 0; i < (int)list.size(); i++)
        {
            if(list.front().first == key)
                return list.front().second;
            else
                list.pop_front();
            
        }
        if(list.front().first != key)
        {
            std::cout << "Key not in Hash!\n";

        }


        return *(new V());

    }

    // return the value at given key; 
    // overloaded operator[] function makes use of vector's [] operator function 
    V& operator[](const K& key) {
        list<pair<K, V>> list = table[hash(key)];
        for(int i = 0; i < (int)list.size(); i++)
        {
            if(list.front().first == key)
                return list.front().second;
            else
                list.pop_front();
        }  
        if(list.front().first != key)
        {
            std::cout << "Key not found!\n";
        }

        return *(new V());
    }

    // count the amount of items in the bucket pertaining to given key value
    int count(const K& key) {
        int count = 0;
        int index = this->hash(key);
        list<pair<K, V>> list = table[index];
        for(int i = 0; i < (int)list.size(); i++)
        {
            if(list.front().first == key)
                count++;

            list.pop_front();
        }
        return count;

    }

    // insert make_pair
    // this function should be corrected to make use of a possible move constructor
    // the move function would allow moving the value from one memory space to another rather than copying the value across memory spaces 
    void emplace(K key, V value) {
        std::pair<K, V> pair{key, value};
        insert(pair);
    }

    // uses the hash function to insert a value with a give key
    // parameter pair can access key with pair.first; 
    // parameter pair can access value with pair.secont;
    // increase numEleents; recalculate load_factor to find if resizing hash necessary
    void insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first);
        float loadFactor;
        table[index].push_back(pair);
        this->numElements++;
        loadFactor = load_factor();
        if(loadFactor >= .75)
            rehash();
        
    }

    // uses vector's remove function to remove key,val pair
    void erase(const K& key) {
        list<pair<K, V>> *list = &table[hash(key)];
       
        for(auto it : *list)
        {
            if(it.first == key)
            {
                list->remove(it);
                numElements--;
                break;
            }

        } 
    }

    // removes every element in the list of every bucket within given vector
    void clear() {
        list<pair<K, V>> *list = &table[0];
        for(int i = 1; i < (int)list->size() - 1; i++)
        {
            while(list != nullptr)
                list->pop_front();
            
            list = &table[i];
        }
        table.clear();
    }

    // returns number of elements
    int bucket_count() {
        return numElements;
    }

    // returns the size of the list at n
    int bucket_size(int n) {
        return table[n].size();
    }

    // returns the hash function to key
    int bucket(const K& key) {
        
        return this->hash(key);

    }

    // calculates load_factor to see if we need more space / resize
    float load_factor() {
        return ((float)numElements / (float)table.size());
    }

    // rehashing function using 50% of sizeT
    // rehashing function inefficient because it requires copying information to a temporary vector, 
        // clearing og vector, resizing og vector, and recopying to og vector from temporary vector
    void rehash() {
        vector<list<pair<K, V>>> copy{table};
        int i = 0;

        this->clear();
        
        i = findNextPrime(sizeT * 2);
        table.resize(i);
        sizeT = i;
        numElements = 0;
        
        i = 0;
        while(!copy.empty())
        {
            while(!copy[i].empty())
            {
                this->insert(copy[i].front());
                copy[i].pop_front();            
            }    
            i++;
            if(copy[i].empty() && copy[copy.size() - 1].empty())
                break;
        }

    }

    // rehashing function which uses given n to findNextPrime
    // rehashing function inefficient because it requires copying information to a temporary vector, 
        // clearing og vector, resizing og vector, and recopying to og vector from temporary vector
    void rehash(int n) {
        vector<list<pair<K, V>>> copy{table};
        int i = 0;

        this->clear();
        
        n = findNextPrime(n);
        table.resize(n);
        sizeT = n;
        numElements = 0;
        
        while(!copy.empty())
        {
            while(!copy[i].empty())
            {
                this->insert(copy[i].front());
                copy[i].pop_front();            
            }    
            i++;
            if(copy[i].empty() && copy[copy.size() - 1].empty())
                break;
        }
    }


private:
    // incrementing given from n until next prime is found
    int findNextPrime(int n)
    {

        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    // checks if given number is prime
    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    // our rehashing function which mostly depends on table.size()
    int hash(const K& key) {
        return key % table.size();       
    }

};

#endif //__CHAINING_HASH_H
