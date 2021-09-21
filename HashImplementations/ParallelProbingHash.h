#ifndef PARALLEL_PROBING_HASH_H
#define PARALLEL_PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "ProbingHash.h"


#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table


template<typename K, typename V>
class ParallelProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<pair<K, V>, EntryState>> table;
    int markedDeleted;
    int numElements;
    int sizeT;

public:
    ParallelProbingHash(int n = 11) {
        sizeT = n;
        table.resize(n);
        markedDeleted = 0;
    
    }

    ~ParallelProbingHash() {
        // Needs to actually free all table contents
        table.clear();
    }

    bool empty() {
        if(table.empty())
            return true;
            
        return false;
    }

    int size() {
        return sizeT - markedDeleted;
    }

    V& at(const K& key) {
        int keyIncrement = key;
        pair<K, V>* pair = &(table.at(this->hash(key))).first;
                    
        while(pair->first != key && (keyIncrement - key) != this->size())
        {                
            pair = &(table.at(this->hash(keyIncrement++))).first;
        }
        if(pair->first == key)
            return pair->second;
        else
            std::cout << "Key not in Hash!\n";   
                
      
        
        return *(new V());

       
    }

    V& operator[](const K& key) {
        int keyIncrement = key;
        pair<pair<K, V>, EntryState>* pair = &table[this->hash(key)]; // its possible that this index doesnt work if it was already taken; unless hash accomodates for that
        if(pair->first.first != 0)
        {
            while(pair->first.first != key && (keyIncrement - key) != this->size())
            {
                pair = &table.at(this->hash(keyIncrement++));
            }
            if(pair->first.first == key)
                return pair->first.second;
            else
                std::cout << "Key not in hash!\n";
                
        }
        else
            std::cout << "Key not in hash!\n";
        

        return *(new V());
    }

    int count(const K& key) { // its possible that this index doesnt work if it was already taken; unless hash accomodates
        int index, keyIncrement = key;
        if(table[this->hash(key)].first.first == key)
            index = this->hash(key);
        else
        {
            do
            {            
                index = hash(keyIncrement++);
            }
            while(table[index].first.first != key && (keyIncrement - key) != this->size());
            if((keyIncrement - key) == this->size())
                std::cout << "Bucket corresponding to key not found!\n";
        }
        
        
        return index;
        
    }

    void emplace(K key, V value) {
        std::pair<K, V> pair{key, value};
        insert(pair);
    }

    void insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first), keyIncrement = pair.first;
        float loadFactor;

        
            if(table[index].second == DELETED || table[index].second == EMPTY)
            {
                table[index].first = pair;
                table[index].second = VALID;
            }
            else
            {          
                #pragma omp critical
                {
                    do
                    {
                        index = hash(keyIncrement++);
                        if(keyIncrement - pair.first == this->size())
                            break;
                    } while (table[index].second == VALID);
                    table[index].first = pair;
                    table[index].second = VALID;
                }  
                
            }
            numElements++;
            loadFactor = load_factor();
            if(loadFactor >= .75)
                rehash();
        
            
    }

    void erase(const K& key) {
        int index = hash(key), keyIncrement = key;
        #pragma omp critical (erase)
        {
            if(table[index].first.first == key)
            {
                table[index].second = DELETED;
                markedDeleted++;
            } else 
            {
                do
                {                
                    index = hash(keyIncrement++);
                    if((keyIncrement - key) == this->size())
                        break;
                } while(table[index].first.first != key);
                if(table[index].first.first == key)
                {
                    table[index].second = DELETED;
                    markedDeleted++;    
                }
                else
                {
                    std::cout << "Could not find Key in Hash...\n";
                }
                
                
            }
        }
        
    }

    void clear() {
        table.clear(); 
    } 

    int bucket_count() { 
        return numElements;
    }

    int bucket_size(int n) { 
        return sizeof(table[n]);
    }

    int bucket(const K& key) {
        int count = 0, keyIncrement = key, index = hash(key); 
        while(table[index].first.first != key && (keyIncrement - key) != this->size())
        {        
            index = hash(keyIncrement++);
        }
        if(table[index].first.first == key)
            count = index;
        else
            std::cout << "Could not find Bucket corresponding to Key!\n";
        
        return count;

    }

    float load_factor() {
        return ((float)numElements/(float)this->size());
    }

    void rehash() {
        vector<pair<pair<K, V>, EntryState>> copy{table};
        int i = 0;
        
            this->clear();
        
            i = findNextPrime(this->size() * 2);
            table.resize(i);
            sizeT = i;
            numElements = 0;
            
            i = 0;
            while(i <= (int)(copy.size() - 1) && copy[i].second != EMPTY)
            {
                this->insert(copy[i].first);
                i++;
                numElements++;
            }
        
            
        
        
    }

    void rehash(int n) {
        vector<pair<pair<K, V>, EntryState>> copy{table};
        int i = 0;
        #pragma omp critical (rehash2)
        {
            this->clear();
        
            n = findNextPrime(n);
            table.resize(n);
            sizeT = n;
            numElements = 0;

            i = 0;
            while(i <= (int)(copy.size() - 1) && copy[i].second != EMPTY)
            {
                this->insert(copy[i].first);
                i++;
                numElements++;
            }
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

#endif //__PROBING_HASH_H
