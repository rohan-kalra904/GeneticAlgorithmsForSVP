#pragma once
#include <cmath>
#include <fplll.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include<random>
#include "test_utils.h"
#include "preprocessing.h"
#include "Individual.h"
using namespace std;
using namespace fplll;

template<class ZT,class FT>
class repres {
public:
    int pop_size;
    int dim;
    FT* alpha;
    ZT* length;
    ZT totLength;
    Individual<ZT,FT>* population;
    preProcessing<ZT,FT>* preprocess;
    ZT* decode(bool *chromosome);
    FT get_norm(ZT* vect, int dim);
    FT get_norm(FT* vect, int dim);
    bool* encode(ZT* y, ZT totalLength);
    void initialise();
    repres(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type);
    ZT **get_B();
    FT** get_mu();
};