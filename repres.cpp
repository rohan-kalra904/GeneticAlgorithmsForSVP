#include "repres.h"
using namespace std;
using namespace fplll;
template<class ZT,class FT>repres<ZT,FT>::repres(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type)
{

        preprocess = new preProcessing<ZT,FT>(input_filename, flags_bkz, flags_gso, prec, float_type);
        dim = preprocess->dim;
        pop_size = 2*dim;
        FT normB0 = get_norm(preprocess->Bstar[0],dim);
        FT log2 = log(2);
        alpha=new FT[dim];
        length=new ZT[dim];
        totLength = 0;
        for(int i = 0;i<dim;i++)
        {
            alpha[i] = normB0/get_norm(preprocess->Bstar[i],dim);
            length[i] .set_f(floor(log(alpha[i])/log2)+FT(2));
            totLength.add(totLength,length[i]);
        }
}
template <class ZT,class FT>
FT repres<ZT,FT>::get_norm(FT* vect, int dim) {
    FT norm = 0.0;
    for (int i = 0; i < dim; ++i) {
        FT use=vect[i];
        norm += use * use;
    }
    return sqrt(norm);
}


template <class ZT,class FT>
FT repres<ZT,FT>::get_norm(ZT* vect, int dim) {
    FT norm = 0.0;
    for (int i = 0; i < dim; ++i) {
        FT use = vect[i].get_d();
        norm += use * use;
    }
    return sqrt(norm);
}


template<class ZT,class FT>
ZT* repres<ZT,FT>::decode(bool *chromosome) {
    ZT *y = new ZT[dim];
    int start = 0;
    for (int i = 0; i < dim; i++) {
        ZT mult;
        mult=(long)1; // Changed pointer to value
        for (int j = start + (int)length[i].get_d() - 1; j > start; j--) {
            ZT use = mult;
            long temp=chromosome[j];
            use.mul_si(use,temp);
            y[i].add(y[i], use);
            mult.mul_si(mult, (long)2);
        }
        if (chromosome[start]) y[i].mul_si(y[i], (long)-1);
        start = start + (int)length[i].get_d();
    }
    return y;
}

template<class ZT,class FT>
bool* repres<ZT,FT>::encode(ZT* y, ZT totalLength) {
    bool* chromosome = new bool[(int)totalLength.get_d()];
    ZT tot;
    tot = (long)0;
    for (int i = 0; i < dim; i++) {
        bool sign = 0;
        ZT element = y[i];
        if (y[i] < (long)0) {
            sign = 1;
            element.neg(element);
        }
        ZT curEl = y[i];
        for (int j = tot.get_d() + length[i].get_d() - 1; j > tot.get_d(); j--) {
            ZT curBit, mod_;
            mod_=(long)2;
            curBit.mod(curEl, mod_);
            chromosome[j] = (int)curBit.get_d();
            curEl.div_2si(curEl, 1);//divide by 2^1
        }
        chromosome[(int)tot.get_d()] = sign;
        tot.add(tot, length[i]);
    }
    return chromosome;
}

template<class ZT,class FT>
void repres<ZT,FT>::initialise(Individual<ZT,FT>v0) {
    //cout<<pop_size<<endl;

    population = new Individual<ZT,FT>[pop_size];
    if(v0.x==NULL)
    {
        population[0].y = new ZT[dim] ;
        population[0].y[0] = 1;
        for(int i = 1;i<dim;i++)population[0].y[i] = 0;

        population[0].x = population[0].YtoX(population[0].y,preprocess->mu,dim);
        ZT* vect = population[0].matrix_multiply(population[0].x, preprocess->B,dim);
        population[0].norm = population[0].get_norm(vect,dim);
    }
    else 
        population[0] = v0;
    for (int i = 1; i < pop_size; i++) {
       // cout<<1<<endl;
        population[i] = Individual<ZT,FT>(dim, preprocess->mu, alpha, preprocess->B, preprocess->Bstar);
    }
}
template<class ZT,class FT>ZT** repres<ZT,FT>::get_B()
{
    return preprocess->B;
}
template<class ZT,class FT>FT** repres<ZT,FT>::get_mu()
{
    return preprocess->mu;
}