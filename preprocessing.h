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
template<class ZT,class FT>class preProcessing
{
    public:
        int dim;
        Matrix<ZT>U;
        Matrix<ZT>UT;
        ZT** B;
        FT** Bstar;
        FT** mu;
        preProcessing(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type);
};