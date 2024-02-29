#include <cstring>
#include <fplll/gso_gram.h>
#include <fplll/gso_interface.h>
#include <fplll/gso_gram.h>
#include <fplll/householder.h>
#include <fplll/nr/matrix.h>
#include "test_utils.h"
using namespace std;
using namespace fplll;

#ifndef TESTDATADIR
#define TESTDATADIR ".."
#endif

template <class ZT, class FT> int genetic_algorithm(ZZ_mat<ZT> &A)
{
    int r = A.r;

    ZZ_mat<ZT> U;
    ZZ_mat<ZT> UT;

    MatGSO<Z_NR<ZT>, FP_NR<FT>> Mbuf(A, U, UT, GSO_INT_GRAM);
    

}

template <class ZT, class FT> int matrix_input(const char *input_filename)
{
    ZZ_mat<ZT>A;
    int status = read_file(A, input_filename);

    if (status == 1)
    {
        return 1;
    }
    return 0;

}

int main(int /*argc*/, char ** /*argv*/)
{

    const auto p1 = std::chrono::system_clock::now();

    if(matrix_input<mpz_t,mpfr_t>(TESTDATADIR "/lattices/SVPChallenge.txt"))
    {
        cout<<"Genetic Algorithm succesful\n";
        std::cout << "seconds since epoch: "
              << std::chrono::duration_cast<std::chrono::seconds>(
                   p1.time_since_epoch()).count() << '\n';

    }
    else
    {
        cout<<"Error\n";
    }


}