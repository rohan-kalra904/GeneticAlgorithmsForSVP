#include "Individual.h"
template<class ZT, class FT>
ZT* Individual<ZT, FT>::common_memory = new ZT[1];
template<class ZT,class FT>
ZT* Individual<ZT,FT>::matrix_multiply(ZT* vec, ZT** mat, int dim) {
    ZT* result = new ZT[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = 0;
        for (int j = 0; j < dim; ++j) {
            ZT temp; 
            temp.mul(vec[j], mat[i][j]);
            result[i].add(result[i], temp);
        }
    }
    return result;
}
template<class ZT,class FT>
ZT* Individual<ZT,FT>::YtoX(ZT* y,FT** mu, int dim) {
    ZT* x = new ZT[dim];
    for (int i = dim - 1; i >= 0; i--) {
        FT t=0.0;
        for(int j=i+1;j<dim;j++)
        {
            FT temp;
            temp.set_z(x[j]);
            t+=mu[j][i]*temp;
        }
        t.rnd(t);
        ZT t_z;
        t_z.set_f(t);
        x[i].sub(y[i],t_z);
    }
    return x;
}
template<class ZT,class FT>
Individual<ZT,FT>::Individual(int dim, FT** mu, FT* alpha, ZT** B, FT** Bstar) {
    this->x = new ZT[dim];
    this->y = new ZT[dim];
    ZT* alpha_r=new ZT[dim];
    for(int i=0;i<dim;i++)
    {
        FT temp=alpha[i];
        alpha[i].floor(alpha[i]);
        ZT use;
        use.set_f(alpha[i]);
        alpha_r[i].add_ui(use,1);
        alpha[i]=temp;
    }
    for (int i = dim - 1; i >= 0; i--) {
        y[i].randm(alpha_r[i]);
        FT t=0.0;
        for(int j=i+1;j<dim;j++)
        {
            FT temp;
            temp.set_z(x[j]);
            t+=mu[j][i]*temp;
        }
        t.rnd(t);
        ZT t_z;
        t_z.set_f(t);
        x[i].sub(y[i],t_z);    
    }
    ZT* vect = matrix_multiply(x, B, dim);
    this->norm = get_norm(vect, dim);
    delete[] vect;
}
template <class ZT,class FT>
FT Individual<ZT,FT>::get_norm(ZT* vect, int dim) {
    FT norm = 0.0;
    for (int i = 0; i < dim; ++i) {
        FT use;
        use.set_z(vect[i]);
        norm += use * use;
    }
    return sqrt(norm);
}
template<class ZT,class FT>
Individual<ZT,FT>::~Individual() 
{
    // if(this->x!=NULL)
    // {
    //     for(int i = 0;i<60;i++)cout<<x[i]<<" ";
    //     cout<<"\n";
    // }
    // // else  cout<<"Hello\n";
    // if(this->y!=NULL)
    // {
    //     for(int i = 0;i<60;i++)cout<<y[i]<<" ";
    //     cout<<"\n";
    //     // delete[]y;

    // }
    // else cout<<"Hello\n";
}
template<class ZT,class FT>
Individual<ZT,FT>::Individual()
{
    this->x = NULL;
    this->y = NULL;
    this->norm = 0.0;
    // this->x=common_memory;
    // this->y=common_memory;
    // x=new ZT[]
}