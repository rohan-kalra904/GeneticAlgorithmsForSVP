#include <cstring>
#include <memory>
#include <fplll.h>
#include "test_utils.h"
#include "paper-1ls.h"
#include <iostream>
#include <fplll.h>
#include <cmath>
#include <fplll.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include<random>
using namespace std;
using namespace fplll;
#include "Individual.h"


#ifndef TESTDATADIR
#define TESTDATADIR ".."
#endif

int main(int /*argc*/, char ** /*argv*/)
{
     


    Paper1_ls<Z_NR<mpz_t>,FP_NR<mpfr_t>>* p1 = new Paper1_ls<Z_NR<mpz_t>,FP_NR<mpfr_t>>("lattices/SVPchallenge",BKZ_DEFAULT,GSO_DEFAULT,10,FT_DEFAULT);
    Individual<Z_NR<mpz_t>,FP_NR<mpfr_t>>v0;

    Z_NR<mpz_t>* ans=p1->runGA(1500,10,v0);
    for(int i=0;i<90;i++)cout<<ans[i]<<" ";
    cout<<endl;

}