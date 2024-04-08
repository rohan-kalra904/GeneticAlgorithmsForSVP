#include <cstring>
#include <memory>
#include <fplll.h>
using namespace std;
using namespace fplll;
#include "test_utils.h"
// #include "repres.h"
// #include "crossover.h"
#include <iostream>
#include <fplll.h>
#include <cmath>
#include <fplll.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include<random>
// #include "GA.h"
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
template<class ZT,class FT>
class Individual {
public:
    FT norm;
    ZT* x;
    ZT* y;
    FT get_norm(ZT* vect, int dim);
    ZT* matrix_multiply(ZT* vec, ZT** mat, int dim);
    ZT* YtoX(ZT* y,FT**mu,int dim);
    Individual(int dim, FT** mu, FT* alpha, ZT** B, FT** Bstar);
    Individual();
    ~Individual();
};
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
template<class ZT,class FT> class GA
{
    public: 
    repres<ZT,FT> *popObj;
    virtual int selection(int k)=0;
    virtual bool* cross(bool* a,bool* b,ZT tot_length)=0;
    virtual bool* mutation(bool* a,ZT tot_length)=0;
    GA(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type);
    virtual ZT* runGA(FT targetNorm,int k)=0;
    virtual Individual<ZT,FT>*runCrossMut(int dim,int k)=0;
};
template<class ZT, class FT>
class Paper1: public GA<ZT, FT> {
public:
    using GA<ZT, FT>::popObj;
    int selection(int k) override;
    bool* cross(bool* a, bool* b, ZT tot_length) override;
    bool* mutation(bool* a, ZT tot_length) override;
    Individual<ZT, FT>* runCrossMut(int dim, int k) override;
    static bool compare(Individual<ZT, FT> &i1, Individual<ZT, FT> &i2);
    Paper1(const char *input_filename,int flags_bkz, int flags_gso, int prec, FloatType float_type);
    bool* logical_xor(bool* a, bool* b, ZT tot_length);
    bool* logical_and(bool* a, bool* b, ZT tot_length);
    ZT* runGA(FT targetNorm, int k) override;
    Paper1();
};

using namespace std;
using namespace fplll;


#ifndef TESTDATADIR
#define TESTDATADIR ".."
#endif

int main(int /*argc*/, char ** /*argv*/)
{


     Paper1<Z_NR<long>,FP_NR<long double>> *p1= new Paper1<Z_NR<long>,FP_NR<long double>>();
// //    Z_NR<mpz_t>* ans=p1->runGA(1600,10);
//     for(int i=0;i<56;i++)cout<<ans[i]<<" ";
//     cout<<endl;

}