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
    vector<list<pair<K, V>>> table;
    int numElements;
    int sizeT;
    
public:
    ChainingHash(int n = 11){
        table.resize(n);
        numElements = 0;
        sizeT = n;
    }
    
    ChainingHash(vector<list<pair<K, V>>> other){
        table = other;
        numElements = 0;
        sizeT = other.size();
    }

    ~ChainingHash() {
        this->clear();
    }

    bool empty() {
        if(table.empty())
            return true;

        return false;
    }

    int size() {
        return sizeT;
    }

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

    void emplace(K key, V value) {
        std::pair<K, V> pair{key, value};
        insert(pair);
    }

    void insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first);
        float loadFactor;
        table[index].push_back(pair);
        this->numElements++;
        loadFactor = load_factor();
        if(loadFactor >= .75)
            rehash();
        
    }

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

    int bucket_count() {
        return numElements;
    }

    int bucket_size(int n) {
        return table[n].size();
    }

    int bucket(const K& key) {
        
        return this->hash(key);

    }

    float load_factor() {
        return ((float)numElements / (float)table.size());
    }

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
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

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

    int hash(const K& key) {
        return key % table.size();       
    }

};

#endif //__CHAINING_HASH_H
