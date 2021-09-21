#ifndef PA5_H
#define PA5_H
#define _CRT_SECURE_NO_WARNINGS
#include "ChainingHash.h"
#include "ProbingHash.h"
#include "ParallelProbingHash.h"
#include <ctime>
#include <fstream>
#include <chrono>
#include <omp.h>


double populate(Hash<int, int> *hash);

double search(Hash<int, int>* hash, int num);

double remove(Hash<int, int>* hash, int num);

double populateParallel(Hash<int, int>* hash, int numThreads);



#endif