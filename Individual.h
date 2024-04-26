#pragma once
#include <cmath>
#include <fplll.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include<random>
#include "test_utils.h"
using namespace std;
using namespace fplll;
template<class ZT,class FT>
class Individual {
public:
    FT norm;
    static  ZT* common_memory; // Initialization with nullptr
    ZT* x;
    ZT* y;
    FT get_norm(ZT* vect, int dim);
    ZT* matrix_multiply(ZT* vec, ZT** mat, int dim);
    ZT* YtoX(ZT* y,FT**mu,int dim);
    Individual(int dim, FT** mu, FT* alpha, ZT** B, FT** Bstar);
    Individual();
    ~Individual();
};
