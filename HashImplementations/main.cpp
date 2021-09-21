#include "pa5.h"

/* How did the serial implementations for the ChainingHash and ProbingHash compare to each other? Did you expect the time results obtained? Explain.
    The Chaining Hash was faster at searching and removing while the Probeing Hash was faster at inserting items. I was expecting something like this since Probing Hash 
    does not depend on an extra data structure like Chaining Hash does.  

      (8 pts) Compare the parallel and serial implementations for the ProbingHash. Did the parallel implementations provide you with the expected speedup? Explain.
    If the parallel implementation would have been implemented with precise knowledge of how to use openmp, it would most likely result in a speedup. It's difficult to say
    based on this program because the parallel implementation is neither efficient nor fully-functioning.

      (8 pts) What could you change in your parallel implementations to improve performance and speedup? Explain. 
    I could add parallel sections and use more precise keywords for the proper situations and connotations. Additionally, if the parallel implementation were
    fully-functioning, it would in and of itself improve performace and speedup.
      */
 

int main()
{
    ChainingHash<int, int> *hashT1 = new ChainingHash<int, int>(101);
    ProbingHash<int, int> *hashT2 = new ProbingHash<int, int>(101);
    ParallelProbingHash<int, int> *hashT3 = new ParallelProbingHash<int, int>(101);
    double timeInsert1 = 0, timeInsert2 = 0, timeInsert3 = 0, timeSearch1 = 0, timeSearch2 = 0, timeSearch3 = 0, timeRemove1 = 0, timeRemove2 = 0, timeRemove3 = 0;
    std::fstream iFile;
    iFile.open("HashAnalysis.txt", std::ios::out);


    timeInsert1 = populate(hashT1) / CLOCKS_PER_SEC;
    timeInsert2 = populate(hashT2) / CLOCKS_PER_SEC;
    iFile << "ChainingHash object insert execution time: " << timeInsert1 << "\n";
    iFile << "ProbingHash object insert execution time: " << timeInsert2 << "\n\n";
    timeSearch1 = search(hashT1, 117) / CLOCKS_PER_SEC;
    timeSearch2 = search(hashT2, 117) / CLOCKS_PER_SEC; // probe hash's search isn't working
    iFile << "ChainingHash object search (for 117) execution time: " << timeSearch1 << std::endl;
    iFile << "ProbingHash object search (for 117) execution time: " << timeSearch2 << "\n\n";
    timeSearch1 = search(hashT1, 2000000) / CLOCKS_PER_SEC;
    timeSearch2 = search(hashT2, 2000000) / CLOCKS_PER_SEC; 
    iFile << "ChainingHash object search (for 2000000) execution time: " << timeSearch1 << std::endl;
    iFile << "ProbingHash object search (for 2000000) execution time: " << timeSearch2 << "\n\n";
    timeRemove1 = remove(hashT1, 117) / CLOCKS_PER_SEC;
    timeRemove2 = remove(hashT2, 117) / CLOCKS_PER_SEC; // since the probe hash's search doesnt work, remove can't find the value either
    iFile << "ChainingHash object removal (for 117) execution time: " << timeRemove1 << std::endl;
    iFile << "ProbingHash object removal (for 117) execution time: " << timeRemove2 << "\n\n";
    iFile << "Chaining Hash:\nFinal Size: " << hashT1->size() << "\nBucket Count: " << hashT1->bucket_count() << "\nLoad Factor: " << hashT1->load_factor();
    iFile << "\n\nProbing Hash:\nFinal Size: " << hashT2->size() << "\nBucket Count: " << hashT2->bucket_count() << "\nLoad Factor: " << hashT2->load_factor();

    timeInsert3 = populate(hashT3) / CLOCKS_PER_SEC;
    timeSearch3 = search(hashT3, 117) / CLOCKS_PER_SEC; // the same as probe hash with parallelprobe hash
    timeRemove3 = remove(hashT3, 117) / CLOCKS_PER_SEC; 
    iFile << "ParallelProbingHash (one thread) object insert execution time: " << timeInsert3 << "\n";
    iFile << "ParallelProbingHash (one thread) object search (for 117) execution time: " << timeSearch3 << "\n";
    iFile << "ParallelProbingHash (one thread) object removal (for 117) execution time: " << timeRemove3 << "\n\n";
    timeSearch3 = search(hashT3, 2000000);
    iFile << "ParallelProbingHash (one thread) object search (for 2000000) execution time: " << timeSearch3 << "\n";
    iFile << "\n\nParallelProbing Hash:\nFinal Size: " << hashT3->size() << "\nBucket Count: " << hashT3->bucket_count() << "\nLoad Factor: " << hashT3->load_factor() << "\n\n";
    hashT3->clear();
    hashT3 = new ParallelProbingHash<int, int>(101);

    timeInsert3 = populate(hashT3) / CLOCKS_PER_SEC; // 4 is the amount of cores my computer has
    iFile << "ParallelProbingHash (multithread) object insert execution time: " << timeInsert3 << "\n";

    #pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num() == 0)
        {
            #pragma omp critical 
            {
                timeSearch3 = search(hashT3, 117) / CLOCKS_PER_SEC;
                iFile << "ParallelProbingHash (multithread) object search execution time: " << timeSearch3 << "\n";
            }

        }   
        else
        {
            #pragma omp critical
            {
                timeSearch3 = search(hashT3, 2000000) / CLOCKS_PER_SEC;
                iFile << "ParallelProbingHash (multithread) object search execution time: " << timeSearch3 << "\n";
            }

        }
        
    }

    timeRemove3 = remove(hashT3, 117) / CLOCKS_PER_SEC; // same as probe hash's remove
    iFile << "ParallelProbingHash (one thread) object removal (for 117) execution time: " << timeRemove3 << "\n\n";
    iFile << "\n\nParallelProbing Hash:\nFinal Size: " << hashT3->size() << "\nBucket Count: " << hashT3->bucket_count() << "\nLoad Factor: " << hashT3->load_factor();
    




    







    return 0;
}