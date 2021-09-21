#include "pa5.h"


double populate(Hash<int, int> *hash)
{
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 1; i < 1000001; i++)
        hash->insert(std::make_pair(i, i));
    
    auto stop = std::chrono::high_resolution_clock::now();
    return (double)std::chrono::duration_cast<std::chrono::microseconds>( stop - start ).count();
}

double search(Hash<int, int>* hash, int num)
{
    auto start = std::chrono::high_resolution_clock::now();
    int val = hash->operator[](num);
    if(val != num)
        std::cout << "Search unsuccessful!\n";

    auto stop = std::chrono::high_resolution_clock::now();
    
    return (double)std::chrono::duration_cast<std::chrono::microseconds>( stop - start ).count();
}

double remove(Hash<int, int>* hash, int num)
{
    auto start = std::chrono::high_resolution_clock::now();
    hash->erase(num);
    auto stop = std::chrono::high_resolution_clock::now();
    return (double)std::chrono::duration_cast<std::chrono::microseconds>( stop - start ).count();
}

double populateParallel(Hash<int, int>* hash, int numThreads)
{
    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel 
    {
        switch(numThreads)
        {
            case 1:
                for(int i = 1; i < 1000001; i++)
                    hash->insert(std::make_pair(i, i));
                break;
            case 2:
                if(omp_get_thread_num() == 0)
                {
                    for(int i = 1; i < 500000; i++)
                        hash->insert(std::make_pair(i, i));
                }
                else
                {
                    for(int i = 500000; i < 1000001; i++)
                        hash->insert(std::make_pair(i, i));
                }            
                break;
            case 3:
                if(omp_get_thread_num() == 0)
                    {
                        for(int i = 1; i < 350000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    else if(omp_get_thread_num() == 1)
                    {
                        for(int i = 350000; i < 700000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    else
                    {
                        for(int i = 700000; i < 1000001; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    
                break;
            case 4: 
                if(omp_get_thread_num() == 0)
                    {
                        for(int i = 1; i < 250000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    else if(omp_get_thread_num() == 1)
                    {
                        for(int i = 250000; i < 500000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    else if(omp_get_thread_num() == 2)
                    {
                        for(int i = 500000; i < 750000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    else
                    {
                        for(int i = 750000; i < 1000000; i++)
                            hash->insert(std::make_pair(i, i));
                    }
                    
                break;
        }  
    } 
              
    
        auto stop = std::chrono::high_resolution_clock::now();
        return (double)std::chrono::duration_cast<std::chrono::microseconds>( stop - start ).count();

}

