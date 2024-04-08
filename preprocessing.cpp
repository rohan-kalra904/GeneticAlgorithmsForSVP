#include "preprocessing.h"

template<class ZT,class FT>preProcessing<ZT,FT>::preProcessing(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type)
{
    ZZ_mat<mpz_t>A;
    int status = read_file(A, input_filename);
    dim = A.get_rows();
    if(status==0)
    {
        int status = bkz_reduction(A, 2, flags_bkz, float_type,prec);
        MatGSO<ZT, FT> M(A, U, UT, flags_gso);
        M.update_gso();
        B = new ZT*[dim];
        Bstar = new FT*[dim];
        mu = new FT*[dim];
        for(int i = 0;i<dim;i++)
        {
            Bstar[i] = new FT[dim];
            mu[i] = new FT[dim];
            B[i] = new ZT[dim];
        }
        for(int i = 0;i<dim;i++)
        {
            for(int j = 0;j<dim;j++)
            {
                M.get_gram(Bstar[i][j],i,j);
                M.get_mu(mu[i][j],i,j);
                B[i][j] = A[i][j];
            }
        }
    }
    else
    {
        cout<<"Error in read file\n";
        
    }


}